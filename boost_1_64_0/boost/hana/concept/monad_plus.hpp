/*!
@file
Defines `boost::hana::MonadPlus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_MONAD_PLUS_HPP
#define BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

#include <boost/hana/fwd/concept/monad_plus.hpp>

#include <boost/hana/concat.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/empty.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename M>
    struct MonadPlus
        : hana::integral_constant<bool,
            !is_default<concat_impl<typename tag_of<M>::type>>::value &&
            !is_default<empty_impl<typename tag_of<M>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_MONAD_PLUS_HPP

/* monad_plus.hpp
tJjDCs1KK36tbXNjA4mRypTtLt2hMcXXjfOj+qTRk4GWbMMrPGwCbkA2P9GqtobSmsmqkeXZvH9Esy+73aRPgzSoddns4UPGb9MqU6+OnjOQM/iInOPWbUr0Br0t84aCWl9lHSpvqVSUmqhVdTrQYzengT1uH14PAPkEpz7fW9skNCmEuajEB6ZNJ1Lp8fEJYds3tieR9p6fC2jyPxu4F6l5F9UOTtHVXW7ISg5+PnU/QZ7DSJE0ZXSWnP4NzEXcnY2xh1Wmo3nCpz8ue1wSuvPze+49iSFDCXzumaLRuAbeUk5WuDS82oxOAjxoHFuwpgmLis5FeP79AQ9GM2r2ghKgiQch5bjkUqgxv550XORSA8K7yHL8NhYA9l8TSL6fQlC2YB+2q6rmLb3OLDt5z2hscIMbTZVeUf68qqHr11JmsBYE39KlL+cW13uIFJAea8NMgqUYyt8ZrC0THPHqxg6qvPpQQfeN0zl4Fh5QcMYh8lp0Cpf9MAc3vH5XLinVJ5ZGbT2aiDa2lV9xwhMcuIX1wpIA24YT5MRSeGSADSKuGKvUWN6lJfluYA==
*/