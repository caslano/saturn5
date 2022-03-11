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