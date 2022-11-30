//
//  bind/bind_cc.hpp - support for different calling conventions
//
//  Do not include this header directly.
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

template<class R>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) () BOOST_BIND_NOEXCEPT, _bi::list0>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) () BOOST_BIND_NOEXCEPT)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) () BOOST_BIND_NOEXCEPT;
    typedef _bi::list0 list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type());
}

template<class R, class B1, class A1>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1) BOOST_BIND_NOEXCEPT, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1) BOOST_BIND_NOEXCEPT, A1 a1)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1));
}

template<class R, class B1, class B2, class A1, class A2>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2) BOOST_BIND_NOEXCEPT, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<R, F, list_type> (f, list_type(a1, a2));
}

template<class R,
    class B1, class B2, class B3,
    class A1, class A2, class A3>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3) BOOST_BIND_NOEXCEPT, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3));
}

template<class R,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4) BOOST_BIND_NOEXCEPT, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5) BOOST_BIND_NOEXCEPT, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5, B6) BOOST_BIND_NOEXCEPT, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5, B6) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5, B6) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_NOEXCEPT, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_NOEXCEPT, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class R,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8, class B9,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<R, BOOST_BIND_ST R (BOOST_BIND_CC *) (B1, B2, B3, B4, B5, B6, B7, B8, B9) BOOST_BIND_NOEXCEPT, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(BOOST_BIND_ST R (BOOST_BIND_CC *f) (B1, B2, B3, B4, B5, B6, B7, B8, B9) BOOST_BIND_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef BOOST_BIND_ST R (BOOST_BIND_CC *F) (B1, B2, B3, B4, B5, B6, B7, B8, B9) BOOST_BIND_NOEXCEPT;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<R, F, list_type>(f, list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

/* bind_cc.hpp
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
*/