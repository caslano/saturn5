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
+fjfyNld+SuE5unqp5RroCqzqNEDeusaq8C3caSRIk5h77Tksyj3pm9WpNJVZoWeA9RpijXVYZV3Xj2UlAITxD2jHU/LG8zc8j4sHGPdlKPOCOWKVu0g31n4Y8TjyTtXotc/noSQLHZB7i6hpuG+vm2Rfx0DaEGz0NrSjg4fMrnWWZFBkA1dFPT2P40mxScHhA7GWt8vAEZq1BsJaYS75IgC8jJ/H67xzBe+T8GuRn5/3+v9kFsvnqsTjKgBiKbi60lFYBjDSwOxXLkcoB5/kZi7rcLU+YqY616T72EoDSjeeMNtFUEtyE0QZb/e/vt31JV/lCdTJKEmqG/no6A+6QW2+kkpoIcYI1UDzLNGqbGxSFkWurXhlggz8Q207T0Pgm+l3HLg0gxbAnh1TLEFqjc6bhq3o7teYqvt1/9aotd9gJdryFZsHHSL/jWqLSqb1Q06DvDycjHvjhtJ49070+gGT2oQ2k/UTWMc0JYzHS/ecWd+893jV4rPzEhthrp58CibGXl+LifYucLuN58wHENCsoEP0DZTCtMSO8MIc+tf4pt6lWXjaOV4KNtzR/wSzWLN7XMg97xXbNjP26mVqY5Rk83jAdxcyymDhtaz3C7kmlPx5VNMJ0CMStRlXn5R9kjH2i3DvY4rzwyW49taddwvm1/lxn/bedc2ssoeLPXLpPI8/xb1AFR9XzDAt2GkStyF0i4qM4v7R4Bz
*/