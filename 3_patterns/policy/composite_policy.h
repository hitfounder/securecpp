#pragma once

#include "policy.h"

#include <memory>
#include <vector>

class CompositePolicy : public Policy
{
public:
    void Apply() override {
        for (const auto& policy: m_policies) {
            policy->Apply();
        }
    }

    void AddPolicy(std::unique_ptr<Policy> policy) {
        m_policies.emplace_back(std::move(policy));
    }

private:
    std::vector<std::unique_ptr<Policy>> m_policies;
};