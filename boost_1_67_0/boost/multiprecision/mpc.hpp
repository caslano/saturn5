///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MULTIPRECISION_MPC_HPP
#define BOOST_MULTIPRECISION_MPC_HPP

#include <boost/multiprecision/number.hpp>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/detail/digits.hpp>
#include <boost/multiprecision/detail/atomic.hpp>
#include <boost/multiprecision/traits/is_variable_precision.hpp>
#include <boost/multiprecision/mpfr.hpp>
#include <boost/multiprecision/logged_adaptor.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <mpc.h>
#include <cmath>
#include <algorithm>
#include <complex>

#ifndef BOOST_MULTIPRECISION_MPFI_DEFAULT_PRECISION
#define BOOST_MULTIPRECISION_MPFI_DEFAULT_PRECISION 20
#endif

namespace boost {
namespace multiprecision {
namespace backends {

template <unsigned digits10>
struct mpc_complex_backend;

} // namespace backends

template <unsigned digits10>
struct number_category<backends::mpc_complex_backend<digits10> > : public mpl::int_<number_kind_complex>
{};

namespace backends {

namespace detail {

inline void mpc_copy_precision(mpc_t dest, const mpc_t src)
{
   mpfr_prec_t p_dest = mpc_get_prec(dest);
   mpfr_prec_t p_src  = mpc_get_prec(src);
   if (p_dest != p_src)
      mpc_set_prec(dest, p_src);
}
inline void mpc_copy_precision(mpc_t dest, const mpc_t src1, const mpc_t src2)
{
   mpfr_prec_t p_dest = mpc_get_prec(dest);
   mpfr_prec_t p_src1 = mpc_get_prec(src1);
   mpfr_prec_t p_src2 = mpc_get_prec(src2);
   if (p_src2 > p_src1)
      p_src1 = p_src2;
   if (p_dest != p_src1)
      mpc_set_prec(dest, p_src1);
}

template <unsigned digits10>
struct mpc_complex_imp
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

   mpc_complex_imp()
   {
      mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_ui(m_data, 0u, GMP_RNDN);
   }
   mpc_complex_imp(unsigned digits2)
   {
      mpc_init2(m_data, digits2);
      mpc_set_ui(m_data, 0u, GMP_RNDN);
   }

   mpc_complex_imp(const mpc_complex_imp& o)
   {
      mpc_init2(m_data, mpc_get_prec(o.m_data));
      if (o.m_data[0].re[0]._mpfr_d)
         mpc_set(m_data, o.m_data, GMP_RNDN);
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpc_complex_imp(mpc_complex_imp&& o) BOOST_NOEXCEPT
   {
      m_data[0]                 = o.m_data[0];
      o.m_data[0].re[0]._mpfr_d = 0;
   }
#endif
   mpc_complex_imp& operator=(const mpc_complex_imp& o)
   {
      if ((o.m_data[0].re[0]._mpfr_d) && (this != &o))
      {
         if (m_data[0].re[0]._mpfr_d == 0)
            mpc_init2(m_data, mpc_get_prec(o.m_data));
         mpc_set(m_data, o.m_data, GMP_RNDD);
      }
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpc_complex_imp& operator=(mpc_complex_imp&& o) BOOST_NOEXCEPT
   {
      mpc_swap(m_data, o.m_data);
      return *this;
   }
#endif
#ifdef BOOST_HAS_LONG_LONG
#ifdef _MPFR_H_HAVE_INTMAX_T
   mpc_complex_imp& operator=(boost::ulong_long_type i)
   {
      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_uj(data(), i, GMP_RNDD);
      return *this;
   }
   mpc_complex_imp& operator=(boost::long_long_type i)
   {
      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_sj(data(), i, GMP_RNDD);
      return *this;
   }
#else
   mpc_complex_imp& operator=(boost::ulong_long_type i)
   {
      mpfr_float_backend<digits10> f(0uL, mpc_get_prec(m_data));
      f = i;
      mpc_set_fr(this->data(), f.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_imp& operator=(boost::long_long_type i)
   {
      mpfr_float_backend<digits10> f(0uL, mpc_get_prec(m_data));
      f = i;
      mpc_set_fr(this->data(), f.data(), GMP_RNDN);
      return *this;
   }
#endif
#endif
   mpc_complex_imp& operator=(unsigned long i)
   {
      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_ui(m_data, i, GMP_RNDN);
      return *this;
   }
   mpc_complex_imp& operator=(long i)
   {
      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_si(m_data, i, GMP_RNDN);
      return *this;
   }
   mpc_complex_imp& operator=(double d)
   {
      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_d(m_data, d, GMP_RNDN);
      return *this;
   }
   mpc_complex_imp& operator=(long double d)
   {
      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_ld(m_data, d, GMP_RNDN);
      return *this;
   }
   mpc_complex_imp& operator=(mpz_t i)
   {
      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_z(m_data, i, GMP_RNDN);
      return *this;
   }
   mpc_complex_imp& operator=(gmp_int i)
   {
      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));
      mpc_set_z(m_data, i.data(), GMP_RNDN);
      return *this;
   }

   mpc_complex_imp& operator=(const char* s)
   {
      using default_ops::eval_fpclassify;

      if (m_data[0].re[0]._mpfr_d == 0)
         mpc_init2(m_data, multiprecision::detail::digits10_2_2(digits10 ? digits10 : (unsigned)get_default_precision()));

      mpfr_float_backend<digits10> a(0uL, mpc_get_prec(m_data)), b(0uL, mpc_get_prec(m_data));

      if (s && (*s == '('))
      {
         std::string part;
         const char* p = ++s;
         while (*p && (*p != ',') && (*p != ')'))
            ++p;
         part.assign(s, p);
         if (part.size())
            a = part.c_str();
         else
            a = 0uL;
         s = p;
         if (*p && (*p != ')'))
         {
            ++p;
            while (*p && (*p != ')'))
               ++p;
            part.assign(s + 1, p);
         }
         else
            part.erase();
         if (part.size())
            b = part.c_str();
         else
            b = 0uL;
      }
      else
      {
         a = s;
         b = 0uL;
      }

      if (eval_fpclassify(a) == (int)FP_NAN)
      {
         mpc_set_fr(this->data(), a.data(), GMP_RNDN);
      }
      else if (eval_fpclassify(b) == (int)FP_NAN)
      {
         mpc_set_fr(this->data(), b.data(), GMP_RNDN);
      }
      else
      {
         mpc_set_fr_fr(m_data, a.data(), b.data(), GMP_RNDN);
      }
      return *this;
   }
   void swap(mpc_complex_imp& o) BOOST_NOEXCEPT
   {
      mpc_swap(m_data, o.m_data);
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      BOOST_ASSERT(m_data[0].re[0]._mpfr_d);

      mpfr_float_backend<digits10> a(0uL, mpc_get_prec(m_data)), b(0uL, mpc_get_prec(m_data));

      mpc_real(a.data(), m_data, GMP_RNDD);
      mpc_imag(b.data(), m_data, GMP_RNDD);

      if (eval_is_zero(b))
         return a.str(digits, f);

      return "(" + a.str(digits, f) + "," + b.str(digits, f) + ")";
   }
   ~mpc_complex_imp() BOOST_NOEXCEPT
   {
      if (m_data[0].re[0]._mpfr_d)
         mpc_clear(m_data);
   }
   void negate() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].re[0]._mpfr_d);
      mpc_neg(m_data, m_data, GMP_RNDD);
   }
   int compare(const mpc_complex_imp& o) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].re[0]._mpfr_d && o.m_data[0].re[0]._mpfr_d);
      return mpc_cmp(m_data, o.m_data);
   }
   int compare(const mpc_complex_backend<digits10>& o) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].re[0]._mpfr_d && o.m_data[0].re[0]._mpfr_d);
      return mpc_cmp(m_data, o.data());
   }
   int compare(long int i) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].re[0]._mpfr_d);
      return mpc_cmp_si(m_data, i);
   }
   int compare(unsigned long int i) const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].re[0]._mpfr_d);
      static const unsigned long int max_val = (std::numeric_limits<long>::max)();
      if (i > max_val)
      {
         mpc_complex_imp d(mpc_get_prec(m_data));
         d = i;
         return compare(d);
      }
      return mpc_cmp_si(m_data, (long)i);
   }
   template <class V>
   int compare(const V& v) const BOOST_NOEXCEPT
   {
      mpc_complex_imp d(mpc_get_prec(m_data));
      d = v;
      return compare(d);
   }
   mpc_t& data() BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].re[0]._mpfr_d);
      return m_data;
   }
   const mpc_t& data() const BOOST_NOEXCEPT
   {
      BOOST_ASSERT(m_data[0].re[0]._mpfr_d);
      return m_data;
   }

 protected:
   mpc_t            m_data;
   static boost::multiprecision::detail::precision_type& get_default_precision() BOOST_NOEXCEPT
   {
      static boost::multiprecision::detail::precision_type val(BOOST_MULTIPRECISION_MPFI_DEFAULT_PRECISION);
      return val;
   }
};

} // namespace detail

template <unsigned digits10>
struct mpc_complex_backend : public detail::mpc_complex_imp<digits10>
{
   mpc_complex_backend() : detail::mpc_complex_imp<digits10>() {}
   mpc_complex_backend(const mpc_complex_backend& o) : detail::mpc_complex_imp<digits10>(o) {}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpc_complex_backend(mpc_complex_backend&& o) : detail::mpc_complex_imp<digits10>(static_cast<detail::mpc_complex_imp<digits10>&&>(o))
   {}
#endif
   template <unsigned D>
   mpc_complex_backend(const mpc_complex_backend<D>& val, typename enable_if_c<D <= digits10>::type* = 0)
       : detail::mpc_complex_imp<digits10>()
   {
      mpc_set(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   explicit mpc_complex_backend(const mpc_complex_backend<D>& val, typename disable_if_c<D <= digits10>::type* = 0)
       : detail::mpc_complex_imp<digits10>()
   {
      mpc_set(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   mpc_complex_backend(const mpfr_float_backend<D>& val, typename enable_if_c<D <= digits10>::type* = 0)
       : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_fr(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   explicit mpc_complex_backend(const mpfr_float_backend<D>& val, typename disable_if_c<D <= digits10>::type* = 0)
       : detail::mpc_complex_imp<digits10>()
   {
      mpc_set(this->m_data, val.data(), GMP_RNDN);
   }
   mpc_complex_backend(const mpc_t val)
       : detail::mpc_complex_imp<digits10>()
   {
      mpc_set(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend(const std::complex<float>& val)
       : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_d_d(this->m_data, val.real(), val.imag(), GMP_RNDN);
   }
   mpc_complex_backend(const std::complex<double>& val)
       : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_d_d(this->m_data, val.real(), val.imag(), GMP_RNDN);
   }
   mpc_complex_backend(const std::complex<long double>& val)
       : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_ld_ld(this->m_data, val.real(), val.imag(), GMP_RNDN);
   }
   mpc_complex_backend(mpz_srcptr val) : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_z(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend& operator=(mpz_srcptr val)
   {
      mpc_set_z(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(gmp_int const& val) : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_z(this->m_data, val.data(), GMP_RNDN);
   }
   mpc_complex_backend& operator=(gmp_int const& val)
   {
      mpc_set_z(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(mpf_srcptr val) : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_f(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend& operator=(mpf_srcptr val)
   {
      mpc_set_f(this->m_data, val, GMP_RNDN);
      return *this;
   }
   template <unsigned D10>
   mpc_complex_backend(gmp_float<D10> const& val) : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_f(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D10>
   mpc_complex_backend& operator=(gmp_float<D10> const& val)
   {
      mpc_set_f(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(mpq_srcptr val) : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_q(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend& operator=(mpq_srcptr val)
   {
      mpc_set_q(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(gmp_rational const& val) : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_q(this->m_data, val.data(), GMP_RNDN);
   }
   mpc_complex_backend& operator=(gmp_rational const& val)
   {
      mpc_set_q(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(mpfr_srcptr val) : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_fr(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend& operator=(mpfr_srcptr val)
   {
      mpc_set_fr(this->m_data, val, GMP_RNDN);
      return *this;
   }
   template <unsigned D10, mpfr_allocation_type AllocationType>
   mpc_complex_backend(mpfr_float_backend<D10, AllocationType> const& val) : detail::mpc_complex_imp<digits10>()
   {
      mpc_set_fr(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D10, mpfr_allocation_type AllocationType>
   mpc_complex_backend& operator=(mpfr_float_backend<D10, AllocationType> const& val)
   {
      mpc_set_fr(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend& operator=(const mpc_complex_backend& o)
   {
      *static_cast<detail::mpc_complex_imp<digits10>*>(this) = static_cast<detail::mpc_complex_imp<digits10> const&>(o);
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpc_complex_backend& operator=(mpc_complex_backend&& o) BOOST_NOEXCEPT
   {
      *static_cast<detail::mpc_complex_imp<digits10>*>(this) = static_cast<detail::mpc_complex_imp<digits10>&&>(o);
      return *this;
   }
#endif
   template <class V>
   mpc_complex_backend& operator=(const V& v)
   {
      *static_cast<detail::mpc_complex_imp<digits10>*>(this) = v;
      return *this;
   }
   mpc_complex_backend& operator=(const mpc_t val)
   {
      mpc_set(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpc_complex_backend& operator=(const std::complex<float>& val)
   {
      mpc_set_d_d(this->m_data, val.real(), val.imag(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend& operator=(const std::complex<double>& val)
   {
      mpc_set_d_d(this->m_data, val.real(), val.imag(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend& operator=(const std::complex<long double>& val)
   {
      mpc_set_ld_ld(this->m_data, val.real(), val.imag(), GMP_RNDN);
      return *this;
   }
   // We don't change our precision here, this is a fixed precision type:
   template <unsigned D>
   mpc_complex_backend& operator=(const mpc_complex_backend<D>& val)
   {
      mpc_set(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
};

template <>
struct mpc_complex_backend<0> : public detail::mpc_complex_imp<0>
{
   mpc_complex_backend() : detail::mpc_complex_imp<0>() {}
   mpc_complex_backend(const mpc_t val)
       : detail::mpc_complex_imp<0>(mpc_get_prec(val))
   {
      mpc_set(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend(const mpc_complex_backend& o) : detail::mpc_complex_imp<0>(o) {}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpc_complex_backend(mpc_complex_backend&& o) BOOST_NOEXCEPT : detail::mpc_complex_imp<0>(static_cast<detail::mpc_complex_imp<0>&&>(o))
   {}
#endif
   mpc_complex_backend(const mpc_complex_backend& o, unsigned digits10)
       : detail::mpc_complex_imp<0>(multiprecision::detail::digits10_2_2(digits10))
   {
      mpc_set(this->m_data, o.data(), GMP_RNDN);
   }
   template <unsigned D>
   mpc_complex_backend(const mpc_complex_backend<D>& val)
       : detail::mpc_complex_imp<0>(mpc_get_prec(val.data()))
   {
      mpc_set(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned D>
   mpc_complex_backend(const mpfr_float_backend<D>& val)
       : detail::mpc_complex_imp<0>(mpfr_get_prec(val.data()))
   {
      mpc_set_fr(this->m_data, val.data(), GMP_RNDN);
   }
   mpc_complex_backend(mpz_srcptr val) : detail::mpc_complex_imp<0>()
   {
      mpc_set_z(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend& operator=(mpz_srcptr val)
   {
      mpc_set_z(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(gmp_int const& val) : detail::mpc_complex_imp<0>()
   {
      mpc_set_z(this->m_data, val.data(), GMP_RNDN);
   }
   mpc_complex_backend& operator=(gmp_int const& val)
   {
      mpc_set_z(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(mpf_srcptr val) : detail::mpc_complex_imp<0>((unsigned)mpf_get_prec(val))
   {
      mpc_set_f(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend& operator=(mpf_srcptr val)
   {
      if ((mp_bitcnt_t)mpc_get_prec(data()) != mpf_get_prec(val))
      {
         mpc_complex_backend t(val);
         t.swap(*this);
      }
      else
         mpc_set_f(this->m_data, val, GMP_RNDN);
      return *this;
   }
   template <unsigned digits10>
   mpc_complex_backend(gmp_float<digits10> const& val) : detail::mpc_complex_imp<0>((unsigned)mpf_get_prec(val.data()))
   {
      mpc_set_f(this->m_data, val.data(), GMP_RNDN);
   }
   template <unsigned digits10>
   mpc_complex_backend& operator=(gmp_float<digits10> const& val)
   {
      if (mpc_get_prec(data()) != (mpfr_prec_t)mpf_get_prec(val.data()))
      {
         mpc_complex_backend t(val);
         t.swap(*this);
      }
      else
         mpc_set_f(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(mpq_srcptr val) : detail::mpc_complex_imp<0>()
   {
      mpc_set_q(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend& operator=(mpq_srcptr val)
   {
      mpc_set_q(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(gmp_rational const& val) : detail::mpc_complex_imp<0>()
   {
      mpc_set_q(this->m_data, val.data(), GMP_RNDN);
   }
   mpc_complex_backend& operator=(gmp_rational const& val)
   {
      mpc_set_q(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(mpfr_srcptr val) : detail::mpc_complex_imp<0>(mpfr_get_prec(val))
   {
      mpc_set_fr(this->m_data, val, GMP_RNDN);
   }
   mpc_complex_backend& operator=(mpfr_srcptr val)
   {
      if (mpc_get_prec(data()) != mpfr_get_prec(val))
      {
         mpc_complex_backend t(val);
         t.swap(*this);
      }
      else
         mpc_set_fr(this->m_data, val, GMP_RNDN);
      return *this;
   }
   mpc_complex_backend(const std::complex<float>& val)
       : detail::mpc_complex_imp<0>()
   {
      mpc_set_d_d(this->m_data, val.real(), val.imag(), GMP_RNDN);
   }
   mpc_complex_backend(const std::complex<double>& val)
       : detail::mpc_complex_imp<0>()
   {
      mpc_set_d_d(this->m_data, val.real(), val.imag(), GMP_RNDN);
   }
   mpc_complex_backend(const std::complex<long double>& val)
       : detail::mpc_complex_imp<0>()
   {
      mpc_set_ld_ld(this->m_data, val.real(), val.imag(), GMP_RNDN);
   }
   // Construction with precision:
   template <class T, class U>
   mpc_complex_backend(const T& a, const U& b, unsigned digits10)
       : detail::mpc_complex_imp<0>(multiprecision::detail::digits10_2_2(digits10))
   {
      // We can't use assign_components here because it copies the precision of
      // a and b, not digits10....
      mpfr_float ca(a), cb(b);
      mpc_set_fr_fr(this->data(), ca.backend().data(), cb.backend().data(), GMP_RNDN);
   }
   template <unsigned N>
   mpc_complex_backend(const mpfr_float_backend<N>& a, const mpfr_float_backend<N>& b, unsigned digits10)
       : detail::mpc_complex_imp<0>(multiprecision::detail::digits10_2_2(digits10))
   {
      mpc_set_fr_fr(this->data(), a.data(), b.data(), GMP_RNDN);
   }

   mpc_complex_backend& operator=(const mpc_complex_backend& o)
   {
      if (this != &o)
      {
         detail::mpc_copy_precision(this->m_data, o.data());
         mpc_set(this->m_data, o.data(), GMP_RNDN);
      }
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   mpc_complex_backend& operator=(mpc_complex_backend&& o) BOOST_NOEXCEPT
   {
      *static_cast<detail::mpc_complex_imp<0>*>(this) = static_cast<detail::mpc_complex_imp<0>&&>(o);
      return *this;
   }
#endif
   template <class V>
   mpc_complex_backend& operator=(const V& v)
   {
      *static_cast<detail::mpc_complex_imp<0>*>(this) = v;
      return *this;
   }
   mpc_complex_backend& operator=(const mpc_t val)
   {
      mpc_set_prec(this->m_data, mpc_get_prec(val));
      mpc_set(this->m_data, val, GMP_RNDN);
      return *this;
   }
   template <unsigned D>
   mpc_complex_backend& operator=(const mpc_complex_backend<D>& val)
   {
      mpc_set_prec(this->m_data, mpc_get_prec(val.data()));
      mpc_set(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   template <unsigned D>
   mpc_complex_backend& operator=(const mpfr_float_backend<D>& val)
   {
      mpc_set_prec(this->m_data, mpfr_get_prec(val.data()));
      mpc_set_fr(this->m_data, val.data(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend& operator=(const std::complex<float>& val)
   {
      mpc_set_d_d(this->m_data, val.real(), val.imag(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend& operator=(const std::complex<double>& val)
   {
      mpc_set_d_d(this->m_data, val.real(), val.imag(), GMP_RNDN);
      return *this;
   }
   mpc_complex_backend& operator=(const std::complex<long double>& val)
   {
      mpc_set_ld_ld(this->m_data, val.real(), val.imag(), GMP_RNDN);
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
      return multiprecision::detail::digits2_2_10(mpc_get_prec(this->m_data));
   }
   void precision(unsigned digits10) BOOST_NOEXCEPT
   {
      mpfr_prec_round(mpc_realref(this->m_data), multiprecision::detail::digits10_2_2((digits10)), GMP_RNDN);
      mpfr_prec_round(mpc_imagref(this->m_data), multiprecision::detail::digits10_2_2((digits10)), GMP_RNDN);
   }
};

template <unsigned digits10, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_eq(const mpc_complex_backend<digits10>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) == 0;
}
template <unsigned digits10, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_lt(const mpc_complex_backend<digits10>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) < 0;
}
template <unsigned digits10, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_gt(const mpc_complex_backend<digits10>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) > 0;
}

template <unsigned D1, unsigned D2>
inline void eval_add(mpc_complex_backend<D1>& result, const mpc_complex_backend<D2>& o)
{
   mpc_add(result.data(), result.data(), o.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpc_complex_backend<D1>& result, const mpfr_float_backend<D2>& o)
{
   mpc_add_fr(result.data(), result.data(), o.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpc_complex_backend<D1>& result, const mpc_complex_backend<D2>& o)
{
   mpc_sub(result.data(), result.data(), o.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpc_complex_backend<D1>& result, const mpfr_float_backend<D2>& o)
{
   mpc_sub_fr(result.data(), result.data(), o.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpc_complex_backend<D1>& result, const mpc_complex_backend<D2>& o)
{
   if ((void*)&result == (void*)&o)
      mpc_sqr(result.data(), o.data(), GMP_RNDN);
   else
      mpc_mul(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpc_complex_backend<D1>& result, const mpfr_float_backend<D2>& o)
{
   mpc_mul_fr(result.data(), result.data(), o.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpc_complex_backend<D1>& result, const mpc_complex_backend<D2>& o)
{
   mpc_div(result.data(), result.data(), o.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpc_complex_backend<D1>& result, const mpfr_float_backend<D2>& o)
{
   mpc_div_fr(result.data(), result.data(), o.data(), GMP_RNDD);
}
template <unsigned digits10>
inline void eval_add(mpc_complex_backend<digits10>& result, unsigned long i)
{
   mpc_add_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10>
inline void eval_subtract(mpc_complex_backend<digits10>& result, unsigned long i)
{
   mpc_sub_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10>
inline void eval_multiply(mpc_complex_backend<digits10>& result, unsigned long i)
{
   mpc_mul_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10>
inline void eval_divide(mpc_complex_backend<digits10>& result, unsigned long i)
{
   mpc_div_ui(result.data(), result.data(), i, GMP_RNDN);
}
template <unsigned digits10>
inline void eval_add(mpc_complex_backend<digits10>& result, long i)
{
   if (i > 0)
      mpc_add_ui(result.data(), result.data(), i, GMP_RNDN);
   else
      mpc_sub_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i), GMP_RNDN);
}
template <unsigned digits10>
inline void eval_subtract(mpc_complex_backend<digits10>& result, long i)
{
   if (i > 0)
      mpc_sub_ui(result.data(), result.data(), i, GMP_RNDN);
   else
      mpc_add_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i), GMP_RNDN);
}
template <unsigned digits10>
inline void eval_multiply(mpc_complex_backend<digits10>& result, long i)
{
   mpc_mul_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i), GMP_RNDN);
   if (i < 0)
      mpc_neg(result.data(), result.data(), GMP_RNDN);
}
template <unsigned digits10>
inline void eval_divide(mpc_complex_backend<digits10>& result, long i)
{
   mpc_div_ui(result.data(), result.data(), boost::multiprecision::detail::unsigned_abs(i), GMP_RNDN);
   if (i < 0)
      mpc_neg(result.data(), result.data(), GMP_RNDN);
}
//
// Specialised 3 arg versions of the basic operators:
//
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_add(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, const mpc_complex_backend<D3>& y)
{
   mpc_add(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_add(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, const mpfr_float_backend<D3>& y)
{
   mpc_add_fr(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_add(mpc_complex_backend<D1>& a, const mpfr_float_backend<D2>& x, const mpc_complex_backend<D3>& y)
{
   mpc_add_fr(a.data(), y.data(), x.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, unsigned long y)
{
   mpc_add_ui(a.data(), x.data(), y, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, long y)
{
   if (y < 0)
      mpc_sub_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y), GMP_RNDD);
   else
      mpc_add_ui(a.data(), x.data(), y, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpc_complex_backend<D1>& a, unsigned long x, const mpc_complex_backend<D2>& y)
{
   mpc_add_ui(a.data(), y.data(), x, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_add(mpc_complex_backend<D1>& a, long x, const mpc_complex_backend<D2>& y)
{
   if (x < 0)
   {
      mpc_ui_sub(a.data(), boost::multiprecision::detail::unsigned_abs(x), y.data(), GMP_RNDN);
      mpc_neg(a.data(), a.data(), GMP_RNDD);
   }
   else
      mpc_add_ui(a.data(), y.data(), x, GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_subtract(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, const mpc_complex_backend<D3>& y)
{
   mpc_sub(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_subtract(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, const mpfr_float_backend<D3>& y)
{
   mpc_sub_fr(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_subtract(mpc_complex_backend<D1>& a, const mpfr_float_backend<D2>& x, const mpc_complex_backend<D3>& y)
{
   mpc_fr_sub(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, unsigned long y)
{
   mpc_sub_ui(a.data(), x.data(), y, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, long y)
{
   if (y < 0)
      mpc_add_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y), GMP_RNDD);
   else
      mpc_sub_ui(a.data(), x.data(), y, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpc_complex_backend<D1>& a, unsigned long x, const mpc_complex_backend<D2>& y)
{
   mpc_ui_sub(a.data(), x, y.data(), GMP_RNDN);
}
template <unsigned D1, unsigned D2>
inline void eval_subtract(mpc_complex_backend<D1>& a, long x, const mpc_complex_backend<D2>& y)
{
   if (x < 0)
   {
      mpc_add_ui(a.data(), y.data(), boost::multiprecision::detail::unsigned_abs(x), GMP_RNDD);
      mpc_neg(a.data(), a.data(), GMP_RNDD);
   }
   else
      mpc_ui_sub(a.data(), x, y.data(), GMP_RNDN);
}

template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_multiply(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, const mpc_complex_backend<D3>& y)
{
   if ((void*)&x == (void*)&y)
      mpc_sqr(a.data(), x.data(), GMP_RNDD);
   else
      mpc_mul(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_multiply(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, const mpfr_float_backend<D3>& y)
{
   mpc_mul_fr(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_multiply(mpc_complex_backend<D1>& a, const mpfr_float_backend<D2>& x, const mpc_complex_backend<D3>& y)
{
   mpc_mul_fr(a.data(), y.data(), x.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, unsigned long y)
{
   mpc_mul_ui(a.data(), x.data(), y, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, long y)
{
   if (y < 0)
   {
      mpc_mul_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y), GMP_RNDD);
      a.negate();
   }
   else
      mpc_mul_ui(a.data(), x.data(), y, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpc_complex_backend<D1>& a, unsigned long x, const mpc_complex_backend<D2>& y)
{
   mpc_mul_ui(a.data(), y.data(), x, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_multiply(mpc_complex_backend<D1>& a, long x, const mpc_complex_backend<D2>& y)
{
   if (x < 0)
   {
      mpc_mul_ui(a.data(), y.data(), boost::multiprecision::detail::unsigned_abs(x), GMP_RNDD);
      mpc_neg(a.data(), a.data(), GMP_RNDD);
   }
   else
      mpc_mul_ui(a.data(), y.data(), x, GMP_RNDD);
}

template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_divide(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, const mpc_complex_backend<D3>& y)
{
   mpc_div(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_divide(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, const mpfr_float_backend<D3>& y)
{
   mpc_div_fr(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2, unsigned D3>
inline void eval_divide(mpc_complex_backend<D1>& a, const mpfr_float_backend<D2>& x, const mpc_complex_backend<D3>& y)
{
   mpc_fr_div(a.data(), x.data(), y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, unsigned long y)
{
   mpc_div_ui(a.data(), x.data(), y, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpc_complex_backend<D1>& a, const mpc_complex_backend<D2>& x, long y)
{
   if (y < 0)
   {
      mpc_div_ui(a.data(), x.data(), boost::multiprecision::detail::unsigned_abs(y), GMP_RNDD);
      a.negate();
   }
   else
      mpc_div_ui(a.data(), x.data(), y, GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpc_complex_backend<D1>& a, unsigned long x, const mpc_complex_backend<D2>& y)
{
   mpc_ui_div(a.data(), x, y.data(), GMP_RNDD);
}
template <unsigned D1, unsigned D2>
inline void eval_divide(mpc_complex_backend<D1>& a, long x, const mpc_complex_backend<D2>& y)
{
   if (x < 0)
   {
      mpc_ui_div(a.data(), boost::multiprecision::detail::unsigned_abs(x), y.data(), GMP_RNDD);
      mpc_neg(a.data(), a.data(), GMP_RNDD);
   }
   else
      mpc_ui_div(a.data(), x, y.data(), GMP_RNDD);
}

template <unsigned digits10>
inline bool eval_is_zero(const mpc_complex_backend<digits10>& val) BOOST_NOEXCEPT
{
   return (0 != mpfr_zero_p(mpc_realref(val.data()))) && (0 != mpfr_zero_p(mpc_imagref(val.data())));
}
template <unsigned digits10>
inline int eval_get_sign(const mpc_complex_backend<digits10>&)
{
   BOOST_STATIC_ASSERT_MSG(digits10 == UINT_MAX, "Complex numbers have no sign bit."); // designed to always fail
   return 0;
}

template <unsigned digits10>
inline void eval_convert_to(unsigned long* result, const mpc_complex_backend<digits10>& val)
{
   if (0 == mpfr_zero_p(mpc_imagref(val.data())))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
   }
   mpfr_float_backend<digits10> t;
   mpc_real(t.data(), val.data(), GMP_RNDN);
   eval_convert_to(result, t);
}
template <unsigned digits10>
inline void eval_convert_to(long* result, const mpc_complex_backend<digits10>& val)
{
   if (0 == mpfr_zero_p(mpc_imagref(val.data())))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
   }
   mpfr_float_backend<digits10> t;
   mpc_real(t.data(), val.data(), GMP_RNDN);
   eval_convert_to(result, t);
}
#ifdef _MPFR_H_HAVE_INTMAX_T
template <unsigned digits10>
inline void eval_convert_to(boost::ulong_long_type* result, const mpc_complex_backend<digits10>& val)
{
   if (0 == mpfr_zero_p(mpc_imagref(val.data())))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
   }
   mpfr_float_backend<digits10> t;
   mpc_real(t.data(), val.data(), GMP_RNDN);
   eval_convert_to(result, t);
}
template <unsigned digits10>
inline void eval_convert_to(boost::long_long_type* result, const mpc_complex_backend<digits10>& val)
{
   if (0 == mpfr_zero_p(mpc_imagref(val.data())))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
   }
   mpfr_float_backend<digits10> t;
   mpc_real(t.data(), val.data(), GMP_RNDN);
   eval_convert_to(result, t);
}
#endif
template <unsigned digits10>
inline void eval_convert_to(double* result, const mpc_complex_backend<digits10>& val) BOOST_NOEXCEPT
{
   if (0 == mpfr_zero_p(mpc_imagref(val.data())))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
   }
   mpfr_float_backend<digits10> t;
   mpc_real(t.data(), val.data(), GMP_RNDN);
   eval_convert_to(result, t);
}
template <unsigned digits10>
inline void eval_convert_to(long double* result, const mpc_complex_backend<digits10>& val) BOOST_NOEXCEPT
{
   if (0 == mpfr_zero_p(mpc_imagref(val.data())))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
   }
   mpfr_float_backend<digits10> t;
   mpc_real(t.data(), val.data(), GMP_RNDN);
   eval_convert_to(result, t);
}

template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
inline void assign_components(mpc_complex_backend<D1>& result, const mpfr_float_backend<D2, AllocationType>& a, const mpfr_float_backend<D2, AllocationType>& b)
{
   //
   // This is called from class number's constructors, so if we have variable
   // precision, then copy the precision of the source variables.
   //
   if (!D1)
   {
      unsigned long prec = (std::max)(mpfr_get_prec(a.data()), mpfr_get_prec(b.data()));
      mpc_set_prec(result.data(), prec);
   }
   using default_ops::eval_fpclassify;
   if (eval_fpclassify(a) == (int)FP_NAN)
   {
      mpc_set_fr(result.data(), a.data(), GMP_RNDN);
   }
   else if (eval_fpclassify(b) == (int)FP_NAN)
   {
      mpc_set_fr(result.data(), b.data(), GMP_RNDN);
   }
   else
   {
      mpc_set_fr_fr(result.data(), a.data(), b.data(), GMP_RNDN);
   }
}

template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
inline void assign_components(mpc_complex_backend<D1>& result, unsigned long a, unsigned long b)
{
   mpc_set_ui_ui(result.data(), a, b, GMP_RNDN);
}

template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
inline void assign_components(mpc_complex_backend<D1>& result, long a, long b)
{
   mpc_set_si_si(result.data(), a, b, GMP_RNDN);
}

#if defined(BOOST_HAS_LONG_LONG) && defined(_MPFR_H_HAVE_INTMAX_T)
template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
inline void assign_components(mpc_complex_backend<D1>& result, unsigned long long a, unsigned long long b)
{
   mpc_set_uj_uj(result.data(), a, b, GMP_RNDN);
}

template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
inline void assign_components(mpc_complex_backend<D1>& result, long long a, long long b)
{
   mpc_set_sj_sj(result.data(), a, b, GMP_RNDN);
}
#endif

template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
inline void assign_components(mpc_complex_backend<D1>& result, double a, double b)
{
   if ((boost::math::isnan)(a))
   {
      mpc_set_d(result.data(), a, GMP_RNDN);
   }
   else if ((boost::math::isnan)(b))
   {
      mpc_set_d(result.data(), b, GMP_RNDN);
   }
   else
   {
      mpc_set_d_d(result.data(), a, b, GMP_RNDN);
   }
}

template <unsigned D1, unsigned D2, mpfr_allocation_type AllocationType>
inline void assign_components(mpc_complex_backend<D1>& result, long double a, long double b)
{
   if ((boost::math::isnan)(a))
   {
      mpc_set_d(result.data(), a, GMP_RNDN);
   }
   else if ((boost::math::isnan)(b))
   {
      mpc_set_d(result.data(), b, GMP_RNDN);
   }
   else
   {
      mpc_set_ld_ld(result.data(), a, b, GMP_RNDN);
   }
}

//
// Native non-member operations:
//
template <unsigned Digits10>
inline void eval_sqrt(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& val)
{
   mpc_sqrt(result.data(), val.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_pow(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& b, const mpc_complex_backend<Digits10>& e)
{
   mpc_pow(result.data(), b.data(), e.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_exp(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_exp(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_log(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_log(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_log10(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_log10(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_sin(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_sin(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_cos(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_cos(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_tan(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_tan(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_asin(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_asin(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_acos(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_acos(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_atan(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_atan(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_sinh(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_sinh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_cosh(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_cosh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_tanh(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_tanh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_asinh(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_asinh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_acosh(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_acosh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_atanh(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_atanh(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_conj(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_conj(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_proj(mpc_complex_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpc_proj(result.data(), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_real(mpfr_float_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpfr_set_prec(result.data(), mpfr_get_prec(mpc_realref(arg.data())));
   mpfr_set(result.data(), mpc_realref(arg.data()), GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_imag(mpfr_float_backend<Digits10>& result, const mpc_complex_backend<Digits10>& arg)
{
   mpfr_set_prec(result.data(), mpfr_get_prec(mpc_imagref(arg.data())));
   mpfr_set(result.data(), mpc_imagref(arg.data()), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const mpfr_float_backend<Digits10>& arg)
{
   mpfr_set(mpc_imagref(result.data()), arg.data(), GMP_RNDN);
}

template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const mpfr_float_backend<Digits10>& arg)
{
   mpfr_set(mpc_realref(result.data()), arg.data(), GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const gmp_int& arg)
{
   mpfr_set_z(mpc_realref(result.data()), arg.data(), GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const gmp_rational& arg)
{
   mpfr_set_q(mpc_realref(result.data()), arg.data(), GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const unsigned& arg)
{
   mpfr_set_ui(mpc_realref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const unsigned long& arg)
{
   mpfr_set_ui(mpc_realref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const int& arg)
{
   mpfr_set_si(mpc_realref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const long& arg)
{
   mpfr_set_si(mpc_realref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const float& arg)
{
   mpfr_set_flt(mpc_realref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const double& arg)
{
   mpfr_set_d(mpc_realref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const long double& arg)
{
   mpfr_set_ld(mpc_realref(result.data()), arg, GMP_RNDN);
}
#if defined(BOOST_HAS_LONG_LONG) && defined(_MPFR_H_HAVE_INTMAX_T)
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const unsigned long long& arg)
{
   mpfr_set_uj(mpc_realref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_real(mpc_complex_backend<Digits10>& result, const long long& arg)
{
   mpfr_set_sj(mpc_realref(result.data()), arg, GMP_RNDN);
}
#endif

template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const gmp_int& arg)
{
   mpfr_set_z(mpc_imagref(result.data()), arg.data(), GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const gmp_rational& arg)
{
   mpfr_set_q(mpc_imagref(result.data()), arg.data(), GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const unsigned& arg)
{
   mpfr_set_ui(mpc_imagref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const unsigned long& arg)
{
   mpfr_set_ui(mpc_imagref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const int& arg)
{
   mpfr_set_si(mpc_imagref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const long& arg)
{
   mpfr_set_si(mpc_imagref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const float& arg)
{
   mpfr_set_flt(mpc_imagref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const double& arg)
{
   mpfr_set_d(mpc_imagref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const long double& arg)
{
   mpfr_set_ld(mpc_imagref(result.data()), arg, GMP_RNDN);
}
#if defined(BOOST_HAS_LONG_LONG) && defined(_MPFR_H_HAVE_INTMAX_T)
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const unsigned long long& arg)
{
   mpfr_set_uj(mpc_imagref(result.data()), arg, GMP_RNDN);
}
template <unsigned Digits10>
inline void eval_set_imag(mpc_complex_backend<Digits10>& result, const long long& arg)
{
   mpfr_set_sj(mpc_imagref(result.data()), arg, GMP_RNDN);
}
#endif

template <unsigned Digits10>
inline std::size_t hash_value(const mpc_complex_backend<Digits10>& val)
{
   std::size_t result = 0;
   std::size_t len    = val.data()[0].re[0]._mpfr_prec / mp_bits_per_limb;
   if (val.data()[0].re[0]._mpfr_prec % mp_bits_per_limb)
      ++len;
   for (std::size_t i = 0; i < len; ++i)
      boost::hash_combine(result, val.data()[0].re[0]._mpfr_d[i]);
   boost::hash_combine(result, val.data()[0].re[0]._mpfr_exp);
   boost::hash_combine(result, val.data()[0].re[0]._mpfr_sign);

   len = val.data()[0].im[0]._mpfr_prec / mp_bits_per_limb;
   if (val.data()[0].im[0]._mpfr_prec % mp_bits_per_limb)
      ++len;
   for (std::size_t i = 0; i < len; ++i)
      boost::hash_combine(result, val.data()[0].im[0]._mpfr_d[i]);
   boost::hash_combine(result, val.data()[0].im[0]._mpfr_exp);
   boost::hash_combine(result, val.data()[0].im[0]._mpfr_sign);
   return result;
}

} // namespace backends

#ifdef BOOST_NO_SFINAE_EXPR

namespace detail {

template <unsigned D1, unsigned D2>
struct is_explicitly_convertible<backends::mpc_complex_backend<D1>, backends::mpc_complex_backend<D2> > : public mpl::true_
{};

} // namespace detail
#endif

namespace detail {
template <>
struct is_variable_precision<backends::mpc_complex_backend<0> > : public true_type
{};
} // namespace detail

template <>
struct number_category<detail::canonical<mpc_t, backends::mpc_complex_backend<0> >::type> : public mpl::int_<number_kind_floating_point>
{};

using boost::multiprecision::backends::mpc_complex_backend;

typedef number<mpc_complex_backend<50> >   mpc_complex_50;
typedef number<mpc_complex_backend<100> >  mpc_complex_100;
typedef number<mpc_complex_backend<500> >  mpc_complex_500;
typedef number<mpc_complex_backend<1000> > mpc_complex_1000;
typedef number<mpc_complex_backend<0> >    mpc_complex;

template <unsigned Digits10, expression_template_option ExpressionTemplates>
struct component_type<number<mpc_complex_backend<Digits10>, ExpressionTemplates> >
{
   typedef number<mpfr_float_backend<Digits10>, ExpressionTemplates> type;
};

template <unsigned Digits10, expression_template_option ExpressionTemplates>
struct component_type<number<logged_adaptor<mpc_complex_backend<Digits10> >, ExpressionTemplates> >
{
   typedef number<mpfr_float_backend<Digits10>, ExpressionTemplates> type;
};

template <unsigned Digits10, expression_template_option ExpressionTemplates>
struct complex_result_from_scalar<number<mpfr_float_backend<Digits10>, ExpressionTemplates> >
{
   typedef number<mpc_complex_backend<Digits10>, ExpressionTemplates> type;
};

}

} // namespace boost::multiprecision

#endif

/* mpc.hpp
aYgPqDve7mXYRmpcFNf8wYZdpOtNrdSneu0YXdlPwaMk4WboHf5vxn1JzaCqMsp1maLu9VVgn7hrye6mvpv4v9IJk6dpomDqWB1aYJOy43XignYuzw4wETJhuUzB3fYr6YM5Ckl31xjSnq6bEwlNsn0B62Jio664SEvLZ7XSrsTaAeLZyVwKX6EkCEJStHm+Qsa7RynTF7v/FCl2nc2MpD06y/9tEMEJ2U4hi5q5Gx2ZpsCYZeXP9lnW5Qu5AAIs/dNlBtkKrOLvJeg3BUfYgIRYGafIbS8wn57p/tQxSp9BQjabHty/uFY7VOoFOZthEHwVUIOwaBhzPSnT3bisD+Kgvd98quoQKpH6fGmcLwHg9oagR+Py7bTxuAPcPE+z6RmH8OHB/6pFh0Q6OIs43Idwx1wN2BGflnUpys6gcBTY0QZU/MddPRaNf3y6+tr4ijQj/PJDPJPk6P5Og1SRSMDYD3/Gr3e7xN1VRTaiDx2sUw79IW1Uuouu5yLT8NeXX61fGg2ur0J4fpMVQWwFltcWLREU/XClAEM0A4rRLocTXue6hxgv3y0kPYkL3OMAF46UJJAk8iiK6sdzjwOxMZ/niAmmj5BKwtNPCwwA0Bc4WCVUDIQEK+FHVq7Fw1Iprbl6PTt0deKo1ajuqCHOWxQdbZLkk+GCp42lkyTIJN9zAad7heJOXnNIST8SjT0/mLoET/KC0/kSRVigGPAPe8otCaS9eR8jUFW2+ViWkEyx00fYKesGRIbXQ8pFCbesogrBcjumc7GpLt4E37PCeXNGlKE8RZaJYVMgISjvs4SUWU00lELId1MSFkByh6lR/OtXYBkQTudWg5ROkxWJ+I9kVt+qSIwAXCNJtOVJr/g+LFlsOR2RIYmJPiJ6wWni8hSdQIPvQzfQLD/ZnCbS0CuZohyhtzBjC/Z2hLHKa1jTu46hQ/H4eK+lR809tsGNUlNLMIk0P7WuQaNCLEe9crtBbq6hGygloSNVjlbdxw8BPGpmyPCNTQsAvTrjqhYADt9Xu9qZRQZVIzpD0KJxcGemW4syeLa6aRNTZftom5hEuOyrRqKPESMnJmVABDgVJSZM5x37quVnzl2QimM1QXaJ0YnnxQmao3dE5AwrlLQi22E+x4c0YhY/JrUDNbw3SLfUjfcrJS+nG6j2vJPQRvcXfPHfQFuwAcfXw5kYO8uwkJPR8NNZ3t7cdGrE9g5IfSEt8qeT6ZI09XZtcBiDlWOJjKSKxLiWFTX4c2pLLbdUehfIbOE5ilj1KBVxBT1os+9EDkuremPptLWI5wbtl21rafbolfnp3dYJWuBG24m2QiAAtQVpofB1vqYNMbF9lKqSiZLnba+eUicv50YZKWRm2BfF5AntL8J8rhXzyBsVBdJX8DHfdLW+SNM9Cj+AlP9Z3Oa8ovySLYI1z5K2UoL+PTkSJaFPZEX6bsF+8vxisbusMNZ/1aRZTTQjtvNpAGucpuwZ0VuHRyyyUW6/9gRvBKSQYpR2O7RIaY+51MJG50lRlSA3FiK0Rja9jVjd/13zEQ5tnYQg8hTipPQ9GOHrbb+REgbbb26nvERme0MCPDrGBWzyLPVtedPo3/CImu/4jNBDTe68Nt8ibzQKecYs5ehPf84mayC1bMUSPGjcoDdkX0qzWqykYRLi+AWFMZ9EI8Dx+a5arqRROmcwm5ywkh2AnA2HoeYh3CFaLQtv+3R8s73S+byEZR9dukoZuGz3SGilDFzznbK5SSq9ImJIuYzt4+ncOdtxNowH88W128l2P/RKF5W+rBBMn1qwPcHvNidGoWBmh4sC8HAopXKJMDpgxaxcP+EcdyFP0cNLYWa0f0PPz//+97ATpzgn+L+zW6q9IbyUhFtcXTuApFFs/IQC++DxzOCXzLQQMZtoz0M252D6YZz4DoUE4JWCNuFBwcOzoc1pqssOHdPtl055Cg8ZYoDtxgOIAILghQPLhOzKW/iBLFBStm6zFFttaYF3um4/377FVqs5Wm2qS2WUsx95z7JLrwQ8b9wfyPa3/RN+T6Kvzs3xU3n7cFsj8ZrKNq9VnJ9R2erLls5qjcLlmrlw7tVb14MkQtNVhwncEqfcmFo5GumckMniWYvGBELoogWVSwBRCgexyYq9pJn5w9hZNiptJ7TOKChkCxJ5X0W0aOfkVaE0ic2JtdjhH9QEVkxPDIDDX2ctEc4HnQ7nzspG7OoH/211+V0Vu66HCbGH8IWw5j1chn6fYYBhS3ChOEgGoaI+BTTXWJ2eBHul2SUDCjGNOJs/emtc7TKhCrciFdxbpH1ncmssmIqpTuBWyPlO0/YgONnNSjkK5KTf9DkrmIOTlHsS2IUrO+kFtQ2xIVZ4DuYNijrdCjGIYqHsjpqflH25HDvM306RvazMPMxaCFd2Clgt8AJHCsQN7tZk5SOQ+qA6WbgNLr1c9Qtsm8/DnZ2v+mqCuggH7RJYHPV5INkKxRBPOQLtKyx0oTZPduQucGHBikty3gE0YkjgDswjOqhzZHVSSRe2gacW6w+IvW0SoozlbKF5b4ZiFtp2Cl2ay6e5Y4SUTdXbvgrp70r8otpEvQh10Af42Cl5kyrlcARrzmAkQRpL1oiXQRMMgsZrWFexgPSEgM3mGXQy7yE024ehsBc0i37duV/0pXOnFZspT9JACq7lSM15o0MkS4o9WSh2XJ2lg9YiKt30PVVWmwTuGBfc9ZvfLJWpSGM2zIZRrGAy221YdDaAwWAhfI4HQ7rnzrmg95vLmu81DWJltBaYth5MO1yWpvVPY0LoRIjwLOMfLZihI3TjiAt59aVYEpttEOKbbUDdLH1j7Pd9/8sv5WxFN8434ToJD7Dd08RBJ4UrHwcX/pBEIBaAhOV7Vo4Ymfxqp1FjkcQ+7Lw67NyLjqMkLA53ouA17BQDW1Ms7GSgCAIGrhpOtEPyP7RpHBvcq11PFBHKbITJEDkxveqn6XoeDyw/81+WpO5UVJApWITY48rabGO4XWiDA3epuxndZJ8d3txvqG8qR2TBR5jwqeI1OmXKHlFfaneBSuZii/GZcwbiYMAQF86rdazT6KANezBgwpikgDs1ngZPfZZbi46HKga3twStBtuIsx+yTzpONUVEK9V+tBoqBzw8fPM4vXaZANm5QWT3fTQwkHDgoF7auUEWWJaDJfYkosfbyy5JM81n2g4+iycacAoez0Vki0BhDQ8FuhaJJkaO3Nmq5D7tlzXHchW1KHn7z4LYwCAmxS04560S3g0W0dIOJqR2Xxmfh2YJt/vNLfcn7EWIeUzte0Efp/G/2tQh6B+7zHhUjTKhNFAtBlRFMPtUQTzaEDWaTsKB1zkAvSq5mkVUzxFzu3Yl8ww9fFahsq/ZeZtrf10YjIrrklgnWiEwaI6Kau66zIlIdJk5rngRI/AEdA4ij0BaoZMaligIrkkYrhNEC6qjyW/EaRg3mK5VIctAr+xWzyiv4ZP7rtURq54gMAVzNs1LN9lt0HSNAFb9FX7SL2bQx3qkDzDSAUGtO4sYVM1oEO2CT5IErIn8ONUF9v5+Nre8dZTCptFj1glMY56EuwqaW6JVVSLCjtxoJ+9gQAobx5KMNnNYgoo+FzCQdbHFLJ47J4GR/QRXHyjoQyT2aptibCLtTl+GhjqWUoeo7dwhWcoFtXkMbRNvY2ZW3x7U4/JbeQY78s7tO4DjRxGwTCnQrseNfV/JwkIYEIIWHNuRLWsJTXOKpF5jzh39dk144JlTGwjIvm2NuRygZS98HDLJQ3+StDLiKaph73KTJbLCpAYOR4iD8aSLln2b4vF4RUwxwmxn/kbJGJ7c9GlKzTVg3F/A1AJYcYi7CQnqOkz95HAtUcZoat1qVZdLCp11CK/T4dddJ9vDAU/2owe6kca6DLPewGbV12xzX/X/MOFQATNvQPo9kfMbVkF9ZifPRZCiPXKUwMX9vXBqFz13hWDVMNF8SbzHMzN6Ixmdk875NC4Ps4BsltYg9sr/OVVv5+YGU88FZg+xEN3JyJgaVz55sH7FF2p0S10Y7k7cm728NO/04pzpykY2AuJD1Ojy8F2e6f169bIvnpo5kttAgDbCgIFBQ8lvh6IWZDNMDSmQvtDm5LYolR7qwrpsIUote3zOHB89Q8BUYTGhTC2f9/+jnq8hzkgeyYtjra12a7C1sa+9cwrk7WU9GDBXT1FUT67WDrBwE2yn0cgqByLMvDujXytcJghTZdxZEHNG8LzRCoeFBHeDa94g2P1k7VHdXvXM72y3eug7Irk8rTARKrZMJs0mHJV2DrMW3ECllB7mqWztXE3sn/t0KvSPuUJaT6V8xsFoVlg0zZD8vLma06ZdRmquXGNQ5uVjm/Th2ox3XCoHNqPZYy7AzAeLkU9d9VjIm8vJL0PTfGYuLwTzOcrYqDs9fEHTyl0wt1bX6SOpHco8IxcpG51t7tNcPO8aGG7maziLEoTM39jlo5H04JZUQ1QhcG2SC+4Iqmr9N5sPWMTm0pVENZpTOyx9N+pCLDhZmx/7dYDXa9Bpe4/dnXYJgvjBL2Fqm6Kwk0O5LllchpSG0IWG4YIFrxNiRLgmWIxA/clXvtMQTfmUEs2lT3RVcZftMbQ2J3OMcwvT+ro+utmrK8iZo/h7ed8Cuit5e9gNnxKc4VK2buYXoMq0597lLGQXu44nZQ21P0h2r8sXRPu+yJ1x87luVZAkbgsgPiMvzg5qiZYuRio972/aUKHEjtQcYPSWwXAuy2fxyhut26QJFyEh968EB6FalEu6/kQeoQ/aScxz5fawiR12Cp03Jm1rq+Kl1WRb4uCgyw2Ap9OLKeAYy5pBACBnHwRtvhlz2lRGAF8mfEUxZ+M3H96UVpBUew/EDcgrBoQuaHOPgQs3WOHNRZHcpdIcquyf76KEPW/yASrZcG3BsypwNIerYtZzF1Vpooydr9AcJ2pF2L5+quL6cNf+CjjyydJo/oDXPJp6mi0vLPIJ6/xHpqklEaSAYJi3Wamhkaz/Yg7189mjfmKVuW4hBXgGQd8PCEXaYgRCAsfLvEkhfgmskWCeeaLNElUn41JTMl87iDDm77b0XAGpzKHAWnhLFz7xubARPqbuAuDmo5sgAV1CrPf46n5is3G64MMKXFzXYsfSwch4BX7/jaZFwJxxSNB1Iu1oafnLRfF7AiIvrO7dymz812KHG0uZ0nd8whclNOba7WS6LzxFLZPD5T0i4gktUWNAVPWZ9fgxLX2n9O5xMVSN06VMf2+MBd35f11SxaPzdtitcSmSSU2mL3npSszeI6u7TbOpJ7uCZJaTQuO6fVBaP6GTE4WQ2dnw8ns/pigt6uKZEe1umNQrsiqqYJ/khDXrgdjrms55Vs2LnPSKyZJ3pao9ildOaFEP1m+G+yRFFhu8rYntKYIUH+hpohwo2NUhRMeEt64Zt12FjkSLQRylBjNBIGt4Na57NizFG/ryiwoY7TTnAsA0DkTl0TLPhKWumQAdAP8B/gH6A/wH5A/oH7A/4H8g/kD+gfoD/QfmD+wfuD/wfxD+IP5B+vPvD/IflD+of9D+oP/B+IP5B+sP9h+cP7h/8P7g/yH4Q/iH6A/xH5I/pH/I/pD/ofhD+YfqD/Ufmj+0f+j+0P9h+MP4h+kP8x+WP6x/2P6w/+H4w/mH6w/3H54/vH/4/vD/Efgj+Efoj/AfkT+if8T+iP+R+CP5R+qP9B+ZP7J/5P7I/1H4o/hH6Y/yH5U/qn/U/qj/0fij+Ufrj/YfnT+6f/T+6P8x+GP4x+iP8R+TP6Z/zP6Y/7H4Y/nH6o/1H5s/tn/s/tj/cfjj+Mfpj/Mflz+uf9z+uP/x+OP5x+uP9x+fP75//P8Mezg4Fwu+75R7UZMnYrgYvpNoKLvD/zxNQBzTVBZzyRnv5dzcfU0ozC+rAC1UclSta75iYphuZC415RMBMijEOhhSShTteh0QUjQqu6EKBUDU/Qy7fximtOgFtG4ehY/WgYQkMAs3+mm0ZaMi8XcqdzKTp0kdKRSub0hG6g5iyW+TKGcJBZroBwLbSziMjrZV/+DoDGf29iZMiKnJBkfCbDncQH/ijfMasHZ9+0eDAqBb6BD23/nxQMXc1UgzjEEk+JpEZKiIITPx305DOJu/LtTKF77GFthMmfAbtmQw9l1+skXOvsh4fOBlxA41fvgm9DaztmTM9xOGVQ7abeR53wyJO2RthJ0CQDTadc0wo4u3n4P9KhG+gistDa1k4wXhpBkY4oNZeejFE94E0W18o+xtdkLCR5ok+IbL9yhRfJAXgU5okY5lQOyqi5DRf9o9chZWoiZflCBZyMy7jC+FpLFk4i0WVX/NNW2EMON4QiYvEt8Kh4y8ufayhPLhzLKV3ELBF1/xwK52/2vQc+fqfE/T7vPrvpLUaQd5zpwtWHSCWuccYIXcnqDXKyWguEyMWfSpnzdbkpL87PSyZxtwjEnRFPUEPV5SwW7u5sS47VoCDQZ5FFrmbzX4Xs08k1B3YwVTdGkcbVksXo1TAxRrVnaZGKyI8dBpTX41wWuTvv1v1lGMUe9TaRl+yLA2S6apsYYrqgNmBZq9Z4ujDwmuFjRW/ktG+quFzRuJsd6tYENWMA2WIF1D1Sab0tUgvrZmax8dgOGFbzzXlgqsnRRnJVSPgEVfmXRJ8HwNExxWIfP+87vlNTfStU/OSO+FH4vkYapCJtbYIITL+eA/dlyMI4z9QBKVR4ReKKwQyH4ne1HnQdRmC1Ck8c/EDT/7JVALwT0VhdiSWzSmB76KE3vGnfPpKeAJH1P/o3FwaZ6O0n2Kei9IrmfiXEDcHyDhQfHyaPzspSwTtYLW0VdLBkJFtB0/R9ugT8mmp0wnzgryfhFmnNBicQXYhFdYjot9yCz8X2FgZbkgySeTGumCmKSq0ZTp5Ah4usHNQppM4nfFWPGVbkliYEev3sRZojKfmknbG/BTSmE3YQ27jEKCtTyyWdsAQMHU1Q1vQpxgu7l/KQzGsKJOo+xHBJkZLJU7Yma0GflPlVtH8ChN0OzIy5T4TCOL5aExeFSSNUw9ML6Nxd2k2pBLaze5NlPmJHVwAdbyizVlwpvATEVpwUjfd7b4g8TqRVhnzl4wR3BZcX2ZDUzHNzVw42r4CMFDpiQF2Du1bmeZL1LYLgMua4OHi4POIoPstVfyN343awZi/TtB2U4uWPj6qb58KYaptqddFlkZL0hDUletV4B6YIN4KYbo8Ee8Bk/HA6Ft8sZFcAFHhrj4k7ix6e6jOD9jWDKqB6/9hOtaFM/uKOzDx755KZzG4vyck4QJvtzcgxY4tmCADI1XmLS408TrN6sQz6RFOd34E2eUtLIh2VUv/h3/tE5jg3KqpSen4mwcBOTtYp2B+MXCUB5gj/mwUG1du0jXjx01hHqvlfYkcIyPHBaDn7J94/hLb3XfDrXNW8CVs+EXksi7tr4qeEBaUOy3FYYhvq4ucCkecJjQLJKry0JvETDu6/r9SvWK4LXjwSoNrck6AAtxi85C6TnCRQsDh/dwKR9wosME0fHUtOJPY8M8/zu0KRvzJCO4kT1yaCS4jQ9jGxKC0NGKf71ts8vCPZypHPMEO0gaoVYD79e5LWQ6lv+SXKUu2DgozABGqsv/V4puQITbLLm3qANruj2a7AyDIaiWyfWdXMIHGm/+JXq5/sYNlw6zgTAXqvr12i+ZgxWrvUJGKq4d5+s1LWikEO6BbbHR24LRLl+bsQLM37lwMsWeV4IdDs7rT8SXjRnhZlgZn+TnqM0OVoQx45v3O9okzsy+caq1EkjTD+voPvRX1zVeIoGv1/39/R7bdYAjDJFP8iER4Jt3Le6H9i8nY+UKowwD/7TQC/FN3WRHrQnoSKiFkk/FaAX5LCRro/UL4KaU8la1VyoYFeZJoO+Ci6fSFRmVKwiT7ODnfOA9hQPASHFIzoRjmoQQyYj56qawiPWwzVshMRG0LXMLsdEtdSU/JhddBa2g67iyJ3hFZwrrK0hCBhJ4xodQpL1k5+ZhLZOX/l0xIIIe3BVdDuswH/F6IHc0ykfoX3b/0fbfrNGPu9zHacOtVYkdpPoeOwzcyLtmh34kBB6dno/2VyldStNdz13bkkEO2BfhSXd5UkzLIQaYW1Sm9iSgM7iiByCHXRIohXlIxkvUdKqTH57g3ViBD7yXQn/Gx4Jyk/ElAIbQB6jPcT9ITWuF+MErhmb26t6xlS7OKb4vH9whZ7TT3PiC7r2nXSMJ/WJGsTN+x5dw2xFlDmgHL1PfSK/4NfMZJoO1MFS+EynGkOkGPJUMRmNHY1/2HK4Ecpj+N7HN1x47JaYd66qxbnzeXm0c7fjLHIheVKWjhP0FtxEdeeU9c6duuW98J/BPaEMLshKqeOb+RA1rugu9g67tax7yweNG/kxUvk3JFEzbcAZ0lzn7NEn2fYUYegQV2+LM7iIB1IN86ET6WYeOLDnl/AeydkVOaq4wsQh4RRRbasbaGNNEHiHqFtw17jeDeehJpt527XQzout1TcKDrspok0CuLHaCg6KCdhHGyX40pFD/kJCebCrgVs75DhNWS+7iCis53Pesm+hp0rXKU8KVNHCYK8Z/m6zdo/z1DWpwcsC+pqo6hzNjSa4M7C8HFlzWiYypfHhAkDnoYnxJL8a0oiz3X6mC0tDJqUh55BMH6ddA/9wJIjhDLKVCom1tS9tNVYecjFPWj11NyICInK9K6Qia2iuh4bvRQ6bX5umCh7sAchTmOxm2qWzGw3ydygZ9M+f3c7FO0a/HMpPxSdkfbEDON+JJTdwUiIwdUhhlpx6eLJkQoqC6OON3nrWcQZ/RSl2NW/oZs7i/EypYUlZH7JfMf0yqKnO1g860Yb4AwUyEc0x4SsPW1/gJu4vngASLCTDvCtTbE8qFFbLULSzrcDkfcA5szR5E5LOMKh5/5q3UvHMqzTLUKTr6AT+fAWoIHAM2lU6Zli3W0MJp8WVnCltgOpUi+udCAJPFJ+T+2aaqqpXzqXqo8ivTVqsl+1MTw4X0kUFD+/WZgbuFiO0oy50SvVxEsq3mnuXJ9NJDqS+7288Nwil6MQ9/mpTUQf5sTecurn+/XRW+BkAkuGpAPl03OSVvfxiYUdWh014EGkkjNnaXzS6GsddWq351ibvMCZViaF1SB2NoqctjVPCbl4EWd4EKEtuSL+nRfe4HzxlFXVWuuTzUSMk=
*/