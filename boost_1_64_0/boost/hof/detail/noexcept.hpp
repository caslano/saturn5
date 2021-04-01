/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    noexcept.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP
#define BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP

#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_NOEXCEPT_DEDUCTION
#define BOOST_HOF_NOEXCEPT(...) noexcept(__VA_ARGS__)
#else
#define BOOST_HOF_NOEXCEPT(...)
#endif

#endif

/* noexcept.hpp
0fT0c8V/PwhT4tue2NSWOHzo3futEOoxAyTZT1KAY9uuHz3AppqyX1oCv7ZUB1mVpIaJoSqF5QTlTtQ4K0Uw/NYl2InsybP1KMTsP8Qs6b82m147WuUFUa4x7iEFPUaHjPk1kA5Z5J/8GJDbDKGmqqfS2a1PU7b35esxyJskUFjFFqefMAGn/KMWe4oRMEJYuMJ+T+7izgVDxVMSeD3XZj4NbEtBT7xwzhcdYb2UrwQ/jNTDKZSs01jCtJFBFdfOyhMgi17D52dvsiEdZ/Ve8EyvCGLDVrfDcSErfx4sIfBoaFAgSQVfOWs8SBWDsDaAXf2RzwsDsSrpaw/vL+ArWV8a4fe8AHTxFBjhyR0oqGeMU5gKLCOex29ufEUMi1NqUXWsN7qWrC+3AqOKrzNiDZZRY5sCYx2CUWTL4Sok6SjhUmHn7v3DeRDoNT6OXfyeI/pKKQuFLyh5zRKvTJ7rCMVSZ/+j/H/KC0rKzEoItd812pK4tU05YWCI2XIBJXC8/m0fWMBOTxiBezO9Xxw0mbm61XS9GsCSzB+ppOS5GJ6tCgQSkeBbw+j63A==
*/