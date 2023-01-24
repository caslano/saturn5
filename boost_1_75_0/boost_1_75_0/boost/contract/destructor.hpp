
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
7zRsVpprn/9Rhv1jeFfhfYgOeGkxNvT2EyJY32luYAsSUVv4dopM0PgxrJe4gkRUhf9CY87Tmumi2W0y4VvhX9L6ndLrhvgT6Vx3TBXRplyLQGA03y+1JB/kSKWoZhW2qikyzYMPbS5dXyFEYw2sra01fyfN6jpFSocJfdrHqhVwi48fV9fcL6uK8sYNrl67xosvv8zGxgaDwYC10YjxeMzG+lqYZlSHRLuTJ4+T5z2m0xl1XePxmKqmrCp0BAHrHP1+vzmu1d962Pu0GONWCoFQSqGUcoBUSgkhhM+yzJ4/f/7Zxx577MvAkGD+u86jcRo7++9aAl17c+k4bjsA2Dx7/NkjR8dfnR8s/ko+6CF1hi5Mk/mWeIB0jwrpcbJEWon0UVvJ2NwC2d7kPpTsaiWwTuFNMCdqW2FnEqUF9aTG7Hl8KRHChdp5b3GFIVcFviex8zCVR2hPGU32XAn6fQXG89zuRR58r2aDitmz7yEXBcLk1PMcPxuR+QLVd8xmdRgEKmi1MbSpvtAKeqP5aRjr8DsTEkYbomlg2bknIhGYuhX79HnMVGzzkKEZKQwdYBHhfMaIRbO5jEMxCdl3uqfJejn4EDY0i4r7Htji9PF+0LQdMzmZzUopNjY2Gi1qjKGu6+Y5hf5WNWsXALp/J9ehSXdeWWl7rTXeexaLBc45Dg4OeOPy5Ybd1zHB5+bePo88/CBra2usr98R
*/