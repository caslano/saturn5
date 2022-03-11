///////////////////////////////////////////////////////////////////////////////
//  Copyright 2011 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BN_MPFR_HPP
#define BOOST_MATH_BN_MPFR_HPP

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/debug_adaptor.hpp>
#include <boost/multiprecision/gmp.hpp>
#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/detail/big_lanczos.hpp>
#include <boost/multiprecision/detail/digits.hpp>
#include <boost/multiprecision/detail/atomic.hpp>
#include <mpfr.h>
#include <cmath>
#include <algorithm>

#ifndef BOOST_MULTIPRECISION_MPFR_DEFAULT_PRECISION
#define BOOST_MULTIPRECISION_MPFR_DEFAULT_PRECISION 20
#endif

namespace boost {
namespace multiprecision {

enum mpfr_allocation_type
{
   allocate_stack,
   allocate_dynamic
};

namespace backends {

template <unsigned digits10, mpfr_allocation_type AllocationType = allocate_dynamic>
struct mpfr_float_backend;

template <>
struct mpfr_float_backend<0, allocate_stack>;

} // namespace backends

template <unsigned digits10, mpfr_allocation_type AllocationType>
struct number_category<backends::mpfr_float_backend<digits10, AllocationType> > : public mpl::int_<number_kind_floating_point>
{};

namespace backends {

namespace detail {

template <bool b>
struct mpfr_cleanup
{
   struct initializer
   {
      initializer() {}
      ~initializer() { mpfr_free_cache(); }
      void force_instantiate() const {}
   };
   static const initializer init;
   static void              force_instantiate() { init.force_instantiate(); }
};

template <bool b>
typename mpfr_cleanup<b>::initializer const mpfr_cleanup<b>::init;

inline void mpfr_copy_precision(mpfr_t dest, const mpfr_t src)
{
   mpfr_prec_t p_dest = mpfr_get_prec(dest);
   mpfr_prec_t p_src  = mpfr_get_prec(src);
   if (p_dest != p_src)
      mpfr_set_prec(dest, p_src);
}
inline void mpfr_copy_precision(mpfr_t dest, const mpfr_t src1, const mpfr_t src2)
{
   mpfr_prec_t p_dest = mpfr_get_prec(dest);
   mpfr_prec_t p_src1 = mpfr_get_prec(src1);
   mpfr_prec_t p_src2 = mpfr_get_prec(src2);
   if (p_src2 > p_src1)
      p_src1 = p_src2;
   if (p_dest != p_src1)
      mpfr_set_prec(dest, p_src1);
}

template <unsigned digits10, mpfr_allocation_type AllocationType>
struct mpfr_float_imp;

template <unsigned digits10>
struct mpfr_float_imp<digits10, allocate_dynamic>
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

   mpfr_float_imp()
   {
      mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_ui(m_data, 0u, GMP_RNDN);
   }
   mpfr_float_imp(unsigned digits2)
   {
      mpfr_init2(m_data, digits2);
      mpfr_set_ui(m_data, 0u, GMP_RNDN);
   }

   mpfr_float_imp(const mpfr_float_imp& o)
   {
      mpfr_init2(m_data, mpfr_get_prec(o.m_data));
      if (o.m_data[0]._mpfr_d)
         mpfr_set(m_data, o.m_data, GMP_RNDN);
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfr_float_imp(mpfr_float_imp&& o) BOOST_NOEXCEPT
   {
      m_data[0]           = o.m_data[0];
      o.m_data[0]._mpfr_d = 0;
   }
#endif
   mpfr_float_imp& operator=(const mpfr_float_imp& o)
   {
      if ((o.m_data[0]._mpfr_d) && (this != &o))
      {
         if (m_data[0]._mpfr_d == 0)
            mpfr_init2(m_data, mpfr_get_prec(o.m_data));
         mpfr_set(m_data, o.m_data, GMP_RNDN);
      }
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfr_float_imp& operator=(mpfr_float_imp&& o) BOOST_NOEXCEPT
   {
      mpfr_swap(m_data, o.m_data);
      return *this;
   }
#endif
#ifdef BOOST_HAS_LONG_LONG
#ifdef _MPFR_H_HAVE_INTMAX_T
   mpfr_float_imp& operator=(boost::ulong_long_type i)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_uj(m_data, i, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(boost::long_long_type i)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_sj(m_data, i, GMP_RNDN);
      return *this;
   }
#else
   mpfr_float_imp& operator=(boost::ulong_long_type i)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      boost::ulong_long_type mask  = ((((1uLL << (std::numeric_limits<unsigned long>::digits - 1)) - 1) << 1) | 1uLL);
      unsigned               shift = 0;
      mpfr_t                 t;
      mpfr_init2(t, (std::max)(static_cast<unsigned long>(std::numeric_limits<boost::ulong_long_type>::digits), mpfr_get_prec(m_data)));
      mpfr_set_ui(m_data, 0, GMP_RNDN);
      while (i)
      {
         mpfr_set_ui(t, static_cast<unsigned long>(i & mask), GMP_RNDN);
         if (shift)
            mpfr_mul_2exp(t, t, shift, GMP_RNDN);
         mpfr_add(m_data, m_data, t, GMP_RNDN);
         shift += std::numeric_limits<unsigned long>::digits;
         i >>= std::numeric_limits<unsigned long>::digits;
      }
      mpfr_clear(t);
      return *this;
   }
   mpfr_float_imp& operator=(boost::long_long_type i)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      bool neg = i < 0;
      *this    = boost::multiprecision::detail::unsigned_abs(i);
      if (neg)
         mpfr_neg(m_data, m_data, GMP_RNDN);
      return *this;
   }
#endif
#endif
   mpfr_float_imp& operator=(unsigned long i)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_ui(m_data, i, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(long i)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_si(m_data, i, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(double d)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_d(m_data, d, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(long double a)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpfr_set_ld(m_data, a, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(const char* s)
   {
      if (m_data[0]._mpfr_d == 0)
         mpfr_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      if (mpfr_set_str(m_data, s, 10, GMP_RNDN) != 0)
      {
         BOOST_THROW_EXCEPTION(std::runtime_error(std::string("Unable to parse string \"") + s + std::string("\"as a valid floating point number.")));
      }
      return *this;
   }
   void swap(mpfr_float_imp& o) BOOST_NOEXCEPT
   {
      mpfr_swap(m_data, o.m_data);
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      BOOST_ASSERT(m_data[0]._mpfr_d);

      bool scientific = (f & std::ios_base::scientific) == std::ios_base::scientific;
      bool fixed      = (f & std::ios_base::fixed) == std::ios_base::fixed;

      std::streamsize org_digits(digits);

      if (scientific && digits)
         ++digits;

      std::string result;
      mp_exp_t    e;
      if (mpfr_inf_p(m_data))
      {
         if (mpfr_sgn(m_data) < 0)
            result = "-inf";
         else if (f & std::ios_base::showpos)
            result = "+inf";
         else
            result = "inf";
         return result;
      }
      if (mpfr_nan_p(m_data))
      {
         result = "nan";
         return result;
      }
      if (mpfr_zero_p(m_data))
      {
         e      = 0;
         result = "0";
      }
      else
      {
         char* ps = mpfr_get_str(0, &e, 10, static_cast<std::size_t>(digits), m_data, GMP_RNDN);
         --e; // To match with what our formatter expects.
         if (fixed && e != -1)
         {
            // Oops we actually need a different number of digits to what we asked for:
            mpfr_free_str(ps);
            digits += e + 1;
            if (digits == 0)
            {
               // We need to get *all* the digits and then possibly round up,
               // we end up with either "0" or "1" as the result.
               ps = mpfr_get_str(0, &e, 10, 0, m_data, GMP_RNDN);
               --e;
               unsigned offset = *ps == '-' ? 1 : 0;
               if (ps[offset] > '5')
               {
                  ++e;
                  ps[offset]     = '1';
                  ps[offset + 1] = 0;
               }
               else if (ps[offset] == '5')
               {
                  unsigned i        = offset + 1;
                  bool     round_up = false;
                  while (ps[i] != 0)
                  {
                     if (ps[i] != '0')
                     {
                        round_up = true;
                        break;
                     }
                     ++i;
                  }
                  if (round_up)
                  {
                     ++e;
                     ps[offset]     = '1';
                     ps[offset + 1] = 0;
                  }
                  else
                  {
                     ps[offset]     = '0';
                     ps[offset + 1] = 0;
                  }
               }
               else
               {
                  ps[offset]     = '0';
                  ps[offset + 1] = 0;
               }
            }
            else if (digits > 0)
            {
               mp_exp_t old_e = e;
               ps             = mpfr_get_str(0, &e, 10, static_cast<std::size_t>(digits), m_data, GMP_RNDN);
               --e; // To match with what our formatter expects.
               if (old_e > e)
               {
                  // in some cases, when we ask for more digits of precision, it will
                  // change the number of digits to the left of the decimal, if that
                  // happens, account for it here.
                  // example: cout << fixed << setprecision(3) << mpf_float_50("99.9809")
                  digits -= old_e - e;
                  ps = mpfr_get_str(0, &e, 10, static_cast<std::size_t>(digits), m_data, GMP_RNDN);
                  --e; // To match with what our formatter expects.
               }
            }
            else
            {
               ps = mpfr_get_str(0, &e, 10, 1, m_data, GMP_RNDN);
               --e;
               unsigned offset = *ps == '-' ? 1 : 0;
               ps[offset]      = '0';
               ps[offset + 1]  = 0;
            }
         }
         result = ps ? ps : "0";
         if (ps)
            mpfr_free_str(ps);
      }
      boost::multiprecision::detail::format_float_string(result, e, org_digits, f, 0 != mpfr_zero_p(m_data));
      return result;
   }
   ~mpfr_float_imp() BOOST_NOEXCEPT
   {
      if (m_data[0]._mpfr_d)
         mpfr_clear(m_data);
      detail::mpfr_cleanup<true>::force_instantiate();
   }
   void negate() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0]._mpfr_d);
      mpfr_neg(m_data, m_data, GMP_RNDN);
   }
   template <mpfr_allocation_type AllocationType>
   int compare(const mpfr_float_backend<digits10, AllocationType>& o) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0]._mpfr_d && o.m_data[0]._mpfr_d);
      return mpfr_cmp(m_data, o.m_data);
   }
   int compare(long i) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0]._mpfr_d);
      return mpfr_cmp_si(m_data, i);
   }
   int compare(unsigned long i) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0]._mpfr_d);
      return mpfr_cmp_ui(m_data, i);
   }
   template <class V>
   int compare(V v) const BOOST_NOEXCEPT
   {
      mpfr_float_backend<digits10, allocate_dynamic> d(0uL, mpfr_get_prec(m_data));
      d = v;
      return compare(d);
   }
   mpfr_t& data() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0]._mpfr_d);
      return m_data;
   }
   const mpfr_t& data() const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0]._mpfr_d);
      return m_data;
   }

 protected:
   mpfr_t           m_data;
   static boost::multiprecision::detail::precision_type& get_default_precision() BOOST_NOEXCEPT
   {
      static boost::multiprecision::detail::precision_type val(BOOST_MULTIPRECISION_MPFR_DEFAULT_PRECISION);
      return val;
   }
};

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable : 4127) // Conditional expression is constant
#endif

template <unsigned digits10>
struct mpfr_float_imp<digits10, allocate_stack>
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

   static const unsigned digits2    = (digits10 * 1000uL) / 301uL + ((digits10 * 1000uL) % 301 ? 2u : 1u);
   static const unsigned limb_count = mpfr_custom_get_size(digits2) / sizeof(mp_limb_t);

   ~mpfr_float_imp() BOOST_NOEXCEPT
   {
      detail::mpfr_cleanup<true>::force_instantiate();
   }
   mpfr_float_imp()
   {
      mpfr_custom_init(m_buffer, digits2);
      mpfr_custom_init_set(m_data, MPFR_NAN_KIND, 0, digits2, m_buffer);
      mpfr_set_ui(m_data, 0u, GMP_RNDN);
   }

   mpfr_float_imp(const mpfr_float_imp& o)
   {
      mpfr_custom_init(m_buffer, digits2);
      mpfr_custom_init_set(m_data, MPFR_NAN_KIND, 0, digits2, m_buffer);
      mpfr_set(m_data, o.m_data, GMP_RNDN);
   }
   mpfr_float_imp& operator=(const mpfr_float_imp& o)
   {
      mpfr_set(m_data, o.m_data, GMP_RNDN);
      return *this;
   }
#ifdef BOOST_HAS_LONG_LONG
#ifdef _MPFR_H_HAVE_INTMAX_T
   mpfr_float_imp& operator=(boost::ulong_long_type i)
   {
      mpfr_set_uj(m_data, i, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(boost::long_long_type i)
   {
      mpfr_set_sj(m_data, i, GMP_RNDN);
      return *this;
   }
#else
   mpfr_float_imp& operator=(boost::ulong_long_type i)
   {
      boost::ulong_long_type mask  = ((((1uLL << (std::numeric_limits<unsigned long>::digits - 1)) - 1) << 1) | 1uL);
      unsigned               shift = 0;
      mpfr_t                 t;
      mp_limb_t              t_limbs[limb_count];
      mpfr_custom_init(t_limbs, digits2);
      mpfr_custom_init_set(t, MPFR_NAN_KIND, 0, digits2, t_limbs);
      mpfr_set_ui(m_data, 0, GMP_RNDN);
      while (i)
      {
         mpfr_set_ui(t, static_cast<unsigned long>(i & mask), GMP_RNDN);
         if (shift)
            mpfr_mul_2exp(t, t, shift, GMP_RNDN);
         mpfr_add(m_data, m_data, t, GMP_RNDN);
         shift += std::numeric_limits<unsigned long>::digits;
         i >>= std::numeric_limits<unsigned long>::digits;
      }
      return *this;
   }
   mpfr_float_imp& operator=(boost::long_long_type i)
   {
      bool neg = i < 0;
      *this    = boost::multiprecision::detail::unsigned_abs(i);
      if (neg)
         mpfr_neg(m_data, m_data, GMP_RNDN);
      return *this;
   }
#endif
#endif
   mpfr_float_imp& operator=(unsigned long i)
   {
      mpfr_set_ui(m_data, i, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(long i)
   {
      mpfr_set_si(m_data, i, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(double d)
   {
      mpfr_set_d(m_data, d, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(long double a)
   {
      mpfr_set_ld(m_data, a, GMP_RNDN);
      return *this;
   }
   mpfr_float_imp& operator=(const char* s)
   {
      if (mpfr_set_str(m_data, s, 10, GMP_RNDN) != 0)
      {
         BOOST_THROW_EXCEPTION(std::runtime_error(std::string("Unable to parse string \"") + s + std::string("\"as a valid floating point number.")));
      }
      return *this;
   }
   void swap(mpfr_float_imp& o) BOOST_NOEXCEPT
   {
      // We have to swap by copying:
      mpfr_float_imp t(*this);
      *this = o;
      o     = t;
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      BOOST_ASSERT(m_data[0]._mpfr_d);

      bool scientific = (f & std::ios_base::scientific) == std::ios_base::scientific;
      bool fixed      = (f & std::ios_base::fixed) == std::ios_base::fixed;

      std::streamsize org_digits(digits);

      if (scientific && digits)
         ++digits;

      std::string result;
      mp_exp_t    e;
      if (mpfr_inf_p(m_data))
      {
         if (mpfr_sgn(m_data) < 0)
            result = "-inf";
         else if (f & std::ios_base::showpos)
            result = "+inf";
         else
            result = "inf";
         return result;
      }
      if (mpfr_nan_p(m_data))
      {
         result = "nan";
         return result;
      }
      if (mpfr_zero_p(m_data))
      {
         e      = 0;
         result = "0";
      }
      else
      {
         char* ps = mpfr_get_str(0, &e, 10, static_cast<std::size_t>(digits), m_data, GMP_RNDN);
         --e; // To match with what our formatter expects.
         if (fixed && e != -1)
         {
            // Oops we actually need a different number of digits to what we asked for:
            mpfr_free_str(ps);
            digits += e + 1;
            if (digits == 0)
            {
               // We need to get *all* the digits and then possibly round up,
               // we end up with either "0" or "1" as the result.
               ps = mpfr_get_str(0, &e, 10, 0, m_data, GMP_RNDN);
               --e;
               unsigned offset = *ps == '-' ? 1 : 0;
               if (ps[offset] > '5')
               {
                  ++e;
                  ps[offset]     = '1';
                  ps[offset + 1] = 0;
               }
               else if (ps[offset] == '5')
               {
                  unsigned i        = offset + 1;
                  bool     round_up = false;
                  while (ps[i] != 0)
                  {
                     if (ps[i] != '0')
                     {
                        round_up = true;
                        break;
                     }
                  }
                  if (round_up)
                  {
                     ++e;
                     ps[offset]     = '1';
                     ps[offset + 1] = 0;
                  }
                  else
                  {
                     ps[offset]     = '0';
                     ps[offset + 1] = 0;
                  }
               }
               else
               {
                  ps[offset]     = '0';
                  ps[offset + 1] = 0;
               }
            }
            else if (digits > 0)
            {
               ps = mpfr_get_str(0, &e, 10, static_cast<std::size_t>(digits), m_data, GMP_RNDN);
               --e; // To match with what our formatter expects.
            }
            else
            {
               ps = mpfr_get_str(0, &e, 10, 1, m_data, GMP_RNDN);
               --e;
               unsigned offset = *ps == '-' ? 1 : 0;
               ps[offset]      = '0';
               ps[offset + 1]  = 0;
            }
         }
         result = ps ? ps : "0";
         if (ps)
            mpfr_free_str(ps);
      }
      boost::multiprecision::detail::format_float_string(result, e, org_digits, f, 0 != mpfr_zero_p(m_data));
      return result;
   }
   void negate() BOOST_NOEXCEPT
   {
      mpfr_neg(m_data, m_data, GMP_RNDN);
   }
   template <mpfr_allocation_type AllocationType>
   int compare(const mpfr_float_backend<digits10, AllocationType>& o) const BOOST_NOEXCEPT
   {
      return mpfr_cmp(m_data, o.m_data);
   }
   int compare(long i) const BOOST_NOEXCEPT
   {
      return mpfr_cmp_si(m_data, i);
   }
   int compare(unsigned long i) const BOOST_NOEXCEPT
   {
      return mpfr_cmp_ui(m_data, i);
   }
   template <class V>
   int compare(V v) const BOOST_NOEXCEPT
   {
      mpfr_float_backend<digits10, allocate_stack> d;
      d = v;
      return compare(d);
   }
   mpfr_t& data() BOOST_NOEXCEPT
   {
      return m_data;
   }
   const mpfr_t& data() const BOOST_NOEXCEPT
   {
      return m_data;
   }

 protected:
   mpfr_t    m_data;
   mp_limb_t m_buffer[limb_count];
};

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

} // namespace detail

template <unsigned digits10, mpfr_allocation_type AllocationType>
struct mpfr_float_backend : public detail::mpfr_float_imp<digits10, AllocationType>
{
   mpfr_float_backend() : detail::mpfr_float_imp<digits10, AllocationType>() {}
   mpfr_float_backend(const mpfr_float_backend& o) : detail::mpfr_float_imp<digits10, AllocationType>(o) {}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfr_float_backend(mpfr_float_backend&& o) BOOST_NOEXCEPT : detail::mpfr_float_imp<digits10, AllocationType>(static_cast<detail::mpfr_float_imp<digits10, AllocationType>&&>(o))
   {}
#endif
   template <unsigned D, mpfr_allocation_type AT>
   mpfr_float_backend(const mpfr_float_backend<D, AT>& val, typename enable_if_c<D <= digits10>::type* = 0)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D, mpfr_allocation_type AT>
   explicit mpfr_float_backend(const mpfr_float_backend<D, AT>& val, typename disable_if_c<D <= digits10>::type* = 0)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   mpfr_float_backend(const gmp_float<D>& val, typename enable_if_c<D <= digits10>::type* = 0)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set_f(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   mpfr_float_backend(const gmp_float<D>& val, typename disable_if_c<D <= digits10>::type* = 0)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set_f(this->m_data, val.data(), GMP_RNDN);
   }
   mpfr_float_backend(const gmp_int& val)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set_z(this->m_data, val.data(), GMP_RNDN);
   }
   mpfr_float_backend(const gmp_rational& val)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set_q(this->m_data, val.data(), GMP_RNDN);
   }
   mpfr_float_backend(const mpfr_t val)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set(this->m_data, val, GMP_RNDN);
   }
   mpfr_float_backend(const mpf_t val)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set_f(this->m_data, val, GMP_RNDN);
   }
   mpfr_float_backend(const mpz_t val)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set_z(this->m_data, val, GMP_RNDN);
   }
   mpfr_float_backend(const mpq_t val)
       : detail::mpfr_float_imp<digits10, AllocationType>()
   {
      mpfr_set_q(this->m_data, val, GMP_RNDN);
   }
   // Construction with precision: we ignore the precision here.
   template <class V>
   mpfr_float_backend(const V& o, unsigned)
   {
      *this = o;
   }
   mpfr_float_backend& operator=(const mpfr_float_backend& o)
   {
      *static_cast<detail::mpfr_float_imp<digits10, AllocationType>*>(this) = static_cast<detail::mpfr_float_imp<digits10, AllocationType> const&>(o);
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfr_float_backend& operator=(mpfr_float_backend&& o) BOOST_NOEXCEPT
   {
      *static_cast<detail::mpfr_float_imp<digits10, AllocationType>*>(this) = static_cast<detail::mpfr_float_imp<digits10, AllocationType>&&>(o);
      return *this;
   }
#endif
   template <class V>
   mpfr_float_backend& operator=(const V& v)
   {
      *static_cast<detail::mpfr_float_imp<digits10, AllocationType>*>(this) = v;
      return *this;
   }
   mpfr_float_backend& operator=(const mpfr_t val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpfr_set(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const mpf_t val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpfr_set_f(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const mpz_t val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpfr_set_z(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const mpq_t val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpfr_set_q(this->m_data, val, GMP_RNDN);
      return *this;
   }
   // We don't change our precision here, this is a fixed precision type:
   template <unsigned D, mpfr_allocation_type AT>
   mpfr_float_backend& operator=(const mpfr_float_backend<D, AT>& val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpfr_set(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   template <unsigned D>
   mpfr_float_backend& operator=(const gmp_float<D>& val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpfr_set_f(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const gmp_int& val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpfr_set_z(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const gmp_rational& val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(digits10));
      mpfr_set_q(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
};

template <>
struct mpfr_float_backend<0, allocate_dynamic> : public detail::mpfr_float_imp<0, allocate_dynamic>
{
   mpfr_float_backend() : detail::mpfr_float_imp<0, allocate_dynamic>() {}
   mpfr_float_backend(const mpfr_t val)
       : detail::mpfr_float_imp<0, allocate_dynamic>((unsigned)mpfr_get_prec(val))
   {
      mpfr_set(this->m_data, val, GMP_RNDN);
   }
   mpfr_float_backend(const mpf_t val)
       : detail::mpfr_float_imp<0, allocate_dynamic>((unsigned)mpf_get_prec(val))
   {
      mpfr_set_f(this->m_data, val, GMP_RNDN);
   }
   mpfr_float_backend(const mpz_t val)
       : detail::mpfr_float_imp<0, allocate_dynamic>()
   {
      mpfr_set_z(this->m_data, val, GMP_RNDN);
   }
   mpfr_float_backend(const mpq_t val)
       : detail::mpfr_float_imp<0, allocate_dynamic>()
   {
      mpfr_set_q(this->m_data, val, GMP_RNDN);
   }
   mpfr_float_backend(const mpfr_float_backend& o) : detail::mpfr_float_imp<0, allocate_dynamic>(o) {}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfr_float_backend(mpfr_float_backend&& o) BOOST_NOEXCEPT : detail::mpfr_float_imp<0, allocate_dynamic>(static_cast<detail::mpfr_float_imp<0, allocate_dynamic>&&>(o))
   {}
#endif
   template <class V>
   mpfr_float_backend(const V& o, unsigned digits10)
       : detail::mpfr_float_imp<0, allocate_dynamic>(multiprecision::detail::digits10_2_2(digits10))
   {
      *this = o;
   }
#ifndef BOOST_NO_CXX17_HDR_STRING_VIEW
   mpfr_float_backend(const std::string_view& o, unsigned digits10)
       : detail::mpfr_float_imp<0, allocate_dynamic>(multiprecision::detail::digits10_2_2(digits10))
   {
      std::string s(o);
      *this = s.c_str();
   }
#endif
   template <unsigned D>
   mpfr_float_backend(const gmp_float<D>& val, unsigned digits10)
       : detail::mpfr_float_imp<0, allocate_dynamic>(multiprecision::detail::digits10_2_2(digits10))
   {
      mpfr_set_f(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   mpfr_float_backend(const mpfr_float_backend<D>& val, unsigned digits10)
       : detail::mpfr_float_imp<0, allocate_dynamic>(multiprecision::detail::digits10_2_2(digits10))
   {
      mpfr_set(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   mpfr_float_backend(const mpfr_float_backend<D>& val)
       : detail::mpfr_float_imp<0, allocate_dynamic>(mpfr_get_prec(val.data()))
   {
      mpfr_set(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   mpfr_float_backend(const gmp_float<D>& val)
       : detail::mpfr_float_imp<0, allocate_dynamic>(mpf_get_prec(val.data()))
   {
      mpfr_set_f(this->m_data, val.data(), GMP_RNDN);
   }
   mpfr_float_backend(const gmp_int& val)
       : detail::mpfr_float_imp<0, allocate_dynamic>()
   {
      mpfr_set_z(this->m_data, val.data(), GMP_RNDN);
   }
   mpfr_float_backend(const gmp_rational& val)
       : detail::mpfr_float_imp<0, allocate_dynamic>()
   {
      mpfr_set_q(this->m_data, val.data(), GMP_RNDN);
   }

   mpfr_float_backend& operator=(const mpfr_float_backend& o)
   {
      if (this != &o)
      {
         if (this->m_data[0]._mpfr_d == 0)
            mpfr_init2(this->m_data, mpfr_get_prec(o.data()));
         else
            detail::mpfr_copy_precision(this->m_data, o.data());
         mpfr_set(this->m_data, o.data(), GMP_RNDN);
      }
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpfr_float_backend& operator=(mpfr_float_backend&& o) BOOST_NOEXCEPT
   {
      *static_cast<detail::mpfr_float_imp<0, allocate_dynamic>*>(this) = static_cast<detail::mpfr_float_imp<0, allocate_dynamic>&&>(o);
      return *this;
   }
#endif
   template <class V>
   mpfr_float_backend& operator=(const V& v)
   {
      *static_cast<detail::mpfr_float_imp<0, allocate_dynamic>*>(this) = v;
      return *this;
   }
   mpfr_float_backend& operator=(const mpfr_t val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, mpfr_get_prec(val));
      else
         mpfr_set_prec(this->m_data, mpfr_get_prec(val));
      mpfr_set(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const mpf_t val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, (mpfr_prec_t)mpf_get_prec(val));
      else
         mpfr_set_prec(this->m_data, (unsigned)mpf_get_prec(val));
      mpfr_set_f(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const mpz_t val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(get_default_precision()));
      mpfr_set_z(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const mpq_t val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(get_default_precision()));
      mpfr_set_q(this->m_data, val, GMP_RNDN);
      return *this;
   }
   template <unsigned D>
   mpfr_float_backend& operator=(const mpfr_float_backend<D>& val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, mpfr_get_prec(val.data()));
      else
         mpfr_set_prec(this->m_data, mpfr_get_prec(val.data()));
      mpfr_set(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   template <unsigned D>
   mpfr_float_backend& operator=(const gmp_float<D>& val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, mpf_get_prec(val.data()));
      else
         mpfr_set_prec(this->m_data, mpf_get_prec(val.data()));
      mpfr_set_f(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const gmp_int& val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(get_default_precision()));
      mpfr_set_z(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpfr_float_backend& operator=(const gmp_rational& val)
   {
      if (this->m_data[0]._mpfr_d == 0)
         mpfr_init2(this->m_data, multiprecision::detail::digits10_2_2(get_default_precision()));
      mpfr_set_q(this->m_data, val.data(), GMP_RNDN);
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
      return multiprecision::detail::digits2_2_10(mpfr_get_prec(this->m_data));
   }
   void precision(unsigned digits10) BOOST_NOEXCEPT
   {
      mpfr_prec_round(this->m_data, multiprecision::detail::digits10_2_2((digits10)), GMP_RNDN);
   }
};

template <unsigned digits10, mpfr_allocation_type AllocationType, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_eq(const mpfr_float_backend<digits10, AllocationType>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) == 0;
}
template <unsigned digits10, mpfr_allocation_type AllocationType, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_lt(const mpfr_float_backend<digits10, AllocationType>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) < 0;
}
template <unsigned digits10, mpfr_allocation_type AllocationType, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_gt(const mpfr_float_backend<digits10, AllocationType>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) > 0;
}

template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_add(mpfr_float_backend<D1, A1>& result, const mpfr_float_backend<D2, A2>& o)
{
   mpfr_add(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_subtract(mpfr_float_backend<D1, A1>& result, const mpfr_float_backend<D2, A2>& o)
{
   mpfr_sub(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_multiply(mpfr_float_backend<D1, A1>& result, const mpfr_float_backend<D2, A2>& o)
{
   if ((void*)&o == (void*)&result)
      mpfr_sqr(result.data(), o.data(), GMP_RNDN);
   else
      mpfr_mul(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_divide(mpfr_float_backend<D1, A1>& result, const mpfr_float_backend<D2, A2>& o)
{
   mpfr_div(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_add(mpfr_float_backend<digits10, AllocationType>& result, unsigned long i)
{
   mpfr_add_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_subtract(mpfr_float_backend<digits10, AllocationType>& result, unsigned long i)
{
   mpfr_sub_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_multiply(mpfr_float_backend<digits10, AllocationType>& result, unsigned long i)
{
   mpfr_mul_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_divide(mpfr_float_backend<digits10, AllocationType>& result, unsigned long i)
{
   mpfr_div_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_add(mpfr_float_backend<digits10, AllocationType>& result, long i)
{
   if (i > 0)
      mpfr_add_ui(result.data(), result.data(), i, GMP_RNDN);
   else
      mpfr_sub_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i), GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_subtract(mpfr_float_backend<digits10, AllocationType>& result, long i)
{
   if (i > 0)
      mpfr_sub_ui(result.data(), result.data(), i, GMP_RNDN);
   else
      mpfr_add_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i), GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_multiply(mpfr_float_backend<digits10, AllocationType>& result, long i)
{
   mpfr_mul_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i), GMP_RNDN);
   if (i < 0)
      mpfr_neg(result.data(), result.data(), GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_divide(mpfr_float_backend<digits10, AllocationType>& result, long i)
{
   mpfr_div_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i), GMP_RNDN);
   if (i < 0)
      mpfr_neg(result.data(), result.data(), GMP_RNDN);
}
//
// Specialised 3 arg versions of the basic operators:
//
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2, unsigned D3>
inline void eval_add(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, const mpfr_float_backend<D3>& y)
{
   mpfr_add(a.data(), x.data(), y.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_add(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, unsigned long y)
{
   mpfr_add_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_add(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, long y)
{
   if (y < 0)
      mpfr_sub_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y), GMP_RNDN);
   else
      mpfr_add_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_add(mpfr_float_backend<D1, A1>& a, unsigned long x, const mpfr_float_backend<D2, A2>& y)
{
   mpfr_add_ui(a.data(), y.data(), x, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_add(mpfr_float_backend<D1, A1>& a, long x, const mpfr_float_backend<D2, A2>& y)
{
   if (x < 0)
   {
      mpfr_ui_sub(a.data(), boost::multiprecision::detail::unsigned_abs(x), y.data(), GMP_RNDN);
      mpfr_neg(a.data(), a.data(), GMP_RNDN);
   }
   else
      mpfr_add_ui(a.data(), y.data(), x, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2, unsigned D3>
inline void eval_subtract(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, const mpfr_float_backend<D3>& y)
{
   mpfr_sub(a.data(), x.data(), y.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_subtract(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, unsigned long y)
{
   mpfr_sub_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_subtract(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, long y)
{
   if (y < 0)
      mpfr_add_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y), GMP_RNDN);
   else
      mpfr_sub_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_subtract(mpfr_float_backend<D1, A1>& a, unsigned long x, const mpfr_float_backend<D2, A2>& y)
{
   mpfr_ui_sub(a.data(), x, y.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_subtract(mpfr_float_backend<D1, A1>& a, long x, const mpfr_float_backend<D2, A2>& y)
{
   if (x < 0)
   {
      mpfr_add_ui(a.data(), y.data(), boost::multiprecision::detail::unsigned_abs(x), GMP_RNDN);
      mpfr_neg(a.data(), a.data(), GMP_RNDN);
   }
   else
      mpfr_ui_sub(a.data(), x, y.data(), GMP_RNDN);
}

template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2, unsigned D3>
inline void eval_multiply(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, const mpfr_float_backend<D3>& y)
{
   if ((void*)&x == (void*)&y)
      mpfr_sqr(a.data(), x.data(), GMP_RNDN);
   else
      mpfr_mul(a.data(), x.data(), y.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_multiply(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, unsigned long y)
{
   mpfr_mul_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_multiply(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, long y)
{
   if (y < 0)
   {
      mpfr_mul_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y), GMP_RNDN);
      a.negate();
   }
   else
      mpfr_mul_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_multiply(mpfr_float_backend<D1, A1>& a, unsigned long x, const mpfr_float_backend<D2, A2>& y)
{
   mpfr_mul_ui(a.data(), y.data(), x, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_multiply(mpfr_float_backend<D1, A1>& a, long x, const mpfr_float_backend<D2, A2>& y)
{
   if (x < 0)
   {
      mpfr_mul_ui(a.data(), y.data(), boost::multiprecision::detail::unsigned_abs(x), GMP_RNDN);
      mpfr_neg(a.data(), a.data(), GMP_RNDN);
   }
   else
      mpfr_mul_ui(a.data(), y.data(), x, GMP_RNDN);
}

template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2, unsigned D3>
inline void eval_divide(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, const mpfr_float_backend<D3>& y)
{
   mpfr_div(a.data(), x.data(), y.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_divide(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, unsigned long y)
{
   mpfr_div_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_divide(mpfr_float_backend<D1, A1>& a, const mpfr_float_backend<D2, A2>& x, long y)
{
   if (y < 0)
   {
      mpfr_div_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y), GMP_RNDN);
      a.negate();
   }
   else
      mpfr_div_ui(a.data(), x.data(), y, GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_divide(mpfr_float_backend<D1, A1>& a, unsigned long x, const mpfr_float_backend<D2, A2>& y)
{
   mpfr_ui_div(a.data(), x, y.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
inline void eval_divide(mpfr_float_backend<D1, A1>& a, long x, const mpfr_float_backend<D2, A2>& y)
{
   if (x < 0)
   {
      mpfr_ui_div(a.data(), boost::multiprecision::detail::unsigned_abs(x), y.data(), GMP_RNDN);
      mpfr_neg(a.data(), a.data(), GMP_RNDN);
   }
   else
      mpfr_ui_div(a.data(), x, y.data(), GMP_RNDN);
}

template <unsigned digits10, mpfr_allocation_type AllocationType>
inline bool eval_is_zero(const mpfr_float_backend<digits10, AllocationType>& val) BOOST_NOEXCEPT
{
   return 0 != mpfr_zero_p(val.data());
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline int eval_get_sign(const mpfr_float_backend<digits10, AllocationType>& val) BOOST_NOEXCEPT
{
   return mpfr_sgn(val.data());
}

template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_convert_to(unsigned long* result, const mpfr_float_backend<digits10, AllocationType>& val)
{
   if (mpfr_nan_p(val.data()))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert NaN to integer."));
   }
   *result = mpfr_get_ui(val.data(), GMP_RNDZ);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_convert_to(long* result, const mpfr_float_backend<digits10, AllocationType>& val)
{
   if (mpfr_nan_p(val.data()))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert NaN to integer."));
   }
   *result = mpfr_get_si(val.data(), GMP_RNDZ);
}
#ifdef _MPFR_H_HAVE_INTMAX_T
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_convert_to(boost::ulong_long_type* result, const mpfr_float_backend<digits10, AllocationType>& val)
{
   if (mpfr_nan_p(val.data()))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert NaN to integer."));
   }
   *result = mpfr_get_uj(val.data(), GMP_RNDZ);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_convert_to(boost::long_long_type* result, const mpfr_float_backend<digits10, AllocationType>& val)
{
   if (mpfr_nan_p(val.data()))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert NaN to integer."));
   }
   *result = mpfr_get_sj(val.data(), GMP_RNDZ);
}
#endif
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_convert_to(float* result, const mpfr_float_backend<digits10, AllocationType>& val) BOOST_NOEXCEPT
{
   *result = mpfr_get_flt(val.data(), GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_convert_to(double* result, const mpfr_float_backend<digits10, AllocationType>& val) BOOST_NOEXCEPT
{
   *result = mpfr_get_d(val.data(), GMP_RNDN);
}
template <unsigned digits10, mpfr_allocation_type AllocationType>
inline void eval_convert_to(long double* result, const mpfr_float_backend<digits10, AllocationType>& val) BOOST_NOEXCEPT
{
   *result = mpfr_get_ld(val.data(), GMP_RNDN);
}

//
// Native non-member operations:
//
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_sqrt(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val)
{
   mpfr_sqrt(result.data(), val.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_abs(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val)
{
   mpfr_abs(result.data(), val.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_fabs(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val)
{
   mpfr_abs(result.data(), val.data(), GMP_RNDN);
}
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_ceil(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val)
{
   mpfr_ceil(result.data(), val.data());
}
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_floor(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val)
{
   mpfr_floor(result.data(), val.data());
}
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_trunc(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val)
{
   mpfr_trunc(result.data(), val.data());
}
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_ldexp(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val, long e)
{
   if (e > 0)
      mpfr_mul_2exp(result.data(), val.data(), e, GMP_RNDN);
   else if (e < 0)
      mpfr_div_2exp(result.data(), val.data(), -e, GMP_RNDN);
   else
      result = val;
}
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_frexp(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val, int* e)
{
   long v;
   mpfr_get_d_2exp(&v, val.data(), GMP_RNDN);
   *e = v;
   eval_ldexp(result, val, -v);
}
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_frexp(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& val, long* e)
{
   mpfr_get_d_2exp(e, val.data(), GMP_RNDN);
   return eval_ldexp(result, val, -*e);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline int eval_fpclassify(const mpfr_float_backend<Digits10, AllocateType>& val) BOOST_NOEXCEPT
{
   return mpfr_inf_p(val.data()) ? FP_INFINITE : mpfr_nan_p(val.data()) ? FP_NAN : mpfr_zero_p(val.data()) ? FP_ZERO : FP_NORMAL;
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_pow(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& b, const mpfr_float_backend<Digits10, AllocateType>& e)
{
   if (mpfr_zero_p(b.data()) && mpfr_integer_p(e.data()) && (mpfr_signbit(e.data()) == 0) && mpfr_fits_ulong_p(e.data(), GMP_RNDN) && (mpfr_get_ui(e.data(), GMP_RNDN) & 1))
   {
      mpfr_set(result.data(), b.data(), GMP_RNDN);
   }
   else
      mpfr_pow(result.data(), b.data(), e.data(), GMP_RNDN);
}

#ifdef BOOST_MSVC
//
// The enable_if usage below doesn't work with msvc - but only when
// certain other enable_if usages are defined first.  It's a capricious
// and rather annoying compiler bug in other words....
//
#define BOOST_MP_ENABLE_IF_WORKAROUND (Digits10 || !Digits10)&&
#else
#define BOOST_MP_ENABLE_IF_WORKAROUND
#endif

template <unsigned Digits10, mpfr_allocation_type AllocateType, class Integer>
inline typename enable_if<mpl::and_<is_signed<Integer>, mpl::bool_<BOOST_MP_ENABLE_IF_WORKAROUND(sizeof(Integer) <= sizeof(long))> > >::type
eval_pow(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& b, const Integer& e)
{
   mpfr_pow_si(result.data(), b.data(), e, GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType, class Integer>
inline typename enable_if<mpl::and_<is_unsigned<Integer>, mpl::bool_<BOOST_MP_ENABLE_IF_WORKAROUND(sizeof(Integer) <= sizeof(long))> > >::type
eval_pow(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& b, const Integer& e)
{
   mpfr_pow_ui(result.data(), b.data(), e, GMP_RNDN);
}

#undef BOOST_MP_ENABLE_IF_WORKAROUND

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_exp(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_exp(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_exp2(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_exp2(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_log(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_log(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_log10(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_log10(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_sin(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_sin(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_cos(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_cos(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_tan(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_tan(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_asin(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_asin(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_acos(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_acos(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_atan(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_atan(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_atan2(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg1, const mpfr_float_backend<Digits10, AllocateType>& arg2)
{
   mpfr_atan2(result.data(), arg1.data(), arg2.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_sinh(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_sinh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_cosh(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_cosh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_tanh(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_tanh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_log2(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   mpfr_log2(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_modf(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& arg, mpfr_float_backend<Digits10, AllocateType>* pipart)
{
   if (0 == pipart)
   {
      mpfr_float_backend<Digits10, AllocateType> ipart;
      mpfr_modf(ipart.data(), result.data(), arg.data(), GMP_RNDN);
   }
   else
   {
      mpfr_modf(pipart->data(), result.data(), arg.data(), GMP_RNDN);
   }
}
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_remainder(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& a, const mpfr_float_backend<Digits10, AllocateType>& b)
{
   mpfr_remainder(result.data(), a.data(), b.data(), GMP_RNDN);
}
template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_remquo(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& a, const mpfr_float_backend<Digits10, AllocateType>& b, int* pi)
{
   long l;
   mpfr_remquo(result.data(), &l, a.data(), b.data(), GMP_RNDN);
   if (pi)
      *pi = l;
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_fmod(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& a, const mpfr_float_backend<Digits10, AllocateType>& b)
{
   mpfr_fmod(result.data(), a.data(), b.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_multiply_add(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& a, const mpfr_float_backend<Digits10, AllocateType>& b)
{
   mpfr_fma(result.data(), a.data(), b.data(), result.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_multiply_add(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& a, const mpfr_float_backend<Digits10, AllocateType>& b, const mpfr_float_backend<Digits10, AllocateType>& c)
{
   mpfr_fma(result.data(), a.data(), b.data(), c.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_multiply_subtract(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& a, const mpfr_float_backend<Digits10, AllocateType>& b)
{
   mpfr_fms(result.data(), a.data(), b.data(), result.data(), GMP_RNDN);
   result.negate();
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline void eval_multiply_subtract(mpfr_float_backend<Digits10, AllocateType>& result, const mpfr_float_backend<Digits10, AllocateType>& a, const mpfr_float_backend<Digits10, AllocateType>& b, const mpfr_float_backend<Digits10, AllocateType>& c)
{
   mpfr_fms(result.data(), a.data(), b.data(), c.data(), GMP_RNDN);
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline int eval_signbit BOOST_PREVENT_MACRO_SUBSTITUTION(const mpfr_float_backend<Digits10, AllocateType>& arg)
{
   return (arg.data()[0]._mpfr_sign < 0) ? 1 : 0;
}

template <unsigned Digits10, mpfr_allocation_type AllocateType>
inline std::size_t hash_value(const mpfr_float_backend<Digits10, AllocateType>& val)
{
   std::size_t result = 0;
   std::size_t len    = val.data()[0]._mpfr_prec / mp_bits_per_limb;
   if (val.data()[0]._mpfr_prec % mp_bits_per_limb)
      ++len;
   for (std::size_t i = 0; i < len; ++i)
      boost::hash_combine(result, val.data()[0]._mpfr_d[i]);
   boost::hash_combine(result, val.data()[0]._mpfr_exp);
   boost::hash_combine(result, val.data()[0]._mpfr_sign);
   return result;
}

} // namespace backends

#ifdef BOOST_NO_SFINAE_EXPR

namespace detail {

template <unsigned D1, unsigned D2, mpfr_allocation_type A1, mpfr_allocation_type A2>
struct is_explicitly_convertible<backends::mpfr_float_backend<D1, A1>, backends::mpfr_float_backend<D2, A2> > : public mpl::true_
{};

} // namespace detail

#endif

namespace detail {
template <>
struct is_variable_precision<backends::mpfr_float_backend<0> > : public true_type
{};
} // namespace detail

template <>
struct number_category<detail::canonical<mpfr_t, backends::mpfr_float_backend<0> >::type> : public mpl::int_<number_kind_floating_point>
{};

using boost::multiprecision::backends::mpfr_float_backend;

typedef number<mpfr_float_backend<50> >   mpfr_float_50;
typedef number<mpfr_float_backend<100> >  mpfr_float_100;
typedef number<mpfr_float_backend<500> >  mpfr_float_500;
typedef number<mpfr_float_backend<1000> > mpfr_float_1000;
typedef number<mpfr_float_backend<0> >    mpfr_float;

typedef number<mpfr_float_backend<50, allocate_stack> >  static_mpfr_float_50;
typedef number<mpfr_float_backend<100, allocate_stack> > static_mpfr_float_100;

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> copysign BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& a, const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& b)
{
   return (boost::multiprecision::signbit)(a) != (boost::multiprecision::signbit)(b) ? boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>(-a) : a;
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> copysign BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates>& a, const boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates>& b)
{
   return (boost::multiprecision::signbit)(a) != (boost::multiprecision::signbit)(b) ? boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates>(-a) : a;
}

} // namespace multiprecision

namespace math {

using boost::multiprecision::copysign;
using boost::multiprecision::signbit;

namespace tools {

template <>
inline int digits<boost::multiprecision::mpfr_float>()
#ifdef BOOST_MATH_NOEXCEPT
    BOOST_NOEXCEPT
#endif
{
   return multiprecision::detail::digits10_2_2(boost::multiprecision::mpfr_float::default_precision());
}
template <>
inline int digits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, boost::multiprecision::et_off> >()
#ifdef BOOST_MATH_NOEXCEPT
    BOOST_NOEXCEPT
#endif
{
   return multiprecision::detail::digits10_2_2(boost::multiprecision::mpfr_float::default_precision());
}

template <>
inline boost::multiprecision::mpfr_float
max_value<boost::multiprecision::mpfr_float>()
{
   boost::multiprecision::mpfr_float result(0.5);
   mpfr_mul_2exp(result.backend().data(), result.backend().data(), mpfr_get_emax(), GMP_RNDN);
   BOOST_ASSERT(mpfr_number_p(result.backend().data()));
   return result;
}

template <>
inline boost::multiprecision::mpfr_float
min_value<boost::multiprecision::mpfr_float>()
{
   boost::multiprecision::mpfr_float result(0.5);
   mpfr_div_2exp(result.backend().data(), result.backend().data(), -mpfr_get_emin(), GMP_RNDN);
   BOOST_ASSERT(mpfr_number_p(result.backend().data()));
   return result;
}

template <>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, boost::multiprecision::et_off>
max_value<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, boost::multiprecision::et_off> >()
{
   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, boost::multiprecision::et_off> result(0.5);
   mpfr_mul_2exp(result.backend().data(), result.backend().data(), mpfr_get_emax(), GMP_RNDN);
   BOOST_ASSERT(mpfr_number_p(result.backend().data()));
   return result;
}

template <>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, boost::multiprecision::et_off>
min_value<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, boost::multiprecision::et_off> >()
{
   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, boost::multiprecision::et_off> result(0.5);
   mpfr_div_2exp(result.backend().data(), result.backend().data(), -mpfr_get_emin(), GMP_RNDN);
   BOOST_ASSERT(mpfr_number_p(result.backend().data()));
   return result;
}

template <>
inline int digits<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float::backend_type> > >()
#ifdef BOOST_MATH_NOEXCEPT
    BOOST_NOEXCEPT
#endif
{
   return multiprecision::detail::digits10_2_2(boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float::backend_type> >::default_precision());
}
template <>
inline int digits<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<0> >, boost::multiprecision::et_off> >()
#ifdef BOOST_MATH_NOEXCEPT
    BOOST_NOEXCEPT
#endif
{
   return multiprecision::detail::digits10_2_2(boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float::backend_type> >::default_precision());
}

template <>
inline boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float::backend_type> >
max_value<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float::backend_type> > >()
{
   return max_value<boost::multiprecision::mpfr_float>().backend();
}

template <>
inline boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float::backend_type> >
min_value<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float::backend_type> > >()
{
   return min_value<boost::multiprecision::mpfr_float>().backend();
}

template <>
inline boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<0> >, boost::multiprecision::et_off>
max_value<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<0> >, boost::multiprecision::et_off> >()
{
   return max_value<boost::multiprecision::mpfr_float>().backend();
}

template <>
inline boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<0> >, boost::multiprecision::et_off>
min_value<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<0> >, boost::multiprecision::et_off> >()
{
   return min_value<boost::multiprecision::mpfr_float>().backend();
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

namespace detail {

template <class T, int N>
struct mpfr_constant_initializer
{
   static void force_instantiate()
   {
      init.force_instantiate();
   }

 private:
   struct initializer
   {
      initializer()
      {
         T::get(boost::integral_constant<int, N>());
      }
      void force_instantiate() const {}
   };
   static const initializer init;
};

template <class T, int N>
typename mpfr_constant_initializer<T, N>::initializer const mpfr_constant_initializer<T, N>::init;

} // namespace detail

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_pi<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      detail::mpfr_constant_initializer<constant_pi<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >, N>::force_instantiate();
      static result_type result;
      static bool        has_init = false;
      if (!has_init)
      {
         mpfr_const_pi(result.backend().data(), GMP_RNDN);
         has_init = true;
      }
      return result;
   }
   static inline const result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfr_const_pi(result.backend().data(), GMP_RNDN);
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_ln_two<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      detail::mpfr_constant_initializer<constant_ln_two<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >, N>::force_instantiate();
      static result_type result;
      static bool        init = false;
      if (!init)
      {
         mpfr_const_log2(result.backend().data(), GMP_RNDN);
         init = true;
      }
      return result;
   }
   static inline const result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfr_const_log2(result.backend().data(), GMP_RNDN);
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_euler<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      detail::mpfr_constant_initializer<constant_euler<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >, N>::force_instantiate();
      static result_type result;
      static bool        init = false;
      if (!init)
      {
         mpfr_const_euler(result.backend().data(), GMP_RNDN);
         init = true;
      }
      return result;
   }
   static inline const result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfr_const_euler(result.backend().data(), GMP_RNDN);
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_catalan<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      detail::mpfr_constant_initializer<constant_catalan<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >, N>::force_instantiate();
      static result_type result;
      static bool        init = false;
      if (!init)
      {
         mpfr_const_catalan(result.backend().data(), GMP_RNDN);
         init = true;
      }
      return result;
   }
   static inline const result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfr_const_catalan(result.backend().data(), GMP_RNDN);
      return result;
   }
};

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_pi<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      detail::mpfr_constant_initializer<constant_pi<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> >, N>::force_instantiate();
      static result_type result;
      static bool        has_init = false;
      if (!has_init)
      {
         mpfr_const_pi(result.backend().value().data(), GMP_RNDN);
         has_init = true;
      }
      return result;
   }
   static inline const result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfr_const_pi(result.backend().value().data(), GMP_RNDN);
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_ln_two<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      detail::mpfr_constant_initializer<constant_ln_two<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> >, N>::force_instantiate();
      static result_type result;
      static bool        init = false;
      if (!init)
      {
         mpfr_const_log2(result.backend().value().data(), GMP_RNDN);
         init = true;
      }
      return result;
   }
   static inline const result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfr_const_log2(result.backend().value().data(), GMP_RNDN);
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_euler<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      detail::mpfr_constant_initializer<constant_euler<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> >, N>::force_instantiate();
      static result_type result;
      static bool        init = false;
      if (!init)
      {
         mpfr_const_euler(result.backend().value().data(), GMP_RNDN);
         init = true;
      }
      return result;
   }
   static inline const result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfr_const_euler(result.backend().value().data(), GMP_RNDN);
      return result;
   }
};
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
struct constant_catalan<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> result_type;
   template <int N>
   static inline const result_type& get(const boost::integral_constant<int, N>&)
   {
      detail::mpfr_constant_initializer<constant_catalan<boost::multiprecision::number<boost::multiprecision::debug_adaptor<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType> >, ExpressionTemplates> >, N>::force_instantiate();
      static result_type result;
      static bool        init = false;
      if (!init)
      {
         mpfr_const_catalan(result.backend().value().data(), GMP_RNDN);
         init = true;
      }
      return result;
   }
   static inline const result_type get(const boost::integral_constant<int, 0>&)
   {
      result_type result;
      mpfr_const_catalan(result.backend().value().data(), GMP_RNDN);
      return result;
   }
};

}} // namespace constants::detail

} // namespace math

namespace multiprecision {
//
// Overloaded special functions which call native mpfr routines:
//
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> asinh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_asinh(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> acosh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_acosh(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> atanh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_atanh(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_cbrt(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> erf BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_erf(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> erfc BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_erfc(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_expm1(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_lngamma(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_gamma(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> log1p BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   boost::multiprecision::detail::scoped_default_precision<number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_log1p(result.backend().data(), arg.backend().data(), GMP_RNDN);
   return result;
}

} // namespace multiprecision

namespace math {
//
// Overloaded special functions which call native mpfr routines:
//
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> asinh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy&)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_asinh(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("asinh<%1%>(%1%)", 0, Policy());
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("asinh<%1%>(%1%)", "Unknown error, result is a NaN", result, Policy());
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> asinh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return asinh(arg, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> acosh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy&)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_acosh(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("acosh<%1%>(%1%)", 0, Policy());
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("acosh<%1%>(%1%)", "Unknown error, result is a NaN", result, Policy());
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> acosh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return acosh(arg, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> atanh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy& )
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_atanh(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("atanh<%1%>(%1%)", 0, Policy());
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("atanh<%1%>(%1%)", "Unknown error, result is a NaN", result, Policy());
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> atanh BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return atanh(arg, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy&)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_cbrt(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("cbrt<%1%>(%1%)", 0, Policy());
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("cbrt<%1%>(%1%)", "Unknown error, result is a NaN", result, Policy());
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> cbrt BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return cbrt(arg, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> erf BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy& pol)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_erf(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("erf<%1%>(%1%)", 0, pol);
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("erf<%1%>(%1%)", "Unknown error, result is a NaN", result, pol);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> erf BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return erf(arg, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> erfc BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy& pol)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_erfc(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("erfc<%1%>(%1%)", 0, pol);
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("erfc<%1%>(%1%)", "Unknown error, result is a NaN", result, pol);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> erfc BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return erfc(arg, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> expm1 BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy& pol)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_expm1(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("expm1<%1%>(%1%)", 0, pol);
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("expm1<%1%>(%1%)", "Unknown error, result is a NaN", result, pol);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> exm1 BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return expm1(arg, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> arg, int* sign, const Policy& pol)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);
   (void)precision_guard;  // warning suppression

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   if (arg > 0)
   {
      mpfr_lngamma(result.backend().data(), arg.backend().data(), GMP_RNDN);
      if (sign)
         *sign = 1;
   }
   else
   {
      if (floor(arg) == arg)
         return policies::raise_pole_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >(
             "lgamma<%1%>", "Evaluation of lgamma at a negative integer %1%.", arg, pol);

      boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> t = detail::sinpx(arg);
      arg                                                                                                                     = -arg;
      if (t < 0)
      {
         t = -t;
      }
      result = boost::multiprecision::log(boost::math::constants::pi<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >()) - lgamma(arg, 0, pol) - boost::multiprecision::log(t);
      if (sign)
      {
         boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> phase = 1 - arg;
         phase                                                                                                                       = floor(phase) / 2;
         if (floor(phase) == phase)
            *sign = -1;
         else
            *sign = 1;
      }
   }
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("lgamma<%1%>(%1%)", 0, pol);
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("lgamma<%1%>(%1%)", "Unknown error, result is a NaN", result, pol);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, int* sign)
{
   return lgamma(arg, sign, policies::policy<>());
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy& pol)
{
   return lgamma(arg, 0, pol);
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> lgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return lgamma(arg, 0, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline typename boost::enable_if_c<boost::math::policies::is_policy<Policy>::value, boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::type tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy& pol)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_gamma(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("tgamma<%1%>(%1%)", 0, pol);
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("tgamma<%1%>(%1%)", "Unknown error, result is a NaN", result, pol);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> tgamma BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return tgamma(arg, policies::policy<>());
}

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates, class Policy>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> log1p BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg, const Policy& pol)
{
   boost::multiprecision::detail::scoped_default_precision<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> > precision_guard(arg);

   boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> result;
   mpfr_log1p(result.backend().data(), arg.backend().data(), GMP_RNDN);
   if (mpfr_inf_p(result.backend().data()))
      return policies::raise_overflow_error<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >("log1p<%1%>(%1%)", 0, pol);
   if (mpfr_nan_p(result.backend().data()))
      return policies::raise_evaluation_error("log1p<%1%>(%1%)", "Unknown error, result is a NaN", result, pol);
   return result;
}
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
inline boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> log1p BOOST_PREVENT_MACRO_SUBSTITUTION(const boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates>& arg)
{
   return log1p(arg, policies::policy<>());
}

} // namespace math

} // namespace boost

namespace std {

//
// numeric_limits [partial] specializations for the types declared in this header:
//
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> number_type;

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
         mpfr_div_2exp(value.second.backend().data(), value.second.backend().data(), -mpfr_get_emin(), GMP_RNDN);
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
         mpfr_mul_2exp(value.second.backend().data(), value.second.backend().data(), mpfr_get_emax(), GMP_RNDN);
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
         mpfr_div_2exp(value.second.backend().data(), value.second.backend().data(), std::numeric_limits<number_type>::digits - 1, GMP_RNDN);
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
         mpfr_div_2exp(value.second.backend().data(), value.second.backend().data(), 1, GMP_RNDN);
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
      // returns epsilon/2
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first  = true;
         value.second = 1;
         mpfr_set_inf(value.second.backend().data(), 1);
      }
      return value.second;
   }
   static number_type quiet_NaN()
   {
      // returns epsilon/2
      initializer.do_nothing();
      static std::pair<bool, number_type> value;
      if (!value.first)
      {
         value.first  = true;
         value.second = 1;
         mpfr_set_nan(value.second.backend().data());
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
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<digits10, AllocateType> > >::epsilon();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<digits10, AllocateType> > >::round_error();
         (std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<digits10, AllocateType> > >::min)();
         (std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<digits10, AllocateType> > >::max)();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<digits10, AllocateType> > >::infinity();
         std::numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<digits10, AllocateType> > >::quiet_NaN();
      }
      void do_nothing() const {}
   };
   static const data_initializer initializer;
};

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
const typename numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::data_initializer numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::initializer;

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::digits;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::digits10;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::max_digits10;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::is_signed;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::is_integer;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::is_exact;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::radix;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::min_exponent;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::min_exponent10;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::max_exponent;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::max_exponent10;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::has_infinity;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::has_quiet_NaN;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::has_signaling_NaN;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::has_denorm;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::has_denorm_loss;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::is_iec559;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::is_bounded;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::is_modulo;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::traps;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::tinyness_before;
template <unsigned Digits10, boost::multiprecision::mpfr_allocation_type AllocateType, boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<Digits10, AllocateType>, ExpressionTemplates> >::round_style;

#endif

template <boost::multiprecision::expression_template_option ExpressionTemplates>
class numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >
{
   typedef boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> number_type;

 public:
   BOOST_STATIC_CONSTEXPR bool is_specialized = false;
   static number_type(min)()
   {
      number_type value(0.5);
      mpfr_div_2exp(value.backend().data(), value.backend().data(), -mpfr_get_emin(), GMP_RNDN);
      return value;
   }
   static number_type(max)()
   {
      number_type value(0.5);
      mpfr_mul_2exp(value.backend().data(), value.backend().data(), mpfr_get_emax(), GMP_RNDN);
      return value;
   }
   static number_type lowest()
   {
      return -(max)();
   }
   BOOST_STATIC_CONSTEXPR int  digits       = INT_MAX;
   BOOST_STATIC_CONSTEXPR int  digits10     = INT_MAX;
   BOOST_STATIC_CONSTEXPR int  max_digits10 = INT_MAX;
   BOOST_STATIC_CONSTEXPR bool is_signed    = true;
   BOOST_STATIC_CONSTEXPR bool is_integer   = false;
   BOOST_STATIC_CONSTEXPR bool is_exact     = false;
   BOOST_STATIC_CONSTEXPR int  radix        = 2;
   static number_type          epsilon()
   {
      number_type value(1);
      mpfr_div_2exp(value.backend().data(), value.backend().data(), boost::multiprecision::detail::digits10_2_2(number_type::default_precision()) - 1, GMP_RNDN);
      return value;
   }
   static number_type round_error()
   {
      return epsilon() / 2;
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
      number_type value;
      mpfr_set_inf(value.backend().data(), 1);
      return value;
   }
   static number_type quiet_NaN()
   {
      number_type value;
      mpfr_set_nan(value.backend().data());
      return value;
   }
   static number_type          signaling_NaN() { return number_type(0); }
   static number_type          denorm_min() { return number_type(0); }
   BOOST_STATIC_CONSTEXPR bool is_iec559                = false;
   BOOST_STATIC_CONSTEXPR bool is_bounded               = true;
   BOOST_STATIC_CONSTEXPR bool is_modulo                = false;
   BOOST_STATIC_CONSTEXPR bool traps                    = false;
   BOOST_STATIC_CONSTEXPR bool tinyness_before          = false;
   BOOST_STATIC_CONSTEXPR float_round_style round_style = round_toward_zero;
};

#ifndef BOOST_NO_INCLASS_MEMBER_INITIALIZATION

template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::digits;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::max_digits10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::is_signed;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::is_integer;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::is_exact;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST int numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::radix;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::min_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::min_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::max_exponent;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST long numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::max_exponent10;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::has_infinity;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::has_quiet_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::has_signaling_NaN;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_denorm_style numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::has_denorm;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::has_denorm_loss;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::is_iec559;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::is_bounded;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::is_modulo;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::traps;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST bool numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::tinyness_before;
template <boost::multiprecision::expression_template_option ExpressionTemplates>
BOOST_CONSTEXPR_OR_CONST float_round_style numeric_limits<boost::multiprecision::number<boost::multiprecision::mpfr_float_backend<0>, ExpressionTemplates> >::round_style;

#endif
} // namespace std
#endif

/* mpfr.hpp
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
*/