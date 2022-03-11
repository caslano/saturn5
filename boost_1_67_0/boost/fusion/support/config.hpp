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