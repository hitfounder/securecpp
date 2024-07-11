#pragma once

#include "policy.h"

#include <selinux/selinux.h>
#include <selinux/get_context_list.h>

#include <iostream>

class SELinuxPolicy : public Policy
{
public:
    void Apply() override {
        if (!is_selinux_enabled()) {
            return;
        }

        char *curcon = 0;
        if (const int rc = getcon(&curcon); rc != 0) {
            throw std::runtime_error("Failed to get current SELinux context");
        }
        std::cout << "SELinux current context " << curcon << std::endl;
        freecon(curcon);

        constexpr char context[]{"system_u:object_r:policy_t:s0"};
        if (const int rc = security_check_context(context); rc != 0) {
            throw std::runtime_error("Context is not valid. Please execute policy.sh");
        }

        if (const int rc = setcon(context); rc != 0) {
            throw std::runtime_error("Failed to set context");
        }

        if (const int rc = getcon(&curcon); rc != 0) {
            throw std::runtime_error("Failed to get current SELinux context");
        }
        std::cout << "SELinux new context " << curcon << std::endl;
        freecon(curcon);

        std::cout << "SELinux policy applied" << std::endl;
    }
};