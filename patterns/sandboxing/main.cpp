#include <functional>
#include <iostream>

#include <linux/audit.h>
#include <linux/filter.h>
#include <linux/seccomp.h>
#include <sys/prctl.h>
#include <sys/ptrace.h>
#include <sys/syscall.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <unistd.h>

class SecurityDomain
{
public:
    using Task = std::function<void ()>;

    explicit SecurityDomain(Task task)
        : m_task(task) {}

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
            struct sock_filter filter[] = {
            /* seccomp(2) says we should always check the arch */
            /* as syscalls may have different numbers on different architectures */
            /* see https://fedora.juszkiewicz.com.pl/syscalls.html */
            /* for simplicity we only allow x86_64 */
            BPF_STMT(BPF_LD | BPF_W | BPF_ABS, (offsetof(struct seccomp_data, arch))),
            /* if not x86_64, tell the kernel to kill the process */
            BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, AUDIT_ARCH_X86_64, 0, 4),
            /* get the actual syscall number */
            BPF_STMT(BPF_LD | BPF_W | BPF_ABS, (offsetof(struct seccomp_data, nr))),
            /* if "uname", tell the kernel to return EPERM, otherwise just allow */
            BPF_JUMP(BPF_JMP | BPF_JEQ | BPF_K, SYS_uname, 0, 1),
            BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ERRNO | (EPERM & SECCOMP_RET_DATA)),
            BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_ALLOW),
            BPF_STMT(BPF_RET | BPF_K, SECCOMP_RET_KILL),
        };

        struct sock_fprog prog = {
            .len = (unsigned short) (sizeof(filter) / sizeof(filter[0])),
            .filter = filter,
        };

        /* see seccomp(2) on why this is needed */
        if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
            perror("PR_SET_NO_NEW_PRIVS failed");
            exit(1);
        };

        /* glibc does not have a wrapper for seccomp(2) */
        /* invoke it via the generic syscall wrapper */
        if (syscall(SYS_seccomp, SECCOMP_SET_MODE_FILTER, 0, &prog)) {
            perror("seccomp failed");
            exit(1);
        };
    }

private:
    Task m_task;
};

int main()
{
    SecurityDomain domain([]() {
        std::cout << "Hello world" << std::endl;
        struct utsname name;
        if (uname(&name)) {
            throw std::runtime_error("uname failed");
        }
    });

    try
    {
        domain.Enter();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}