/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_extraction_fwd.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * The header contains forward declaration of tools for extracting attribute values
 * from the view.
 */

#ifndef BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace result_of {

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 */
template< typename T, typename DefaultT = T, typename TagT = void >
struct extract_or_default;

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 */
template< typename T, typename TagT = void >
struct extract_or_throw;

/*!
 * \brief A metafunction that allows to acquire the result of the value extraction
 */
template< typename T, typename TagT = void >
struct extract;

} // namespace result_of

/*!
 * \brief Generic attribute value extractor
 */
template< typename T, typename FallbackPolicyT = fallback_to_none, typename TagT = void >
class value_extractor;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_VALUE_EXTRACTION_FWD_HPP_INCLUDED_

/* value_extraction_fwd.hpp
VLKNEpjpVAPVeQK7FF0B/Cjd8qLTO9i7o2qx2vpoz5QVwIvd4iF4yUR5TTaNh5csvoN21AbQOfq1IkHGxwU2VuBTTbfgE0YUFy+z2fDCQiip9tWpr8YxlePgJev1DkbwN/gocbnmWuzGVTbe0x+yJ6uKvW/fAZCAgwQE0mzvydWmP7/35Xs+tXpWFfLdMEE2LHfS2WQS3mj+MUeIrQJspdlWW1999dVdgwAGiYUksSrJb7ln1dUgAMGsAXDTCDAalgVbwzSZtWJ9XVwLlG/ztLcxyhrqGkLdFgejLLajXFWwBLhQsQBQcqJqHIMGo0aVaPfGvgECa60nvPtxdPame7potZaSedXrBNbaXH7rkrRSl9SjK2uW1llK8/rGMavkNBlb03+4z9rfsr1T+Je/RoYXp7/zrw9o3Gxh/KTUnHxCwdehVwF3fu4FvYNXPz2pMNjRAeg0oE7nxAYMcq4kOfwVCGsOMQ1jMq0ubbbaLesgGA8I8E7OtbibOcZqNFWD/eOT7lHw8+lBv9vv/tJf17dRft5BDc392AoS7IcAQY/8Yd/si4LfX3LHZx3RKSzSN+W1GQMiMRqZOBkbDxNwbi1go/fKy+VfwnAF/fOgJD7nMF43BWqNAgcjzFM2K+c6vddyTheHCecEmuIl
*/