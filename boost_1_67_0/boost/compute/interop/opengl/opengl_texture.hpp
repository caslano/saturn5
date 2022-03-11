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