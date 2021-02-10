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
8/5JM3p5vMGN6LKNqg4FR4urjY91bPUJd5FSMQAmJcBTGOA1bL0yhj803vNxz1V3M71DpTCEsdbhIBbITCssAQilxLeo5alzJUIp9LeS5AXu/OeIljms1W31LRy0V+QYBUPORVhxcrvJtrYgp2NdsXCTmQoIHpNoPSLrCB7rjZwK6eMjBeVb9kbCTCLdL8HGeggjab0s4OQ1Gk4GUAKyCyP6lYONORhtVlh3oo+ihR5EzhrIyIvCFcX4rBIsMAQyFpI7YwNC34T5nWha+HXiTmKTrYu9sH0MSC6jYsGEbPQEVuOJwFeC17xTZq/JElQcPA0dIsqkbPT0xuxEJ5VFqqqcLKN576CVAzyfxgvVd8Tc8IrFf2jzoR6z8Y78MjdXgeWcNVeiUiarKcbo9KGmDi5s0AUtLVaQugcCBG83DLtd1WsF9LPL7T6UGVAZB2gqSWUw95aDIq5kFm+S/ES61WJ6xJXSFLVJIbdjQ3Llnj1ssl8/nw16p91xz6qJ1VSLcBP6zsAOfYpSlrwU1F4RefIu3Xr1Z/hw+ofZlduXL15cm02PAOeuYaWX67Bab43yNr1cJXc2NJEx3AFYdqsTWCK4bMSn2S6R6875vm/MDNYgOh0bKNDDAHeTucO8HgiO+3+fwkM4ihu8Z7MN
*/