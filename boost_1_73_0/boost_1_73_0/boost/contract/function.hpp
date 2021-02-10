
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
DN4V3c6fFbm7czV9PwNqgHD3EWBaMQ1aluaWKAp4z1lOhaYFEA0F1bliO/zBBJiKQsk4hUUUb4PwwwxuK5ZXA85etqAr2fICKnJDQdGcspsepiHKgCwRAfELpg1itoZJ4WJ4CoaqWg8wlgThWgK5IYyTHYYjBipjGv1mPs9bxfEk80Lmep6PqXArUz851RbZ1GQPsjFgJLSazsDaz6CWBSvtiinCzabdcaar2T0tDCiKuVSgKecDHLoyqvsjUEiGbM2sJTTInhm7aCm0jXZbyfqRIaZ1ACpbJTAcpgXtComJn0ErCqo6+y4RY5Qhy13Kv1Oye+4FSIGsYOIlECQT2BHN9AwugvQs2qRw4a3XXphuIVqCF24HvI9BeIraYBhVAb1rFNXIQgGrG85o8Sj4T+10x03PYLFZr6I4zRZe7OHPY5g8fwV/tQJV/fzlBCac7WzZ4ZV7/Mo9wg37K6NE7zNNjS0wflBLGuGSMwi9c995gnl5CLqhOdYdU4XCNFLtoZK8YOIKFh7kVBlWspwYqjuQZBtGcRIkzi9M5LwtKLyzUXv9Ve+dLkAucf8pmal9As8qVAZHgTwmghqsiIJnOWmIqQ7edrFO/WSxDuI0iEInJph5MlhZiRAQLeeHVhhMEFtfW2lkLUhtF/KN
*/