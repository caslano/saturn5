/*

@Copyright Barrett Adair 2015-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_FUNCTION_HPP
#define BOOST_CLBL_TRTS_DETAIL_FUNCTION_HPP

#include <boost/callable_traits/detail/config.hpp>
#include <boost/callable_traits/detail/qualifier_flags.hpp>
#include <boost/callable_traits/detail/forward_declarations.hpp>
#include <boost/callable_traits/detail/set_function_qualifiers.hpp>
#include <boost/callable_traits/detail/default_callable_traits.hpp>

namespace boost { namespace callable_traits { namespace detail {

template<typename T>
struct function : default_callable_traits<T> {};

#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#ifndef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS volatile
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const volatile
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#ifndef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS &
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS &&
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const &
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const &&
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS volatile &
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS volatile &&
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const volatile &
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#define BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS const volatile &&
#include <boost/callable_traits/detail/unguarded/function.hpp>
#undef BOOST_CLBL_TRTS_INCLUDE_QUALIFIERS

#endif // #ifndef BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
#endif // #ifndef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

// function pointers

#define BOOST_CLBL_TRTS_CC_TAG dummy
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC
#define BOOST_CLBL_TRTS_ST
#include <boost/callable_traits/detail/unguarded/function_ptr.hpp>
#include <boost/callable_traits/detail/unguarded/function_ptr_varargs.hpp>
#undef BOOST_CLBL_TRTS_ST
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC

/* ?
#ifdef BOOST_CLBL_TRTS_ENABLE_CDECL
#define BOOST_CLBL_TRTS_CC_TAG cdecl_tag
#define BOOST_CLBL_TRTS_VARARGS_CC __cdecl
#define BOOST_CLBL_TRTS_CC __cdecl
#define BOOST_CLBL_TRTS_ST
#include <boost/callable_traits/detail/unguarded/function_ptr.hpp>
#undef BOOST_CLBL_TRTS_ST
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif*/

#ifdef BOOST_CLBL_TRTS_ENABLE_STDCALL
#define BOOST_CLBL_TRTS_CC_TAG stdcall_tag
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC __stdcall
#define BOOST_CLBL_TRTS_ST
#include <boost/callable_traits/detail/unguarded/function_ptr.hpp>
#undef BOOST_CLBL_TRTS_ST
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif

#ifdef BOOST_CLBL_TRTS_ENABLE_FASTCALL
#define BOOST_CLBL_TRTS_CC_TAG fastcall_tag
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC __fastcall
#define BOOST_CLBL_TRTS_ST
#include <boost/callable_traits/detail/unguarded/function_ptr.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_ST
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif

#ifdef BOOST_CLBL_TRTS_ENABLE_PASCAL
#define BOOST_CLBL_TRTS_CC_TAG pascal_tag
#define BOOST_CLBL_TRTS_VARARGS_CC BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#define BOOST_CLBL_TRTS_CC
#define BOOST_CLBL_TRTS_ST pascal
#include <boost/callable_traits/detail/unguarded/function_ptr.hpp>
#undef BOOST_CLBL_TRTS_CC
#undef BOOST_CLBL_TRTS_ST
#undef BOOST_CLBL_TRTS_CC_TAG
#undef BOOST_CLBL_TRTS_VARARGS_CC
#endif

template<typename T>
struct function<T&> : std::conditional<function<T>::value,
    function<T>, default_callable_traits<T&>>::type {

    static constexpr const bool value = !std::is_pointer<T>::value;

    using traits = function;
    using base = function<T>;
    using type = T&;
    using remove_varargs = typename base::remove_varargs&;
    using add_varargs = typename base::add_varargs&;

    using remove_member_reference = reference_error;
    using add_member_lvalue_reference = reference_error;
    using add_member_rvalue_reference = reference_error;
    using add_member_const = reference_error;
    using add_member_volatile = reference_error;
    using add_member_cv = reference_error;
    using remove_member_const = reference_error;
    using remove_member_volatile = reference_error;
    using remove_member_cv = reference_error;

    template<typename NewReturn>
    using apply_return = typename base::template apply_return<NewReturn>&;
    
    using clear_args = typename base::clear_args&;
    
    template<typename... NewArgs>
    using push_front = typename base::template push_front<NewArgs...>&;

    template<typename... NewArgs>
    using push_back = typename base::template push_back<NewArgs...>&;

    template<std::size_t Count>
    using pop_back = typename base::template pop_back<Count>&;

    template<std::size_t Count>
    using pop_front = typename base::template pop_front<Count>&;

    template<std::size_t Index, typename... NewArgs>
    using insert_args = typename base::template insert_args<Index, NewArgs...>&;

    template<std::size_t Index, std::size_t Count>
    using remove_args = typename base::template remove_args<Index, Count>&;

    template<std::size_t Index, typename... NewArgs>
    using replace_args = typename base::template replace_args<Index, NewArgs...>&;
};

}}} // namespace boost::callable_traits::detail

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_FUNCTION_HPP

/* function.hpp
uobiFoqtLrwHtoQ7YDe4E/aFu+AAeD8cBH8FR8I9MA/uhQVwH5wN98P58NdwFXwYroePwDvgo3AbPAD3woPwEfgEPAgPwafhk/A1eBiegE/DP8Nn4Cn4LPwCHoF/h0eh0/P+BuPhKdgKfgi7wb/BFPgpnAC/gHnwSzgPnoML4d/hcvgPuAZ+BbfCb+FO+B3cDb+HD8Ef4DPQ8sxXcQD4CnTCN6ALfghD4WewDPwShsFvYVlY1okuhFfA8jAGVoS1YH1YBzaASbAR7AEbw2TYFF4Pm8HRsAXMgAlwEmwNl8D2cBm8ClIvyCztP9U+b0+e9eN3odaLTU7G9cK7YVt4D+wLt8MpcAe8Bd4L98Od8AW4C74G74d/gHvhabgPkhfWflge/hpWhI/B+vBx2BkehL3hE/A6eBimwafhdPhbuAH+Du6AL8H74KvwVXgMfg7fhF/Bt2AY1/Q2jIV/hrXgO7AxfBf2gqdgH/gRvB5+DGdCF/fRauiG6+GnuD8AP4Mfqj3SVWTvAD32NLXPgCGEmw1D4VwYBlfDcnAfjICPwvLwCKwA34KVoINyqQzDYFUYAaNheVgNVoIxsAqsAWvAmjABxsJWMA4mwlowCdaG3WEdmALrwgxYD2bCBjAbNoLjYWOYB5vCAtgMzoLN4a2wBVwDE+A62BJuha3hdpgIH4Zt4DOwLXwOXgWlHlraJwef1vlmV8BCq+hwuov0kwsmwlDYQe3dYBgcDMvCkTAc5sIImA/Lw0WwAlwOK8EtsDLcDatCk44bzR4oJdLB/SLPrYVwOFwEl8DF8F64BB6BS+Eb8Bb4R7gMfgSXQwdxroA14UrYEN4KE8VelI7HTF8G976mo4r00RYdJzzPJfgWbAtPwvbwXdgFvge7wg9hD/gxTId/g2PhaTgJfg5nq301/AJuh2fhHngO/gb+HR6BX+nz82t4Cn4Lv4M/QHSX9ZOWZ7zT214sfQ2Sfk96qqheedfB/Q4/hE3gR/BaOIPrH6j20fBTuB1+Bl+Fn8NT8IzuwXIWtoZfwmHwHLwBfg0XwW/gA/Bb+Aj8Dh6EDs7zLnTCMp77G0ZCN6wCw2AnWBZOgNXhfTAGPgtrwNOwJuTes2JhUxgHW8NacBaMh3thbbgf1odPw4bwedgIvggbw1DP/QW7wWawB2wOF8EE+BBsBZ+EifBt2BZ+ANtBuhOs9jAUdoAV4NUwGvaADdS9qbonwCSYBgfDpXAY3AmHw/thT/gn2Bu+BUfCT2EmjKRcs2AVOBZGw2yYAHNgazgZJsECeC2cCkfCGVrPT5p2P2n7lHpyFb+PQ0v35KkFB8JBMA2mwnQ4HmbAyXAsLITj4DKYDdfDHHgAToCH4CR4Gk6G38E8WEfni/aDBTAfFsLdcC18Fa6HP8Dp0OUk/TAEzoKN4WyYAufCHHgzXA4XwUfhYvgbuAQ+C1fA9+FKiK62boed4SY4GN4Bb4ab4WZ4N3wGboOvwu3wQ8izT/T/vTAK7oI14QMwA+6Gk+EeuBXuhX+FB+A5+Dj8Bh6E1cj/J2AMfBI2hS/AHvAI7AWPwr7wt3AM/B0cC1+DefANOBP+Ec6Gb0LZo8m0Dci9IeXcxlPmWs5x+v5ZB7aE9WA32EDfPxvCAbCRvn82gWmwGRwDm8PxsAUshC3hXJio76Ft4FLYFq6D7eGdsCPcCjvBnbAzfBBeDZ+A3eBTsDt8AfbQ99Fe8E14LXwHXgffhX3gh7A/PAMHwC9hMgzhWq+H0XAIjINDYQs4AnaBN8BucDQcAtNhBsyEY2EWnAmz4VKYC1fAiXATnAy3wEVwG1wMD8Ol8Dl4CzwGl8PfwxXwHbgKvgtvhZ/BtbCM7mVXDm6EJxw=
*/