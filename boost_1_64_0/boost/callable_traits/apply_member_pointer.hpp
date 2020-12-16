/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_APPLY_MEMBER_POINTER_HPP
#define BOOST_CLBL_TRTS_APPLY_MEMBER_POINTER_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(apply_member_pointer)
BOOST_CLBL_TRTS_SFINAE_MSG(apply_member_pointer, members_cannot_have_a_type_of_void)
BOOST_CLBL_TRTS_SFINAE_MSG(apply_member_pointer, second_template_argument_must_be_a_class_or_struct)

namespace detail {

    template<typename T, typename C, bool = std::is_class<C>::value>
    struct make_member_pointer;

    template<typename T, typename C>
    struct make_member_pointer<T, C, true> {
        using type = typename std::remove_reference<T>::type C::*;
    };

    template<typename C>
    struct make_member_pointer<void, C, true> {
        using type = invalid_type;
    };

    template<typename T, typename C>
    struct make_member_pointer<T, C, false> {
        using type = error_type<T>;
    };

    template<typename T, typename C>
    using make_member_pointer_t = typename make_member_pointer<T, C>::type;
}

//[ apply_member_pointer_hpp
/*`
[section:ref_apply_member_pointer apply_member_pointer]
[heading Header]
``#include <boost/callable_traits/apply_member_pointer.hpp>``
[heading Definition]
*/

template<typename T, typename C>
using apply_member_pointer_t = //see below
//<-
    detail::sfinae_try<
        detail::fallback_if_invalid<
            typename detail::traits<T>::template apply_member_pointer<C>,
            typename detail::make_member_pointer<T, C>::type>,

        detail::fail_when_same<void, T, members_cannot_have_a_type_of_void>,

        detail::fail_if<!std::is_class<C>::value,
            second_template_argument_must_be_a_class_or_struct> >;

namespace detail {

    template<typename T, typename C, typename = std::false_type>
    struct apply_member_pointer_impl {};

    template<typename T, typename C>
    struct apply_member_pointer_impl <T, C, typename std::is_same<
        apply_member_pointer_t<T, C>, detail::dummy>::type>
    {
        using type = apply_member_pointer_t<T, C>;
    };
}

//->

template<typename T, typename C>
struct apply_member_pointer : detail::apply_member_pointer_impl<T, C> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` may be any type except `void`
* `C` must be a user-defined type

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* When `T` is a function, function pointer (unqualified), or function reference, then the aliased type is a member function pointer of `C` with the same parameters and return type.
* When `T` is a member function pointer (unqualified)  of any type, the aliased type is a member function pointer of `C` with the same parameters and return type.
* Otherwise, the aliased type is a member data pointer equivalent to `std::remove_reference_t<T> C::*`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`apply_member_pointer_t<T, foo>`]]
    [[`int()`]                          [`int(foo::*)()`]]
    [[`int (&)()`]                      [`int(foo::*)()`]]
    [[`int (*)()`]                      [`int(foo::*)()`]]
    [[`int(bar::*)()`]                  [`int(foo::*)()`]]
    [[`int(bar::*)() &`]                [`int(foo::*)() &`]]
    [[`int(bar::*)() &&`]               [`int(foo::*)() &&`]]
    [[`int(bar::*)() const`]            [`int(foo::*)() const`]]
    [[`int(bar::*)() transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int bar::*`]                     [`int foo::*`]]
    [[`int`]                            [`int foo::*`]]
    [[`int &`]                          [`int foo::*`]]
    [[`const int &`]                    [`const int foo::*`]]
    [[`int (*const)()`]                 [`int (*const foo::*)()`]]
    [[`void`]                           [(substitution failure)]]
]

[heading Example Program]
[import ../example/apply_member_pointer.cpp]
[apply_member_pointer]
[endsect]
*/
//]
#endif

/* apply_member_pointer.hpp
h8MOcajXODj8eLYqD44scM77zHMih592ZVj4Z9DG92Q6h/uoQ7jpGm7wRaP14eZMc+5bJp7rUMc3SriOD6StCf/IHOf2vd8h/HptY6E/kK0LN+ES5z4tvUPkcDM0v+0/uGdSxxojhD1b03zAIew9WsdbfshqZVtb5Fz24xIixyNL88DpYaY1ZVC31Dn8Aw7h55jwzYPvmYe/0Lm/m9gxcvjHTTk4Piy26rmiYYnzc8UBhzjURYwDiW/lb2vGghbKPzFy2BWa/5EfrltX/9KWOOf/ow7hN2n4ji+3rc2Duc79wLhODvmvcYj0MtWasj++0Pm37oBD2Hu072v2YH4G5d+0rIX639mh/E3dc36xbk0eVMx3roOPOsThuPn9MS8zZ9wHVCxrofy7ONRBLYPwAaDW1r202c3DHqNh39/FIe3Nwm5dmzsy2/n3tl+Sw/ub5nfYwFirfvPqZzmX816HcOu1nUV88W9tP7vY+fmqe7JDOQfTfcb1q35qhDam4e5xCHePpttxAKaV9ayuhd/5tBSHMtc4OAyGtarsm+Y7t7GTXf0Otur3GFuQ2l6+PyT8sIHRwrL88oLCwHdJm+QblIqCwkrzLYa6GyjfoMyX+2sK1+SWrLaC36moTi/xI0N0ataU6v0sc39C8DsW/Nggn97pN15GZ4v48WfJhfI1qMh3g2kav6Lusgq5RNyRJbWwr7jLkfuD5MyRwny+/hB342zfG16b4M/fZaf4hiQHbpJvYCQf5BuYIguz2GnaVbcCZoi9pFd0a833MppG1U2DpAt7f7oSVZc0+XRL7N/gkA7sJB0h/Ul1qkPdCi/b0/vtmh3y3jLHuT0fcwi3Ueu0Dtie0XjEkSzn57Wibg59toYbYdC8Ve2o7mLnNDc5hN24MTTsM3lOtCK032Ga5j09/A6uRzogn0VqkknzBnMuTz5DJ7a2xFtqpfQmcl5SoqW6+NDHypN28WV/u16XW0IcpM0Gdcby1cUlfCWQKPYuK0vS18+K1e/SdotbSZ+4zbK5vRCdFdI3YG9zG2e1D5yfJH7EtvH5UVibW7nanLUVI7qbrEn8uxbRb4rV78TwM7rMOV4dxF22NZgQEmnbsdybSJ87CZmccurzuHxtNN20UZN3pu2RV9hLXpnvj3eLHXlg+y6UNGEnaZLyG6nlVyFx5tsILb/VWn7WZlN+a3IriynEFstQ9RdzBstwyZtETHliFxdeplp2ATeXBtxgZ9yEl6WWWXM3WUE3TmUobhdEcLsgzO1MdftkT+m3SbZlyj9R9C6zUvh3HJJEWbrRcnWiT6UcpyCeTv/+8jypgQ/U39O+Wp4Nm0x5VhaucWyTWnYB/S6mLH8sZm94WWq5BfR7qtnoh5ejlpnRV7PRdypDLS+7O8xh7mbafj/vTTz1N5gfd1mkkPnyLbuWxVYti7Rg36gtq8WyQD+0LO4Us9epXal+Db1kby0P48apXambtcZNVtBNi33jAuN2lbi9lBzQsjHu7W0rRvqbymIJW5/ZRoveElZt9NfnuND4PuFvj9W4wuxvj5lyP03uf1/uV6yX++rn5+R+B3871frQo7O/nfbu+O+vG4f147ZMrRsXat1ICLbTqtOpG379nqZuzG65nap+XzWjf4p2qvpqRv8026m6U3Oou5nB/Rm49FtqLddBopemv5XBckv6N5bZCewORb/JNt9k3ynfRnsfihvXc9G2HY+c2DrT8/Ilz/13fXudZum8NGyn3z66YGetUNNphAG9xhb05gf1mO911osxelxXOurRg9r8c9bDHNRraiHcJHv8WkjHBJteQgvhHrds6djkrDfYplffgl6O0UNaCPc9m156C3q/s+ffRic9aI8=
*/