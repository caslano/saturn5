
#ifndef BOOST_CONTRACT_FUNCTION_HPP_
#define BOOST_CONTRACT_FUNCTION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for (non-public) functions.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/specify.hpp>
#if     !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
        !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
         defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/operation/function.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for non-member, private and protected functions.

This is used to specify preconditions, postconditions, exception guarantees, and
old value copies at body for non-member, private and protected functions (these
functions never check class invariants, see
@RefSect{contract_programming_overview.function_calls, Function Calls}):

@code
void f(...) {
    boost::contract::old_ptr<old_type> old_var;
    boost::contract::check c = boost::contract::function()
        .precondition([&] { // Optional.
            BOOST_CONTRACT_ASSERT(...);
            ...
        })
        .old([&] { // Optional.
            old_var = BOOST_CONTRACT_OLDOF(old_expr);  
            ...
        })
        .postcondition([&] { // Optional.
            BOOST_CONTRACT_ASSERT(...);
            ...
        })
        .except([&] { // Optional.
            BOOST_CONTRACT_ASSERT(...);
            ...
        })
    ;

    ... // Function body.
}
@endcode

This can be used also to program contracts in implementation code for lambda
functions, loops, and arbitrary blocks of code.
For optimization, this can be omitted for code that does not have preconditions,
postconditions, and exception guarantees.

@see    @RefSect{tutorial.non_member_functions, Non-Member Functions},
        @RefSect{advanced.private_and_protected_functions,
        Private and Protected Functions},
        @RefSect{advanced.lambdas__loops__code_blocks__and__constexpr__,
        Lambdas\, Loops\, Code Blocks}

@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::check} declared explicitly (i.e., without
        using C++11 @c auto declarations) and locally just before the code of
        the function body (otherwise this library will generate a run-time
        error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
*/
inline specify_precondition_old_postcondition_except<> function() {
    // Must #if also on ..._INVARIANTS here because specify_... is generic.
    #if     !defined(BOOST_CONTRACT_NO_FUNCTIONS) || \
            !defined(BOOST_CONTRACT_NO_INVARIANTS) || \
             defined(BOOST_CONTRACT_STATIC_LINK)
        return specify_precondition_old_postcondition_except<>(
                new boost::contract::detail::function());
    #else
        return specify_precondition_old_postcondition_except<>();
    #endif
}

} } // namespace

#endif // #include guard


/* function.hpp
ZNX8hc6xLGf58y+SCJ5UcgFo/xZwPjRds6ActmAJ/gR1leCECxhbXQD06BmCFo739t645WMtKhQES8UJA+XxQHTPb8ss/aHaH6Cv1vQqLDaQmTmmomiTqQ73I4vxv7IF2SxwyuMciZVga5Xx3mBi/66z0k5zWKTZtaAFBaNFUrE0gVEG2FReXTvN6QTQ2PUgFUHC2zizKbrZAqcpoIxzb0HtVlODh4rYlEjoSgk/1O0kDH9FJL7dkeUBuBXMJ4+gQ3N1IugkvrpQYiyccWRf2Nzs2Lrxf3B0IJMY2AyPIigAFEmmPxs43WOdz91ij3UT47Vb5rv0XdcHOEXiGjAC59yJxQJtLwccW0qIH08LnK99jtoByG9CGXThoftklDZtWBIz2Uiimt2rUPJkM5OnTR3+L1mX2gEAWgiqMtcLQi+Q3TgGXyUF1Cpxs9vXoeZdK6WAlNmRl8hV3Gy9mkjI8Y37rAtHIqaTLhXluk7TDykAlLyL2Om/D6yrhK0v3F2Pcb1N0YDXajGU9sBp9AVT0dyiyi9iStO5GXKZzPBXDPz+ggj6QIqIXMpKtw==
*/