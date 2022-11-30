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
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
*/