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
fjGH7k53VN1lGpUp8zq5MG/kb/+nhktj2w/y3GcxevX7wMQDtTuPG7l+GtMzfHJmEZGocS9RsYeLOChI82itkNdw08cl1OqN8jTL8sJj4GXUzFYnzgIVn1l+7tJWlefESTRXLIMbvY01mnyC8EFuVwwt0jY1PzTO/PMPNM7TMI+j0o1ZiZlBNDcQDQ3EukI+JK0crcOECqa2x5iDjtk9vzQ/W/MIu0617BGWlphZs1szA5ocAtyTv9lVFXuo8LtZmZJGc3luvkJCz6ziCitKvYJd9jR2RB9O7pK/8xYWPnR6ev5Cn72hBv3FToa7kD72me+UfjdS9MliOKXeDTHnHqjLwTI6jzIvD+93H4Gfy4O0GDyuG8ROaaoPj+vz922fXa+OWWCXvtPNrNZ8Z+MP0nMVuHliUwuRZVPUs8WlC0srAzrYX0u+7OQxpKneO31Zx4RWR2pFiW2nOf2ik0srQ34XrjJcnTzS+C36L5C6YLWOhK5lflombtqlWUGvh8o/6xzdx3tzQqMbzbBuewU74NgHL+d/R+wpPtdkvRPb9HpdJ/fzMg5G13t21Xon5e8yrv7OpRXGUdenpTO6XvZ7zYoF4cZVI2xZWqjTUuskhXvMUlTHZXDfdc5Y6P9lrc7MipwoCNzEb69zZmmZV+xUfc6fn6b8v7vsj/cfcf+1eunulORpQVfB9no14f8sVZSKekgCqdaTWLR7RqmTee316JsLq0fuE6Vaz8HCDu2sjNhWKey8Je4Ux2FtxHHo0fvdmvQifQ1dWaf5NHWLbpmXhaVtorAn+kBH810sg6z06JIx8YyDhw4feebRY8b69J65XuU19pw89X2LRvoo7tu4l6zTx6ebRUniF1n7+Myep2XW/AVpz5Pz4dY6fX/Ku6nb9SNnRH3DS23zIczYH9ZZlYtQ5TOywogeZqUfrFqvl4+sF/536/XYHrTEirzbjdvrbXALmYO0Ieg8gNUnznIl5rek9wUdJ2xlw4973U3QtUNOwuocLltN3ACtMTuEpx7t6NRO9f21zxR2AFOnikl/mgf0hlxvDZUZ03i70FfkqT8aM+j8Fkl03OsMurAJQGwNk14pnCHr89ZJutn3mcUlMivqqbmZt7RiJUuIBTX+gBG4+YGoliSEqt3/+Cj8sNZrj8CYNvzrHmziBo1YIB9pYrRYIOMPadKpGeikXy/o6u+BOBTbQcNvgXKgKb+DfDNwGpslIm4nV1rQv5aWp/lNUrUbeVgbVmxjqv7i4SYOPyow13bqGNQzqNvzHmFgtB8SdVFHTRwlwyQdgJYT/ZEGpkonQdIMng0csTK/Ohq3LOL+TLOqdyGfN8NXnVxaHNKWOajtoveBpjVGXR2yQCYLqo/EfsLytxTWjD72TwK9MRc7aj1PbsMNMBeuPaWmizawJ3z+AKORIHx5hiK10pNnmp4zSt23nkp0/pZr5/Ha00BflcfLTweulcd0oqajDTmmz6hoy6PaELifHWrD1T4N/SNEr2wJ0BURlBMY65lNjGkfdKsVs3JBxbztaBNjxr146bEWzIDS+ap5uFswZmyMG8cJs8o7uf+sJt2M4+k9mzDQw1BphfYzlWbYXnzpBKNdbMw95K7dpMedCl3y0PdcnryaYmM00xereVPUssdLO3FSu7QthASS9qDIm6Lij/mOR889ulGfpjhjOeCEh+16hYdtse+nZZR4lt8MFgY755tqmUOuE5Q+vQgsL5/SZQW/0HDdrEhzp3Cs508a98RbHAfdgee4xIJrefPLaL3O46mNh1dm1EPPas1ngj5u2qz753bDLHPLWEuJYo7LTrVMYSV25LO7mDWJoGT0EvN0G+T9ahknsspukJSeHyu/1qE=
*/