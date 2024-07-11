#ifdef WITH_SELINUX
#include "selinux_policy.h"
#endif // WITH_SELINUX

#include "composite_policy.h"
#include "seccomp_policy.h"

#include <sys/wait.h>

#include <functional>
#include <iostream>
#include <memory>

class SecurityDomain
{
public:
    using Task = std::function<void ()>;

    explicit SecurityDomain(Task task)
        : m_task(task) {
        m_policy.AddPolicy(std::make_unique<SeccompPolicy>());
#ifdef WITH_SELINUX
        m_policy.AddPolicy(std::make_unique<SELinuxPolicy>());
#endif // WITH_SELINUX
    }

    void Enter() {
        const pid_t child_pid = fork();

        if (child_pid < 0) {
            throw std::runtime_error("Fork failed");
        } else if (child_pid == 0) {
            // Code executed by child process
            GoToSandox();
            m_task();
        } else {
            // Code executed by parent process
            std::cout << "Parent process: Child process ID is " << child_pid << std::endl;
            // Wait for the child process to complete
            int status{0};
            waitpid(child_pid, &status, 0);
            if (WIFEXITED(status)) {
                std::cout << "Parent process: Child exited with status " << WEXITSTATUS(status) << std::endl;
            }
        }
    }

private:
    void GoToSandox() {
        m_policy.Apply();
    }

private:
    Task m_task;
    CompositePolicy m_policy;
};

int main()
{
    try
    {
        SecurityDomain domain([]() {
            std::cout << "Hello world" << std::endl;
        });
        domain.Enter();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
