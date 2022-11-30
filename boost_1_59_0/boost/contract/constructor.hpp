
#ifndef BOOST_CONTRACT_CONSTRUCTOR_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program contracts for constructors.
*/

#include <boost/contract/core/config.hpp>
#include <boost/contract/core/specify.hpp>
#include <boost/contract/core/access.hpp>
#include <boost/contract/core/constructor_precondition.hpp>
#if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
        !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
         defined(BOOST_CONTRACT_STATIC_LINK)
    #include <boost/contract/detail/operation/constructor.hpp>
#endif

namespace boost { namespace contract {

/**
Program contracts for constructors.

This is used to specify postconditions, exception guarantees, old value copies
at body, and check class invariants for constructors (see
@RefClass{boost::contract::constructor_precondition} to specify preconditions
for constructors):

@code
class u {
    friend class boost::contract:access;

    void invariant() const { // Optional (as for static and volatile).
        BOOST_CONTRACT_ASSERT(...);
        ...
    }

public:
    u(...) {
        boost::contract::old_ptr<old_type> old_var;
        boost::contract::check c = boost::contract::constructor(this)
            // No `.precondition` (use `constructor_precondition` instead).
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

        ... // Constructor body.
    }

    ...
};
@endcode

For optimization, this can be omitted for constructors that do not have
postconditions and exception guarantees, within classes that have no invariants.

@see @RefSect{tutorial.constructors, Constructors}
    
@param obj  The object @c this from the scope of the enclosing constructor
            declaring the contract.
            (Constructors check all class invariants, including static and
            volatile invariants, see @RefSect{tutorial.class_invariants,
            Class Invariants} and
            @RefSect{extras.volatile_public_functions,
            Volatile Public Functions}).

@tparam Class   The type of the class containing the constructor declaring the
                contract.
                (Usually this template parameter is automatically deduced by C++
                and it does not need to be explicitly specified by programmers.)

@return The result of this function must be assigned to a variable of type
        @RefClass{boost::contract::check} declared explicitly (i.e., without
        using C++11 @c auto declarations) and locally just before the code of
        the constructor body (otherwise this library will generate a run-time
        error, see @RefMacro{BOOST_CONTRACT_ON_MISSING_CHECK_DECL}).
*/
template<class Class>
specify_old_postcondition_except<> constructor(Class* obj) {
    // Must #if also on ..._PRECONDITIONS here because specify_... is generic.
    #if     !defined(BOOST_CONTRACT_NO_CONSTRUCTORS) || \
            !defined(BOOST_CONTRACT_NO_PRECONDITIONS) || \
             defined(BOOST_CONTRACT_STATIC_LINK)
        return specify_old_postcondition_except<>(
                new boost::contract::detail::constructor<Class>(obj));
    #else
        return specify_old_postcondition_except<>();
    #endif
}

} } // namespace

#endif // #include guard


/* constructor.hpp
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
*/