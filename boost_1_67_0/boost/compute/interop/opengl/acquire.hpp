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