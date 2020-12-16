// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_COMMON_TYPES_H
#define BOOST_MSM_COMMON_TYPES_H

#include <boost/tuple/tuple.hpp>
#include <boost/msm/common.hpp>

namespace boost { namespace msm { namespace back
{
// used for disable_if
template <int> struct dummy { dummy(int) {} };
// return value for transition handling
typedef enum
{
    HANDLED_FALSE=0,
    HANDLED_TRUE =1,
    HANDLED_GUARD_REJECT=2,
    HANDLED_DEFERRED=4
} HandledEnum;

typedef HandledEnum execute_return;

// source of event provided to RTC algorithm
enum EventSourceEnum
{
    EVENT_SOURCE_DEFAULT=0,
    EVENT_SOURCE_DIRECT=1,
    EVENT_SOURCE_DEFERRED=2,
    EVENT_SOURCE_MSG_QUEUE=4
};

typedef unsigned char EventSource;

}}}

#endif //BOOST_MSM_COMMON_TYPES_H


/* common_types.hpp
LtqkrXEWtQf94JuRs4g3Z6A3/C7PtcgiYmwZm1zPnFZgC/cj22/jG4uI6b9Br7IOkvZbpsZkrzf9JvEogM64Jz8cXyYelHdFNuwRFRk/T44K70Zfpw3nOro8Adnei+2NDFAvU9vRX6mHGEjsC+CP4lry1tXYI/YbZP1XxSZL2HvldGx+d2Ltan6/kxjwAb7DWYjAzqpyLjfBQw5aAf1gJzFiU4z9lApxOkgNW7hwNGsg9Me+aLnIveSQyh+wk9XIHdusyPyMbYbk3iZxstyNTW/mPJXfg1OJt/BXZr88eBR6/Saxp4p9PIcvl6hDifnFdmzvhgnYK3N7k5gRwz7xlyqxXmxmfjn6uQE+u8j3v8M+2MON3Us/i4cRP5ALa7wcPlT8Dv0n4edzavJHqL+mYzM881/oYm/3bubag3yRR+4/xMgTyZP58awL2CthvuHjiRucNYsyfVzKnMnhgYnofCf6CmLbU5A5NWaA+iFMzq9+hg5/gz2+i53AU0Se1SGLAGubIvZXeAl/vBO9TkQXU5DZG9RR8h2bJ4ewPoMf6r7Soci0BznfjG38GvnMpW/qpirjlP7K/PPI8tER8Eh8u5g8zn5/+jVk/BD+iY+GNjEG+iiwlgh1INP4AOILvvYi8YE4W7oP29uOvHzsOGQ8ghiAPeOL5eHY0eP41zx4f60R/ZGDT0bu2C3rTc5MWAfsNwx7Jse/z5pxKXl7FrmBfRHxN2IOOaV8I/qjVqrK+U4kprE3UihsyzjYPDVqhfgcwN+q8Bnmnaky8VPwN2YFfVfeRL670deNyJ9cGmOtX4KHwEP4UCOy+zt93Y9NMWfB7yFsJUCsKb+Ljv88hHqPuMr5hfgLslyL7O/FJ1lTBHrxydH4NrQw+8C5bxOf3mKt9SP8uQW/eIYYc9ZI7JLYhyzFugB7G+zp4pshat3qEuaVQofs8+axxWA3vEo/pJZILx1HjcVYPKeTPgQ9voJOr4QnaBH8IfQO8ZBaoNyDbaxEruSe4L/Q1U+lb6DDB7BdatPgpcisii7yyBvbz++BHcTGMkf8cy3+xpohyFoosoEcgU5if+Ie9m/TC4ex9wpPb8H/WtbUJ40l35AL7pM2T2yjn8II/ELgUzvCG3uMgvxYkWNQK8a+yfrrZObG/qPopoY5jzzwLHIAE+KaeIHP2Esxwv7dbtis5Im/eV56hPj/OnHlbGQn17Fr6V+us4YgZ+rmKjyUyHuV1cyHeJHDpkUBvsnn+Qz1+iPY5CJ8lXlHsHNRRSfU9jnmVDyd8fGHyhjshTOeovTR08nj8Jwm3oo/MG4L47KeDPwE+X8TWyQvlKgpxYno92fEH3iv9jDOYciZmCfYuy0/wX3Sfl+lpdYqEH8K8m92E0PF1VI3rEmJdXmePRDsMeR/jEwZrzKI/HsVsmKvufoCtoFNBrm3lKNOe417b2WOlzay/0ys5p2gAvYYmkp/w8gZrJ9C5NIC94TQjTgb+4rR9/3EG/gTG4gj1H5h+ogRh8I7sr7FR8TbyHwyfbzSyDM12MVt+BB5Nve+/I4V5sA+Q34Eun2aPYgvibnklOBI5DmU9cxc6hPsOIcsIrOoLdP8vgNx6mTamxjjTnRfwY4+J45UG5EFtf35+FYJ7I+Yy7PI4W70yHo+d8BWxCau70heYl8nJ21/KjKYSO0V4udE9LCC+LFyHHOTa0fk3I3+kHF1M36Hf1d/zNqGuFNYhi8txkYuRMcJ/G8n5vEG8Ra55C4cg64nsG7GV9i/yEm7WYfd4ltBYnn+emQo308+jNgl9yyYZ3pv5nETYz6LjH8Ajlggeon9FeLvtvgi+w6xacipgL1/hq9LmzsNm0Le+ZH4wlHUHF0=
*/