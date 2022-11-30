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
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
*/