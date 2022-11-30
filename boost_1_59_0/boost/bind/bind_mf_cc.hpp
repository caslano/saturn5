//
//  bind/bind_mf_cc.hpp - support for different calling conventions
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

// 0

template<class R, class T,
    class A1>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf0)<R, T>, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) () BOOST_BIND_MF_NOEXCEPT, A1 a1)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf0)<R, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1));
}

template<class R, class T,
    class A1>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf0)<R, T>, typename _bi::list_av_1<A1>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) () const BOOST_BIND_MF_NOEXCEPT, A1 a1)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf0)<R, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1));
}

template<class Rt2, class R, class T,
    class A1>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf0)<R, T>, typename _bi::list_av_1<A1>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) () BOOST_BIND_MF_NOEXCEPT, A1 a1)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf0)<R, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1));
}

template<class Rt2, class R, class T,
    class A1>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf0)<R, T>, typename _bi::list_av_1<A1>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) () const BOOST_BIND_MF_NOEXCEPT, A1 a1)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf0)<R, T> F;
    typedef typename _bi::list_av_1<A1>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1));
}

// 1

template<class R, class T,
    class B1,
    class A1, class A2>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf1)<R, T, B1>, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf1)<R, T, B1> F;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2));
}

template<class R, class T,
    class B1,
    class A1, class A2>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf1)<R, T, B1>, typename _bi::list_av_2<A1, A2>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf1)<R, T, B1> F;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2));
}

template<class Rt2, class R, class T,
    class B1,
    class A1, class A2>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf1)<R, T, B1>, typename _bi::list_av_2<A1, A2>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf1)<R, T, B1> F;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2));
}

template<class Rt2, class R, class T,
    class B1,
    class A1, class A2>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf1)<R, T, B1>, typename _bi::list_av_2<A1, A2>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf1)<R, T, B1> F;
    typedef typename _bi::list_av_2<A1, A2>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2));
}

// 2

template<class R, class T,
    class B1, class B2,
    class A1, class A2, class A3>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf2)<R, T, B1, B2>, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf2)<R, T, B1, B2> F;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3));
}

template<class R, class T,
    class B1, class B2,
    class A1, class A2, class A3>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf2)<R, T, B1, B2>, typename _bi::list_av_3<A1, A2, A3>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf2)<R, T, B1, B2> F;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3));
}

template<class Rt2, class R, class T,
    class B1, class B2,
    class A1, class A2, class A3>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf2)<R, T, B1, B2>, typename _bi::list_av_3<A1, A2, A3>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf2)<R, T, B1, B2> F;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3));
}

template<class Rt2, class R, class T,
    class B1, class B2,
    class A1, class A2, class A3>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf2)<R, T, B1, B2>, typename _bi::list_av_3<A1, A2, A3>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf2)<R, T, B1, B2> F;
    typedef typename _bi::list_av_3<A1, A2, A3>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3));
}

// 3

template<class R, class T,
    class B1, class B2, class B3,
    class A1, class A2, class A3, class A4>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf3)<R, T, B1, B2, B3>, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf3)<R, T, B1, B2, B3> F;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4));
}

template<class R, class T,
    class B1, class B2, class B3,
    class A1, class A2, class A3, class A4>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf3)<R, T, B1, B2, B3>, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf3)<R, T, B1, B2, B3> F;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3,
    class A1, class A2, class A3, class A4>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf3)<R, T, B1, B2, B3>, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf3)<R, T, B1, B2, B3> F;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3,
    class A1, class A2, class A3, class A4>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf3)<R, T, B1, B2, B3>, typename _bi::list_av_4<A1, A2, A3, A4>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf3)<R, T, B1, B2, B3> F;
    typedef typename _bi::list_av_4<A1, A2, A3, A4>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4));
}

// 4

template<class R, class T,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf4)<R, T, B1, B2, B3, B4>, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf4)<R, T, B1, B2, B3, B4> F;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5));
}

template<class R, class T,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4, class A5>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf4)<R, T, B1, B2, B3, B4>, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf4)<R, T, B1, B2, B3, B4> F;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4, class A5>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf4)<R, T, B1, B2, B3, B4>, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf4)<R, T, B1, B2, B3, B4> F;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4,
    class A1, class A2, class A3, class A4, class A5>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf4)<R, T, B1, B2, B3, B4>, typename _bi::list_av_5<A1, A2, A3, A4, A5>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf4)<R, T, B1, B2, B3, B4> F;
    typedef typename _bi::list_av_5<A1, A2, A3, A4, A5>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5));
}

// 5

template<class R, class T,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf5)<R, T, B1, B2, B3, B4, B5>, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf5)<R, T, B1, B2, B3, B4, B5> F;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6));
}

template<class R, class T,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5, class A6>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf5)<R, T, B1, B2, B3, B4, B5>, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf5)<R, T, B1, B2, B3, B4, B5> F;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5, class A6>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf5)<R, T, B1, B2, B3, B4, B5>, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf5)<R, T, B1, B2, B3, B4, B5> F;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5,
    class A1, class A2, class A3, class A4, class A5, class A6>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf5)<R, T, B1, B2, B3, B4, B5>, typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf5)<R, T, B1, B2, B3, B4, B5> F;
    typedef typename _bi::list_av_6<A1, A2, A3, A4, A5, A6>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6));
}

// 6

template<class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf6)<R, T, B1, B2, B3, B4, B5, B6>, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf6)<R, T, B1, B2, B3, B4, B5, B6> F;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf6)<R, T, B1, B2, B3, B4, B5, B6>, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf6)<R, T, B1, B2, B3, B4, B5, B6> F;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf6)<R, T, B1, B2, B3, B4, B5, B6>, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf6)<R, T, B1, B2, B3, B4, B5, B6> F;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf6)<R, T, B1, B2, B3, B4, B5, B6>, typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf6)<R, T, B1, B2, B3, B4, B5, B6> F;
    typedef typename _bi::list_av_7<A1, A2, A3, A4, A5, A6, A7>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7));
}

// 7

template<class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf7)<R, T, B1, B2, B3, B4, B5, B6, B7>, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf7)<R, T, B1, B2, B3, B4, B5, B6, B7> F;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf7)<R, T, B1, B2, B3, B4, B5, B6, B7>, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf7)<R, T, B1, B2, B3, B4, B5, B6, B7> F;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf7)<R, T, B1, B2, B3, B4, B5, B6, B7>, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf7)<R, T, B1, B2, B3, B4, B5, B6, B7> F;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf7)<R, T, B1, B2, B3, B4, B5, B6, B7>, typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf7)<R, T, B1, B2, B3, B4, B5, B6, B7> F;
    typedef typename _bi::list_av_8<A1, A2, A3, A4, A5, A6, A7, A8>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8));
}

// 8

template<class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(mf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8>, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8> F;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template<class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    _bi::bind_t<R, _mfi::BOOST_BIND_MF_NAME(cmf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8>, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7, B8) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8> F;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<R, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(mf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8>, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7, B8) BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef _mfi::BOOST_BIND_MF_NAME(mf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8> F;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

template<class Rt2, class R, class T,
    class B1, class B2, class B3, class B4, class B5, class B6, class B7, class B8,
    class A1, class A2, class A3, class A4, class A5, class A6, class A7, class A8, class A9>
    typename boost::enable_if_c<!boost::core::is_same<Rt2, R>::value,
    _bi::bind_t<Rt2, _mfi::BOOST_BIND_MF_NAME(cmf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8>, typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type>
    >::type BOOST_BIND(R (BOOST_BIND_MF_CC T::*f) (B1, B2, B3, B4, B5, B6, B7, B8) const BOOST_BIND_MF_NOEXCEPT, A1 a1, A2 a2, A3 a3, A4 a4, A5 a5, A6 a6, A7 a7, A8 a8, A9 a9)
{
    typedef _mfi::BOOST_BIND_MF_NAME(cmf8)<R, T, B1, B2, B3, B4, B5, B6, B7, B8> F;
    typedef typename _bi::list_av_9<A1, A2, A3, A4, A5, A6, A7, A8, A9>::type list_type;
    return _bi::bind_t<Rt2, F, list_type>(F(f), list_type(a1, a2, a3, a4, a5, a6, a7, a8, a9));
}

/* bind_mf_cc.hpp
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
*/