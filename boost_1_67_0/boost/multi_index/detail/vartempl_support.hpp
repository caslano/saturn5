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