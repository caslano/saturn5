/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_const_hpp
/*`
[section:ref_remove_member_const remove_member_const]
[heading Header]
``#include <boost/callable_traits/remove_member_const.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_const_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_const,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_const_impl {};

    template<typename T>
    struct remove_member_const_impl <T, typename std::is_same<
        remove_member_const_t<T>, detail::dummy>::type>
    {
        using type = remove_member_const_t<T>;
    };
}

//->

template<typename T>
struct remove_member_const : detail::remove_member_const_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the member `const` qualifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_const_t<T>`]]
    [[`int() const`]                    [`int()`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() &`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)() volatile`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_const.cpp]
[remove_member_const]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_CONST_HPP

/* remove_member_const.hpp
0iAcPawp3R63B8ulgSwWyBuGQ6kWl9T4Xkn6LnrQjs4YnFVpWrpNlkRa0wjkU+GddYB577Y36OgIR7QY5WxPnLKNYOJjt6tRTzibeJUMHROjZ3axzgHELGMuE3Ifg0ySINAGAjFiMuHbgUjATbmvBdJ+SLfzfakNiBXIdMSs90HHCPNNIXnHeNS+35fevRNTSL5PYe8giW0bRhr/x0oEkO0P15STrikhTPoqX4fS1zHWxCQnNrFGeiVFkQOPSfpnSYFfw8XAjJdQarxGLjxbW/jAM96FBSzMevX+NDlN5BrcbsDKrn3Gy4DW/SWtAe0YGdB+7KPIlmOFnOmlrI1Qh9iKFShF8dDqGYtawxIM6jdPHAd44Cz1mENWknHyIpJL2F7gLOV9+uhFA24qeN8BSR4hoOeKcaTi/9zG42FfKYLwxyLfhJCMQO6Uclujpa4INy2bclujfDNlszbSPOMo+2PSWMZh9leKkeJJpWpo+WlyCGJn2hOayuf8HcVXUP6wmvpxP6kga6B/j0MiKEz9yICYVMGaOSzdkkUi2YfopVUz3DuPUsbHNb4ZH4cRQ+QZH9e8QPpOKfnFQqnP8go5zBWqBS+gdsy65azgjx6gR9CJo3LNo42DxRv0Ge0IzjCAvDaQOOlX7bGHhqUfcAQUnX80J/6r8V/LDDrroh2svAnWY3cTSf6YVIXOqtNK/urYWKc/XoadLqWOc/Wz
*/