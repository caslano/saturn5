///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BN_MPFI_HPP
#define BOOST_MATH_BN_MPFI_HPP

#include <boost/multiprecision/number.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/detail/big_lanczos.hpp>
#include <boost/multiprecision/detail/digits.hpp>
#include <boost/multiprecision/detail/atomic.hpp>
#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/logged_adaptor.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <mpfi.h>
#include <cmath>
#include <algorithm>

#ifndef BOOST_MULTIPRECISION_MPFI_DEFAULT_PRECISION
#define BOOST_MULTIPRECISION_MPFI_DEFAULT_PRECISION 20
#endif

namespace boost {
namespace multiprecision {
namespace backends {

template <unsigned digits10>
struct mpfi_float_backend;

} // namespace backends

template <unsigned digits10>
struct number_category<backends::mpfi_float_backend<digits10> > : public mpl::int_<number_kind_floating_point>
{};

struct interval_error : public std::runtime_error
{
   interval_error(const std::string& s) : std::runtime_error(s) {}
};

namespace backends {

namespace detail {

inline int mpfi_sgn(mpfi_srcptr p)
{
   if (mpfi_is_zero(p))
      return 0;
   if (mpfi_is_strictly_pos(p))
      return 1;
   if (mpfi_is_strictly_neg(p))
      return -1;
   BOOST_THROW_EXCEPTION(interval_error("Sign of interval is ambiguous."));
}

template <unsigned digits10>
struct mpfi_float_imp;

template <unsigned digits10>
struct mpfi_float_imp
{
#ifdef BOOST_HAS_LONG_LONG
   typedef mpl::list<long, boost::long_long_type>           signed_types;
   typedef mpl::list<unsigned long, boost::ulong_long_type> unsigned_types;
#else
   typedef mpl::list<long>          signed_types;
   typedef mpl::list<unsigned long> unsigned_types;
#endif
   typedef mpl::list<double, long double> float_types;
   typedef long                           exponent_type;

   mpfi_float_imp()
   {
      mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfi_set_ui(m_data, 0u);
   }
   mpfi_float_imp(unsigned prec)
   {
      mpfi_init2(m_data, prec);
      mpfi_set_ui(m_data, 0u);
   }

   mpfi_float_imp(const mpfi_float_imp& o)
   {
      mpfi_init2(m_data, mpfi_get_prec(o.data()));
      if (o.m_data[0].left._mpfr_d)
         mpfi_set(m_data, o.m_data);
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfi_float_imp(mpfi_float_imp&& o) BOOST_NOEXCEPT
   {
      m_data[0]                = o.m_data[0];
      o.m_data[0].left._mpfr_d = 0;
   }
#endif
   mpfi_float_imp& operator=(const mpfi_float_imp& o)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, mpfi_get_prec(o.data()));
      if (mpfi_get_prec(o.data()) != mpfi_get_prec(data()))
      {
         mpfi_float_imp t(mpfi_get_prec(o.data()));
         t = o;
         t.swap(*this);
      }
      else
      {
         if (o.m_data[0].left._mpfr_d)
            mpfi_set(m_data, o.m_data);
      }
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfi_float_imp& operator=(mpfi_float_imp&& o) BOOST_NOEXCEPT
   {
      mpfi_swap(m_data, o.m_data);
      return *this;
   }
#endif
#ifdef BOOST_HAS_LONG_LONG
#ifdef _MPFR_H_HAVE_INTMAX_T
   mpfi_float_imp& operator=(boost::ulong_long_type i)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_uj(left_data(), i, GMP_RNDD);
      mpfr_set_uj(right_data(), i, GMP_RNDU);
      return *this;
   }
   mpfi_float_imp& operator=(boost::long_long_type i)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_sj(left_data(), i, GMP_RNDD);
      mpfr_set_sj(right_data(), i, GMP_RNDU);
      return *this;
   }
#else
   mpfi_float_imp& operator=(boost::ulong_long_type i)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      boost::ulong_long_type mask  = ((((1uLL << (std::numeric_limits<unsigned long>::digits - 1)) - 1) << 1) | 1u);
      unsigned               shift = 0;
      mpfi_t                 t;
      mpfi_init2(t, (std::max)(static_cast<unsigned long>(std::numeric_limits<boost::ulong_long_type>::digits), static_cast<unsigned long>(multiprecision::detail::digits10_2_2(digits10))));
      mpfi_set_ui(m_data, 0);
      while (i)
      {
         mpfi_set_ui(t, static_cast<unsigned long>(i & mask));
         if (shift)
            mpfi_mul_2exp(t, t, shift);
         mpfi_add(m_data, m_data, t);
         shift += std::numeric_limits<unsigned long>::digits;
         i >>= std::numeric_limits<unsigned long>::digits;
      }
      mpfi_clear(t);
      return *this;
   }
   mpfi_float_imp& operator=(boost::long_long_type i)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      bool neg = i < 0;
      *this    = boost::multiprecision::detail::unsigned_abs(i);
      if (neg)
         mpfi_neg(m_data, m_data);
      return *this;
   }
#endif
#endif
   mpfi_float_imp& operator=(unsigned long i)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfi_set_ui(m_data, i);
      return *this;
   }
   mpfi_float_imp& operator=(long i)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfi_set_si(m_data, i);
      return *this;
   }
   mpfi_float_imp& operator=(double d)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfi_set_d(m_data, d);
      return *this;
   }
   mpfi_float_imp& operator=(long double a)
   {
      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_ld(left_data(), a, GMP_RNDD);
      mpfr_set_ld(right_data(), a, GMP_RNDU);
      return *this;
   }
   mpfi_float_imp& operator=(const char* s)
   {
      using default_ops::eval_fpclassify;

      if (m_data[0].left._mpfr_d == 0)
         mpfi_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));

      if (s && (*s == '{'))
      {
         mpfr_float_backend<digits10> a, b;
         std::string                  part;
         const char*                  p = ++s;
         while (*p && (*p != ',') && (*p != '}'))
            ++p;
         part.assign(s + 1, p);
         a = part.c_str();
         s = p;
         if (*p && (*p != '}'))
         {
            ++p;
            while (*p && (*p != ',') && (*p != '}'))
               ++p;
            part.assign(s + 1, p);
         }
         else
            part.erase();
         b = part.c_str();

         if (eval_fpclassify(a) == (int)FP_NAN)
         {
            mpfi_set_fr(this->data(), a.data());
         }
         else if (eval_fpclassify(b) == (int)FP_NAN)
         {
            mpfi_set_fr(this->data(), b.data());
         }
         else
         {
            if (a.compare(b) > 0)
            {
               BOOST_THROW_EXCEPTION(std::runtime_error("Attempt to create interval with invalid range (start is greater than end)."));
            }
            mpfi_interv_fr(m_data, a.data(), b.data());
         }
      }
      else if (mpfi_set_str(m_data, s, 10) != 0)
      {
         BOOST_THROW_EXCEPTION(std::runtime_error(std::string("Unable to parse string \"") + s + std::string("\"as a valid floating point number.")));
      }
      return *this;
   }
   void swap(mpfi_float_imp& o) BOOST_NOEXCEPT
   {
      mpfi_swap(m_data, o.m_data);
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d);

      mpfr_float_backend<digits10> a, b;

      mpfi_get_left(a.data(), m_data);
      mpfi_get_right(b.data(), m_data);

      if (a.compare(b) == 0)
         return a.str(digits, f);

      return "{" + a.str(digits, f) + "," + b.str(digits, f) + "}";
   }
   ~mpfi_float_imp() BOOST_NOEXCEPT
   {
      if (m_data[0].left._mpfr_d)
         mpfi_clear(m_data);
   }
   void negate() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d);
      mpfi_neg(m_data, m_data);
   }
   int compare(const mpfi_float_imp& o) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d && o.m_data[0].left._mpfr_d);
      if (mpfr_cmp(right_data(), o.left_data()) < 0)
         return -1;
      if (mpfr_cmp(left_data(), o.right_data()) > 0)
         return 1;
      if ((mpfr_cmp(left_data(), o.left_data()) == 0) && (mpfr_cmp(right_data(), o.right_data()) == 0))
         return 0;
      BOOST_THROW_EXCEPTION(interval_error("Ambiguous comparison between two values."));
      return 0;
   }
   template <class V>
   int compare(V v) const BOOST_NOEXCEPT
   {
      mpfi_float_imp d;
      d = v;
      return compare(d);
   }
   mpfi_t& data() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d);
      return m_data;
   }
   const mpfi_t& data() const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d);
      return m_data;
   }
   mpfr_ptr left_data() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d);
      return &(m_data[0].left);
   }
   mpfr_srcptr left_data() const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d);
      return &(m_data[0].left);
   }
   mpfr_ptr right_data() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d);
      return &(m_data[0].right);
   }
   mpfr_srcptr right_data() const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].left._mpfr_d);
      return &(m_data[0].right);
   }

 protected:
   mpfi_t           m_data;
   static boost::multiprecision::detail::precision_type& get_default_precision() BOOST_NOEXCEPT
   {
      static boost::multiprecision::detail::precision_type val(BOOST_MULTIPRECISION_MPFI_DEFAULT_PRECISION);
      return val;
   }
};

} // namespace detail

template <unsigned digits10>
struct mpfi_float_backend : public detail::mpfi_float_imp<digits10>
{
   mpfi_float_backend() : detail::mpfi_float_imp<digits10>() {}
   mpfi_float_backend(const mpfi_float_backend& o) : detail::mpfi_float_imp<digits10>(o) {}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfi_float_backend(mpfi_float_backend&& o) : detail::mpfi_float_imp<digits10>(static_cast<detail::mpfi_float_imp<digits10>&&>(o))
   {}
#endif
   template <unsigned D>
   mpfi_float_backend(const mpfi_float_backend<D>& val, typename enable_if_c<D <= digits10>::type* = 0)
       : detail::mpfi_float_imp<digits10>()
   {
      mpfi_set(this->m_data, val.data());
   }
   template <unsigned D>
   explicit mpfi_float_backend(const mpfi_float_backend<D>& val, typename disable_if_c<D <= digits10>::type* = 0)
       : detail::mpfi_float_imp<digits10>()
   {
      mpfi_set(this->m_data, val.data());
   }
   mpfi_float_backend(const mpfi_t val)
       : detail::mpfi_float_imp<digits10>()
   {
      mpfi_set(this->m_data, val);
   }
   mpfi_float_backend& operator=(const mpfi_float_backend& o)
   {
      *static_cast<detail::mpfi_float_imp<digits10>*>(this) = static_cast<detail::mpfi_float_imp<digits10> const&>(o);
      return *this;
   }
   template <unsigned D>
   mpfi_float_backend(const mpfr_float_backend<D>& val, typename enable_if_c<D <= digits10>::type* = 0)
       : detail::mpfi_float_imp<digits10>()
   {
      mpfi_set_fr(this->m_data, val.data());
   }
   template <unsigned D>
   mpfi_float_backend& operator=(const mpfr_float_backend<D>& val)
   {
      mpfi_set_fr(this->m_data, val.data());
      return *this;
   }
   template <unsigned D>
   explicit mpfi_float_backend(const mpfr_float_backend<D>& val, typename disable_if_c<D <= digits10>::type* = 0)
       : detail::mpfi_float_imp<digits10>()
   {
      mpfi_set_fr(this->m_data, val.data());
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfi_float_backend& operator=(mpfi_float_backend&& o) BOOST_NOEXCEPT
   {
      *static_cast<detail::mpfi_float_imp<digits10>*>(this) = static_cast<detail::mpfi_float_imp<digits10>&&>(o);
      return *this;
   }
#endif
   template <class V>
   mpfi_float_backend& operator=(const V& v)
   {
      *static_cast<detail::mpfi_float_imp<digits10>*>(this) = v;
      return *this;
   }
   mpfi_float_backend& operator=(const mpfi_t val)
   {
      mpfi_set(this->m_data, val);
      return *this;
   }
   // We don't change our precision here, this is a fixed precision type:
   template <unsigned D>
   mpfi_float_backend& operator=(const mpfi_float_backend<D>& val)
   {
      mpfi_set(this->m_data, val.data());
      return *this;
   }
};

template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
void assign_components(mpfi_float_backend<D1>& result, const mpfr_float_backend<D2, AllocationType>& a, const mpfr_float_backend<D2, AllocationType>& b);

template <unsigned Digits10, class V>
typename enable_if_c<boost::is_constructible<number<mpfr_float_backend<Digits10, allocate_dynamic>, et_on>, V>::value || boost::is_convertible<V, const char*>::value>::type
assign_components(mpfi_float_backend<Digits10>& result, const V& a, const V& b);

template <>
struct mpfi_float_backend<0> : public detail::mpfi_float_imp<0>
{
   mpfi_float_backend() : detail::mpfi_float_imp<0>() {}
   mpfi_float_backend(const mpfi_t val)
       : detail::mpfi_float_imp<0>(mpfi_get_prec(val))
   {
      mpfi_set(this->m_data, val);
   }
   mpfi_float_backend(const mpfi_float_backend& o) : detail::mpfi_float_imp<0>(o) {}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfi_float_backend(mpfi_float_backend&& o) BOOST_NOEXCEPT : detail::mpfi_float_imp<0>(static_cast<detail::mpfi_float_imp<0>&&>(o))
   {}
#endif
   mpfi_float_backend(const mpfi_float_backend& o, unsigned digits10)
       : detail::mpfi_float_imp<0>(multiprecision::detail::digits10_2_2(digits10))
   {
      mpfi_set(this->m_data, o.data());
   }
   template <class V>
   mpfi_float_backend(const V& a, const V& b, unsigned digits10)
       : detail::mpfi_float_imp<0>(multiprecision::detail::digits10_2_2(digits10))
   {
      assign_components(*this, a, b);
   }

   template <unsigned D>
   mpfi_float_backend(const mpfi_float_backend<D>& val)
       : detail::mpfi_float_imp<0>(mpfi_get_prec(val.data()))
   {
      mpfi_set(this->m_data, val.data());
   }
   mpfi_float_backend& operator=(const mpfi_float_backend& o)
   {
      mpfi_set_prec(this->m_data, mpfi_get_prec(o.data()));
      mpfi_set(this->m_data, o.data());
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfi_float_backend& operator=(mpfi_float_backend&& o) BOOST_NOEXCEPT
   {
      *static_cast<detail::mpfi_float_imp<0>*>(this) = static_cast<detail::mpfi_float_imp<0>&&>(o);
      return *this;
   }
#endif
   template <class V>
   mpfi_float_backend& operator=(const V& v)
   {
      *static_cast<detail::mpfi_float_imp<0>*>(this) = v;
      return *this;
   }
   mpfi_float_backend& operator=(const mpfi_t val)
   {
      mpfi_set_prec(this->m_data, mpfi_get_prec(val));
      mpfi_set(this->m_data, val);
      return *this;
   }
   template <unsigned D>
   mpfi_float_backend& operator=(const mpfi_float_backend<D>& val)
   {
      mpfi_set_prec(this->m_data, mpfi_get_prec(val.data()));
      mpfi_set(this->m_data, val.data());
      return *this;
   }
   static unsigned default_precision() BOOST_NOEXCEPT
   {
      return get_default_precision();
   }
   static void default_precision(unsigned v) BOOST_NOEXCEPT
   {
      get_default_precision() = v;
   }
   unsigned precision() const BOOST_NOEXCEPT
   {
      return multiprecision::detail::digits2_2_10(mpfi_get_prec(this->m_data));
   }
   void precision(unsigned digits10) BOOST_NOEXCEPT
   {
      mpfi_float_backend t(*this, digits10);
      this->swap(t);
   }
};

template <unsigned digits10, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_eq(const mpfi_float_backend<digits10>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) == 0;
}
template <unsigned digits10, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_lt(const mpfi_float_backend<digits10>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) < 0;
}
template <unsigned digits10, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_gt(const mpfi_float_backend<digits10>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) > 0;
}

template <unsigned D1, unsigned D2>
inline void eval_add(mpfi_float_backend<D1>& result, const mpfi_float_backend<D2>& o)
{
   mpfi_add(result.data(), result.data(), o.data());
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpfi_float_backend<D1>& result, const mpfi_float_backend<D2>& o)
{
   mpfi_sub(result.data(), result.data(), o.data());
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpfi_float_backend<D1>& result, const mpfi_float_backend<D2>& o)
{
   if ((void*)&result == (void*)&o)
      mpfi_sqr(result.data(), o.data());
   else
      mpfi_mul(result.data(), result.data(), o.data());
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpfi_float_backend<D1>& result, const mpfi_float_backend<D2>& o)
{
   mpfi_div(result.data(), result.data(), o.data());
}
template <unsigned digits10>
inline void eval_add(mpfi_float_backend<digits10>& result, unsigned long i)
{
   mpfi_add_ui(result.data(), result.data(), i);
}
template <unsigned digits10>
inline void eval_subtract(mpfi_float_backend<digits10>& result, unsigned long i)
{
   mpfi_sub_ui(result.data(), result.data(), i);
}
template <unsigned digits10>
inline void eval_multiply(mpfi_float_backend<digits10>& result, unsigned long i)
{
   mpfi_mul_ui(result.data(), result.data(), i);
}
template <unsigned digits10>
inline void eval_divide(mpfi_float_backend<digits10>& result, unsigned long i)
{
   mpfi_div_ui(result.data(), result.data(), i);
}
template <unsigned digits10>
inline void eval_add(mpfi_float_backend<digits10>& result, long i)
{
   if (i > 0)
      mpfi_add_ui(result.data(), result.data(), i);
   else
      mpfi_sub_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i));
}
template <unsigned digits10>
inline void eval_subtract(mpfi_float_backend<digits10>& result, long i)
{
   if (i > 0)
      mpfi_sub_ui(result.data(), result.data(), i);
   else
      mpfi_add_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i));
}
template <unsigned digits10>
inline void eval_multiply(mpfi_float_backend<digits10>& result, long i)
{
   mpfi_mul_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i));
   if (i < 0)
      mpfi_neg(result.data(), result.data());
}
template <unsigned digits10>
inline void eval_divide(mpfi_float_backend<digits10>& result, long i)
{
   mpfi_div_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i));
   if (i < 0)
      mpfi_neg(result.data(), result.data());
}
//
// Specialised 3 arg versions of the basic operators:
//
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_add(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, const mpfi_float_backend<D3>& y)
{
   mpfi_add(a.data(), x.data(), y.data());
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, unsigned long y)
{
   mpfi_add_ui(a.data(), x.data(), y);
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, long y)
{
   if (y < 0)
      mpfi_sub_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y));
   else
      mpfi_add_ui(a.data(), x.data(), y);
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpfi_float_backend<D1>& a, unsigned long x, const mpfi_float_backend<D2>& y)
{
   mpfi_add_ui(a.data(), y.data(), x);
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpfi_float_backend<D1>& a, long x, const mpfi_float_backend<D2>& y)
{
   if (x < 0)
   {
      mpfi_ui_sub(a.data(), boost::multiprecision::detail::unsigned_abs(x), y.data());
      mpfi_neg(a.data(), a.data());
   }
   else
      mpfi_add_ui(a.data(), y.data(), x);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_subtract(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, const mpfi_float_backend<D3>& y)
{
   mpfi_sub(a.data(), x.data(), y.data());
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, unsigned long y)
{
   mpfi_sub_ui(a.data(), x.data(), y);
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, long y)
{
   if (y < 0)
      mpfi_add_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y));
   else
      mpfi_sub_ui(a.data(), x.data(), y);
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpfi_float_backend<D1>& a, unsigned long x, const mpfi_float_backend<D2>& y)
{
   mpfi_ui_sub(a.data(), x, y.data());
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpfi_float_backend<D1>& a, long x, const mpfi_float_backend<D2>& y)
{
   if (x < 0)
   {
      mpfi_add_ui(a.data(), y.data(), boost::multiprecision::detail::unsigned_abs(x));
      mpfi_neg(a.data(), a.data());
   }
   else
      mpfi_ui_sub(a.data(), x, y.data());
}

template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_multiply(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, const mpfi_float_backend<D3>& y)
{
   if ((void*)&x == (void*)&y)
      mpfi_sqr(a.data(), x.data());
   else
      mpfi_mul(a.data(), x.data(), y.data());
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, unsigned long y)
{
   mpfi_mul_ui(a.data(), x.data(), y);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, long y)
{
   if (y < 0)
   {
      mpfi_mul_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y));
      a.negate();
   }
   else
      mpfi_mul_ui(a.data(), x.data(), y);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpfi_float_backend<D1>& a, unsigned long x, const mpfi_float_backend<D2>& y)
{
   mpfi_mul_ui(a.data(), y.data(), x);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpfi_float_backend<D1>& a, long x, const mpfi_float_backend<D2>& y)
{
   if (x < 0)
   {
      mpfi_mul_ui(a.data(), y.data(), boost::multiprecision::detail::unsigned_abs(x));
      mpfi_neg(a.data(), a.data());
   }
   else
      mpfi_mul_ui(a.data(), y.data(), x);
}

template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_divide(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, const mpfi_float_backend<D3>& y)
{
   mpfi_div(a.data(), x.data(), y.data());
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, unsigned long y)
{
   mpfi_div_ui(a.data(), x.data(), y);
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpfi_float_backend<D1>& a, const mpfi_float_backend<D2>& x, long y)
{
   if (y < 0)
   {
      mpfi_div_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y));
      a.negate();
   }
   else
      mpfi_div_ui(a.data(), x.data(), y);
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpfi_float_backend<D1>& a, unsigned long x, const mpfi_float_backend<D2>& y)
{
   mpfi_ui_div(a.data(), x, y.data());
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpfi_float_backend<D1>& a, long x, const mpfi_float_backend<D2>& y)
{
   if (x < 0)
   {
      mpfi_ui_div(a.data(), boost::multiprecision::detail::unsigned_abs(x), y.data());
      mpfi_neg(a.data(), a.data());
   }
   else
      mpfi_ui_div(a.data(), x, y.data());
}

template <unsigned digits10>
inline bool eval_is_zero(const mpfi_float_backend<digits10>& val) BOOST_NOEXCEPT
{
   return 0 != mpfi_is_zero(val.data());
}
template <unsigned digits10>
inline int eval_get_sign(const mpfi_float_backend<digits10>& val)
{
   return detail::mpfi_sgn(val.data());
}

template <unsigned digits10>
inline void eval_convert_to(unsigned long* result, const mpfi_float_backend<digits10>& val)
{
   mpfr_float_backend<digits10> t;
   mpfi_mid(t.data(), val.data());
   eval_convert_to(result, t);
}
template <unsigned digits10>
inline void eval_convert_to(long* result, const mpfi_float_backend<digits10>& val)
{
   mpfr_float_backend<digits10> t;
   mpfi_mid(t.data(), val.data());
   eval_convert_to(result, t);
}
#ifdef _MPFR_H_HAVE_INTMAX_T
template <unsigned digits10>
inline void eval_convert_to(boost::ulong_long_type* result, const mpfi_float_backend<digits10>& val)
{
   mpfr_float_backend<digits10> t;
   mpfi_mid(t.data(), val.data());
   eval_convert_to(result, t);
}
template <unsigned digits10>
inline void eval_convert_to(boost::long_long_type* result, const mpfi_float_backend<digits10>& val)
{
   mpfr_float_backend<digits10> t;
   mpfi_mid(t.data(), val.data());
   eval_convert_to(result, t);
}
#endif
template <unsigned digits10>
inline void eval_convert_to(double* result, const mpfi_float_backend<digits10>& val) BOOST_NOEXCEPT
{
   *result = mpfi_get_d(val.data());
}
template <unsigned digits10>
inline void eval_convert_to(long double* result, const mpfi_float_backend<digits10>& val) BOOST_NOEXCEPT
{
   mpfr_float_backend<digits10> t;
   mpfi_mid(t.data(), val.data());
   eval_convert_to(result, t);
}

template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
inline void assign_components(mpfi_float_backend<D1>& result, const mpfr_float_backend<D2, AllocationType>& a, const mpfr_float_backend<D2, AllocationType>& b)
{
   using default_ops::eval_fpclassify;
   if (eval_fpclassify(a) == (int)FP_NAN)
   {
      mpfi_set_fr(result.data(), a.data());
   }
   else if (eval_fpclassify(b) == (int)FP_NAN)
   {
      mpfi_set_fr(result.data(), b.data());
   }
   else
   {
      if (a.compare(b) > 0)
      {
         BOOST_THROW_EXCEPTION(std::runtime_error("Attempt to create interval with invalid range (start is greater than end)."));
      }
      mpfi_interv_fr(result.data(), a.data(), b.data());
   }
}

template <unsigned Digits10, class V>
inline typename enable_if_c<boost::is_constructible<number<mpfr_float_backend<Digits10, allocate_dynamic>, et_on>, V>::value || boost::is_convertible<V, const char*>::value>::type
assign_components(mpfi_float_backend<Digits10>& result, const V& a, const V& b)
{
   number<mpfr_float_backend<Digits10, allocate_dynamic>, et_on> x(a), y(b);
   assign_components(result, x.backend(), y.backend());
}

//
// Native non-member operations:
//
template <unsigned Digits10>
inline void eval_sqrt(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& val)
{
   mpfi_sqrt(result.data(), val.data());
}

template <unsigned Digits10>
inline void eval_abs(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& val)
{
   mpfi_abs(result.data(), val.data());
}

template <unsigned Digits10>
inline void eval_fabs(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& val)
{
   mpfi_abs(result.data(), val.data());
}
template <unsigned Digits10>
inline void eval_ceil(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& val)
{
   mpfr_float_backend<Digits10> a, b;
   mpfr_set(a.data(), val.left_data(), GMP_RNDN);
   mpfr_set(b.data(), val.right_data(), GMP_RNDN);
   eval_ceil(a, a);
   eval_ceil(b, b);
   if (a.compare(b) != 0)
   {
      BOOST_THROW_EXCEPTION(interval_error("Attempt to take the ceil of a value that straddles an integer boundary."));
   }
   mpfi_set_fr(result.data(), a.data());
}
template <unsigned Digits10>
inline void eval_floor(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& val)
{
   mpfr_float_backend<Digits10> a, b;
   mpfr_set(a.data(), val.left_data(), GMP_RNDN);
   mpfr_set(b.data(), val.right_data(), GMP_RNDN);
   eval_floor(a, a);
   eval_floor(b, b);
   if (a.compare(b) != 0)
   {
      BOOST_THROW_EXCEPTION(interval_error("Attempt to take the floor of a value that straddles an integer boundary."));
   }
   mpfi_set_fr(result.data(), a.data());
}
template <unsigned Digits10>
inline void eval_ldexp(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& val, long e)
{
   if (e > 0)
      mpfi_mul_2exp(result.data(), val.data(), e);
   else if (e < 0)
      mpfi_div_2exp(result.data(), val.data(), -e);
   else
      result = val;
}
template <unsigned Digits10>
inline void eval_frexp(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& val, int* e)
{
   mpfr_float_backend<Digits10> t, rt;
   mpfi_mid(t.data(), val.data());
   eval_frexp(rt, t, e);
   eval_ldexp(result, val, -*e);
}
template <unsigned Digits10>
inline void eval_frexp(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& val, long* e)
{
   mpfr_float_backend<Digits10> t, rt;
   mpfi_mid(t.data(), val.data());
   eval_frexp(rt, t, e);
   eval_ldexp(result, val, -*e);
}

template <unsigned Digits10>
inline int eval_fpclassify(const mpfi_float_backend<Digits10>& val) BOOST_NOEXCEPT
{
   return mpfi_inf_p(val.data()) ? FP_INFINITE : mpfi_nan_p(val.data()) ? FP_NAN : mpfi_is_zero(val.data()) ? FP_ZERO : FP_NORMAL;
}

template <unsigned Digits10>
inline void eval_pow(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& b, const mpfi_float_backend<Digits10>& e)
{
   typedef typename boost::multiprecision::detail::canonical<unsigned, mpfi_float_backend<Digits10> >::type ui_type;
   using default_ops::eval_get_sign;
   int s = eval_get_sign(b);
   if (s == 0)
   {
      if (eval_get_sign(e) == 0)
      {
         result = ui_type(1);
      }
      else
      {
         result = ui_type(0);
      }
      return;
   }
   if (s < 0)
   {
      if (eval_get_sign(e) < 0)
      {
         mpfi_float_backend<Digits10> t1, t2;
         t1 = e;
         t1.negate();
         eval_pow(t2, b, t1);
         t1 = ui_type(1);
         eval_divide(result, t1, t2);
         return;
      }
      typename boost::multiprecision::detail::canonical<boost::uintmax_t, mpfi_float_backend<Digits10> >::type an;
#ifndef BOOST_NO_EXCEPTIONS
      try
      {
#endif
         using default_ops::eval_convert_to;
         eval_convert_to(&an, e);
         if (e.compare(an) == 0)
         {
            mpfi_float_backend<Digits10> pb(b);
            pb.negate();
            eval_pow(result, pb, e);
            if (an & 1u)
               result.negate();
            return;
         }
#ifndef BOOST_NO_EXCEPTIONS
      }
      catch (const std::exception&)
      {
         // conversion failed, just fall through, value is not an integer.
      }
#endif
      result = std::numeric_limits<number<mpfi_float_backend<Digits10>, et_on> >::quiet_NaN().backend();
      return;
   }
   mpfi_log(result.data(), b.data());
   mpfi_mul(result.data(), result.data(), e.data());
   mpfi_exp(result.data(), result.data());
}

template <unsigned Digits10>
inline void eval_exp(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_exp(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_exp2(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_exp2(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_log(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_log(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_log10(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_log10(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_sin(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_sin(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_cos(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_cos(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_tan(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_tan(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_asin(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_asin(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_acos(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_acos(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_atan(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_atan(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_atan2(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg1, const mpfi_float_backend<Digits10>& arg2)
{
   mpfi_atan2(result.data(), arg1.data(), arg2.data());
}

template <unsigned Digits10>
inline void eval_sinh(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_sinh(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_cosh(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_cosh(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_tanh(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_tanh(result.data(), arg.data());
}

template <unsigned Digits10>
inline void eval_log2(mpfi_float_backend<Digits10>& result, const mpfi_float_backend<Digits10>& arg)
{
   mpfi_log2(result.data(), arg.data());
}

template <unsigned Digits10>
inline std::size_t hash_value(const mpfi_float_backend<Digits10>& val)
{
   std::size_t result = 0;
   std::size_t len    = val.left_data()[0]._mpfr_prec / mp_bits_per_limb;
   if (val.left_data()[0]._mpfr_prec % mp_bits_per_limb)
      ++len;
   for (std::size_t i = 0; i < len; ++i)
      boost::hash_combine(result, val.left_data()[0]._mpfr_d[i]);
   boost::hash_combine(result, val.left_data()[0]._mpfr_exp);
   boost::hash_combine(result, val.left_data()[0]._mpfr_sign);

   len = val.right_data()[0]._mpfr_prec / mp_bits_per_limb;
   if (val.right_data()[0]._mpfr_prec % mp_bits_per_limb)
      ++len;
   for (std::size_t i = 0; i < len; ++i)
      boost::hash_combine(result, val.right_data()[0]._mpfr_d[i]);
   boost::hash_combine(result, val.right_data()[0]._mpfr_exp);
   boost::hash_combine(result, val.right_data()[0]._mpfr_sign);
   return result;
}

template <class To, unsigned D>
void generic_interconvert(To& to, const mpfi_float_backend<D>& from, const mpl::int_<number_kind_integer>& to_type, const mpl::int_<number_kind_floating_point>& from_type)
{
   using boost::multiprecision::detail::generic_interconvert;
   mpfr_float_backend<D> t;
   mpfi_mid(t.data(), from.data());
   generic_interconvert(to, t, to_type, from_type);
}

template <class To, unsigned D>
void generic_interconvert(To& to, const mpfi_float_backend<D>& from, const mpl::int_<number_kind_rational>& to_type, const mpl::int_<number_kind_floating_point>& from_type)
{
   using boost::multiprecision::detail::generic_interconvert;
   mpfr_float_backend<D> t;
   mpfi_mid(t.data(), from.data());
   generic_interconvert(to, t, to_type, from_type);
}

template <class To, unsigned D>
void generic_interconvert(To& to, const mpfi_float_backend<D>& from, const mpl::int_<number_kind_floating_point>& to_type, const mpl::int_<number_kind_floating_point>& from_type)
{
   using boost::multiprecision::detail::generic_interconvert;
   mpfr_float_backend<D> t;
   mpfi_mid(t.data(), from.data());
   generic_interconvert(to, t, to_type, from_type);
}

} // namespace backends

#ifdef BOOST_NO_SFINAE_EXPR

namespace detail {

template <unsigned D1, unsigned D2>
struct is_explicitly_convertible<backends::mpfi_float_backend<D1>, backends::mpfi_float_backend<D2> > : public mpl::true_
{};

} // namespace detail
#endif

namespace detail {
template <>
struct is_variable_precision<backends::mpfi_float_backend<0> > : public true_type
{};
} // namespace detail

template <>
struct number_category<detail::canonical<mpfi_t, backends::mpfi_float_backend<0> >::type> : public mpl::int_<number_kind_floating_point>
{};
template <unsigned Digits10>
struct is_interval_number<backends::mpfi_float_backend<Digits10> > : public mpl::true_
{};

using boost::multiprecision::backends::mpfi_float_backend;

typedef number<mpfi_float_backend<50> >   mpfi_float_50;
typedef number<mpfi_float_backend<100> >  mpfi_float_100;
typedef number<mpfi_float_backend<500> >  mpfi_float_500;
typedef number<mpfi_float_backend<1000> > mpfi_float_1000;
typedef number<mpfi_float_backend<0> >    mpfi_float;

//
// Special interval specific functions:
//
template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline number<mpfr_float_backend<Digits10>, ExpressionTemplates> lower(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& val)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfr_float_backend<Digits10>, ExpressionTemplates> > precision_guard(val);
   number<mpfr_float_backend<Digits10> >                                                                               result;
   mpfr_set(result.backend().data(), val.backend().left_data(), GMP_RNDN);
   return result;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline number<mpfr_float_backend<Digits10>, ExpressionTemplates> upper(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& val)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfr_float_backend<Digits10>, ExpressionTemplates> > precision_guard(val);
   number<mpfr_float_backend<Digits10> >                                                                               result;
   mpfr_set(result.backend().data(), val.backend().right_data(), GMP_RNDN);
   return result;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline number<mpfr_float_backend<Digits10>, ExpressionTemplates> median(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& val)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfr_float_backend<Digits10>, ExpressionTemplates> > precision_guard(val);
   number<mpfr_float_backend<Digits10> >                                                                               result;
   mpfi_mid(result.backend().data(), val.backend().data());
   return result;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline number<mpfr_float_backend<Digits10>, ExpressionTemplates> width(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& val)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfr_float_backend<Digits10>, ExpressionTemplates> > precision_guard(val);
   number<mpfr_float_backend<Digits10> >                                                                               result;
   mpfi_diam_abs(result.backend().data(), val.backend().data());
   return result;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline number<mpfi_float_backend<Digits10>, ExpressionTemplates> intersect(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& a, const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& b)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfi_float_backend<Digits10>, ExpressionTemplates> > precision_guard(a, b);
   number<mpfi_float_backend<Digits10>, ExpressionTemplates>                                                           result;
   mpfi_intersect(result.backend().data(), a.backend().data(), b.backend().data());
   return result;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline number<mpfi_float_backend<Digits10>, ExpressionTemplates> hull(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& a, const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& b)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfi_float_backend<Digits10>, ExpressionTemplates> > precision_guard(a, b);
   number<mpfi_float_backend<Digits10>, ExpressionTemplates>                                                           result;
   mpfi_union(result.backend().data(), a.backend().data(), b.backend().data());
   return result;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline bool overlap(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& a, const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& b)
{
   return (lower(a) <= lower(b) && lower(b) <= upper(a)) ||
          (lower(b) <= lower(a) && lower(a) <= upper(b));
}

template <unsigned Digits10, expression_template_option ExpressionTemplates1, expression_template_option ExpressionTemplates2>
inline bool in(const number<mpfr_float_backend<Digits10>, ExpressionTemplates1>& a, const number<mpfi_float_backend<Digits10>, ExpressionTemplates2>& b)
{
   return mpfi_is_inside_fr(a.backend().data(), b.backend().data()) != 0;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline bool zero_in(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& a)
{
   return mpfi_has_zero(a.backend().data()) != 0;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline bool subset(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& a, const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& b)
{
   return mpfi_is_inside(a.backend().data(), b.backend().data()) != 0;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline bool proper_subset(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& a, const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& b)
{
   return mpfi_is_strictly_inside(a.backend().data(), b.backend().data()) != 0;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline bool empty(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& a)
{
   return mpfi_is_empty(a.backend().data()) != 0;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline bool singleton(const number<mpfi_float_backend<Digits10>, ExpressionTemplates>& a)
{
   return mpfr_cmp(a.backend().left_data(), a.backend().right_data()) == 0;
}

template <unsigned Digits10, expression_template_option ExpressionTemplates>
struct component_type<number<mpfi_float_backend<Digits10>, ExpressionTemplates> >
{
   typedef number<mpfr_float_backend<Digits10>, ExpressionTemplates> type;
};

//
// Overloaded special functions which call native mpfr routines:
//
template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> asinh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfi_float_backend<Digits10>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result;
   mpfi_asinh(result.backend().data(), arg.backend().data());
   return result;
}
template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> acosh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfi_float_backend<Digits10>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result;
   mpfi_acosh(result.backend().data(), arg.backend().data());
   return result;
}
template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> atanh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfi_float_backend<Digits10>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result;
   mpfi_atanh(result.backend().data(), arg.backend().data());
   return result;
}
template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfi_float_backend<Digits10>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result;
   mpfi_cbrt(result.backend().data(), arg.backend().data());
   return result;
}
template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfi_float_backend<Digits10>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result;
   mpfi_expm1(result.backend().data(), arg.backend().data());
   return result;
}
template <unsigned Digits10, expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> log1p BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<mpfi_float_backend<Digits10>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result;
   mpfi_log1p(result.backend().data(), arg.backend().data());
   return result;
}

} // namespace multiprecision

namespace math {

namespace tools {

template <>
inline int digits<boost::multiprecision::mpfi_float>()
#ifdef BOOST_MATH_NOEXCEPT
    BOOST_NOEXCEPT
#endif
{
   return multiprecision::detail::digits10_2_2(boost::multiprecision::mpfi_float::default_precision());
}
template <>
inline int digits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, boost::multiprecision::et_off> >()
#ifdef BOOST_MATH_NOEXCEPT
    BOOST_NOEXCEPT
#endif
{
   return multiprecision::detail::digits10_2_2(boost::multiprecision::mpfi_float::default_precision());
}

template <>
inline boost::multiprecision::mpfi_float
max_value<boost::multiprecision::mpfi_float>()
{
   boost::multiprecision::mpfi_float result(0.5);
   mpfi_mul_2exp(result.backend().data(), result.backend().data(), mpfr_get_emax());
   //BOOST_ASSERT(mpfi_number_p(result.backend().data()));
   return result;
}

template <>
inline boost::multiprecision::mpfi_float
min_value<boost::multiprecision::mpfi_float>()
{
   boost::multiprecision::mpfi_float result(0.5);
   mpfi_div_2exp(result.backend().data(), result.backend().data(), -mpfr_get_emin());
   //BOOST_ASSERT(mpfi_number_p(result.backend().data()));
   return result;
}

template <>
inline boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, boost::multiprecision::et_off>
max_value<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, boost::multiprecision::et_off> >()
{
   boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, boost::multiprecision::et_off> result(0.5);
   mpfi_mul_2exp(result.backend().data(), result.backend().data(), mpfr_get_emax());
   //BOOST_ASSERT(mpfi_number_p(result.backend().data()));
   return result;
}

template <>
inline boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, boost::multiprecision::et_off>
min_value<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, boost::multiprecision::et_off> >()
{
   boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, boost::multiprecision::et_off> result(0.5);
   mpfi_div_2exp(result.backend().data(), result.backend().data(), -mpfr_get_emin());
   //BOOST_ASSERT(mpfi_number_p(result.backend().data()));
   return result;
}

// mpfi gets used with logged_adaptor fairly often, so specialize for that use case as well:
typedef boost::multiprecision::number<boost::multiprecision::backends::logged_adaptor<boost::multiprecision::mpfi_float::backend_type>, boost::multiprecision::et_on>  logged_type1;
typedef boost::multiprecision::number<boost::multiprecision::backends::logged_adaptor<boost::multiprecision::mpfi_float::backend_type>, boost::multiprecision::et_off> logged_type2;

template <>
inline int digits<logged_type1>()
#ifdef BOOST_MATH_NOEXCEPT
    BOOST_NOEXCEPT
#endif
{
   return multiprecision::detail::digits10_2_2(logged_type1::default_precision());
}
template <>
inline int digits<logged_type2>()
#ifdef BOOST_MATH_NOEXCEPT
    BOOST_NOEXCEPT
#endif
{
   return multiprecision::detail::digits10_2_2(logged_type1::default_precision());
}

template <>
inline logged_type1
max_value<logged_type1>()
{
   logged_type1 result(0.5);
   mpfi_mul_2exp(result.backend().value().data(), result.backend().value().data(), mpfr_get_emax());
   //BOOST_ASSERT(mpfi_number_p(result.backend().data()));
   return result;
}

template <>
inline logged_type1
min_value<logged_type1>()
{
   logged_type1 result(0.5);
   mpfi_div_2exp(result.backend().value().data(), result.backend().value().data(), -mpfr_get_emin());
   //BOOST_ASSERT(mpfi_number_p(result.backend().data()));
   return result;
}

template <>
inline logged_type2
max_value<logged_type2>()
{
   logged_type2 result(0.5);
   mpfi_mul_2exp(result.backend().value().data(), result.backend().value().data(), mpfr_get_emax());
   //BOOST_ASSERT(mpfi_number_p(result.backend().data()));
   return result;
}

template <>
inline logged_type2
min_value<logged_type2>()
{
   logged_type2 result(0.5);
   mpfi_div_2exp(result.backend().value().data(), result.backend().value().data(), -mpfr_get_emin());
   //BOOST_ASSERT(mpfi_number_p(result.backend().data()));
   return result;
}
} // namespace tools

namespace constants { namespace detail {

template <class T>
struct constant_pi;
template <class T>
struct constant_ln_two;
template <class T>
struct constant_euler;
template <class T>
struct constant_catalan;

//
// Initializer: ensure all our constants are initialized prior to the first call of main:
//
template <class T>
struct mpfi_initializer
{
   struct init
   {
      init()
      {
         boost::math::constants::pi<T>();
         boost::math::constants::ln_two<T>();
         boost::math::constants::euler<T>();
         boost::math::constants::catalan<T>();
      }
      void force_instantiate() const {}
   };
   static const init initializer;
   static void       force_instantiate()
   {
      initializer.force_instantiate();
   }
};

template <class T>
const typename mpfi_initializer<T>::init mpfi_initializer<T>::initializer;

template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_pi<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      mpfi_initializer<result_type>::force_instantiate();
      static result_type result;
      static bool        has_init = false;
      if (!has_init)
      {
         has_init = true;
         mpfi_const_pi(result.backend().data());
      }
      return result;
   }
   static inline result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfi_const_pi(result.backend().data());
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_ln_two<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      mpfi_initializer<result_type>::force_instantiate();
      static result_type result;
      static bool        has_init = false;
      if (!has_init)
      {
         has_init = true;
         mpfi_const_log2(result.backend().data());
      }
      return result;
   }
   static inline result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfi_const_log2(result.backend().data());
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_euler<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result_type;
   template <int N>
   static inline result_type const& get(const boost::integral_constant<int, N>&)
   {
      mpfi_initializer<result_type>::force_instantiate();
      static result_type result;
      static bool        has_init = false;
      if (!has_init)
      {
         has_init = true;
         mpfi_const_euler(result.backend().data());
      }
      return result;
   }
   static inline result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfi_const_euler(result.backend().data());
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_catalan<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> result_type;
   template <int N>
   static inline result_type const& get(const boost::integral_constant<int, N>&)
   {
      mpfi_initializer<result_type>::force_instantiate();
      static result_type result;
      static bool        has_init = false;
      if (!has_init)
      {
         has_init = true;
         mpfi_const_catalan(result.backend().data());
      }
      return result;
   }
   static inline result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfi_const_catalan(result.backend().data());
      return result;
   }
};

}} // namespace constants::detail

} // namespace math
} // namespace boost

namespace std {

//
// numeric_limits [partial] specializations for the types declared in this header:
//
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> number_type;

 public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = true;
   static number_type(min)()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first  = true;
         value.second = 0.5;
         mpfi_div_2exp(value.second.backend().data(), value.second.backend().data(), -mpfr_get_emin());
      }
      return value.second;
   }
   static number_type(max)()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first  = true;
         value.second = 0.5;
         mpfi_mul_2exp(value.second.backend().data(), value.second.backend().data(), mpfr_get_emax());
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR number_type lowest()
   {
      return -(max)();
   }
   BOOST_STATIC_CONSTEXPR int digits   = static_cast<int>((Digits10 * 1000L) / 301L + ((Digits10 * 1000L) % 301 ? 2 : 1));
   BOOST_STATIC_CONSTEXPR int digits10 = Digits10;
   // Is this really correct???
   BOOST_STATIC_CONSTEXPR int  max_digits10 = Digits10 + 3;
   BOOST_STATIC_CONSTEXPR bool is_signed    = true;
   BOOST_STATIC_CONSTEXPR bool is_integer   = false;
   BOOST_STATIC_CONSTEXPR bool is_exact     = false;
   BOOST_STATIC_CONSTEXPR int  radix        = 2;
   static number_type          epsilon()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first  = true;
         value.second = 1;
         mpfi_div_2exp(value.second.backend().data(), value.second.backend().data(), std::numeric_limits<number_type>::digits - 1);
      }
      return value.second;
   }
   // What value should this be????
   static number_type round_error()
   {
      // returns epsilon/2
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first  = true;
         value.second = 1;
         mpfi_div_2exp(value.second.backend().data(), value.second.backend().data(), 1);
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR long min_exponent                  = MPFR_EMIN_DEFAULT;
   BOOST_STATIC_CONSTEXPR long min_exponent10                = (MPFR_EMIN_DEFAULT / 1000) * 301L;
   BOOST_STATIC_CONSTEXPR long max_exponent                  = MPFR_EMAX_DEFAULT;
   BOOST_STATIC_CONSTEXPR long max_exponent10                = (MPFR_EMAX_DEFAULT / 1000) * 301L;
   BOOST_STATIC_CONSTEXPR bool has_infinity                  = true;
   BOOST_STATIC_CONSTEXPR bool has_quiet_NaN                 = true;
   BOOST_STATIC_CONSTEXPR bool has_signaling_NaN             = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm      = denorm_absent;
   BOOST_STATIC_CONSTEXPR bool               has_denorm_loss = false;
   static number_type                        infinity()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         boost::multiprecision::mpfr_float_backend<Digits10> t;
         mpfr_set_inf(t.data(), 1);
         value.first = true;
         mpfi_set_fr(value.second.backend().data(), t.data());
      }
      return value.second;
   }
   static number_type quiet_NaN()
   {
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         boost::multiprecision::mpfr_float_backend<Digits10> t;
         mpfr_set_nan(t.data());
         value.first = true;
         mpfi_set_fr(value.second.backend().data(), t.data());
      }
      return value.second;
   }
   BOOST_STATIC_CONSTEXPR number_type signaling_NaN()
   {
      return number_type(0);
   }
   BOOST_STATIC_CONSTEXPR number_type denorm_min() { return number_type(0); }
   BOOST_STATIC_CONSTEXPR bool        is_iec559         = false;
   BOOST_STATIC_CONSTEXPR bool        is_bounded        = true;
   BOOST_STATIC_CONSTEXPR bool        is_modulo         = false;
   BOOST_STATIC_CONSTEXPR bool        traps             = true;
   BOOST_STATIC_CONSTEXPR bool        tinyness_before   = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style = round_to_nearest;

 private:
   struct data_initializer
   {
      data_initializer()
      {
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<digits10> > >::epsilon();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<digits10> > >::round_error();
         (std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<digits10> > >::min)();
         (std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<digits10> > >::max)();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<digits10> > >::infinity();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<digits10> > >::quiet_NaN();
      }
      void do_nothing() const {}
   };
   static const data_initializer initializer;
};

template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
const typename numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::data_initializer numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::initializer;

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::digits;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::digits10;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::max_digits10;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::is_signed;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::is_integer;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::is_exact;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::radix;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::min_exponent;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::min_exponent10;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::max_exponent;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::max_exponent10;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::has_infinity;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::has_quiet_NaN;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::has_signaling_NaN;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::has_denorm;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::has_denorm_loss;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::is_iec559;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::is_bounded;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::is_modulo;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::traps;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::tinyness_before;
template <unsigned Digits10, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<Digits10>, ExpressionTemplates> >::round_style;

#endif

template <boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> number_type;

 public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = false;
   static number_type(min)() { return number_type(0); }
   static number_type(max)() { return number_type(0); }
   static number_type          lowest() { return number_type(0); }
   BOOST_STATIC_CONSTEXPR int  digits       = 0;
   BOOST_STATIC_CONSTEXPR int  digits10     = 0;
   BOOST_STATIC_CONSTEXPR int  max_digits10 = 0;
   BOOST_STATIC_CONSTEXPR bool is_signed    = false;
   BOOST_STATIC_CONSTEXPR bool is_integer   = false;
   BOOST_STATIC_CONSTEXPR bool is_exact     = false;
   BOOST_STATIC_CONSTEXPR int  radix        = 0;
   static number_type          epsilon() { return number_type(0); }
   static number_type          round_error() { return number_type(0); }
   BOOST_STATIC_CONSTEXPR int  min_exponent                  = 0;
   BOOST_STATIC_CONSTEXPR int  min_exponent10                = 0;
   BOOST_STATIC_CONSTEXPR int  max_exponent                  = 0;
   BOOST_STATIC_CONSTEXPR int  max_exponent10                = 0;
   BOOST_STATIC_CONSTEXPR bool has_infinity                  = false;
   BOOST_STATIC_CONSTEXPR bool has_quiet_NaN                 = false;
   BOOST_STATIC_CONSTEXPR bool has_signaling_NaN             = false;
   BOOST_STATIC_CONSTEXPR float_denorm_style has_denorm      = denorm_absent;
   BOOST_STATIC_CONSTEXPR bool               has_denorm_loss = false;
   static number_type                        infinity() { return number_type(0); }
   static number_type                        quiet_NaN() { return number_type(0); }
   static number_type                        signaling_NaN() { return number_type(0); }
   static number_type                        denorm_min() { return number_type(0); }
   BOOST_STATIC_CONSTEXPR bool               is_iec559       = false;
   BOOST_STATIC_CONSTEXPR bool               is_bounded      = false;
   BOOST_STATIC_CONSTEXPR bool               is_modulo       = false;
   BOOST_STATIC_CONSTEXPR bool               traps           = false;
   BOOST_STATIC_CONSTEXPR bool               tinyness_before = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style      = round_toward_zero;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::digits;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::max_digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::is_signed;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::is_integer;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::is_exact;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::radix;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::min_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::min_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::max_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::max_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::has_infinity;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::has_quiet_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::has_signaling_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::has_denorm;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::has_denorm_loss;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::is_iec559;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::is_bounded;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::is_modulo;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::traps;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::tinyness_before;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfi_float_backend<0>, ExpressionTemplates> >::round_style;

#endif
} // namespace std
#endif

/* mpfi.hpp
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
*/