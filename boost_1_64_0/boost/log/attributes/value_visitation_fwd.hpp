/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   value_visitation_fwd.hpp
 * \author Andrey Semashev
 * \date   01.03.2008
 *
 * The header contains forward declaration of convenience tools to apply visitors to an attribute value
 * in the view.
 */

#ifndef BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/fallback_policy_fwd.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief The class represents attribute value visitation result
 */
class visitation_result;

/*!
 * \brief Generic attribute value visitor invoker
 */
template< typename T, typename FallbackPolicyT = fallback_to_none >
class value_visitor_invoker;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_ATTRIBUTES_VALUE_VISITATION_FWD_HPP_INCLUDED_

/* value_visitation_fwd.hpp
EXcD5zhUyrrGZJ3fXXakEfeB8kYVmzxnf4Xy090sL+XpKML1o7i2e1pTEvrvUxRuA6W/hFJbeFBZnztD4Y0w5TlkB8p/aWWO97c8dU1yINISR3n8Wyl5bX0RyXW1sxzN0Z4huyVy30tEaxDjWRtqe7f7yfMQXXvxX615ntPIHVzjNu40sc6P/DZo2qjmvvam7n6V7H6/6kppCzfk52t5HrCKxuzLmAd8KOYBd5OfX/BsH29rZXvcOGmrRPOAeSizPJIvJ88rmsjzkLfg7vq+axbkP6brD+V7QLKsBzrtDI/kCyH/HV2/rM5bm1jmoxs0z9iWMWGzZrzSzavWuc9ZU6x1MscaFmR0Y9UOrl8Pa55iLjCL0v+t8hzxC7X3ZRhRZsl1lSCX7bqiOT7pJjfRdbBcFxRXLNfjUnLfGHDaeM3YbibbLvk9aTxsD6K6XAL/n5P7e3LdJMnfCPiG3MdTfAWQ70dldY8snyLX5Q9S+g5B/me6LpTlU2X5G3B3nav3JuSDKfxNyhzTWhdD89zqPsFa9zM0+hBdf5y3WtMfLfOA+br5fqJ7WAFW3QrkdM8sI1jHoFmvFjJP0zgXpdxbOnD7kMf3/mwnj3Ofkd37ptzfkApRp4OojL+jMj8K+Ry6XuAv6//kOdhy1r+FGEfwncbPzD22c8ZazMHk5wpZ/mWSP+AfgHaTC/3bDowf3fzGK3M263zs5BpNnVrmKL24z8v9Wfd8NnG121wmyRpfjm7sjHcfG+6jvJQ1NGv7ol5+ovLeZcr3pGBK6yzD21r9CfK72JTvrx3JLgXhLVOeo6xtfNdqzbO7pjyWctkqcqnucn2tzzWoA+vc+nnIWMJK1j0j1dXpDxPc+8J1rqvi9hsMor7QRCnzSKq/p5RnqVvIjufWvK/qObILskttNUkeT3dK49UMyO92PhMr45s8t65C7aGK8P+N45rPgT8I/wl0fau/vIYh+896lssY8oshn0vXLZXxznqve3G9pj1bnrtXud+fknVzgR3cnuUxSlcv70HOGqf1eSBxg2Zebhk7P3DXbaTo5jKfU3xhipxOp3LVvd+m6vI5xarnhJyunYat1ZSHJn3rrfd1yOnuJwM5fdb9K9a5dRqF94q9grHJLj8jfkP94TfMrTuY8l7M7iQ/SnmGs9ZH1TUavVqCJR/u97tEax9v5z7OJunqokWeps1p5kTxLCfPr6zpWma9x0JGd+9cRmGFK/WqW5d4lduvLKdL2zmuL+s+IPk5JJfGnwbKfXe3Ix3SmsUI1NEaZ9qsehu3cbaUIzzLfq8ISsdaZT44YI3zGxXh0F/L+8D2QBZ/+TnWvfN+x56FYt6vEHsY3m3Pcx8bxlXwYdCehDiek9as4xPiU1JStHu5D2xxyH2kW7fmMEx5P714FokltwpmG6MW78d2yW8UYbCdp/3Yot7GbuX91dKej7vI34+GvBesL9ndbvO2hnWd5FLRN6ua8j62aMprWWUOVpbsFpjFrZ8spvCSsTftFlO+t91JftOVvdAPkWxFW3FrIpfIX7iyvvIG+YsSYTnKbg/ZnTa9rX8M3uq+x67FFvd9at05//J41QV2jv5RnI70c5IJUfpVPKVtlrIvuzHZZdq87WEeSuGNVfeqkl0ppUymkF2QIe/JfoTiKO91D/Mq8rtNiaMblVOosve1I8ndZd2vLNJBf5O/ecocpgWl4xllX2EzshtuK25P8q8UX3vlGfOCs81IeYcc2UUasp7XRn5XmN70Qa+T3xZmsNHQlNP8KbcxWYd9kuwOm972Fz/h7CdKeVajcimt7HsMJrlF2r3EchrvpXir2+w4T17O94TnuB1Ic8PxZBdnK+45rCfFW0Ep634=
*/