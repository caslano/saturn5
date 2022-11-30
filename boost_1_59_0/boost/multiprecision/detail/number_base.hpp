///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BIG_NUM_BASE_HPP
#define BOOST_MATH_BIG_NUM_BASE_HPP

#include <climits>
#include <ios>
#include <string>
#include <limits>
#include <type_traits>
#include <stdexcept>
#include <tuple>
#include <boost/multiprecision/detail/standalone_config.hpp>
#include <boost/multiprecision/traits/transcendental_reduction_type.hpp>
#include <boost/multiprecision/traits/std_integer_traits.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4307)
#pragma warning(pop)
#endif

#ifndef BOOST_MP_STANDALONE
#include <boost/lexical_cast.hpp>
#include <boost/core/nvp.hpp>
#endif

#ifdef BOOST_MP_MATH_AVAILABLE
#include <boost/math/tools/complex.hpp>
#endif

//
// We now require C++11, if something we use is not supported, then error and say why:
//
#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_RVALUE_REFERENCES being set"
#endif
#ifdef BOOST_NO_CXX11_TEMPLATE_ALIASES
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_TEMPLATE_ALIASES being set"
#endif
#ifdef BOOST_NO_CXX11_HDR_ARRAY
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_HDR_ARRAY being set"
#endif
#ifdef BOOST_NO_CXX11_HDR_TYPE_TRAITS
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_HDR_TYPE_TRAITS being set"
#endif
#ifdef BOOST_NO_CXX11_ALLOCATOR
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_ALLOCATOR being set"
#endif
#ifdef BOOST_NO_CXX11_CONSTEXPR
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_CONSTEXPR being set"
#endif
#ifdef BOOST_MP_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_MP_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS being set"
#endif
#ifdef BOOST_NO_CXX11_REF_QUALIFIERS
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_REF_QUALIFIERS being set"
#endif
#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_HDR_FUNCTIONAL being set"
#endif
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_VARIADIC_TEMPLATES being set"
#endif
#ifdef BOOST_NO_CXX11_USER_DEFINED_LITERALS
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_USER_DEFINED_LITERALS being set"
#endif
#ifdef BOOST_NO_CXX11_DECLTYPE
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_DECLTYPE being set"
#endif
#ifdef BOOST_NO_CXX11_STATIC_ASSERT
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_STATIC_ASSERT being set"
#endif
#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_DEFAULTED_FUNCTIONS being set"
#endif
#ifdef BOOST_NO_CXX11_NOEXCEPT
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_NOEXCEPT being set"
#endif
#ifdef BOOST_NO_CXX11_REF_QUALIFIERS
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_REF_QUALIFIERS being set"
#endif
#ifdef BOOST_NO_CXX11_USER_DEFINED_LITERALS
#error "This library now requires a C++11 or later compiler - this message was generated as a result of BOOST_NO_CXX11_USER_DEFINED_LITERALS being set"
#endif

#if defined(NDEBUG) && !defined(_DEBUG)
#define BOOST_MP_FORCEINLINE BOOST_FORCEINLINE
#else
#define BOOST_MP_FORCEINLINE inline
#endif

//
// Thread local storage:
// Note fails on Mingw, see https://sourceforge.net/p/mingw-w64/bugs/527/
//
#if defined(BOOST_NO_CXX11_THREAD_LOCAL)
#define BOOST_MP_THREAD_LOCAL
#elif !(defined(__MINGW32__) && (defined(__GNUC__) && (__GNUC__ < 9)) && !defined(__clang__))
#define BOOST_MP_THREAD_LOCAL thread_local
#define BOOST_MP_USING_THREAD_LOCAL
#else
#pragma GCC warning "thread_local on mingw is broken, please use MSys mingw gcc-9 or later, see https://sourceforge.net/p/mingw-w64/bugs/527/"
#define BOOST_MP_THREAD_LOCAL
#endif

#ifdef __has_include
# if __has_include(<version>)
#  include <version>
#  ifdef __cpp_lib_is_constant_evaluated
#   include <type_traits>
#   define BOOST_MP_HAS_IS_CONSTANT_EVALUATED
#  endif
# endif
#endif

#ifdef __has_builtin
#if __has_builtin(__builtin_is_constant_evaluated) && !defined(BOOST_NO_CXX14_CONSTEXPR) && !defined(BOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX)
#define BOOST_MP_HAS_BUILTIN_IS_CONSTANT_EVALUATED
#endif
#endif
//
// MSVC also supports __builtin_is_constant_evaluated if it's recent enough:
//
#if defined(_MSC_FULL_VER) && (_MSC_FULL_VER >= 192528326)
#  define BOOST_MP_HAS_BUILTIN_IS_CONSTANT_EVALUATED
#endif
//
// As does GCC-9:
//
#if defined(BOOST_GCC) && !defined(BOOST_NO_CXX14_CONSTEXPR) && (__GNUC__ >= 9) && !defined(BOOST_MP_HAS_BUILTIN_IS_CONSTANT_EVALUATED)
#  define BOOST_MP_HAS_BUILTIN_IS_CONSTANT_EVALUATED
#endif

#if defined(BOOST_MP_HAS_IS_CONSTANT_EVALUATED) && !defined(BOOST_NO_CXX14_CONSTEXPR)
#  define BOOST_MP_IS_CONST_EVALUATED(x) std::is_constant_evaluated()
#elif defined(BOOST_MP_HAS_BUILTIN_IS_CONSTANT_EVALUATED)
#  define BOOST_MP_IS_CONST_EVALUATED(x) __builtin_is_constant_evaluated()
#elif !defined(BOOST_NO_CXX14_CONSTEXPR) && defined(BOOST_GCC) && (__GNUC__ >= 6)
#  define BOOST_MP_IS_CONST_EVALUATED(x) __builtin_constant_p(x)
#else
#  define BOOST_MP_NO_CONSTEXPR_DETECTION
#endif

#define BOOST_MP_CXX14_CONSTEXPR BOOST_CXX14_CONSTEXPR
//
// Early compiler versions trip over the constexpr code:
//
#if defined(__clang__) && (__clang_major__ < 5)
#undef BOOST_MP_CXX14_CONSTEXPR
#define BOOST_MP_CXX14_CONSTEXPR
#endif
#if defined(__apple_build_version__) && (__clang_major__ < 9)
#undef BOOST_MP_CXX14_CONSTEXPR
#define BOOST_MP_CXX14_CONSTEXPR
#endif
#if defined(BOOST_GCC) && (__GNUC__ < 6)
#undef BOOST_MP_CXX14_CONSTEXPR
#define BOOST_MP_CXX14_CONSTEXPR
#endif
#if defined(BOOST_INTEL)
#undef BOOST_MP_CXX14_CONSTEXPR
#define BOOST_MP_CXX14_CONSTEXPR
#define BOOST_MP_NO_CONSTEXPR_DETECTION
#endif

#ifdef BOOST_MP_NO_CONSTEXPR_DETECTION
#  define BOOST_CXX14_CONSTEXPR_IF_DETECTION
#else
#  define BOOST_CXX14_CONSTEXPR_IF_DETECTION constexpr
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 6326)
#endif

namespace boost {
namespace multiprecision {

enum expression_template_option
{
   et_off = 0,
   et_on  = 1
};

enum struct variable_precision_options : signed char
{
   assume_uniform_precision = -1,
   preserve_target_precision = 0,
   preserve_source_precision = 1,
   preserve_component_precision = 2,
   preserve_related_precision = 3,
   preserve_all_precision = 4,
};

inline constexpr bool operator==(variable_precision_options a, variable_precision_options b)
{
   return static_cast<unsigned>(a) == static_cast<unsigned>(b);
}

template <class Backend>
struct expression_template_default
{
   static constexpr const expression_template_option value = et_on;
};

template <class Backend, expression_template_option ExpressionTemplates = expression_template_default<Backend>::value>
class number;

template <class T>
struct is_number : public std::integral_constant<bool, false>
{};

template <class Backend, expression_template_option ExpressionTemplates>
struct is_number<number<Backend, ExpressionTemplates> > : public std::integral_constant<bool, true>
{};

template <class T>
struct is_et_number : public std::integral_constant<bool, false>
{};

template <class Backend>
struct is_et_number<number<Backend, et_on> > : public std::integral_constant<bool, true>
{};

template <class T>
struct is_no_et_number : public std::integral_constant<bool, false>
{};

template <class Backend>
struct is_no_et_number<number<Backend, et_off> > : public std::integral_constant<bool, true>
{};

namespace detail {

// Forward-declare an expression wrapper
template <class tag, class Arg1 = void, class Arg2 = void, class Arg3 = void, class Arg4 = void>
struct expression;

} // namespace detail

template <class T>
struct is_number_expression : public std::integral_constant<bool, false>
{};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct is_number_expression<detail::expression<tag, Arg1, Arg2, Arg3, Arg4> > : public std::integral_constant<bool, true>
{};

template <class T, class Num>
struct is_compatible_arithmetic_type
    : public std::integral_constant<bool, 
          std::is_convertible<T, Num>::value && !std::is_same<T, Num>::value && !is_number_expression<T>::value>
{};

namespace detail {
//
// Workaround for missing abs(long long) and abs(__int128) on some compilers:
//
template <class T>
constexpr typename std::enable_if<(boost::multiprecision::detail::is_signed<T>::value || std::is_floating_point<T>::value), T>::type abs(T t) noexcept
{
   // This strange expression avoids a hardware trap in the corner case
   // that val is the most negative value permitted in long long.
   // See https://svn.boost.org/trac/boost/ticket/9740.
   return t < 0 ? T(1u) + T(-(t + 1)) : t;
}
template <class T>
constexpr typename std::enable_if<boost::multiprecision::detail::is_unsigned<T>::value, T>::type abs(T t) noexcept
{
   return t;
}

#define BOOST_MP_USING_ABS using boost::multiprecision::detail::abs;

template <class T>
constexpr typename std::enable_if<(boost::multiprecision::detail::is_signed<T>::value || std::is_floating_point<T>::value), typename boost::multiprecision::detail::make_unsigned<T>::type>::type unsigned_abs(T t) noexcept
{
   // This strange expression avoids a hardware trap in the corner case
   // that val is the most negative value permitted in long long.
   // See https://svn.boost.org/trac/boost/ticket/9740.
   return t < 0 ? static_cast<typename boost::multiprecision::detail::make_unsigned<T>::type>(1u) + static_cast<typename boost::multiprecision::detail::make_unsigned<T>::type>(-(t + 1)) : static_cast<typename boost::multiprecision::detail::make_unsigned<T>::type>(t);
}
template <class T>
constexpr typename std::enable_if<boost::multiprecision::detail::is_unsigned<T>::value, T>::type unsigned_abs(T t) noexcept
{
   return t;
}

template <class T>
struct bits_of
{
   static_assert(boost::multiprecision::detail::is_integral<T>::value || std::is_enum<T>::value || std::numeric_limits<T>::is_specialized, "Failed integer size check");
   static constexpr const unsigned value =
       std::numeric_limits<T>::is_specialized ? std::numeric_limits<T>::digits
                                              : sizeof(T) * CHAR_BIT - (boost::multiprecision::detail::is_signed<T>::value ? 1 : 0);
};

#if defined(_GLIBCXX_USE_FLOAT128) && defined(BOOST_GCC) && !defined(__STRICT_ANSI__)
#define BOOST_MP_BITS_OF_FLOAT128_DEFINED
template <>
struct bits_of<float128_type>
{
   static constexpr const unsigned value = 113;
};
#endif

template <int b>
struct has_enough_bits
{
   template <class T>
   struct type : public std::integral_constant<bool, bits_of<T>::value >= b>
   {};
};

template <class Tuple, int i, int digits, bool = (i >= std::tuple_size<Tuple>::value)>
struct find_index_of_large_enough_type
{
   static constexpr int value = bits_of<typename std::tuple_element<static_cast<std::size_t>(i), Tuple>::type>::value >= digits ? i : find_index_of_large_enough_type<Tuple, i + 1, digits>::value;
};
template <class Tuple, int i, int digits>
struct find_index_of_large_enough_type<Tuple, i, digits, true>
{
   static constexpr int value = INT_MAX;
};

template <int index, class Tuple, class Fallback, bool = (std::tuple_size<Tuple>::value <= index)>
struct dereference_tuple
{
   using type = typename std::tuple_element<static_cast<std::size_t>(index), Tuple>::type;
};
template <int index, class Tuple, class Fallback>
struct dereference_tuple<index, Tuple, Fallback, true>
{
   using type = Fallback;
};

template <class Val, class Backend, class Tag>
struct canonical_imp
{
   using type = typename std::remove_cv<typename std::decay<const Val>::type>::type;
};
template <class B, class Backend, class Tag>
struct canonical_imp<number<B, et_on>, Backend, Tag>
{
   using type = B;
};
template <class B, class Backend, class Tag>
struct canonical_imp<number<B, et_off>, Backend, Tag>
{
   using type = B;
};
#ifdef __SUNPRO_CC
template <class B, class Backend>
struct canonical_imp<number<B, et_on>, Backend, std::integral_constant<int, 3> >
{
   using type = B;
};
template <class B, class Backend>
struct canonical_imp<number<B, et_off>, Backend, std::integral_constant<int, 3> >
{
   using type = B;
};
#endif
template <class Val, class Backend>
struct canonical_imp<Val, Backend, std::integral_constant<int, 0> >
{
   static constexpr int index = find_index_of_large_enough_type<typename Backend::signed_types, 0, bits_of<Val>::value>::value;
   using type = typename dereference_tuple<index, typename Backend::signed_types, Val>::type;
};
template <class Val, class Backend>
struct canonical_imp<Val, Backend, std::integral_constant<int, 1> >
{
   static constexpr int index = find_index_of_large_enough_type<typename Backend::unsigned_types, 0, bits_of<Val>::value>::value;
   using type = typename dereference_tuple<index, typename Backend::unsigned_types, Val>::type;
};
template <class Val, class Backend>
struct canonical_imp<Val, Backend, std::integral_constant<int, 2> >
{
   static constexpr int index = find_index_of_large_enough_type<typename Backend::float_types, 0, bits_of<Val>::value>::value;
   using type = typename dereference_tuple<index, typename Backend::float_types, Val>::type;
};
template <class Val, class Backend>
struct canonical_imp<Val, Backend, std::integral_constant<int, 3> >
{
   using type = const char*;
};
template <class Val, class Backend>
struct canonical_imp<Val, Backend, std::integral_constant<int, 4> >
{
   using underlying = typename std::underlying_type<Val>::type;
   using tag = typename std::conditional<boost::multiprecision::detail::is_signed<Val>::value, std::integral_constant<int, 0>, std::integral_constant<int, 1>>::type;
   using type = typename canonical_imp<underlying, Backend, tag>::type;
};

template <class Val, class Backend>
struct canonical
{
   using tag_type = typename std::conditional<
       boost::multiprecision::detail::is_signed<Val>::value && boost::multiprecision::detail::is_integral<Val>::value,
       std::integral_constant<int, 0>,
       typename std::conditional<
           boost::multiprecision::detail::is_unsigned<Val>::value,
           std::integral_constant<int, 1>,
           typename std::conditional<
               std::is_floating_point<Val>::value,
               std::integral_constant<int, 2>,
               typename std::conditional<
                   (std::is_convertible<Val, const char*>::value || std::is_same<Val, std::string>::value),
                   std::integral_constant<int, 3>,
                   typename std::conditional<
                     std::is_enum<Val>::value,
                     std::integral_constant<int, 4>,
                     std::integral_constant<int, 5> >::type>::type>::type>::type>::type;

   using type = typename canonical_imp<Val, Backend, tag_type>::type;
};

struct terminal
{};
struct negate
{};
struct plus
{};
struct minus
{};
struct multiplies
{};
struct divides
{};
struct modulus
{};
struct shift_left
{};
struct shift_right
{};
struct bitwise_and
{};
struct bitwise_or
{};
struct bitwise_xor
{};
struct bitwise_complement
{};
struct add_immediates
{};
struct subtract_immediates
{};
struct multiply_immediates
{};
struct divide_immediates
{};
struct modulus_immediates
{};
struct bitwise_and_immediates
{};
struct bitwise_or_immediates
{};
struct bitwise_xor_immediates
{};
struct complement_immediates
{};
struct function
{};
struct multiply_add
{};
struct multiply_subtract
{};

template <class T>
struct backend_type;

template <class T, expression_template_option ExpressionTemplates>
struct backend_type<number<T, ExpressionTemplates> >
{
   using type = T;
};

template <class tag, class A1, class A2, class A3, class A4>
struct backend_type<expression<tag, A1, A2, A3, A4> >
{
   using type = typename backend_type<typename expression<tag, A1, A2, A3, A4>::result_type>::type;
};

template <class T1, class T2>
struct combine_expression
{
   using type = decltype(T1() + T2());
};

template <class T1, expression_template_option ExpressionTemplates, class T2>
struct combine_expression<number<T1, ExpressionTemplates>, T2>
{
   using type = number<T1, ExpressionTemplates>;
};

template <class T1, class T2, expression_template_option ExpressionTemplates>
struct combine_expression<T1, number<T2, ExpressionTemplates> >
{
   using type = number<T2, ExpressionTemplates>;
};

template <class T, expression_template_option ExpressionTemplates>
struct combine_expression<number<T, ExpressionTemplates>, number<T, ExpressionTemplates> >
{
   using type = number<T, ExpressionTemplates>;
};

template <class T1, expression_template_option ExpressionTemplates1, class T2, expression_template_option ExpressionTemplates2>
struct combine_expression<number<T1, ExpressionTemplates1>, number<T2, ExpressionTemplates2> >
{
   using type = typename std::conditional<
       std::is_convertible<number<T2, ExpressionTemplates2>, number<T1, ExpressionTemplates2> >::value,
       number<T1, ExpressionTemplates1>,
       number<T2, ExpressionTemplates2> >::type;
};

template <class T>
struct arg_type
{
   using type = expression<terminal, T>;
};

template <class Tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct arg_type<expression<Tag, Arg1, Arg2, Arg3, Arg4> >
{
   using type = expression<Tag, Arg1, Arg2, Arg3, Arg4>;
};

struct unmentionable
{
   unmentionable* proc() { return nullptr; }
};

typedef unmentionable* (unmentionable::*unmentionable_type)();

template <class T, bool b>
struct expression_storage_base
{
   using type = const T&;
};

template <class T>
struct expression_storage_base<T, true>
{
   using type = T;
};

template <class T>
struct expression_storage : public expression_storage_base<T, boost::multiprecision::detail::is_arithmetic<T>::value>
{};

template <class T>
struct expression_storage<T*>
{
   using type = T*;
};

template <class T>
struct expression_storage<const T*>
{
   using type = const T*;
};

template <class tag, class A1, class A2, class A3, class A4>
struct expression_storage<expression<tag, A1, A2, A3, A4> >
{
   using type = expression<tag, A1, A2, A3, A4>;
};

template <class tag, class Arg1>
struct expression<tag, Arg1, void, void, void>
{
   using arity = std::integral_constant<int, 1>                   ;
   using left_type = typename arg_type<Arg1>::type  ;
   using left_result_type = typename left_type::result_type;
   using result_type = typename left_type::result_type;
   using tag_type = tag                            ;

   explicit BOOST_MP_CXX14_CONSTEXPR expression(const Arg1& a) : arg(a) {}
   BOOST_MP_CXX14_CONSTEXPR expression(const expression& e) : arg(e.arg) {}

   //
   // If we have static_assert we can give a more useful error message
   // than if we simply have no operator defined at all:
   //
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not assign to a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator+=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator+= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator-=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator-= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator*=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator*= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator/=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator/= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator%=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator%= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator|=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator|= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator&=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator&= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator^=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator^= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator<<=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator<<= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator>>=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator>>= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }

   BOOST_MP_CXX14_CONSTEXPR left_type left() const
   {
      return left_type(arg);
   }

   BOOST_MP_CXX14_CONSTEXPR const Arg1& left_ref() const noexcept { return arg; }

   static constexpr const unsigned depth = left_type::depth + 1;
   template <class T
#ifndef __SUNPRO_CC
             ,
             typename std::enable_if<!is_number<T>::value && !std::is_convertible<result_type, T const&>::value && std::is_constructible<T, result_type>::value, int>::type = 0
#endif
             >
   explicit BOOST_MP_CXX14_CONSTEXPR operator T() const
   {
      return static_cast<T>(static_cast<result_type>(*this));
   }
   BOOST_MP_FORCEINLINE explicit BOOST_MP_CXX14_CONSTEXPR operator bool() const
   {
      result_type r(*this);
      return static_cast<bool>(r);
   }

   template <class T>
   BOOST_MP_CXX14_CONSTEXPR T convert_to()
   {
      result_type r(*this);
      return r.template convert_to<T>();
   }

 private:
   typename expression_storage<Arg1>::type arg;
   expression&                             operator=(const expression&);
};

template <class Arg1>
struct expression<terminal, Arg1, void, void, void>
{
   using arity = std::integral_constant<int, 0>;
   using result_type = Arg1        ;
   using tag_type = terminal    ;

   explicit BOOST_MP_CXX14_CONSTEXPR expression(const Arg1& a) : arg(a) {}
   BOOST_MP_CXX14_CONSTEXPR expression(const expression& e) : arg(e.arg) {}

   //
   // If we have static_assert we can give a more useful error message
   // than if we simply have no operator defined at all:
   //
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not assign to a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator+=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator+= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator-=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator-= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator*=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator*= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator/=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator/= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator%=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator%= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator|=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator|= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator&=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator&= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator^=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator^= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator<<=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator<<= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator>>=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator>>= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }

   BOOST_MP_CXX14_CONSTEXPR const Arg1& value() const noexcept
   {
      return arg;
   }

   static constexpr const unsigned depth = 0;

   template <class T
#ifndef __SUNPRO_CC
             ,
             typename std::enable_if<!is_number<T>::value && !std::is_convertible<result_type, T const&>::value && std::is_constructible<T, result_type>::value, int>::type = 0
#endif
             >
   explicit BOOST_MP_CXX14_CONSTEXPR operator T() const
   {
      return static_cast<T>(static_cast<result_type>(*this));
   }
   BOOST_MP_FORCEINLINE explicit BOOST_MP_CXX14_CONSTEXPR operator bool() const
   {
      result_type r(*this);
      return static_cast<bool>(r);
   }

   template <class T>
   BOOST_MP_CXX14_CONSTEXPR T convert_to()
   {
      result_type r(*this);
      return r.template convert_to<T>();
   }

 private:
   typename expression_storage<Arg1>::type arg;
   expression&                             operator=(const expression&);
};

template <class tag, class Arg1, class Arg2>
struct expression<tag, Arg1, Arg2, void, void>
{
   using arity = std::integral_constant<int, 2>                                                          ;
   using left_type = typename arg_type<Arg1>::type                                         ;
   using right_type = typename arg_type<Arg2>::type                                         ;
   using left_result_type = typename left_type::result_type                                       ;
   using right_result_type = typename right_type::result_type                                      ;
   using result_type = typename combine_expression<left_result_type, right_result_type>::type;
   using tag_type = tag                                                                   ;

   BOOST_MP_CXX14_CONSTEXPR expression(const Arg1& a1, const Arg2& a2) : arg1(a1), arg2(a2) {}
   BOOST_MP_CXX14_CONSTEXPR expression(const expression& e) : arg1(e.arg1), arg2(e.arg2) {}

   //
   // If we have static_assert we can give a more useful error message
   // than if we simply have no operator defined at all:
   //
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not assign to a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator+=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator+= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator-=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator-= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator*=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator*= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator/=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator/= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator%=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator%= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator|=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator|= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator&=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator&= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator^=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator^= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator<<=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator<<= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator>>=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator>>= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }

   BOOST_MP_CXX14_CONSTEXPR left_type left() const
   {
      return left_type(arg1);
   }
   BOOST_MP_CXX14_CONSTEXPR right_type  right() const { return right_type(arg2); }
   BOOST_MP_CXX14_CONSTEXPR const Arg1& left_ref() const noexcept { return arg1; }
   BOOST_MP_CXX14_CONSTEXPR const Arg2& right_ref() const noexcept { return arg2; }

   template <class T
#ifndef __SUNPRO_CC
             ,
             typename std::enable_if<!is_number<T>::value && !std::is_convertible<result_type, T const&>::value && std::is_constructible<T, result_type>::value, int>::type = 0
#endif
             >
   explicit BOOST_MP_CXX14_CONSTEXPR operator T() const
   {
      return static_cast<T>(static_cast<result_type>(*this));
   }
   BOOST_MP_FORCEINLINE explicit BOOST_MP_CXX14_CONSTEXPR operator bool() const
   {
      result_type r(*this);
      return static_cast<bool>(r);
   }
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR T convert_to()
   {
      result_type r(*this);
      return r.template convert_to<T>();
   }

   static const constexpr unsigned                left_depth  = left_type::depth + 1;
   static const constexpr unsigned                right_depth = right_type::depth + 1;
   static const constexpr unsigned                depth       = left_depth > right_depth ? left_depth : right_depth;

 private:
   typename expression_storage<Arg1>::type arg1;
   typename expression_storage<Arg2>::type arg2;
   expression&                             operator=(const expression&);
};

template <class tag, class Arg1, class Arg2, class Arg3>
struct expression<tag, Arg1, Arg2, Arg3, void>
{
   using arity = std::integral_constant<int, 3>                     ;
   using left_type = typename arg_type<Arg1>::type    ;
   using middle_type = typename arg_type<Arg2>::type    ;
   using right_type = typename arg_type<Arg3>::type    ;
   using left_result_type = typename left_type::result_type  ;
   using middle_result_type = typename middle_type::result_type;
   using right_result_type = typename right_type::result_type ;
   using result_type = typename combine_expression<
       left_result_type,
       typename combine_expression<right_result_type, middle_result_type>::type>::type;
   using tag_type = tag                                                                        ;

   BOOST_MP_CXX14_CONSTEXPR expression(const Arg1& a1, const Arg2& a2, const Arg3& a3) : arg1(a1), arg2(a2), arg3(a3) {}
   BOOST_MP_CXX14_CONSTEXPR expression(const expression& e) : arg1(e.arg1), arg2(e.arg2), arg3(e.arg3) {}

   //
   // If we have static_assert we can give a more useful error message
   // than if we simply have no operator defined at all:
   //
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not assign to a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator+=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator+= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator-=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator-= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator*=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator*= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator/=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator/= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator%=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator%= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator|=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator|= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator&=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator&= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator^=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator^= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator<<=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator<<= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator>>=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator>>= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }

   BOOST_MP_CXX14_CONSTEXPR left_type left() const
   {
      return left_type(arg1);
   }
   BOOST_MP_CXX14_CONSTEXPR middle_type middle() const { return middle_type(arg2); }
   BOOST_MP_CXX14_CONSTEXPR right_type  right() const { return right_type(arg3); }
   BOOST_MP_CXX14_CONSTEXPR const Arg1& left_ref() const noexcept { return arg1; }
   BOOST_MP_CXX14_CONSTEXPR const Arg2& middle_ref() const noexcept { return arg2; }
   BOOST_MP_CXX14_CONSTEXPR const Arg3& right_ref() const noexcept { return arg3; }

   template <class T
#ifndef __SUNPRO_CC
             ,
             typename std::enable_if<!is_number<T>::value && !std::is_convertible<result_type, T const&>::value && std::is_constructible<T, result_type>::value, int>::type = 0
#endif
             >
   explicit BOOST_MP_CXX14_CONSTEXPR operator T() const
   {
      return static_cast<T>(static_cast<result_type>(*this));
   }
   BOOST_MP_FORCEINLINE explicit BOOST_MP_CXX14_CONSTEXPR operator bool() const
   {
      result_type r(*this);
      return static_cast<bool>(r);
   }
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR T convert_to()
   {
      result_type r(*this);
      return r.template convert_to<T>();
   }

   static constexpr const unsigned left_depth   = left_type::depth + 1;
   static constexpr const unsigned middle_depth = middle_type::depth + 1;
   static constexpr const unsigned right_depth  = right_type::depth + 1;
   static constexpr const unsigned depth        = left_depth > right_depth ? (left_depth > middle_depth ? left_depth : middle_depth) : (right_depth > middle_depth ? right_depth : middle_depth);

 private:
   typename expression_storage<Arg1>::type arg1;
   typename expression_storage<Arg2>::type arg2;
   typename expression_storage<Arg3>::type arg3;
   expression&                             operator=(const expression&);
};

template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
struct expression
{
   using arity = std::integral_constant<int, 4>                           ;
   using left_type = typename arg_type<Arg1>::type          ;
   using left_middle_type = typename arg_type<Arg2>::type          ;
   using right_middle_type = typename arg_type<Arg3>::type          ;
   using right_type = typename arg_type<Arg4>::type          ;
   using left_result_type = typename left_type::result_type        ;
   using left_middle_result_type = typename left_middle_type::result_type ;
   using right_middle_result_type = typename right_middle_type::result_type;
   using right_result_type = typename right_type::result_type       ;
   using result_type = typename combine_expression<
       left_result_type,
       typename combine_expression<
           left_middle_result_type,
           typename combine_expression<right_middle_result_type, right_result_type>::type>::type>::type;
   using tag_type = tag                                                                                         ;

   BOOST_MP_CXX14_CONSTEXPR expression(const Arg1& a1, const Arg2& a2, const Arg3& a3, const Arg4& a4) : arg1(a1), arg2(a2), arg3(a3), arg4(a4) {}
   BOOST_MP_CXX14_CONSTEXPR expression(const expression& e) : arg1(e.arg1), arg2(e.arg2), arg3(e.arg3), arg4(e.arg4) {}

   //
   // If we have static_assert we can give a more useful error message
   // than if we simply have no operator defined at all:
   //
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not assign to a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator++(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not increment a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--()
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   BOOST_MP_CXX14_CONSTEXPR expression& operator--(int)
   {
      // This should always fail:
      static_assert(sizeof(*this) == INT_MAX, "You can not decrement a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator+=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator+= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator-=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator-= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator*=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator*= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator/=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator/= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator%=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator%= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator|=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator|= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator&=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator&= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator^=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator^= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator<<=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator<<= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }
   template <class Other>
   BOOST_MP_CXX14_CONSTEXPR expression& operator>>=(const Other&)
   {
      // This should always fail:
      static_assert(sizeof(Other) == INT_MAX, "You can not use operator>>= on a Boost.Multiprecision expression template: did you inadvertantly store an expression template in a \"auto\" variable?  Or pass an expression to a template function with deduced temnplate arguments?");
      return *this;
   }

   BOOST_MP_CXX14_CONSTEXPR left_type left() const
   {
      return left_type(arg1);
   }
   BOOST_MP_CXX14_CONSTEXPR left_middle_type  left_middle() const { return left_middle_type(arg2); }
   BOOST_MP_CXX14_CONSTEXPR right_middle_type right_middle() const { return right_middle_type(arg3); }
   BOOST_MP_CXX14_CONSTEXPR right_type        right() const { return right_type(arg4); }
   BOOST_MP_CXX14_CONSTEXPR const Arg1&       left_ref() const noexcept { return arg1; }
   BOOST_MP_CXX14_CONSTEXPR const Arg2&       left_middle_ref() const noexcept { return arg2; }
   BOOST_MP_CXX14_CONSTEXPR const Arg3&       right_middle_ref() const noexcept { return arg3; }
   BOOST_MP_CXX14_CONSTEXPR const Arg4&       right_ref() const noexcept { return arg4; }

   template <class T
#ifndef __SUNPRO_CC
             ,
             typename std::enable_if<!is_number<T>::value && !std::is_convertible<result_type, T const&>::value && std::is_constructible<T, result_type>::value, int>::type = 0
#endif
             >
   explicit BOOST_MP_CXX14_CONSTEXPR operator T() const
   {
      return static_cast<T>(static_cast<result_type>(*this));
   }
   BOOST_MP_FORCEINLINE explicit BOOST_MP_CXX14_CONSTEXPR operator bool() const
   {
      result_type r(*this);
      return static_cast<bool>(r);
   }
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR T convert_to()
   {
      result_type r(*this);
      return r.template convert_to<T>();
   }

   static constexpr const unsigned left_depth         = left_type::depth + 1;
   static constexpr const unsigned left_middle_depth  = left_middle_type::depth + 1;
   static constexpr const unsigned right_middle_depth = right_middle_type::depth + 1;
   static constexpr const unsigned right_depth        = right_type::depth + 1;

   static constexpr const unsigned left_max_depth  = left_depth > left_middle_depth ? left_depth : left_middle_depth;
   static constexpr const unsigned right_max_depth = right_depth > right_middle_depth ? right_depth : right_middle_depth;

   static constexpr const unsigned depth = left_max_depth > right_max_depth ? left_max_depth : right_max_depth;

 private:
   typename expression_storage<Arg1>::type arg1;
   typename expression_storage<Arg2>::type arg2;
   typename expression_storage<Arg3>::type arg3;
   typename expression_storage<Arg4>::type arg4;
   expression&                             operator=(const expression&);
};

template <class T>
struct digits2
{
   static_assert(std::numeric_limits<T>::is_specialized, "numeric_limits must be specialized here");
   static_assert((std::numeric_limits<T>::radix == 2) || (std::numeric_limits<T>::radix == 10), "Failed radix check");
   // If we really have so many digits that this fails, then we're probably going to hit other problems anyway:
   static_assert(LONG_MAX / 1000 > (std::numeric_limits<T>::digits + 1), "Too many digits to cope with here");
   static constexpr const long  m_value = std::numeric_limits<T>::radix == 10 ? (((std::numeric_limits<T>::digits + 1) * 1000L) / 301L) : std::numeric_limits<T>::digits;
   static inline constexpr long value() noexcept { return m_value; }
};

#ifndef BOOST_MP_MIN_EXPONENT_DIGITS
#ifdef _MSC_VER
#define BOOST_MP_MIN_EXPONENT_DIGITS 2
#else
#define BOOST_MP_MIN_EXPONENT_DIGITS 2
#endif
#endif

template <class S>
void format_float_string(S& str, std::intmax_t my_exp, std::intmax_t digits, std::ios_base::fmtflags f, bool iszero)
{
   using size_type = typename S::size_type;

   bool scientific = (f & std::ios_base::scientific) == std::ios_base::scientific;
   bool fixed      = (f & std::ios_base::fixed) == std::ios_base::fixed;
   bool showpoint  = (f & std::ios_base::showpoint) == std::ios_base::showpoint;
   bool showpos    = (f & std::ios_base::showpos) == std::ios_base::showpos;

   bool neg = str.size() && (str[0] == '-');

   if (neg)
      str.erase(0, 1);

   if (digits == 0 && !fixed)
   {
      digits = (std::max)(str.size(), size_type(16));
   }

   if (iszero || str.empty() || (str.find_first_not_of('0') == S::npos))
   {
      // We will be printing zero, even though the value might not
      // actually be zero (it just may have been rounded to zero).
      str = "0";
      if (scientific || fixed)
      {
         if (showpoint || digits > 0) {
            str.append(1, '.');
            if (digits > 0)
               str.append(size_type(digits), '0');
         }
         if (scientific)
            str.append("e+00");
      }
      else
      {
         if (showpoint)
         {
            str.append(1, '.');
            if (digits > 1)
               str.append(size_type(digits - 1), '0');
         }
      }
      if (neg)
         str.insert(static_cast<std::string::size_type>(0), 1, '-');
      else if (showpos)
         str.insert(static_cast<std::string::size_type>(0), 1, '+');
      return;
   }

   if (!fixed && !scientific && !showpoint)
   {
      //
      // Suppress trailing zeros:
      //
      std::string::iterator pos = str.end();
      while (pos != str.begin() && *--pos == '0')
      {
      }
      if (pos != str.end())
         ++pos;
      str.erase(pos, str.end());
      if (str.empty())
         str = '0';
   }
   else if (!fixed || (my_exp >= 0))
   {
      //
      // Pad out the end with zero's if we need to:
      //
      std::intmax_t chars = str.size();
      chars                 = digits - chars;
      if (scientific)
         ++chars;
      if (chars > 0)
      {
         str.append(static_cast<std::string::size_type>(chars), '0');
      }
   }

   if (fixed || (!scientific && (my_exp >= -4) && (my_exp < digits)))
   {
      if (1 + my_exp > static_cast<std::intmax_t>(str.size()))
      {
         // Just pad out the end with zeros:
         str.append(static_cast<std::string::size_type>(1 + my_exp - str.size()), '0');
         if (showpoint || (fixed && digits > 0))
            str.append(".");
      }
      else if (my_exp + 1 < static_cast<std::intmax_t>(str.size()))
      {
         if (my_exp < 0)
         {
            str.insert(static_cast<std::string::size_type>(0), static_cast<std::string::size_type>(-1 - my_exp), '0');
            str.insert(static_cast<std::string::size_type>(0), "0.");
         }
         else
         {
            // Insert the decimal point:
            str.insert(static_cast<std::string::size_type>(my_exp + 1), 1, '.');
         }
      }
      else if (showpoint || (fixed && digits > 0)) // we have exactly the digits we require to left of the point
         str += ".";

      if (fixed)
      {
         // We may need to add trailing zeros:
         auto pos = str.find('.');
         if (pos != str.npos) { // this test is probably redundant, but just to be safe and for clarity
            std::intmax_t l = pos + 1;
            l               = digits - (str.size() - l);
            if (l > 0)
               str.append(size_type(l), '0');
         }
      }
   }
   else
   {
      BOOST_MP_USING_ABS
      // Scientific format:
      if (showpoint || (str.size() > 1))
         str.insert(static_cast<std::string::size_type>(1u), 1, '.');
      str.append(static_cast<std::string::size_type>(1u), 'e');

      S e;

      #ifndef BOOST_MP_STANDALONE
      e = boost::lexical_cast<S>(abs(my_exp));
      #else
      BOOST_IF_CONSTEXPR(std::is_same<S, std::string>::value)
      {
         e = std::to_string(abs(my_exp));
      }
      else
      {
         const std::string str_local_exp = std::to_string(abs(my_exp));
         e = S(str_local_exp.cbegin(), str_local_exp.cend());
      }
      #endif

      if (e.size() < BOOST_MP_MIN_EXPONENT_DIGITS)
         e.insert(static_cast<std::string::size_type>(0), BOOST_MP_MIN_EXPONENT_DIGITS - e.size(), '0');
      if (my_exp < 0)
         e.insert(static_cast<std::string::size_type>(0), 1, '-');
      else
         e.insert(static_cast<std::string::size_type>(0), 1, '+');
      str.append(e);
   }
   if (neg)
      str.insert(static_cast<std::string::size_type>(0), 1, '-');
   else if (showpos)
      str.insert(static_cast<std::string::size_type>(0), 1, '+');
}

template <class V>
BOOST_MP_CXX14_CONSTEXPR void check_shift_range(V val, const std::integral_constant<bool, true>&, const std::integral_constant<bool, true>&)
{
   if (val > (std::numeric_limits<std::size_t>::max)())
      BOOST_MP_THROW_EXCEPTION(std::out_of_range("Can not shift by a value greater than std::numeric_limits<std::size_t>::max()."));
   if (val < 0)
      BOOST_MP_THROW_EXCEPTION(std::out_of_range("Can not shift by a negative value."));
}
template <class V>
BOOST_MP_CXX14_CONSTEXPR void check_shift_range(V val, const std::integral_constant<bool, false>&, const std::integral_constant<bool, true>&)
{
   if (val < 0)
      BOOST_MP_THROW_EXCEPTION(std::out_of_range("Can not shift by a negative value."));
}
template <class V>
BOOST_MP_CXX14_CONSTEXPR void check_shift_range(V val, const std::integral_constant<bool, true>&, const std::integral_constant<bool, false>&)
{
   if (val > (std::numeric_limits<std::size_t>::max)())
      BOOST_MP_THROW_EXCEPTION(std::out_of_range("Can not shift by a value greater than std::numeric_limits<std::size_t>::max()."));
}
template <class V>
BOOST_MP_CXX14_CONSTEXPR void check_shift_range(V, const std::integral_constant<bool, false>&, const std::integral_constant<bool, false>&) noexcept {}

template <class T>
BOOST_MP_CXX14_CONSTEXPR const T& evaluate_if_expression(const T& val) { return val; }
template <class T>
BOOST_MP_CXX14_CONSTEXPR T&& evaluate_if_expression(T&& val) { return static_cast<T&&>(val); }
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
BOOST_MP_CXX14_CONSTEXPR typename expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type evaluate_if_expression(const expression<tag, Arg1, Arg2, Arg3, Arg4>& val) { return val; }
template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
BOOST_MP_CXX14_CONSTEXPR typename expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type evaluate_if_expression(expression<tag, Arg1, Arg2, Arg3, Arg4>&& val) { return val; }

template <class T>
struct convertible_to
{
   operator T () const;
};

} // namespace detail

//
// Traits class, lets us know what kind of number we have, defaults to a floating point type:
//
enum number_category_type
{
   number_kind_unknown        = -1,
   number_kind_integer        = 0,
   number_kind_floating_point = 1,
   number_kind_rational       = 2,
   number_kind_fixed_point    = 3,
   number_kind_complex        = 4
};

template <class Num, bool, bool>
struct number_category_base : public std::integral_constant<int, number_kind_unknown>
{};
template <class Num>
struct number_category_base<Num, true, false> : public std::integral_constant<int, std::numeric_limits<Num>::is_integer ? number_kind_integer : (std::numeric_limits<Num>::max_exponent ? number_kind_floating_point : number_kind_unknown)>
{};
template <class Num>
struct number_category : public number_category_base<Num, std::is_class<Num>::value || boost::multiprecision::detail::is_arithmetic<Num>::value, std::is_abstract<Num>::value>
{};
template <class Backend, expression_template_option ExpressionTemplates>
struct number_category<number<Backend, ExpressionTemplates> > : public number_category<Backend>
{};
template <class tag, class A1, class A2, class A3, class A4>
struct number_category<detail::expression<tag, A1, A2, A3, A4> > : public number_category<typename detail::expression<tag, A1, A2, A3, A4>::result_type>
{};
//
// Specializations for types which do not always have numberic_limits specializations:
//
#ifdef BOOST_HAS_INT128
template <>
struct number_category<boost::multiprecision::int128_type> : public std::integral_constant<int, number_kind_integer>
{};
template <>
struct number_category<boost::multiprecision::uint128_type> : public std::integral_constant<int, number_kind_integer>
{};
#endif
#ifdef BOOST_HAS_FLOAT128
template <>
struct number_category<boost::multiprecision::float128_type> : public std::integral_constant<int, number_kind_floating_point>
{};
#endif

template <class T>
struct component_type
{
   using type = T;
};
template <class tag, class A1, class A2, class A3, class A4>
struct component_type<detail::expression<tag, A1, A2, A3, A4> > : public component_type<typename detail::expression<tag, A1, A2, A3, A4>::result_type>
{};

template <class T>
struct scalar_result_from_possible_complex
{
   using type = typename std::conditional<number_category<T>::value == number_kind_complex, typename component_type<T>::type, T>::type;
};

template <class T>
struct complex_result_from_scalar; // individual backends must specialize this trait.

template <class T>
struct is_unsigned_number : public std::integral_constant<bool, false>
{};
template <class Backend, expression_template_option ExpressionTemplates>
struct is_unsigned_number<number<Backend, ExpressionTemplates> > : public is_unsigned_number<Backend>
{};
template <class T>
struct is_signed_number : public std::integral_constant<bool, !is_unsigned_number<T>::value>
{};
template <class T>
struct is_interval_number : public std::integral_constant<bool, false>
{};
template <class Backend, expression_template_option ExpressionTemplates>
struct is_interval_number<number<Backend, ExpressionTemplates> > : public is_interval_number<Backend>
{};

template <class T, class U>
struct is_equivalent_number_type : public std::is_same<T, U>
{};

template <class Backend, expression_template_option ExpressionTemplates, class T2>
struct is_equivalent_number_type<number<Backend, ExpressionTemplates>, T2> : public is_equivalent_number_type<Backend, T2>
{};
template <class T1, class Backend, expression_template_option ExpressionTemplates>
struct is_equivalent_number_type<T1, number<Backend, ExpressionTemplates> > : public is_equivalent_number_type<Backend, T1>
{};
template <class Backend, expression_template_option ExpressionTemplates, class Backend2, expression_template_option ExpressionTemplates2>
struct is_equivalent_number_type<number<Backend, ExpressionTemplates>, number<Backend2, ExpressionTemplates2> > : public is_equivalent_number_type<Backend, Backend2>
{};

}
} // namespace boost

#ifdef BOOST_MP_MATH_AVAILABLE
namespace boost { namespace math {
   namespace tools {

      template <class T>
      struct promote_arg;

      template <class tag, class A1, class A2, class A3, class A4>
      struct promote_arg<boost::multiprecision::detail::expression<tag, A1, A2, A3, A4> >
      {
         using type = typename boost::multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type;
      };

      template <class R, class B, boost::multiprecision::expression_template_option ET>
      inline R real_cast(const boost::multiprecision::number<B, ET>& val)
      {
         return val.template convert_to<R>();
      }

      template <class R, class tag, class A1, class A2, class A3, class A4>
      inline R real_cast(const boost::multiprecision::detail::expression<tag, A1, A2, A3, A4>& val)
      {
         using val_type = typename boost::multiprecision::detail::expression<tag, A1, A2, A3, A4>::result_type;
         return val_type(val).template convert_to<R>();
      }

      template <class B, boost::multiprecision::expression_template_option ET>
      struct is_complex_type<boost::multiprecision::number<B, ET> > : public std::integral_constant<bool, boost::multiprecision::number_category<B>::value == boost::multiprecision::number_kind_complex> {};

} // namespace tools

namespace constants {

template <class T>
struct is_explicitly_convertible_from_string;

template <class B, boost::multiprecision::expression_template_option ET>
struct is_explicitly_convertible_from_string<boost::multiprecision::number<B, ET> >
{
   static constexpr const bool value = true;
};

} // namespace constants

}} // namespace boost::math
#endif

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_MATH_BIG_NUM_BASE_HPP

/* number_base.hpp
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
*/