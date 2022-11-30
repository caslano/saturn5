//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_ROW_BUFFER_HELPER_HPP
#define BOOST_GIL_IO_ROW_BUFFER_HELPER_HPP

// TODO: Shall we move toolbox to core?
#include <boost/gil/extension/toolbox/metafunctions/is_bit_aligned.hpp>
#include <boost/gil/extension/toolbox/metafunctions/is_homogeneous.hpp>
#include <boost/gil/extension/toolbox/metafunctions/pixel_bit_size.hpp>

#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/typedefs.hpp>

#include <cstddef>
#include <type_traits>
#include <vector>

namespace boost { namespace gil { namespace detail {

template< typename Pixel
        , typename DummyT = void
        >
struct row_buffer_helper
{
    using element_t = Pixel;
    using buffer_t = std::vector<element_t>;
    using iterator_t = typename buffer_t::iterator;

    row_buffer_helper( std::size_t width
                     , bool
                     )
    : _row_buffer( width )
    {}

    element_t* data() { return &_row_buffer[0]; }

    iterator_t begin() { return _row_buffer.begin(); }
    iterator_t end()   { return _row_buffer.end();   }

    buffer_t& buffer() { return _row_buffer; }

private:

    buffer_t _row_buffer;
};

template <typename Pixel>
struct row_buffer_helper
<
    Pixel,
    typename std::enable_if
    <
        is_bit_aligned<Pixel>::value
    >::type
>
{
    using element_t = byte_t;
    using buffer_t = std::vector<element_t>;
    using pixel_type = Pixel;
    using iterator_t = bit_aligned_pixel_iterator<pixel_type>;

    row_buffer_helper(std::size_t width, bool in_bytes)
        : _c{( width * pixel_bit_size< pixel_type >::value) >> 3}
        , _r{width * pixel_bit_size< pixel_type >::value - (_c << 3)}
    {
        if (in_bytes)
        {
            _row_buffer.resize(width);
        }
        else
        {
            // add one byte if there are remaining bits
            _row_buffer.resize(_c + (_r != 0));
        }
    }

    element_t* data() { return &_row_buffer[0]; }

    iterator_t begin() { return iterator_t( &_row_buffer.front(),0 ); }
    iterator_t end()   { return _r == 0 ? iterator_t( &_row_buffer.back() + 1,  0 )
                                        : iterator_t( &_row_buffer.back()    , (int) _r );
                       }

    buffer_t& buffer() { return _row_buffer; }

private:

    // For instance 25 pixels of rgb2 type would be:
    // overall 25 pixels * 3 channels * 2 bits/channel = 150 bits
    // c = 18 bytes
    // r = 6 bits

    std::size_t _c; // number of full bytes
    std::size_t _r; // number of remaining bits

    buffer_t _row_buffer;
};

template<typename Pixel>
struct row_buffer_helper
<
    Pixel,
    typename std::enable_if
    <
        mp11::mp_and
        <
            typename is_bit_aligned<Pixel>::type,
            typename is_homogeneous<Pixel>::type
        >::value
    >
>
{
    using element_t = byte_t;
    using buffer_t = std::vector<element_t>;
    using pixel_type = Pixel;
    using iterator_t = bit_aligned_pixel_iterator<pixel_type>;

    row_buffer_helper( std::size_t width
                     , bool        in_bytes
                     )
    : _c( ( width
          * num_channels< pixel_type >::value
          * channel_type< pixel_type >::type::num_bits
          )
          >> 3
        )

    , _r( width
        * num_channels< pixel_type >::value
        * channel_type< pixel_type >::type::num_bits
        - ( _c << 3 )
       )
    {
        if( in_bytes )
        {
            _row_buffer.resize( width );
        }
        else
        {
            // add one byte if there are remaining bits
            _row_buffer.resize( _c + ( _r!=0 ));
        }
    }

    element_t* data() { return &_row_buffer[0]; }

    iterator_t begin() { return iterator_t( &_row_buffer.front(),0 ); }
    iterator_t end()   { return _r == 0 ? iterator_t( &_row_buffer.back() + 1,  0 )
                                        : iterator_t( &_row_buffer.back()    , (int) _r );
                       }

    buffer_t& buffer() { return _row_buffer; }

private:

    // For instance 25 pixels of rgb2 type would be:
    // overall 25 pixels * 3 channels * 2 bits/channel = 150 bits
    // c = 18 bytes
    // r = 6 bits

    std::size_t _c; // number of full bytes
    std::size_t _r; // number of remaining bits

    buffer_t _row_buffer;
};

template <typename View, typename D = void>
struct row_buffer_helper_view : row_buffer_helper<typename View::value_type>
{
    row_buffer_helper_view(std::size_t width, bool in_bytes)
        : row_buffer_helper<typename View::value_type>(width, in_bytes)
    {}
};

template <typename View>
struct row_buffer_helper_view
<
    View,
    typename std::enable_if
    <
        is_bit_aligned<typename View::value_type>::value
    >::type
> : row_buffer_helper<typename View::reference>
{
    row_buffer_helper_view(std::size_t width, bool in_bytes)
        : row_buffer_helper<typename View::reference>(width, in_bytes)
    {}
};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* row_buffer_helper.hpp
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
*/