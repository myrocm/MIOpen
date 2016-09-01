#ifndef GUARD_MLOPEN_OCLDEVICE_HPP
#define GUARD_MLOPEN_OCLDEVICE_HPP

#if defined(__APPLE__) || defined(__MACOSX)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

#include <type_traits>
#include <string>
#include <mlopen/errors.hpp>

namespace mlopen { namespace detail {

template<int N>
struct ComputeDeviceAttributeReturnType;

template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_TYPE> { using type = cl_device_type; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_VENDOR_ID> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_COMPUTE_UNITS> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_WORK_GROUP_SIZE> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_WORK_ITEM_SIZES> { using type = size_t*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_CLOCK_FREQUENCY> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_ADDRESS_BITS> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_READ_IMAGE_ARGS> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_WRITE_IMAGE_ARGS> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_MEM_ALLOC_SIZE> { using type = cl_ulong; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_IMAGE2D_MAX_WIDTH> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_IMAGE2D_MAX_HEIGHT> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_IMAGE3D_MAX_WIDTH> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_IMAGE3D_MAX_HEIGHT> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_IMAGE3D_MAX_DEPTH> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_IMAGE_SUPPORT> { using type = cl_bool; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_PARAMETER_SIZE> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_SAMPLERS> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MEM_BASE_ADDR_ALIGN> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MIN_DATA_TYPE_ALIGN_SIZE> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_SINGLE_FP_CONFIG> { using type = cl_device_fp_config; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_GLOBAL_MEM_CACHE_TYPE> { using type = cl_device_mem_cache_type; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_GLOBAL_MEM_CACHE_SIZE> { using type = cl_ulong; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_GLOBAL_MEM_SIZE> { using type = cl_ulong; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE> { using type = cl_long; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_MAX_CONSTANT_ARGS> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_LOCAL_MEM_TYPE> { using type = cl_device_local_mem_type; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_LOCAL_MEM_SIZE> { using type = cl_ulong; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_ERROR_CORRECTION_SUPPORT> { using type = cl_bool; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PROFILING_TIMER_RESOLUTION> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_ENDIAN_LITTLE> { using type = cl_bool; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_AVAILABLE> { using type = cl_bool; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_COMPILER_AVAILABLE> { using type = cl_bool; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_EXECUTION_CAPABILITIES> { using type = cl_device_exec_capabilities; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_QUEUE_PROPERTIES> { using type = cl_command_queue_properties; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_NAME> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_VENDOR> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DRIVER_VERSION> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PROFILE> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_VERSION> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_EXTENSIONS> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PLATFORM> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_DOUBLE_FP_CONFIG> { using type = cl_device_fp_config; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_HOST_UNIFIED_MEMORY> { using type = cl_bool; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_NATIVE_VECTOR_WIDTH_INT> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_OPENCL_C_VERSION> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_LINKER_AVAILABLE> { using type = cl_bool; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_BUILT_IN_KERNELS> { using type = char*; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_IMAGE_MAX_BUFFER_SIZE> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_IMAGE_MAX_ARRAY_SIZE> { using type = size_t; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PARENT_DEVICE> { using type = cl_device_id; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PARTITION_MAX_SUB_DEVICES> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PARTITION_AFFINITY_DOMAIN> { using type = cl_device_affinity_domain; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_REFERENCE_COUNT> { using type = cl_uint; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PREFERRED_INTEROP_USER_SYNC> { using type = cl_bool; };
template<> struct ComputeDeviceAttributeReturnType<CL_DEVICE_PRINTF_BUFFER_SIZE> { using type = size_t; };

template<int N>
using DeviceAttributeReturnType = typename ComputeDeviceAttributeReturnType<N>::type;

template<class T>
struct GetDeviceInfoImpl
{
    static T apply(int N, cl_device_id device)
    {
        T result;
        auto status = clGetDeviceInfo(device, N, sizeof(T), &result, nullptr);
        if (status != CL_SUCCESS) { MLOPEN_THROW_CL_STATUS(status);
}
        return result;
    }
};


template<class T>
struct GetDeviceInfoImpl<T*>
{
    using type = typename std::conditional<
        std::is_same<T, char>::value, 
        std::string, 
        std::vector<T>
    >::type;

    static int GetSize(int N, cl_device_id device)
    {
        size_t size;
        auto status = clGetDeviceInfo(device, N, 0, nullptr, &size);
        if (status != CL_SUCCESS) { MLOPEN_THROW_CL_STATUS(status); }
        return size/sizeof(T);
    }

    static type apply(int N, cl_device_id device)
    {
        type result(GetSize(N, device), 0);
        auto status = clGetDeviceInfo(device, N, result.size()*sizeof(T), reinterpret_cast<void*>(&result[0]), nullptr);
        if (status != CL_SUCCESS) { MLOPEN_THROW_CL_STATUS(status); }
		if(std::is_same<T, char>()) { result.pop_back(); }
        return result;
    }
};
} // namespace detail

template<int N>
auto GetDeviceInfo(cl_device_id device) MLOPEN_RETURNS(detail::GetDeviceInfoImpl<detail::DeviceAttributeReturnType<N>>::apply(N, device));

} // namespace mlopen
#endif //GUARD_MLOPEN_OCLDEVICE_HPP