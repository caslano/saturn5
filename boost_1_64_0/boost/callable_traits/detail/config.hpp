/*
@Copyright Barrett Adair 2016-2017

Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

*/

#ifndef BOOST_CLBL_TRTS_DETAIL_CONFIG_HPP
#define BOOST_CLBL_TRTS_DETAIL_CONFIG_HPP

#include <type_traits>
#include <tuple>
#include <utility>
#include <cstdint>

#define BOOST_CLBL_TRTS_EMPTY_
#define BOOST_CLBL_TRTS_EMPTY BOOST_CLBL_TRTS_EMPTY_

#ifdef __cpp_transactional_memory
# define BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
#endif

#ifdef __cpp_inline_variables
# define BOOST_CLBL_TRAITS_INLINE_VAR inline
#else
# define BOOST_CLBL_TRAITS_INLINE_VAR
#endif

#ifdef __cpp_noexcept_function_type
# define BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#endif

#ifdef BOOST_CLBL_TRTS_ENABLE_TRANSACTION_SAFE
#  define BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER transaction_safe
#else
#  define BOOST_CLBL_TRTS_TRANSACTION_SAFE_SPECIFIER
#endif

#ifndef __clang__
#  if defined(__GNUC__)
#    define BOOST_CLBL_TRTS_GCC
#    if __GNUC__ >= 6
#        define BOOST_CLBL_TRTS_GCC_AT_LEAST_6_0_0
#    endif
#    if __GNUC__ < 5
#        define BOOST_CLBL_TRTS_GCC_OLDER_THAN_5_0_0
#    endif
#    if __GNUC__ >= 5
#      define BOOST_CLBL_TRTS_GCC_AT_LEAST_4_9_2
#    elif __GNUC__ == 4 && __GNUC_MINOR__ == 9 && __GNUC_PATCHLEVEL__ >= 2
#      define BOOST_CLBL_TRTS_GCC_AT_LEAST_4_9_2
#    else
#      define BOOST_CLBL_TRTS_GCC_OLDER_THAN_4_9_2
#    endif //#if __GNUC__ >= 5
#  endif //#if defined __GNUC__
#endif // #ifndef __clang__

#ifdef _MSC_VER
#  ifdef __clang__
#    define BOOST_CLBL_TRTS_CLANG_C2
#  else
#    define BOOST_CLBL_TRTS_MSVC
#  endif // #ifdef __clang__
#endif // #ifdef _MSC_VER

#define BOOST_CLBL_TRTS_IX_SEQ(...) ::std::index_sequence< __VA_ARGS__ >
#define BOOST_CLBL_TRTS_MAKE_IX_SEQ(...) ::std::make_index_sequence< __VA_ARGS__ >
#define BOOST_CLBL_TRTS_DISJUNCTION(...) ::std::disjunction< __VA_ARGS__ >

#ifndef __cpp_variable_templates
#  define BOOST_CLBL_TRTS_DISABLE_VARIABLE_TEMPLATES
#endif

#ifndef __cpp_lib_logical_traits
#  include <boost/callable_traits/detail/polyfills/disjunction.hpp>
#endif //__cpp_lib_logical_traits

#ifndef __cpp_lib_integer_sequence
#  include <boost/callable_traits/detail/polyfills/make_index_sequence.hpp>
#endif // __cpp_lib_integer_sequence

#if defined(BOOST_CLBL_TRTS_MSVC) && !defined(BOOST_DISABLE_WIN32)
#  define BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC __cdecl
#  define BOOST_CLBL_TRTS_PMF_VARGARGS_CDECL_DEFAULT
#else
#  define BOOST_CLBL_TRTS_DEFAULT_VARARGS_CC
#endif // #if defined(BOOST_CLBL_TRTS_MSVC) && !defined(BOOST_DISABLE_WIN32))

#if (defined(BOOST_CLBL_TRTS_GCC) && !defined(BOOST_CLBL_TRTS_GCC_AT_LEAST_4_9_2)) || defined(__INTEL_COMPILER)
#  define BOOST_CLBL_TRTS_DISABLE_REFERENCE_QUALIFIERS
#  define BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#endif // #if defined BOOST_CLBL_TRTS_GCC && !defined(BOOST_CLBL_TRTS_GCC_AT_LEAST_4_9_2)

#ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS
#  define BOOST_CLBL_TRTS_ABOMINABLE_CONST BOOST_CLBL_TRTS_EMPTY
#  define BOOST_CLBL_TRTS_ABOMINABLE_VOLATILE BOOST_CLBL_TRTS_EMPTY
#else
#  define BOOST_CLBL_TRTS_ABOMINABLE_CONST const
#  define BOOST_CLBL_TRTS_ABOMINABLE_VOLATILE volatile
#endif // #ifdef BOOST_CLBL_TRTS_DISABLE_ABOMINABLE_FUNCTIONS

#ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES
#  define BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER noexcept
#else
#  define BOOST_CLBL_TRTS_NOEXCEPT_SPECIFIER BOOST_CLBL_TRTS_EMPTY
#endif // #ifdef BOOST_CLBL_TRTS_ENABLE_NOEXCEPT_TYPES

#endif // #ifndef BOOST_CLBL_TRTS_DETAIL_CONFIG_HPP

/* config.hpp
ytYMqqNmi/9Uu47SMGEBddQ3kpZ7REfVJQ8T6HkfYl1rdNRmCesOqqMOSPjrXXdxjc0d4aqjvOes4a+jjP5+UsL1czEijP6uTxyqrzVcbFD9tH/LhfXTHo+M+h8K8k41we+dqneQd6pobGMlvto61tmbxjvJ42pO//eq+pqGsLvkHdThsqqgsSIo7WqMX8ikz/tK60NiitLrGSFyz1vN8R/BSIUYrbcdxf0F0nC1lWU1pC++mrwz3cmz3V1J35nmV/C+M4V4FJvoJ5WJr2R01ynVXcavUyWju5qiuy76nclfV+VdQFdl23TVVj9dtctPV+0PoKseC6KrEo4F/ob3f2c65PfO1Nuuv1RX3bElsK5qGm1xIOvmvMpEZM7cXUJX8QHqr6u6yfkbbpVvGLdXL8SKvY47i/tpGiHuJuZyjh+dWrc17ubuZtYXLq9uOCRhrgyk21S+o9FtTUS2insN8bZyHFXd5o3jLZ6mq4PpNo2ru9wLZwK9d6m+rStx1XRv4hwpjr1GpxFedRpy3nPqGslP+um0lts9fufULrKB37v03fMj8e/sai46DTcJE1ynpYvfY346LdXotOrbzq/TYory3H0P1zjNsV51mvectYPqtHjxr+W+k3ALHAsJh7sJVzeoTntd8qPTeXXaqx4Z9X/aT6c19JaXn05LO49OW7rdR6dpGnNcda2Xguq02yTfbnG0INxQvvMmU9dPobV68uWe7og16y68KXKpDhchr+dZvRm9V9HR2qqj9fYT8a+Bzk+0xuB/L6k6QorfsxrIPMvekXzzVdV3OOf8NuHlPGqullfNFekylQuLMnrubETTUB+/el6/Jgs/i3An/Mt6bv8F9Nxqm5476afnPvLTc2cC6LmvA4zRbAifNvrLNi/I6K9ifdg7gD40za+q5w5tD6znqtWw5GA8DyXBoe9kafeW0HM0ggV8J1PZlqadao3Yz9jbqcy3yV3i96xzC2/2HzAyS3WZxtHZvBOl7TpvG5XKdwv6nah6SeU6mDk0d4j9fWewtqiO98l6ME6+O/zTElDXHJP4HpK2qIZWiOzGPspKMbpm4X0BdY2Zo7NKwn/u9NMppk3lNvF/yRnu2O0ocsMmcT7sKMu87GA65b2dsr600SnPyHdaoflOI8+xcy9KXPHm260ibpUlbBkjVw23K8Ut0itHCPLKuCGnY7EH+skl4DbOT649bnP95JJwWyduFXy+5xK4f7+vrrqg5vwGrkbh9VAEofI1F4428LYVqWy1GKMP3ojoHurjl+j167bg1gh3z4vSB90CtBXNu4A+yPuZvtHSjgXuc/B/73nGfI/53utv673+OKYC5iHMc8gm31/iXh87ddIY2ztHnvm2yRDZ+6xa/L8ak4q5CaO6QOOKNGuMk5++5qLm6jEPz+RLns964mdqWnLU0QC1MY/hllS03pRcwJi8VNlcQO8N3DMLbOsfqWwNtaOdxO4Q+QdEhxTkj1H5PkY+XO02+QB72Wcb+Tq2/oLga0aFQdLIdZJGdasISQdupEPdqvntgW7Pk8w4S47+mBBMb8wByjXPP09SE4LlicqWF/v12G8Ue1KwPFH56iZPtok9NlieqHx/mz/z/dQ/x/h3Ujtvb2IPtetcs0bXDPHr9bPmr95L6iZptc2TCDY/INj4/Z9/3kDg+Q2XPp8j2LwBxxUe9yPbV/6qdcWronfUTd87tfDgh8HmB1z6PINLnd8QeN7Gpc8XCTyP4fLNXwk8P+b88yRUxckz7wx0kZZe+ru8w7tHu/YfQ6LCzzYWXvdK9/B9WAZ+AL3htp4n3Mca7m8a7hNbuP3nCfeZhvtcw+Fvwh0+T7gvNdw5Dfd3W7hj5wn3tYY=
*/