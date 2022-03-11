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