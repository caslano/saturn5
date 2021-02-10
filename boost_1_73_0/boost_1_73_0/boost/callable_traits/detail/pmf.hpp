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
AUjwhJKibLmUxVPbf1+vV+tGw7Ek9WksFPA7jFaKs5rFoN1NcjK0CuEZ39FJeFvfn72p19/gQGRQKjapKnoViv2tKLR+UazRUQiohWl+npFolZlq/Zx5r69bcYojTPYIQs4lLwHUbMqkNOAKe18XB77Cfqg3ZqInWf9pJh4Okj/VH7AFLMtVr+pdS0JDtCMH80vOv8I7ZodzoKr5ZqwRvbXdvSzgljamMSsblyYO2bk0h2R78mkcZttRK2QjtRV1PvVtv3hf6D1Q3n0q4W7AHUvfSDlaleneb4IlUYE2GMMgZFpHL2iQoS3Fd27yS6v0IwplDNs6EqaHMZ180aE4Q18RPNNp3uwWKLb+37J+j2VtNZAvXnNO2fcWE3nOQLa8WdlPM5Ba/gPFbUm+QvMna7svATaJiGcdktEZfqqRe+GJb7Ej+ZmpAWw0ZumXlBlHaS9dZ0W5hnam8hAfT+4mDfGnNveSvf7hNvs77fb32e4fZb8v2/ATdtznayYNKfkW+1k7NvX9mOY5VKGjQFdJJU9qzC1VphhM0sephEwbfkafP62rHwv/BlBLAwQKAAAACAAtZ0pS1SD2xuIGAADMEQAAMAAJAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvdGhyZWFkZWQtc2hh
*/