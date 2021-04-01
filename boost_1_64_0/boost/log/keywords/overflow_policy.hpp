/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/overflow_policy.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c overflow_policy keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue overflow policy to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, overflow_policy)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_OVERFLOW_POLICY_HPP_INCLUDED_

/* overflow_policy.hpp
TDduE2rqEYxfU0WQQ7By1gdmZyDk8Z1mSya5QR/jwBr7KVKuCjQ0p8gUz0my/H+BTEkiUQQgko9zrnxyK7YA0YZKj/DISO4vv6JZvxvRVlnvA8Ee/XxQ1q0APFeBe1i4vDZ1yq1uzzas5w5Yw2Xo129/4NcfeQp2tGaNvncJIlB3s/IR4etpmPHCdeGvFxKVFvDyT3tqL4yc1CQTTbNBsxq5D3yi0A/RQkg/D9rd6iXn9tX042SZ19gKUc8y6vc6rfsOcjTx2rM5LrLcsjoqbKXs8r3E3XOA/c2RQ1QSVScoNnZMhytCPnkpQFxDy1sGD4o+7CGWk2rNFO1XBeZpO9v9mk6EOSTV5NbmWk6ao8nFXz5E6nkRVSRfOVjoHjWfWHsNtFY6kZFiNkUC1XSCneufTqKdiBwUNgAKwGUPogvqBWXXLjjJrtrL5lusrkRuVuYTBkkr+biLPK0uqJ1iQBnBx/OWKaxwZjI5Up5D9Nbe85MLCg/jEDKdmOLiQJOMlKHDMuqsFYTw29b6WUOtNDakSNQWCwgDYPX+xTrCzM4OIci+8JH/G55maQ==
*/