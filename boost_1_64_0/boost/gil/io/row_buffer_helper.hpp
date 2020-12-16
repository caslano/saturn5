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
ww27TSqwPeMtge0fWzXpp/8EXZl0ktCGnL4zSI40hEBscI6l4DzTn5axk5vyfpkEd97AcitKBl9yb6M/cLwBIxavyfoaj9dEvlriON5TeLlelXbYVHFsj1SRYFtJKgaooT5gZM3svmBiM47/Nkr9+lr1W95PORG6pRJBNwAI1JsUddAfdrsOMIDt+p7itGmomfQd4Y0cmFIH/YILfrQXyZ5ZqSdJCgc/RQjPvR2WwdmuYpdk3rmfJZlYlwoO1XWOZtAzoT3cj+TL9lkZuS4HHyfsRR+e6nL8A89EPNPwPHfB8yqeRXiW4vkCz2Y8Kb11csLp3xRO/957ODIruWaDPf0bY03/TE76MCExMGHSuR3nXT/IUqzM/LDmB+tjuZaIxnbgvlcP5wAz02OcM33LdQ4odgnDS71Ty3UO2AbfKdNz2mci6VJA0G1c72XdeXfv70KWNbwJDD0Y1xAwF/TJiVy1y+/r4ObnpKa0/yRWAdZMSU9ENP/qg4J2GtE6JftST2GBzgP2/ibqbxjDUxBZ0pJ7rRk1BVnopDKTk8qJf9MGa00qO5MskFfGnYe0Q8myAubFPeHtds9KdX8aiye6aVq7jdmxWFNMQ7RDafmbeJ7vN4r4HL1c/Jy5uA/T3SmkMZfJRzFnlmOsmeXs0TL8n2LNLDn458TybTCo6n2dsZUXqUIPWfz7wWsco93Gr05HAZYzXNgL5LYf1xlAxttjfYGUWPzG4zcev03xC/r1xvWyGQmyFncnqOtt6y1OSZSBCRq42XKAXHDWl+ff1gsZspC8Obu3ajj611E/wI0RmmqkJJhje7NzGaVkfxDIXOP7BMCkogsXk+Rb+vrKQK3faHvthIUxa2gl0zHmNc5A8MxhfSSDSU3FIIZt8SMqe8x8HjAHC2lL2KPdgVfysSXtX75Uv2scjJfco1OSK/uwYMF/ccYl1nT2rRAQOCQMOwSneQmQOAkCiGOjZRCBNN7pP8A81dvOaX9vVbovXpCOB0fIwWbOboDBouCT/sj0GNJP61xYGbJKM0vIhO1mKNg6kBTCdoi6J63Y4ngEkNY7vMZfF3Yqt+eUeFRtz98i7XngWrs9JyIE4pF0JN3YaPyEFu3notcB882RNCBE+5wu7ZPzoiWk9y6ZsukA46Ty8nJ0hmDl+9jHwvgtPVCDpfs74hNnnoNcdzAXGqOyYzp/t4xzO3MSYp83o0FDkaAw9iTkQoOXC2Kuk5iTv0s3mkCnELHWSEG8hV3JsQeEWEaZYZodhnG/IjSQURM4Xx0Lbc+iceyRjDadXc84ygTqKWKipzBOu4cTf2j3cPndjHAD2/dRUTo+EI03gnyYoSI7A7TT5nl8lDRPELly86y8zJdC0g0GmtJ/d5HSn8tjBR7cd0azpIL2UWvKXeENueWNJk9WZZBgvjVYaPWod/hW4yzshepPyWmW4MiuHS6mDWTy7pyjZsLdEY5kedkpocQ3/UH10i6K4x+Uth1HPx8AFkgq6OU0XdN5e5xLSOMdvk0MgG+XZYlHs0WkQpyrDlmj41xEMz+/S8Xwc6vqWMdjvc88qJsWA+Ti7Qsv1Gb9E2BVTCL4quzkqXryPSjk4BGVPUlH2EGMgQV00kncGIzVxHTsz3CTiPepdEAR6ulYSeSuHwdrl4+oEMQ0AFbgEcb1QwCBicSKEyzTtvQx9w7X5QBrQ0+U0GG0LkQs7q0iwqA/WcKXhxMAZUbIzw7Z+Sl2xOCFnYFD8tEFJW62jGKvMYbEyeTttRPP6SboGOK8CZxUbhPtYMwtwzXmsxLzO9n/EVDWZE6SuiRtpzhnoDjWfhGHW1+vFn6MPazDkba9pFVm+S1tMEkT6Jba6f3WnD5mt/g=
*/