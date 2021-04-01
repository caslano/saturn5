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
w1k+YG657UxByf+7sOrFbByp3SPa6Rs/0BbYJkPXWsnkenc5IZ9rOGuswCOoP7KzCQPUM0Pq9zIphanuDg/CF1vfhA7pwdPoU79qPKUHClSPZWg0GL8MgdSV2kd3GB9u9chhYehLE2Tt5yCEH2ndGQ2tE4XUYxyoNocUFW38g0d1lT+Y+Ku+nnMsTQdeatibwDzvEUMQaYQ5SN7m5iOxM4InQuQwmDO65QQ++ScG1XzpkP3+bTiI2IJPSHSbHMiyK1lMhOO+F8NG3Qq8ObPayzvC10eWNuVbPyuiosXwvXpN+ff59QWMyHS3XZirqR85867CuzANm56zFwJkLeM4Yq+K1cxgy1YbfCbqzb7XKv8wylXds8DqZmCPPOb8xbuc7m8SSaU+lrAcOBXLmZwUDiHVlwwTCNwjop39qSztUBchow8YgbgC4f/30qqnZSwa0IiXGEuCi3gq3MEV6cMuGYPKem2+JC2zX3trd4J41cDBTCWwSbbyZmnbF4hcYTfJ1qkqA1Zcr5gUux5RdAuSAwg0JOM4XI2vUMZRW5m3QD78T5/SFNeni8h0xQ==
*/