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