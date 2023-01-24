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
pXk3JNmGVzDxT9tta2m2tXSw7uZI6mKV/NFDY+pYj+gdx26/dTFi+3qz+Sl6F90mqvZeR3FS66Laux8NNjuWbp3apDLa8h2TutqYKquE5N3EV/WB684ktpqHRbyE68+eUxMfuxFOFpTCfCQXMjBbAAlaqXY/EoQtbxOYniAx1kreqjip57TEyawb9GMUbM0qeLuauLEZgkigjTXQ97QQ/B89mu+pEywQp/Eg0oY4p1yt3LAC9lvPgAJDRxjiJHlBrsVkPAYq+VZSyUGoxs+Ns2p5wdWW5uG8nls2twDny5X5OHBpvrh5mBwMy1pgOJ193OPhjJnmAbmtcv0zjA2UzIP9SoJf3vHVwk0jexXDYgubqlap9s9qLLDJ3YJckqtFSjBcvZ5JO1ODCczkvol3++NP4cmfoRXKxy1NwmF5eOLdcuvT7FMrlF8T8HxHzgr61BEOVS655II7sfD83s89bkbht8ENeQ+T4KavWk2KpQwHxCIq6gxFJ+di0XgquhaKvqOiQVSUAUVbqehOKuoPRZ9S0bVUNBaKXqeidhIlApEMSB1m4KuVRJSlrOM42A/uK91MtXugo3EsVgjf5xX6vnpDHro51ejqkaOwuXaVIURMyXtsQvJNiWL9eBi1d4OCTGAv8I9U6x9B393rR6MJplD33f3pLR5bh123s+vX/Pd2/nsz//3ZW0Hn6ZLSmPp8ICNj5uWSPDhRkuPP
*/