/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP
#define BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ qualified_class_of_hpp
/*`
[section:ref_qualified_class_of qualified_class_of]
[heading Header]
``#include <boost/callable_traits/qualified_class_of.hpp>``
[heading Definition]
*/

template<typename T>
using qualified_class_of_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<detail::shallow_decay<T>>::invoke_type,
        type_is_not_a_member_pointer>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct qualified_class_of_impl {};

    template<typename T>
    struct qualified_class_of_impl <T, typename std::is_same<
        qualified_class_of_t<T>, detail::dummy>::type>
    {
        using type = qualified_class_of_t<T>;
    };
}

//->

template<typename T>
struct qualified_class_of : detail::qualified_class_of_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a member pointer

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* If `T` is a member function pointer, the aliased type is the parent class of the member, qualified according to the member qualifiers on `T`. If `T` does not have a member reference qualifier, then the aliased type will be an lvalue reference.
* If `T` is a member data pointer, the aliased type is equivalent to `ct::class_of<T> const &`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`qualified_class_of_t<T>`]]
    [[`void(foo::*)()`]                 [`foo &`]]
    [[`void(foo::* volatile)() const`]           [`foo const &`]]
    [[`void(foo::*)() &&`]              [`foo &&`]]
    [[`void(foo::*&)() volatile &&`]     [`foo volatile &&`]]
    [[`int foo::*`]                     [`foo const &`]]
    [[`const int foo::*`]               [`foo const &`]]
]

[heading Example Program]
[import ../example/qualified_class_of.cpp]
[qualified_class_of]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_QUALIFIED_class_of_HPP

/* qualified_class_of.hpp
AzLOm82mw1QIMTOVfSz0cQbvZSE91RKMSc+1VMYj4LZWTCQ3UPF3fZ0Bxgofax5+mX08IVLBUBMsm7KbNapI1Ez3VvX3dRN0N5zeOORgY66kE5p92N5IXaorVP/fKfavSl3VpKB+Nub+29WXIpdepM4oe4tZ5bGHTH4CuNbuo32/W8ko65Y33CLZCrJqdZb0vLtydt2w8s2/BWc0ljGUeXYwTEbOVylcIKCsRjMR0u6n67ct74w5AqjaH89h7BcHItb40qhinShSC69wId4V03E3yGwegFK3esVI24j6rqgN5et0o0twTMVkDI0LJD1badkrdt9VfqRxR0LDW4EL/uBpxOe78184/9dberLFSnPNolsaG63XZAuXRjIyArSqPazJHERO7ygB03vQNBj8W/pxxlk9Bqk1P2h7qp7i8rzV0aGzE28aDGBodibxk0FrZkrS/HDS0MMnEzj31tFOmwNc24Pe+gMkiSJSM6CI4frjhXiz7OZ4PeuaB2mgyuNJFhPGLlgZzUMa2NSey2hhojxtBgPgOMquLLCqWx0L0quXXiEFS3yhtDearg==
*/