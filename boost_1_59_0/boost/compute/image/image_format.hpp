//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_IMAGE_IMAGE_FORMAT_HPP
#define BOOST_COMPUTE_IMAGE_IMAGE_FORMAT_HPP

#include <boost/compute/cl.hpp>

namespace boost {
namespace compute {

/// \class image_format
/// \brief A OpenCL image format
///
/// For example, to create a format for a 8-bit RGBA image:
/// \code
/// boost::compute::image_format rgba8(CL_RGBA, CL_UNSIGNED_INT8);
/// \endcode
///
/// After being constructed, image_format objects are usually passed to the
/// constructor of the various image classes (e.g. \ref image2d, \ref image3d)
/// to create an image object on a compute device.
///
/// Image formats supported by a context can be queried with the static
/// get_supported_formats() in each image class. For example:
/// \code
/// std::vector<image_format> formats = image2d::get_supported_formats(ctx);
/// \endcode
///
/// \see image2d
class image_format
{
public:
    enum channel_order {
        r = CL_R,
        a = CL_A,
        intensity = CL_INTENSITY,
        luminance = CL_LUMINANCE,
        rg = CL_RG,
        ra = CL_RA,
        rgb = CL_RGB,
        rgba = CL_RGBA,
        argb = CL_ARGB,
        bgra = CL_BGRA
    };

    enum channel_data_type {
        snorm_int8 = CL_SNORM_INT8,
        snorm_int16 = CL_SNORM_INT16,
        unorm_int8 = CL_UNORM_INT8,
        unorm_int16 = CL_UNORM_INT16,
        unorm_short_565 = CL_UNORM_SHORT_565,
        unorm_short_555 = CL_UNORM_SHORT_555,
        unorm_int_101010 = CL_UNORM_INT_101010,
        signed_int8 = CL_SIGNED_INT8,
        signed_int16 = CL_SIGNED_INT16,
        signed_int32 = CL_SIGNED_INT32,
        unsigned_int8 = CL_UNSIGNED_INT8,
        unsigned_int16 = CL_UNSIGNED_INT16,
        unsigned_int32 = CL_UNSIGNED_INT32,
        float16 = CL_HALF_FLOAT,
        float32 = CL_FLOAT
    };

    /// Creates a new image format object with \p order and \p type.
    explicit image_format(cl_channel_order order, cl_channel_type type)
    {
        m_format.image_channel_order = order;
        m_format.image_channel_data_type = type;
    }

    /// Creates a new image format object from \p format.
    explicit image_format(const cl_image_format &format)
    {
        m_format.image_channel_order = format.image_channel_order;
        m_format.image_channel_data_type = format.image_channel_data_type;
    }

    /// Creates a new image format object as a copy of \p other.
    image_format(const image_format &other)
        : m_format(other.m_format)
    {
    }

    /// Copies the format from \p other to \c *this.
    image_format& operator=(const image_format &other)
    {
        if(this != &other){
            m_format = other.m_format;
        }

        return *this;
    }

    /// Destroys the image format object.
    ~image_format()
    {
    }

    /// Returns a pointer to the \c cl_image_format object.
    const cl_image_format* get_format_ptr() const
    {
        return &m_format;
    }

    /// Returns \c true if \c *this is the same as \p other.
    bool operator==(const image_format &other) const
    {
        return m_format.image_channel_order ==
                   other.m_format.image_channel_order &&
               m_format.image_channel_data_type ==
                   other.m_format.image_channel_data_type;
    }

    /// Returns \c true if \c *this is not the same as \p other.
    bool operator!=(const image_format &other) const
    {
        return !(*this == other);
    }

private:
    cl_image_format m_format;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_IMAGE_IMAGE_FORMAT_HPP

/* image_format.hpp
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
*/