
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
cZDv8yStrwyXi3/ol74qtBcY2vMpfKHI1CxpXgR9BKrXrh5TvTV31UmY9D3szUgHO9L4xUtlHPYR6ZMM0LsgGH51L29HZDu7i20Fr6lKHnHttXcSdUsoXDqWw7Qx4Z6rXTs7PYtv3ZPoRru91l6wz/yb6E/zaEudLEeALNfMkfGvrAMfAfVym6mX1xobv07K73osP6G71uj620J7o6G9gcLfEdorpay3g/052DWCv0bw36O/Mj7GOxP5dxDsryQ4j49vBtspm0hzqEAzJHOjt0KaU8f6NCj/bSLDDA/OHoOM1xoZfwR15BpT128XXdwhukA+PzF1907gc6Xh81OjJ+uTfk4wXavTd2xz9xvd6d44DaYH5J3yCLiuiWm/MZKfYQOxda3gXrEzJ9+vxAbfKPDHHC6scwH3C+5Awd0r6Sod2udDop8HpX17WPT8a9MvSPt5pim+eOjcc6HfVzBnoQfc4jHD9E7qR6HO7bHzvPpv5Jmye0xkexzyc7+xhyfn0M/Uo6ck3m8N7T0UftDQPgO287Tg7hHdPAu4e4xsz2l9EbkfgjaXwlxfnhc5HjJtyp9EZqX/k9C/IO3+L8G/vGjy8JJNh/LwF/qLeXzC1I+XAf+QyIo6eIXCDbnf6uTdGEOZXp2BQ7/9HyLvCWJH/huJjnRxZs37Vde/ZFgbx1Z43Vjnn9Nd3amV/OYVwkt5nTcMf6bU+WT/GdamzelkX4omsmh+a4msh+8AGyx/n++5tub2BfWNjfQOp7s3rpFOVK5YvHwZ88uB17unRE8Voqc7ed6AViCHgveg/sV6cltI0v2Dbt5Z2rN/Y3sm+aKJsm66YlGIIV9ROHcXuqRbx+kOJjcSEucBFTcacK3JRKqf9n7onpz/DJfDEa+n1pQ3iqAQiNB2Vs/+NY1VX0PWMJis71nXTzOLXb0huwjw/h2SJWQTbEMpT+9gfRPkKRO9aCQUBqHZz82K2BuG5QWB2e9K3YX0eb+0jjtFJ29xXtLtqVb/1WPVxTtzOG8DrjwSPW0ZnRwsZfLucJu37ykjjNNfi+XA/j0oAt2bWCy26eZWFxEF7lssF9zhyS2MUnidR6ZHV64uG+ptJ6vO3LnqVcF8Zp7vAUfuv3ofNsf75KtkLKdtHfdv1vX3d8peWpZPYlOcgGaob30fbb1w8zoyDiysyu9+y2z91VEcf2OiZyjpNUgZFoF+infRB+9kD/PyxraW+PJlTa1NRzCTKERGT6NFT+0hX7ExOej8rOgl8REnv5hT/2BmXn4MxS1WeHM3yRz47FKFg9M+VGzjQ5D3sl2qgyhjx2DPysGekB8jGBmi8SkEk/WLg8WH7AHpl/rpExGYJoA07WV56Lxt8bLDmkm7bS3MJRsyo/u9RPcn5ND9hbNY9/paNzWw2F7S4zGdQx3JzvqM7/hwldOptm8pT8ujXGHYilKchdKOFoNOqqVMJALfoAWqMRhta7AvQCXXmBxEexgtbXirtQqi0TpRgnViF9+K13m4PVmHKuAKqYNqHwr3MmmON2lK7uLtW9JJrIYIhrsroV1v38IVQ21PYOQvM+flP/IB/cje4Ee0fS5F+d/Hm++RfcJd1APfWVaFbZvmX/Ud7gPuU4Vl0eBYebrXeHJEfmxHDoEqw07fwM/TjtUPTq3StlloFsi7l9KGVu+kL1MX0ZdZJH2ZJeIH94W8tviy0iPP3R1ROUYU5jtyne998uL1w6rwWHI6hXFMNEPCBJe5JXgnXcIa91Uzntpf4hJcaaPP9uTpk528FUbe2UbeSgnPNvKeCvLyfRpmDF1t+NRIuLoqL9l32h9zaR5gZJ9n0pwvYQe3ut3H0B4kYQfHfE01aRxi4n1Cwoc=
*/