/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2012 Hartmut Kaiser
 * Copyright (c) 2014 Andrey Semashev
 */
/*!
 * \file   atomic/detail/config.hpp
 *
 * This header defines macros for linking with compiled library of Boost.Atomic
 */

#ifndef BOOST_ATOMIC_DETAIL_LINK_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_LINK_HPP_INCLUDED_

#include <boost/atomic/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

///////////////////////////////////////////////////////////////////////////////
//  Set up dll import/export options
#if (defined(BOOST_ATOMIC_DYN_LINK) || defined(BOOST_ALL_DYN_LINK)) && \
    !defined(BOOST_ATOMIC_STATIC_LINK)

#if defined(BOOST_ATOMIC_SOURCE)
#define BOOST_ATOMIC_DECL BOOST_SYMBOL_EXPORT
#define BOOST_ATOMIC_BUILD_DLL
#else
#define BOOST_ATOMIC_DECL BOOST_SYMBOL_IMPORT
#endif

#endif // building a shared library

#ifndef BOOST_ATOMIC_DECL
#define BOOST_ATOMIC_DECL
#endif

///////////////////////////////////////////////////////////////////////////////
//  Auto library naming
#if !defined(BOOST_ATOMIC_SOURCE) && !defined(BOOST_ALL_NO_LIB) && \
    !defined(BOOST_ATOMIC_NO_LIB)

#define BOOST_LIB_NAME boost_atomic

// tell the auto-link code to select a dll when required:
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_ATOMIC_DYN_LINK)
#define BOOST_DYN_LINK
#endif

#include <boost/config/auto_link.hpp>

#endif  // auto-linking disabled

#endif

/* link.hpp
y6ffibF8+jV3wqdfcwd8+jV3XpeO1adfQpa/D7zi5mPzgYd8ezrE/s7rUEd84IXqs8SnPrfncgYy9ZnH9bFxQdlp/5MJPr4D8yhnU+RxUAnaQK8NovynetpkfubRy6BtovM0+Xnq/6JPue6k/i2ecqmqxixbi0tP98fQ05aPoKccM0pP90frqWnv3dnR9dpGvQ546oXryVh1UtksvVeK8jvJ/s77neR4UTrKMdTv5H/Xjilur+TYK1FOsVd6++1Fl2Qd7PbeTT89v37DYOvd+PqynV1f9q9h+yJ539AiPviQdf2dEf5bro9rAtE+KnmHYmSaXTL36N/t+avk+ljWtN1pobf698NqS7XbvFOS92mybzx/b4eW2jgNhIMhwRoCC+AweBIcDufCkfAzcAy8FI6FZXAcXAjzYRU8FdbC6fAqeCa8Ds6AN8DJ8A54Grwbng6/DWfC/XA2fAzOga/BT8E/wXNhEmX+NMyA58Fe8AKYDy+EM+A8OAt+Bl4EL4Lz4cWwBM6HC2AprIZlsB5eBlfDcrgOVsAmeDn8HKyCd+jxHoBL4DdhNWyFU+ArsBa+Duvg27Aevgsb4IdwOUxQW5RMuBL2hKvUFme4eXfBcwLtL/qI1QjCNl4D4Ne13x6Gp6ht1+lwHyyG39R++zZcB9+Cr8L39DgH1DbqF7AnfBqOgc/B8fDX8Az4IpwGX4Lnwd/AJfBlWANfgxvh69peh7S93oM74A+1vX4MH4WPwyfhE/BZ+BP4EnwSvqzp3oDfgX+D34MptEMrPB5+F/aAoXqUhp6J6jPkSo8f1HuRGwJ3wkJ4H/zAJq753A9z4ANwBHT2F8Bd8ARnux7nsdCzCX1+w3HkvPuIHqeR/3PhtXAMvBtOgRthKbweLoWb4HK4GV4Jb4DXwBvhJrVpvBPeApvhVrgX3gFbNf6oxh/X/J+F23W83KXj5W61ebsVdoO3wX5wm9vf5o6O+dE80EG5wx2U695s5Jjb2vG32UG54g7K1bjkWjzlK3PJNXVQrqWDcgeOItcYtzH7j9iY/a/Zl8XXGP/odmWVqxOtqwnbCfsITxOOEIaswdaMUEnYSNhNeIzwe0LC2ri9WfwX/8V/8V/8F//Ff/Ff/Pe/+/sv2v9XXCHm/x/d/n9TnmV811yifswOETIJLxH+xgOEgze47f/1o+uSsrpyK6bfEk1zisZZjf5GJz4jpg8ajmfSDKVkHt9HxobsfZF5yioO+6EjXUx/JcY2768icx/rph8n6apMuizjj+A0KWOXiPeGHn+CmkbtANvzIeaR3UY8xchWG7lJHrlm4qbu+s2/8Unikd1NvD0/TUUe+ZbIdU4roNad93JS92FRbZFhbM4aqquki8N9fI7IJBg/fdr+KhvpkyZRZTPUl0ZXiX+Pd1HH0wMXpTuqd4N+C3AjHKjvu0qPYntS42NnsjKGnUmjj/+njTF8pzSZ7eiAbtvm8afSjW3NZlu1yOw2x5C+U79D/r6kio2saVuP7a+2o8fH1OE0S35zE3lfACfCwY5twk1+45Q8jE5FjVNNM9PYlv3pZic+2PiZaMfPkKY908pQPxrnS/zihNfsxYG2bVjhf45tPGVOs3J8/ZkV+5ThG1KGoVIGnpe364eItMan2lLikyVen/CBXROQbaYMB7QMMcc2eR3FP6CuC1/QJPbqgUetW2wz3j3pD3nHu9qy/UvS7mLt9MtN2kmetIfbmwM8skc6MAe45YHJm7cnqEb4e4RpIjcgcT9lmxlMsssTEtVODwtd6ZPtwUvtgYGrg5nGvvZnkmZrgpNnTqYMzZolBeixzteltzj7z7Pv4c3QWBv/J2on+WlJl5K4w9oVLOI4cxOSrUs=
*/