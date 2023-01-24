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
qDCVz8ldS9BtbmuLvS8n5Mhhs/T5F8qLg/znVgor9r175ht01GoEyirPYJGNicYdDt/ZqacA8rslje0Mywb3ePH9bKShonqq/DtILAR/soeRiDgwJ++peHfQ91bLpoiZWXxT9YVC4km8jIbdqrvDURkSQG13EVTDtu44l0oK2xPbHcG4IVehyv5C4u0PcC+Rq51z/hQuZQXOGnCUJ0NGqbVkY2JqEr+NZGOjmx+TEX9m060hZfSJYuxgcIFizeg1Z+4PnXlpqvane0QyhqErC5jjywu3/Y64IdnZnDQ/++QJrZRPZd1Le0Xh3Vc0onnkk8Jh0WTUe8nzhOr28RaYOSJGJf6ZCOvvE5+39LJLKZheJle76mzk+2D3qXd+2oD4fEisOfYyxSsX2WYOyeEX4R7XXQYLbAsCwgsOsNZpRyEQs1M1h3GVqP1eo7TAn1D6w7sOpLecHJz3bh0E9BV9a4uKnNOfgXmS+Cb4JyY3lNF4v6WHuYLSet6gOZ83IHLagq8vHOrbN7gnYKQXj75M/CA4j0Xad+yBTwlIhc9rSRB2yPybhIt5xcnLX22U8gR6qmLq4sMsLf1TXmNf8nre7hlXZR7waJkk2dQPvL1JeOxwCCDIpLC2s950f5CFF8gjq9M16bFHZPGnc3Jokn8iuoSCsp9r0PoWGFRBLIXe6dYPDm+AIgBNgIPzDpVLyhaf4Je8qNn4GUmuXX8K
*/