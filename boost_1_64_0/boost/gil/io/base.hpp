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
HkU3xw7X4xZwSwBzN5ioxnQbsdDZ6OEyRbCcsxb2Fcfwf1VmGTrZT4cCRI9jXX78TkxkPAD+V5raDCpJhpXBIiQXG0R7MuOIs5Jy/tjyBJ8DozEuYx5MXNcIPtLZIT2crxIE3kPQcVLdttEiPb+nbHuTdo/vq2b0vQPX2CSTgtwTB/mPR/R6M6iGbH3N1r5dlBQ1D4RgQyrX87A6u0yOpL64IAmZAy+xaxm0BXuQV6pg7g4N+HWI28n4ukdeNbqiY4Qla0GImkvFcf+FpB5EU+bFPQZZmOwTxhEWh+SR6purxBIG/KaVXqeBJC1c+4rhiOdu2iL0TbqF5oE59S05Ffrs/GbW8BQ20MRox3tNDnkgpG1YhmkeIYnVBtkePvj32uSfck/NzBTojynLjs6H02A6J14A9H0QF8Jj3SEa9fTcA9g59LtdCyOpJLb2tsxr32uEjOcaiFbuesItokGKTudcMH78sCuINLLevBWTtU0Bgxu8UCjKtiX70ETIXyxdAH71V2M5n0MeE7a69xLkb09IOyyX6yUxsKM+nwr2xLiNVu31D45WakoeQg==
*/