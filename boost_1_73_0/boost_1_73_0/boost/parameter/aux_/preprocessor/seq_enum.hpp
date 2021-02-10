// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_SEQ_ENUM_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_SEQ_ENUM_HPP

#include <boost/preprocessor/seq/enum.hpp>
#include <boost/config.hpp>
#include <boost/config/workaround.hpp>

#if BOOST_WORKAROUND(__MWERKS__, <= 0x3003)
#include <boost/preprocessor/seq/size.hpp>
// Temporary version of BOOST_PP_SEQ_ENUM
// until Paul M. integrates the workaround.
#define BOOST_PARAMETER_SEQ_ENUM_I(size, seq) \
    BOOST_PP_CAT(BOOST_PP_SEQ_ENUM_, size) seq
#define BOOST_PARAMETER_SEQ_ENUM(seq) \
    BOOST_PARAMETER_SEQ_ENUM_I(BOOST_PP_SEQ_SIZE(seq), seq)
#else
#define BOOST_PARAMETER_SEQ_ENUM(seq) BOOST_PP_SEQ_ENUM(seq)
#endif

#endif  // include guard


/* seq_enum.hpp
x34un+9EqTcKUqb7LYkJfLCdp+LAWwIWGUhq5yjtUN0RUMhx6mF9CvmUaO/bCa5tgRLkaFAg7os7KjAiDmsiMQKRyu2yJ7PQiJa5fBm1IRF4JXiHvtVFHzjqEhTXPWwog9M6yy8n4lXLSzpngy1sDRXX/fZJrHWY4LS7JtJBLu5qVB7DQtuHrg/5pFfyKWGjL/UlkTpu9NaqiNMItuEVQS76tCwNAQmR4bTiIuOmAiK0C4o0pvuJVHqBUf2V6TqYTr73etPXEU60iJzIB+pbYIuOY/xD0VvD6UnELEE+ZTCOPc2B2x4hqjps6JwBo87FKpeEoHFSxuOP2razUtcGRRHwW5tW+0gBG+MIGqhIy/16ckPYdSyLb+9x02myKFaVdzew40n/Ib6RT1QtPj03WYuNhVAsqn1a+tRafJVBAUkqRa662KQAgz+m+EQH8J8kHh+tpWogu1dPxPkIdxwZYRb58x4iJHPs/Xms4pgKOHnn6gJ+uLZXMc0LdtdsRi9mfJSMhUraHT8g7GpkeEssAxFriz2MbNKwNmv++wZsIgjYISJ3phnPQ4Rt94pzNh9qBVZhW66TSPy7pov1Q0a4m5lJbIysKG42Q0iQrJmvYNAyHRQIloAEzNx3JCBKyjxHuAECqHoXOZJjCjDE
*/