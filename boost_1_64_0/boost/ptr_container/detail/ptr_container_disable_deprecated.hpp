#ifndef BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED
#define BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/ptr_container/detail/ptr_container_disable_deprecated.hpp
//
//  Copyright 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>

#if defined( __GNUC__ ) && ( defined( __GXX_EXPERIMENTAL_CXX0X__ ) || ( __cplusplus >= 201103L ) ) && !defined(BOOST_NO_AUTO_PTR)

# if defined( BOOST_GCC )

#  if BOOST_GCC >= 40600
#   define BOOST_PTR_CONTAINER_DISABLE_DEPRECATED
#  endif

# elif defined( __clang__ ) && defined( __has_warning )

#  if __has_warning( "-Wdeprecated-declarations" )
#   define BOOST_PTR_CONTAINER_DISABLE_DEPRECATED
#  endif

# endif

#endif

#endif // #ifndef BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED

/* ptr_container_disable_deprecated.hpp
m02aFyvkwrYwKCFS1QKGmjyU/hUz/5+PZGCvEJ+eJ0f9WQWFdBmbtt4zAD6mL17QpFjUV8JPHTXNkSZuxVVJSVG+mJPKprJk/f8gsQn7sdqU6n5etGUo7Fz8dHWBfcwBj+HYz5TR0zZ+qXsVsgdkUqdRp8mUa/eykwJfDayC+CtLRDNIqGqs76DRFlzBN6dAhDbfrOdBqfz+1r+ica1EwDOwm59K2DOAah26m0iP4SK3uhXnvFc9Ds17vaE9X9Y2PrWIGHkvlhil3UEiSwW6dlktty/i06FW/rigEKiErlWA7o95F8B+baRNkKeDbll+EepD2nB49eS04umDkvwzVQo1lWjUIOmsN+sI821bN5NMTqKuguthDGxaWeAINlsifplSF4ROo6/e1X/IxBskDQ+bQaEb6P7slZHJDyrdelu9Fe1r1zsBrzN9GduP85PMu3tbsZ/XPceD5CYNoEwhwwU4bI8yz4JmZQowrSRoDwzhs9egSzmGT13Tg3uz5Ua2CqR8CYmYWQAb7e8Euot7InhsRcFd+cRBJX9RM7mz+V9DuXvNFOB9DbQOyQ==
*/