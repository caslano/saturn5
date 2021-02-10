
//          Copyright Oliver Kowalke 2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_COROUTINES_DETAIL_PREALLOCATED_H
#define BOOST_COROUTINES_DETAIL_PREALLOCATED_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/coroutine/detail/config.hpp>
#include <boost/coroutine/stack_context.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace coroutines {
namespace detail {

struct BOOST_COROUTINES_DECL preallocated {
    void        *   sp;
    std::size_t     size;
    stack_context   sctx;

    preallocated() BOOST_NOEXCEPT :
        sp( 0), size( 0), sctx() {
    }

    preallocated( void * sp_, std::size_t size_, stack_context sctx_) BOOST_NOEXCEPT :
        sp( sp_), size( size_), sctx( sctx_) {
    }
};

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_COROUTINES_DETAIL_PREALLOCATED_H

/* preallocated.hpp
IjZ37Ddw4D6dK6bL8/5o6JcXaRa/y66iq3i+JNH53u04zTPTlaXMpVCWVQIZZxqe40HGptppHOn3GRlq6ivPbcfrek/jrKe5F1c/rIxm/p3jOVccSDKEOx4obZEDlv4b5ER1JOimnx94ZGMU4WTbM4N5hXmqS+t5MkiiCMJJEuPp8nZ+7Mt1NH8bJxEMsGJsDjyQxWGd/QdQSwMECgAAAAgALWdKUvSYXDkuBAAAkAgAADEACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX0VHRFNPQ0tFVC4zVVQFAAG2SCRgrVVdb6M4FH3nV1yxL2lFyXQ7Undmu6NlUtqyJRAFMt1IlZADpnjHsZFt+qHt/ve9BrJtpyt1HoYomFx877k+59jxr13Y/2GX49ty8OZV9N8CLxx3SQsl/6Kl+f+EoniE4YOJ1zh+B9QUnrIeiz34rqxHmPRZxYh1Yp+L4jvgrm2T9ja1ydeFfcTIkDnmz2T7oNhNY2Ay24PDDx9+gQP4+d3hsQenRDDKITNUbKi68eCk6iO/N+T+3tf0kwfUAOH+i4J5wzRoWZs7oijgM2clFZpWQDRUVJeKbfAHE2AaCjXjFGbpYh0l5x7cNaxsxjoPsgPdyI5X0JBbCoqW
*/