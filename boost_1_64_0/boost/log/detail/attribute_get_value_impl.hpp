/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_get_value_impl.hpp
 * \author Andrey Semashev
 * \date   04.08.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

inline attribute_value attribute::get_value() const
{
    return m_pImpl->get_value();
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_

/* attribute_get_value_impl.hpp
NlnKRZaN7eV5PdNA76w3F6XzzTINuvf0hPaaTXp4PT1mSA1GLa9NWwXYg/gdKQ/5mLVe3j/cp/O80K1YcnztXTrOt38cZg82xrBtA1NI6v0kRvJEEyMOGhuX/nRa37+jhLo6CGI6McbHlPJkhL30J79FxdMsO3QRf/ji6OamXgSnoXvbw03beyv7PsSNrJq9bkTXllNng4K39L2T9wt0mPxRKw6bBwMvc5hjLHULpP6kT9LdfdAtFfMJ9NLCEkFe/AsSgB3n6rB8QXVhabVj1e4qpPb2+67JO07ov/oMgLzjlVDuqCSJhnN9xgF62ckgmpk8iSrsas8ipgHmeNJuG4Nx+0/JrZkY7O61uVemlpZ2N+RaUGQlfb5HyHjbDM0GmEMFAEaN0yXMJZp4hPLegzGlB+y+m2bGePo9tpKcIt7u8l7128g7VpV68kLf+LOAR36u9dxXr9knUXxcp6xH4aWtb5UZ38deN9rDPOq0QMwF5CBvkrYhSu1isz6AcJuw9AtqtPHXs0tPCgtJS41p1YREVaeLWZkbtWHemjYEK1a9OHh57gkydRPFOg==
*/