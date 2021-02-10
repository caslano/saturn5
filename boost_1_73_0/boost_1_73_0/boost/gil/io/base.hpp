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
Pia851FHuHOskdf7moGjTk/HPRmu27vZYb4sKfF9/7aHmLhQnHyTpRh4jFta0xqy8GVji7k/t/Rem7Fl7eZB083Dpptvmm4ebR2Fur0j2DyMhxqTGNe/xNfb5RBej2S3b29biwajGth/9s8s99S+r+9V43vrSje4FklClXCFkz7NWXfvASlTGiNHg7HIKA60a9er5+X3HJuDGaWWX63cH+K2Yj44bHBRhbnx3fbg8Aku4rhnBrj5we8T1tYtvxtZu93wJSut+A9QSwMECgAAAAgALWdKUlBRYCXhDAAAbDEAACEACQBjdXJsLW1hc3Rlci9saWIvdmF1dGgvbnRsbV9zc3BpLmNVVAUAAbZIJGDtGv1T20b2d/6KVzpHbGow4M61CSVXY5vEE7A525TLNBmNLK3xXmRJp5UMTtP//d7bD1mWJQOBu5venZsC1r6vffu+V/Xd5/tswS7c+7Hk/xZ+8LfEuIyCvzMnLoa2rC+g/kOsD/j7PiZ1WKJ8sapwP8oXqEgUS3P5if62rPsYfSDZ6EedMD9Y9Cc+QTTCbAXhIuI30xgqrSocvnz5I+zB0cHRQQ3ats+ZB8OY+WMW3dTgJ1c++Xlq393tC/a6BiwG29vXpEZTLkAEk/jWjhjg3x53mC+YC7YAlwkn
*/