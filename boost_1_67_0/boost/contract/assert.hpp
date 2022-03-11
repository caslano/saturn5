
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