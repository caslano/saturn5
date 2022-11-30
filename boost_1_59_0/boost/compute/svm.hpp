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
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
*/