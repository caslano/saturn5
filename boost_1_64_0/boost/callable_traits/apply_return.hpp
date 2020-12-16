/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_APPLY_RETURN_HPP
#define BOOST_CLBL_TRTS_APPLY_RETURN_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

BOOST_CLBL_TRTS_DEFINE_SFINAE_ERROR_ORIGIN(apply_return)
BOOST_CLBL_TRTS_SFINAE_MSG(apply_return, invalid_types_for_apply_return)

namespace detail {

    template<typename T, typename R>
    struct apply_return_helper {
        using type = typename detail::traits<T>::template apply_return<R>;
    };

    //special case
    template<typename... Args, typename R>
    struct apply_return_helper<std::tuple<Args...>, R> {
        using type = R(Args...);
    };
}

//[ apply_return_hpp
/*`
[section:ref_apply_return apply_return]
[heading Header]
``#include <boost/callable_traits/apply_return.hpp>``
[heading Definition]
*/

template<typename T, typename R>
using apply_return_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::apply_return_helper<T, R>::type,
        invalid_types_for_apply_return>;

namespace detail {

    template<typename T, typename R, typename = std::false_type>
    struct apply_return_impl {};

    template<typename T, typename R>
    struct apply_return_impl <T, R, typename std::is_same<
        apply_return_t<T, R>, detail::dummy>::type>
    {
        using type = apply_return_t<T, R>;
    };
}
    //->

template<typename T, typename R>
struct apply_return : detail::apply_return_impl<T, R> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must one of the following:
  * `std::tuple` template instantiation
  * function
  * function pointer
  * function reference
  * member function pointer
  * member data pointer
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* When `T` is `std::tuple<Args...>`, the aliased type is `R(Args...)`.
* When `T` is a function, function pointer, function reference, or member function pointer, the aliased type's return type is `R`, but is otherwise identical to `T`.
* When `T` is a member data pointer of class `foo` to a `U` type (such that `T` is `U foo::*`), the aliased type is `R foo::*`.

[heading Input/Output Examples]
[table
    [[`T`]                              [`apply_return_t<T, float>`]]
    [[`std::tuple<int, int>`]           [`float(int, int)`]]
    [[`int()`]                          [`float()`]]
    [[`int (&)()`]                      [`float(&)()`]]
    [[`int (*)()`]                      [`float(*)()`]]
    [[`int (*)(...)`]                   [`float(*)()`]]
    [[`int(foo::*)()`]                  [`float(foo::*)()`]]
    [[`int(foo::*)() &`]                [`float(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`float(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`float(foo::*)() const`]]
    [[`int(foo::*)() transaction_safe`] [`float(foo::*)() transaction_safe`]]
    [[`int foo::*`]                     [`float foo::*`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (*const)()`]                 [(substitution failure)]]
]

[heading Example Program]
[/import ../example/apply_return.cpp]
[apply_return]
[endsect]
*/
//]
#endif

/* apply_return.hpp
Xwv50mDTy2gh3IdtentaSO96m15WC/59zaaX04Leapve8RbC/YJNr64FvctsehUthHutTa+pBb2u9nBb0Cux518L5fGUPX4tpOMie760UA8et6ejhXBXuGz+taCXb9NraCHcpTa9+hbyZbs9fi349yt7/rXgX6VNr8FZz+zhMNPSsS6wVfXawImqV0s6zoHbYEf4GdgZfh52h1+AW+AN9nzZ4hxutb3fbSF+S+zl24Jef5teYwv5N1X1dpjxCH63VM9+Bmk34pcIe8Jk2Av2gn3gBXA4nAbT4Ww4GmbB82AOHAjL4fmwGo6CW1RvG+wNPyvmYHwsrW+l4fHRvQg66N4EifBWmAx3wTR4GzwPfhkOhl+C4+BdcLraz4F3wCx4J7wU7oZ5qrda9fQsUX0HIy0aH/tZolfqngGbNT5bYE9Yp2e1Xq3+7DPvNaRR/UmEt6s/h9SfZ9WfH8Au8IewGzwM+8EfwaHwx3AMfA5mwhfhLPgSnAePwEXwebgc/hTmwJ/BVfAovELNW9T9VnX/LlwWeNaGmRJfBM7V+KZrfEdofEfCVHiBpnsUHAJHwwlwLLwQjoO3k4EHLvNaryDu5V5rCLIY2YTsQ44gx5EUFltNRAqQeuRR5HUk/nLOC0QWI9uQ/UgTEr/Sa2UgBcgO5FHkGJKQ7bXGIUXILuQgcgIZmIMfyDZkP/IW0jnXa2UiJcgu5BDCvg9mr4eUP/xv7vHQ2nNaA/s87EiN/Y/f64EzV09vv4cIZ6xWxMWafR/2cT9lKm6zPZHOWm1xDwj2DAnuA4Gf2/ibPURC94P4mPeCOJ4a+7HuB8EZqR/LnhBhZ6BGPP+UPVjOeH+IU52BmgPD94ngrNPT3iuiETlBP9I9j74FKUFuQg4gryBWvtfqhyxG6pC9yCHkBJJSQJ+GVCN7kMPISSStkH4JqUX2IIeQ95F+q9hTAilCdiIHkFeQdqu91ihkGVKL7EIakSbkfaRzEX0qMrMouhdF9Ipe0St6Ra/oFb2iV/SKXvbrE//+Pzdf/pGP/8/C+f+/S7bMutsSPf8vT9fDrEA292TstULXUU2Zlj1t8bLsfGJWVlPhX/cj+8znV9fa5jHfFf35Oh8dcJ9opTKv6UHv94TZNtEup147EtgzmvCYd5LwQtYM74jxKz+AdEL2Ip9DN2dtWNzLKzZwyxb38prq4H7W6OscLOa5mOvE/FnfKilxs0PcFJeZNZXGTQ+z7mmzmL/AiiuX2UedXC0JuOkI7xOdTpgv6+iL+jHy5A/Jrc0HibuZ490hdsQtLG/m6hmIkyVvoJZrRmVo3qzigxZuOZbrUtEfoHkVcJ9k1i1sFrPLzF+/nexfF5Sb0Np0Sbih37hqGtzqyGe8Fd36sDTIeQisGy5ifSG+REwLcVd37lOuA/TFq12EeI3UeFVrhAq1zWQj29HdExavssL1Ji6WxiVR8/X7onuhNcSWd9nEynWaeWePz0AmKIT42xUmw6sIM60qGJ8ZxXzW2bycTXxmie6fqfPxml8B9+eLm7Q2oe1mjrnf37SbGWL+kDbQVtZw9BU3FThiRa26yzLu+oq7pZinidntSrW3HUZJ7GtmtovOdPK7j9q5rBfFbjir2Xo7trkK0YkVcxLmKjE/oXnub3/vJJ95fxRoh+SPts3gvvx9xU7TH1ZmDbpw9Q4XevDTcKevDlUHy2xWmazTcKrPqsvaPu2DnhNznit4HgxrnG1t+bDcX+7S8lP3Q/xlFbbuO0nL9FnRedgaSplO1vVKWcbt+Vr2Lus9MY9xtbXSXD7/ftRR4iuNMuDfTNw9LXo7rHT8W2R11vUy6h/+i57xb4grhhnaUuu7kgevJUo/XFpREnY=
*/