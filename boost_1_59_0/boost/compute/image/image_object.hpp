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
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
*/