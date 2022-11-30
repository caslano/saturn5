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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) () BOOST_BIND_MF_NOEXCEPT, A1 a1)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf0)<R, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1));
}

template<class Rt2, class R, class T,
    class A1>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf0)<R, T>, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) () const BOOST_BIND_MF_NOEXCEPT, A1 a1)
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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf1)<R, T, B1> F;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2));
}

template<class Rt2, class R, class T,
    class B1,
    class A1, class A2>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf1)<R, T, B1>, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2)
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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf2)<R, T, B1, B2> F;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3));
}

template<class Rt2, class R, class T,
    class B1, class B2,
    class A1, class A2, class A3>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf2)<R, T, B1, B2>, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3)
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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf3)<R, T, B1, B2, B3> F;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3,
    class A1, class A2, class A3, class A4>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf3)<R, T, B1, B2, B3>, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4)
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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf4)<R, T, B1, B2, B3, B4> F;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf4)<R, T, B1, B2, B3, B4>, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf5)<R, T, B1, B2, B3, B4, B5> F;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf5)<R, T, B1, B2, B3, B4, B5>, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf6)<R, T, B1, B2, B3, B4, B5, B6> F;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf6)<R, T, B1, B2, B3, B4, B5, B6>, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf7)<R, T, B1, B2, B3, B4, B5, B6, B7> F;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf7)<R, T, B1, B2, B3, B4, B5, B6, B7>, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
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
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8> F;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8>, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(boost::type<Rt2>, R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7, B8) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8> F;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

/* bind_mf2_cc.hpp
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
*/