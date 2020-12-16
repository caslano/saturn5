/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains function object adapters.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Bind provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_HPP_INCLUDED_

#include <boost/type_traits/remove_cv.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
struct make_arg_type
{
    typedef T const& type;
};

template< typename T >
struct make_arg_type< T& >
{
    typedef T& type;
};

} // namespace aux

//! First argument binder
template< typename FunT, typename FirstArgT >
struct binder1st :
    private FunT
{
    typedef typename FunT::result_type result_type;

    binder1st(FunT const& fun, typename aux::make_arg_type< FirstArgT >::type arg) : FunT(fun), m_arg(arg) {}

    result_type operator() () const
    {
        return FunT::operator()(m_arg);
    }

    template< typename T0 >
    result_type operator() (T0 const& arg0) const
    {
        return FunT::operator()(m_arg, arg0);
    }

    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return FunT::operator()(m_arg, arg0, arg1);
    }

private:
    FirstArgT m_arg;
};

//! First argument binder
template< typename FunT, typename FirstArgT >
struct binder1st< FunT&, FirstArgT >
{
    typedef typename remove_cv< FunT >::type::result_type result_type;

    binder1st(FunT& fun, typename aux::make_arg_type< FirstArgT >::type arg) : m_fun(fun), m_arg(arg) {}

    result_type operator() () const
    {
        return m_fun(m_arg);
    }

    template< typename T0 >
    result_type operator() (T0 const& arg0) const
    {
        return m_fun(m_arg, arg0);
    }

    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return m_fun(m_arg, arg0, arg1);
    }

private:
    FunT& m_fun;
    FirstArgT m_arg;
};

template< typename FunT, typename FirstArgT >
BOOST_FORCEINLINE binder1st< FunT, FirstArgT > bind1st(FunT fun, FirstArgT const& arg)
{
    return binder1st< FunT, FirstArgT >(fun, arg);
}

template< typename FunT, typename FirstArgT >
BOOST_FORCEINLINE binder1st< FunT, FirstArgT > bind1st(FunT fun, FirstArgT& arg)
{
    return binder1st< FunT, FirstArgT >(fun, arg);
}

//! Second argument binder
template< typename FunT, typename SecondArgT >
struct binder2nd :
    private FunT
{
    typedef typename FunT::result_type result_type;

    binder2nd(FunT const& fun, typename aux::make_arg_type< SecondArgT >::type arg) : FunT(fun), m_arg(arg) {}

    template< typename T >
    result_type operator() (T const& arg) const
    {
        return FunT::operator()(arg, m_arg);
    }

    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return FunT::operator()(arg0, m_arg, arg1);
    }

private:
    SecondArgT m_arg;
};

//! Second argument binder
template< typename FunT, typename SecondArgT >
struct binder2nd< FunT&, SecondArgT >
{
    typedef typename remove_cv< FunT >::type::result_type result_type;

    binder2nd(FunT& fun, typename aux::make_arg_type< SecondArgT >::type arg) : m_fun(fun), m_arg(arg) {}

    template< typename T >
    result_type operator() (T const& arg) const
    {
        return m_fun(arg, m_arg);
    }

    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return m_fun(arg0, m_arg, arg1);
    }

private:
    FunT& m_fun;
    SecondArgT m_arg;
};

template< typename FunT, typename SecondArgT >
BOOST_FORCEINLINE binder2nd< FunT, SecondArgT > bind2nd(FunT fun, SecondArgT const& arg)
{
    return binder2nd< FunT, SecondArgT >(fun, arg);
}

template< typename FunT, typename SecondArgT >
BOOST_FORCEINLINE binder2nd< FunT, SecondArgT > bind2nd(FunT fun, SecondArgT& arg)
{
    return binder2nd< FunT, SecondArgT >(fun, arg);
}

//! Third argument binder
template< typename FunT, typename ThirdArgT >
struct binder3rd :
    private FunT
{
    typedef typename FunT::result_type result_type;

    binder3rd(FunT const& fun, typename aux::make_arg_type< ThirdArgT >::type arg) : FunT(fun), m_arg(arg) {}

    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return FunT::operator()(arg0, arg1, m_arg);
    }

private:
    ThirdArgT m_arg;
};

//! Third argument binder
template< typename FunT, typename ThirdArgT >
struct binder3rd< FunT&, ThirdArgT >
{
    typedef typename remove_cv< FunT >::type::result_type result_type;

    binder3rd(FunT& fun, typename aux::make_arg_type< ThirdArgT >::type arg) : m_fun(fun), m_arg(arg) {}

    template< typename T0, typename T1 >
    result_type operator() (T0 const& arg0, T1 const& arg1) const
    {
        return m_fun(arg0, arg1, m_arg);
    }

private:
    FunT& m_fun;
    ThirdArgT m_arg;
};

template< typename FunT, typename ThirdArgT >
BOOST_FORCEINLINE binder3rd< FunT, ThirdArgT > bind3rd(FunT fun, ThirdArgT const& arg)
{
    return binder3rd< FunT, ThirdArgT >(fun, arg);
}

template< typename FunT, typename ThirdArgT >
BOOST_FORCEINLINE binder3rd< FunT, ThirdArgT > bind3rd(FunT fun, ThirdArgT& arg)
{
    return binder3rd< FunT, ThirdArgT >(fun, arg);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_HPP_INCLUDED_

/* bind.hpp
b4W8PCg3TrB5FS9bXvKps83r+Ji3d69OtL1Hsjrq2+Yml6ksecWtrTUdl6PeT9k6SOk2vQ9Et2Hv+i+DnfhQVQlQHfUsfGAnzvMNBJ32IE8V2vg8lxu6LERVGhm2sRPjvYt6TRT8+nXk2QX9HVhGMXCThXZugPxMKHui0M5hbXk7L31X9fNR5RDzOnVDGQFCnfohz09o52VcprL0qFF91kN9zqLuqXKorj5PIW+urErjZPQbVkYdLCNZ6JOXNb2XR6p1FFUOxk8+B5vpXo7rjLqC7juQZxfsUdiOyQ1aHgR2NrTHDtD/JOr6hsLnikvAq4/yDkuhunJ3YL7LHj7Smx56O32PdZoPpc+SQnU6/YL85VDedEGvM1yvgGVvqXI9Uxs170Jt1BJ59QW7R7Xn7bdsqyp7qw5fwzEV63Ud69BO8L1LzPf0ZV9D3VtKetv9jLxZQtlbtLJXNFND7aqjiVg281v8a9wVfQJ6DZzT0clthPw5kH+C4Bc3NdnLb6h+4BdBquKnKkFm7TWkKx0LY5AXIPj0+g6aXxw3aifnWvh9HHN+J3OfuAy8j5F3wUNf5t/QHq2FsfFFzOct6BGMegQL99Ffxnx1BN0uc92U5Zvd6qm143Ussx7y6nNfQ16s0H5dO/JxDr6AI9d1dipHsMU4l9gN14GC3jnd6FyyjMsNXfEhjHOm8jrgu0GCvO6Mp/Mh8D/Nhx6GuVP18zbX8Y9dqY4/I6+u0I7NIng7rljkLkvze3zPX2jH95A3Q2jHUi7Lf6XNOV846qiOVhbtOAHX03cJOk5DniroeIvLvfu+V4z80LkP8GSn6r0fvfxVzL/0Y1AVtmsxcBOEueIc8mdB744V2jy6E2/z+xapch3Vz25en/cN/OI6s6PeLypdMmeqst1wDLoGddqJ+n+l6OeLNcgbqnhLbRT9mPMilpMg6O7VmZXju/ILVfZXFQvdu99L1xN9kVdXkBnPZcorD6rBiqo0NJep3EvHGT/kBQgyD7lkZtTk178x8Jl3ulO//onLVFYOM/PrHd3p+HCyOx0fxnfhfn1/JVsHKSEWfq32oPUO6kHHh4tcboP7F5itNZ17hXFo298Kc+lUbMdVUitpPNcf/yIxr7fg26sxbyKUHS2U36wrb/f7B6oBiml9NuP7wUJ9HkdekNDm5Vyecn9ro7qchrrEoH7rRazCfEKPVQZgPi9hXl2K+cYLtrnBy/RftZPbJtDCNj+jHQKFuvxiYJu8bnzsXpWpOhqZrhMGor/sl/VltOpOx50ZWEYWlBEv2CaH8d3XqGd4+fKqMBh3LPtEKcpoLNTpgR4EC4Be3D6rVLNxNBJ1vyiMOW2QN0JWpZbCGjUdy4gX7FHGy/BfvbY29viqJ7XH9Z7UHtK9vK+sHq86jPsKxijQR/4m69t+EMorAW9KFvpKAOb1FOwxHvPmgfxxQvkxvHx5dYga4G1an6KeFN8vRJ6fIO+sJm/VNzDmGdbnANSnBer4jYAzR6C8+kJ/uYvVRW+f6J4UQ4T14OWumYsYIlBV6oCJzOrzei86p32APB+xPi65I9UguymGWIXrhk4Ovl48BLxYlHdAKPcI8hShD92LvHmSXcoR7Diuq2ZHTceevfi+RqrQrxr11PSUVL86ltgvsRfFT1OQFybILNdkrn4f5nNYeUtG9ce6lqCuv/PUl9MeZYYK9pzWldqzD+bLEcq+qZX9wAS1LpTd2BxXxPTm/WCKgCsGIb8MvHayJOD/XprsxjA/qI4w63mvsDed9xYiL0Dwleua3DVX1QAvg7bqj/NeW/Tfx2XeflXAi0TeTmG8bYNlNBOwhUdPii0G9KbYwhPz+QrjZI/efJxcc94MW4Q=
*/