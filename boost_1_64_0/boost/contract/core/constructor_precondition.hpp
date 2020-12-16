
#ifndef BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION_HPP_
#define BOOST_CONTRACT_CONSTRUCTOR_PRECONDITION_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

/** @file
Program preconditions for constructors.
*/

// IMPORTANT: Included by contract_macro.hpp so must #if-guard all its includes.
#include <boost/contract/core/config.hpp>
#ifndef BOOST_CONTRACT_NO_PRECONDITIONS
    #include <boost/contract/core/exception.hpp>
    #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
        #include <boost/contract/detail/checking.hpp>
    #endif
#endif

namespace boost { namespace contract {

/**
Program preconditions for constructors.

This class must be the very first base of the class declaring the
constructor for which preconditions are programmed (that way constructor
arguments can be checked by preconditions even before they are used to
initialize other base classes):

@code
    class u
        #define BASES private boost::contract::constructor_precondition<u>, \
                public b
        : BASES
    {
        friend class boost::contract::access;

        typedef BOOST_CONTRACT_BASE_TYPES(BASES) base_types;
        #undef BASES

    public:
        explicit u(unsigned x) :
            boost::contract::constructor_precondition<u>([&] {
                BOOST_CONTRACT_ASSERT(x != 0);
                ...
            }),
            b(1.0 / float(x))
        {
            ...
        }

        ...
    };
@endcode

User-defined classes should inherit privately from this class (to not alter the
public interface of user-defined classes).
In addition, this class should never be declared as a virtual base (because
virtual bases are initialized only once across the entire inheritance hierarchy
preventing preconditions of other base classes from being checked).

This class cannot be used this way in a @c union because unions cannot have base
classes in C++.
Instead, this class is used in a @c union to declare a local object within the
constructor definition just before @RefFunc{boost::contract::constructor} is
used (see @RefSect{extras.unions, Unions}).

@see @RefSect{tutorial.constructors, Constructors}

@tparam Class   The class type of the constructor for which preconditions are
                being programmed.
*/
template<class Class>
class constructor_precondition { // Copyable (has no data).
public:
    /**
    Construct this object without specifying constructor preconditions.

    This is implicitly called for those constructors of the contracted class
    that do not specify preconditions.
    
    @note   The implementation of this library is optimized so that calling this
            default constructor should amount to negligible compile-time and
            run-time overheads (likely to be optimized away completely by most
            compilers).
    */
    constructor_precondition() {}

    /**
    Construct this object specifying constructor preconditions.

    @param f    Nullary functor called by this library to check constructor
                preconditions @c f().
                Assertions within this functor call are usually programmed
                using @RefMacro{BOOST_CONTRACT_ASSERT}, but any exception thrown
                by a call to this functor indicates a contract failure (and will
                result in this library calling
                @RefFunc{boost::contract::precondition_failure}).
                This functor should capture variables by (constant) value, or
                better by (constant) reference to avoid extra copies.
    */
    template<typename F>
    explicit constructor_precondition(F const& f) {
        #ifndef BOOST_CONTRACT_NO_PRECONDITIONS
            try {
                #ifndef BOOST_CONTRACT_ALL_DISABLE_NO_ASSERTION
                    if(boost::contract::detail::checking::already()) return;
                    #ifndef BOOST_CONTRACT_PRECONDITIONS_DISABLE_NO_ASSERTION
                        boost::contract::detail::checking k;
                    #endif
                #endif
                f();
            } catch(...) { precondition_failure(from_constructor); }
        #endif
    }

    // Default copy operations (so user's derived classes can be copied, etc.).
};

} } // namespace

#endif // #include guard


/* constructor_precondition.hpp
H9rLScZvPAJzBdqfxLskp4N/433KoEfCsTwTpolMoMdTge7+fQNaS/cF0LfDXyTyuDzzmwQiL+FY3pfL/PBV42UefgLsu5w2/H3zs0z8mdOEHuRH+nNA7nk58nee6lzyp/MimkfU+fkmj44O83gB4fEM6l0lYftYadqhr0F9fV7K+MNmHH+x+LbXYL/cpca3XWZ82+Uqp+AIDv0lmmcC3bizXAdQe3lwWXBPQvl4XzdXGbrJQIf3ln4T0ntS+CkfnncyfM6ZGeZz4kd9PtsMXY1Jr1Lkug7TEzrF8x3zhs8Zhs+ppT6fG6WfUS5zKhhn+1yjkxI/zncN748Z3jNFxptQRqYTvMh4i6Q9KiLt75u0R0nat0mc/gnD4/zQxCEajvMj00/JVta3G7psZfQTQ5etjO4ydNnK4GeGLpve7zZ02fT+S0OXTZf3Grps+rtP2wnRc7ncNazjHo2Dc4UPaNlDHKz3Dxl8y0fD+F+bNCvzSPNRw7PSpPmYwTv9I/4JK7Pxp08Z/JOmPX3ayDwzD5l/Z3jGjUy/N3h79/QfDH6UkfmPBt9vxpUvqMxsA/mV7YumD2bL9i8Gb8v25VCa+ZXtK4anLdt/GLwt2x0Gb8v2NYO3ZfvvkMz5le1/DE9btm8avC3btwzelu07Bm/L9j0ztn3XvOs3QGrB8KsFOz0TsXpe9UHxxcsWLofdbQjOrPUXVg/3z6MIhnqiMPuXomr0Q9npRldD2PQ9HazY6Gf3au43sCzab9izGvsNRE9h7Dd8mMKME56ov7HVkp7E0z4FpcvpjauGsQ6MEd3aWYkZI04gWifPU2Nh37+c+d6bcJiPUuBLOGdzzE91hHwnVaOd+jq5pDy3nU5W/Uv6+M4hnvmeavJXLj89645ylIEckn/SBdNT3Gg5plMcPBNG0XZI35DiRs+zfbQ6PPeyO8XB8IcojO8I/EHukppVDes0bJ+5y2s20QNtzrzPUX0K7fhJ4fx2Srs/19DtZ9rzT4/z6WpM/cjGr9bQZeM3T+1Y0u00fuljUHbSzrGvG8hhQwdRHL7zEeLoWDJ33DHexyE9iJszvU+YPLi8YR4+qXjRhc1jfaie5JfHRs0jx9m1PDaF0ssvj4eZPNg8Lga82IXaA+MPJ7zWnz0nab1GW6B5L6KR+zIkH0on9U3gRA+8R3vLje1unRHOQ4X0RY8wNpmNrs3kZXIpjq/ovdBhNrLz9ndVSOf5xVmjcsh7WpeWh3X+KdUp42XexfikY4xu3Jga03pexoxxo5tsdAlj63YepwNkQt+q+uP9UOC/0mN9mdNw5zr6r3XaBgotjue7h/Hhn02T+awnWizDNXuLnEYGlLMP41B6lxRj2J/XtjwenRLW/2A1jIfMvd8ONnGc/8M4Q1AWQGPoCr1Nga5Ffjg/K7y2AE35+EDPmN6ngWZmFprPgEyu7/jYjOCH7fJntbyEDvszn4N0kAeecf+8lim8QTSU5Y3R06plPk/1DzaUlh/O550O6Z8Ivh3zeabat9AMmfWBLxkevk7NOX1DMzOC5hxTT6JkOQ90AfJG9rXON/2hXLQXGPkqxw2X7yKiOTa0d34z9avdfnFvh4HRoRc8Y9DfkU6mvSCc6kx1B/FKfJo0va/G5xBI3qKvV+/aOQS3novnEC6uDs4h6Pn7S6pxPWNgfQfdcEbbzNfpql0Iku0OnDziuf7bZdJ/W5J7vNJyeGMbRW2rX9jUUH8Yc8uC03cxha/e43w554mSFn1zu+nu0CaQrpX6bWKqS6AM21rNsMTaZMrLVgZX5lkG87OUwVVQBi58Rwnfe8A3wDnZ9LzkN6rxrFM426pjC+V3XDldzV+nO4alNqZ3j8MZq+4=
*/