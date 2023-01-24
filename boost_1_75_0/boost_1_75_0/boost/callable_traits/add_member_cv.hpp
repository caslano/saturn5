/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_ADD_MEMBER_CV_HPP
#define BOOST_CLBL_TRTS_ADD_MEMBER_CV_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ add_member_cv_hpp
/*`
[section:ref_add_member_cv add_member_cv]
[heading Header]
``#include <boost/callable_traits/add_member_cv.hpp>``
[heading Definition]
*/

template<typename T>
using add_member_cv_t = //see below
//<-
#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

    detail::sfinae_try<
        typename detail::traits<T>::add_member_cv,

        detail::fail_when_same<typename detail::traits<T>::add_member_cv,
                detail::abominable_functions_not_supported_on_this_compiler,
            this_compiler_doesnt_support_abominable_function_types>,

        detail::fail_if_invalid<typename detail::traits<T>::add_member_cv,
            member_qualifiers_are_illegal_for_this_type>>;
#else

    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::add_member_cv,
        member_qualifiers_are_illegal_for_this_type>;

#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

namespace detail {

    template<typename T, typename = std::false_type>
    struct add_member_cv_impl {};

    template<typename T>
    struct add_member_cv_impl <T, typename std::is_same<
        add_member_cv_t<T>, detail::dummy>::type>
    {
        using type = add_member_cv_t<T>;
    };
}

//->

template<typename T>
struct add_member_cv : detail::add_member_cv_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Adds member `const` and `volatile` qualifiers to `T`, if not already present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`add_member_cv_t<T>`]]
    [[`int()`]                          [`int() const volatile`]]
    [[`int(foo::*)()`]                  [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() &`]                [`int(foo::*)() const volatile &`]]
    [[`int(foo::*)() &&`]               [`int(foo::*)() const volatile &&`]]
    [[`int(foo::*)() const`]            [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)() const volatile`]]
    [[`int(foo::*)() transaction_safe`] [`int(foo::*)() const volatile transaction_safe`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/add_member_cv.cpp]
[add_member_cv]
[endsect]
*/
//]

#endif

/* add_member_cv.hpp
QqG8VYcCdcQeyw8RWzx7OFDe7fkpewT7Pw/j5Ru6DPySypUfpusV/P4yfm0PV6mQvw3iTy9U0fU3fi3g73+sQrHWi+cyfkvwNXy7SuG3aN6CcNRTKFKjsW2t3T1+LYD3vS6NjW2xrxCfrUVIPYmUlFHB1sUwbsxhDWQrE8nPhKhMnn4A0u1wHgGhFoyKJGMeGY/59i6cNWQiDjiiUnwP3Mo7o4OUdSVA9BKhVqRkfboBmBQ20A466QJGjeYj+m4az2yTzPuTisnQgO3jIdlgJEPKSUerQ7w5nl+69AhP+GwR6LCpVM7jIjmq87AVMCz6bGPGYep5sVSlWKpSjB8gDflPIrx6DIvnfIMHYwwj+eKpbQCE/wSJypN8geB5GxizZMpfo6N+o1nP0xlXAUIjMEIBp9wF+YhtDBtJ0Rr+MF6pFFAb0QDiv9yE2gXIZCdFMtS2MNSW0Vp/gNArjyN1Fr92OUjXdvzail+nEKb/eQCwUcHFeZGKEZ6BwJD4mqIEptLpjZBe1TWnhKFhCYzvqs6k3zEQ2022Q4Cogi12PeHhE7Ao3ZwdmrczwplAIJprgCRMDNFYzcmQSYb9vtu6oH5v625fmvJuZpXjzK6AEB2dZx4XtgB/Xwm/DQ/jbwxzZ7zOQsjRZrMcqA4bFCDfdttCIucdDSQrWjhrjlRZsw5fBdrFpBR8iFh5OoifOcHe4FGtPB/g90E8HyDj
*/