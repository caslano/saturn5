// Forward declaration of the circular buffer and its adaptor.

// Copyright (c) 2003-2008 Jan Gaspar

// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See www.boost.org/libs/circular_buffer for documentation.

#if !defined(BOOST_CIRCULAR_BUFFER_FWD_HPP)
#define BOOST_CIRCULAR_BUFFER_FWD_HPP

#if defined(_MSC_VER)
    #pragma once
#endif

#include <boost/config.hpp>
#if !defined(BOOST_NO_STD_ALLOCATOR)
    #include <memory>
#else
    #include <vector>
#endif

namespace boost {

#if !defined(BOOST_NO_STD_ALLOCATOR)
    #define BOOST_CB_DEFAULT_ALLOCATOR(T) std::allocator<T>
#else
    #define BOOST_CB_DEFAULT_ALLOCATOR(T) BOOST_DEDUCED_TYPENAME std::vector<T>::allocator_type
#endif

template <class T, class Alloc = BOOST_CB_DEFAULT_ALLOCATOR(T)>
class circular_buffer;

template <class T, class Alloc = BOOST_CB_DEFAULT_ALLOCATOR(T)>
class circular_buffer_space_optimized;

#undef BOOST_CB_DEFAULT_ALLOCATOR

} // namespace boost

#endif // #if !defined(BOOST_CIRCULAR_BUFFER_FWD_HPP)

/* circular_buffer_fwd.hpp
WGnYLyR5tYWQqV3+4UboOh7OcPzM0evNMQw9PuJUzVWnjMTlhQVQE2jTM6hkZ3JtYf/WuBDLiAwx+RD03T4m0CjhyAOVVQN1lcMj6JGQ7ohHpAgKg5VVjG9JyVZfoOIIOMFEfptGh9YBJ8gF3ecWndQ+UmYf8Us7NbswFlUBNoLpQSgcB89TSBGJB2PgarIBgeiPm8HKwZFwxc5vXcVc4E1zubV4qPudsUE1P3vQA/EF2Yu+37Yt7PJ8x0xLjClwRctfu8INDgeOj0iGqVH/Wcz+UrnkO2qtbzwBHEJkCYJHqYyXyt8Dij8lhQqW9yBitlHIfWhO9V8ij9z38wjr9n3XtGAtls0tJFKbaX/f9xqyxOFmuNE6qtFLm4umlybNb+4vFF8p4cWKhKn7zpNSlGlfGDx4xEQvYB0kShnU9d2vWtcljkgzzaUXYld4HpMkC2QrjSylLDmayr4+sRuQK5f1wOeL2EKPOgTbkTBvBRlSMrwjAzsNh/gSmxMoY+FYJwaOYgwyOW8lsfGre6wxeSd7DMhcs2tlz3m/1T2FRvTm8hJ5hOkm+7/aMg==
*/