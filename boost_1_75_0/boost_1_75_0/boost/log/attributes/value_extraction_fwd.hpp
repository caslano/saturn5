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
+dkfDa9yBBj3LoKZhOEH+4Jxe6u7aF0lViwemUHJL3rY8LMStliOQj3IaXvHmRmkKZzpDaF3XqtixgIyvEMUZepjX9Xgwdp67AllNH8oK/Z9ZZucjvYdKG6+K7jJ88g+Gwwg+MP+N/A5LVSrP90o5uHSbx9GtOXMe8CIoEToK81ApzDFZWwLRqHbtUsJrvHXJgisOC3e1cdDikOA9UGG1akrguGJ7wlvQG2q4k1iE/JVI9Lz4IH6GlPg+A/YJ0PxwPD84jLrmngJJehIPowb6dwLoI9yhoTlnIr45QclmkgR1WWDn9G0QHp6bchlx55KJPETb6P2vOO0Z2JqyOll2bUt/8nVe9UZOdCfkMoIgS7MCZAqKKxZ7BB4aN0YFCnM+kwTmP+c0C1lWgwpA0mpUTwx64QpdGNBjg7J3q9kHIxek523fjItARWCSkEFoBIQR4y7aYRqu1maX9wajsSd7NHggWTBccuGrGYzhyk/27ii2rL7vLtgBu9EVhYNg8BSniqjRhpXtG3bX80NTR82kg9xTVgRri0RGBxd34oWPZZjOUkrOmCkG05dy0pXTMjjFV35jRSwTci5mvJQNhiYgE5ImmQ03Gc5V0B3G8T8+NtwAeCZ2b+SO+Oj/sx3I3Ianr3rznWPLyPLBA9mNSreghkRE9FH8fzsGD1DuFCfdzOZSacpFXHzXkypInxJ2UOu639acztkPtQyWHIY
*/