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