#ifndef BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED
#define BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED

// Copyright 2019 Peter Dimov
//
// Distributed under the Boost Software License, Version 1.0.
// http://www.boost.org/LICENSE_1_0.txt

#include <boost/cstdint.hpp>
#include <boost/config.hpp>
#include <cstddef>

namespace boost
{
namespace endian
{
namespace detail
{

template<std::size_t N> struct integral_by_size
{
};

template<> struct integral_by_size<1>
{
    typedef uint8_t type;
};

template<> struct integral_by_size<2>
{
    typedef uint16_t type;
};

template<> struct integral_by_size<4>
{
    typedef uint32_t type;
};

template<> struct integral_by_size<8>
{
    typedef uint64_t type;
};

#if defined(BOOST_HAS_INT128)

template<> struct integral_by_size<16>
{
    typedef uint128_type type;
};

#endif

} // namespace detail
} // namespace endian
} // namespace boost

#endif  // BOOST_ENDIAN_DETAIL_INTEGRAL_BY_SIZE_HPP_INCLUDED

/* integral_by_size.hpp
Aafup5cR22Jn+GDRuOZJ5BoOilNVS+gC4z+EmHEyarTY/2ie8qn1sj9K5lZPQJpzV0pMpanoJAlD6bmnYdSH/EUxJetdqjPXzgZgpSSikDt3qggef9wFxz9mDltHk8OH2VzQbgchLtf1nmvKMnlXrzt6cBaGiIjb/gefq+XTde18Ri4C9CegucAURSbl9d4swuKlahQSXCOnKcKHtC4E7e6ObgUDCPm59aYLrhGM2Rg3NUoprXdqHQQ11+NOGWWhgXrY5s3vNVI6flAw63lPUScF1PB6mwxPRRbzbWpTZIXWPdsHTAHlmtS+b6Cs+szLsmtXQR87w4LBgpN4t3CBzHiKHONVxbWHEc4N3djbfCOygkUsw5hAnP0vxrmE1X8c84KAOqN57Clj/L3oanKzLOIYb8g+Ex9p76gb/8Pa/3MyQMYHWM9naZwGTrzv3iwqE+hHDtoKKKf3ga4mvA2kgtLoGGtzX6nb94T0Y09glvun5xIBw1vtkCfpGYrJ968TRuVvF/XX8xgegpE7F3glTAlQt+3CCACGQ0IV36wO6CNJA5hn9tv3iSb8vw==
*/