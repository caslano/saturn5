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
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
*/