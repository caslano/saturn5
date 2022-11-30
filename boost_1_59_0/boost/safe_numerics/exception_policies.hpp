#ifndef BOOST_NUMERIC_EXCEPTION_POLICIES_HPP
#define BOOST_NUMERIC_EXCEPTION_POLICIES_HPP

//  Copyright (c) 2015 Robert Ramey
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mp11.hpp>
#include <boost/config.hpp> // BOOST_NO_EXCEPTIONS
#include "exception.hpp"

namespace boost {
namespace safe_numerics {

template<
    typename AE,
    typename IDB,
    typename UB,
    typename UV
>
struct exception_policy {
    constexpr static void on_arithmetic_error(
        const safe_numerics_error & e,
        const char * msg
    ){
        AE()(e, msg);
    }
    constexpr static void on_implementation_defined_behavior(
        const safe_numerics_error & e,
        const char * msg
    ){
        IDB()(e, msg);
    }
    constexpr static void on_undefined_behavior(
        const safe_numerics_error & e,
        const char * msg
    ){
        UB()(e, msg);
    }
    constexpr static void on_uninitialized_value(
        const safe_numerics_error & e,
        const char * msg
    ){
        UV()(e, msg);
    }
};

////////////////////////////////////////////////////////////////////////////////
// pre-made error action handers

// ignore any error and just return.
struct ignore_exception {
    constexpr ignore_exception() = default;
    constexpr void operator () (
        const boost::safe_numerics::safe_numerics_error &,
        const char *
    ){}
};

// emit compile time error if this is invoked.
struct trap_exception {
    constexpr trap_exception() = default;
    // error will occur on operator call.
    // hopefully this will display arguments
};

// If an exceptional condition is detected at runtime throw the exception.
struct throw_exception {
    constexpr throw_exception() = default;
    #ifndef BOOST_NO_EXCEPTIONS
    void operator()(
        const safe_numerics_error & e,
        const char * message
    ){
        throw std::system_error(std::error_code(e), message);
    }
    #else
    constexpr trap_exception()(const safe_numerics_error & e, const char * message);
    #endif
};

// given an error code - return the action code which it corresponds to.
constexpr inline safe_numerics_actions
make_safe_numerics_action(const safe_numerics_error & e){
    // we can't use standard algorithms since we want this to be constexpr
    // this brute force solution is simple and pretty fast anyway
    switch(e){
    case safe_numerics_error::negative_overflow_error:
    case safe_numerics_error::underflow_error:
    case safe_numerics_error::range_error:
    case safe_numerics_error::domain_error:
    case safe_numerics_error::positive_overflow_error:
    case safe_numerics_error::precision_overflow_error:
        return safe_numerics_actions::arithmetic_error;

    case safe_numerics_error::negative_value_shift:
    case safe_numerics_error::negative_shift:
    case safe_numerics_error::shift_too_large:
        return safe_numerics_actions::implementation_defined_behavior;

    case safe_numerics_error::uninitialized_value:
        return safe_numerics_actions::uninitialized_value;

    case safe_numerics_error::success:
        return safe_numerics_actions::no_action;
    default:
        assert(false);
    }
    // should never arrive here
    //include to suppress bogus warning
    return safe_numerics_actions::no_action;
}

////////////////////////////////////////////////////////////////////////////////
// pre-made error policy classes

// loose exception
// - throw on arithmetic errors
// - ignore other errors.
// Some applications ignore these issues and still work and we don't
// want to update them.
using loose_exception_policy = exception_policy<
    throw_exception,    // arithmetic error
    ignore_exception,   // implementation defined behavior
    ignore_exception,   // undefined behavior
    ignore_exception     // uninitialized value
>;

// loose trap
// same as above in that it doesn't check for various undefined behaviors
// but traps at compile time for hard arithmetic errors.  This policy
// would be suitable for older embedded systems which depend on
// bit manipulation operations to work.
using loose_trap_policy = exception_policy<
    trap_exception,    // arithmetic error
    ignore_exception,  // implementation defined behavior
    ignore_exception,  // undefined behavior
    ignore_exception   // uninitialized value
>;

// strict exception
// - throw at runtime on any kind of error
// recommended for new code.  Check everything at compile time
// if possible and runtime if necessary.  Trap or Throw as
// appropriate.  Should guarantee code to be portable across
// architectures.
using strict_exception_policy = exception_policy<
    throw_exception,
    throw_exception,
    throw_exception,
    ignore_exception
>;

// strict trap
// Same as above but requires code to be written in such a way as to
// make it impossible for errors to occur.  This naturally will require
// extra coding effort but might be justified for embedded and/or
// safety critical systems.
using strict_trap_policy = exception_policy<
    trap_exception,
    trap_exception,
    trap_exception,
    trap_exception
>;

// default policy
// One would use this first. After experimentation, one might
// replace some actions with ignore_exception
using default_exception_policy = strict_exception_policy;

} // namespace safe_numerics
} // namespace boost

#endif // BOOST_NUMERIC_EXCEPTION_POLICIES_HPP

/* exception_policies.hpp
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
*/