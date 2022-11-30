/*
  Author: Frank Mori Hess <fmhess@users.sourceforge.net>
  Begin: 2007-01-23
*/
// Copyright Frank Mori Hess 2007-2008
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_SIGNALS2_SIGNALS_COMMON_MACROS_HPP
#define BOOST_SIGNALS2_SIGNALS_COMMON_MACROS_HPP

#include <boost/config.hpp>

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES

#ifndef BOOST_SIGNALS2_MAX_ARGS
#define BOOST_SIGNALS2_MAX_ARGS 9
#endif

// signaln
#define BOOST_SIGNALS2_SIGNAL_CLASS_NAME(arity) BOOST_PP_CAT(signal, arity)
// weak_signaln
#define BOOST_SIGNALS2_WEAK_SIGNAL_CLASS_NAME(arity) BOOST_PP_CAT(weak_, BOOST_SIGNALS2_SIGNAL_CLASS_NAME(arity))
// signaln_impl
#define BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(arity) BOOST_PP_CAT(BOOST_SIGNALS2_SIGNAL_CLASS_NAME(arity), _impl)
// argn
#define BOOST_SIGNALS2_SIGNATURE_ARG_NAME(z, n, data) BOOST_PP_CAT(arg, BOOST_PP_INC(n))
// Tn argn
#define BOOST_SIGNALS2_SIGNATURE_FULL_ARG(z, n, data) \
  BOOST_PP_CAT(T, BOOST_PP_INC(n)) BOOST_SIGNALS2_SIGNATURE_ARG_NAME(~, n, ~)
// T1 arg1, T2 arg2, ..., Tn argn
#define BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(arity) \
  BOOST_PP_ENUM(arity, BOOST_SIGNALS2_SIGNATURE_FULL_ARG, ~)
// arg1, arg2, ..., argn
#define BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(arity) BOOST_PP_ENUM(arity, BOOST_SIGNALS2_SIGNATURE_ARG_NAME, ~)
// T1, T2, ..., TN
#define BOOST_SIGNALS2_ARGS_TEMPLATE_INSTANTIATION(arity) \
  BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(arity), T)
// R (T1, T2, ..., TN)
#define BOOST_SIGNALS2_SIGNATURE_FUNCTION_TYPE(arity) \
  R ( BOOST_SIGNALS2_ARGS_TEMPLATE_INSTANTIATION(arity) )
// typename prefixR, typename prefixT1, typename prefixT2, ..., typename prefixTN
#define BOOST_SIGNALS2_PREFIXED_SIGNATURE_TEMPLATE_DECL(arity, prefix) \
  typename BOOST_PP_CAT(prefix, R) BOOST_PP_COMMA_IF(arity) \
  BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(arity), typename BOOST_PP_CAT(prefix, T))
// typename R, typename T1, typename T2, ..., typename TN
#define BOOST_SIGNALS2_SIGNATURE_TEMPLATE_DECL(arity) \
  typename R BOOST_PP_COMMA_IF(arity) \
  BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(arity), typename T)
// typename prefixT1, typename prefixT2, ..., typename prefixTN
#define BOOST_SIGNALS2_PREFIXED_ARGS_TEMPLATE_DECL(arity, prefix) \
  BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(arity), typename BOOST_PP_CAT(prefix, T))
// typename T1, typename T2, ..., typename TN
#define BOOST_SIGNALS2_ARGS_TEMPLATE_DECL(arity) \
  BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(arity), typename T)
// prefixR, prefixT1, prefixT2, ..., prefixTN
#define BOOST_SIGNALS2_PREFIXED_SIGNATURE_TEMPLATE_INSTANTIATION(arity, prefix) \
  BOOST_PP_CAT(prefix, R) BOOST_PP_COMMA_IF(arity) BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(arity), BOOST_PP_CAT(prefix, T))
// R, T1, T2, ..., TN
#define BOOST_SIGNALS2_SIGNATURE_TEMPLATE_INSTANTIATION(arity) \
  R BOOST_PP_COMMA_IF(arity) BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(arity), T)
// boost::functionN<R, T1, T2, ..., TN>
#define BOOST_SIGNALS2_FUNCTION_N_DECL(arity) BOOST_PP_CAT(boost::function, arity)<\
  BOOST_SIGNALS2_SIGNATURE_TEMPLATE_INSTANTIATION(arity) >
// R, const boost::signals2::connection&, T1, T2, ..., TN
#define BOOST_SIGNALS2_EXT_SLOT_TEMPLATE_INSTANTIATION(arity) \
  R, const boost::signals2::connection&  BOOST_PP_COMMA_IF(arity) \
  BOOST_PP_ENUM_SHIFTED_PARAMS(BOOST_PP_INC(arity), T)
// boost::functionN<R, const boost::signals2::connection &, T1, T2, ..., TN>
#define BOOST_SIGNALS2_EXT_FUNCTION_N_DECL(arity) BOOST_PP_CAT(boost::function, BOOST_PP_INC(arity))<\
  BOOST_SIGNALS2_EXT_SLOT_TEMPLATE_INSTANTIATION(arity) >
// slotN
#define BOOST_SIGNALS2_SLOT_CLASS_NAME(arity) BOOST_PP_CAT(slot, arity)
// slotN+1<R, const connection &, T1, T2, ..., TN, extended_slot_function_type>
#define BOOST_SIGNALS2_EXTENDED_SLOT_TYPE(arity) \
  BOOST_SIGNALS2_SLOT_CLASS_NAME(BOOST_PP_INC(arity))< \
  BOOST_SIGNALS2_EXT_SLOT_TEMPLATE_INSTANTIATION(arity), \
  extended_slot_function_type>
// bound_extended_slot_functionN
#define BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_N(arity) BOOST_PP_CAT(bound_extended_slot_function, arity)
// bound_extended_slot_function_helperN
#define BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_INVOKER_N(arity) BOOST_PP_CAT(bound_extended_slot_function_invoker, arity)
// typename function_traits<Signature>::argn_type
#define BOOST_SIGNALS2_SIGNATURE_TO_ARGN_TYPE(z, n, Signature) \
  BOOST_PP_CAT(BOOST_PP_CAT(typename function_traits<Signature>::arg, BOOST_PP_INC(n)), _type)
// typename function_traits<Signature>::result_type,
// typename function_traits<Signature>::arg1_type,
// typename function_traits<Signature>::arg2_type,
// ...,
// typename function_traits<Signature>::argn_type
#define BOOST_SIGNALS2_PORTABLE_SIGNATURE(arity, Signature) \
  typename function_traits<Signature>::result_type \
  BOOST_PP_COMMA_IF(arity) BOOST_PP_ENUM(arity, BOOST_SIGNALS2_SIGNATURE_TO_ARGN_TYPE, Signature)
// prefixTn & argn
#define BOOST_SIGNALS2_PREFIXED_FULL_REF_ARG(z, n, prefix) \
  BOOST_PP_CAT(BOOST_PP_CAT(prefix, T), BOOST_PP_INC(n)) & BOOST_SIGNALS2_SIGNATURE_ARG_NAME(~, n, ~)
// prefixT1 & arg1, prefixT2 & arg2, ..., prefixTn & argn
#define BOOST_SIGNALS2_PREFIXED_FULL_REF_ARGS(arity, prefix) \
  BOOST_PP_ENUM(arity, BOOST_SIGNALS2_PREFIXED_FULL_REF_ARG, prefix)
// Tn & argn
#define BOOST_SIGNALS2_FULL_CREF_ARG(z, n, data) \
  const BOOST_PP_CAT(T, BOOST_PP_INC(n)) & BOOST_SIGNALS2_SIGNATURE_ARG_NAME(~, n, ~)
// const T1 & arg1, const T2 & arg2, ..., const Tn & argn
#define BOOST_SIGNALS2_FULL_FORWARD_ARGS(arity) \
  BOOST_PP_ENUM(arity, BOOST_SIGNALS2_FULL_CREF_ARG, ~)
#define BOOST_SIGNALS2_FORWARDED_ARGS(arity) \
  BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(arity)
// preprocessed_arg_typeN
#define BOOST_SIGNALS2_PREPROCESSED_ARG_N_TYPE_CLASS_NAME(arity) BOOST_PP_CAT(preprocessed_arg_type, arity)

// typename R, typename T1, typename T2, ..., typename TN, typename SlotFunction
#define BOOST_SIGNALS2_SLOT_TEMPLATE_SPECIALIZATION_DECL(arity) \
  BOOST_SIGNALS2_SIGNATURE_TEMPLATE_DECL(arity), \
  typename SlotFunction
#define BOOST_SIGNALS2_SLOT_TEMPLATE_SPECIALIZATION

// typename R, typename T1, typename T2, ..., typename TN, typename Combiner, ...
#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_DECL(arity) \
  BOOST_SIGNALS2_SIGNATURE_TEMPLATE_DECL(arity), \
  typename Combiner, \
  typename Group, \
  typename GroupCompare, \
  typename SlotFunction, \
  typename ExtendedSlotFunction, \
  typename Mutex
// typename R, typename T1, typename T2, ..., typename TN, typename Combiner = optional_last_value<R>, ...
#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_DEFAULTED_DECL(arity) \
  BOOST_SIGNALS2_SIGNATURE_TEMPLATE_DECL(arity), \
  typename Combiner = optional_last_value<R>, \
  typename Group = int, \
  typename GroupCompare = std::less<Group>, \
  typename SlotFunction = BOOST_SIGNALS2_FUNCTION_N_DECL(arity), \
  typename ExtendedSlotFunction = BOOST_SIGNALS2_EXT_FUNCTION_N_DECL(arity), \
  typename Mutex = signals2::mutex
#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION_DECL(arity) BOOST_SIGNALS2_SIGNAL_TEMPLATE_DECL(arity)
#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION

#define BOOST_SIGNALS2_STD_FUNCTIONAL_BASE std_functional_base

#define BOOST_SIGNALS2_PP_COMMA_IF(arity) BOOST_PP_COMMA_IF(arity)

#else // BOOST_NO_CXX11_VARIADIC_TEMPLATES

#define BOOST_SIGNALS2_SIGNAL_CLASS_NAME(arity) signal
#define BOOST_SIGNALS2_WEAK_SIGNAL_CLASS_NAME(arity) weak_signal
#define BOOST_SIGNALS2_SIGNAL_IMPL_CLASS_NAME(arity) signal_impl
#define BOOST_SIGNALS2_SIGNATURE_TEMPLATE_DECL(arity) typename Signature
#define BOOST_SIGNALS2_ARGS_TEMPLATE_INSTANTIATION(arity) Args...
#define BOOST_SIGNALS2_SIGNATURE_TEMPLATE_INSTANTIATION(arity) R (Args...)
#define BOOST_SIGNALS2_SIGNATURE_FUNCTION_TYPE(arity) R (Args...)
#define BOOST_SIGNALS2_ARGS_TEMPLATE_DECL(arity) typename ... Args
#define BOOST_SIGNALS2_FULL_FORWARD_ARGS(arity) Args && ... args
#define BOOST_SIGNALS2_FORWARDED_ARGS(arity) std::forward<Args>(args)...
#define BOOST_SIGNALS2_SLOT_CLASS_NAME(arity) slot
#define BOOST_SIGNALS2_EXTENDED_SLOT_TYPE(arity) slot<R (const connection &, Args...), extended_slot_function_type>
#define BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_N(arity) bound_extended_slot_function
#define BOOST_SIGNALS2_BOUND_EXTENDED_SLOT_FUNCTION_INVOKER_N(arity) bound_extended_slot_function_invoker
#define BOOST_SIGNALS2_FUNCTION_N_DECL(arity) boost::function<Signature>
#define BOOST_SIGNALS2_PREFIXED_SIGNATURE_TEMPLATE_DECL(arity, prefix) typename prefixSignature
#define BOOST_SIGNALS2_PREFIXED_SIGNATURE_TEMPLATE_INSTANTIATION(arity, prefix) prefixSignature
#define BOOST_SIGNALS2_SIGNATURE_FULL_ARGS(arity) Args ... args
#define BOOST_SIGNALS2_SIGNATURE_ARG_NAMES(arity) args...
#define BOOST_SIGNALS2_PORTABLE_SIGNATURE(arity, Signature) Signature

#define BOOST_SIGNALS2_SLOT_TEMPLATE_SPECIALIZATION_DECL(arity) \
  typename SlotFunction, \
  typename R, \
  typename ... Args
#define BOOST_SIGNALS2_SLOT_TEMPLATE_SPECIALIZATION \
  <R (Args...), SlotFunction>

#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_DECL(arity) \
  typename Signature, \
  typename Combiner, \
  typename Group, \
  typename GroupCompare, \
  typename SlotFunction, \
  typename ExtendedSlotFunction, \
  typename Mutex
#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_DEFAULTED_DECL(arity) \
  typename Signature, \
  typename Combiner = optional_last_value<typename boost::function_traits<Signature>::result_type>, \
  typename Group = int, \
  typename GroupCompare = std::less<Group>, \
  typename SlotFunction = boost::function<Signature>, \
  typename ExtendedSlotFunction = typename detail::variadic_extended_signature<Signature>::function_type, \
  typename Mutex = signals2::mutex
#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION_DECL(arity) \
  typename Combiner, \
  typename Group, \
  typename GroupCompare, \
  typename SlotFunction, \
  typename ExtendedSlotFunction, \
  typename Mutex, \
  typename R, \
  typename ... Args
#define BOOST_SIGNALS2_SIGNAL_TEMPLATE_SPECIALIZATION <\
  R (Args...), \
  Combiner, \
  Group, \
  GroupCompare, \
  SlotFunction, \
  ExtendedSlotFunction, \
  Mutex>

#define BOOST_SIGNALS2_STD_FUNCTIONAL_BASE \
  std_functional_base<Args...>

#define BOOST_SIGNALS2_PP_COMMA_IF(arity) ,

#endif // BOOST_NO_CXX11_VARIADIC_TEMPLATES

#endif // BOOST_SIGNALS2_SIGNALS_COMMON_MACROS_HPP

/* signals_common_macros.hpp
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
*/