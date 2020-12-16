// Copyright Cromwell D. Enage 2019.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_RETURN_TYPE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_PARENTHESIZED_RETURN_TYPE_HPP

namespace boost { namespace parameter { namespace aux {

    // A metafunction that transforms void(*)(T) -> identity<T>
    template <typename UnaryFunctionPointer>
    struct unaryfunptr_return_type;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <boost/mp11/utility.hpp>
#else
#include <boost/mpl/identity.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename Arg>
    struct unaryfunptr_return_type<void(*)(Arg)>
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_identity<Arg>;
#else
        typedef ::boost::mpl::identity<Arg> type;
#endif
    };

    template <>
    struct unaryfunptr_return_type<void(*)(void)>
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        using type = ::boost::mp11::mp_identity<void>;
#else
        typedef ::boost::mpl::identity<void> type;
#endif
    };
}}} // namespace boost::parameter::aux

#if !defined(BOOST_NO_SFINAE)
#include <boost/core/enable_if.hpp>

namespace boost { namespace parameter { namespace aux {

    template <typename Pred, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::enable_if<Pred,Ret>)>
    {
        typedef ::boost::enable_if<Pred,Ret> type;
    };

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::enable_if_c<b,Ret>)>
    {
        typedef ::boost::enable_if_c<b,Ret> type;
    };

    template <typename Pred, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::lazy_enable_if<Pred,Ret>)>
    {
        typedef ::boost::lazy_enable_if<Pred,Ret> type;
    };

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::lazy_enable_if_c<b,Ret>)>
    {
        typedef ::boost::lazy_enable_if_c<b,Ret> type;
    };

    template <typename Pred, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::disable_if<Pred,Ret>)>
    {
        typedef ::boost::disable_if<Pred,Ret> type;
    };

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::disable_if_c<b,Ret>)>
    {
        typedef ::boost::disable_if_c<b,Ret> type;
    };

    template <typename B, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::lazy_disable_if<B,Ret>)>
    {
        typedef ::boost::lazy_disable_if<B,Ret> type;
    };

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::boost::lazy_disable_if_c<b,Ret>)>
    {
        typedef ::boost::lazy_disable_if_c<b,Ret> type;
    };
}}} // namespace boost::parameter::aux

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS)
#include <type_traits>

namespace boost { namespace parameter { namespace aux {

    template <bool b, typename Ret>
    struct unaryfunptr_return_type<void(*)(::std::enable_if<b,Ret>)>
    {
        typedef ::std::enable_if<b,Ret> type;
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_NO_CXX11_HDR_TYPE_TRAITS
#endif  // BOOST_NO_SFINAE

// A macro that takes a parenthesized C++ type name (T) and transforms it
// into an un-parenthesized type expression equivalent to identity<T>.
#define BOOST_PARAMETER_PARENTHESIZED_RETURN_TYPE(x)                         \
    ::boost::parameter::aux::unaryfunptr_return_type< void(*)x >::type

#endif  // include guard


/* parenthesized_return_type.hpp
7uzMzsybySZv3hwMBoPBYDCOLA6L/e+2u3Lc3nrb/+1FvPkKC2zSi9S9/C8drNTcol9YEKc/4kzU4lTfgF4+Iw33U2Zjjny1Z6TlONQ6ekRY4wxPG/YZPAWuackCeULk2nbk0UeutX9IUdxWh8eu7zao7wFowT6DQ+Te/3atEIpLL4XxvAF6ln7eQN3791to/348P+jTm4se5ktoL4AbLf7rq+n6Wrq+ga5vomsrXSsW//qCnlT/eVT//ZDGkHLIMMTxyPiNFWp/JctDVafyd4SyaiIO5Ud+KH9xRWXlcDzHNgq6wPWeyspKG65px0RZhoupDC3pWfHUBk2oDPN2VS+D2+rMssvtHqksYegS+ehtPZvyWUF1LYTYkc+HMp/LtXwCG1vmkRK6vvp5C+0hlAbDZja7IF2U6LqoXu/8WCGRFOMvTwtwFuIt2U31Dl6e/qOp3u0OsUzqvXi657KqJz+gX+Guz+kVSdr5D60M9zz+eqytqgfiNTDPRf5TUIdOiD+zHGWm+iJapfpsh1//vDdmBOOGofbGHCjnDT045NYXZiT/3GtTwYnijG7vXBByfFPOG+qtvXvo/dYd/zQUtH8IrYdpAB5L84LuAbek9SyptJ5lh5o2Rnsf4D1Bz2kPTgGrWErziz6l9Mto/tBasAX8G80P+h3cCbyO1vWU0DqeP2jdznpwX/AGWp+zETwQ/Cetv9lE623+AmeCS8FZ4M3gkeDtYBd4B9gH3gkeDS4D3wneBR4L3g2+H7wXPAFcAZ4KPgB+Ftw4Rox9GdwEPB/cFLwIHA/+GpwA/hlsBm8GJ4LL5efYry/Ujd5dSEP6agCGDiRamfx6bw1uAj4BvEM+V3sX4R1F6dqCY0nPH8b49bwQ3BK8GNwK/CPYAv4JrOaxBtwJXAzuDP4ZfC74F3Av8K/gvuC14CvAv4EHgn8Hp4PXgRVwCTgT/Ac4C7wePBK8CewC/wX2gUvBo8GbwXeCt4DHgreC7wfvAE8A7wJPFYDJr+cY8MvgBuD54Fjwx+Cm4EJwPOnlshh6J0odS73I7+lepJcLSS8XkV76kF6Gkl5uIr3cTHpRSC/DSC9W0stw0ksG6cVGerGTXjJJL1mkl1tILw7Sy0jSi5P0kkN6cZFeckkvbtKLj/QymvRyH/hZ8Djqfw+A3waPB78PngBeAn4U/Bl4Ivgb8BPgX8CTwTvBU8GNoJtp4Djw0+AW4OngdsHPi5F+hxl/4fwWyFqI6ouILTWJU0q1M2QOfS/d7nhGqP10CzbWvafuMKQPdl5M8pCqM2PGIE7xhsjPjskvRRkgJZCEzUizmecqMhiMfx+if/4f7H+Pz6UaIUfqDIA5Btt8AL2KZ0AS5bpq//z7RhWBZwA4nA6vfgSAPANgpEUAnjwPioEwaXuXwS5R742Q97D2PzPD66Z7pXTPJ4CAswPM4EdknibRgs4SuEVenyk6Igzppc3TWktvMhSNHtWCntNKpmsH++kYacO1FFWIEzro7IGmssyoi14ThMmyog56DRAm8/fpJffb/D1lXohHYwCX0/WIFP/1oIBrha59iK/ZbHFRtNn+qbkYb0nbaf2iJmVzp7rOu2/5t+Ur23QYHbmNp/4WfVNQ/6N+WQA5DjKbGu4q4d8rIQ3cHHwT+GSwlfZHHE62TzbtWZBLNo+X9iLwga8F30W2zkNk2zwFzgVPB9+m5k22zTPgMeBZ4PHg2eDHwC+C88EvgQvBoeeWHMKckmmmes0rwe+2Gr/V+m2p/nvtMuQRbK7J0C38+4zBYDAYDAaDwRDicPj/pbM1IzNLtf4Pv+0/P1FofmnpK/SH6yzP/xPyXPwCJcuH3fbp7D9HBnbjF8az/64=
*/