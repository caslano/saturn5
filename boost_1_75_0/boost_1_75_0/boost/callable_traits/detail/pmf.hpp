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
CPkG8VIeaA9fCgAAFtbh6/clWnuAhNazU26/lSihrQQJbSOLevEk5sUTYCyzSvtY/HWzpvWxlKRCV2E0KSTeOYV412AW7zZOi6WmqE+rsDvQ+86rvoqyaSE5r8s7mk1LWSg5dO67LSrKr7NDyAKG4ijoYcgZ6iyel4XsoU2bVf3eKI+7WWgvVia+tb+LFUOdA9/XyihA4UKNscexDKZCCzXgPZbZATdcBjPUh77iMsjNhg7xfXI83LvtdI85yUOFO47hPXLBIX9qi/58wc5j+n2q6T4Zy2Ofn7n3uN7/+ZON+6Xvm8b4dsS4riIgARy2vmOUOV8fVzXW7+N+2rGfSXyPquHQ/hi6x4Q/Ib/N6P8ZXAbjYoV2xhznvo2waXDIxHryE6jMboRbFZdxht6NMfpcP1orT3VadpvG+61xv98Eh2LTfdo3Aib16gm9Tke8asaBeTynadify3gsjdif0dyflNCImIg+LOxLZZqxzJw4uqd578/l00J3x2n9Tw711r+1YP2brVQeQ6eFRsYf1+c3xTS/r5j6n/lXq0W7b/7GeN643bi3bBdjXN5Na9cZOv+tFr0P496KmOscba4/WKY9p7lL5b5J2M/+fO/E+5F8jylEQz2tYh6bLMfNuHHcYuDwFBOeJPO3KXi/jctgBMpQoQlPlK3GWHZrYxm/wViDYb3/6VjPaosB/ykWAfPbLBF4JXCS5nSBxZjT
*/