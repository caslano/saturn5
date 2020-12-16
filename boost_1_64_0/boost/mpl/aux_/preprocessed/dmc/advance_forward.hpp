
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/advance_forward.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl { namespace aux {

template< long N > struct advance_forward;
template<>
struct advance_forward<0>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef iter0 type;
    };
};

template<>
struct advance_forward<1>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef iter1 type;
    };
};

template<>
struct advance_forward<2>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef iter2 type;
    };
};

template<>
struct advance_forward<3>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef iter3 type;
    };
};

template<>
struct advance_forward<4>
{
    template< typename Iterator > struct apply
    {
        typedef Iterator iter0;
        typedef typename next<iter0>::type iter1;
        typedef typename next<iter1>::type iter2;
        typedef typename next<iter2>::type iter3;
        typedef typename next<iter3>::type iter4;
        typedef iter4 type;
    };
};

template< long N >
struct advance_forward
{
    template< typename Iterator > struct apply
    {
        typedef typename apply_wrap1<
              advance_forward<4>
            , Iterator
            >::type chunk_result_;

        typedef typename apply_wrap1<
              advance_forward<(
                (N - 4) < 0
                    ? 0
                    : N - 4
                    )>
            , chunk_result_
            >::type type;
    };
};

}}}


/* advance_forward.hpp
SL+Egu8rte45frqR35nX7P+wP6+5OM9eZjjnvW/sEvi8/FY25+VXGDbEAfIazrnvbhmlNfzPtP0BGeXI0Jm2fnJCkeEuz++rcLZtr0j/803/RTpRk93nmx6dTtRxoHNOtZ8bPaVDJ+nQgXDAKPs89zpS1XQIuJYkvZwdTPG0ZuG29bee/1bTfu0oYfKvs3a0o6b92lHK5F937chdH+vkC6Cr1o66wINGm8jX2pFdOw3JXgobo0lVO1/QqBtnVvNkIxzgTE3iePYBe+vYu35UdhzWj/7fziCyXxcLf50o3HW0/7Z1pY7OdaUbh3Zc1n9to/bX7j4yb+Tua1KOz7pSXISey3pej/Q5K+R88z6NPPmetol3rileqdKLDpJeueKdUWk8PVNgs0riJRhypV8nxasF2ytePPEitU7WVPsu22m9rIMRz+yLW/Lqay4TaD0sRfEaKp79epjGP42L6KX1MOt+zi4wxoijfRfdtB6WoP0pPWC61sumaL2sEPaGq7Ru9rDWzV6AfbVO1g/u0vrZx1o/+0HrZ3HoM8iQB4fAP8JE2Aomwc5aR+uidbTtNbV/4iABtuwReczWwX7vfrx/r2thwfx3Tyn771wTOxb+u/19d1evj1V5fewYr40NZGzKJxQRNhLKCTV7sk5G6EvI6nn818uOk/+/1LzMtKP2/9dC7/6H2hvvvt2HJqVm81Vfb/z83H9P6OD6e7+0IbmuOGMziOJZO5jp+TtHlTvPQe+ZkZM5VtHYP6B4W/3i5VnWF96NivDaMtfQnni9ZzwA34vmmTzU+Z5hUWaiw/V+ERuhXyXvnO+QRmqy3iV0PSbZ+405wbhW/EO6pjCdPgUSjAc8eg0BnYcZeljfN3L1LmH2Q+Ko4b9O0p8044f75cNYIQn63urOR1fpZZa1u4b9+khKkp+szPwQ3pHdayMZHcxrI1aZCZH+ayMtWChI9M8fqyLBZZrtl1vWUn5qutpAbRhH2g6lbdPgUrNzsjOn6p23byA5et+8+kpnHablZKd73jfnU0FjnYm5ynqru27T/f2wNeV6r/YhpCZPTJ2S7MialJdMct729GyMsY/B1X6M9ZTtNZFBPZ19hdeXx06lMcZIQ/+225yuyeZV8TKz9W/lnnj8m8nHRVdTO96va3c7jkWHrYSDXG8aoXass/JrR1vasUfvuFouXxpvjPTqXWqj40YbfXZIvtqrZY2pqJZ//zizifEBO0Adh+mPifr0yO3jXrOpI7tG+e1IhEa7WhFQZmaemhZdwCW7fZC29c6o4G1rV5C2tT+MtmWczXOotmHDh63H1d46KrdpW3tDbFv7bOvS2rZ2WuvWo0siZUx7wdDOq0uZjdztNjJ2V9JeyurYj3ERQwPWXX4o64HusW5Nh8DrwO3r+o91Z9FuCkcHks2QF4Js8xr3qrr+/aElMor9ZeSFu6Y+vaH/MyP2RPvyjBrqLy+c9fQKSzla8zjlRP9y/AN5LLPJYzhr6e2UfvmJ/mX4R9KvcKdfhedtbbVHs5zEevZll5gkOVV41ra0lJtV3up6/uV2LvmKukbywn7OyleZ/PY9qLnW/fB80o0nXfkq05TT6SQV5OQm5xqyQvMd9UKy77qu2iIp8r8W31HXZ2SOzXDv4dS+zomZ8puqa0YPjYEaJ3JyPfsGL0BvjbHWbzgnyxZG+1E/IrQmbkKKfR6zM9LxVhE8f6Hmx18/a59YIf2GSL8BhAuJm5Lqq59nkhPyflmvblaZMfKRlyiZAyWzzF+myiOvyjK7utvaKfb5TBjjK9Py0K2yXHdeTz5VNm+SO58Qb4yr/nJxQYhfwBB8z1jHVb1T6HqMTx+bKflN1XdjCUf4j2Osn3w=
*/