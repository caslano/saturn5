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