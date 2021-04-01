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
hQooWjmHS7OXlrz1Kgl+hgXthYNRrLlvi5D5Bcl0Jdo5iZ4qLlfVVaXxpqun2tjPDm2GBMtsd0Rlc3HJkE5NRim6YNa+4nerxka+WQFMPAkUFACWgaCacJX0q90bXMw6W36Gv2Lq4pCqZswiM5WlgWVavEPbOCagOAA97ee/kI5eqeWohK0sXejuUNLQW7Ds97sPIdEe9Q80pd/+5ugyk2LIIhjKYxo7jioSxipbUzuqaUWUIo25uSpdp26ahuERWHIH02OlWkRP6nzVuT025EKvS44TDqA9J72fbeIngedE9xLls86jvTvRyFPE+vEbfRz3KxRqqNfjjo+eXFX8xU9CQGwzIj5c7/iyVCXrD3PrWMkc35h23j51m8gjY7BEGm5+nnav/fkMScszkWjImCpksAzocDlTJvzX3ad7LyUvuLJIieA9UOyZO1O71zihxOsi/SZQvgPhqeysYS11VH+xC9C/vlqZN7+Ltsieg/haqIe3tPybDCY9BzBjrsX5NSN9id/q7HFM+TkWpUtkQYjmOD/PgND4TuTIEasWfeQK/idAQuiN5MS1IQ==
*/