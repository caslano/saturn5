//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny, Lubomir Bourdev
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_BASE_HPP
#define BOOST_GIL_IO_BASE_HPP

#include <boost/gil/extension/toolbox/toolbox.hpp>

#include <boost/gil/bit_aligned_pixel_reference.hpp>
#include <boost/gil/bit_aligned_pixel_iterator.hpp>
#include <boost/gil/color_convert.hpp>
#include <boost/gil/utilities.hpp>
#include <boost/gil/io/error.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <istream>
#include <ostream>
#include <type_traits>
#include <vector>

namespace boost { namespace gil {

struct format_tag {};

template< typename Property >
struct property_base
{
    using type = Property;
};

template<typename FormatTag>
struct is_format_tag : std::is_base_of<format_tag, FormatTag> {};

struct image_read_settings_base
{
protected:

    image_read_settings_base()
    : _top_left( 0, 0 )
    , _dim     ( 0, 0 )
    {}

    image_read_settings_base( const point_t& top_left
                            , const point_t& dim
                            )
    : _top_left( top_left )
    , _dim     ( dim      )
    {}


public:

    void set( const point_t& top_left
            , const point_t& dim
            )
    {
        _top_left = top_left;
        _dim      = dim;
    }

public:

    point_t _top_left;
    point_t _dim;
};

/**
 * Boolean meta function, std::true_type if the pixel type \a PixelType is supported
 * by the image format identified with \a FormatTag.
 * \todo the name is_supported is to generic, pick something more IO realted.
 */
// Depending on image type the parameter Pixel can be a reference type
// for bit_aligned images or a pixel for byte images.
template< typename Pixel, typename FormatTag > struct is_read_supported {};
template< typename Pixel, typename FormatTag > struct is_write_supported {};


namespace detail {

template< typename Property >
struct property_base
{
    using type = Property;
};

} // namespace detail

struct read_support_true  { static constexpr bool is_supported = true; };
struct read_support_false { static constexpr bool is_supported = false; };
struct write_support_true { static constexpr bool is_supported = true; };
struct write_support_false{ static constexpr bool is_supported = false; };

class no_log {};

template< typename Device, typename FormatTag > struct reader_backend;
template< typename Device, typename FormatTag > struct writer_backend;

template< typename FormatTag > struct image_read_info;
template< typename FormatTag > struct image_read_settings;
template< typename FormatTag, typename Log = no_log > struct image_write_info;

} // namespace gil
} // namespace boost

#endif

/* base.hpp
OF6jPhZDYqvfXwLFiGYCnkzHHnoPCv29JU0hO+AHaSdJvXRltAtJmX5f8ofToARHuwbEB+S+ny80OJMVFutJEq52B2Ggi/sZEyoyfeO668czSWiTx0c0fRKK7N24MUd8t72SqvYM+yVEGSS/qxYVMhMwQJIQplIVdus3a2Z3odYE1XTvIWXzLtoUepRPuS+p/ee3VDmQyUkBL6LpKpDtAdQf8q7Lxd9fnhE1I8HgKadgPJJcC9G7RwiztVKeUpXLqfJ+jTycJHwJRvbRD3Rhj3tQuU5p8d4HSQHngoY+K6HhSDcNsv3eIB9okNNfFwVpxSALrCD2HiVwt5jcHUy2Zeu9rFi4IMk/w9GGKUm/x58/LfonQk6monmm6kpZth2qFNPwQ3nsg0c0XFI6rRBKnKj2O7TTm10N+wf4YLuzy9gQByONQUSK8TKJsUWgD7a3Yf71Q/QZ5M3xZ9iHiCwEwfx9P98AaOD4F34IvgacE7PKqoyhVEWUGsUxqvORtN4tDDXDEmmvzaUS868aujOqoc+UNNtKMBOftmCleq4VUIk3v/Ryw0q1Xil6B1Bvc+qNaDoZ/qBpD+vCfWdVfABi0k7wPr2opDwN2ZAhr3cVGKSIzmp/oJwgcs6AA5sFZXxHLeczBQrpQXCJxFkAMKTo8LLF0Th3Eo2zkWAgXYz/GwykE/zlhTc6zw7Tql2yz9d9dUPaSgsHaRojfLYrUegWQtMkHJT4gftxbvwjvVt8MEKasK5FGEhjIJt6GpwE/Wb8+CkqpmJXtsA6ioM0YIMaF3UFkesykCtC7TWzQOVXrQTyUYOhLPsF9dhZ4xoeTEaGw9j+ArAsS+JNzx4i/TgiabSakyVzv/Vasqo1Eh26V+njhlU0NoroFyn3775H8Q6vuEzvaEd0QHQmOo1djp0Q+G/f2/JDiu5j+h0lnZ30p0Ztpie4YcyObNEyuPl0yfYWYgZ4ZL61ZL4rJVPFtPXInLRk1paSqWyqe2QuWDLZpWSqmhtPuWUuWjJDS8lUM996ZPItmdhSMg+azzwyNyyZh0rJVDcOj8wtS+ZOl5IyNc3L9+g5VUqmlungkblqyawvJVPD1PbIXLFk3iwl09jc6lyM4sgDrba5CFpRucYI5F2pwYqzEzT9/fiwqsyPrUZQZrA0ghhHSPc9voCX4WWD0bzAgfd5xOJ4TzW+/2DRVvVzoisnMu6Qh0nKcMmYfux2tS8g+yjYTh4NYtj2BOGtba+i+Ge3ipB4d00JB/4Zgh7ZLUFTEDRo81VY+B+hTY1D49i5W3rl8mBCUULj3KANwbwa1Nb4m2R/qMGJvEuIZQT0TBfRwPNrxegJGjsyMR0SibTxGni6frn/K4nta/IeAQ+kDV+VeKs3KTV8dwnqskT5DH+n2RJVlTXhtanqTIIEekpIuLfLxHfzzPMeQmfaQmXz35IuMwYxmo8SRGO6jcZWMfXCI/dOasH7fzSBv0MyhqjZe80UCAL3xqY4dciefFsldH4chgvWbsO1MTJvsPC7LLH5Ccz+xF2+bnCwcDDX665gT1BNXQiQrG3HcwWo9i5/hy+cN0Ah2pxQlPoVQZDasaPLM1fSBUTZxPfWT3EiNHNh/lpnfY6S5wI5IxLpa50ApSXI5mQ13W0HGio/u3OWmdhX55uVwEZKF+xE1dIo3fzQCb2re/nch+Bsy8Czid19raVqdy+xfRGvdvc7S9jdPxunZ1xaybu0Kybc5x4QTzZLBfG0jtukdbYOJvpwMQUFPU+n9NbJlGNQyd8siG1+RS40OaK3Ks0xI5/yLLKv6sKK+GMHE9uM8vZOUiw8F5SOYXbDbqqmr5BDNkOQ2ajajcF2SbAwjh3e0GWFn0U=
*/