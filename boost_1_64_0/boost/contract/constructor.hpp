
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
7cxEySPcU82/88ZkjjEqREcUp/cXYzvDYfTZSsf67MlRGe8AHpbxFIgvj/o4GL+fyOHi7L7fclOO06Igo4SR1qzRMrYEWbAPY8eWMyV9kejkKrnfeX9ju86H2HzNiYqcEo976w+gMKbtM2cLvxT1x3eujZCnNblulUr6g2T9oNq2T9YntG6hBoROMiyvWR4j5yZmYcFsV/uJzfI8H/etCcH9kfZnQdR/Q6GLCZEdyphtIdhzBHiG8VNeWgbEi3/njMP+JJZpgVcjdXPLiKDeN+0ZfB8p8AUi/xKWp8tdGe4Ysk+uZdl74wpU/13Hbep6ulvHAXk9jce5SyFPxYPUo+SN8/T9cX5+MG9oX8uIT2h9HqAe+R5U6FOswLoNNt6g9qdnUkSnKwV/af8+ZUVDTX1j47JYYxMdYV4iwoTGiY9pima+/+i/BaHS04MV0i7O53LZ5N9VJLBGLhO+OV4O4QdvaBR7i9bSIKBuYWxZ3QIeJLwNdzJ005t5PiXFj2o7St2qYC6V10BpkBnjQ53Y35qdpr94GsKrA3gVtv217p0DeH9lFcne4GB0D9ACeb9kNdjSGihX7h/QuyubsXARXl2943o9ABp896zxVyQn6cfcPSs2sjYKa5bgtx0c8Q+hMNIbb+6ojomNLYa2e7l8ax3BetFMceui/l+sIy3YfpRlr0fEhc9aoY0ytxmZ28EnrzU++XChswTkrYXvOlO3OincRb9u+uHaUkLCq0Laq1WmveqlMNTV0LWUlGk/HzJjqk0m/nUTv9nE72Z0stXXSWET+JFtpr/0daOro5SmxDk4votwDMFwzf0weioB22VrW7b9O5bSrx5IPye2cFnN/PpVDbG6pprl4JjCEdJzB8dFg3Gz0weu8Tn9YfghCKuMGCb/oGHVF/clsJxPhXI+Psr9z6w53dNM3/VUCR8PdiQ6ExrmHTUKY3xEbU3fUQMZLhrF6/ZZMpxjbMXVN6Txfakjf4C2eH+Zt3Dl3cfz0dztS8//9snuN/7mKP/+twuiutcleM/gh9g3zu9tmYGXlARBLsczM+i3TxW/LDzap0GY+LRXQZjkbZ+O4UKvfQaGR3n1nRgu9urbNXzBePJ1IrfGf03W63TN6MIovoHaWDuf+1GaEQjnXDPqP++6b+sKtr1grHsRt50bdE6U+2cXY18mv6mG9mitXDgjPUOOgHT9OHOEP07T/v2l0dxv3vwkGqwBlcmahasTBxRa3J28y8V+roD6VwD2jbZXYOz7Z8Y27XuSPzfxdk3+GhNv3+C/TmQbBrJdn0O2nY1sNxra+Sb+JhP/gfHRt5j4V038bVp3oSw8uyYEbZubO0NfdSfE/cC0QXdD3Pkm7p4o3ivjz6POjWTPE/82mvkOPqGyvydeLNu9cM+Ig9m7VO4jGMaXmvj7Tfwe5i6VP5r4IhP/IMHw/aTHiv2ydvUF5x4fiQbrrZGCzH0lj2oZCF5K8LDtf5zgofW5fx/Asjxh+i+O/5PGjp6CsoI4ztPTKp/EFYTcr/qspKFyZnoToR12MFsuL0QxPrtc/mriHzHvKLxs4h838a+a+CdN/N9E3ldNG7wdwlhvHBzTv0Hpc+21LOf2J7lB/DqnL/Tn8jzFL/b6elKJVh4Dz5W1tn/ieHeA825qXymY4xhq7Gs7yxpiO59hjkjnn95hWZ0YSW+uzD+9m2OeL9W8DjIAMLHPt8U+te15n+m0rIP9KESvubeN76SQcwPAq9Doip44p+G4MMyO4Hzo3Ubqg9E3nTTO77fuEYX1CFOHPorSz9Shj7UOSTzOq3wa9XY4v7ojPeVVBn2jIfKt/IZSGPOQXynvhZn+doHBGyZ4exi8nQ3eLoK3a2U=
*/