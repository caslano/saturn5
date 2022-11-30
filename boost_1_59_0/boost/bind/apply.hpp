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

#include <boost/config.hpp>

namespace boost
{

template<class R> struct apply
{
    typedef R result_type;

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

    template<class F, class... A> result_type operator()( F&& f, A&&... a ) const
    {
        return static_cast<F&&>( f )( static_cast<A&&>( a )... );
    }

#else

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

#endif
};

} // namespace boost

#endif // #ifndef BOOST_BIND_APPLY_HPP_INCLUDED

/* apply.hpp
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
*/