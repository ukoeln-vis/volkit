// This file is distributed under the MIT license.
// See the LICENSE file for details.

#include <thread>
#include <unordered_map>

#include <vkt/ExecutionPolicy.hpp>

#include <vkt/ExecutionPolicy.h>

//-------------------------------------------------------------------------------------------------
// C++ API
//

namespace vkt
{
    static std::unordered_map<std::thread::id, ExecutionPolicy> threadPolicyMap;

    void SetThreadExecutionPolicy(ExecutionPolicy policy)
    {
        if (threadPolicyMap.find(std::this_thread::get_id()) == threadPolicyMap.end())
            threadPolicyMap.insert({ std::this_thread::get_id(), policy });
        else
            threadPolicyMap[std::this_thread::get_id()] = policy;
    }

    ExecutionPolicy GetThreadExecutionPolicy()
    {
        auto it = threadPolicyMap.find(std::this_thread::get_id());

        if (it == threadPolicyMap.end())
            return ExecutionPolicy();
        else
            return it->second;
    }

} // vkt


//-------------------------------------------------------------------------------------------------
// C API
//

void vktSetThreadExecutionPolicy(vktExecutionPolicy_t policy)
{
    vkt::ExecutionPolicy policyCPP;

    switch (policy.device)
    {
    case vktExecutionPolicyDeviceCPU:
        policyCPP.device = vkt::ExecutionPolicy::Device::CPU;
        break;

    case vktExecutionPolicyDeviceGPU:
        policyCPP.device = vkt::ExecutionPolicy::Device::GPU;
        break;
    }

    switch (policy.hostApi)
    {
    case vktExecutionPolicyHostAPISerial:
        policyCPP.hostApi = vkt::ExecutionPolicy::HostAPI::Serial;
        break;
    }

    switch (policy.deviceApi)
    {
    case vktExecutionPolicyDeviceAPICUDA:
        policyCPP.deviceApi = vkt::ExecutionPolicy::DeviceAPI::CUDA;
        break;
    }

    vkt::SetThreadExecutionPolicy(policyCPP);
}

vktExecutionPolicy_t vktGetThreadExecutionPolicy()
{
    vktExecutionPolicy_t policy;

    vkt::ExecutionPolicy policyCPP = vkt::GetThreadExecutionPolicy();

    switch (policyCPP.device)
    {
    case vkt::ExecutionPolicy::Device::CPU:
        policy.device = vktExecutionPolicyDeviceCPU;
        break;

    case vkt::ExecutionPolicy::Device::GPU:
        policy.device = vktExecutionPolicyDeviceGPU;
        break;
    }

    switch (policyCPP.hostApi)
    {
    case vkt::ExecutionPolicy::HostAPI::Serial:
        policy.hostApi = vktExecutionPolicyHostAPISerial;
        break;
    }

    switch (policyCPP.deviceApi)
    {
    case vkt::ExecutionPolicy::DeviceAPI::CUDA:
        policy.deviceApi = vktExecutionPolicyDeviceAPICUDA;
        break;
    }

    return policy;
}
