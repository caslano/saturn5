/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fun_ref.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains function object reference adapter. The adapter stores a reference to external
 * function object and forwards all calls to the referred function.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_FUN_REF_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_FUN_REF_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Reference wrapper for function objects
template< typename FunT >
struct function_reference_wrapper
{
    typedef typename FunT::result_type result_type;

    explicit function_reference_wrapper(FunT& fun) : m_Fun(fun) {}

    result_type operator() () const
    {
        return m_Fun();
    }

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
    template< typename... ArgsT >
    result_type operator() (ArgsT const&... args) const
    {
        return m_Fun(args...);
    }
#else
    template< typename T >
    result_type operator() (T const& arg) const
    {
        return m_Fun(arg);
    }

    template< typename T1, typename T2 >
    result_type operator() (T1 const& arg1, T2 const& arg2) const
    {
        return m_Fun(arg1, arg2);
    }
#endif

private:
    FunT& m_Fun;
};

template< typename FunT >
BOOST_FORCEINLINE function_reference_wrapper< FunT > fun_ref(FunT& fun)
{
    return function_reference_wrapper< FunT >(fun);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_FUN_REF_HPP_INCLUDED_

/* fun_ref.hpp
R3cqViVhqTpS+L6mZtbxirpuj8xtk/gy4jR919KT4s3tVNCHVexggxB/ZXfp22br0+Ktfhwc6gvxBkdPhhJX18WMbm0CnMYmXtU/Yy75zxmnpq3FFbj1EyhObqLI2G9UmWslxTG8RfXSyZwGyf8i85eqpH1KKFGFWjKK3avzzSKNQ7RwMEq+1DC5QtoHFVOwbuTpVOV4cLCb59wliSp3KCznXp/XN/aPXvgW8juwywtSIGoeyxMuBTKVHE3LfpP1sJzzyEKaYv2ifvNmUU9trIrjS1yvXReHkKA9OI58M1/2rYmicz4iWitVQNzQJgWyKeIzA304pPLjjKtAJ/bQscXDRNOCxl0RMzXwcEmTdv2g2+Pw8cYUm8fA3Z1z8vXjlfQ+VnEutnZ+W8spNprsZRfIVfd6stXBrzaa1B2LspZZiZDrgzclWP6qhEgoV8FUba1kesPi2TDcnz9g9QdYU6x0OQuS09FI67cY2Jt22uA3ZRHic5Qct/MDnkVAe7BLGDdpNf/HfDZd3ukKH8OevLX52GKVuIRAg/9pq+5PJkDrYGTclkolMDWzjW0teG2z2QkjAGe96tbMbDavDuQRWqdz7gzOE9jsytGavF7LQKk7bKpx8B6HjcQSdMUqMtB7AhtIvtFLrim/BfVbyU6pfbtAQr/hU9RWryOUaL4ZMUljS6/eSQ/85e0E7mJKpKb8sAsHs0CIPl+fv01l
*/