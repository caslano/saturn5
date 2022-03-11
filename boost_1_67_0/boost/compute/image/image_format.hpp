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