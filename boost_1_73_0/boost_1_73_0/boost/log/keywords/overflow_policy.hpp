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
WqpIxajgAvhPqX55Bdo1bBYms+0ar6vEU7JhJLc4aGsMlBzoLbohhyoY899ANOlQ5JW/LTSI4nXIr2OluGNWROox/YkLhMFM4ynWlg5MqQpeTTPg0ta4g6XG0pVdtDglzaLtxqJKrO29KojWgsKmnPt06EDBvxwe/3T4jG/5KVHb7b6T7Y9o9Bs/JBc486lCNF1kg6jpC0dJlmFn0nc0l0YIKrUkvg3VlpQoO11jYIiYm1RVLSxSYH8WKYz9utkt2ud0h4OdduX+6Bf2+vriojvy8BJ1OwSypeheuqbyPbSVORf3q9LgpwFmwvB61mk9CcM7w75kSXEnWs2zMjFZH7A+Lo1cCgDWtrWAUDXnMs+5rOfBUNa4bTlCIq+O+6fP+qbOtwpV1dG5g+Hr4flvtrbVU2cwqOpNAzAwEidAx3B/HbavJ29PvNddsE5GWiaNDkvr7p814dKNgzk4CkI3rQgCWuWwgqWJ9ZfDH6rD5KYfl/eO56Vd3U9+u+paKNza5yV2jgETP64+nFtwcMtgczdv2ietCkN6Xm9NYL0vjvP1YNDtW71l2ygKVoqNdlHx5PBZBSGDSlq6qNAtzmYgJ3QHLsfPDn+stfdRhs80zNZ++tE1M8i4u3bvuRjAZvi11x78VvDfCxhFAXhO
*/