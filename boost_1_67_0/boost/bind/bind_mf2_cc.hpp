//
//  bind/bind_mf2_cc.hpp - member functions, type<> syntax
//
//  Do not include this header directly.
//
//  Copyright (c) 2001 Peter Dimov and Multi Media Ltd.
//  Copyright (c) 2008 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//
//  See http://www.boost.org/libs/bind/bind.html for documentation.
//

// 0

template<class Rt2, class R, class T,
    class A1>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf0)<R, T>, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (), A1 a1)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf0)<R, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1));
}

template<class Rt2, class R, class T,
    class A1>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf0)<R, T>, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) () const, A1 a1)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf0)<R, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1));
}

// 1

template<class Rt2, class R, class T,
    class B1,
    class A1, class A2>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf1)<R, T, B1>, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1), A1 a1, A2 a2)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf1)<R, T, B1> F;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2));
}

template<class Rt2, class R, class T,
    class B1,
    class A1, class A2>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf1)<R, T, B1>, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1) const, A1 a1, A2 a2)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf1)<R, T, B1> F;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2));
}

// 2

template<class Rt2, class R, class T,
    class B1, class B2,
    class A1, class A2, class A3>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf2)<R, T, B1, B2>, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2), A1 a1, A2 a2, A3 a3)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf2)<R, T, B1, B2> F;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3));
}

template<class Rt2, class R, class T,
    class B1, class B2,
    class A1, class A2, class A3>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf2)<R, T, B1, B2>, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2) const, A1 a1, A2 a2, A3 a3)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf2)<R, T, B1, B2> F;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3));
}

// 3

template<class Rt2, class R, class T,
    class B1, class B2, class B3,
    class A1, class A2, class A3, class A4>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf3)<R, T, B1, B2, B3>, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3), A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf3)<R, T, B1, B2, B3> F;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3,
    class A1, class A2, class A3, class A4>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf3)<R, T, B1, B2, B3>, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3) const, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf3)<R, T, B1, B2, B3> F;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4));
}

// 4

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf4)<R, T, B1, B2, B3, B4>, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf4)<R, T, B1, B2, B3, B4> F;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf4)<R, T, B1, B2, B3, B4>, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf4)<R, T, B1, B2, B3, B4> F;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5));
}

// 5

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf5)<R, T, B1, B2, B3, B4, B5>, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf5)<R, T, B1, B2, B3, B4, B5> F;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf5)<R, T, B1, B2, B3, B4, B5>, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf5)<R, T, B1, B2, B3, B4, B5> F;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6));
}

// 6

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf6)<R, T, B1, B2, B3, B4, B5, B6>, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf6)<R, T, B1, B2, B3, B4, B5, B6> F;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf6)<R, T, B1, B2, B3, B4, B5, B6>, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf6)<R, T, B1, B2, B3, B4, B5, B6> F;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7));
}

// 7

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf7)<R, T, B1, B2, B3, B4, B5, B6, B7>, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf7)<R, T, B1, B2, B3, B4, B5, B6, B7> F;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf7)<R, T, B1, B2, B3, B4, B5, B6, B7>, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf7)<R, T, B1, B2, B3, B4, B5, B6, B7> F;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

// 8

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8>, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7, B8), A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8> F;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8>, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7, B8) const, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8> F;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

/* bind_mf2_cc.hpp
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
*/