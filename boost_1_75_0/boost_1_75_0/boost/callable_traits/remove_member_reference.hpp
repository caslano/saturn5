/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_reference_hpp
/*`
[section:ref_remove_member_reference remove_member_reference]
[heading Header]
``#include <boost/callable_traits/remove_member_reference.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_reference_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_reference,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_reference_impl {};

    template<typename T>
    struct remove_member_reference_impl <T, typename std::is_same<
        remove_member_reference_t<T>, detail::dummy>::type>
    {
        using type = remove_member_reference_t<T>;
    };
}

//->

template<typename T>
struct remove_member_reference
  : detail::remove_member_reference_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occuers if the constraints are violated.
* Removes member `&` or `&&` qualifiers from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_const_t<T>`]]
    [[`int() &`]                        [`int()`]]
    [[`int(foo::*)() &`]                [`int(foo::*)()`]]
    [[`int(foo::*)() const &`]          [`int(foo::*)() const`]]
    [[`int(foo::*)() const &&`]         [`int(foo::*)() const`]]
    [[`int(foo::*)()`]                  [`int(foo::*)()`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_reference.cpp]
[remove_member_reference]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_REFERENCE_HPP

/* remove_member_reference.hpp
Hv0bn40h/4Y9hvs3qqTfnyT/xks4V7ZqcDkk9CvXVh7XjhwOdBf/NPkbqqRPWFX3HL22aEh7f4ltKBK6SnLhtzJimvjOL+Ha71QVyN8Z9yQsw6RqvFmdTL4HidwaVapbI5+wDV6wbx6S/Rrg+rZJCGFXiKpEjn3WgM1XS2fccotAgSlpODfaojQ1tRVDnZztyXjMN8eaDioqzB9D2LEqkVCinmNR3ViuP2rp5jtRaQ2Y+qsACZ7hh+5y6q9sXINf4kHgpx3i6no9l7EeQBsJE7+mQxVg6ZNlq8l4PE357qg0nYDnGnPs+TWLYc/SeEKNG/FDh8kxmXpboK5AyQolYqzhYQ6+LgGkBtIrBtRMeBqqeWoqWgrbrTwFmRztzspoB07MNt5to79SdjAcBFsXKpG2gZS8TLOl0ZZNfj42kGgdP6kcDyaXNzTicl6wFCl4a5Lpsj3msudAfMoITnCnBdT2F/CAa5KHfOpKI+8j+eM20JAXodLGD6x0XK7TaIfToGqmrFpnkmQOFa+kIJRXHMEoVmeCnSk4Gj9/ufwc+zSI9eljA9ZKMCWcosIKs/i2wKArDtJhStsEE2ghBCwriD+Uty1zHijOaTSpdldQlNI5PMM9WSWgsnTkKgA8Vkz6jxQY5FnI4ye8p+lkfKbtqwylFwcjNQQk9KaGcWMUvF7lIDze46Rr5BjC7wh+Ded4b+T3q3i5+tEaPY/p
*/