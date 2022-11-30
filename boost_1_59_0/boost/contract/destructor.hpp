
#ifndef BOOST_CONTRACT_DESTRUCTOR_HPP_
#define BOOST_CONTRACT_DESTRUCTOR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for destructors.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/specify.hpp>
#include <boost/contract/core/access.hpp>
#if     !defined(BOOST_CONTRACT_NO_DESTRUCTORS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
         defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/operation/destructor.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for destructors.

This is used to specify postconditions, exception guarantees, old value copies
at body, and check class invariants for destructors (destructors cannot have
preconditions, see
@RefSect{contract_programming_overview.destructor_calls, Destructor Calls}):

@code
class u {
    friend class boost::contract::access;

    void invariant() const { // Optional (as for static and volatile).
        BOOST_CONTRACT_ASSERT(...);
        ...
    }

public:
    ~u() {
        boost::contract::old_ptr<old_type> old_var;
        boost::contract::check c = boost::contract::destructor(this)
            // No `.precondition` (destructors have no preconditions).
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

        ... // Destructor body.
    }
    
    ...
};
@endcode

For optimization, this can be omitted for destructors that do not have
postconditions and exception guarantees, within classes that have no invariants.

@see @RefSect{tutorial.destructors, Destructors}

@param obj  The object @c this from the scope of the enclosing destructor
            declaring the contract.
            (Destructors check all class invariants, including static and
            volatile invariants, see @RefSect{tutorial.class_invariants,
            Class Invariants} and
            @RefSect{extras.volatile_public_functions,
            Volatile Public Functions}).

@tparam Class   The type of the class containing the destructor declaring the
                contract.
                (Usually this template parameter is automatically deduced by C++
                and it does not need to be explicitly specified by programmers.)

@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::check} declared explicitly (i.e., without
        using C++11 @c auto declarations) and locally just before the code of
        the destructor body (otherwise this library will generate a run-time
        error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
*/
template<class Class>
specify_old_postcondition_except<> destructor(Class* obj) {
    // Must #if also on ..._PRECONDITIONS here because specify_... is generic.
    #if     !defined(BOOST_CONTRACT_NO_DESTRUCTORS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
             defined(BOOST_CONTRACT_STATIC_LINK)
        return specify_old_postcondition_except<>(
                new boost::contract::detail::destructor<Class>(obj));
    #else
        return specify_old_postcondition_except<>();
    #endif
}

} } // namespace

#endif // #include guard


/* destructor.hpp
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
*/