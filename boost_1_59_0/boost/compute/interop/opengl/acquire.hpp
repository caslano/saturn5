//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENGL_ACQUIRE_HPP
#define BOOST_COMPUTE_INTEROP_OPENGL_ACQUIRE_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/interop/opengl/cl_gl.hpp>
#include <boost/compute/interop/opengl/opengl_buffer.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/utility/wait_list.hpp>

namespace boost {
namespace compute {

/// Enqueues a command to acquire the specified OpenGL memory objects.
///
/// \see_opencl_ref{clEnqueueAcquireGLObjects}
inline event opengl_enqueue_acquire_gl_objects(const uint_ num_objects,
                                              const cl_mem *mem_objects,
                                              command_queue &queue,
                                              const wait_list &events = wait_list())
{
    BOOST_ASSERT(queue != 0);

    event event_;

    cl_int ret = clEnqueueAcquireGLObjects(queue.get(),
                                           num_objects,
                                           mem_objects,
                                           events.size(),
                                           events.get_event_ptr(),
                                           &event_.get());
    if(ret != CL_SUCCESS){
        BOOST_THROW_EXCEPTION(opencl_error(ret));
    }

    return event_;
}

/// Enqueues a command to release the specified OpenGL memory objects.
///
/// \see_opencl_ref{clEnqueueReleaseGLObjects}
inline event opengl_enqueue_release_gl_objects(const uint_ num_objects,
                                              const cl_mem *mem_objects,
                                              command_queue &queue,
                                              const wait_list &events = wait_list())
{
    BOOST_ASSERT(queue != 0);

    event event_;

    cl_int ret = clEnqueueReleaseGLObjects(queue.get(),
                                           num_objects,
                                           mem_objects,
                                           events.size(),
                                           events.get_event_ptr(),
                                           &event_.get());
    if(ret != CL_SUCCESS){
        BOOST_THROW_EXCEPTION(opencl_error(ret));
    }

    return event_;
}

/// Enqueues a command to acquire the specified OpenGL buffer.
///
/// \see_opencl_ref{clEnqueueAcquireGLObjects}
inline event opengl_enqueue_acquire_buffer(const opengl_buffer &buffer,
                                          command_queue &queue,
                                          const wait_list &events = wait_list())
{
    BOOST_ASSERT(buffer.get_context() == queue.get_context());

    return opengl_enqueue_acquire_gl_objects(1, &buffer.get(), queue, events);
}

/// Enqueues a command to release the specified OpenGL buffer.
///
/// \see_opencl_ref{clEnqueueReleaseGLObjects}
inline event opengl_enqueue_release_buffer(const opengl_buffer &buffer,
                                          command_queue &queue,
                                          const wait_list &events = wait_list())
{
    BOOST_ASSERT(buffer.get_context() == queue.get_context());

    return opengl_enqueue_release_gl_objects(1, &buffer.get(), queue, events);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENGL_ACQUIRE_HPP

/* acquire.hpp
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
*/