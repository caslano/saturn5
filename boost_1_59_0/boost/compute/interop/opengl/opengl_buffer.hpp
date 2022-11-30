//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_BUFFER_HPP
#define BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_BUFFER_HPP

#include <boost/compute/buffer.hpp>
#include <boost/compute/interop/opengl/gl.hpp>
#include <boost/compute/interop/opengl/cl_gl.hpp>

namespace boost {
namespace compute {

/// \class opengl_buffer
///
/// A OpenCL buffer for accessing an OpenGL memory object.
class opengl_buffer : public buffer
{
public:
    /// Creates a null OpenGL buffer object.
    opengl_buffer()
        : buffer()
    {
    }

    /// Creates a new OpenGL buffer object for \p mem.
    explicit opengl_buffer(cl_mem mem, bool retain = true)
        : buffer(mem, retain)
    {
    }

    /// Creates a new OpenGL buffer object in \p context for \p bufobj
    /// with \p flags.
    ///
    /// \see_opencl_ref{clCreateFromGLBuffer}
    opengl_buffer(const context &context,
                  GLuint bufobj,
                  cl_mem_flags flags = read_write)
    {
        cl_int error = 0;
        m_mem = clCreateFromGLBuffer(context, flags, bufobj, &error);
        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new OpenGL buffer object as a copy of \p other.
    opengl_buffer(const opengl_buffer &other)
        : buffer(other)
    {
    }

    /// Copies the OpenGL buffer object from \p other.
    opengl_buffer& operator=(const opengl_buffer &other)
    {
        if(this != &other){
            buffer::operator=(other);
        }

        return *this;
    }

    /// Destroys the OpenGL buffer object.
    ~opengl_buffer()
    {
    }

    /// Returns the OpenGL memory object ID.
    ///
    /// \see_opencl_ref{clGetGLObjectInfo}
    GLuint get_opengl_object() const
    {
        GLuint object = 0;
        clGetGLObjectInfo(m_mem, 0, &object);
        return object;
    }

    /// Returns the OpenGL memory object type.
    ///
    /// \see_opencl_ref{clGetGLObjectInfo}
    cl_gl_object_type get_opengl_type() const
    {
        cl_gl_object_type type;
        clGetGLObjectInfo(m_mem, &type, 0);
        return type;
    }
};

namespace detail {

// set_kernel_arg specialization for opengl_buffer
template<>
struct set_kernel_arg<opengl_buffer> : set_kernel_arg<memory_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_BUFFER_HPP

/* opengl_buffer.hpp
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
*/