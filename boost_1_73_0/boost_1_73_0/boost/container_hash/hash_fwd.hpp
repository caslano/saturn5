
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
YSJjCzTHNKy1LtWLXi+pqwxP0ktlonpJE4pgrfMbp7pEb3J2DbLUoCXUivtA8j7kMhVL+sYQ4WZZLzKh1v7eLTRYpD1ZgeJZ5uBQVXBlj8Bh5qLlkySU6L3Q9KVkocjadi3zI0EMqwNa1lWB5jAsKJdKDLwPdZHyysibQDRWXJRNyL+Tsr3vKcgCvYJWOINo1oIFU0L58CGavx1fzOFDOJ2Go/kljF9DOLp0eO+i0RlyQ6DVCvinsuIKvahA5GUmeHpk/IdWuhfM30L/Yjo8H0/m8WzcfzeYv74Y9efReARPofUURnJD7P6jBa1MLCj98Cx4+jx4jBu0ivM60yJWXFOm8Y2kUog7ewuj8Hzg3Qd+9QgSlmULlnxEai9llRNTF7LWmD1mOLNlmFV8YsBml6PxZBbNvKBYej+LIsnqlMNLcsGScv2X54lCY1qSj1zHDXibHIAuZwopZ3tKF2iFRVKkSO5uz7urFZizOSwE9UnNLu/TIOPkur9rXt1d+SpDqG/rb6RIoYuFUpV+o19WYsOwIHahKiWaQZJ8E8PaKTsnRxjO+gGCTU4iMZC3Umnidg5dGyX/PpL4N+PdOTHpOhvM+tNoQiLehCGb2c4wZhZbVbU/07IuEqKNa2dNE8uZxgXFrayklvq65B4+
*/