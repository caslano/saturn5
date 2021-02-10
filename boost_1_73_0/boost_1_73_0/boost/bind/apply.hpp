#ifndef BOOST_BIND_APPLY_HPP_INCLUDED
#define BOOST_BIND_APPLY_HPP_INCLUDED

//
//  apply.hpp
//
//  Copyright (c) 2002, 2003 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//

namespace boost
{

template<class R> struct apply
{
    typedef R result_type;

    template<class F> result_type operator()(F & f) const
    {
        return f();
    }

    template<class F, class A1> result_type operator()(F & f, A1 & a1) const
    {
        return f(a1);
    }

    template<class F, class A1, class A2> result_type operator()(F & f, A1 & a1, A2 & a2) const
    {
        return f(a1, a2);
    }

    template<class F, class A1, class A2, class A3> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3) const
    {
        return f(a1, a2, a3);
    }

    template<class F, class A1, class A2, class A3, class A4> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4) const
    {
        return f(a1, a2, a3, a4);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5) const
    {
        return f(a1, a2, a3, a4, a5);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6) const
    {
        return f(a1, a2, a3, a4, a5, a6);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7, a8);
    }

    template<class F, class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9> result_type operator()(F & f, A1 & a1, A2 & a2, A3 & a3, A4 & a4, A5 & a5, A6 & a6, A7 & a7, A8 & a8, A9 & a9) const
    {
        return f(a1, a2, a3, a4, a5, a6, a7, a8, a9);
    }
};

} // namespace boost

#endif // #ifndef BOOST_BIND_APPLY_HPP_INCLUDED

/* apply.hpp
nKYfk08pXI4vLsbz9AqS9zCeXzHY+XR+Sq1XRGYB72qLjsgtqHWtFcod59974iAewOj0bDk5Yfr/0G7BMRnCxzRdwIezlO2jeO8SB/+oKteNRBg5L5UZlicHJh6AbgrIHKjKU69V1b81SobBtwBg8uliBgP2ON79y43kUXTHARl4A962S4bCbTNVKd8P2VcVfTaHwDBw4OLQ0zC1m1GLmCzSjJYIevu5xDvBNQ1zs+61YHRHDODAyn2zKBUdCWpbRP2EDfdeazppqzYrGo7CaG02D450OliQP8jmfTKbJZezZDJOp8k8ghezsC23TWOBtjC2G02LXxt0PmJBYKOI/obugW7H05xCq9aOlH0Otao7oE6mhyonJeZfKHWaJ2uNdfto0pMBnr1tszzLkvMw6G61orbUuaJP/aUQkvFXihAKOv4o38Bzd131ouDne/FADm9bWuYKD4oWeiO2DnKNomrqX2XcbTzW8j2AvQZHx8H34AdQSwMECgAAAAgALWdKUt6WBuJLAwAAUwcAACYACQBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL3NpbXBsZXBvc3QuY1VUBQABtkgkYK1UYW/bNhD9rl9x8zDMMlQr7ae1cYMGTroaLWIjdldkCCDQ0sniRpMqSdkx
*/