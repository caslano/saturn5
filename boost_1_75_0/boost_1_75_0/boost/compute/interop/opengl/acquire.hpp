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
+9FeifljO3yOJyjf+69zuvMhuQWCJrfJsalDCwDiivgq5dIR9XFgwL/Rfou5nTKydQclhIOhIf0byE/L8geTtMucnNDznIqxexWf+q5zXdw1c28ruI+RJv6HJwS53JiuQdba5uyOwMbPQYb6lXiZ23IclWLcjnqK3dUNZ9b/7D42XXppTsZh+J+XEouSbrb76iG3KyTNA7+I3qyaZgcEXtL2hAonhehu6a0jLlEZ8/is09fOfcjO0VDEyvNld9mRLUxzEA9SyqYpWXI1Tg8L7fPnKW0rZlmwmre+Sx1P2YdHdEZ0vyVHbWwrVnpZRnWQYpwbGZ6ANutYJ8CbiJR6iK/82X+cziRfX37RisEe3PlXM+ehl0fW4SCtJPs+5vVDRYfpzmaJ6og3Qdx72taV7f/qX7qGX6zG12HGBNaE6efuh0VNuf7sejEkPmVY8jqw95lhQfZjn8rGJY6F6VlgulCA2FqwujQ9lhlZKhIeY0RzKvN0+/XqSO/Mf8F3VM6MG8Kd1rtNFeqeyFBNJ4CLdRn3fhGKpsla5RynEO8EE7GzJf0/HgC6NIfnoorSCg5sX92N82XwjAn8gsM1pgsPdd+diuW62J8lJvexuQ1hHuF2HJJ6mAjV2T4wY70Hl/KyEq4KBhkHB819Tx3Duvg6uRXemBtRTOqCC8s/AJElypplpvXAJkZG4OMpXOnENm6deUKibx8lFKwfchKV
*/