/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_PERFECT_FWD_HPP
#define BOOST_FLYWEIGHT_DETAIL_PERFECT_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

/* C++03-compatible implementation of perfect forwarding.
 * Usage:
 *
 *  # define NAME ...
 *  # define BODY(args) {...BOOST_FLYWEIGHT_FORWARD(args)...}
 *  BOOST_FLYWEIGHT_PERFECT_FWD(name,body)
 *
 * where NAME includes the return type and qualifiers (if any) and BODY(args)
 * is expected to fo the forwarding through BOOST_FLYWEIGHT_FORWARD(args).
 *
 * In compilers capable of perfect forwarding, the real thing is provided
 * (just one variadic args overload is generated). Otherwise the machinery
 * generates n+1 overloads, if rvalue refs are supported, or else 2^(n+1)-1
 * overloads accepting any combination of lvalue refs and const lvalue refs,
 * up to BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS args.
 *
 * BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) is a variation omitting the
 * overloads with zero args --when perfect forwarding is available, this second
 * macro is exactly the same as the original. 
 */

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/seq/seq.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#include <utility>
#endif

#define BOOST_FLYWEIGHT_FORWARD_FORWARD_AUX(z,n,_) \
std::forward<BOOST_PP_CAT(T,n)>(BOOST_PP_CAT(t,n))

#define BOOST_FLYWEIGHT_FORWARD_FORWARD(n) \
BOOST_PP_ENUM(n,BOOST_FLYWEIGHT_FORWARD_FORWARD_AUX,~)

#define BOOST_FLYWEIGHT_FORWARD_ENUM(n) BOOST_PP_ENUM_PARAMS(n,t)

#define BOOST_FLYWEIGHT_FORWARD_PASS(arg) arg

#define BOOST_FLYWEIGHT_FORWARD(args)\
BOOST_PP_CAT(BOOST_FLYWEIGHT_FORWARD_,BOOST_PP_SEQ_HEAD(args))( \
BOOST_PP_SEQ_HEAD(BOOST_PP_SEQ_TAIL(args)))

#if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)||\
    defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

#if !defined(BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS)
#define BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS 5
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS<0
#error BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS must be >=0
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS<=5
#include <boost/flyweight/detail/pp_perfect_fwd.hpp>
#else
#include <boost/flyweight/detail/dyn_perfect_fwd.hpp>
#endif

#else

/* real perfect forwarding */

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body) \
template<typename... Args>name(Args&&... args) \
body((PASS)(std::forward<Args>(args)...))

#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS  \
BOOST_FLYWEIGHT_PERFECT_FWD

#endif
#endif

/* perfect_fwd.hpp
Ar//2sXufVSKf8DBfy9vHf/gSlv6HrL/4aheLh9y/80SC0F93JSg5pcpYT1dQ4W4n6vfim3Ntw8QkELH3LRI1pd2IfBXlItgvv6tiWm+PtzxqN31ZXMT1f7tXLEdf/SPmOu7vWOp9kK/JBvtbxpUMr7Pwner9Y/q0g61Vc9/TtoZr1815gE32vLzn042zmPWcKBO+EnI85/vS64P71cgfyb7N47qzA/FrP4KnWzo57OY/quxVM2w3REpCVL43swjXStBLPm2bh/fDn8u3S5KNbs7acZ2TB0K76AT+fjT4mDh1Mkna9d1eKO2BI9JhYR+5e6zWFqs/egZ1iJ/r4PyA/dYZBYm8cz+FpnrcnlmlkVm9USeWc0iM6sWZUonUnMGAgc+/ns5/M7Fv/x9Ffzuht89l/BHGS+TGsooBplo5/pdcRBaugZok7TkdBvjLZvgtUe/Vcbb4G+LI4nvgE2FUUqZ+7KOOEpAPKjEUkWIPw+F/cO8FPCFbshL4eH/ipx21xdlvKaw+a+BPE/MoLt/3JNdYRxFJEyFMRmdNqV9mnvsYO/QaByM3mI2GD1pymBMRUoCbfXHpvpjXf0xRX9MFI/CpXLKO0m1HB/Ures4zH+3wu9X+Je/n4Tfc3UvbnxQ103LoK7bH6Dvu4U+C9rxD9iVg7ePDXUG2JzYIm2LW77ko2YlD99IusvWAg0uxIqO0WPqw9frM3Kw60RXFfCueuow66pj6WpXsZHKVEFXmd47mt6bmt5rmt7LGd9pvKA63S36cyLU/Bj/vRt+n8a//H01/G5Kv7j+NHfNynpW86+bqy5j2Xwb6MKnKjEdQyTFy9TgFBSUopbFhHa/i8rZ9oqn7n+JNK1VnLIeNvDbWQ8/TifQX9y0Hj7ULiL5bT4Hv7qF9flf60jP/zi+x7Viy/O/SPH9nEb4Zp6wxFcvUnzLOL5dsdbxb1vZl1ev5agqNTfLq2Nb2TkPq8bhb/um2AR/uS34I3UJ/i6/Gf5MSzvwizj8pjJm+l8vDd7L+Cd4HqwknkfrIE0o3nxkCYUOOKxdgP7dyDa1PHmqvkUrDj2lrUtb1T3l5Xb7CblV/R1EZ+GjcpB3qAMJxkf8Bonoiv2dDpHLUrZFU0LmBeoiLU3BhtWRTA/hZDcnspMZ2Xcg2bdIsrsS2Xdrb54xMuwKtKYzILSn40EkhhAjM8swxWs5rpMswzA0YZwE6inRDJ/3UDsZKvw48YJNHJRlY1LtP8EfDvrTKm/cL9xH79btf5Cd/6aK/fzHaXI/v5nv5086uLFnOONTjXn4dAvj01wyPtWzGsRx41NcjrMMFqfHMN8fZbY4JccOmIL1IjI6BFkdJ3U7DJ1DqglGaZfDikJPVUF9In1qYmhnLRZSUCYA2mJY1I2h8J+MnNucfz7pXxWbLEsXYgEsy93Kj+Ke109BQZmcvC8u1sHjTCkZcjGjrHGQJYPnbvKo15+HteYKI2lH6l/EbnRtZG3vKEgS7qq1mm5o/t5YOCvQA0ftTfz8Sh+1D8tRW6vsUQVJVYaE7ilWgu+GWrSGG824sCs2cwXK842ZAuWgXQH3T/7Js/I/UK+mev6KAzpGtZ7mikcftVWnJNlWhbKtTsUxxWMnV3gb6yVY7s0yYpj/TsNcz6oQy5WdWnYDg6mxr6JiaFwcg4ebdBF/PL/XXM6CoJuBIP8SJ6S1E34C6Nw48HyiI8Tr50OEaTjD9JgRUwpiGqDaKbI50ttoh7dwi7hXMYRPOqMMoRDHkQoPcbMoS1OZYwbpfldehX0F5XNmc/0d/2IG5ax/mMHF7E/Esb6X4aXCP6ifGWfgEWJgWaJFUwx0AwO4aAlJfhEKdnR66iQicIXsi3g=
*/