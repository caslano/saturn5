/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP
#define BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP

#include <boost/callable_traits/detail/core.hpp>

namespace boost { namespace callable_traits {

//[ remove_member_volatile_hpp
/*`
[section:ref_remove_member_volatile remove_member_volatile]
[heading Header]
``#include <boost/callable_traits/remove_member_volatile.hpp>``
[heading Definition]
*/

template<typename T>
using remove_member_volatile_t = //see below
//<-
    detail::try_but_fail_if_invalid<
        typename detail::traits<T>::remove_member_volatile,
        member_qualifiers_are_illegal_for_this_type>;

namespace detail {

    template<typename T, typename = std::false_type>
    struct remove_member_volatile_impl {};

    template<typename T>
    struct remove_member_volatile_impl <T, typename std::is_same<
        remove_member_volatile_t<T>, detail::dummy>::type>
    {
        using type = remove_member_volatile_t<T>;
    };
}

//->

template<typename T>
struct remove_member_volatile : detail::remove_member_volatile_impl<T> {};

//<-
}} // namespace boost::callable_traits
//->

/*`
[heading Constraints]
* `T` must be a function type or a member function pointer type
* If `T` is a pointer, it may not be cv/ref qualified

[heading Behavior]
* A substitution failure occurs if the constraints are violated.
* Removes the member `volatile` qualifier from `T`, if present.

[heading Input/Output Examples]
[table
    [[`T`]                              [`remove_member_volatile_t<T>`]]
    [[`int() volatile`]                 [`int()`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() volatile &`]       [`int(foo::*)() &`]]
    [[`int(foo::*)() volatile &&`]      [`int(foo::*)() &&`]]
    [[`int(foo::*)() volatile`]         [`int(foo::*)()`]]
    [[`int(foo::*)() const volatile`]   [`int(foo::*)() const`]]
    [[`int`]                            [(substitution failure)]]
    [[`int (&)()`]                      [(substitution failure)]]
    [[`int (*)()`]                      [(substitution failure)]]
    [[`int foo::*`]                     [(substitution failure)]]
    [[`int (foo::* const)()`]           [(substitution failure)]]
]

[heading Example Program]
[import ../example/remove_member_volatile.cpp]
[remove_member_volatile]
[endsect]
*/
//]

#endif // #ifndef BOOST_CLBL_TRTS_REMOVE_MEMBER_VOLATILE_HPP

/* remove_member_volatile.hpp
wlZ+nokjztVHVpfzrdTh8nD9IePrSUnfyjNkHdfxFtr6DYpYv94u+TOsXqFSyotzWpC6mLZVu/TShxspMKeG+hVfv1VuCe63rAj9VqD65NcQbgyfhb65cc8Wa/Mh/whzo8q2sPYDzFZf+D7nbhMfNC/K/Gflm9lx/S8Jb3TuNbFWd2JtLuh4+EpkHnMeMk7YucYLS+S4LZ10k6FxaLokLs1JMN+Ffr9A+vBLSb9C+7RK3ms+cI85e513lPQlTrlJCjvG6j8tugvjVV1IHQmfbmKIG26au+ueP9dlU+JbOb9HnPuNh/4dx6c7aacE1kP4XYhZuqfOvHhPTFJ8bN3axAd0snGkhdF9y9jbLPWs7x97th0aOx7j4McnBd6B/0J1ewfxh/B8g4X5oSa63riklU8H72/JDvPbNKXqt0nW5ntJPXg/ksZxj8PddYw4Imkl6qPjMPOZwDhk8vjxcaiymbS9zv8SfsnZQKGJzlxrB6B0m1xn1vZAmDGqZbWRsiYRPknCu52RJsNZ6QzUeMfcIPHn8fsWw1roVCmTSS7cOJaxPlvktzvrTFzoOLbfHNklMr2cNuZo1uEWaLxj/inxxzh1GY9L5BsaQ0Xv87bED3OqxmOB1aXNknO90j327TW1SNKKTVf5tgZxtm0S3GPfzk83y3F+75zKr9Yr5nqNd8y/JL6+E0dZW03r0OtC8j4p5bauQZ7Z9lq6Qvsp9Jrx6vU+R8p41rmHv7WdgE49cA7J9ruhM0TuVVf7zLPXySqRTZRrroi5cFKdwDV3WK655J9wzbXZFnTNaX+1dPhFl2tO7RPYa+7R5ODrLesI11ud7cHXW2mY660y5Hq785nw11teXSNuBr4BfjL+dcpavz1wvZVwt11SzOnZc19Vg98e3/34bspZ+gBtaPw3dcRJe1VKnJisCtoHlF2fP/rNxxRlTBrX4LNaF//DgrT7dYnS7u5vhyCnex313nGChA/LF2c/wIf5HormaWq8el0eL+GvTSY1+wIfsh/S6tJPELkDph2/Vf/Ah7svuUtkquzv7JDwRH73+7mvDfub8pqkl7DrtZU/zuaZZuKIDXdv8bmkNwlzjC6h9xYyp4yW9H+antIyjr23uNF/jwjxNbAz5RuHmc/pOCyusil1nYw57RfiRkW431jRwIhbgk/Fn45/w/cs9lxQX+fMURtTV5ALW0ju/lbZdHsfdq+EJzIC4sN+h2utpI/hjqOOv/9tGU3C2htpBA9Luv83nnPDzbLz5uOSNs7QT9bmyGnIzMMX4b0UML8GbRl4nuMcaSc5xwjfzGrgv05UyZil+vQ++LubMpafD+yXyq8s1T0B8jwUfI+tclmR9stpegv3XHdEHXzwni/aXOrv3nfg1sH/8jrmX1rHH0H3HEHH//PZXomk4/9O9gQ8823h6vNXDl5x8h2Fpy7v8cf7I+n+I+1RiLQn4Kfr5sPr+H+6bj6CDj6Czj5IBy+/375n/NtUB19gdM0FLlNbHrXhdJWv6/h1jsmwO2wIB8NmcAz0whM1fCpMg0WwCSyHTWGlpKtO2K6dyNqLHK+175qGPtdbdbr9YR84DGbB4XAyHAlvhKPgJjgavgTHwb3wRHgIToLfwjIYq7rARDgFpsKpsCecBofDGfBEeCqcAWfCRbAAXgML4Wp4GrwLzoPr4Xy4AxbD12AJfFvT98Iy+A84BtbhfCtgC7gAjoML4QS4CJ4Az4CnwEpYDBfDUon3t99uo+sBup5A+8lvxQsu2zBeiBedcRpsBpvAHrA7HKThobApzIXN4ByYDs+F3eAKlb8GtoTXwQx4M2wF74Ct4WbYBu6AbeHbsB18H7aHH8KO8CjHL1cftoaNYFc=
*/