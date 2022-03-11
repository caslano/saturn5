
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