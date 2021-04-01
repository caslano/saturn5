
// Copyright 2005-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  Based on Peter Dimov's proposal
//  http://www.open-std.org/JTC1/SC22/WG21/docs/papers/2005/n1756.pdf
//  issue 6.18. 

#if !defined(BOOST_FUNCTIONAL_HASH_FWD_HPP)
#define BOOST_FUNCTIONAL_HASH_FWD_HPP

#include <boost/config/workaround.hpp>
#include <cstddef>

#if defined(BOOST_HAS_PRAGMA_ONCE)
#pragma once
#endif


namespace boost
{
    template <class T> struct hash;

    template <class T> void hash_combine(std::size_t& seed, T const& v);

    template <class It> std::size_t hash_range(It, It);
    template <class It> void hash_range(std::size_t&, It, It);

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x551))
    template <class T> inline std::size_t hash_range(T*, T*);
    template <class T> inline void hash_range(std::size_t&, T*, T*);
#endif
}

#endif

/* hash_fwd.hpp
KkT3qRbPBdwb7lQbc1ejQQ0lzOF0AX1ZJUhgG+OIUvnPU+vQFyVdhglJS02gEixOlN562mq/17aFO1trzcAurlOHDwnkD3cs6pNx0MYbVOezFaSn/x7ShhoxfQvTPjjAsH7H0VbZbKWgBaRhLswzi/nHhxn+rgzVcAWYGR0ggcRWBArp/2S3vq9Tup1HL0owi0ZAoeN9U76h2XA7gp3O71rn3ctjrFaYCtB4vhD7GAZx8nd7Any3I/WyUhk9zWiQrWc4mRaJZr7vXNAWP3BvzZj/KiP0XJ3To4/D9pJ6yWzO8lSJyxnU8u9AoReQy8UtfoeWSQZjKzLPOtKjnQGKZ1EcX9O5kf7CZvM0kSgH8OnwDVQCAQXlSTm3SdqmteqenZK9gNT1/EB0MrCArcmwHHu+sqCau982W8/exl2YnGPBHUaZaeHoVfsEa+pxqy78HRRMw20zOkYAD4x+aFvXaFUnvIglLjr0xRiVQbn4ldqZ0fg02UDAa3i/ul2IvLyXPgCPsEIMXf339OYsl+OmGtjxh1IfZKGZZaax/VREaVx2iyITw3sIMW4w1g==
*/