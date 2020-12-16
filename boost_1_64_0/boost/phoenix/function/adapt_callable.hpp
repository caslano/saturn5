/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2011 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUNCTION_ADAPT_CALLABLE_HPP
#define BOOST_PHOENIX_FUNCTION_ADAPT_CALLABLE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/detail/function_eval.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>

#define BOOST_PHOENIX_ADAPT_CALLABLE_NULLARY(NAME, FUNC)                        \
    inline                                                                      \
    boost::phoenix::detail::expression::function_eval<FUNC>::type const         \
    NAME()                                                                      \
    {                                                                           \
        return boost::phoenix::detail::expression::                             \
                function_eval<FUNC>::make(FUNC());                              \
    }                                                                           \
/**/


#define BOOST_PHOENIX_ADAPT_CALLABLE(NAME, FUNC, N)                             \
    template <BOOST_PHOENIX_typename_A(N)>                                      \
    inline                                                                      \
    typename                                                                    \
        boost::phoenix::detail::expression::function_eval<                      \
            FUNC                                                                \
          , BOOST_PHOENIX_A(N)>::type const                                     \
    NAME(BOOST_PHOENIX_A_const_ref_a(N))                                        \
    {                                                                           \
        return boost::phoenix::detail::expression::                             \
            function_eval<FUNC, BOOST_PHOENIX_A(N)>::                           \
                make(FUNC(), BOOST_PHOENIX_a(N));                               \
    }                                                                           \
/**/


#define BOOST_PHOENIX_ADAPT_CALLABLE_VARARG(NAME, FUNC)                         \
    BOOST_PHOENIX_ADAPT_CALLABLE_NULLARY(NAME, FUNC)                            \
    BOOST_PP_REPEAT_FROM_TO(                                                    \
        1                                                                       \
      , BOOST_PHOENIX_LIMIT                                                     \
      , BOOST_PHOENIX_ADAPT_CALLABLE_VARARG_R                                   \
      , (NAME, FUNC)                                                            \
    )                                                                           \
/**/

#define BOOST_PHOENIX_ADAPT_CALLABLE_VARARG_R(Z, N, D)                          \
    BOOST_PHOENIX_ADAPT_CALLABLE(                                               \
        BOOST_PP_TUPLE_ELEM(2, 0, D)                                            \
      , BOOST_PP_TUPLE_ELEM(2, 1, D)                                            \
      , N                                                                       \
    )                                                                           \
/**/

#endif

/* adapt_callable.hpp
U7xwtr8H7qgpsjIEVG32+OnWEcE9YocC+XyXe2O4+cgQPv1W75B1DNSnugvHH4Nybwyv/lq/PqGeMQAvOSXj2Clgt+U0rIVqETNFj5tED9iHeGd6CpffLvXkImGzk9Zot3vSGlXv6QT0CYvy5nGH0s/yzls6dO/1n0sb/X42LOftf6/EvYJ3IgTvWpjQ189CPP1Ve++0jNPve4rqUzRZ59O2lUqh/Ra8N8SPDVP0xQKvZrUfd48TX0/ejNW64i7qZA1BH9/rf98453/rOq//g2JD0qZHN/LePenT37b08cYj1JPjIgTyy/8m5U4o9L0uMh51/pBKzz4UWFOgnTf3J/U4empqrKeD65PGQRo9p2hstYWm8bNqPsE4S/o5L9MmUCdsYzGS/5xXx6lYCPPRdHk9MFfXSK1lPfUprravPqdDFQKyFb+8GxhHr+XNwFr88Xye+EjaBGmvY+UX5gdkR2Ll3it4qu0X44J36Tgy6Wd7a9yYsUbnaPvv7RmVYz3Oe4fW3pTickeDuVj6XFDnCIqCkJQslz6XPfdSGHryQPsTKl10iJrXV3ZeDQ3ukEcQqCcP54rNT9v7Cdn6dBJklo4Wm26yzzws9QWM0YJXB/Mf9p67DlU2QcqmqLLJham+I23ZluLarnB3Wx9cO2R0Nr00pdCPT8a626Ltqm73QnkHm/fxezsj8Igfp59ZKLxDfbb3AfeWcW12uOMApXNnFzpaMZ4klATs4ZzA2MHcxbnBejFoGofsm62NXK6hx9o/SzthOm8tB+o24a6M96ZLg/0FhaTr97R0WOaq7SccFlUE7oKbFqyXDLX0/Oal9yAqm4AAShNvjHLa1NpGIp3hZKac7SZxexnB7pTjy0r6DdmGfbbxBeG3KimbrsoOouyxI8DfqqyeMj7RbGJD/LLF0u5g225LedVlRgVt6ISsvHpEYeq+gpYEICDcEZL97g+jQuiQPRlXvncQn2ZvE8/yPr1zAJQeOqLPHQTSRI1zvBff9aKbxJx6u1vVmsKsqbW5210QLq9Mm3Rde7quywYM7TD+OWtU+E5Ylu7pUCxP8SNsnv6+XOl68J2A6uy6vjPFk40NTfXuKmC+JwE97Z+V1TUVmfi4qzBI98y7umKFmt6ZdT167W32yEy9CzpS9LzcxOzclsDdUIcrO+he7kqjPyW78UIZp7GpriEw96SVraaauvmqUvt3ywvVPSKB3NfZY/xnEyd3v4N54KcXZlmDIOOepH8X1ho9RznXBNy7rdT3+p7fh9aZ9yxckElr6nxa/awweEYkicdq/EtUf7SYp1P3UvezUKcdoZCaNySw97348zla8WiQtpcq2gbfKbksgx6Za7w8sGfa97giPWY8YjGBzpj1z+Oy7YkbxV/nlbTxEoZZrE6D9e6j/3hAXnD0022uz/Zcl8Tvz+1mRROqvKNCPc7v9PqFWRw8VfK7Nlsbccakre97pOdVU1e3YFF96lae1mhcP/PuzP3AbMstsYp37gmME8BHwee4aegYw72Zz9BXpvQ0Jzsy6P1bHXcRTeceqGjwRH/0JhobJxHFxYQ225YTYPWe8Qv9tRN5VvF8z89uDoepk1Cl0EPH7Vtj2d8FfSXrsyA9CXExySUJ6ihx/vlTzqeyv5vtnRXoHFnpKje++nR8Pes8XByvJyIv/+nzU/0cd6Vnd+b6JvR3j4PcZ5SNhgDT7khYiKjmfYOKNYjm9+/bG+n3D+bWX9O3DsXl7kvMyHd4O6UzrYnC1MsLAb7i3MxeMbrsVXpOH6TtHaM1B2KsH1JX2ri0tix9KVHcmuejYy367qjUXsvpR3NiVXfYtvDzigr9dVnPyxOOQIxdaCbHBMK8mbnXMo4=
*/