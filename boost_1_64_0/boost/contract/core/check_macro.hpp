
#ifndef BOOST_CONTRACT_CHECK_MACRO_HPP_
#define BOOST_CONTRACT_CHECK_MACRO_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Macros for implementation checks.
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp> 
#include <boost/contract/detail/noop.hpp>

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Preferred way to assert implementation check conditions.
    
    It is preferred to use this macro instead of programming implementation
    checks in a nullary functor passed to @RefClass{boost::contract::check}
    constructor because this macro will completely remove implementation checks
    from the code when @RefMacro{BOOST_CONTRACT_NO_CHECKS} is defined:

    @code
    void f() {
        ...
        BOOST_CONTRACT_CHECK(cond);
        ...
    }
    @endcode
    
    @RefMacro{BOOST_CONTRACT_CHECK}, @RefMacro{BOOST_CONTRACT_CHECK_AUDIT}, and
    @RefMacro{BOOST_CONTRACT_CHECK_AXIOM} are the three assertion levels
    predefined by this library for implementation checks.

    @see @RefSect{advanced.implementation_checks, Implementation Checks}

    @param cond Boolean condition to check within implementation code (function
                body, etc.).
                (This is not a variadic macro parameter so any comma it might
                contain must be protected by round parenthesis and
                @c BOOST_CONTRACT_CHECK((cond)) will always work.)
    */
    #define BOOST_CONTRACT_CHECK(cond)
#elif !defined(BOOST_CONTRACT_NO_CHECKS)
    #include <boost/contract/detail/check.hpp>
    #include <boost/contract/detail/assert.hpp>

    #define BOOST_CONTRACT_CHECK(cond) \
        BOOST_CONTRACT_DETAIL_CHECK(BOOST_CONTRACT_DETAIL_ASSERT(cond))
#else
    #define BOOST_CONTRACT_CHECK(cond) /* nothing */
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Preferred way to assert implementation check conditions that are
    computationally expensive, at least compared to the computational cost of
    executing the function body.

    The specified condition will always be compiled and validated syntactically,
    but it will not be checked at run-time unless
    @RefMacro{BOOST_CONTRACT_AUDITS} is defined (undefined by default).
    This macro is defined by code equivalent to:

    @code
    #ifdef BOOST_CONTRACT_AUDITS
        #define BOOST_CONTRACT_CHECK_AUDIT(cond) \
            BOOST_CONTRACT_CHECK(cond)
    #else
        #define BOOST_CONTRACT_CHECK_AUDIT(cond) \
            BOOST_CONTRACT_CHECK(true || cond)
    #endif
    @endcode

    @RefMacro{BOOST_CONTRACT_CHECK}, @RefMacro{BOOST_CONTRACT_CHECK_AUDIT}, and
    @RefMacro{BOOST_CONTRACT_CHECK_AXIOM} are the three assertion levels
    predefined by this library for implementation checks.
    If there is a need, programmers are free to implement their own assertion
    levels defining macros similar to the one above.

    @see @RefSect{extras.assertion_levels, Assertion Levels}

    @param cond Boolean condition to check within implementation code (function
                body, etc.).
                (This is not a variadic macro parameter so any comma it might
                contain must be protected by round parenthesis and
                @c BOOST_CONTRACT_CHECK_AUDIT((cond)) will always work.)
    */
    #define BOOST_CONTRACT_CHECK_AUDIT(cond)
#elif defined(BOOST_CONTRACT_AUDITS)
    #define BOOST_CONTRACT_CHECK_AUDIT(cond) \
        BOOST_CONTRACT_CHECK(cond)
#else
    #define BOOST_CONTRACT_CHECK_AUDIT(cond) \
        BOOST_CONTRACT_DETAIL_NOEVAL(cond)
#endif
    
/**
Preferred way to document in the code implementation check conditions that are
computationally prohibitive, at least compared to the computational cost of
executing the function body.

The specified condition will always be compiled and validated syntactically, but
it will never be checked at run-time.
This macro is defined by code equivalent to:

@code
#define BOOST_CONTRACT_CHECK_AXIOM(cond) \
    BOOST_CONTRACT_CHECK(true || cond)
@endcode

@RefMacro{BOOST_CONTRACT_CHECK}, @RefMacro{BOOST_CONTRACT_CHECK_AUDIT}, and
@RefMacro{BOOST_CONTRACT_CHECK_AXIOM} are the three assertion levels predefined
by this library for implementation checks.
If there is a need, programmers are free to implement their own assertion levels
defining macros similar to the one above.

@see @RefSect{extras.assertion_levels, Assertion Levels}

@param cond Boolean condition to check within implementation code (function
            body, etc.).
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis and
            @c BOOST_CONTRACT_CHECK_AXIOM((cond)) will always work.)
*/
#define BOOST_CONTRACT_CHECK_AXIOM(cond) \
    BOOST_CONTRACT_DETAIL_NOEVAL(cond)

#endif // #include guard


/* check_macro.hpp
XUFCfbWnacdZtdguNUx0zejIAaMCLsi+/n4G7I08cTnDILKAHHFt2JQD18/JLzcyKkMT9YL4/YNS4xqLbFia9vvKbFCo60QRACFQ1I5EKsWStEE5QqnJ2YR9OuD+zC9LU1RoFahtgqqUSzUkZ4cK/5hL/Kf10LlKxCOFOAnlCovgDdnKVwITdX1Ugk5z34rtmybnIF7iBFQFtLF4HnHhS3m0FhdA2AlDdRTWrfBOWIQ0ffjlwvTPOxMTVBfA+dzlgfio62sO227s+9NzPYmw24uIBm5IovLnx2Tv3dwcw/Baaa03AdtEPrYNcN3j3jlTCg3lAL+iD+TPwjmdDZxto5ZRS+U21Tsrb0FxT1ZN2ZgybEH797Z6MBsxUjaJFD9c45USzGqRrPLUHHLuS8HIQ4AgzEH7TJwPGSDUtkbYL/dTEKqbf9sWZ9CS8CvHABE8V78f4nRGqXh5uT+Wi7QKad6bKMijaox8N+Z3le31Ffe2ZrPmRqEpQ13Zq3TBdZYnDzMhFrKt5ojxT354j2FWSFJp4Uajz/d9DjQZQpPxZMbm54elQZt14YT5mg==
*/