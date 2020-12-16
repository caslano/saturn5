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
HgNMJOE3JRgShqnoDGd/9WQ5e1Nk/xlJVI5z9V2SWyZuABjWk7fEH0F/CxVf7mxI8fdU4z5qrKqcOc4gcqYo5yg5d/9i/pVwXvL/lyicAYX4SaPe75W0lv7D8Of6LYVXWvV2Zb1O1hfqn0T/h+pf1ApaaCninEcCfcabkbFpvvsKIb3GQ8SZ4uH+fFq4fJ1DMcWMBReddkf88G49/Ji97XUVOAZheJ8G3jpnb3lZW/oz6ibM0UJVwzUVHDEyoW3ZQ/idXA9+BSuuFKc384K9bOlAr92UIprm/E08LR2UPa/+0+ukMNatl58V5OxV8SXObepZ6VwHj6nPeBXkz7mMhAdAUODA9xDMAg7MBEcAA78aqYPCJ8uUBAwcwqCnvr/rmrpNzmb4yFc3wItflATwcjPcZGcURVeXFg0W0YdKilbUpK5xltVsfYJsOe8UskIXwivFcFkeZ+IRIfD+49EkQbsb4fIwCKqSArkZayyfc72H4aMMy+dc4GF4K8PyOdM9DC9liI/tn5HOBZ4lB4G5GRvd37hnSE+z6BrSdVdDqq+Y7MOU7VpC9o7K0ldS9q8bUhy/fOGL/MNvXjxlNdEyw9lEDRnfqdBB+vdTqDWEUK1fkLCRhIYaimcomn0hoEGA8yMjWCRjA5xv8slbnmRQ55xyg0XQzp2QMeT/lCf8KST0I+EbIcSmOJ/h0y5lzyY7moTPlTCfhOYkvC8Ev88/R8JqkzBbCTdJuI+EySQwf5WHMX/Hw8C4dl3yd4ZCTvhNH7fQ70O9xHybL90RcHLh92pHOE+KhbnFvlaxVOcqkmu4yV+QHHvQOfe67DznmT/GKOKJ9J6TQZ168xt/tNasV8V/Gf5Jo9yDrAeCpj8PslilcNuxovGP1EFfkrWA28Q8xKj05Nnt1hZs3sKTHpoRGg5Xip7AsE+kK7Ev10/OTHDzsfLdo8DsN/JRqe6KneK8eE06l1/TZfnGtQr9zsDWOiVK4jUZunQD1oi1YL3/hAWBHNpGPEeJhwivGdxanmG5powG5vG2anTRRH4Tm/MLjByZNioZzpMRfG6iz4b2T4s5rpjH797jSm0HaphQ3yG1llB18FJDyPNJ9heyjk38hPwuyQURoqPAPNuOnppvrfGVhZqeXKbwnHfWHfTDixjsJPfKN0V4dtA3CjWP1GVCPUC7ChC5ORy98TQZb4DBCvuSuPWPSZFPlWAL/HnkzK8qYuWf6S8aAgeqTF+RWch0ximjgzJihLGIjEeV8ddnPIXRUjJTaD7Qkokz30Z5LGKCJcwyhrkVLtQk7v8vJHUFqb8oNc8smq5rPWvC1QSmYyth2MzcpQIvNo9xXQKT50/gRwYmf2Zl4ES4mMuAZFcSraQ50S1hPIOId0zFl2q1GFvESKUEL5HW9f5HUF4m3GpdMG+QBuZcXEyyskqOp+SZVqUlkyGZ6PCtx/0gxMF9Vgp+AUFnZzH4CMx+CIQG6HkkJEw1JGS047ozHAJmEsxGzH6M+NOj5q3miTHpHO334wCzIGbdh/idV29zKeFr8JVjJ6ceOafAcU8+7sdQWziN/gHOdnBw2nWE4P+RGkPqR6ACPyY1VEhdSZqnoEwyN89GA3dkNxBvrDFTR91xI3cd/gRZGi6ifVNgZAUbnUGjgb2CAzrsLxODYn7jjmJQzDnjSNZuJp5pc6RtxdkyuXknI4R65c3ym463ApuHo9221bCKUYvQSW9I/91AbtKn/e+HKL6WLM+/MIBCEDsGJWMQmo2l62QRruoW/obCARQ+BGFiRFrHZxuiIrovLg7e16N5EXJftXTFkJrPQOnbBDzWPtxKaVSplOKd05Qez5TI49yRd2fkjicQeVJRSh9drFY=
*/