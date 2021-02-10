/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_to_log.hpp
 * \author Andrey Semashev
 * \date   06.11.2012
 *
 * This header contains a function object that puts the received value to the bound stream using the \c to_log manipulator.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/utility/manipulators/to_log.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that outputs its second operand to the first one
template< typename TagT = void >
struct to_log_fun
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log< TagT >(val);
    }
};

//! The function object that outputs its second operand to the first one
template< >
struct to_log_fun< void >
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << boost::log::to_log(val);
    }
};

template< typename StreamT >
BOOST_FORCEINLINE binder1st< to_log_fun< >, StreamT& > bind_to_log(StreamT& strm)
{
    return binder1st< to_log_fun< >, StreamT& >(to_log_fun< >(), strm);
}

template< typename TagT, typename StreamT >
BOOST_FORCEINLINE binder1st< to_log_fun< TagT >, StreamT& > bind_to_log(StreamT& strm)
{
    return binder1st< to_log_fun< TagT >, StreamT& >(to_log_fun< TagT >(), strm);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_TO_LOG_HPP_INCLUDED_

/* bind_to_log.hpp
18yiMVT6egfm4BKibjlO9SDraSN0wO03jrcyPcicVKZOHUXFvyzEdIzBkwMM9Ck1cmg3lVZLG/UrYD0DJaO3Fhka6bAUD337UjUutOJEIVj/1B3gVH42u4NSBCBsqoMKBjlQ/1wJhDBX7PlpCMr6zIPla6gd35LzZL3DDksd9lTlc+oyxJNZkTem6xl+6E1D7Pv3cmhL0z51Vb3xZI55x4I2eXNpCOegvypFyxBMqLoMBq8mvHgz0JOl4/1SkfA1LMN4jkdiJ9j0fdK7fyuqlIB9zXxlRumlX0/mlHoVUw56gZg0iKdyF7/EN8VEHbO3BvCQumglqIry3ePO/wBQSwMECgAAAAgALWdKUt0L1MawBQAArBgAAB0ACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF9zZXRvcHQuaFVUBQABtkgkYK1ZW3PaOBR+51ecTV6AcaHbmZ3ZNt2dpQ4tTChmsNNuZrvjEbbA2soWY9kk9PLf90jY4RJsc4mT2Fg+37npfEcyuWTTyKdT6HU7192xa96OB65jWQPX7jrWyHF7tUt8zCJaItFuPt9RgyZUHq7+c/HAq0aMYvEf9ZL90q77A1Y/iPqC1yojbVhDfrgNqIb8gLqGuJmVt+qz61YZ+qJ8U6e2Qn5x1UccQZhC
*/