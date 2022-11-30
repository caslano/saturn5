//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_TEXTURE_HPP
#define BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_TEXTURE_HPP

#include <boost/compute/image/image_object.hpp>
#include <boost/compute/interop/opengl/gl.hpp>
#include <boost/compute/interop/opengl/cl_gl.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/utility/extents.hpp>

namespace boost {
namespace compute {

/// \class opengl_texture
///
/// A OpenCL image2d for accessing an OpenGL texture object.
class opengl_texture : public image_object
{
public:
    /// Creates a null OpenGL texture object.
    opengl_texture()
        : image_object()
    {
    }

    /// Creates a new OpenGL texture object for \p mem.
    explicit opengl_texture(cl_mem mem, bool retain = true)
        : image_object(mem, retain)
    {
    }

    /// Creates a new OpenGL texture object in \p context for \p texture
    /// with \p flags.
    ///
    /// \see_opencl_ref{clCreateFromGLTexture}
    opengl_texture(const context &context,
                   GLenum texture_target,
                   GLint miplevel,
                   GLuint texture,
                   cl_mem_flags flags = read_write)
    {
        cl_int error = 0;

        #ifdef BOOST_COMPUTE_CL_VERSION_1_2
        m_mem = clCreateFromGLTexture(context,
                                      flags,
                                      texture_target,
                                      miplevel,
                                      texture,
                                      &error);
        #else
        m_mem = clCreateFromGLTexture2D(context,
                                        flags,
                                        texture_target,
                                        miplevel,
                                        texture,
                                        &error);
        #endif

        if(!m_mem){
            BOOST_THROW_EXCEPTION(opencl_error(error));
        }
    }

    /// Creates a new OpenGL texture object as a copy of \p other.
    opengl_texture(const opengl_texture &other)
        : image_object(other)
    {
    }

    /// Copies the OpenGL texture object from \p other.
    opengl_texture& operator=(const opengl_texture &other)
    {
        if(this != &other){
            image_object::operator=(other);
        }

        return *this;
    }

    /// Destroys the texture object.
    ~opengl_texture()
    {
    }

    /// Returns the size (width, height) of the texture.
    extents<2> size() const
    {
        extents<2> size;
        size[0] = get_image_info<size_t>(CL_IMAGE_WIDTH);
        size[1] = get_image_info<size_t>(CL_IMAGE_HEIGHT);
        return size;
    }

    /// Returns the origin of the texture (\c 0, \c 0).
    extents<2> origin() const
    {
        return extents<2>();
    }

    /// Returns information about the texture.
    ///
    /// \see_opencl_ref{clGetGLTextureInfo}
    template<class T>
    T get_texture_info(cl_gl_texture_info info) const
    {
        return detail::get_object_info<T>(clGetGLTextureInfo, m_mem, info);
    }
};

namespace detail {

// set_kernel_arg() specialization for opengl_texture
template<>
struct set_kernel_arg<opengl_texture> : public set_kernel_arg<image_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

BOOST_COMPUTE_TYPE_NAME(boost::compute::opengl_texture, image2d_t)

#endif // BOOST_COMPUTE_INTEROP_OPENGL_OPENGL_TEXTURE_HPP

/* opengl_texture.hpp
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
*/