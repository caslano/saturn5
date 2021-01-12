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
3BW/zjYt3mBHxGX93Uy2LMBp+aLdR6iBxBwSrZRCmMPnEjy7rvscyJcT9xFaWoBzpefnUn8Ce5tpHToqDhibqA/98GqJ9IWT/c6QO3YkBKptymLerweX9cW8tr+layWPgqoDtJWEVyA1uo0JEi7w63fmMCza/sRXCYwm/WKJMzJVgrJfb3YynVpna8mZ/RgOzEPy8y4HzMu21TRgg6tZm+/2gT3Iw2ZeIUbBe3dDMaE5zTJh
*/