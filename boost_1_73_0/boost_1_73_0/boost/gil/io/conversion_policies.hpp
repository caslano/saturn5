//
// Copyright 2007-2008 Christian Henning, Andreas Pokorny
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_CONVERSION_POLICIES_HPP
#define BOOST_GIL_IO_CONVERSION_POLICIES_HPP

#include <boost/gil/image_view_factory.hpp>
#include <boost/gil/detail/mp11.hpp>
#include <boost/gil/io/error.hpp>

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace boost{ namespace gil { namespace detail {

struct read_and_no_convert
{
public:
    using color_converter_type = void *;

    template <typename InIterator, typename OutIterator>
    void read(
        InIterator const& /*begin*/, InIterator const& /*end*/ , OutIterator /*out*/,
        typename std::enable_if
        <
            mp11::mp_not
            <
                pixels_are_compatible
                <
                    typename std::iterator_traits<InIterator>::value_type,
                    typename std::iterator_traits<OutIterator>::value_type
                >
            >::value
        >::type* /*dummy*/ = nullptr)
    {
        io_error("Data cannot be copied because the pixels are incompatible.");
    }

    template <typename InIterator, typename OutIterator>
    void read(InIterator const& begin, InIterator const& end, OutIterator out,
        typename std::enable_if
        <
            pixels_are_compatible
            <
                typename std::iterator_traits<InIterator>::value_type,
                typename std::iterator_traits<OutIterator>::value_type
            >::value
        >::type* /*dummy*/ = nullptr)
    {
        std::copy(begin, end, out);
    }
};

template<typename CC>
struct read_and_convert
{
public:
    using color_converter_type = default_color_converter;
    CC _cc;

    read_and_convert()
    {}

    read_and_convert( const color_converter_type& cc )
    : _cc( cc )
    {}

    template< typename InIterator
            , typename OutIterator
            >
    void read( const InIterator& begin
             , const InIterator& end
             , OutIterator       out
             )
    {
        using deref_t = color_convert_deref_fn<typename std::iterator_traits<InIterator>::reference
                                      , typename std::iterator_traits<OutIterator>::value_type //reference?
                                      , CC
                                      >;

        std::transform( begin
                      , end
                      , out
                      , deref_t( _cc )
                      );
    }
};

/// is_read_only metafunction
/// \brief Determines if reader type is read only ( no conversion ).
template< typename Conversion_Policy >
struct is_read_only : std::false_type {};

template<>
struct is_read_only<detail::read_and_no_convert> : std::true_type {};

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* conversion_policies.hpp
dQrxYbyAa+67wa0AOliiV98aB4G3UdZ5wN3q1m9bGLmHzLn8dNP1JwHgn0nE48Wl7Xyyb9gxLg87ratBd/TeGo6ao6shiNiOE3G8hUuo6r8mLFpIzxIaFQORxIUJWr2UFsUBjQYnIKwQuZz5e68lbo4jSVGpjFpvmwPYrcKo87dRZXhp9ZoX2kJrW5szU/6zk2NQNZIPmMfQLKXsRuRxMpmg22I0xcCDSvaDGGPsPxIeUYz1F2ghTG2HTypmRyekIqtj9d9V4Tcp3XKLZxFjrcCP2V18KmlX1sUB+J1EiuRBQwFZ+Is6/Vdw1jwfdhDl93VrdCKGFqZOOV6E7BANWgjkUGqVN8xnkS1jMiYERHcXwHwncHFZnhuR2TsETQcUBJ4qESN/4/4N0SEFYiLiGMn9uMCa9RMKDaScX7n/UZ7MnvRTgdQxSWE+810VkknAKFyHpMfgI9U0SQbRDFPXFT1HW2sHM5v7H+irJBPaQty6YRGZF0KtBpF0PxQimmM6XpdNPSZFoMM5U7IMypQ1EDP6GQahiu12KOlMAxEX7FE+JsklEB2RBqoHSfxRA0mVSyVh8kmwkhozUrA8LUqHMrnqDAKIF8bRGg3bdWW+ucXkg99QPo62F9Ep+ezWW+A5e4FjU9RQ4a6kPJoG
*/