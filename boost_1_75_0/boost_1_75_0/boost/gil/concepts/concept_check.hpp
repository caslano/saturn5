//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_CONCEPTS_CHECK_HPP
#define BOOST_GIL_CONCEPTS_CONCEPTS_CHECK_HPP

#include <boost/config.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wconversion"
#pragma clang diagnostic ignored "-Wfloat-equal"
#pragma clang diagnostic ignored "-Wuninitialized"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wfloat-equal"
#pragma GCC diagnostic ignored "-Wuninitialized"
#endif

#include <boost/concept_check.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

// TODO: Document BOOST_GIL_USE_CONCEPT_CHECK here

namespace boost { namespace gil {

// TODO: What is BOOST_GIL_CLASS_REQUIRE for; Why not use BOOST_CLASS_REQUIRE?
// TODO: What is gil_function_requires for; Why not function_requires?

#ifdef BOOST_GIL_USE_CONCEPT_CHECK
    #define BOOST_GIL_CLASS_REQUIRE(type_var, ns, concept) \
        BOOST_CLASS_REQUIRE(type_var, ns, concept);

    template <typename Concept>
    void gil_function_requires() { function_requires<Concept>(); }
#else
    #define BOOST_GIL_CLASS_REQUIRE(type_var, ns, concept)

    template <typename C>
    void gil_function_requires() {}
#endif

}} // namespace boost::gil:

#endif

/* concept_check.hpp
nnJYhqkyKgbVmgcTjamPu74VOgpDE7Y7qL3vK8d0sgy+QcDiyoQgwWs8Gw1pMcFiLru/M8uSWcsTJYv6jkhIPZMMWxJOBLdROe6IOXGpVaUXQXqDees/d4jGdMrwogUTaniKOVmTHT6booO5pYOzG9mDDwcdiO2ejg+ZLzsgXkx6+QwRQhUSDui5LJb9xJuVTBUZASOQpyqp3TamYS6ZqiDh4gc9r1swIe5amJ8qymtyXE/Tx2u2v+U1QV+F7lGaNv40+cO5iIN51qT77DAgZ2OfemUwGzAgZRafPdsobZbCmns1dNoSNbq6lL+0IABmppfbJK2S5IPkDOfdn1ahqM0JBF93YJ7hXXzmi6+G5NssFYR3Tx2VKn44JUlndLFo8ogG99vNcETgQt+JQh9P4uDKzTyI9+zmlHeRGsNVMtjIoLJHNUZ7H9CYSJLUGpBwxeMPbipkkrmYNdZW1nqEH42mteaZC1/B87AZNkYN7ioTcsCz2IUuMjNPLLZoF0fPYUu2UWgVj3HArctdyrSW/riiIipcAOOa/ZkdeWNzdNtFC8i1Is1rVFsfT6wA/sVqMD7sI6x7gldYTRtjuZiuwOdLYPW37oR7vdDp3BkBYPJN92yvLZQXliN4Vno+X69rxmPt9nHeI1vTEiZJmj743bj8gkCdotSEBpHcGkd52JHjUlScFdGC4xJ5Hs7yxCOREA9aBaQv2oKp/G9H
*/