//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_SVM_HPP
#define BOOST_COMPUTE_SVM_HPP

#include <boost/compute/config.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/memory/svm_ptr.hpp>

// svm functions require OpenCL 2.0
#if defined(BOOST_COMPUTE_CL_VERSION_2_0) || defined(BOOST_COMPUTE_DOXYGEN_INVOKED)

namespace boost {
namespace compute {

/// Allocates a shared virtual memory (SVM) buffer.
//
/// \opencl_version_warning{2,0}
///
/// \see_opencl2_ref{clSVMAlloc}
///
/// \see svm_free()
template<class T>
inline svm_ptr<T> svm_alloc(const context &context,
                            size_t size,
                            cl_svm_mem_flags flags = CL_MEM_READ_WRITE,
                            unsigned int alignment = 0)
{
    svm_ptr<T> ptr(
        clSVMAlloc(context.get(), flags, size * sizeof(T), alignment),
        context
    );
    if(!ptr.get()){
        BOOST_THROW_EXCEPTION(opencl_error(CL_MEM_OBJECT_ALLOCATION_FAILURE));
    }
    return ptr;
}

/// Deallocates a shared virtual memory (SVM) buffer.
///
/// \opencl_version_warning{2,0}
///
/// \see_opencl2_ref{clSVMFree}
///
/// \see svm_alloc(), command_queue::enqueue_svm_free()
template<class T>
inline void svm_free(svm_ptr<T> ptr)
{
    clSVMFree(ptr.get_context(), ptr.get());
}

/// \overload
template<class T>
inline void svm_free(const context &context, svm_ptr<T> ptr)
{
    clSVMFree(context.get(), ptr.get());
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CL_VERSION_2_0

#endif // BOOST_COMPUTE_PIPE_HPP

/* svm.hpp
mwnTZy7VSXMeuVRXMPYzWdvwPVHqeaTf/qb5ZOwH2EutOHOtL864PV+1Dn+DRdK19fWnZ92J/S3Pb9daAUd3uZeEn+SP9XywrQk9ixWENXwOaK3P4rdJvm/6uhNzETaPWc6JzDBcnyea0MtYvDfm84LzjNfvbtEtleeFMpOATGeCiaXLsWEf38BYJ33nCGcOtUuO4yraL46W22yF9SR7Spln0fp9VP8w7GfF1PdYtg99j51S
*/