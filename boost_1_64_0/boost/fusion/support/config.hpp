/*=============================================================================
    Copyright (c) 2014 Eric Niebler
    Copyright (c) 2014,2015,2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_SUPPORT_CONFIG_01092014_1718)
#define FUSION_SUPPORT_CONFIG_01092014_1718

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <utility>

#ifndef BOOST_FUSION_GPU_ENABLED
#define BOOST_FUSION_GPU_ENABLED BOOST_GPU_ENABLED
#endif

// Enclose with inline namespace because unqualified lookup of GCC < 4.5 is broken.
//
//      namespace detail {
//          struct foo;
//          struct X { };
//      }
//
//      template <typename T> void foo(T) { }
//
//      int main()
//      {
//            foo(detail::X());
//            // prog.cc: In function 'int main()':
//            // prog.cc:2: error: 'struct detail::foo' is not a function,
//            // prog.cc:6: error: conflict with 'template<class T> void foo(T)'
//            // prog.cc:10: error: in call to 'foo'
//      }
namespace boost { namespace fusion { namespace detail
{
    namespace barrier { }
    using namespace barrier;
}}}
#define BOOST_FUSION_BARRIER_BEGIN namespace barrier {
#define BOOST_FUSION_BARRIER_END   }


#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1900))
// All of rvalue-reference ready MSVC don't perform implicit conversion from
// fundamental type to rvalue-reference of another fundamental type [1].
//
// Following example doesn't compile
//
//   int i;
//   long &&l = i; // sigh..., std::forward<long&&>(i) also fail.
//
// however, following one will work.
//
//   int i;
//   long &&l = static_cast<long &&>(i);
//
// OK, now can we replace all usage of std::forward to static_cast? -- I say NO!
// All of rvalue-reference ready Clang doesn't compile above static_cast usage [2], sigh...
//
// References:
// 1. https://connect.microsoft.com/VisualStudio/feedback/details/1037806/implicit-conversion-doesnt-perform-for-fund
// 2. http://llvm.org/bugs/show_bug.cgi?id=19917
//
// Tentatively, we use static_cast to forward if run under MSVC.
#   define BOOST_FUSION_FWD_ELEM(type, value) static_cast<type&&>(value)
#else
#   define BOOST_FUSION_FWD_ELEM(type, value) std::forward<type>(value)
#endif


// Workaround for LWG 2408: C++17 SFINAE-friendly std::iterator_traits.
// http://cplusplus.github.io/LWG/lwg-defects.html#2408
//
// - GCC 4.5 enables the feature under C++11.
//   https://gcc.gnu.org/ml/gcc-patches/2014-11/msg01105.html
//
// - MSVC 10.0 implements iterator intrinsics; MSVC 13.0 implements LWG2408.
#if (defined(BOOST_LIBSTDCXX_VERSION) && (BOOST_LIBSTDCXX_VERSION < 40500) && \
     defined(BOOST_LIBSTDCXX11)) || \
    (defined(BOOST_MSVC) && (1600 <= BOOST_MSVC && BOOST_MSVC < 1900))
#   define BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename>
    struct iterator_traits;
}
#endif


// Workaround for older GCC that doesn't accept `this` in constexpr.
#if BOOST_WORKAROUND(BOOST_GCC, < 40700)
#define BOOST_FUSION_CONSTEXPR_THIS
#else
#define BOOST_FUSION_CONSTEXPR_THIS BOOST_CONSTEXPR
#endif


// Workaround for compilers not implementing N3031 (DR743 and DR950).
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1913)) || \
    BOOST_WORKAROUND(BOOST_GCC, < 40700) || \
    defined(BOOST_CLANG) && (__clang_major__ == 3 && __clang_minor__ == 0)
# if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)
namespace boost { namespace fusion { namespace detail
{
    template <typename T>
    using type_alias_t = T;
}}}
#   define BOOST_FUSION_DECLTYPE_N3031(parenthesized_expr) \
        boost::fusion::detail::type_alias_t<decltype parenthesized_expr>
# else
#   include <boost/mpl/identity.hpp>
#   define BOOST_FUSION_DECLTYPE_N3031(parenthesized_expr) \
        boost::mpl::identity<decltype parenthesized_expr>::type
# endif
#else
#   define BOOST_FUSION_DECLTYPE_N3031(parenthesized_expr) \
        decltype parenthesized_expr
#endif


// Workaround for GCC 4.6 that rejects defaulted function with noexcept.
#if BOOST_WORKAROUND(BOOST_GCC, / 100 == 406)
#   define BOOST_FUSION_NOEXCEPT_ON_DEFAULTED
#else
#   define BOOST_FUSION_NOEXCEPT_ON_DEFAULTED BOOST_NOEXCEPT
#endif

#endif

/* config.hpp
E0/XPqlq+TSN6uKrnYZvI8PZKg7GS+fNPucpLm14AXr6PNF7fHPg53k33OsQOvGp/0Ok0fqgj4tpQ6dthX3y94b+5EceX6wX3Hu81Znm+8JiDTSqQ4XvvVpOOXK5v6NjTZG2e5DQtLzbt8RLvTu3ugyDXARsZbN5gPLoRrU5hFGwDasTHlP/LbpzBeFXrJZJWBSqZtpA7NF67MwZ1iYhPXmAUPlvdC+RdAqW1mUt8riy6WAyF4D/3PKI6uVvIvwJi8uklqouHf5zwy39+gxcsprs0X+Fy1uzSOl7sTx2Wbs3Lsv4ZnOpd4dRR0VRJtJh2jJ+WttwzfS9Khy06JucNKoLkWRufakbCuftyRHCG7IoV2GmgqjHO9zqvUWeI3yClVlVVaoMDB8Erm54zVM3aieuCK+E/uEhl2XIWiEB37DaHmptvA09bFOgtowjNw3JsqjkUSoLk719SNTV82KvnlWYxrnKc8OglYOxY+L5nI7vTYQvYLyKRVkXicPXjPXOTze+1XD5FKvrKsmAz2HTUwAt45VeGWUZFWlRxA7TU6ydps3rNy5fzYQskjzKui6k7xTw7VBPZspK5FmRl00fINPSlhE38u5odpne8yepVHlYxS2vUWQTVmube3SZlBVmBwmjyzQnfZSAPHMuT8nirOJBjG153ja/cwfPSBkjJrI6gw4PLBMVTrRh6NWtrvIyiWU3FrWTJTMgxt674xHhFaxOgiqtVTdvnOJRptqY7eNhV0e0+SO8ISvDUsRlalgBvwQTwOpwqz9+392rZ8FT/UKfu4ybG9v42Bx9mvfyK9I6yBIeWT7SPNan+TL1+aJfCseZdNjwISWeo667PJIlWVbGwNXxoLkzzmdn6fyrSujuUnUMOJeZwUB4j/Z4eRbURYF9cDpLKn6KdoJ9M0J4UxZK7cA/Ej4vsdFmeJ/by1tHeAPZDp1ykwmV2JL3eKskkVzWHHkvjNaHdL3CPnmby1uxMo5FnlSm2PSN3Lm8q6uYou9s0ioS+q2+EbP51eXmVfWkF9cmrZmu3W7qtVuaJrniiUkKHT3g8cPwr+FbXcKfszxOYCrnrBPc+eUNOJe1TnVGW8Ox9Zxg3+Bf3x64MpYGlYrqUjK9EpCH/lPOO++zVJaDRBRhXqHbHP3M3S6ZU+OuvrPn6BsrIeM8zHnI3OfVTcY0CdHpMs/R822hai5FWBH+vRwlOG/Fnn2OtrvKq1plZcna6s53D8Zx82B8EKAPFsIvGM/rvCrLsOOHAbLdJNB2JLY5+qsg/DlTWSULGZXWN0gj6abvyBPr1U7ur7yQ+tpI4lC726gbfxmdEQN9cD8U3bpH8q9ZqKJQ1GEFvMZREpS+YzbZQzvubPT8/cyuuP0RMl5nQZhmkIzTdiZF7UHD2fyRfefcCh3DBbRnXEaqSQhnLUhgc8M0SVOMc7h33CUynHBRVEkZGXa65nRlV6TsghUizoMs4Hv73GizB0mCgti5720rvTGcweRXiaJd0xtZ6gqBw4msJyv0PavMVCmV7Nh1bd05E/1gpC8akDcmUr/3qzhnbV6ksU1NbA+676FI+YV2wlaKJK2ZOSlMHJCOT7J/knbMWAmTN1dVhvx7ey4BX1p2Hn8tqU/ICl4KGSQJa6ZuYBjubvfmo82wmxeGdF9cKh5Weal9Fuh711ZJpXcupFXoe7l0SPsxScIgSlQ9IY0LwwvagHDTe6O2OuyPqyRSvK78NKxzqEl7qUvDnq+AuMxKrgL0aUGGJuV9N+GNWBiXsQLhsLwo4N7574uENwPeIovzivigwEnNyTvEN9AD+rauqqMoUgHlN6sT9cdxf3wvOezv5as4ToO68wPRjAvKe1Lrxx70CK0=
*/