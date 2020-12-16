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
hurlm7Al3Adbwbc0vf3m2Z7rVPVqAH/vUb1q4SYfsC3sDNtDmYMFJ8AOMAuugnmwEyyEXeBVsCe8FfaGt8M+8HewH3wa9ofvwrPgB3AgbOCmPDARroJpcAhMh5mwFzwbis1kKHaW4QJ4DrwMjoKr4Wh4HxwLq+EEuA1Ohq/CKfBLOBV+A6dDSz8uhJkwF45U/1j1XwBnwnxYCFfA2fB6WAR/CovhbfBiuB2WwCfgXPgWnAffgaXQRb2Xw1RYAdvBxbAnXAr7wko4GC6DmfBqOAUuhxfClbAAdoXXwnS4Gq4ya230OUefB7MC1to8pHPstsEB8BHtp34Nh8NHtT95D06Fj8F8+DtYCXfAa+HLcLD1rAVz4Ot6fb8Fy+Hb8HL4DlwG/wxvhe/CO+B7Zm6g3hPr80FWwNzAj3SO+cewH/yb9n+HNL9/h1nwC3g+/Armwm+0nz0GS6Cb+lkP68HtMBp+DWPgMXgajLDODc0crk80X7jsgDlw7VykFxX+XCrvPKoanUuV+GndPKpw51H9t8yfqmXeVFhzpn6o+VLM5Qt7ztRx5kv9V86V+iHmSZ2qOVL/8vlRtrlRzOf8j5gfdTJzo3bg1vHEvRN3EBfN7oV9cZNxpbi6X92v7lf3q/vV/ep+db+6X92v7lf3q/vV/b7v7180/7+keKZM///e8/+/TnSZfcJn6Pv+Trimug/i/daetM+ZOd/D2ChVP4177Dc3MnMS88x8jHYiH2u+kRPfb9+pVjKPtfa9aqw9BjPM3Kg8vz3NX9C8puh3/Ba4e5HLDJ1XbDq7/M4/r1nt+/ra521i10l+07RehuOuJPOloc9XWlbMlHidK6j7vQbOqdK4Xcw+kbeIv4OtThdL2Fgj2xG/7pEt/u62ee3F8wo4O3+afZrWikw/8ReZNNpLfrAhyt+696u2W5UtPxONfKpfva1pXvtcI12HoHt9apk5Nsq05WJXgt++OZp3jZsNyR/HJX9+7bC5nkt+q1VHV+AqaYf9z/mtSwixQ4vjugSNGy91eRVpUXLdW983J/QrkSl3xfBvIS5gTyszFyd9lyU3wJopJ/PKsyM5Rp6Pyd5NE12B88q9MlnIfGvJRHU1Mn9TmWT8Ufi/IzxRdBeGeQ3pXBLHPbcPRwXX50oSrNrlV58hd1lB1KlONX68hF+jdVpWUm7q855dwfWpe4D51ee+gPrcQj0tJc/uJIf6VJlNUfiTjl+fkYT3k/qE37M+z9D63KvrZl7GJSqvJ8HM5/3r01Iw5/pTeXKToH3DReLfxvkb00aNnfYw13itzBzo6eL/tSuZPF6PC6njWtezRPZ+Vzz/XoMLta/kCpG5nn4wNuQ1MIp0bhWZIcxGTtZjbteDciyPNKfIfm1HaICsBrpfW+TAmKhGMZFdnfZqVPmKBrpfW6MsV8g96vUaiaJdjyaGNx/XcY/GEHu39/a2sa43OFOvmV64G1Mpz+/92xiFd2xfZM38/Kg4CUfat3/jTAlPI323tq3GQcJpv7zZEp5s6sZ1AnurBpa/PyRfHCNfgTreUG096xqObqrjm/zK36tWHffIt3LSZQ1PMOt+HhF/m5B7Iz8hYc3NWFWPst+TeHLXs5bfsf2jG+vaOG3/Adr+BwPL79z+yB6//SP+YIWn29pf4yBh7U24jzao5lNGfcoZGVc/gkun8QRQr77L3v6OutJA0j/db41hw6TvV19O+pLYxPpX5isgS1y4lPiZf/DWl2x+N7J4Xl6Js76oPL1qO9WHbPEXu+M5WxnuG86Z4K7PPA7mdpt7LtKYWTzfzP016bSQdMbhnyL+ue5E/r0E9x1rYJLdUdg29YxL5VKKUtk4t53O/82VOLnuxq4=
*/