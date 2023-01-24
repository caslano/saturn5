/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   bind_output.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains a function object that puts the received value to the bound stream.
 * This is a lightweight alternative to what Boost.Phoenix and Boost.Lambda provides.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/functional/bind.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! The function object that outputs its second operand to the first one
struct output_fun
{
    typedef void result_type;

    template< typename StreamT, typename T >
    void operator() (StreamT& strm, T const& val) const
    {
        strm << val;
    }
};

template< typename StreamT >
BOOST_FORCEINLINE binder1st< output_fun, StreamT& > bind_output(StreamT& strm)
{
    return binder1st< output_fun, StreamT& >(output_fun(), strm);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_BIND_OUTPUT_HPP_INCLUDED_

/* bind_output.hpp
ezVjaT3Spbw8IzWWdRK2bWriJNy8O7ZHoLXhfO1uPxNx4LqDYbGrMRdebJnn1JDuYi7EbPKP+KeRgrJGlc+b/Bjixh0ec5+rozhqCXucZJbyb2ZwfDVpA7ThsWYe0sF0+Do23jrdktpdkpFw4bD5H6nyZ5bfEo2MWBxaN4oySpGbCfKLeflRkIfCZsKmoSpfrWSp+UmTkrq7u9sbrxTCtzY46OLpZjEFW6UCZOjRE8wJRtgD7s+VhpDhZ9cg3cvEhcb/rBKKT7bocv/V3pZYogH15QZRnfX6d77OKqgNBovCpfxAixYopfgCLRQo7t7CjxR3dwvu7pRiLe7Bpbi7BigFgjsEC8FDCBDcA6uz+7A7+3Qf7tznM2fmnu9wRiaaUbZv3L04i4vtpzlLSAG+kyY2e33YCckjFYn2elwpkFmouP9xmHSRxPJSUeRr5FwZ37Izj13+m92/vBTPOfRAT34vSL8TBjvCe1R4lOnFczuEfrYbTRC97KRr1G66HDSsWgw3OcVjW+onJdskF56JUAROqEykMa+Ik2PJkXdhVScspZ0ubRefKugD/R6neco6PMbt9+YPVGBNNA5UKuKLjejwu7QaUko50VmpMorlmiw7hp9NuoLzXmsrQR128gmeKOMOacUk/7gV1tXVL7J4WSmX0kRqlwHQnLtKG69i672eFRrThBwjccapkCmMu6M25+jtw7Ko+9nWWGd1
*/