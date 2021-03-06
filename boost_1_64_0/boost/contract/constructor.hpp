
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
B5AJJrteICIRM26B44pRfgTuYNT1MAQen5j5yBBJAryBojkvpnXy5RbGt+MFWe7aGB1PjDp9VIl3d0y28dgFHVG39Ad2wijErZ5IpS38b6Uz5z7y8weA0+G5sAl30hS8L6bt556zerniYsiECyjM/721hohdt+1ntFGD4LqC5kE9OPyUy94ZnVnqk2gg22/Lu800r9+5W86AsnmI8OIXMnVf5LXDPhWLB16ygKWCSKdZ2q/AeS66xoO4FmPltUJcYEwtOlnsiwDuGaU00pW6dFaQPGNrhJ1VUcyek6UFulTYBfIEoqeVyDYEa8j+Qg57Tl614FNcdM7PYay/1pB7KAeCvRf8uDtSTfgbo6UBPW5z2Ph8r2M71pBET6iTStwIU0P/NqNd+6+KYRNZWPokxGudlasULYmggbl5zHDU5KlCkQKnanTYUvGwAgtTaW3/MDf/hhdj1XSZaUQCT1/bbhZPUXjyHD1Eul6oj2qTW3yVK5IH47TterCwF56KIe2MeQHaRkVGrGznMPv2lt3R1fUYaoNoMNVoaUWcki5P018+k/dXn9vuKYQFAw==
*/