///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_EXTENDED_REAL_HPP
#define BOOST_MATH_EXTENDED_REAL_HPP

#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/mpl/max.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/remove_pointer.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_unsigned.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_complex.hpp>
#include <boost/type_traits/make_unsigned.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/throw_exception.hpp>
#include <boost/multiprecision/detail/precision.hpp>
#include <boost/multiprecision/detail/generic_interconvert.hpp>
#include <boost/multiprecision/detail/number_compare.hpp>
#include <boost/multiprecision/traits/is_restricted_conversion.hpp>
#include <boost/container_hash/hash.hpp>
#include <istream> // stream operators
#include <cstdio>  // EOF
#include <cctype>  // isspace
#ifndef BOOST_NO_CXX17_HDR_STRING_VIEW
#include <string_view>
#endif

namespace boost {
namespace multiprecision {

#ifdef BOOST_MSVC
// warning C4127: conditional expression is constant
// warning C4714: function marked as __forceinline not inlined
#pragma warning(push)
#pragma warning(disable : 4127 4714 6326)
#endif

template <class Backend, expression_template_option ExpressionTemplates>
class number
{
   typedef number<Backend, ExpressionTemplates> self_type;

 public:
   typedef Backend                                  backend_type;
   typedef typename component_type<self_type>::type value_type;
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number() BOOST_MP_NOEXCEPT_IF(noexcept(Backend())) {}
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number(const number& e) BOOST_MP_NOEXCEPT_IF(noexcept(Backend(std::declval<Backend const&>()))) : m_backend(e.m_backend) {}
   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number(const V& v, typename boost::enable_if_c<
                                               (boost::is_arithmetic<V>::value || is_same<std::string, V>::value || is_convertible<V, const char*>::value) && !is_convertible<typename detail::canonical<V, Backend>::type, Backend>::value && !detail::is_restricted_conversion<typename detail::canonical<V, Backend>::type, Backend>::value
#ifdef BOOST_HAS_FLOAT128
                                               && !boost::is_same<V, __float128>::value
#endif
                                               >::type* = 0)
   {
      m_backend = canonical_value(v);
   }
   template <class V>
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number(const V& v, typename boost::enable_if_c<
                                                               is_convertible<typename detail::canonical<V, Backend>::type, Backend>::value && !detail::is_restricted_conversion<typename detail::canonical<V, Backend>::type, Backend>::value>::type* = 0)
#ifndef BOOST_INTEL
       BOOST_MP_NOEXCEPT_IF(noexcept(Backend(std::declval<typename detail::canonical<V, Backend>::type const&>())))
#endif
       : m_backend(canonical_value(v))
   {}
   template <class V>
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number(const V& v, unsigned digits10, typename boost::enable_if_c<(boost::is_arithmetic<V>::value || is_same<std::string, V>::value || is_convertible<V, const char*>::value) && !detail::is_restricted_conversion<typename detail::canonical<V, Backend>::type, Backend>::value && (boost::multiprecision::number_category<Backend>::value != boost::multiprecision::number_kind_complex) && (boost::multiprecision::number_category<Backend>::value != boost::multiprecision::number_kind_rational)
#ifdef BOOST_HAS_FLOAT128
                                                                                                          && !boost::is_same<V, __float128>::value
#endif
                                                                                                          >::type* = 0)
       : m_backend(canonical_value(v), digits10)
   {}
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number(const number& e, unsigned digits10)
       BOOST_MP_NOEXCEPT_IF(noexcept(Backend(std::declval<Backend const&>(), std::declval<unsigned>())))
       : m_backend(e.m_backend, digits10) {}
   template <class V>
   explicit BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number(const V& v, typename boost::enable_if_c<
                                                        (boost::is_arithmetic<V>::value || is_same<std::string, V>::value || is_convertible<V, const char*>::value) && !detail::is_explicitly_convertible<typename detail::canonical<V, Backend>::type, Backend>::value && detail::is_restricted_conversion<typename detail::canonical<V, Backend>::type, Backend>::value>::type* = 0)
       BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<Backend&>() = std::declval<typename detail::canonical<V, Backend>::type const&>()))
   {
      m_backend = canonical_value(v);
   }
   template <class V>
   explicit BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number(const V& v, typename boost::enable_if_c<
                                                                        detail::is_explicitly_convertible<typename detail::canonical<V, Backend>::type, Backend>::value && (detail::is_restricted_conversion<typename detail::canonical<V, Backend>::type, Backend>::value || !is_convertible<typename detail::canonical<V, Backend>::type, Backend>::value)>::type* = 0)
       BOOST_MP_NOEXCEPT_IF(noexcept(Backend(std::declval<typename detail::canonical<V, Backend>::type const&>())))
       : m_backend(canonical_value(v)) {}
   template <class V>
   explicit BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number(const V& v, unsigned digits10, typename boost::enable_if_c<(boost::is_arithmetic<V>::value || is_same<std::string, V>::value || is_convertible<V, const char*>::value) && detail::is_restricted_conversion<typename detail::canonical<V, Backend>::type, Backend>::value && (boost::multiprecision::number_category<Backend>::value != boost::multiprecision::number_kind_complex) && (boost::multiprecision::number_category<Backend>::value != boost::multiprecision::number_kind_rational)>::type* = 0)
       : m_backend(canonical_value(v), digits10) {}

   template <expression_template_option ET>
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number(const number<Backend, ET>& val)
       BOOST_MP_NOEXCEPT_IF(noexcept(Backend(std::declval<Backend const&>()))) : m_backend(val.backend()) {}

   template <class Other, expression_template_option ET>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number(const number<Other, ET>& val,
                               typename boost::enable_if_c<(boost::is_convertible<Other, Backend>::value && !detail::is_restricted_conversion<Other, Backend>::value)>::type* = 0)
       BOOST_MP_NOEXCEPT_IF(noexcept(Backend(std::declval<Other const&>())))
       : m_backend(val.backend()) {}

   template <class Other, expression_template_option ET>
   explicit BOOST_MP_CXX14_CONSTEXPR number(const number<Other, ET>& val, typename boost::enable_if_c<
                                                     (!detail::is_explicitly_convertible<Other, Backend>::value)>::type* = 0)
   {
      //
      // Attempt a generic interconvertion:
      //
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard_1(val);
      detail::scoped_default_precision<number<Other, ET> >                    precision_guard_2(val);
      using detail::generic_interconvert;
      generic_interconvert(backend(), val.backend(), number_category<Backend>(), number_category<Other>());
   }
   template <class Other, expression_template_option ET>
   explicit BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number(const number<Other, ET>& val, typename boost::enable_if_c<
                                                                          (detail::is_explicitly_convertible<Other, Backend>::value && (detail::is_restricted_conversion<Other, Backend>::value || !boost::is_convertible<Other, Backend>::value))>::type* = 0) BOOST_MP_NOEXCEPT_IF(noexcept(Backend(std::declval<Other const&>())))
       : m_backend(val.backend()) {}

   template <class V, class U>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number(const V& v1, const U& v2,
                               typename boost::enable_if_c<(is_convertible<V, value_type>::value && is_convertible<U, value_type>::value && !is_same<typename component_type<self_type>::type, self_type>::value)>::type* = 0)
   {
      using default_ops::assign_components;
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(v1, v2);
      assign_components(m_backend, canonical_value(detail::evaluate_if_expression(v1)), canonical_value(detail::evaluate_if_expression(v2)));
   }
   template <class V, class U>
   BOOST_MP_FORCEINLINE explicit BOOST_MP_CXX14_CONSTEXPR number(const V& v1, const U& v2,
                                        typename boost::enable_if_c<
                                            (is_constructible<value_type, V>::value || is_convertible<V, std::string>::value) && (is_constructible<value_type, U>::value || is_convertible<U, std::string>::value) && !is_same<typename component_type<self_type>::type, self_type>::value && !is_same<V, self_type>::value && !(is_convertible<V, value_type>::value && is_convertible<U, value_type>::value)>::type* = 0)
   {
      using default_ops::assign_components;
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(v1, v2);
      assign_components(m_backend, canonical_value(detail::evaluate_if_expression(v1)), canonical_value(detail::evaluate_if_expression(v2)));
   }
#ifndef BOOST_NO_CXX17_HDR_STRING_VIEW
   //
   // Support for new types in C++17
   //
   template <class Traits>
   explicit inline BOOST_MP_CXX14_CONSTEXPR number(const std::basic_string_view<char, Traits>& view)
   {
      using default_ops::assign_from_string_view;
      assign_from_string_view(this->backend(), view);
   }
   template <class Traits>
   explicit inline BOOST_MP_CXX14_CONSTEXPR number(const std::basic_string_view<char, Traits>& view_x, const std::basic_string_view<char, Traits>& view_y)
   {
      using default_ops::assign_from_string_view;
      assign_from_string_view(this->backend(), view_x, view_y);
   }
   template <class Traits>
   explicit BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number(const std::basic_string_view<char, Traits>& v, unsigned digits10)
       : m_backend(canonical_value(v), digits10) {}
   template <class Traits>
   BOOST_MP_CXX14_CONSTEXPR number& assign(const std::basic_string_view<char, Traits>& view)
   {
      using default_ops::assign_from_string_view;
      assign_from_string_view(this->backend(), view);
      return *this;
   }
#endif

   template <class V, class U>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number(const V& v1, const U& v2, unsigned digits10,
                               typename boost::enable_if_c<(is_convertible<V, value_type>::value && is_convertible<U, value_type>::value && !is_same<typename component_type<self_type>::type, self_type>::value)>::type* = 0)
       : m_backend(canonical_value(detail::evaluate_if_expression(v1)), canonical_value(detail::evaluate_if_expression(v2)), digits10)
   {}
   template <class V, class U>
   BOOST_MP_FORCEINLINE explicit BOOST_MP_CXX14_CONSTEXPR number(const V& v1, const U& v2, unsigned digits10,
                                        typename boost::enable_if_c<((is_constructible<value_type, V>::value || is_convertible<V, std::string>::value) && (is_constructible<value_type, U>::value || is_convertible<U, std::string>::value) && !is_same<typename component_type<self_type>::type, self_type>::value) && !(is_convertible<V, value_type>::value && is_convertible<U, value_type>::value)>::type* = 0)
       : m_backend(canonical_value(detail::evaluate_if_expression(v1)), canonical_value(detail::evaluate_if_expression(v2)), digits10) {}

   template <class Other, expression_template_option ET>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number(const number<Other, ET>& v1, const number<Other, ET>& v2, typename boost::enable_if_c<boost::is_convertible<Other, Backend>::value>::type* = 0)
   {
      using default_ops::assign_components;
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(v1, v2);
      assign_components(m_backend, v1.backend(), v2.backend());
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      typedef mpl::bool_<is_same<number, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value> tag_type;
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> >                                       precision_guard(e);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(e);
         return *this = BOOST_MP_MOVE(t);
      }
      do_assign(e, tag_type());
      return *this;
   }
   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR number& assign(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      typedef mpl::bool_<is_same<number, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type>::value> tag_type;
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> >                                       precision_guard(e);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t;
         t.assign(e);
         return *this = BOOST_MP_MOVE(t);
      }
      do_assign(e, tag_type());
      return *this;
   }

   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number& operator=(const number& e)
       BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<Backend&>() = std::declval<Backend const&>()))
   {
      m_backend = e.m_backend;
      return *this;
   }

   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
   operator=(const V& v)
       BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<Backend&>() = std::declval<const typename detail::canonical<V, Backend>::type&>()))
   {
      m_backend = canonical_value(v);
      return *this;
   }
   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<Backend, ExpressionTemplates>& assign(const V& v)
       BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<Backend&>() = std::declval<const typename detail::canonical<V, Backend>::type&>()))
   {
      m_backend = canonical_value(v);
      return *this;
   }
   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number<Backend, ExpressionTemplates>& assign(const V& v, unsigned digits10)
       BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<Backend&>() = std::declval<const typename detail::canonical<V, Backend>::type&>()))
   {
      number t(v, digits10);
      return *this = t;
   }
   template <class Other, expression_template_option ET>
   BOOST_MP_CXX14_CONSTEXPR typename boost::disable_if<boost::multiprecision::detail::is_explicitly_convertible<Other, Backend>, number<Backend, ExpressionTemplates>&>::type
   assign(const number<Other, ET>& v)
   {
      //
      // Attempt a generic interconvertion:
      //
      using detail::generic_interconvert;
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(v);
      detail::scoped_default_precision<number<Other, ET> >                    precision_guard2(v);
      //
      // If the current precision of *this differs from that of value v, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(v);
         return *this = BOOST_MP_MOVE(t);
      }
      generic_interconvert(backend(), v.backend(), number_category<Backend>(), number_category<Other>());
      return *this;
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR number(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e, typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value>::type* = 0)
   {
      //
      // No preicsion guard here, we already have one in operator=
      //
      *this = e;
   }
   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   explicit BOOST_MP_CXX14_CONSTEXPR number(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e,
                   typename boost::enable_if_c<!is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value && boost::multiprecision::detail::is_explicitly_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value>::type* = 0)
   {
      //
      // No precision guard as assign has one already:
      //
      assign(e);
   }

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR number(number&& r)
       BOOST_MP_NOEXCEPT_IF(noexcept(Backend(std::declval<Backend>())))
       : m_backend(static_cast<Backend&&>(r.m_backend))
   {}
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number& operator=(number&& r) BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<Backend&>() = std::declval<Backend>()))
   {
      m_backend = static_cast<Backend&&>(r.m_backend);
      return *this;
   }
#endif

   BOOST_MP_CXX14_CONSTEXPR number& operator+=(const self_type& val)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, val);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(*this + val);
         return *this = BOOST_MP_MOVE(t);
      }
      do_add(detail::expression<detail::terminal, self_type>(val), detail::terminal());
      return *this;
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator+=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      // Create a copy if e contains this, but not if we're just doing a
      //    x += x
      if ((contains_self(e) && !is_self(e)))
      {
         self_type temp(e);
         do_add(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
      }
      else
      {
         do_add(e, tag());
      }
      return *this;
   }

   template <class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR number& operator+=(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& e)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(*this + e);
         return *this = BOOST_MP_MOVE(t);
      }
      //
      // Fused multiply-add:
      //
      using default_ops::eval_multiply_add;
      eval_multiply_add(m_backend, canonical_value(e.left_ref()), canonical_value(e.right_ref()));
      return *this;
   }

   template <class V>
   typename boost::enable_if_c<boost::is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
      BOOST_MP_CXX14_CONSTEXPR operator+=(const V& v)
   {
      using default_ops::eval_add;
      eval_add(m_backend, canonical_value(v));
      return *this;
   }

   BOOST_MP_CXX14_CONSTEXPR number& operator-=(const self_type& val)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, val);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(*this - val);
         return *this = BOOST_MP_MOVE(t);
      }
      do_subtract(detail::expression<detail::terminal, self_type>(val), detail::terminal());
      return *this;
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator-=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      // Create a copy if e contains this:
      if (contains_self(e))
      {
         self_type temp(e);
         do_subtract(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
      }
      else
      {
         do_subtract(e, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::tag_type());
      }
      return *this;
   }

   template <class V>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
   operator-=(const V& v)
   {
      using default_ops::eval_subtract;
      eval_subtract(m_backend, canonical_value(v));
      return *this;
   }

   template <class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR number& operator-=(const detail::expression<detail::multiply_immediates, Arg1, Arg2, Arg3, Arg4>& e)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(*this - e);
         return *this = BOOST_MP_MOVE(t);
      }
      //
      // Fused multiply-subtract:
      //
      using default_ops::eval_multiply_subtract;
      eval_multiply_subtract(m_backend, canonical_value(e.left_ref()), canonical_value(e.right_ref()));
      return *this;
   }

   BOOST_MP_CXX14_CONSTEXPR number& operator*=(const self_type& e)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(*this * e);
         return *this = BOOST_MP_MOVE(t);
      }
      do_multiplies(detail::expression<detail::terminal, self_type>(e), detail::terminal());
      return *this;
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator*=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      // Create a temporary if the RHS references *this, but not
      // if we're just doing an   x *= x;
      if ((contains_self(e) && !is_self(e)))
      {
         self_type temp(e);
         do_multiplies(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
      }
      else
      {
         do_multiplies(e, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::tag_type());
      }
      return *this;
   }

   template <class V>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
   operator*=(const V& v)
   {
      using default_ops::eval_multiply;
      eval_multiply(m_backend, canonical_value(v));
      return *this;
   }

   BOOST_MP_CXX14_CONSTEXPR number& operator%=(const self_type& e)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The modulus operation is only valid for integer types");
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(*this % e);
         return *this = BOOST_MP_MOVE(t);
      }
      do_modulus(detail::expression<detail::terminal, self_type>(e), detail::terminal());
      return *this;
   }
   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator%=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The modulus operation is only valid for integer types");
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      // Create a temporary if the RHS references *this:
      if (contains_self(e))
      {
         self_type temp(e);
         do_modulus(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
      }
      else
      {
         do_modulus(e, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::tag_type());
      }
      return *this;
   }
   template <class V>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
   operator%=(const V& v)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The modulus operation is only valid for integer types");
      using default_ops::eval_modulus;
      eval_modulus(m_backend, canonical_value(v));
      return *this;
   }

   //
   // These operators are *not* proto-ized.
   // The issue is that the increment/decrement must happen
   // even if the result of the operator *is never used*.
   // Possibly we could modify our expression wrapper to
   // execute the increment/decrement on destruction, but
   // correct implementation will be tricky, so defered for now...
   //
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number& operator++()
   {
      using default_ops::eval_increment;
      eval_increment(m_backend);
      return *this;
   }

   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number& operator--()
   {
      using default_ops::eval_decrement;
      eval_decrement(m_backend);
      return *this;
   }

   inline BOOST_MP_CXX14_CONSTEXPR number operator++(int)
   {
      using default_ops::eval_increment;
      self_type temp(*this);
      eval_increment(m_backend);
      return temp;
   }

   inline BOOST_MP_CXX14_CONSTEXPR number operator--(int)
   {
      using default_ops::eval_decrement;
      self_type temp(*this);
      eval_decrement(m_backend);
      return temp;
   }

   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_integral<V>::value, number&>::type operator<<=(V val)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The left-shift operation is only valid for integer types");
      detail::check_shift_range(val, mpl::bool_<(sizeof(V) > sizeof(std::size_t))>(), mpl::bool_<is_signed<V>::value>());
      eval_left_shift(m_backend, static_cast<std::size_t>(canonical_value(val)));
      return *this;
   }

   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_integral<V>::value, number&>::type operator>>=(V val)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The right-shift operation is only valid for integer types");
      detail::check_shift_range(val, mpl::bool_<(sizeof(V) > sizeof(std::size_t))>(), mpl::bool_<is_signed<V>::value>());
      eval_right_shift(m_backend, static_cast<std::size_t>(canonical_value(val)));
      return *this;
   }

   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number& operator/=(const self_type& e)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      //
      // If the current precision of *this differs from that of expression e, then we
      // create a temporary (which will have the correct precision thanks to precision_guard)
      // and then move the result into *this.  In C++17 we add a leading "if constexpr"
      // which causes this code to be eliminated in the common case that this type is
      // not actually variable precision.  Pre C++17 this code should still be mostly
      // optimised away, but we can't prevent instantiation of the dead code leading
      // to longer build and possibly link times.
      //
      BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(number)
      if (precision_guard.precision() != boost::multiprecision::detail::current_precision_of(*this))
      {
         number t(*this / e);
         return *this = BOOST_MP_MOVE(t);
      }
      do_divide(detail::expression<detail::terminal, self_type>(e), detail::terminal());
      return *this;
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator/=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      detail::scoped_default_precision<number<Backend, ExpressionTemplates> > precision_guard(*this, e);
      // Create a temporary if the RHS references *this:
      if (contains_self(e))
      {
         self_type temp(e);
         do_divide(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
      }
      else
      {
         do_divide(e, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::tag_type());
      }
      return *this;
   }

   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
   operator/=(const V& v)
   {
      using default_ops::eval_divide;
      eval_divide(m_backend, canonical_value(v));
      return *this;
   }

   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number& operator&=(const self_type& e)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise & operation is only valid for integer types");
      do_bitwise_and(detail::expression<detail::terminal, self_type>(e), detail::terminal());
      return *this;
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator&=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise & operation is only valid for integer types");
      // Create a temporary if the RHS references *this, but not
      // if we're just doing an   x &= x;
      if (contains_self(e) && !is_self(e))
      {
         self_type temp(e);
         do_bitwise_and(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
      }
      else
      {
         do_bitwise_and(e, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::tag_type());
      }
      return *this;
   }

   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
   operator&=(const V& v)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise & operation is only valid for integer types");
      using default_ops::eval_bitwise_and;
      eval_bitwise_and(m_backend, canonical_value(v));
      return *this;
   }

   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number& operator|=(const self_type& e)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise | operation is only valid for integer types");
      do_bitwise_or(detail::expression<detail::terminal, self_type>(e), detail::terminal());
      return *this;
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator|=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise | operation is only valid for integer types");
      // Create a temporary if the RHS references *this, but not
      // if we're just doing an   x |= x;
      if (contains_self(e) && !is_self(e))
      {
         self_type temp(e);
         do_bitwise_or(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
      }
      else
      {
         do_bitwise_or(e, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::tag_type());
      }
      return *this;
   }

   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
   operator|=(const V& v)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise | operation is only valid for integer types");
      using default_ops::eval_bitwise_or;
      eval_bitwise_or(m_backend, canonical_value(v));
      return *this;
   }

   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR number& operator^=(const self_type& e)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise ^ operation is only valid for integer types");
      do_bitwise_xor(detail::expression<detail::terminal, self_type>(e), detail::terminal());
      return *this;
   }

   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_convertible<typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type, self_type>::value, number&>::type operator^=(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise ^ operation is only valid for integer types");
      if (contains_self(e))
      {
         self_type temp(e);
         do_bitwise_xor(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
      }
      else
      {
         do_bitwise_xor(e, typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::tag_type());
      }
      return *this;
   }

   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<V, self_type>::value, number<Backend, ExpressionTemplates>&>::type
   operator^=(const V& v)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise ^ operation is only valid for integer types");
      using default_ops::eval_bitwise_xor;
      eval_bitwise_xor(m_backend, canonical_value(v));
      return *this;
   }
   //
   // swap:
   //
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR void swap(self_type& other) BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<Backend>().swap(std::declval<Backend&>())))
   {
      m_backend.swap(other.backend());
   }
   //
   // Zero and sign:
   //
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR bool is_zero() const
   {
      using default_ops::eval_is_zero;
      return eval_is_zero(m_backend);
   }
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR int sign() const
   {
      using default_ops::eval_get_sign;
      return eval_get_sign(m_backend);
   }
   //
   // String conversion functions:
   //
   std::string str(std::streamsize digits = 0, std::ios_base::fmtflags f = std::ios_base::fmtflags(0)) const
   {
      return m_backend.str(digits, f);
   }
   template <class Archive>
   void serialize(Archive& ar, const unsigned int /*version*/)
   {
      ar& boost::make_nvp("backend", m_backend);
   }

 private:
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR void convert_to_imp(T* result) const
   {
      using default_ops::eval_convert_to;
      eval_convert_to(result, m_backend);
   }
   template <class B2, expression_template_option ET>
   BOOST_MP_CXX14_CONSTEXPR void convert_to_imp(number<B2, ET>* result) const
   {
      result->assign(*this);
   }
   BOOST_MP_CXX14_CONSTEXPR void convert_to_imp(std::string* result) const
   {
      *result = this->str();
   }

 public:
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR T convert_to() const
   {
      T result = T();
      convert_to_imp(&result);
      return result;
   }
   //
   // Use in boolean context, and explicit conversion operators:
   //
#ifndef BOOST_MP_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#if (defined(__GNUC__) && (__GNUC__ == 4) && (__GNUC_MINOR__ < 7) && !defined(__clang__)) || (defined(BOOST_INTEL) && (BOOST_INTEL <= 1500))
   //
   // Horrible workaround for gcc-4.6.x which always prefers the template
   // operator bool() rather than the non-template operator when converting to
   // an arithmetic type:
   //
   template <class T, typename boost::enable_if_c<is_same<T, bool>::value, int>::type = 0>
   explicit operator T() const
   {
      using default_ops::eval_is_zero;
      return !eval_is_zero(backend());
   }
   template <class T, typename boost::disable_if_c<is_same<T, bool>::value || is_void<T>::value, int>::type = 0>
   explicit operator T() const
   {
      return this->template convert_to<T>();
   }
#else
#if BOOST_WORKAROUND(BOOST_MSVC, < 1900) || (defined(__apple_build_version__) && BOOST_WORKAROUND(__clang_major__, < 9))
   template <class T>
#else
   template <class T, class = typename boost::disable_if_c<boost::is_constructible<T, self_type const&>::value || !boost::is_default_constructible<T>::value || (!boost::is_arithmetic<T>::value && !boost::is_complex<T>::value), T>::type>
#endif
   explicit BOOST_MP_CXX14_CONSTEXPR operator T() const
   {
      return this->template convert_to<T>();
   }
   BOOST_MP_FORCEINLINE explicit BOOST_MP_CXX14_CONSTEXPR operator bool() const
   {
      return !is_zero();
   }
#if BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40800)
   BOOST_MP_FORCEINLINE explicit operator void() const
   {}
#endif
#endif
#else
   typedef bool (self_type::*unmentionable_type)() const;

   BOOST_MP_FORCEINLINE operator unmentionable_type() const
   {
      return is_zero() ? 0 : &self_type::is_zero;
   }
#endif
   //
   // Default precision:
   //
   static BOOST_MP_CXX14_CONSTEXPR unsigned default_precision() BOOST_NOEXCEPT
   {
      return Backend::default_precision();
   }
   static BOOST_MP_CXX14_CONSTEXPR void default_precision(unsigned digits10)
   {
      Backend::default_precision(digits10);
   }
   BOOST_MP_CXX14_CONSTEXPR unsigned precision() const BOOST_NOEXCEPT
   {
      return m_backend.precision();
   }
   BOOST_MP_CXX14_CONSTEXPR void precision(unsigned digits10)
   {
      m_backend.precision(digits10);
   }
   //
   // Comparison:
   //
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR int compare(const number<Backend, ExpressionTemplates>& o) const
       BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<Backend>().compare(std::declval<Backend>())))
   {
      return m_backend.compare(o.m_backend);
   }
   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_arithmetic<V>::value && (number_category<Backend>::value != number_kind_complex), int>::type compare(const V& o) const
   {
      using default_ops::eval_get_sign;
      if (o == 0)
         return eval_get_sign(m_backend);
      return m_backend.compare(canonical_value(o));
   }
   template <class V>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR typename boost::enable_if_c<is_arithmetic<V>::value && (number_category<Backend>::value == number_kind_complex), int>::type compare(const V& o) const
   {
      using default_ops::eval_get_sign;
      return m_backend.compare(canonical_value(o));
   }
   //
   // Direct access to the underlying backend:
   //
#if !(defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_NO_CXX11_REF_QUALIFIERS) || BOOST_WORKAROUND(BOOST_GCC, < 50000))
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR Backend& backend() & BOOST_NOEXCEPT
   {
      return m_backend;
   }
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR const Backend& backend() const& BOOST_NOEXCEPT { return m_backend; }
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR Backend&& backend() && BOOST_NOEXCEPT { return static_cast<Backend&&>(m_backend); }
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR Backend const&& backend() const&& BOOST_NOEXCEPT { return static_cast<Backend const&&>(m_backend); }
#else
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR Backend& backend() BOOST_NOEXCEPT
   {
      return m_backend;
   }
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR const Backend& backend() const BOOST_NOEXCEPT { return m_backend; }
#endif
   //
   // Complex number real and imag:
   //
   BOOST_MP_CXX14_CONSTEXPR typename scalar_result_from_possible_complex<number<Backend, ExpressionTemplates> >::type
   real() const
   {
      using default_ops::eval_real;
      detail::scoped_default_precision<typename scalar_result_from_possible_complex<multiprecision::number<Backend, ExpressionTemplates> >::type> precision_guard(*this);
      typename scalar_result_from_possible_complex<multiprecision::number<Backend, ExpressionTemplates> >::type                                   result;
      eval_real(result.backend(), backend());
      return result;
   }
   BOOST_MP_CXX14_CONSTEXPR typename scalar_result_from_possible_complex<number<Backend, ExpressionTemplates> >::type
   imag() const
   {
      using default_ops::eval_imag;
      detail::scoped_default_precision<typename scalar_result_from_possible_complex<multiprecision::number<Backend, ExpressionTemplates> >::type> precision_guard(*this);
      typename scalar_result_from_possible_complex<multiprecision::number<Backend, ExpressionTemplates> >::type                                   result;
      eval_imag(result.backend(), backend());
      return result;
   }
   template <class T>
   inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<boost::is_convertible<T, self_type>::value, self_type&>::type real(const T& val)
   {
      using default_ops::eval_set_real;
      eval_set_real(backend(), canonical_value(val));
      return *this;
   }
   template <class T>
   inline BOOST_MP_CXX14_CONSTEXPR typename enable_if_c<boost::is_convertible<T, self_type>::value && number_category<self_type>::value == number_kind_complex, self_type&>::type imag(const T& val)
   {
      using default_ops::eval_set_imag;
      eval_set_imag(backend(), canonical_value(val));
      return *this;
   }

 private:
   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e, const mpl::true_&)
   {
      do_assign(e, tag());
   }
   template <class tag, class Arg1, class Arg2, class Arg3, class Arg4>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const detail::expression<tag, Arg1, Arg2, Arg3, Arg4>& e, const mpl::false_&)
   {
      // The result of the expression isn't the same type as this -
      // create a temporary result and assign it to *this:
      typedef typename detail::expression<tag, Arg1, Arg2, Arg3, Arg4>::result_type temp_type;
      temp_type                                                                     t(e);
      this->assign(t);
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::add_immediates&)
   {
      using default_ops::eval_add;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_add(m_backend, canonical_value(e.left().value()), canonical_value(e.right().value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::subtract_immediates&)
   {
      using default_ops::eval_subtract;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_subtract(m_backend, canonical_value(e.left().value()), canonical_value(e.right().value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::multiply_immediates&)
   {
      using default_ops::eval_multiply;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_multiply(m_backend, canonical_value(e.left().value()), canonical_value(e.right().value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::multiply_add&)
   {
      using default_ops::eval_multiply_add;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_multiply_add(m_backend, canonical_value(e.left().value()), canonical_value(e.middle().value()), canonical_value(e.right().value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::multiply_subtract&)
   {
      using default_ops::eval_multiply_subtract;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_multiply_subtract(m_backend, canonical_value(e.left().value()), canonical_value(e.middle().value()), canonical_value(e.right().value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::divide_immediates&)
   {
      using default_ops::eval_divide;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_divide(m_backend, canonical_value(e.left().value()), canonical_value(e.right().value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::negate&)
   {
      typedef typename Exp::left_type left_type;
      do_assign(e.left(), typename left_type::tag_type());
      m_backend.negate();
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::plus&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;

      BOOST_CONSTEXPR int const left_depth  = left_type::depth;
      BOOST_CONSTEXPR int const right_depth = right_type::depth;

      bool bl = contains_self(e.left());
      bool br = contains_self(e.right());

      if (bl && br)
      {
         self_type temp(e);
         temp.m_backend.swap(this->m_backend);
      }
      else if (bl && is_self(e.left()))
      {
         // Ignore the left node, it's *this, just add the right:
         do_add(e.right(), typename right_type::tag_type());
      }
      else if (br && is_self(e.right()))
      {
         // Ignore the right node, it's *this, just add the left:
         do_add(e.left(), typename left_type::tag_type());
      }
      else if (!br && (bl || (left_depth >= right_depth)))
      { // br is always false, but if bl is true we must take the this branch:
         do_assign(e.left(), typename left_type::tag_type());
         do_add(e.right(), typename right_type::tag_type());
      }
      else
      {
         do_assign(e.right(), typename right_type::tag_type());
         do_add(e.left(), typename left_type::tag_type());
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::minus&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;

      BOOST_CONSTEXPR int const left_depth  = left_type::depth;
      BOOST_CONSTEXPR int const right_depth = right_type::depth;

      bool bl = contains_self(e.left());
      bool br = contains_self(e.right());

      if (bl && br)
      {
         self_type temp(e);
         temp.m_backend.swap(this->m_backend);
      }
      else if (bl && is_self(e.left()))
      {
         // Ignore the left node, it's *this, just subtract the right:
         do_subtract(e.right(), typename right_type::tag_type());
      }
      else if (br && is_self(e.right()))
      {
         // Ignore the right node, it's *this, just subtract the left and negate the result:
         do_subtract(e.left(), typename left_type::tag_type());
         m_backend.negate();
      }
      else if (!br && (bl || (left_depth >= right_depth)))
      { // br is always false, but if bl is true we must take the this branch:
         do_assign(e.left(), typename left_type::tag_type());
         do_subtract(e.right(), typename right_type::tag_type());
      }
      else
      {
         do_assign(e.right(), typename right_type::tag_type());
         do_subtract(e.left(), typename left_type::tag_type());
         m_backend.negate();
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::multiplies&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;

      BOOST_CONSTEXPR int const left_depth  = left_type::depth;
      BOOST_CONSTEXPR int const right_depth = right_type::depth;

      bool bl = contains_self(e.left());
      bool br = contains_self(e.right());

      if (bl && br)
      {
         self_type temp(e);
         temp.m_backend.swap(this->m_backend);
      }
      else if (bl && is_self(e.left()))
      {
         // Ignore the left node, it's *this, just add the right:
         do_multiplies(e.right(), typename right_type::tag_type());
      }
      else if (br && is_self(e.right()))
      {
         // Ignore the right node, it's *this, just add the left:
         do_multiplies(e.left(), typename left_type::tag_type());
      }
      else if (!br && (bl || (left_depth >= right_depth)))
      { // br is always false, but if bl is true we must take the this branch:
         do_assign(e.left(), typename left_type::tag_type());
         do_multiplies(e.right(), typename right_type::tag_type());
      }
      else
      {
         do_assign(e.right(), typename right_type::tag_type());
         do_multiplies(e.left(), typename left_type::tag_type());
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::divides&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;

      bool bl = contains_self(e.left());
      bool br = contains_self(e.right());

      if (bl && is_self(e.left()))
      {
         // Ignore the left node, it's *this, just add the right:
         do_divide(e.right(), typename right_type::tag_type());
      }
      else if (br)
      {
         self_type temp(e);
         temp.m_backend.swap(this->m_backend);
      }
      else
      {
         do_assign(e.left(), typename left_type::tag_type());
         do_divide(e.right(), typename right_type::tag_type());
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::modulus&)
   {
      //
      // This operation is only valid for integer backends:
      //
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The modulus operation is only valid for integer types");

      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;

      bool bl = contains_self(e.left());
      bool br = contains_self(e.right());

      if (bl && is_self(e.left()))
      {
         // Ignore the left node, it's *this, just add the right:
         do_modulus(e.right(), typename right_type::tag_type());
      }
      else if (br)
      {
         self_type temp(e);
         temp.m_backend.swap(this->m_backend);
      }
      else
      {
         do_assign(e.left(), typename left_type::tag_type());
         do_modulus(e.right(), typename right_type::tag_type());
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::modulus_immediates&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The modulus operation is only valid for integer types");
      using default_ops::eval_modulus;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_modulus(m_backend, canonical_value(e.left().value()), canonical_value(e.right().value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::bitwise_and&)
   {
      //
      // This operation is only valid for integer backends:
      //
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "Bitwise operations are only valid for integer types");

      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;

      BOOST_CONSTEXPR int const left_depth  = left_type::depth;
      BOOST_CONSTEXPR int const right_depth = right_type::depth;

      bool bl = contains_self(e.left());
      bool br = contains_self(e.right());

      if (bl && is_self(e.left()))
      {
         // Ignore the left node, it's *this, just add the right:
         do_bitwise_and(e.right(), typename right_type::tag_type());
      }
      else if (br && is_self(e.right()))
      {
         do_bitwise_and(e.left(), typename left_type::tag_type());
      }
      else if (!br && (bl || (left_depth >= right_depth)))
      {
         do_assign(e.left(), typename left_type::tag_type());
         do_bitwise_and(e.right(), typename right_type::tag_type());
      }
      else
      {
         do_assign(e.right(), typename right_type::tag_type());
         do_bitwise_and(e.left(), typename left_type::tag_type());
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::bitwise_and_immediates&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "Bitwise operations are only valid for integer types");
      using default_ops::eval_bitwise_and;
      eval_bitwise_and(m_backend, canonical_value(e.left().value()), canonical_value(e.right().value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::bitwise_or&)
   {
      //
      // This operation is only valid for integer backends:
      //
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "Bitwise operations are only valid for integer types");

      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;

      BOOST_CONSTEXPR int const left_depth  = left_type::depth;
      BOOST_CONSTEXPR int const right_depth = right_type::depth;

      bool bl = contains_self(e.left());
      bool br = contains_self(e.right());

      if (bl && is_self(e.left()))
      {
         // Ignore the left node, it's *this, just add the right:
         do_bitwise_or(e.right(), typename right_type::tag_type());
      }
      else if (br && is_self(e.right()))
      {
         do_bitwise_or(e.left(), typename left_type::tag_type());
      }
      else if (!br && (bl || (left_depth >= right_depth)))
      {
         do_assign(e.left(), typename left_type::tag_type());
         do_bitwise_or(e.right(), typename right_type::tag_type());
      }
      else
      {
         do_assign(e.right(), typename right_type::tag_type());
         do_bitwise_or(e.left(), typename left_type::tag_type());
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::bitwise_or_immediates&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "Bitwise operations are only valid for integer types");
      using default_ops::eval_bitwise_or;
      eval_bitwise_or(m_backend, canonical_value(e.left().value()), canonical_value(e.right().value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::bitwise_xor&)
   {
      //
      // This operation is only valid for integer backends:
      //
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "Bitwise operations are only valid for integer types");

      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;

      BOOST_CONSTEXPR int const left_depth  = left_type::depth;
      BOOST_CONSTEXPR int const right_depth = right_type::depth;

      bool bl = contains_self(e.left());
      bool br = contains_self(e.right());

      if (bl && is_self(e.left()))
      {
         // Ignore the left node, it's *this, just add the right:
         do_bitwise_xor(e.right(), typename right_type::tag_type());
      }
      else if (br && is_self(e.right()))
      {
         do_bitwise_xor(e.left(), typename left_type::tag_type());
      }
      else if (!br && (bl || (left_depth >= right_depth)))
      {
         do_assign(e.left(), typename left_type::tag_type());
         do_bitwise_xor(e.right(), typename right_type::tag_type());
      }
      else
      {
         do_assign(e.right(), typename right_type::tag_type());
         do_bitwise_xor(e.left(), typename left_type::tag_type());
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::bitwise_xor_immediates&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "Bitwise operations are only valid for integer types");
      using default_ops::eval_bitwise_xor;
      eval_bitwise_xor(m_backend, canonical_value(e.left().value()), canonical_value(e.right().value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::terminal&)
   {
      if (!is_self(e))
      {
         m_backend = canonical_value(e.value());
      }
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::function&)
   {
      typedef typename Exp::arity tag_type;
      boost::multiprecision::detail::maybe_promote_precision(this);
      do_assign_function(e, tag_type());
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::shift_left&)
   {
      // We can only shift by an integer value, not an arbitrary expression:
      typedef typename Exp::left_type    left_type;
      typedef typename Exp::right_type   right_type;
      typedef typename right_type::arity right_arity;
      BOOST_STATIC_ASSERT_MSG(right_arity::value == 0, "The left shift operator requires an integer value for the shift operand.");
      typedef typename right_type::result_type right_value_type;
      BOOST_STATIC_ASSERT_MSG(is_integral<right_value_type>::value, "The left shift operator requires an integer value for the shift operand.");
      typedef typename left_type::tag_type tag_type;
      do_assign_left_shift(e.left(), canonical_value(e.right().value()), tag_type());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::shift_right&)
   {
      // We can only shift by an integer value, not an arbitrary expression:
      typedef typename Exp::left_type    left_type;
      typedef typename Exp::right_type   right_type;
      typedef typename right_type::arity right_arity;
      BOOST_STATIC_ASSERT_MSG(right_arity::value == 0, "The left shift operator requires an integer value for the shift operand.");
      typedef typename right_type::result_type right_value_type;
      BOOST_STATIC_ASSERT_MSG(is_integral<right_value_type>::value, "The left shift operator requires an integer value for the shift operand.");
      typedef typename left_type::tag_type tag_type;
      do_assign_right_shift(e.left(), canonical_value(e.right().value()), tag_type());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::bitwise_complement&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise ~ operation is only valid for integer types");
      using default_ops::eval_complement;
      self_type temp(e.left());
      eval_complement(m_backend, temp.backend());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign(const Exp& e, const detail::complement_immediates&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise ~ operation is only valid for integer types");
      using default_ops::eval_complement;
      eval_complement(m_backend, canonical_value(e.left().value()));
   }

   template <class Exp, class Val>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_right_shift(const Exp& e, const Val& val, const detail::terminal&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The right shift operation is only valid for integer types");
      using default_ops::eval_right_shift;
      detail::check_shift_range(val, mpl::bool_<(sizeof(Val) > sizeof(std::size_t))>(), mpl::bool_<is_signed<Val>::value>());
      eval_right_shift(m_backend, canonical_value(e.value()), static_cast<std::size_t>(val));
   }

   template <class Exp, class Val>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_left_shift(const Exp& e, const Val& val, const detail::terminal&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The left shift operation is only valid for integer types");
      using default_ops::eval_left_shift;
      detail::check_shift_range(val, mpl::bool_<(sizeof(Val) > sizeof(std::size_t))>(), mpl::bool_<is_signed<Val>::value>());
      eval_left_shift(m_backend, canonical_value(e.value()), static_cast<std::size_t>(val));
   }

   template <class Exp, class Val, class Tag>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_right_shift(const Exp& e, const Val& val, const Tag&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The right shift operation is only valid for integer types");
      using default_ops::eval_right_shift;
      self_type temp(e);
      detail::check_shift_range(val, mpl::bool_<(sizeof(Val) > sizeof(std::size_t))>(), mpl::bool_<is_signed<Val>::value>());
      eval_right_shift(m_backend, temp.backend(), static_cast<std::size_t>(val));
   }

   template <class Exp, class Val, class Tag>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_left_shift(const Exp& e, const Val& val, const Tag&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The left shift operation is only valid for integer types");
      using default_ops::eval_left_shift;
      self_type temp(e);
      detail::check_shift_range(val, mpl::bool_<(sizeof(Val) > sizeof(std::size_t))>(), mpl::bool_<is_signed<Val>::value>());
      eval_left_shift(m_backend, temp.backend(), static_cast<std::size_t>(val));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function(const Exp& e, const mpl::int_<1>&)
   {
      e.left().value()(&m_backend);
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function(const Exp& e, const mpl::int_<2>&)
   {
      typedef typename Exp::right_type      right_type;
      typedef typename right_type::tag_type tag_type;
      do_assign_function_1(e.left().value(), e.right_ref(), tag_type());
   }
   template <class F, class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_1(const F& f, const Exp& val, const detail::terminal&)
   {
      f(m_backend, function_arg_value(val));
   }
   template <class F, class Exp, class Tag>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_1(const F& f, const Exp& val, const Tag&)
   {
      typename Exp::result_type t(val);
      f(m_backend, t.backend());
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function(const Exp& e, const mpl::int_<3>&)
   {
      typedef typename Exp::middle_type      middle_type;
      typedef typename middle_type::tag_type tag_type;
      typedef typename Exp::right_type       end_type;
      typedef typename end_type::tag_type    end_tag;
      do_assign_function_2(e.left().value(), e.middle_ref(), e.right_ref(), tag_type(), end_tag());
   }
   template <class F, class Exp1, class Exp2>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_2(const F& f, const Exp1& val1, const Exp2& val2, const detail::terminal&, const detail::terminal&)
   {
      f(m_backend, function_arg_value(val1), function_arg_value(val2));
   }
   template <class F, class Exp1, class Exp2, class Tag1>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_2(const F& f, const Exp1& val1, const Exp2& val2, const Tag1&, const detail::terminal&)
   {
      typename Exp1::result_type temp1(val1);
      f(m_backend, BOOST_MP_MOVE(temp1.backend()), function_arg_value(val2));
   }
   template <class F, class Exp1, class Exp2, class Tag2>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_2(const F& f, const Exp1& val1, const Exp2& val2, const detail::terminal&, const Tag2&)
   {
      typename Exp2::result_type temp2(val2);
      f(m_backend, function_arg_value(val1), BOOST_MP_MOVE(temp2.backend()));
   }
   template <class F, class Exp1, class Exp2, class Tag1, class Tag2>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_2(const F& f, const Exp1& val1, const Exp2& val2, const Tag1&, const Tag2&)
   {
      typename Exp1::result_type temp1(val1);
      typename Exp2::result_type temp2(val2);
      f(m_backend, BOOST_MP_MOVE(temp1.backend()), BOOST_MP_MOVE(temp2.backend()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function(const Exp& e, const mpl::int_<4>&)
   {
      typedef typename Exp::left_middle_type  left_type;
      typedef typename left_type::tag_type    left_tag_type;
      typedef typename Exp::right_middle_type middle_type;
      typedef typename middle_type::tag_type  middle_tag_type;
      typedef typename Exp::right_type        right_type;
      typedef typename right_type::tag_type   right_tag_type;
      do_assign_function_3a(e.left().value(), e.left_middle_ref(), e.right_middle_ref(), e.right_ref(), left_tag_type(), middle_tag_type(), right_tag_type());
   }
   template <class F, class Exp1, class Exp2, class Exp3, class Tag2, class Tag3>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_3a(const F& f, const Exp1& val1, const Exp2& val2, const Exp3& val3, const detail::terminal&, const Tag2& t2, const Tag3& t3)
   {
      do_assign_function_3b(f, val1, val2, val3, t2, t3);
   }
   template <class F, class Exp1, class Exp2, class Exp3, class Tag1, class Tag2, class Tag3>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_3a(const F& f, const Exp1& val1, const Exp2& val2, const Exp3& val3, const Tag1&, const Tag2& t2, const Tag3& t3)
   {
      typename Exp1::result_type t(val1);
      do_assign_function_3b(f, BOOST_MP_MOVE(t), val2, val3, t2, t3);
   }
   template <class F, class Exp1, class Exp2, class Exp3, class Tag3>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_3b(const F& f, const Exp1& val1, const Exp2& val2, const Exp3& val3, const detail::terminal&, const Tag3& t3)
   {
      do_assign_function_3c(f, val1, val2, val3, t3);
   }
   template <class F, class Exp1, class Exp2, class Exp3, class Tag2, class Tag3>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_3b(const F& f, const Exp1& val1, const Exp2& val2, const Exp3& val3, const Tag2& /*t2*/, const Tag3& t3)
   {
      typename Exp2::result_type t(val2);
      do_assign_function_3c(f, val1, BOOST_MP_MOVE(t), val3, t3);
   }
   template <class F, class Exp1, class Exp2, class Exp3>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_3c(const F& f, const Exp1& val1, const Exp2& val2, const Exp3& val3, const detail::terminal&)
   {
      f(m_backend, function_arg_value(val1), function_arg_value(val2), function_arg_value(val3));
   }
   template <class F, class Exp1, class Exp2, class Exp3, class Tag3>
   BOOST_MP_CXX14_CONSTEXPR void do_assign_function_3c(const F& f, const Exp1& val1, const Exp2& val2, const Exp3& val3, const Tag3& /*t3*/)
   {
      typename Exp3::result_type t(val3);
      do_assign_function_3c(f, val1, val2, BOOST_MP_MOVE(t), detail::terminal());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_add(const Exp& e, const detail::terminal&)
   {
      using default_ops::eval_add;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_add(m_backend, canonical_value(e.value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_add(const Exp& e, const detail::negate&)
   {
      typedef typename Exp::left_type left_type;
      boost::multiprecision::detail::maybe_promote_precision(this);
      do_subtract(e.left(), typename left_type::tag_type());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_add(const Exp& e, const detail::plus&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_add(e.left(), typename left_type::tag_type());
      do_add(e.right(), typename right_type::tag_type());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_add(const Exp& e, const detail::minus&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_add(e.left(), typename left_type::tag_type());
      do_subtract(e.right(), typename right_type::tag_type());
   }

   template <class Exp, class unknown>
   BOOST_MP_CXX14_CONSTEXPR void do_add(const Exp& e, const unknown&)
   {
      self_type temp(e);
      do_add(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_add(const Exp& e, const detail::add_immediates&)
   {
      using default_ops::eval_add;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_add(m_backend, canonical_value(e.left().value()));
      eval_add(m_backend, canonical_value(e.right().value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_add(const Exp& e, const detail::subtract_immediates&)
   {
      using default_ops::eval_add;
      using default_ops::eval_subtract;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_add(m_backend, canonical_value(e.left().value()));
      eval_subtract(m_backend, canonical_value(e.right().value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_subtract(const Exp& e, const detail::terminal&)
   {
      using default_ops::eval_subtract;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_subtract(m_backend, canonical_value(e.value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_subtract(const Exp& e, const detail::negate&)
   {
      typedef typename Exp::left_type left_type;
      do_add(e.left(), typename left_type::tag_type());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_subtract(const Exp& e, const detail::plus&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_subtract(e.left(), typename left_type::tag_type());
      do_subtract(e.right(), typename right_type::tag_type());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_subtract(const Exp& e, const detail::minus&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_subtract(e.left(), typename left_type::tag_type());
      do_add(e.right(), typename right_type::tag_type());
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_subtract(const Exp& e, const detail::add_immediates&)
   {
      using default_ops::eval_subtract;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_subtract(m_backend, canonical_value(e.left().value()));
      eval_subtract(m_backend, canonical_value(e.right().value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_subtract(const Exp& e, const detail::subtract_immediates&)
   {
      using default_ops::eval_add;
      using default_ops::eval_subtract;
      eval_subtract(m_backend, canonical_value(e.left().value()));
      eval_add(m_backend, canonical_value(e.right().value()));
   }
   template <class Exp, class unknown>
   BOOST_MP_CXX14_CONSTEXPR void do_subtract(const Exp& e, const unknown&)
   {
      self_type temp(e);
      do_subtract(detail::expression<detail::terminal, self_type>(temp), detail::terminal());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_multiplies(const Exp& e, const detail::terminal&)
   {
      using default_ops::eval_multiply;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_multiply(m_backend, canonical_value(e.value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_multiplies(const Exp& e, const detail::negate&)
   {
      typedef typename Exp::left_type left_type;
      do_multiplies(e.left(), typename left_type::tag_type());
      m_backend.negate();
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_multiplies(const Exp& e, const detail::multiplies&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_multiplies(e.left(), typename left_type::tag_type());
      do_multiplies(e.right(), typename right_type::tag_type());
   }
   //
   // This rearrangement is disabled for integer types, the test on sizeof(Exp) is simply to make
   // the disable_if dependent on the template argument (the size of 1 can never occur in practice).
   //
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR typename boost::disable_if_c<boost::multiprecision::number_category<self_type>::value == boost::multiprecision::number_kind_integer || sizeof(Exp) == 1>::type
   do_multiplies(const Exp& e, const detail::divides&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_multiplies(e.left(), typename left_type::tag_type());
      do_divide(e.right(), typename right_type::tag_type());
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_multiplies(const Exp& e, const detail::multiply_immediates&)
   {
      using default_ops::eval_multiply;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_multiply(m_backend, canonical_value(e.left().value()));
      eval_multiply(m_backend, canonical_value(e.right().value()));
   }
   //
   // This rearrangement is disabled for integer types, the test on sizeof(Exp) is simply to make
   // the disable_if dependent on the template argument (the size of 1 can never occur in practice).
   //
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR typename boost::disable_if_c<boost::multiprecision::number_category<self_type>::value == boost::multiprecision::number_kind_integer || sizeof(Exp) == 1>::type
   do_multiplies(const Exp& e, const detail::divide_immediates&)
   {
      using default_ops::eval_divide;
      using default_ops::eval_multiply;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_multiply(m_backend, canonical_value(e.left().value()));
      eval_divide(m_backend, canonical_value(e.right().value()));
   }
   template <class Exp, class unknown>
   BOOST_MP_CXX14_CONSTEXPR void do_multiplies(const Exp& e, const unknown&)
   {
      using default_ops::eval_multiply;
      boost::multiprecision::detail::maybe_promote_precision(this);
      self_type temp(e);
      eval_multiply(m_backend, temp.m_backend);
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_divide(const Exp& e, const detail::terminal&)
   {
      using default_ops::eval_divide;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_divide(m_backend, canonical_value(e.value()));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_divide(const Exp& e, const detail::negate&)
   {
      typedef typename Exp::left_type left_type;
      do_divide(e.left(), typename left_type::tag_type());
      m_backend.negate();
   }
   //
   // This rearrangement is disabled for integer types, the test on sizeof(Exp) is simply to make
   // the disable_if dependent on the template argument (the size of 1 can never occur in practice).
   //
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR typename boost::disable_if_c<boost::multiprecision::number_category<self_type>::value == boost::multiprecision::number_kind_integer || sizeof(Exp) == 1>::type
   do_divide(const Exp& e, const detail::multiplies&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_divide(e.left(), typename left_type::tag_type());
      do_divide(e.right(), typename right_type::tag_type());
   }
   //
   // This rearrangement is disabled for integer types, the test on sizeof(Exp) is simply to make
   // the disable_if dependent on the template argument (the size of 1 can never occur in practice).
   //
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR typename boost::disable_if_c<boost::multiprecision::number_category<self_type>::value == boost::multiprecision::number_kind_integer || sizeof(Exp) == 1>::type
   do_divide(const Exp& e, const detail::divides&)
   {
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_divide(e.left(), typename left_type::tag_type());
      do_multiplies(e.right(), typename right_type::tag_type());
   }
   //
   // This rearrangement is disabled for integer types, the test on sizeof(Exp) is simply to make
   // the disable_if dependent on the template argument (the size of 1 can never occur in practice).
   //
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR typename boost::disable_if_c<boost::multiprecision::number_category<self_type>::value == boost::multiprecision::number_kind_integer || sizeof(Exp) == 1>::type
   do_divides(const Exp& e, const detail::multiply_immediates&)
   {
      using default_ops::eval_divide;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_divide(m_backend, canonical_value(e.left().value()));
      eval_divide(m_backend, canonical_value(e.right().value()));
   }
   //
   // This rearrangement is disabled for integer types, the test on sizeof(Exp) is simply to make
   // the disable_if dependent on the template argument (the size of 1 can never occur in practice).
   //
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR typename boost::disable_if_c<boost::multiprecision::number_category<self_type>::value == boost::multiprecision::number_kind_integer || sizeof(Exp) == 1>::type
   do_divides(const Exp& e, const detail::divide_immediates&)
   {
      using default_ops::eval_divide;
      using default_ops::eval_multiply;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_divide(m_backend, canonical_value(e.left().value()));
      mutiply(m_backend, canonical_value(e.right().value()));
   }

   template <class Exp, class unknown>
   BOOST_MP_CXX14_CONSTEXPR void do_divide(const Exp& e, const unknown&)
   {
      using default_ops::eval_multiply;
      boost::multiprecision::detail::maybe_promote_precision(this);
      self_type temp(e);
      eval_divide(m_backend, temp.m_backend);
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_modulus(const Exp& e, const detail::terminal&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The modulus operation is only valid for integer types");
      using default_ops::eval_modulus;
      boost::multiprecision::detail::maybe_promote_precision(this);
      eval_modulus(m_backend, canonical_value(e.value()));
   }

   template <class Exp, class Unknown>
   BOOST_MP_CXX14_CONSTEXPR void do_modulus(const Exp& e, const Unknown&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The modulus operation is only valid for integer types");
      using default_ops::eval_modulus;
      boost::multiprecision::detail::maybe_promote_precision(this);
      self_type temp(e);
      eval_modulus(m_backend, canonical_value(temp));
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_and(const Exp& e, const detail::terminal&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise & operation is only valid for integer types");
      using default_ops::eval_bitwise_and;
      eval_bitwise_and(m_backend, canonical_value(e.value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_and(const Exp& e, const detail::bitwise_and&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise & operation is only valid for integer types");
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_bitwise_and(e.left(), typename left_type::tag_type());
      do_bitwise_and(e.right(), typename right_type::tag_type());
   }
   template <class Exp, class unknown>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_and(const Exp& e, const unknown&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise & operation is only valid for integer types");
      using default_ops::eval_bitwise_and;
      self_type temp(e);
      eval_bitwise_and(m_backend, temp.m_backend);
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_or(const Exp& e, const detail::terminal&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise | operation is only valid for integer types");
      using default_ops::eval_bitwise_or;
      eval_bitwise_or(m_backend, canonical_value(e.value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_or(const Exp& e, const detail::bitwise_or&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise | operation is only valid for integer types");
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_bitwise_or(e.left(), typename left_type::tag_type());
      do_bitwise_or(e.right(), typename right_type::tag_type());
   }
   template <class Exp, class unknown>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_or(const Exp& e, const unknown&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise | operation is only valid for integer types");
      using default_ops::eval_bitwise_or;
      self_type temp(e);
      eval_bitwise_or(m_backend, temp.m_backend);
   }

   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_xor(const Exp& e, const detail::terminal&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise ^ operation is only valid for integer types");
      using default_ops::eval_bitwise_xor;
      eval_bitwise_xor(m_backend, canonical_value(e.value()));
   }
   template <class Exp>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_xor(const Exp& e, const detail::bitwise_xor&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise ^ operation is only valid for integer types");
      typedef typename Exp::left_type  left_type;
      typedef typename Exp::right_type right_type;
      do_bitwise_xor(e.left(), typename left_type::tag_type());
      do_bitwise_xor(e.right(), typename right_type::tag_type());
   }
   template <class Exp, class unknown>
   BOOST_MP_CXX14_CONSTEXPR void do_bitwise_xor(const Exp& e, const unknown&)
   {
      BOOST_STATIC_ASSERT_MSG(number_category<Backend>::value == number_kind_integer, "The bitwise ^ operation is only valid for integer types");
      using default_ops::eval_bitwise_xor;
      self_type temp(e);
      eval_bitwise_xor(m_backend, temp.m_backend);
   }

   // Tests if the expression contains a reference to *this:
   template <class Exp>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR bool contains_self(const Exp& e) const BOOST_NOEXCEPT
   {
      return contains_self(e, typename Exp::arity());
   }
   template <class Exp>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR bool contains_self(const Exp& e, mpl::int_<0> const&) const BOOST_NOEXCEPT
   {
      return is_realy_self(e.value());
   }
   template <class Exp>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR bool contains_self(const Exp& e, mpl::int_<1> const&) const BOOST_NOEXCEPT
   {
      typedef typename Exp::left_type child_type;
      return contains_self(e.left(), typename child_type::arity());
   }
   template <class Exp>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR bool contains_self(const Exp& e, mpl::int_<2> const&) const BOOST_NOEXCEPT
   {
      typedef typename Exp::left_type  child0_type;
      typedef typename Exp::right_type child1_type;
      return contains_self(e.left(), typename child0_type::arity()) || contains_self(e.right(), typename child1_type::arity());
   }
   template <class Exp>
   BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR bool contains_self(const Exp& e, mpl::int_<3> const&) const BOOST_NOEXCEPT
   {
      typedef typename Exp::left_type   child0_type;
      typedef typename Exp::middle_type child1_type;
      typedef typename Exp::right_type  child2_type;
      return contains_self(e.left(), typename child0_type::arity()) || contains_self(e.middle(), typename child1_type::arity()) || contains_self(e.right(), typename child2_type::arity());
   }

   // Test if the expression is a reference to *this:
   template <class Exp>
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR bool is_self(const Exp& e) const BOOST_NOEXCEPT
   {
      return is_self(e, typename Exp::arity());
   }
   template <class Exp>
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR bool is_self(const Exp& e, mpl::int_<0> const&) const BOOST_NOEXCEPT
   {
      return is_realy_self(e.value());
   }
   template <class Exp, int v>
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR bool is_self(const Exp&, mpl::int_<v> const&) const BOOST_NOEXCEPT
   {
      return false;
   }

   template <class Val>
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR bool is_realy_self(const Val&) const BOOST_NOEXCEPT { return false; }
   BOOST_MP_FORCEINLINE BOOST_CONSTEXPR bool is_realy_self(const self_type& v) const BOOST_NOEXCEPT { return &v == this; }

   static BOOST_MP_FORCEINLINE BOOST_CONSTEXPR const Backend& function_arg_value(const self_type& v) BOOST_NOEXCEPT { return v.backend(); }
   template <class Other, expression_template_option ET2>
   static BOOST_MP_FORCEINLINE BOOST_CONSTEXPR const Other& function_arg_value(const number<Other, ET2>& v) BOOST_NOEXCEPT { return v.backend(); }
   template <class V>
   static BOOST_MP_FORCEINLINE BOOST_CONSTEXPR const V& function_arg_value(const V& v) BOOST_NOEXCEPT { return v; }
   template <class A1, class A2, class A3, class A4>
   static BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR const A1& function_arg_value(const detail::expression<detail::terminal, A1, A2, A3, A4>& exp) BOOST_NOEXCEPT { return exp.value(); }
   template <class A2, class A3, class A4>
   static BOOST_MP_FORCEINLINE BOOST_CONSTEXPR const Backend& function_arg_value(const detail::expression<detail::terminal, number<Backend>, A2, A3, A4>& exp) BOOST_NOEXCEPT { return exp.value().backend(); }
   Backend                                                    m_backend;

 public:
   //
   // These shouldn't really need to be public, or even member functions, but it makes implementing
   // the non-member operators way easier if they are:
   //
   static BOOST_MP_FORCEINLINE BOOST_CONSTEXPR const Backend& canonical_value(const self_type& v) BOOST_NOEXCEPT { return v.m_backend; }
   template <class B2, expression_template_option ET>
   static BOOST_MP_FORCEINLINE BOOST_CONSTEXPR const B2& canonical_value(const number<B2, ET>& v) BOOST_NOEXCEPT { return v.backend(); }
   template <class V>
   static BOOST_MP_FORCEINLINE BOOST_CONSTEXPR typename boost::disable_if<is_same<typename detail::canonical<V, Backend>::type, V>, typename detail::canonical<V, Backend>::type>::type
   canonical_value(const V& v) BOOST_NOEXCEPT { return static_cast<typename detail::canonical<V, Backend>::type>(v); }
   template <class V>
   static BOOST_MP_FORCEINLINE BOOST_CONSTEXPR typename boost::enable_if_c<is_same<typename detail::canonical<V, Backend>::type, V>::value, const V&>::type
   canonical_value(const V& v) BOOST_NOEXCEPT { return v; }
   static BOOST_MP_FORCEINLINE typename detail::canonical<std::string, Backend>::type canonical_value(const std::string& v) BOOST_NOEXCEPT { return v.c_str(); }
};

template <class Backend, expression_template_option ExpressionTemplates>
inline std::ostream& operator<<(std::ostream& os, const number<Backend, ExpressionTemplates>& r)
{
   std::streamsize d  = os.precision();
   std::string     s  = r.str(d, os.flags());
   std::streamsize ss = os.width();
   if (ss > static_cast<std::streamsize>(s.size()))
   {
      char fill = os.fill();
      if ((os.flags() & std::ios_base::left) == std::ios_base::left)
         s.append(static_cast<std::string::size_type>(ss - s.size()), fill);
      else
         s.insert(static_cast<std::string::size_type>(0), static_cast<std::string::size_type>(ss - s.size()), fill);
   }
   return os << s;
}

namespace detail {

template <class tag, class A1, class A2, class A3, class A4>
inline std::ostream& operator<<(std::ostream& os, const expression<tag, A1, A2, A3, A4>& r)
{
   typedef typename expression<tag, A1, A2, A3, A4>::result_type value_type;
   value_type                                                    temp(r);
   return os << temp;
}
//
// What follows is the input streaming code: this is not "proper" iostream code at all
// but that's fiendishly hard to write when dealing with multiple backends all
// with different requirements... yes we could deligate this to the backend author...
// but we really want backends to be EASY to write!
// For now just pull in all the characters that could possibly form the number
// and let the backend's string parser make use of it.  This fixes most use cases
// including CSV type formats such as those used by the Random lib.
//
inline std::string read_string_while(std::istream& is, std::string const& permitted_chars)
{
   std::ios_base::iostate     state = std::ios_base::goodbit;
   const std::istream::sentry sentry_check(is);
   std::string                result;

   if (sentry_check)
   {
      int c = is.rdbuf()->sgetc();

      for (;; c = is.rdbuf()->snextc())
         if (std::istream::traits_type::eq_int_type(std::istream::traits_type::eof(), c))
         { // end of file:
            state |= std::ios_base::eofbit;
            break;
         }
         else if (permitted_chars.find_first_of(std::istream::traits_type::to_char_type(c)) == std::string::npos)
         {
            // Invalid numeric character, stop reading:
            //is.rdbuf()->sputbackc(static_cast<char>(c));
            break;
         }
         else
         {
            result.append(1, std::istream::traits_type::to_char_type(c));
         }
   }

   if (!result.size())
      state |= std::ios_base::failbit;
   is.setstate(state);
   return result;
}

} // namespace detail

template <class Backend, expression_template_option ExpressionTemplates>
inline std::istream& operator>>(std::istream& is, number<Backend, ExpressionTemplates>& r)
{
   bool        hex_format = (is.flags() & std::ios_base::hex) == std::ios_base::hex;
   bool        oct_format = (is.flags() & std::ios_base::oct) == std::ios_base::oct;
   std::string s;
   switch (boost::multiprecision::number_category<number<Backend, ExpressionTemplates> >::value)
   {
   case boost::multiprecision::number_kind_integer:
      if (oct_format)
         s = detail::read_string_while(is, "+-01234567");
      else if (hex_format)
         s = detail::read_string_while(is, "+-xXabcdefABCDEF0123456789");
      else
         s = detail::read_string_while(is, "+-0123456789");
      break;
   case boost::multiprecision::number_kind_floating_point:
      s = detail::read_string_while(is, "+-eE.0123456789infINFnanNANinfinityINFINITY");
      break;
   default:
      is >> s;
   }
   if (s.size())
   {
      if (hex_format && (number_category<Backend>::value == number_kind_integer) && ((s[0] != '0') || (s[1] != 'x')))
         s.insert(s.find_first_not_of("+-"), "0x");
      if (oct_format && (number_category<Backend>::value == number_kind_integer) && (s[0] != '0'))
         s.insert(s.find_first_not_of("+-"), "0");
      r.assign(s);
   }
   else if (!is.fail())
      is.setstate(std::istream::failbit);
   return is;
}

template <class Backend, expression_template_option ExpressionTemplates>
BOOST_MP_FORCEINLINE BOOST_MP_CXX14_CONSTEXPR void swap(number<Backend, ExpressionTemplates>& a, number<Backend, ExpressionTemplates>& b)
    BOOST_MP_NOEXCEPT_IF(noexcept(std::declval<number<Backend, ExpressionTemplates>&>() = std::declval<number<Backend, ExpressionTemplates>&>()))
{
   a.swap(b);
}
//
// Boost.Hash support, just call hash_value for the backend, which may or may not be supported:
//
template <class Backend, expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR std::size_t hash_value(const number<Backend, ExpressionTemplates>& val)
{
   return hash_value(val.backend());
}

} // namespace multiprecision

template <class T>
class rational;

template <class Backend, multiprecision::expression_template_option ExpressionTemplates>
inline std::istream& operator>>(std::istream& is, rational<multiprecision::number<Backend, ExpressionTemplates> >& r)
{
   std::string                                          s1;
   multiprecision::number<Backend, ExpressionTemplates> v1, v2;
   char                                                 c;
   bool                                                 have_hex   = false;
   bool                                                 hex_format = (is.flags() & std::ios_base::hex) == std::ios_base::hex;
   bool                                                 oct_format = (is.flags() & std::ios_base::oct) == std::ios_base::oct;

   while ((EOF != (c = static_cast<char>(is.peek()))) && (c == 'x' || c == 'X' || c == '-' || c == '+' || (c >= '0' && c <= '9') || (have_hex && (c >= 'a' && c <= 'f')) || (have_hex && (c >= 'A' && c <= 'F'))))
   {
      if (c == 'x' || c == 'X')
         have_hex = true;
      s1.append(1, c);
      is.get();
   }
   if (hex_format && ((s1[0] != '0') || (s1[1] != 'x')))
      s1.insert(static_cast<std::string::size_type>(0), "0x");
   if (oct_format && (s1[0] != '0'))
      s1.insert(static_cast<std::string::size_type>(0), "0");
   v1.assign(s1);
   s1.erase();
   if (c == '/')
   {
      is.get();
      while ((EOF != (c = static_cast<char>(is.peek()))) && (c == 'x' || c == 'X' || c == '-' || c == '+' || (c >= '0' && c <= '9') || (have_hex && (c >= 'a' && c <= 'f')) || (have_hex && (c >= 'A' && c <= 'F'))))
      {
         if (c == 'x' || c == 'X')
            have_hex = true;
         s1.append(1, c);
         is.get();
      }
      if (hex_format && ((s1[0] != '0') || (s1[1] != 'x')))
         s1.insert(static_cast<std::string::size_type>(0), "0x");
      if (oct_format && (s1[0] != '0'))
         s1.insert(static_cast<std::string::size_type>(0), "0");
      v2.assign(s1);
   }
   else
      v2 = 1;
   r.assign(v1, v2);
   return is;
}

template <class T, multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR multiprecision::number<T, ExpressionTemplates> numerator(const rational<multiprecision::number<T, ExpressionTemplates> >& a)
{
   return a.numerator();
}

template <class T, multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR multiprecision::number<T, ExpressionTemplates> denominator(const rational<multiprecision::number<T, ExpressionTemplates> >& a)
{
   return a.denominator();
}

template <class T, multiprecision::expression_template_option ExpressionTemplates>
inline BOOST_MP_CXX14_CONSTEXPR std::size_t hash_value(const rational<multiprecision::number<T, ExpressionTemplates> >& val)
{
   std::size_t result = hash_value(val.numerator());
   boost::hash_combine(result, hash_value(val.denominator()));
   return result;
}

namespace multiprecision {

template <class I>
struct component_type<boost::rational<I> >
{
   typedef I type;
};

} // namespace multiprecision

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

} // namespace boost

#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL

#include <functional>

namespace std {

template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates>
struct hash<boost::multiprecision::number<Backend, ExpressionTemplates> >
{
   BOOST_MP_CXX14_CONSTEXPR std::size_t operator()(const boost::multiprecision::number<Backend, ExpressionTemplates>& val) const { return hash_value(val); }
};
template <class Backend, boost::multiprecision::expression_template_option ExpressionTemplates>
struct hash<boost::rational<boost::multiprecision::number<Backend, ExpressionTemplates> > >
{
   BOOST_MP_CXX14_CONSTEXPR std::size_t operator()(const boost::rational<boost::multiprecision::number<Backend, ExpressionTemplates> >& val) const
   {
      std::size_t result = hash_value(val.numerator());
      boost::hash_combine(result, hash_value(val.denominator()));
      return result;
   }
};

} // namespace std

#endif

#include <boost/multiprecision/detail/ublas_interop.hpp>

#endif

/* number.hpp
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
*/