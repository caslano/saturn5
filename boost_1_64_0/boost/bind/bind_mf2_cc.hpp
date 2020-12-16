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
plEdov/ZHtz/yPEdkOuB4+Z6MPOpaWuOS1v7zWuP1/3+WmsFtMJ9Hsc/f5G+KocemhP06cWRkP02fZPKtnbsoyMkPOk4ds1S/eyadZa8co6AfnV5jEf6p/SnLeBq+BR1nuHJKxXvP8bKSJ8jo39IWw/kXeMu4HtdS2M7Yd1fOYY/1Jg81sS5BEsuXZDhmIkT5eufuZZzCgolvMjESXOlqG3gyeKfH9mXu573qfX33OuYb9VPzlFCegPeI5wvUS1dTeVa9dg7L8y378uXLWkUR/agjr703zNA98jxpZNEXxhn3wvCMpJia8P3RC7e2Ii8yZPfyJ/Rpz3n6h/h7V96i1yC9vNm3wmzznqixFsYeRb/RiAfp32qJSebYtnsE8+QtEKmbe/rjI230ZL2ZZGZfAiOdkdq/69peywiGRvRcZLWsoh0YvvKjZz2r3HaB/9e0vx9xBJXM7VxpmWy2RfLhd56bMWspLXuXFdH+r1ElHVNY8Ya+pnIZdH1T4tsjBXbziwdbxJbv2sM3Y5vHdCnLSm3pk+bzSN5Mzb2f1/2PeL8+IPbXvM0nyi+Mek8iVPP6PEo8Q+hZpoaPS4QnYy0lWtmyfz8OSadLOINk3h91O+NEy399jzynuzbl0761+XNjN/YdMIvfXkErit1sUj7+W7a/+bgqCPo8afb+uU8eDCuVlsqxiYm+fPfBzFEv1sU4j6u1PSvnusyQeO2l2Omvf3WyaQ1dcnvl5zwdHgH/LW1Tu8D6W9QppyF86QbJ77fvc/8hRW+a0vluxm75tIeXjk9r/QjRraX0eM/i/9Sdxu1EVwvVvTHxMkycXqo/jCfRvxXutNc9QJ1Dhm1xSsyK93ddO/NiSadzuY+yC33QT47Q3+S8OvcPakl332cxuM/3VcspL7FaZ/1kciWulugY+ZeQ+pB9jmVvYT+KjKXuW223S/hH2OnsfdHUl5bH0RnZrv3y/iwvtht74j+Ruu1Z+le9ySf66Fs2yw8veOcfnpXasZl8q7j72LYXo9pu5o9k+p5xl9zbJXRPW0XvYeg3jmm9a5ypK9pBqyVk385NxlrDSNUP2s+MvpptDNIN7WuPhfZD1VXvXHbOOuokelu7mOPif99J/1U+a7mnvZr8X8c3B+qnh0y4eilid8uhF4aHVQZt7nGnPrN+I+139TroKH490m/6aS3k5CLErl8RuoGegxL3nLsWY7cadPlgoVz5y4x+99GiMx7xqYguij3uT2TLBee/aisELqW7aBruSF0rSiErpWG0LUio2tSBr+1sCVxwWsG37LuvT6pr2sGg15x6NJl3cMu2I6Exk3Q+6zg9ZCEn/R6yKQQdiQ4h996yMMww3H94P/fOsFTtR5whqwH7PTc9uptvWO6LH71jS57ztr6Wd16wP/U9YCh18kef52gXoPyjm+/W+af8Pwvc+noqT33e1kc/5i/dQ6cvmvk/tD6O2AOXEud45QE42AyzICtYG+YBs+EKXAgbAOHwFQ4GraFxbAdnAvbwzKNdwhywev7HnkvJ+f/EX8fhi6d4zIIdoeDYT84Ep4Bx8JMeAE8G86Ew+BsOBxeA0fAG+A58GY4Cj4Cx8DfwwnwZXgufBNOgvvhZHgMToFtyMtUmAanwXQ4HWbAGXA4vAjOhDnwYpgLS+BMuBDmw0thAVwJC+EqOBv+FBbBu+DF8F44Dz4JS+ELcAHcDSvg23Ah/AAuht/AJbAedXkZbASvhM1hJf+3hlfBDvBqeAZcDofBFTALroLFcA2cC2+AV8K18HZ4E9wM18Nfw1vgo3ADfB5uhLvhHfAgvBMegZvhMXgXbEL73g1bwHtgGtwKzVxI65lP33nsD5i7uBc5i6/DCPg=
*/