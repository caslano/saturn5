/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_PMF_HPP
#define BOOST_CLBL_TRTS_DETAIL_PMF_HPP

#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/set_function_qualifiers.hpp>
#include <boost/callable_traits/detail/qualifier_flags.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>
#include <boost/callable_traits/detail/utility.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<qualifier_flags Applied, bool IsTransactionSafe, bool IsNoExcept,
    typename CallingConvention, typename T, typename Return,
    typename... Args>
struct set_member_function_qualifiers_t;

template<qualifier_flags Applied, bool IsTransactionSafe, bool IsNoexcept,
    typename CallingConvention, typename T, typename Return,
    typename... Args>
struct set_varargs_member_function_qualifiers_t;

template<qualifier_flags Flags, bool IsTransactionSafe, bool IsNoexcept,
    typename... Ts>
using set_member_function_qualifiers =
    typename set_member_function_qualifiers_t<Flags, IsTransactionSafe,
        IsNoexcept, Ts...>::type;

template<qualifier_flags Flags, bool IsTransactionSafe, bool IsNoexcept,
    typename... Ts>
using set_varargs_member_function_qualifiers =
    typename set_varargs_member_function_qualifiers_t<Flags,
        IsTransactionSafe, IsNoexcept, Ts...>::type;

template<typename T>
struct pmf : default_callable_traits<T> {};

#define BOOST_CLBL_TRTS_CC_TAG dummy
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC
#include <boost/callable_traits/detail/unguarded/pmf.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC

#define BOOST_CLBL_TRTS_CC_TAG dummy
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC
#include <boost/callable_traits/detail/unguarded/pmf_varargs.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC

#ifdef BOOST_CLBL_TRTS_ENABLE_CDECL
#define BOOST_CLBL_TRTS_CC_TAG cdecl_tag
#define BOOST_CLBL_TRTS_VARARGS_CC __cdecl
#define BOOST_CLBL_TRTS_CC __cdecl
#include <boost/callable_traits/detail/unguarded/pmf.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_CDECL

// Defining this macro enables undocumented features, likely broken.
// Too much work to maintain, but knock yourself out
#ifdef BOOST_CLBL_TRTS_ENABLE_STDCALL
#define BOOST_CLBL_TRTS_CC_TAG stdcall_tag
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC __stdcall
#include <boost/callable_traits/detail/unguarded/pmf.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_STDCALL

// Defining this macro enables undocumented features, likely broken.
// Too much work to officially maintain, but knock yourself out
#ifdef BOOST_CLBL_TRTS_ENABLE_FASTCALL
#define BOOST_CLBL_TRTS_CC_TAG fastcall_tag
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC __fastcall
#include <boost/callable_traits/detail/unguarded/pmf.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_FASTCALL

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_PMF_HPP

/* pmf.hpp
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
*/