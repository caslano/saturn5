
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
FMUfOsH/IY3PEU5FDnuxZcH3IZWb9Q0KW75FKhfwxfhRRm4bP4biHa+PoR5+YuphMeHsRb+I2Sc+NiTPfQZnPPDv4Z+cVRX+exsa7mdpREwerQ5KMZ5pmHvoKT7U94XZoui+ojzdBnE5qB+MClxlnkThStEPyjy5n7K29YT3IAC/CuC3n7GBfSn8Bfph/qZC/keExFdR2NGdAnRnIF3Jx0yTbla59HOFLvaRZytP0AGmnUthlNnGfxFoFxva88qhT4z7XAU3JXaE+p4P9NDG+E51ipsVOn9es9DMoCNAfLW8G2D2Ry6WerNE9KiyYFwd6lhorDJj/QMFd5nghrcn8ZZYW2+ir0fFhLC01fVQtitC+DaUmzlr4bsyBNfuN2sS3FU7krEnQVupQEYJq4wHgYxrQviuNTIeLHy/Wo59Tj3LxfigTzk3IGkOlTS6nyl7nl/XzGzZDvcOExrNhu+UftYHWyRNq6QJnasakL0NKVxfDmd6QG4rb1u5f86gXXh3SLrcaw82rwXeBknbCf5nPZRTN+oA6CTKhRbooEdobZQ0++WZuRoch8GcQi3h453GSyls7zReXu6/39Aja9qN3Ceg5UK/IjCd1QSbyjC3/t2c0vHo1wg+m+H+fSdMU/hWe7JmJ7AYwWpD9v6u4/4GL1xyOE7hNV72muXhBD9M4B1yR1MXwdo9WcAUvF6C9QiMMQk+T+5TSmb0Y+J8P4t5fcMC+5kfJVSbFtJpf7QPynyTlN9S6ZMdwfK4NLjHdA3sTVgLexMO9oI7qA+mGyBjiW4q9yqZ890MeYv27zP4Tmy/396woq6+yV27Ldd+0efyBrokrbFG7x7Lz8ZZVQ9YDqcgG6d27YKVdYvMeGArychi8HSW3GC3PtHbpUciwyOdyE5/7Itx/LoN/RrBvy715ChsO0zcMegfhYb14d8U3G+hvxBcuycA70f8tqQ7zqRz9HH9y6Y7QdKdaPLXYPJ3suCdgnlgPKGJb1kK7mnlcGeWoX+GoX+mpDkL9Wfivoe8hYZtX84R3HOz5SR8s8ddcH+APhZwrb7Rx14gaX8Yknat0blNe6Gk/bEpK8vXltXFku4Sk87ytOl+Iuku64efw7XprpB0V+bI45HlsqcY0pZJHn8maa/KwVP3jFmeV0u6a3KkWys/m+46SfcL07ZBOpMm37tB0txo+v+SxuDTvLfg32xtK8QObxXc25A24Fradwj+r6z8Ns/4dqWkuRvq2RnZ6VnP94Sk/42k/y2kJz64ZwhthOncW85r/IbWMO/3Qus+6+NC/MP9gvtAqK/Kbf9/knQPYh5NOpvHhyXNI1gOkMaWw2OC/7jBX1Wsto52TneVCP6TiM99svD7dv4i+E+jPxT66A+fFbznBO/DfFi35X4Wrtuu74h3tmbc+Xg0pRvu+QMK7oUJ/BuuXyZw6Y2l4cUCb+mMN/dKrKY71tV1iecem56Tcn02gbveWEtf7ybto53k+m4S12biTnX9N4hrjbf1xuNeOq5a4hK9dMlKjJelOe507suJHO1xuqSqtSPZ0ttBE0nN3dLX/K5rV6W1x7yfzf07hmPeGX6YwMPy/n3u60k85P187u8xnPOeShA7lzTl72n7kZurg/ilPb2Jw+MtKTrZSnQoZyRzik61Llncw/gXEf4xgt82APxLCf8EoN+8npgjqujscsI7Xen2g/dTwjsX6OnLbfHWbNyfE+6FPm5VoiXF8lxLsMs9ClUxnGHXE+waj1ZCpdx/SeGbvNZ1nRK+hcJ3eh28wpheKyXYvR71MptTgUIl7k6Ke9DjHmiGPf2a4E9oGdH0oNJ+3utq3hCXLAvu7wj+mo+bjEG08vgDxb/ldfWpjH8=
*/