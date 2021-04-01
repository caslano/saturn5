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
7FHwn1TxJOHbRO5GgUJS76hDUpvpv/0KepCRjvZp8yVN43wx2q4I9u/WZn+RvQOUX+Rw/g29KZk0qaEsDkUOpmN0lPSVxkDGvHFkfX/jlI1lVyUKNSuUTYfEzu1ifVFSwLVKNRmRy1RjjPxPl6UrcmJ+RFRLQiUfpr7CBPXawUbCG/nm0cspZt7y0HJW9bR4ZmlPVlpoBdk/vYYwG7BIsGILVGhV44Ayot2CGWkAWsgBPJ8Tr87RAjtZ9AMakFXHTGH+xLK1G9walJHfNGmq583TYxeOGetUiF0+bwsgLKl9odUDjB7F4t+pRhPXWK0HjJzXoTYyrLppRnHwnkCL4QkEVjiHumRpraq+1f96IAeGvsJqZgHLHcyE7rdsqT9QkCpBeYApEGLnVag4/HUlIIAdy8qtQSq7P/IMIKYuo9faRByEClBCOsE5ZD7Nq7tf51xT5YclE45vBUWPjUIx0j5Fyn7uhIwTD/uYuA7mNfKsE2xuGuBEDQ3U1qmPX3ilg1oQ6QAot0XXqlM0I0yVXRAXu7myl8+ZYqCTyvMBEA5Wp75s3T7zAvs7tQ==
*/