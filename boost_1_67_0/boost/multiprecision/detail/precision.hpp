///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MP_PRECISION_HPP
#define BOOST_MP_PRECISION_HPP

#include <boost/multiprecision/traits/is_variable_precision.hpp>
#include <boost/multiprecision/detail/number_base.hpp>
#include <boost/multiprecision/detail/digits.hpp>

namespace boost { namespace multiprecision { namespace detail {

template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_CONSTEXPR unsigned current_precision_of_last_chance_imp(const boost::multiprecision::number<B, ET>&, const mpl::false_&)
{
   return std::numeric_limits<boost::multiprecision::number<B, ET> >::digits10;
}
template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR unsigned current_precision_of_last_chance_imp(const boost::multiprecision::number<B, ET>& val, const mpl::true_&)
{
   //
   // We have an arbitrary precision integer, take it's "precision" as the
   // location of the most-significant-bit less the location of the
   // least-significant-bit, ie the number of bits required to represent the
   // the value assuming we will have an exponent to shift things by:
   //
   return val.is_zero() ? 1 : digits2_2_10(msb(abs(val)) - lsb(abs(val)) + 1);
}

template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_MP_CXX14_CONSTEXPR unsigned current_precision_of_imp(const boost::multiprecision::number<B, ET>& n, const mpl::true_&)
{
   return n.precision();
}
template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_CONSTEXPR unsigned current_precision_of_imp(const boost::multiprecision::number<B, ET>& val, const mpl::false_&)
{
   return current_precision_of_last_chance_imp(val,
                                               mpl::bool_ <
                                                       std::numeric_limits<boost::multiprecision::number<B, ET> >::is_specialized &&
                                                   std::numeric_limits<boost::multiprecision::number<B, ET> >::is_integer && std::numeric_limits<boost::multiprecision::number<B, ET> >::is_exact && !std::numeric_limits<boost::multiprecision::number<B, ET> >::is_modulo > ());
}

template <class Terminal>
inline BOOST_CONSTEXPR unsigned current_precision_of(const Terminal&)
{
   return std::numeric_limits<Terminal>::digits10;
}

template <class Terminal, std::size_t N>
inline BOOST_CONSTEXPR unsigned current_precision_of(const Terminal (&)[N])
{ // For string literals:
   return 0;
}

template <class B, boost::multiprecision::expression_template_option ET>
inline BOOST_CONSTEXPR unsigned current_precision_of(const boost::multiprecision::number<B, ET>& n)
{
   return current_precision_of_imp(n, boost::multiprecision::detail::is_variable_precision<boost::multiprecision::number<B, ET> >());
}

template <class tag, class Arg1>
inline BOOST_CONSTEXPR unsigned current_precision_of(const expression<tag, Arg1, void, void, void>& expr)
{
   return current_precision_of(expr.left_ref());
}

template <class Arg1>
inline BOOST_CONSTEXPR unsigned current_precision_of(const expression<terminal, Arg1, void, void, void>& expr)
{
   return current_precision_of(expr.value());
}

template <class tag, class Arg1, class Arg2>
inline BOOST_CONSTEXPR unsigned current_precision_of(const expression<tag, Arg1, Arg2, void, void>& expr)
{
   return (std::max)(current_precision_of(expr.left_ref()), current_precision_of(expr.right_ref()));
}

template <class tag, class Arg1, class Arg2, class Arg3>
inline BOOST_CONSTEXPR unsigned current_precision_of(const expression<tag, Arg1, Arg2, Arg3, void>& expr)
{
   return (std::max)((std::max)(current_precision_of(expr.left_ref()), current_precision_of(expr.right_ref())), current_precision_of(expr.middle_ref()));
}

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4130)
#endif

template <class R, bool = boost::multiprecision::detail::is_variable_precision<R>::value>
struct scoped_default_precision
{
   template <class T>
   BOOST_CONSTEXPR scoped_default_precision(const T&) {}
   template <class T, class U>
   BOOST_CONSTEXPR scoped_default_precision(const T&, const U&) {}
   template <class T, class U, class V>
   BOOST_CONSTEXPR scoped_default_precision(const T&, const U&, const V&) {}

   //
   // This function is never called: in C++17 it won't be compiled either:
   //
   unsigned precision() const
   {
      BOOST_ASSERT("This function should never be called!!" == 0);
      return 0;
   }
};

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class R>
struct scoped_default_precision<R, true>
{
   template <class T>
   BOOST_MP_CXX14_CONSTEXPR scoped_default_precision(const T& a)
   {
      init(current_precision_of(a));
   }
   template <class T, class U>
   BOOST_MP_CXX14_CONSTEXPR scoped_default_precision(const T& a, const U& b)
   {
      init((std::max)(current_precision_of(a), current_precision_of(b)));
   }
   template <class T, class U, class V>
   BOOST_MP_CXX14_CONSTEXPR scoped_default_precision(const T& a, const U& b, const V& c)
   {
      init((std::max)((std::max)(current_precision_of(a), current_precision_of(b)), current_precision_of(c)));
   }
   ~scoped_default_precision()
   {
      if(m_new_prec != m_old_prec)
         R::default_precision(m_old_prec);
   }
   BOOST_MP_CXX14_CONSTEXPR unsigned precision() const
   {
      return m_new_prec;
   }

 private:
   BOOST_MP_CXX14_CONSTEXPR void init(unsigned p)
   {
      m_old_prec = R::default_precision();
      if (p && (p != m_old_prec))
      {
         R::default_precision(p);
         m_new_prec = p;
      }
      else
         m_new_prec = m_old_prec;
   }
   unsigned m_old_prec, m_new_prec;
};

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T*, const mpl::false_&) {}

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T* obj, const mpl::true_&)
{
   if (obj->precision() != T::default_precision())
   {
      obj->precision(T::default_precision());
   }
}

template <class T>
inline BOOST_MP_CXX14_CONSTEXPR void maybe_promote_precision(T* obj)
{
   maybe_promote_precision(obj, mpl::bool_<boost::multiprecision::detail::is_variable_precision<T>::value>());
}

#ifndef BOOST_NO_CXX17_IF_CONSTEXPR
#define BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(T) \
   if                                               \
   constexpr(boost::multiprecision::detail::is_variable_precision<T>::value)
#else
#define BOOST_MP_CONSTEXPR_IF_VARIABLE_PRECISION(T) if (boost::multiprecision::detail::is_variable_precision<T>::value)
#endif

}
}
} // namespace boost::multiprecision::detail

#endif // BOOST_MP_IS_BACKEND_HPP

/* precision.hpp
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
*/