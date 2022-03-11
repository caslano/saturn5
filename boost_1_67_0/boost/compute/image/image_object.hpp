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