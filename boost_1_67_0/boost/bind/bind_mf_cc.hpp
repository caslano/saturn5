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