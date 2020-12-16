//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_IMAGE_IMAGE_OBJECT_HPP
#define BOOST_COMPUTE_IMAGE_IMAGE_OBJECT_HPP

#include <algorithm>
#include <vector>

#include <boost/compute/config.hpp>
#include <boost/compute/memory_object.hpp>
#include <boost/compute/detail/get_object_info.hpp>
#include <boost/compute/image/image_format.hpp>

namespace boost {
namespace compute {

/// \class image_object
/// \brief Base-class for image objects.
///
/// The image_object class is the base-class for image objects on compute
/// devices.
///
/// \see image1d, image2d, image3d
class image_object : public memory_object
{
public:
    image_object()
        : memory_object()
    {
    }

    explicit image_object(cl_mem mem, bool retain = true)
        : memory_object(mem, retain)
    {
    }

    image_object(const image_object &other)
        : memory_object(other)
    {
    }

    image_object& operator=(const image_object &other)
    {
        if(this != &other){
            memory_object::operator=(other);
        }

        return *this;
    }

    #ifndef BOOST_COMPUTE_NO_RVALUE_REFERENCES
    image_object(image_object&& other) BOOST_NOEXCEPT
        : memory_object(std::move(other))
    {
    }

    /// \internal_
    image_object& operator=(image_object&& other) BOOST_NOEXCEPT
    {
        memory_object::operator=(std::move(other));

        return *this;
    }
    #endif // BOOST_COMPUTE_NO_RVALUE_REFERENCES

    /// Destroys the image object.
    ~image_object()
    {
    }

    /// Returns information about the image object.
    ///
    /// \see_opencl_ref{clGetImageInfo}
    template<class T>
    T get_image_info(cl_mem_info info) const
    {
        return detail::get_object_info<T>(clGetImageInfo, m_mem, info);
    }

    /// Returns the format for the image.
    image_format format() const
    {
        return image_format(get_image_info<cl_image_format>(CL_IMAGE_FORMAT));
    }

    /// \internal_ (deprecated)
    image_format get_format() const
    {
        return format();
    }

    /// Returns the width of the image.
    size_t width() const
    {
        return get_image_info<size_t>(CL_IMAGE_WIDTH);
    }

    /// Returns the height of the image.
    ///
    /// For 1D images, this function will return \c 1.
    size_t height() const
    {
        return get_image_info<size_t>(CL_IMAGE_HEIGHT);
    }

    /// Returns the depth of the image.
    ///
    /// For 1D and 2D images, this function will return \c 1.
    size_t depth() const
    {
        return get_image_info<size_t>(CL_IMAGE_DEPTH);
    }

    /// Returns the supported image formats for the \p type in \p context.
    ///
    /// \see_opencl_ref{clGetSupportedImageFormats}
    static std::vector<image_format>
    get_supported_formats(const context &context,
                          cl_mem_object_type type,
                          cl_mem_flags flags = read_write)
    {
        cl_uint count = 0;
        clGetSupportedImageFormats(context, flags, type, 0, 0, &count);

        std::vector<cl_image_format> cl_formats(count);
        clGetSupportedImageFormats(context, flags, type, count, &cl_formats[0], 0);

        std::vector<image_format> formats;
        formats.reserve(count);

        for(cl_uint i = 0; i < count; i++){
            formats.push_back(image_format(cl_formats[i]));
        }

        return formats;
    }

    /// Returns \c true if \p format is a supported image format for
    /// \p type in \p context with \p flags.
    static bool is_supported_format(const image_format &format,
                                    const context &context,
                                    cl_mem_object_type type,
                                    cl_mem_flags flags = read_write)
    {
        const std::vector<image_format> formats =
            get_supported_formats(context, type, flags);

        return std::find(formats.begin(), formats.end(), format) != formats.end();
    }
};

namespace detail {

// set_kernel_arg() specialization for image_object
template<>
struct set_kernel_arg<image_object> : public set_kernel_arg<memory_object> { };

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_IMAGE_IMAGE_OBJECT_HPP

/* image_object.hpp
247oJvhQ0O5G9ecxviyiMw7ZgdqK5zk0RE4K6s2JdlfQeDRpvNxod8mll7Kr4SN5xveyNxJngFWs5nVUntGSuMdc5kdY3gb6pQNRxqaIBXcuX7bPruwIDKuevCuRzmaFUSHW+SfXk/yySxf5EXVRx3uiHuRC1j5vztO9iZbjskaRz9OoPFlOm07bI870WZwPXHTTWaksL0WRHQv+Ao4RfRCLM11m7CKvz4sFRnYXRZvK3kJOsm9eLnDy8j27TV47Iw8rnlaeUzZANWKYfz+6jeeJfVy6XD/s0s2upO1YnC7lKwvk7fNm+t14BYTX8V1WO4heduMzP2y0A90is+KeQWhQu6vQDBWD+0mRxm56pBP1+TRhzNvLVXmfF2kNVpGQ531U2nd2jP7XCnnYsc+nmazYgiQOq6j4UKu/7DM9PzDaQ4gF8sZ5OhplNL6EjPzUGReSIWSq2uxXxb7ouDLQhPzTARY+HsX32m2N8cLZEX2TEJ6hxHUFgp8/iXKKD8c4ZzL+VpD/4jj917UtmYwXOqL9Lnkds/3s8w9XIRpuJ1dn3q7jyJgTw39tQdeXrIMu+Hj21S0+KKqorF2G/cfLcTt/nfI+ceOu76z0H92mR6KMK21V/U9TPs6N9Px7j9rFvmFW4O9zHYvPzkIsylm8jitTtszXBN3O0jlHtAz9h6h33I/Q4I3AxFyU1zLzs6K+BT132xvsiPZbIXqpDDk8rV7HkQ8qn42R33BdJPTQNdSdDox3HuUjeNi6jjuGkbl5drbacO7boA9cBtcpfZFBgb3EzVlMchra911Q6UuC7ytQWucVD/59165PuBALfNuSs429sZSPCeHtVwTE2Nq/TpkOs89R5kqvktCpOf65yE8LrZLFJ1KbmspD6ZUXoCyQCrH67xAYd14u3Gl0SDjjVlFHvuh6LNH2jsx1k6hOd8qq872u7DnnuL6i5zPimRkz/PaPbi7vUXmP1Dk0JpfyrIPzgR8srUOxrh8Bzp5vIeLq/hcuE+wAj6jnMy2ZEG0+pG+OwcO/P0joDREpR0UoffKJwji3ZTqU6cJEnOX7NOEL86hzFuizxf7t6Lq4fcSFSdx5RGWFnQ4uKWb99kRLvmF6irtOruGMZWmT/gz9JQL8KDfWV5y3L16nOIdo7kt14tJCLOr11bK6o7lEX36jXI+jDNXu33PnF+dOtaeSTGmBFN+WqH3IV4H2YTz9COWZXW7fcfaBa6nztctRm6qUy7Q/Kekn90zxz8v0vNPfvxIYcwgU5q1fok94WC4GkGrzc65elucQL5bWz56L/lzGo3Me6R/u/OHMC2fs8h+0EIv+/PesecVpg0tft9gGrj11ecI47V04K3alQj5F+fwc8eQoav494POtOcqF3DyG8HhlQ5bzO90f7EIFMxKTekW02dWu6+hFx86uUXkU6UtldR4cp/q+hddckkKRL8lnCn5ORsiAoJ29FKOx2770WlXUXdDvdRlJF45eBlKPL1J/CMxPgNkbFlHURhJHxwoItzYYCocx+PvC5dh3vsgldw1nAfy96/ImbZtCTTgd/J2/Auj2hqdR7vkracx0dxvlvuLq6jv2h0B7xDVMGjcMUWbjmqC5G0JoE5oHZ2HYPgnKmb8ecBsi8kL3jXd90AxHlO7X99zYpHP+kfbnN9G0vR1x2Mvs1+RmFp0z12UBiIZs/OPmDIMYAJUH7vi4160tuogfULzfzqQNJltGus+ChrgDlPme24NGXcmLtPI9voNBFyTQHnIXizYWMQuSdg+TZlUXZW/fy8SgvyBHF+8LOtvNwV0oz3wAvus4C3MMBQ4dXiKN+X4EjO0IM/i7GGsMDTPuQqU6QubOJjadQh+669s=
*/