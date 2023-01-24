/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_const_hpp
/*`
[section:ref_add_member_const add_member_const]
[heading Header]
``#include <boost/callable_traits/add_member_const.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_const_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_const,

        detail::fail_when_same<typename detail::traits<T>::add_member_const,
            detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_const,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_const,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_const_impl {};

    template<typename T>
    struct add_member_const_impl <T, typename std::is_same<
        add_member_const_t<T>, detail::dummy>::type>
    {
        using type = add_member_const_t<T>;
    };
}

//->

template<typename T>
struct add_member_const : detail::add_member_const_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->


/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member `const` qualifier to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_const_t<T>`]]
    [[`int()`]                          [`int() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_const.cpp]
[add_member_const]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CONST_HPP




/* add_member_const.hpp
+DPMl2LK/TSQoALE0w47+pbwnxWeAjJwfBYVwYdLOaP1MMwImqNOgxgxxAn6NIjKRuOUPJUdrEAmGncm8ioiH1gBxccuwV7Q/tJnEC7iUeAUKcrn8nZltAdn/fwePAl2zUT+pXC90ptw6k3yN8Fy/vPu0AA/7jy9t1oc9wCbgVvgPX6Kv6R06OdxP2IgcLtkxCsEYS2HEh2uqkACoAWPPAUSR7LPA6mAfC6rST3P3prxR22AWApIMRe/DclGKQErqKNsGPH4lQQebwewg0Sf1mKk9exTsQRb2EXuMQ/HlWqYeaY1ooOkKQNoAffSkcuC8Aaa8Zif7hKMKAp3cKQ1L/RAN9gw+REhIFP0g8RSkMrKPeYUqCDu1JQdBmXdYT2/Bk3Qiu0Z2rMbTZGe3fg3A+Gb3eVvBnp988+uQWwkRZXBvp88EeH7yYquQYgoEsd3gKx0MxMqtPMgyvNQx+dhZIAGDD92CvKalLYec+9uwZoJVXdR+j9ulpCYb/snHNe8i9C+i/B+V6fTvOO9pQ2V8spd1xVX7mIOf+zdwq6+NAEVL8wugNuloY2aRyC3QDhRBFOfXMybc9oUvhhJw2lTu8VRIArZ3U/lhygrpUCnWYSJRsxIxX7WzPRAnoIowIyjMv0HfmDA3inEKljubKR2zJHeY7Zo31nUd7UhcmZJVqiQA0a2jmyDh8ibYP9HAaV0SsRkdZOi7eKcWMVG
*/