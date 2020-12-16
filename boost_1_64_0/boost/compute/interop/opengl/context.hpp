//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENGL_CONTEXT_HPP
#define BOOST_COMPUTE_INTEROP_OPENGL_CONTEXT_HPP

#include <boost/throw_exception.hpp>

#include <boost/compute/device.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/context.hpp>
#include <boost/compute/exception/unsupported_extension_error.hpp>
#include <boost/compute/interop/opengl/cl_gl.hpp>

#ifdef __APPLE__
#include <OpenCL/cl_gl_ext.h>
#include <OpenGL/OpenGL.h>
#endif

#ifdef __linux__
#include <GL/glx.h>
#endif

namespace boost {
namespace compute {

/// Creates a shared OpenCL/OpenGL context for the currently active
/// OpenGL context.
///
/// Once created, the shared context can be used to create OpenCL memory
/// objects which can interact with OpenGL memory objects (e.g. VBOs).
///
/// \throws unsupported_extension_error if no CL-GL sharing capable devices
///         are found.
inline context opengl_create_shared_context()
{
    // name of the OpenGL sharing extension for the system
#if defined(__APPLE__)
    const char *cl_gl_sharing_extension = "cl_APPLE_gl_sharing";
#else
    const char *cl_gl_sharing_extension = "cl_khr_gl_sharing";
#endif

#if defined(__APPLE__)
    // get OpenGL share group
    CGLContextObj cgl_current_context = CGLGetCurrentContext();
    CGLShareGroupObj cgl_share_group = CGLGetShareGroup(cgl_current_context);

    cl_context_properties properties[] = {
        CL_CONTEXT_PROPERTY_USE_CGL_SHAREGROUP_APPLE,
        (cl_context_properties) cgl_share_group,
        0
    };

    cl_int error = 0;
    cl_context cl_gl_context = clCreateContext(properties, 0, 0, 0, 0, &error);
    if(!cl_gl_context){
        BOOST_THROW_EXCEPTION(opencl_error(error));
    }

    return context(cl_gl_context, false);
#else
    typedef cl_int(*GetGLContextInfoKHRFunction)(
        const cl_context_properties*, cl_gl_context_info, size_t, void *, size_t *
    );

    std::vector<platform> platforms = system::platforms();
    for(size_t i = 0; i < platforms.size(); i++){
        const platform &platform = platforms[i];

        // check whether this platform supports OpenCL/OpenGL sharing
        if (!platform.supports_extension(cl_gl_sharing_extension))
          continue;

        // load clGetGLContextInfoKHR() extension function
        GetGLContextInfoKHRFunction GetGLContextInfoKHR =
            reinterpret_cast<GetGLContextInfoKHRFunction>(
                reinterpret_cast<size_t>(
                    platform.get_extension_function_address("clGetGLContextInfoKHR")
                )
            );
        if(!GetGLContextInfoKHR){
            continue;
        }

        // create context properties listing the platform and current OpenGL display
        cl_context_properties properties[] = {
            CL_CONTEXT_PLATFORM, (cl_context_properties) platform.id(),
        #if defined(__linux__)
            CL_GL_CONTEXT_KHR, (cl_context_properties) glXGetCurrentContext(),
            CL_GLX_DISPLAY_KHR, (cl_context_properties) glXGetCurrentDisplay(),
        #elif defined(_WIN32)
            CL_GL_CONTEXT_KHR, (cl_context_properties) wglGetCurrentContext(),
            CL_WGL_HDC_KHR, (cl_context_properties) wglGetCurrentDC(),
        #endif
            0
        };

        // lookup current OpenCL device for current OpenGL context
        cl_device_id gpu_id;
        cl_int ret = GetGLContextInfoKHR(
            properties,
            CL_CURRENT_DEVICE_FOR_GL_CONTEXT_KHR,
            sizeof(cl_device_id),
            &gpu_id,
            0
        );
        if(ret != CL_SUCCESS){
            continue;
        }

        // create device object for the GPU and ensure it supports CL-GL sharing
        device gpu(gpu_id, false);
        if(!gpu.supports_extension(cl_gl_sharing_extension)){
            continue;
        }

        // return CL-GL sharing context
        return context(gpu, properties);
    }
#endif

    // no CL-GL sharing capable devices found
    BOOST_THROW_EXCEPTION(
        unsupported_extension_error(cl_gl_sharing_extension)
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENGL_CONTEXT_HPP

/* context.hpp
2LNLL7ADr0j+nz372FjzDg8bqDUG3dhL3ryW6KPzDAJ3pw2HxVHvnz9aJ3BmrLEaivu59SZzL6gg8K9U7XVYqHDSTpVpet+2hapdyFF9T5ld7tFtQI39vw6Ytn0M4/q29cCpvOPs728w6dXAU3ncg0HH/lbzemZzG53uKIp+4vSWCoPfFj5C4j37AKKvEtfu64x+D3HtKCakiWvsdQsPFBhzrzPOOO9BI3CG/9FthrvHd8KPthH2Hs7hL40D1/6ekHa+mp2Yk8VxHJHh7HB5ZTA07cQ+rWKfGZdFQIs+s5Z7ZH8mwMB+SauXpdd2mS8gbZgzA7Pe1/fWqDx0/aQbRWVlB9rIDa7WW1hpHEVF1LVYL3kUTZYDhpcR+q9vs/w0/2BlNAi0ZJDvMruDMR1j+kz11zQwms/UL5p0/ks/ATmcQacr5zOmq4GbXuL2e2x+Ic+yjmM/BmBqDNsNwPFx5SeBQr9t0mlVPUNp5xubQGcldX4GNS7drOE0fgaqn12N43aGJj8f2KLTJT+4924FXbAyu9CbWQZ93wNBZyxIMu5sNw16T8nVMPcgRqOkQYwppc3d2+g71x9ov1tNHyc6k9frdKyzW4x+D2fK6QcT7h7y0h57CHDmHQ82Sz/+u7IGjqcsVo3tOGIN0I5lxo26peHzxCtZ+COebZM22XNL5np8220Ff7RwyMQj7MYWBcaieVSF0gL20loFezjPmA9vUPHSsNkoVXv33CrI4itI3FgYmlZO+CbvZ97QUXh3M1rucRhYAyNIlC3xd9W+Huu6ITPxKC2us6JHNWyzkMPhr2pf4zxnViSFJYxqdRv4w7bC/6HIZZEh4oDZ1Op27Zv+oY53EkV2Zvu+sOt/fuSZPO9U8akVZ0GYJnYqmUAJ+BN9UMNHruuWKRmIImyc2GERw1St302sPHWCbuTcd67PF8jfRKsvs0rH89IoHOET3e+PdolmLty0RkU+Musu9mlaqLSuhe3wFXzHtk20qsx5TsPUZwW5z/MPyedu7980GgpjP6H9+sgY6I0Y4F/X6IgBLuzbNBrf5x8maFdA45ojfN+9Ft81u4AvVd+xv2Jyq/KIdSqG9LPVLQ179Pn1Gh1ViFCd4IFMWgSOdwff+/iu391u1N8HSrso972NRMf+WY/P9U3qd75lgva9LZKG8UN9330A0bDf1mXethXfzfpILgga6kOutG2SttyryMOzA9XXcVzSL4l5B412Lad7CGFW16fhnLnDsbyu2bPKnnrjr+q+FEdpnMRdujq9GjuwkofGwJaOkzhZtb9T2FjYGMu6d6h75DO7iWuXXuRZ/ZWz2JosxDJc6BhxJOMyyW1rRuY+HGi+fbShavctPyRjwdh1wMw00ujUa/L2n1kZINiSRK5A6y8aDet5j8xJCDpqZxXwu9zHqPyNJr1xlzu8hv7GdIx5l/teE6Pd5ayxBl3zf/+SRufrHLQTa1Uabxq0GxqNNwmatU6l8eZA+zSnYc0QXfHlXw+aym8di38D0bE+9LJnNoKmlsV8PrCJ0Zdpkor5jLz39B3vC/sUxT9znn9K1QTUc58enaovSuz6vk3vBrpLLDXO+yt/1s62MnbtPPZ9Npnp6TeNCQ37VxWfWVFOz5LEC6v5WT7fIZ8B2QTOw2t/1s+vLGE+lHF2v+ehnLM37lRzEi0aOTQ7fzbomLFVrOpHsfj6Lyhp4ypDf5LK0bd99I1Gl30uqYQIY420HbzcBGEkoNOpyh1pL4d0IQ8jzBaUA4CXfVZrWT5/0ebXjnfUnvD6frW9ro/FsKWZwr8fVdqpIn7U8+6f9HdoTKnJkOVcWWPQcW/HW6pJn6jPw2NrDTpEgTMXtNgg6wycETs=
*/