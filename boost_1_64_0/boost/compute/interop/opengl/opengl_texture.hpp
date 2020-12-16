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
8RzQuCTMub78ck3GLCEJt0G5xLmK425EuAPsoTRaasenVjnfSotPbH35wB1C/movjiqXw2rcTAun6KI4rC77md6yz5yVmKU2hjKFDgXdzF/p566bFTucc+ewx331NtBavUvzqdjexsnFDfq/HW0MP5DxbCn6v37cHD3Wgj3WM0d7cWsrK4Pa/l6JHXrwBhvjofJT8nypmwfhC6AXumE/rs7K6rqqR9q6sxePEKWqHumNvfi1RRHoDXn2dnVj71vXH2T+oQeHXqLq2Hf3YDFDNGU7eKN+LEaeUhef3QCPEai04+yNu/GtmUjJ/+iebh70ZXXv3odFt+Ldtanvm/TgBysrSyuN3B9viMORCnl+6t5uPCJQKXXy8Jv2YpfZQXAV1djI/0cPj1x1zDN0NxazE8o5frNurDYzKvX9/X48ZsgR9dx78x48X+ExHNA++2/RjRczJsr4vl4cZlbMd9X+NraOKN9glm/VxgibXZRlz63bGHlIhbJF6WvZbdt4Hk5F1BLKfLseHF9SG9yvOnHt+e3K7ftworrp6DpN71RA53WgD48GQt99/h36sLzi5wezYuJS72Lu2MkjxybyvXCnTpw5lpHv8YNdeHjT6G1x504slCOEw/1eG9eeH6514vrnh8/etQ+P+QF5+PahTiyUM9Dv3q0TB8WJKvPFd+/CQnEC3Gvv0YWD0gS41Xt248xxmt2rH2eO04P3BpaObmh1nsNbyTVew3Aa0po9ChpMPMS5brBau/zgHut9Yw32PJNCGvTHKTYz0QnQJRW8p8ZbNPYYPuir95d0lJJ33FtJ//EHMvrZtfkFDBaca8cTRsOijvuGkQzfh4OFc/zqhYYl6G/kdL6oavpBvB1Sgi5yo8RRPwlanR/1tk7J26GHAsczBx/vR2nfZZlA/+BjdDp/EFChXz6j0WWXBH3fDOh8RpRrGGIzzBr0ZWr3YcNfPVahDxYoFvfZ6eGgqZszc6ALNZxi7zPf0OZnlTItqN/l7NDIvOci6HV2Fd5PLjc0yini7ONu6QmgE22aGnuNnL3PNnq7IejCaZ8aanWFKn11qPnOrUscNmagXXgKaJgukL+ngqZu0EA/cwF01g9l/iHbezro0LXi3ZVncRq18vTjqd44SG3r1edKOv3MLksAdHhXnyfp6KPS3Q+Yr7ygxoCfyRJ9Bu36Ioape9OR2SbvX3mJ/A6xoD31VaCtDGgOU2kHXw0a7O0h8zWMxtR3OLSA9trXMppUHfDeCdq116m0IZ2qB6BdfoNGe7yal1NvkTQuj1ORl7dLGrIC2uF36jTGiHc438Vo86jRWWYzKmW+h9FkGNK27+ml9zO6sqHEW2CiLT5g0Ic8y0h7/cOMzrS57C2hhbNs74K3Jz9CNKZj9OLJU1NVGRe1mhv+gG16y8/v4kcZZmPfw+pjwPT6Hh76OGG69csYu1/pxiBPmM8/UeNgW2Dkx/qkQYeaVvH5/ZSBMfJ7TaN32ye8+NMdGEPO3GcUjLQgW17V+tYDP6th1pYV2rdVmlGGhc8pNGj1FV7Q229iLXxepVH9KPW79QsqDXUH3h9rdK7WBu3Nl1RaPRGA9kWFZtTT+pc4zdSUaf3jNl/uxKB/7JXzKMfxlRJles5X2DdsrLDOY3x/zaCvLIC27+sNTS7gsMn+BqNtrOe++ltVN5tZgZ27ZRlf99spON+x/Um9h4KDrmGOCuzLN/dhYY4K7F+3trHiDD2/yp49VvfM27qwMAsF7tD2ThzMQnEG6MINu9N++Y5urJn2c0Y7cUj7drD74ji8u0zLp+bf9/BdDV0OYYKAfmF3Qxe6Cv1d8huZdNheAjOyp40x7YWv3aQbgypCmoS9aRtrvhE=
*/