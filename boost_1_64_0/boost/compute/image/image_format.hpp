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
bGW+fwWbEfs2p6cjvndUm8i4S8x73qptg1Yr1TTLkxj5yM0X5LChcvBuqezHU1Ye5DSg0LQ0pc1h5GFuittZufv5/qpdL5qEozSNq4W8hF3n1gvts7pq2yWVIMyqadPg6bHYsC5jCGsqp33ILRBRPJw159Ay2TGPvHuo9AdO+jhpNBrVet1MH5akV/PIR8z0d8vyRjvJajUeQ7t9VtqiaixfMLH3IiM0D1u01GVG0jrbNpuXCVTeX7DyJm8L265u8bz3zjpr/qNV2zcT1yvVnJqhNyA1H2w/2swfMur0QbtdCyuVKk3ctE/PTAq+YUC2HX/CWITnVpvoA/D5DzOfhZR2z2oVyo7xqfbfc9UGXs/A3iOsRjnturTIFAtNDvXa5/I9ew2VE5O1WgQWmabgLI7pPo8uLUOLbMKWef7LPYPPMG81adtL9JXq2AH8BGa592pUqmGLNsl8ZaARr7afze/ZY6xCN0M1aq3cbssNYnRj5Dany2fydpvPNCGnQ+j3CJ6o9lTY1Z4pI41WHjdbeUPI30MEOFc26JaJzf12td1o0a6HH8nlLD0QL3Zv0Q1eVdVv36pf6tMiilwhUYtbgvwxT7buFJvQcL1QXhi1hty9zcyrSkO1WqsEeRaU57VLC7XdYX9DqErf2LM67jnr8yQMaXlE1immKL2bcQ97LeutOevCvF7LGmnLD870Btu9te2+dFTdDR0E/q+3Zq+Dw7Qa5nSySrT6Hs0UUufNKwUmCCqnVMnYmjPnsEbNgpQ5y4QONDc3iBvRolbOJl+ra7Zups0GcuxFFb8+mrK12FkjQ75QcrTqkupri6/cD+t50KxUSCfanh5Uk2eG7oYAsL1rxdsH1uw1DN0hyLZAaTFJRlZ/l2/YsXnjbsxrxuv++NHuY3u79Dos8afXcMdmPveq5rUGOWBjt+XRZ49Wev7imr0PRIHJtJNDDj1KcTql+UXcB0RckL7UXb5bUXpo3ZY1CrPJqAYhpXfSnmY3dZlis5Gq9YGZRzXxyaWStcKsTnmIP8q2JY6oeVlboIk1UcvP6rotP41Wiy4SaufID/2FDJGdYHWZZEiPifNOHckhUW0kQSjGE7P2+ODc5H1/D1v/Ha7b+xRxFFZpXCSclxr2t1IlNlXBCP0HGuqckpUjJ68oalbJryLaicSsnY7cPOlrpjIKUtXn67bOohFep3kxRz7V3nDxXlO27N6d9M3oAys/fUZiw5pj2ZCIq7WYZ9cRj+6LJhb9jj2o29rpyINeyclO8akAShlPJnv9XSQ01p0fuIcxD9w1itp0dIViHhRfE6wVzfwXKmFcS7N66LcfKnGYo0xcJfPrWVChkU2bomrTr+hYdAZUoPLa2rDnZdqLoYJphoTu4qsDsgNHu+VZeQHkbsM5e5LR1FSLQ9PX6KiqRcQ7mGlD0itkfdUb1CmYS5gdOS80HxNcS4fyeYb1FcbUzzecuJGULMIkEgYHr5cYDNOzfI1DamrAdpuEvYeq6fzm+vbeWbPaSqrVNPaRzcSZ7wpM8vzgl+1b7U7O3Go9DEhJK1nOhSzPbjrPv4lavx5ScI+xZlKrpZvQmZXb3p/6pcPKEozubJBxtTmc8NhQok/ZOH0XpRd0itGgOCf5/ev8OzPKirRvc9pGKe37Ij/iHETOy7cWaK78EcqijKW/3vM4/cwtaQxo+oam67x9Tqcd326vP2GRKzLt7aie4xVWT8pW0VgXSPrtiX4Men+45dDnb0x0zjc38Givg6+ZpxNJv9Q88f5ui06bJhN+7vDmkrfwR6BvD9a6fB+O+mJDlCEwpw6BEXTmLhF0fqbntowu19Cq9TyDPl+gs0qI2LRbXUfE6j3obl12Eqk=
*/