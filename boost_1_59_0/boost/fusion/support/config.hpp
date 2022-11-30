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
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
*/