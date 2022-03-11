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