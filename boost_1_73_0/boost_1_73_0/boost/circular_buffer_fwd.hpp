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
985EIQoazlb5MJE1FJQ2la3/CmQLmaRsnWEZtoBjpGWDI2iNRNfFdpc+KOzd7Kz9T0lecpVgDWcCJ+M5TOcnkAtSFMH9dPHt5tcC7sd3d+PZYgk3X2A8WzLX9+nsmuutWMkBbhuHxMoOVN1ohbITfLsxwK13ogjlHQ0AiqYJEwDLch9gv+GtKB7FCmkEw+CPWFsl2XdTtsRI2HC23Ia5bdCIkmKJ677V+g5pnF0r7kwQoT+TanD4XuIAItIB0B2Kkp3ODuIsVotHBGrZVb3ydVJw7aRFMu98aBmY/AzvT3utFRp0wgcdrrxrQ72RPJ0NDmquhrjsQT+4QpT4rX9+maR5q7QMt+rOwkKt2j4PvlfX4cQZma5r+d5CQ4nCcwh1H44lUhy1Z+RcOVaOmPiZCuK4Z4pFAMVxcC7uTKguDtsVkWjUq5fO182rbY1eaGUeB38AUEsDBAoAAAAIAC1nSlLnjrqLbgYAAMsOAAAUAAkAY3VybC1tYXN0ZXIvLm1haWxtYXBVVAUAAbZIJGCdV81yFDcQvvspdMuBQgVrHCpVWy6BDUvWMVA2gYIL1TPTu6MdjTToZ9bjN8klqTxArpy4uXivtKRZswvhx7l41V9rWlL/fN2eBdQeLTvREBZsqqTzTiwbveYa/SGb
*/