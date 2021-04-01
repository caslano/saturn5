/*=============================================================================
    Copyright (c) 2013 Mateusz Loskot

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_STD_ARRAY_ARRAY_SIZE_01062013_1700)
#define BOOST_FUSION_STD_ARRAY_ARRAY_SIZE_01062013_1700

#include <cstddef>
#include <boost/type_traits/integral_constant.hpp>

namespace boost { namespace fusion
{
    namespace extension
    {
        template<class T>
        struct std_array_size;

        template<template<typename, std::size_t> class Array, typename T, std::size_t N>
        struct std_array_size<Array<T, N> > : boost::integral_constant<std::size_t, N> {};
    }
}}

#endif

/* array_size.hpp
loqB18qO3fwN+8RTbXLXf7h7uTPRrkHgHYlxXzAz4eZqSZMOw+mez/XIisqFK27v+19d1pqzFJQuRIic413Owh2pE5Mv1BLdLpodpX74WTaaWyCDvfTbYSDaxnV4CniplE+xoinlcxCCipTMe74UVlruTw8DXMuKr1dOF3kK+Eo/1WyVUxNOvYSpH4SPI6mkMte5Q17fs5AYCYS2hkwXNeI8jQBZR562+9DL8Tp3Twra6/XDPKEi99wB7h1IpKuNj4M2CVBuU1E8zzXxViMEgsLCvXybdUdqLezLPeh3n9MpQAeIUXpKaoldA2o4Z+Vqa7V5O3HjYczyXEOqFkEDOot5udzqxPaSf2ABJn7pXTrvp66O6oECwnnbJC1VcfRjoCL6DseG364lh7KU25+OUVYRtm4oXfhsY19wk/V+wb9ZsUrj/JldoHFeuYzY6cnl/eT3SQsHPNQ2QxM4V/8sDCGJBk6GE6d8B706poNhKYGnUlJ4Fsqmbc7uYssccQ8r7+Ywq5m8081mdnm/qGSRfJGTp0G6lnRObjC8yk30ywjC+aW/8voKIcjtIQ==
*/