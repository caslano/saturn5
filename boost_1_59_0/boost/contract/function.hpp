
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
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
*/