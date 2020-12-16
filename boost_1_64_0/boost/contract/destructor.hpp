
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
ph4KXFhxRQ+7U1j9BclJ5Wltcqi3B8EXD2C+eSBl6eQaUZldPkVGrpGSh1GCyzJKHkZXCj7IOIbC6fmkSu57c/1ya7kpL3tOr5hwmL/gW583Vvh7UI6fGLsaT3ETRA6Si9PtDXQdTG1rZ4mPVOLcpMxrAr7DQ/wywFe5+D15sPcKo89Jkh9MFzX5dXDU92SI3zkkforoY9+Q8thP8LE8vqD0xNdZeaZR/DzxIT7M39d1yUj2H7IWpfsfknL3jPpj/71I9cXTK0P2PSyuq1/kpqPYHA2MLJHfIoX2w86VqbwkD+dnluZHcFxatJfZleJPRP/YJs+V8APcT+L5Zw7nmzHnUD1zKOPGp4sy8T8w7V/JqMz4Z3K0h88YWReqjRn+BRDGcftUHrdDOA/Ccua+fgdt1sqVMjcYHM3IFZn2E0vF1pCXNzzzbcBqzw+XmnBPgZwrlLArUw1fKXa3nO0m3tsbC9b46glWzbB1fevXB2/3riD4MQyXMZ+mz1OYEBH8BkeH4+S9U8G/k2GdHd0CS3GRpBI9YN/5Q9YlUqlEF4/fZE/nV8DGhw9xNDI6kgDo702cHafjve6mvWoy7csqqAt816x5d+4g48uXij07OnYcVSrpcd7oq9omQXyZeffsEPGDzi7UD8aM3IeJHGtGy35tkPvAShtP+9WhDUnJbz7FpQr0L/YTCrw40DPxTK+tUsZNuejoXnWjr7WjIV7k5n2Ixs8fls4D3EUkuAmD20XhHsGlvDPuRqMPpwfUR1LLAcrZjiX6Kn1fcaDssX5+D2+76v9AYzebK3OdJWo4cGHjtKpY4/zFNQvmpx8Js1A9h7u1MijzIyuDteRtJs9fr6Sf0c9Rop+jBVfGQSxfrazrfaOyv/W0REuyx90ZT0v9G/toH4NKa+HBmO5bgV3yt8r+bWOvx4msx1b68hwvsp4geEtzy5Ps6G7rdKyTPYnuZBxlsnGBHk8CWU4GPZ5i9HhqJf2MHr8jsp0W9I+Innm/yJT/mZLmLEjzG+lTLc6ZNxHcPXER3IGXFYH+62wjxzlGjnNFju8L3tycvHmDCLJFmJYv2SOsQxreFwjv86VMfyi8f6R4bAdwDsLo/qJK+hndXyw0LjG8zjf5/IngXQb29wMo8yuA75WG708r3c/MvQm9qwQ3xz73xkZVEesMwqKvHxi5rzFyXyt8rgMdXQ15uBrycIOhdaPQul70/UuhdROkPxvS3wI6uNXo4LZK+hkd3C707gDZ/lIU0LjT0Lirkn6Gxt1C49dA4waQ4zeGxm8r6Wdo/E5o3As0rjC6uE/SXCO6+IOkuR/S3GLS/FHSnCNp/iRpHjR4x5oye1jwHjF41xu8xwTvcZDhZJPmCUlzhsjwpKR5yow9tE9n18qeFvxnjB6fpfBQ01d5jmA6l1HKsJTMDWm40wHSb5a/QPj5O7yrknq0cm03dbASdItryzp5+xx1MXt8zvv1NvXEavg1k9jC1Gb1Phaq/uclySeeBXh2J2/7LRlzXtSf5dPU0M9kWGL9eoDRXZpdPQZvN4Z1d2begx9nSRA2yq3L9eK8WUtC3xt6mWSM8H25s9JrLK8QLEoyKP9z9iQFFxAvWUPZhQroVez37rJu1owY77/zFRIE+9lz238a3p9s7O9lM377O/SDOB/41rLY3BvGzv8u4Zehz6vrI0gj+ywLFRynhTtYRnjbf/6ZylL0r+UoeyppLz6UYyI997nbKCoz2feZeUajN077JrlwER714fFuofcOyT3VyQFrYO9C+TWMIJvBsqAglgWeo3iAz1+E6+d9ohle1v3T5/3Qxoe4PGtZoA/5EHhk182edekulgRxf+9H0L58DH79E+OPPq0=
*/