/*

@Copyright Barrett Adair 2015-2018
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_LVALUE_REFERENCE_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_LVALUE_REFERENCE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_lvalue_reference_hpp
/*`
[section:ref_add_member_lvalue_reference add_member_lvalue_reference]
[heading Header]
``#include <boost/callable_traits/add_member_lvalue_reference.hpp>``
[heading Definition]
*/
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

template<typename T>
struct add_member_lvalue_reference_t {
    static_assert(std::is_same<T, detail::dummy>::value,
        "Reference member qualifiers are not supported by this configuration.");
};

#else
//->
template<typename T>
using add_member_lvalue_reference_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_lvalue_reference,

        detail::fail_when_same<typename detail::traits<T>::add_member_lvalue_reference,
            detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<
            typename detail::traits<T>::add_member_lvalue_reference,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_lvalue_reference,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_lvalue_reference_impl {};

    template<typename T>
    struct add_member_lvalue_reference_impl <T, typename std::is_same<
        add_member_lvalue_reference_t<T>, detail::dummy>::type>
    {
        using type = add_member_lvalue_reference_t<T>;
    };
}
//->

template<typename T>
struct add_member_lvalue_reference
  : detail::add_member_lvalue_reference_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds a member lvalue reference qualifier (`&`) to `T`, if not already present.
* If an rvalue reference qualifier is present, the lvalue reference qualifier replaces it (in accordance with reference collapsing rules).

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_lvalue_reference_t<T>`]]
    [[`int()`]                          [`int() &`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() &`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() &`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const &`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() & transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_lvalue_reference.cpp]
[add_member_lvalue_reference]
[endsect]
*/
//]

#endif


/* add_member_lvalue_reference.hpp
FM3ctaLTmzLnmNrSelqOXeF+hRboXHcDm71OuZW56Xz37WsiG22TWWQe/glq++9pue4g/Gcau55vyLFEeZbkcs/2aOrpN0UWRydHJtRdZPpN5tkgdcW0Xa1wWbhx6p+Nq+3dz9BdsT2hNLfPnlC2O/gZkOcOfv9Kg5QFx6Qs/OraJ809F5ipda2v1DXcbRXWNR35cGx3VL+/Uz3T8Itdw0PVM21jvhaZtrY6sdiqE6bOzL/dCr/Pz77a56LTjzrhs6/WQeQ+pUYMooeRGGSv0mprvxC9Dm5bfQmqCzfLecb61YX7rWOcszr13arP/5DrdXS3p37U0frRWuvFeaZeoJ9w+urGt8hav3+j1xR+onWj7GdOdaPU1gw5tkOqn2N9twv5Hj9GZex22B4Q//PUBfN+dLH0vdWW7psSvtVdm5wIqk/67NstMs9yDlP+c6GpA/dJ+Otue5+S+ma+GT0k4f34LhIb/D1O6+RdIvOyqbPEwa9fukXC33IPpNzra7nfRduxGbcFd7f2F++B1AXzP5RnzuCUqtn9tZ45A+6s2vuRf52wf5eSPParE81ayzUoCWThE546QSIc64StuQjdd6ROqP4KvlYk8vRp4FQvVK6J6T80Ef+D7i78dSr3OSJzYWDd4dpDJP0DJHyNuy7fsofShwioH6Yf0kjkHnJ3dUUGl7/W0/NFZqZc6+OGUoe4r3z14yIJnxxYP0zfK1HCd7u7kev9qCP1tI5QN6SebLXVkXu1juj/tBXVqx+rNx9f/ZgeXD+Mfat3CbB+f1KZl3B/RD99SwX1Qzqyjt/0VPdsU56F4v+F07uqyncx/ZUF4n/I/r3T757MN+fjPjf6nUR+UYi9kS+S8IfFn2/k2zu2CSskfK3L29a31/fEbfA+3HZf2VLOldu903Y7qFz6hHj/S7d9ezXfY4PfCc1al/XtPBf6QOfKvIH7O9fJvttmU/XSrNklBd2YAFC8IMR4iXkf/InoPOkq4/w/x2l56rma6H3maQts3zk1vJGcJwX/YvG/4FrN31/iAt83rIi/LDJTsU9Tzzybu93DMb6RBbXn+s6wSnQySH8j8x3tCzk2lGMDXEH3sMZ/k8jEqN+rU8+s+Wki7wZVnZvj+M1c3xO9edM3/iW5Dt99kbXfc7+m4ybUMvs57q/IlN3jV2aMDmQVFufPs97BLAPhJfmFBead3K3v5JpG1W1i7qHbxL/Fnvfmfthzj/aLtLx2i7+QOM7hmCXjpnLLPUmZ1lU577Fu1jGJR5eW8u5XPM/2nedmOdddEr5QwnNy8mzvfS9KeDP1M1tiq89W5e89cxr85OtKeFygvLw3bqTux5KXD8h3oTaxteJjIzvy6ujw3ijyacjvkPfG9GDb0SqTjcxOS+aM+bFR7bFyjUxF51yJ/IOWfN2yssBzVrVtmCD1ScpU72+1P9jJV1ca4H6hdaVoa2BdMVUksI6Y+/tq0dnmWsnfTTitO3quJHtdMffyVglb7somTpfgAt7nzb35uMhl4z/XlNWrcixeyqqcPNrbUd/xozAaXjc2qjtZ65CvIv8u8ndIvgaXldd/fzXaX5PHAbYrO3b2CO/XPN6H+w2y2ffa8li/42Tlej/kOH9XWyx6O1zpMkvM5LOer5GrNaloS7kexFnfzaJjYqPKVkbXjYyp25WPmhFWWkJ+P9PvGqnyPPLZgP7cYjXaLqc91A9rPkzQfBjjzYdtJh/k+6LJjFDvDJoHxZYOOdzDpF/Pg4RJW+Vt7uiqxPuzM3V/Yh13tWTHJ5K/vnjLBDgin1WcLyOSIfsWxFF1uqmfuN8n398C3kGHSH1yS1hiUBsbb8LqqN97nohK15RqXbX1AdRerHk=
*/