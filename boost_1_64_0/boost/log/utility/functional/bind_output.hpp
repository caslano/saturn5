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
ek3TK7/TItlEj7vd75W5bZNNtoxU5/65mXPY2flmQg307d4GymPTouf+vIrNRAsQK5ZCIhz4gTmEn3+4gzMl6R5hM6V5dGC+7tPojZpb9mbIt/sC+qoqmmoHNFpMDIBlsVMvxt2ZmTLkSH2EBRoNMWW1yYb3roQhnT2hg413vghPvYkJWrXto7dpvYqP+YeMHTw6cQ0jZwTKvcN81ZO+h1FridVlyMZP1ZGljivP7P5PNlgx5RIi/PI1pWguuelmREjxB1BwFxVZeIdUnt+1C0ISQa34rBprZIyS4xu9H8dQml0qzGZb2+WdARK1Ivzxlmb8QcaTD2uvVwqe8nEBRYVYh27AK8ljEQzJRpvPVNkeycqhc+nOUU8R7bQKh7ZXIZxIFofS3VS0kfKfdgwVMQ0ivgPqueNx2L+H2LtCfqErV4w6ZoWF9SJk58euSDF954BtHn8ZFWNPb8bpvjP7nfzIl3aeTOC+rlvIFQsphdmCLR2BOY3yZ88JYAP+j5m2SN1146PhKaiLvP9pffGt359VZwWSEEHzRM6Jqu3nEp7U1k+JhgrteHvpwA==
*/