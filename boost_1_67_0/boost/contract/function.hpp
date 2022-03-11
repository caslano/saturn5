
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