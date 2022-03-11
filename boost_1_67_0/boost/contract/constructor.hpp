
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