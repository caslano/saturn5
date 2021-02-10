
//          Copyright Oliver Kowalke 2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES2_SEGMENTED_H
#define BOOST_COROUTINES2_SEGMENTED_H

#include <exception>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/segmented_stack.hpp>

#include <boost/coroutine2/detail/coroutine.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines2 {

#if defined(BOOST_USE_SEGMENTED_STACKS)
# if ! defined(BOOST_WINDOWS)
using segmented_stack = boost::context::segmented_stack;
using default_stack = boost::context::default_stack;
# endif
#endif

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES2_SEGMENTED_H

/* segmented_stack.hpp
kZfHKIxvFEsqBA4LNIE7bIuCS6t5xBEFSqDCWhjZWLR0EcWzNEydH5goeFdSuDDueznWHx3rqZC4/jKqA7MDRzUKhaNeXovIBS7FXR/A4a/W31WQTpJwloVx5MwIFoPYMx6kGOmyCu3ZZTUzIjo1N5vRjiKsIPYw03zbgxo1OU/S3dRUoPYEhQ2WvBdeS4SqaOtBJNs14RwbZAf3jdIGI8Be2GOYb2zul1DmZQdlJkZB0DsB1RUFpSXDLM2JSnIuN8rRNbJdoFhbetz1Ya496NXdF3M3UFbUlKLsnRTEjg7be1Jgkqwyw8exbaS0Wd4YZOzJUmLT4vxhvR9FWyY7ZUzWDSlsz1YmX6y45ziGXOTyxNzsCHvKgKXpCYmywczRGBqpFDNjihMjmT4X56CkFem4xtARisn20Bsqe+3Pp5lzYr9mSZzFk3iaOrdSabsUfPVvZ9PA8UTl/OXAfwVlFvZCwocLo914pA8EW5Z6hVyPR6ilN82f6/B0+sJm4Mca4RbujY/6Ia4oclHui21mrZAa0x8qCYqsnxF2NP4/6L8dr2KWAP+zH079y3AaZgvH5xuyVXY9CbJ5EsFnfzoPnIRqHKTK5hHk8Sd7YpQGAfjTNMYRcJnsc0yC9CafxFEUTDIYHZwdImP/7t76
*/