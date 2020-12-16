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
PAE+QRlzxhmb0k6hmgkV/SmhTg81oDaSZyghyKjomkp+3GYLfFLyTk1S3beWtavNNlxbWl0nY97FR/9Z2T9Z5POM/BjVQ0fk1SZAngL4o8gMTUojT6XJc3bgKDO2XvTvmFXUv9rIjDTj9l+X9D5J65lx2flmPsJfZd/gpIie+FFJH+mwOVGesQOBQLScaVJOCf9/JjIFppwTDlD9t9bNK7I/FLVHxZSb7Ci3RsottmyB4XMx5VZJud2M3v192T86areKKTeVbVY97c01TNZ1/838jlLWeeQdhk0uHB6XvKMC6bItKNvS9hdf9KTTg1lSVgdR+sha5WbMxxfhfElRn3aMuKGob8GUIFuknFnBcDoY+Fh+P0/KnC8HYDXA6PyM30qZw5Os/deKRVUus5wXv63j7FXXb7OD70PejyRvPscj506oLauswMtdZYqQOW1/OeZgOM2ofDmeA1lRfH+pj1Tunz/SWPvLivx+L6ucTuG4J9uCMInYhtiOuA5xJds7wq80z2p4NPl+hONJQ2REvon16Kl88YsYKPMi7M2xpTHnghwfh3GINemCzsPwi26zNqXr+vLcr+TR+zW6xrz6Pcg9KbIrjS1D7zuVXW3siJH7SoYf6Pj+fEknm/Q0SadqWtcvl+tzrfweRcTY2xarzXHXpPD91QU+k0G9jLf1RTP6ay8U4uJWzZjE0UXaXlDbnt5bmi/LtMU+B1rpP4JmjAc+D7W1aqsy8jsZH4ktVV7brspLfZg+ZFORaSf3YaUpY9uwLbNjOM+00kNM291C5GeG+yQj31/3BwOrD7LS23GNTf/q6HOQN/dwD72H30qz5A4RN3TTj8TI9rFkzXlUTAmVV0T7hhjZTJV9NsPYy2R7DYzOKTFN7eX2bfmyrcSxrUa2FTjuS9OuTD1MPEjrwT6Hiu7PgItlf5Kmg4FPJL279vWRMqN2xDLZv5N7X6DX4kq5FvsGY+pe8izLkDLl4tmfbZtJnnWTTLnIaMlynpVynqM7VvJcLU6mS+B+7rDhcck2PzfOIr9jZC6Wzp3C9/+sjmFuRPpOaI/0NxKTRDZqk1zSTB/RqH2E1R9QX455WawE9wz75Z5hm9y7Ou4nfF+k6/1Lteq2aF+QEYTSn2j7ZluPoOljLBlpc7RN0to22ZZpytM2qHPE0NbYprZZ8Vlw9iMlAWc/U2DSNXKclSYdvR70LWY+5GIXW/4L/ObikNyPjpcl8VrUNrzM6cuAfIv8Fvey2+kpy/gt7qw2+aXrufstrnQ7rqq6hP0VAwfH+SuaushKia+L16z2XuLym+KpmLCvohyD/fwyNwjvqCfz5jAEn85ge4n6HJTVRt6ArTfMuHdErXeV72X65iJJjw2aOXVi+pQ8k2eAud/LJT3Qlsf0CeYZUSoyWUHtR7SMHQLOd0T6LLNvK/Ms2E/So4O290B7363ywbi+lGeEvd82cuZ9xryrcLwTp+PCE31XmyiyewSb6rOmiEzvYDr90iCu/aoO2NWsfqn9Vh2SN7RdW+2b0lQuY/1I/3XsCNPeY2QGRWVSY2V2Jt2B9LjU8HvRvTASnyHeQ4y8Dx2t/d/KtObnv7b6sxmltv6MdBFp8w5kfPzi322i/Yq2l7h5iuxtgn4lpt+piemX6k26xvfZ+Ad8Nrx8Dy5ob22/6JpNNnvjzvf3nTah/UHJb3y+1PflaM6X4weZP1uC9BEzgzLej3vc/C9+HfPM97ToDmTfDrrOQEDHIBJlrOEYuAscB7NgifpNVMNB8FA4GB4Fh8Dj4B7wNjgUPgSHw8fVH+J5mAtfhiPh+zAPfgLz4Vdwb/gjLIS/wH1ge45tX9gR7ge7wgNgb3ggzIEHwSI4AY4=
*/