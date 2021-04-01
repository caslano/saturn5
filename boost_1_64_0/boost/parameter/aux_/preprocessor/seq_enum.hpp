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
7IhYxsKBoH21s7R8HhDvf38kO5paxKnFbUuOk9cQViHSd47stY89atStpRJ8o/lwmhlFwDynbQR8doGfK8LpMexU1lPw4bVfPRJWid/Bl5IvBOmK9fqhSy+V3sv3aVGqW1CI9ASFoYmtBLvOHJEx9bRsK66Nnv75UXxNVeSQ+aSAPoyjUDg07zlyNWW71GpAM6rOFlh+JsbNZgUJdsCqbxJE1tOWWc9M6fP4kdoSJIYqaPDyJT8X8kiGZdyZ20bs9Xop6sd/wnpMhK0zsHlW3+IrDjhk+qpRBJNn8aC+ErW7drHGYnxjJAiTiG88C3Ef6gAkx1mdze820E8Nl7tCPdr6eyMFizfQnl276CMREYxl47vjQPimW30MGWgTDfmJzK3jn9sJqu8pmh7YZ6+OpD6veSKXu/atZXXy7LlDXzD0jRwsrLBrh3n64CVfSjvn7rwiM4/5f2ZqoNLeugPnvij8n88etA6x8w/sq4j/IliyXrr95bBFdfY3xYFNbjgkTkeBRVjCCGVak76xEdksnsx/yuJWQvm/KqQM4HjrYhFXCCmrc9zkWvNwQA==
*/