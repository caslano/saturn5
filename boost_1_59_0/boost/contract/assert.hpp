
#ifndef BOOST_CONTRACT_ASSERT_HPP_
#define BOOST_CONTRACT_ASSERT_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Assert contract conditions.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/detail/noop.hpp>

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Preferred way to assert contract conditions.

    Any exception thrown from within a contract (preconditions, postconditions,
    exception guarantees, old value copies at body, class invariants, etc.) is
    interpreted by this library as a contract failure.
    Therefore, users can program contract assertions manually throwing an
    exception when an asserted condition is checked to be @c false (this
    library will then call the appropriate contract failure handler
    @RefFunc{boost::contract::precondition_failure}, etc.).
    However, it is preferred to use this macro because it expands to
    code that throws @RefClass{boost::contract::assertion_failure} with the
    correct assertion file name (using <c>__FILE__</c>), line number (using
    <c>__LINE__</c>), and asserted condition code so to produce informative
    error messages (C++11 <c>__func__</c> is not used here because in most cases
    it will simply expand to the internal compiler name of the lambda function
    used to program the contract conditions adding no specificity to the error
    message).
    
    @RefMacro{BOOST_CONTRACT_ASSERT}, @RefMacro{BOOST_CONTRACT_ASSERT_AUDIT},
    and @RefMacro{BOOST_CONTRACT_ASSERT_AXIOM} are the three assertion levels
    predefined by this library.

    @see    @RefSect{tutorial.preconditions, Preconditions},
            @RefSect{tutorial.postconditions, Postconditions},
            @RefSect{tutorial.exception_guarantees, Exceptions Guarantees},
            @RefSect{tutorial.class_invariants, Class Invariants},
            @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}
    
    @param cond Boolean contract condition to check.
                (This is not a variadic macro parameter so any comma it might
                contain must be protected by round parenthesis and
                @c BOOST_CONTRACT_ASSERT((cond)) will always work.)
    */
    // This must be an expression (a trivial one so the compiler can optimize it
    // away). It cannot an empty code block `{}`, etc. otherwise code like
    // `if(...) ASSERT(...); else ASSERT(...);` won't work when NO_ALL.
    #define BOOST_CONTRACT_ASSERT(cond)
#elif !defined(BOOST_CONTRACT_NO_ALL)
    #include <boost/contract/detail/assert.hpp>
    #define BOOST_CONTRACT_ASSERT(cond) \
        BOOST_CONTRACT_DETAIL_ASSERT(cond) /* no `;`  here */
#else
    // This must be an expression (a trivial one so the compiler can optimize it
    // away). It cannot an empty code block `{}`, etc. otherwise code like
    // `if(...) ASSERT(...); else ASSERT(...);` won't work when NO_ALL.
    #define BOOST_CONTRACT_ASSERT(cond) \
        BOOST_CONTRACT_DETAIL_NOOP
#endif

#ifdef BOOST_CONTRACT_DETAIL_DOXYGEN
    /**
    Preferred way to assert contract conditions that are computationally
    expensive, at least compared to the computational cost of executing the
    function body.

    The asserted condition will always be compiled and validated syntactically,
    but it will not be checked at run-time unless
    @RefMacro{BOOST_CONTRACT_AUDITS} is defined (undefined by default).
    This macro is defined by code equivalent to:

    @code
        #ifdef BOOST_CONTRACT_AUDITS
            #define BOOST_CONTRACT_ASSERT_AUDIT(cond) \
                BOOST_CONTRACT_ASSERT(cond)
        #else
            #define BOOST_CONTRACT_ASSERT_AUDIT(cond) \
                BOOST_CONTRACT_ASSERT(true || cond)
        #endif
    @endcode

    @RefMacro{BOOST_CONTRACT_ASSERT}, @RefMacro{BOOST_CONTRACT_ASSERT_AUDIT},
    and @RefMacro{BOOST_CONTRACT_ASSERT_AXIOM} are the three assertion levels
    predefined by this library.
    If there is a need, programmers are free to implement their own assertion
    levels defining macros similar to the one above.
    
    @see    @RefSect{extras.assertion_levels, Assertion Levels},
            @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}
    
    @param cond Boolean contract condition to check.
                (This is not a variadic macro parameter so any comma it might
                contain must be protected by round parenthesis and
                @c BOOST_CONTRACT_ASSERT_AUDIT((cond)) will always work.)
    */
    #define BOOST_CONTRACT_ASSERT_AUDIT(cond)
#elif defined(BOOST_CONTRACT_AUDITS)
    #define BOOST_CONTRACT_ASSERT_AUDIT(cond) \
        BOOST_CONTRACT_ASSERT(cond)
#else
    #define BOOST_CONTRACT_ASSERT_AUDIT(cond) \
        BOOST_CONTRACT_DETAIL_NOEVAL(cond)
#endif

/**
Preferred way to document in the code contract conditions that are
computationally prohibitive, at least compared to the computational cost of
executing the function body.

The asserted condition will always be compiled and validated syntactically, but
it will never be checked at run-time.
This macro is defined by code equivalent to:

@code
    #define BOOST_CONTRACT_ASSERT_AXIOM(cond) \
        BOOST_CONTRACT_ASSERT(true || cond)
@endcode

@RefMacro{BOOST_CONTRACT_ASSERT}, @RefMacro{BOOST_CONTRACT_ASSERT_AUDIT}, and
@RefMacro{BOOST_CONTRACT_ASSERT_AXIOM} are the three assertion levels predefined
by this library.
If there is a need, programmers are free to implement their own assertion levels
defining macros similar to the one above.

@see    @RefSect{extras.assertion_levels, Assertion Levels},
        @RefSect{extras.no_macros__and_no_variadic_macros_, No Macros}

@param cond Boolean contract condition to check.
            (This is not a variadic macro parameter so any comma it might
            contain must be protected by round parenthesis and
            @c BOOST_CONTRACT_ASSERT_AXIOM((cond)) will always work.)
*/
#define BOOST_CONTRACT_ASSERT_AXIOM(cond) \
    BOOST_CONTRACT_DETAIL_NOEVAL(cond)

#endif // #include guard


/* assert.hpp
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
*/