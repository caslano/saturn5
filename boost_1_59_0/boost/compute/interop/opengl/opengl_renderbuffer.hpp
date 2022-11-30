//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_RENDERBUFFER_HPP
#define BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_RENDERBUFFER_HPP

#include <boost/compute/image/image_object.hpp>
#include <boost/compute/interop/opengl/gl.hpp>
#include <boost/compute/interop/opengl/cl_gl.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {

/// \class opengl_renderbuffer
///
/// A OpenCL buffer for accessing an OpenGL renderbuffer object.
class opengl_renderbuffer : public image_object
{
public:
    /// Creates a null OpenGL renderbuffer object.
    opengl_renderbuffer()
        : image_object()
    {
    }

    /// Creates a new OpenGL renderbuffer object for \p mem.
    explicit opengl_renderbuffer(cl_mem mem, bool retain = true)
        : image_object(mem, retain)
    {
    }

    /// Creates a new OpenGL renderbuffer object in \p context for
    /// \p renderbuffer with \p flags.
    ///
    /// \see_opencl_ref{clCreateFromGLRenderbuffer}
    opengl_renderbuffer(const context &context,
                        GLuint renderbuffer,
                        cl_mem_flags flags = read_write)
    {
        cl_int error = 0;

        m_mem = clCreateFromGLRenderbuffer(
            context, flags, renderbuffer, &error
        );

        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new OpenGL renderbuffer object as a copy of \p other.
    opengl_renderbuffer(const opengl_renderbuffer &other)
        : image_object(other)
    {
    }

    /// Copies the OpenGL renderbuffer object from \p other.
    opengl_renderbuffer& operator=(const opengl_renderbuffer &other)
    {
        if(this != &other){
            image_object::operator=(other);
        }

        return *this;
    }

    /// Destroys the OpenGL buffer object.
    ~opengl_renderbuffer()
    {
    }

    /// Returns the size (width, height) of the renderbuffer.
    extents<2> size() const
    {
        extents<2> size;
        size[0] = get_image_info<size_t>(CL_IMAGE_WIDTH);
        size[1] = get_image_info<size_t>(CL_IMAGE_HEIGHT);
        return size;
    }

    /// Returns the origin of the renderbuffer (\c 0, \c 0).
    extents<2> origin() const
    {
        return extents<2>();
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

// set_kernel_arg() specialization for opengl_renderbuffer
template<>
struct set_kernel_arg<opengl_renderbuffer> : public set_kernel_arg<image_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(boost::compute::opengl_renderbuffer, image2d_t)

#endif // BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_RENDERBUFFER_HPP

/* opengl_renderbuffer.hpp
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
*/