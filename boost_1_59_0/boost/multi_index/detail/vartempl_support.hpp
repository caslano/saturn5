/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_VARTEMPL_SUPPORT_HPP
#define BOOST_MULTI_INDEX_DETAIL_VARTEMPL_SUPPORT_HPP

#if defined(_MSC_VER)
#pragma once
#endif

/* Utilities for emulation of variadic template functions. Variadic packs are
 * replaced by lists of BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS parameters:
 *
 *   - typename... Args            --> BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK
 *   - Args&&... args              --> BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK
 *   - std::forward<Args>(args)... --> BOOST_MULTI_INDEX_FORWARD_PARAM_PACK
 *
 * Forwarding emulated with Boost.Move. A template functions foo_imp
 * defined in such way accepts *exactly* BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS
 * arguments: variable number of arguments is emulated by providing a set of
 * overloads foo forwarding to foo_impl with
 * 
 *   BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL
 *   BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG (initial extra arg)
 *
 * which fill the extra args with boost::multi_index::detail::noarg's.
 * boost::multi_index::detail::vartempl_placement_new works the opposite
 * way: it acceps a full a pointer x to Value and a
 * BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK and forwards to
 * new(x) Value(args) where args is the argument pack after discarding
 * noarg's.
 *
 * Emulation decays to the real thing when the compiler supports variadic
 * templates and move semantics natively.
 */

#include <boost/config.hpp>

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)||\
    defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#include <boost/move/core.hpp>
#include <boost/move/utility.hpp>
#include <boost/preprocessor/arithmetic/add.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/logical/and.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/seq/elem.hpp>

#if !defined(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS)
#define BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS 5
#endif

#define BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK                        \
BOOST_PP_ENUM_PARAMS(                                                \
  BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,typename T)

#define BOOST_MULTI_INDEX_VARTEMPL_ARG(z,n,_)                        \
BOOST_FWD_REF(BOOST_PP_CAT(T,n)) BOOST_PP_CAT(t,n)

#define BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK                        \
BOOST_PP_ENUM(                                                       \
  BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,                             \
  BOOST_MULTI_INDEX_VARTEMPL_ARG,~)

#define BOOST_MULTI_INDEX_VARTEMPL_FORWARD_ARG(z,n,_)                \
boost::forward<BOOST_PP_CAT(T,n)>(BOOST_PP_CAT(t,n))

#define BOOST_MULTI_INDEX_FORWARD_PARAM_PACK                         \
BOOST_PP_ENUM(                                                       \
  BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,                             \
  BOOST_MULTI_INDEX_VARTEMPL_FORWARD_ARG,~)

namespace boost{namespace multi_index{namespace detail{
struct noarg{};
}}}

/* call vartempl function without args */

#define BOOST_MULTI_INDEX_NULL_PARAM_PACK                            \
BOOST_PP_ENUM_PARAMS(                                                \
  BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,                             \
  boost::multi_index::detail::noarg() BOOST_PP_INTERCEPT)

#define BOOST_MULTI_INDEX_TEMPLATE_N(n)                              \
template<BOOST_PP_ENUM_PARAMS(n,typename T)>

#define BOOST_MULTI_INDEX_TEMPLATE_0(n)

#define BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_AUX(z,n,data)        \
BOOST_PP_IF(n,                                                       \
  BOOST_MULTI_INDEX_TEMPLATE_N,                                      \
  BOOST_MULTI_INDEX_TEMPLATE_0)(n)                                   \
BOOST_PP_SEQ_ELEM(0,data) /* ret */                                  \
BOOST_PP_SEQ_ELEM(1,data) /* name_from */ (                          \
  BOOST_PP_ENUM(n,BOOST_MULTI_INDEX_VARTEMPL_ARG,~))                 \
{                                                                    \
  return BOOST_PP_SEQ_ELEM(2,data) /* name_to */ (                   \
    BOOST_PP_ENUM(n,BOOST_MULTI_INDEX_VARTEMPL_FORWARD_ARG,~)        \
    BOOST_PP_COMMA_IF(                                               \
      BOOST_PP_AND(                                                  \
        n,BOOST_PP_SUB(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,n)))    \
    BOOST_PP_ENUM_PARAMS(                                            \
      BOOST_PP_SUB(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,n),         \
      boost::multi_index::detail::noarg() BOOST_PP_INTERCEPT)        \
  );                                                                 \
}

#define BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL(                     \
  ret,name_from,name_to)                                             \
BOOST_PP_REPEAT_FROM_TO(                                             \
  0,BOOST_PP_ADD(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,1),           \
  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_AUX,                       \
  (ret)(name_from)(name_to))

#define BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG_AUX(       \
  z,n,data)                                                          \
BOOST_PP_IF(n,                                                       \
  BOOST_MULTI_INDEX_TEMPLATE_N,                                      \
  BOOST_MULTI_INDEX_TEMPLATE_0)(n)                                   \
BOOST_PP_SEQ_ELEM(0,data) /* ret */                                  \
BOOST_PP_SEQ_ELEM(1,data) /* name_from */ (                          \
  BOOST_PP_SEQ_ELEM(3,data) BOOST_PP_SEQ_ELEM(4,data) /* extra arg */\
  BOOST_PP_COMMA_IF(n)                                               \
  BOOST_PP_ENUM(n,BOOST_MULTI_INDEX_VARTEMPL_ARG,~))                 \
{                                                                    \
  return BOOST_PP_SEQ_ELEM(2,data) /* name_to */ (                   \
    BOOST_PP_SEQ_ELEM(4,data) /* extra_arg_name */                   \
    BOOST_PP_COMMA_IF(n)                                             \
    BOOST_PP_ENUM(n,BOOST_MULTI_INDEX_VARTEMPL_FORWARD_ARG,~)        \
    BOOST_PP_COMMA_IF(                                               \
      BOOST_PP_SUB(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,n))         \
    BOOST_PP_ENUM_PARAMS(                                            \
      BOOST_PP_SUB(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,n),         \
      boost::multi_index::detail::noarg() BOOST_PP_INTERCEPT)        \
  );                                                                 \
}

#define BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG(           \
  ret,name_from,name_to,extra_arg_type,extra_arg_name)               \
BOOST_PP_REPEAT_FROM_TO(                                             \
  0,BOOST_PP_ADD(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,1),           \
  BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG_AUX,             \
  (ret)(name_from)(name_to)(extra_arg_type)(extra_arg_name))

namespace boost{
  
namespace multi_index{
  
namespace detail{

#define BOOST_MULTI_INDEX_VARTEMPL_TO_PLACEMENT_NEW_AUX(z,n,name)    \
template<                                                            \
  typename Value                                                     \
  BOOST_PP_COMMA_IF(n)                                               \
  BOOST_PP_ENUM_PARAMS(n,typename T)                                 \
>                                                                    \
Value* name(                                                         \
  Value* x                                                           \
  BOOST_PP_COMMA_IF(n)                                               \
  BOOST_PP_ENUM(n,BOOST_MULTI_INDEX_VARTEMPL_ARG,~)                  \
  BOOST_PP_COMMA_IF(                                                 \
    BOOST_PP_SUB(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,n))           \
  BOOST_PP_ENUM_PARAMS(                                              \
    BOOST_PP_SUB(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,n),           \
    BOOST_FWD_REF(noarg) BOOST_PP_INTERCEPT))                        \
{                                                                    \
  return new(x) Value(                                               \
    BOOST_PP_ENUM(n,BOOST_MULTI_INDEX_VARTEMPL_FORWARD_ARG,~));      \
}

#define BOOST_MULTI_INDEX_VARTEMPL_TO_PLACEMENT_NEW(name)            \
BOOST_PP_REPEAT_FROM_TO(                                             \
  0,BOOST_PP_ADD(BOOST_MULTI_INDEX_LIMIT_VARTEMPL_ARGS,1),           \
  BOOST_MULTI_INDEX_VARTEMPL_TO_PLACEMENT_NEW_AUX,                   \
  name)

BOOST_MULTI_INDEX_VARTEMPL_TO_PLACEMENT_NEW(vartempl_placement_new)

#undef BOOST_MULTI_INDEX_VARTEMPL_TO_PLACEMENT_NEW_AUX
#undef BOOST_MULTI_INDEX_VARTEMPL_TO_PLACEMENT_NEW

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#else

/* native variadic templates support */

#include <utility>

#define BOOST_MULTI_INDEX_TEMPLATE_PARAM_PACK typename... Args
#define BOOST_MULTI_INDEX_FUNCTION_PARAM_PACK Args&&... args
#define BOOST_MULTI_INDEX_FORWARD_PARAM_PACK  std::forward<Args>(args)...
#define BOOST_MULTI_INDEX_NULL_PARAM_PACK

#define BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL(                     \
  ret,name_from,name_to)                                             \
template<typename... Args> ret name_from(Args&&... args)             \
{                                                                    \
  return name_to(std::forward<Args>(args)...);                       \
}

#define BOOST_MULTI_INDEX_OVERLOADS_TO_VARTEMPL_EXTRA_ARG(           \
  ret,name_from,name_to,extra_arg_type,extra_arg_name)               \
template<typename... Args> ret name_from(                            \
  extra_arg_type extra_arg_name,Args&&... args)                      \
{                                                                    \
  return name_to(extra_arg_name,std::forward<Args>(args)...);        \
}

namespace boost{
  
namespace multi_index{
  
namespace detail{

template<typename Value,typename... Args>
Value* vartempl_placement_new(Value*x,Args&&... args)
{
  return new(x) Value(std::forward<Args>(args)...);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
#endif

/* vartempl_support.hpp
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
*/