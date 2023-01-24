/*

@Copyright Barrett Adair 2015-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP
#define BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_varargs_hpp
/*`
[section:ref_remove_varargs remove_varargs]
[heading Header]
``#include <boost/callable_traits/remove_varargs.hpp>``
[heading Definition]
*/

template<typename T>
using remove_varargs_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_varargs,
        varargs_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_varargs_impl {};

    template<typename T>
    struct remove_varargs_impl <T, typename std::is_same<
        remove_varargs_t<T>, detail::dummy>::type>
    {
        using type = remove_varargs_t<T>;
    };
}

//->

template<typename T>
struct remove_varargs : detail::remove_varargs_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be one of the following:
  * function type
  * function pointer type
  * function reference type
  * member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes C-style variadics (`...`) from the signature of `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                                 [`remove_varargs_t<T>`]]
    [[`int(...)`]                          [`int()`]]
    [[`int(int, ...)`]                     [`int(int)`]]
    [[`int (&)(...)`]                      [`int(&)()`]]
    [[`int (*)()`]                         [`int(*)()`]]
    [[`int(foo::*)(...)`]                  [`int(foo::*)()`]]
    [[`int(foo::*)(...) &`]                [`int(foo::*)() &`]]
    [[`int(foo::*)(...) &&`]               [`int(foo::*)() &&`]]
    [[`int(foo::*)(...) const`]            [`int(foo::*)() const`]]
    [[`int(foo::*)(...) transaction_safe`] [`int(foo::*)() transaction_safe`]]
    [[`int`]                               [(substitution failure)]]
    [[`int foo::*`]                        [(substitution failure)]]
    [[`int (* const)()`]                   [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_varargs.cpp]
[remove_varargs]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_VARARGS_HPP

/* remove_varargs.hpp
GJN3HtXEpPfJ1fLyE+RqeQNtbbNO2sVgMNeyAqV2xQ8+KQBfhgj4MoRqyy83oh2EVQEpuJoUwRAE6BcgzsRtN+V+jj/2mHK36LCh59mfh5DFA+edDURkqdLs0vCwicZS7G8Fa/AkNhhJ/fiDqv7BqiYNlFUiU/4Jsh3/IbiyVlApTPX48616xQwQgps+lfhJrvvYYX80Hy9qci9hS8HKOPHho+zhZgybwmkanm3Q+cwSwtpq2nCUwTvhKM1JNyrWaEqYjHmeJpKDCzZ5AYRlxYtGPLIBdkTNOslj2OLY7cPXUAe2Pua/A+zjeR0a8NCRmlAwqWE/lrDSNdUX5du8x8jGx9p55DEZa3gnVEeQ0yQ/M6nPjsnPjqnPOnMDIawZHttVGzCQEUxnT1jSN/xOS1pH8V2FukYbZhYMIZXiYX6dza/38uud/DpxCC32sUPIvoFOp64cJ4BgcZa99FGDbjMQJoYAvXlZj9xJD6cgu6XWvNmAIS2gHWNb/T9POzZkXSrtmJ/192lHyuP/97Sj4zWXTDu+7P+XtGPRf0M7Qua3iHZUz/uvaMcT8/4O7Uie50U77PMU2nHzvP+cdpyv+yvaYYvle7T49Tp+7c+vvfm1eyzRDnNs87Rj4iMq7ai5oUnaUX4DNbvzhhbQDrPh/3na8cjDl0o74h/++7Qj6tH/e9pR1ueSaYe7z1/Sjoak/4R27J7bItqxau5/
*/