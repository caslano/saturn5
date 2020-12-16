/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/order.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c order keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering predicate to sink frontends
BOOST_PARAMETER_KEYWORD(tag, order)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDER_HPP_INCLUDED_

/* order.hpp
8ztJW1edm+ttTxDR/Aa1VUb+XtJW+ee+l/j3g1q7qfm9pCNMe/X0EGG7O6KYHzoqI39e6qiM/HmpozLy56WOyn/uu4lfb9f1Mb+bZLnXozempkj1luWOfG7Kckeutyx35HrLckeutyz3P/f9xK+3qn7m95Pi9emNN5RI9Vbsju4dpTgK3RVHobviKHRX7P53vKOU9De/o7SE6k/eUiL/btXijvzZscX9576j+PvrqwNC31EW0t5Fhvbqt5Qo55lFtnbnhX9PgTe6Z6BF7sjfUxa5u/c9Je8PvKf4+9uTqeb3lJVm+avOFunz08oo+ttK91/zrmKlm99VOhzbqx9HImpzhzuKZ5Eo+1qH++99Vxk/0PyuklIVXnYM1Yhkl1IV+fNASlV0skup+nvfVToGmt9Vcp1lJ28rkY213Krue1dZB7a7ovd7NPuzOfk9Ru/n9rxaj3RDv+t2Lr80ec/Ro8qG3vP829s5+3Oa/TCd/QzNfonRr/8x+086+Q1G77dp9hd18ud09p9U56T7bVTy29tqPydd1tH4cFswAxwD+tOVS7rhhnS7SLpCcBg4wZauNUy6fElXIOl2tKVrC5NuL0m3t6Tb15auQ9L1N6TbStJtDfYDR+p08l0RzDSkK5Z0B4CDwMm2dIWVTuWBkm5LKW+YXZ6SLt2QbqCkywDVmlOdjj/CpNtc0mVJuiG2dIskXYohXX9JNwDcFEy166HSub94JN3R0l+8dj1UOuvvVEk3W/R3ui1dlts53SxJd5ykO9GWrjhMurMl3TxJ12qXp9tZfzMkXa3or84uT7dzf5kv6S6S/nKxLd3KMOVNlXTTpLzpdnm6nfV+uKQrFb0fYe/XVc7pKiRdpaRz63RQlXN/OUjSHSz95RCwNMH6W3yOzf7Gob7GqyCTj7HZv9juU9y9/sR2X2K7H7Hdh9juP5x+gN1n2NlfeD4U4icc4iNs8g82+Qab/YLFHzgiX+BgP2BnH2Dt/2v3/cXvF9S+vgF+vkE+vtH795p9e538ekP8ecWX1+THG+TDG6X/7vr8dRcE+uj+Yf/cSHxzl0BdvrhGP1y7D672v13DuqnkYsY7VAW1Qkuhj6DEAziLEiqH5kJLoNVQ4mTioVJoLrQYWgUlHBjz542FWIiFWIiFWIiFWIiFWOju8Ff5/zfVj/YtAPhD/v9bW8l9BvPRIjnHxXds3yf1SV6OM9unetaufE2vqWzGWNpUfXSZ18t3TXiHp/ONSPNOruZUqxrOI4N/7yqwZmpNdaM/wRjJ+ybN78t2WmN1tU5nS+SeThpVnxED8XcJLUOfmUQuZRXNM6lPZ/4Jo8LzSnU0/16af1JjzTR25vM2NBY3V9bWuG3chDHS3nkG/q6KT/IJS2pv6fp/NMq5zfVTG3T9b+XDVvo2YXl1jYZJfU7o4t99n1Cxqzq8Qb4ddj5jlshEeAu39fMWVzQ1HdvQWGVMoPvL4m0D+ouROVtk0aF5Q2UwTGSQmGvmEblqvrmab/f6Y6prGzyy552WkbQncbTwydZ4QWxall7FF3qspb297fCt0Xy7NtNgRO6uCOLVeS4c4+f1DbPG6qamQMbB8K1NZc8Nxae28qyeWtFc6/XdlLpdUUAbtuvKp96rpVZV6a2shU3Ld4WZD+mSl+jrIxOPra9vLXUakefn0+O/qexAbGxlNd7qOphtvFNMvAerrQ793Lr8uXk2/VbXeLxNezQ21Gn1atmtCOabXH10M/rr6lPSX7cP4rO1JVvyatU8B6r51NZkPRes0Tx7NzU1VzfuWl91IC2oqN2/ua6ya0xp/pyxAf1+QnUjg0/1hT0aGusqdDW2lv7q0fw21gnTG2rcyIrW28dUh58=
*/