/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010      Eric Niebler
    Copyright (c) 2014-2015 John Fletcher
    Copyright (c) 2016      Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CONFIG_HPP
#define BOOST_PHOENIX_CONFIG_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

//////////////////////////////////////////////////////////////////////////
// This section is to sort out whether hash types or unordered types
// are available. This depends on whether stdlib or libc++ is being used
// and also whether C++11 or C++03 is being used.
//////////////////////////////////////////////////////////////////////////
// The idea is to set up the configuration without including the actual
// headers unless that is unavoidable.
//
// The client code should contain the following to include headers
//
// #ifdef BOOST_PHOENIX_HAS_HASH
// #include BOOST_PHOENIX_HASH_SET_HEADER
// #include BOOST_PHOENIX_HASH_MAP_HEADER
// #endif
//
// #ifdef BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP
// #include BOOST_PHOENIX_UNORDERED_SET_HEADER
// #include BOOST_PHOENIX_UNORDERED_MAP_HEADER
// #endif
//
// The client code can then chose the implementation provided.
// See the example in test/stl/querying_find2.cpp

// There is no specific thing in Boost Config for libc++
#ifdef _LIBCPP_VERSION
#define BOOST_PHOENIX_USING_LIBCPP
#endif

// This may not be true for some very old version of libc++
// Current libc++ supports unordered_set and unordered_map without C++11.
#if defined(BOOST_PHOENIX_USING_LIBCPP) \
 && !(defined(BOOST_NO_CXX11_HDR_UNORDERED_MAP) || defined(BOOST_NO_CXX11_HDR_UNORDERED_SET))
// This is either libc++ or C++11 or later
#define BOOST_PHOENIX_HAS_UNORDERED_SET_AND_MAP
#define BOOST_PHOENIX_UNORDERED_SET_HEADER <unordered_set>
#define BOOST_PHOENIX_UNORDERED_MAP_HEADER <unordered_map>
#define BOOST_PHOENIX_UNORDERED_NAMESPACE std
#endif

#if defined(BOOST_HAS_HASH)
// This is to sort out case of Clang when using stdlib from gcc
// as Clang thinks it is gcc 4.2.1
// This prevents the failure to include a header with a warning.
#define _GLIBCXX_PERMIT_BACKWARD_HASH
#define BOOST_PHOENIX_HASH_SET_HEADER BOOST_HASH_SET_HEADER
#define BOOST_PHOENIX_HASH_MAP_HEADER BOOST_HASH_MAP_HEADER
#define BOOST_PHOENIX_HAS_HASH
#define BOOST_PHOENIX_HASH_NAMESPACE BOOST_STD_EXTENSION_NAMESPACE
#define BOOST_PHOENIX_HASH_template_rest_param class Hash, class Cmp, class Alloc
#define BOOST_PHOENIX_HASH_type_rest_param           Hash,       Cmp,       Alloc
#elif defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB < 610)
#define BOOST_PHOENIX_HASH_SET_HEADER <hash_set>
#define BOOST_PHOENIX_HASH_MAP_HEADER <hash_map>
#define BOOST_PHOENIX_HAS_HASH
#define BOOST_PHOENIX_HASH_NAMESPACE stdext
#define BOOST_PHOENIX_HASH_template_rest_param class Tr, class Alloc
#define BOOST_PHOENIX_HASH_type_rest_param           Tr,       Alloc
#endif

#if BOOST_WORKAROUND(BOOST_GCC, < 40100)
#define BOOST_PHOENIX_SFINAE_AND_OVERLOADS , void* = 0
#else
#define BOOST_PHOENIX_SFINAE_AND_OVERLOADS
#endif

#endif

/* config.hpp
Ns4LcWMjPxmS+0kddyNKIZMmWpBCZruN4mxacbKye5IcQ3JHkGxaKZ7CIrZtp7v0rIanSL8CQOGUVaPMWTpXmaMy1QU1dgIty57WIgDSyFnxY7w5i23ysaSZD8YBbuYwlspVHTAup7iEczdxAgHR6y2lMzrL2gqhItkbV9UuPqCdmq+lrkY6n2eTtdkvAjimI9k4jH/IZXoxoROnO/ztvBPWHakOJWDW9KMgOb8kOz5NQH7rFL8Bv3UK7AohhyDvkvbHy5YXCTTWicxgWV8Z486hK2CRahlfwmpo1dB/7Ze8/PDzOV5URgbm9ntjLSPNAmCc/uh0J0fofApvYe5sQ64UoBdN2F68FrYB2ywT86PUBP82wgLvYnGVjqWLrVDbeVx8a34i039FtSi8wjAcbO4gu4j3GdbzRNCC4bMGlQOKXY68nhrlVxLZYkZCCjk+NnKCv7GkfCW9XmnKrF/2yKg0uI84spgUJ3RNt3JGSrobehogyHfzcquEu8wjB6n2bZMKj++cww9dWyzUbJj6gIWZnADYrevyStpYQgX+XPnR1jmkCHk762D7QsgjTpKKTV8oC0f4SWQ2N5uDokKK2yR7VqNxlaXqLK7ab/+c32FcYK+7V8EniWw+clx2bMLS6chkThYGqqSdFLMkCcy25sHSWMIkgY057DC32kFOU9e/ZYnfQCQ3u+Jfajt9/97TcVbH7Vawjs9PozAF
*/