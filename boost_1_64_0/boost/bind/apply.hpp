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
DpCn0IK1I+ZwvfxA2Y9NT1g6R1JanZO7Fcm0cm6yuEzlvkoIE3Me0T43ATsdoAM8UO251nGCTgYJ3GRpnKYUjBsI4IeLgcBIiltdSt1YzC/1upXILFzxgW5eodgmKwHQlpRLsYkobjfaKNtXcOn4n4LLUNVXrLQM9t5jF1HAu/w+V3b0DYz51RosNPwMxdorLqsloh1EEq/1FTfLIh+gtrL6WMu5Ijz9JHCvYq0OsdxpdiP9wj3f9ZC8DhGEKT2trIkjVBzpcDZkxAYZM1oiGhcqIwhzlZhw82VeG2n+e2MDlCFxpPuJpSAfr3OZmEWCA69xPNbiNpStloJCg7oGOWgaQxrFbbmXSvgS5+4/Of+IKPmr4Afo+7nBTP+M0ujQp3kEa776dfyEtBkzPoZto1ww9wIdKabwQLxk6yyPYkUX1XI8Ze5m7uKjOU7ecW6pjvw24EQuL6hV9CLmWEJGafx8k+JORcclUdimqMcTorPdkYklTS/fSf5fxg3M7zRI4pCtO7KkCSiRelseq8SH74QcjrMlMDN2hCXI4672cEwLfpga+ASXijX4Sw==
*/