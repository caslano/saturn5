/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/capacity.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c capacity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue capacity to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, capacity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

/* capacity.hpp
om/jhtzB+Eqxcq8+31hoYjPMGFqdIkCSDKJUhZ+c1iKOXdxeen4r9PYd2CjixUVnPivz0Uim8MM+dvlPYp9kZkSfBofv9PmIU1Ffhf3WBwL/jGJMeNIdjzhRd3M2ATKKhBHH7vFf0HqWwp0NaXljHh62/J68q6xi89Ct1iLQ1d/ur25JW5DNMvA8Qodt78d4ndGUrsPJaK/NUj4Lbc0/9Vl9bBpC7bsKse16gM3p8+60P9UfxdMkzLmjqGIfXaG4SubIKSSuRPi///WXjkGR3C2qVO/Ni7R9xfmIw6qPJt6Mo8c0i2F9YUK2mfLztKr99CvCJny/HMEiNDPBK/GqOH7bN/VW8r+afPqs8u7DaNpIFvx/l1He2DAKllBKfB+HrlpEEUtQ0ygNCmhkEL0HsJmFTTA2UAlOosU8pA9ax/56zSxRMrrcp1LExvJgamxAXZXoUZ2a7InNabOsXoCQk53ZOyyLkNms49tgPa0YiAafQx04k0OfQnTrgXme2Jx2wiIWs/mqD4kYc2Q3ijOQlnXopAeUxKvI/soZOuR52JV9KTm9GXCUUzQmeySG4Vdk8L65KKetKK8NoyN4WsxC0+n6K6M4Y7yDW9Pb1QtUAs992ydQc0I0/own/Yq/vVfnoKppuPVbT29PxW1Ii4Tqa6DnpzhDYX9gjhPCVG3TFEyign2X6wDyvFha5I14xLeepErRvHknwBqRVbwM
*/