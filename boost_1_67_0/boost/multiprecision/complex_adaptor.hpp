///////////////////////////////////////////////////////////////////////////////
//  Copyright 2018 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MULTIPRECISION_COMPLEX_ADAPTOR_HPP
#define BOOST_MULTIPRECISION_COMPLEX_ADAPTOR_HPP

#include <boost/multiprecision/number.hpp>
#include <boost/cstdint.hpp>
#include <boost/multiprecision/detail/digits.hpp>
#include <boost/functional/hash_fwd.hpp>
#include <boost/type_traits/is_complex.hpp>
#include <cmath>
#include <algorithm>
#include <complex>

namespace boost {
namespace multiprecision {
namespace backends {

template <class Backend>
struct complex_adaptor
{
 protected:
   Backend m_real, m_imag;

 public:
   Backend& real_data()
   {
      return m_real;
   }
   const Backend& real_data() const
   {
      return m_real;
   }
   Backend& imag_data()
   {
      return m_imag;
   }
   const Backend& imag_data() const
   {
      return m_imag;
   }

   typedef typename Backend::signed_types   signed_types;
   typedef typename Backend::unsigned_types unsigned_types;
   typedef typename Backend::float_types    float_types;
   typedef typename Backend::exponent_type  exponent_type;

   complex_adaptor() {}
   complex_adaptor(const complex_adaptor& o) : m_real(o.real_data()), m_imag(o.imag_data()) {}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   complex_adaptor(complex_adaptor&& o) : m_real(std::move(o.real_data())), m_imag(std::move(o.imag_data()))
   {}
#endif
   complex_adaptor(const Backend& val)
       : m_real(val)
   {}

   complex_adaptor(const std::complex<float>& val)
   {
      m_real = (long double)val.real();
      m_imag = (long double)val.imag();
   }
   complex_adaptor(const std::complex<double>& val)
   {
      m_real = (long double)val.real();
      m_imag = (long double)val.imag();
   }
   complex_adaptor(const std::complex<long double>& val)
   {
      m_real = val.real();
      m_imag = val.imag();
   }

   complex_adaptor& operator=(const complex_adaptor& o)
   {
      m_real = o.real_data();
      m_imag = o.imag_data();
      return *this;
   }
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
   complex_adaptor& operator=(complex_adaptor&& o) BOOST_NOEXCEPT
   {
      m_real = std::move(o.real_data());
      m_imag = std::move(o.imag_data());
      return *this;
   }
#endif
   template <class V>
   complex_adaptor& operator=(const V& v)
   {
      typedef typename mpl::front<unsigned_types>::type ui_type;
      m_real = v;
      m_imag = ui_type(0u);
      return *this;
   }
   template <class T>
   complex_adaptor& operator=(const std::complex<T>& val)
   {
      m_real = (long double)val.real();
      m_imag = (long double)val.imag();
      return *this;
   }
   complex_adaptor& operator=(const char* s)
   {
      typedef typename mpl::front<unsigned_types>::type ui_type;
      ui_type                                           zero = 0u;

      using default_ops::eval_fpclassify;

      if (s && (*s == '('))
      {
         std::string part;
         const char* p = ++s;
         while (*p && (*p != ',') && (*p != ')'))
            ++p;
         part.assign(s, p);
         if (part.size())
            real_data() = part.c_str();
         else
            real_data() = zero;
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
            imag_data() = part.c_str();
         else
            imag_data() = zero;

         if (eval_fpclassify(imag_data()) == (int)FP_NAN)
         {
            real_data() = imag_data();
         }
      }
      else
      {
         real_data() = s;
         imag_data() = zero;
      }
      return *this;
   }

   int compare(const complex_adaptor& o) const
   {
      // They are either equal or not:
      return (m_real.compare(o.real_data()) == 0) && (m_imag.compare(o.imag_data()) == 0) ? 0 : 1;
   }
   template <class T>
   int compare(const T& val) const
   {
      using default_ops::eval_is_zero;
      return (m_real.compare(val) == 0) && eval_is_zero(m_imag) ? 0 : 1;
   }
   void swap(complex_adaptor& o)
   {
      real_data().swap(o.real_data());
      imag_data().swap(o.imag_data());
   }
   std::string str(std::streamsize dig, std::ios_base::fmtflags f) const
   {
      using default_ops::eval_is_zero;
      if (eval_is_zero(imag_data()))
         return m_real.str(dig, f);
      return "(" + m_real.str(dig, f) + "," + m_imag.str(dig, f) + ")";
   }
   void negate()
   {
      m_real.negate();
      m_imag.negate();
   }
};

template <class Backend, class T>
inline typename enable_if<is_arithmetic<T>, bool>::type eval_eq(const complex_adaptor<Backend>& a, const T& b) BOOST_NOEXCEPT
{
   return a.compare(b) == 0;
}

template <class Backend>
inline void eval_add(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& o)
{
   eval_add(result.real_data(), o.real_data());
   eval_add(result.imag_data(), o.imag_data());
}
template <class Backend>
inline void eval_subtract(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& o)
{
   eval_subtract(result.real_data(), o.real_data());
   eval_subtract(result.imag_data(), o.imag_data());
}
template <class Backend>
inline void eval_multiply(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& o)
{
   Backend t1, t2, t3;
   eval_multiply(t1, result.real_data(), o.real_data());
   eval_multiply(t2, result.imag_data(), o.imag_data());
   eval_subtract(t3, t1, t2);
   eval_multiply(t1, result.real_data(), o.imag_data());
   eval_multiply(t2, result.imag_data(), o.real_data());
   eval_add(t1, t2);
   result.real_data() = BOOST_MP_MOVE(t3);
   result.imag_data() = BOOST_MP_MOVE(t1);
}
template <class Backend>
inline void eval_divide(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& z)
{
   // (a+bi) / (c + di)
   using default_ops::eval_add;
   using default_ops::eval_divide;
   using default_ops::eval_fabs;
   using default_ops::eval_is_zero;
   using default_ops::eval_multiply;
   using default_ops::eval_subtract;
   Backend t1, t2;

   if (eval_is_zero(z.imag_data()))
   {
      eval_divide(result.real_data(), z.real_data());
      eval_divide(result.imag_data(), z.real_data());
      return;
   }

   eval_fabs(t1, z.real_data());
   eval_fabs(t2, z.imag_data());
   if (t1.compare(t2) < 0)
   {
      eval_divide(t1, z.real_data(), z.imag_data()); // t1 = c/d
      eval_multiply(t2, z.real_data(), t1);
      eval_add(t2, z.imag_data()); // denom = c * (c/d) + d
      Backend t_real(result.real_data());
      // real = (a * (c/d) + b) / (denom)
      eval_multiply(result.real_data(), t1);
      eval_add(result.real_data(), result.imag_data());
      eval_divide(result.real_data(), t2);
      // imag = (b * c/d - a) / denom
      eval_multiply(result.imag_data(), t1);
      eval_subtract(result.imag_data(), t_real);
      eval_divide(result.imag_data(), t2);
   }
   else
   {
      eval_divide(t1, z.imag_data(), z.real_data()); // t1 = d/c
      eval_multiply(t2, z.imag_data(), t1);
      eval_add(t2, z.real_data()); // denom = d * d/c + c

      Backend r_t(result.real_data());
      Backend i_t(result.imag_data());

      // real = (b * d/c + a) / denom
      eval_multiply(result.real_data(), result.imag_data(), t1);
      eval_add(result.real_data(), r_t);
      eval_divide(result.real_data(), t2);
      // imag = (-a * d/c + b) / denom
      eval_multiply(result.imag_data(), r_t, t1);
      result.imag_data().negate();
      eval_add(result.imag_data(), i_t);
      eval_divide(result.imag_data(), t2);
   }
}
template <class Backend, class T>
inline typename boost::disable_if_c<boost::is_same<complex_adaptor<Backend>, T>::value>::type eval_add(complex_adaptor<Backend>& result, const T& scalar)
{
   using default_ops::eval_add;
   eval_add(result.real_data(), scalar);
}
template <class Backend, class T>
inline typename boost::disable_if_c<boost::is_same<complex_adaptor<Backend>, T>::value>::type eval_subtract(complex_adaptor<Backend>& result, const T& scalar)
{
   using default_ops::eval_subtract;
   eval_subtract(result.real_data(), scalar);
}
template <class Backend, class T>
inline typename boost::disable_if_c<boost::is_same<complex_adaptor<Backend>, T>::value>::type eval_multiply(complex_adaptor<Backend>& result, const T& scalar)
{
   using default_ops::eval_multiply;
   eval_multiply(result.real_data(), scalar);
   eval_multiply(result.imag_data(), scalar);
}
template <class Backend, class T>
inline typename boost::disable_if_c<boost::is_same<complex_adaptor<Backend>, T>::value>::type eval_divide(complex_adaptor<Backend>& result, const T& scalar)
{
   using default_ops::eval_divide;
   eval_divide(result.real_data(), scalar);
   eval_divide(result.imag_data(), scalar);
}
// Optimised 3 arg versions:
template <class Backend, class T>
inline typename boost::disable_if_c<boost::is_same<complex_adaptor<Backend>, T>::value>::type eval_add(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& a, const T& scalar)
{
   using default_ops::eval_add;
   eval_add(result.real_data(), a.real_data(), scalar);
   result.imag_data() = a.imag_data();
}
template <class Backend, class T>
inline typename boost::disable_if_c<boost::is_same<complex_adaptor<Backend>, T>::value>::type eval_subtract(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& a, const T& scalar)
{
   using default_ops::eval_subtract;
   eval_subtract(result.real_data(), a.real_data(), scalar);
   result.imag_data() = a.imag_data();
}
template <class Backend, class T>
inline typename boost::disable_if_c<boost::is_same<complex_adaptor<Backend>, T>::value>::type eval_multiply(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& a, const T& scalar)
{
   using default_ops::eval_multiply;
   eval_multiply(result.real_data(), a.real_data(), scalar);
   eval_multiply(result.imag_data(), a.imag_data(), scalar);
}
template <class Backend, class T>
inline typename boost::disable_if_c<boost::is_same<complex_adaptor<Backend>, T>::value>::type eval_divide(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& a, const T& scalar)
{
   using default_ops::eval_divide;
   eval_divide(result.real_data(), a.real_data(), scalar);
   eval_divide(result.imag_data(), a.imag_data(), scalar);
}

template <class Backend>
inline bool eval_is_zero(const complex_adaptor<Backend>& val) BOOST_NOEXCEPT
{
   using default_ops::eval_is_zero;
   return eval_is_zero(val.real_data()) && eval_is_zero(val.imag_data());
}
template <class Backend>
inline int eval_get_sign(const complex_adaptor<Backend>&)
{
   BOOST_STATIC_ASSERT_MSG(sizeof(Backend) == UINT_MAX, "Complex numbers have no sign bit."); // designed to always fail
   return 0;
}

template <class Result, class Backend>
inline typename disable_if_c<boost::is_complex<Result>::value>::type eval_convert_to(Result* result, const complex_adaptor<Backend>& val)
{
   using default_ops::eval_convert_to;
   using default_ops::eval_is_zero;
   if (!eval_is_zero(val.imag_data()))
   {
      BOOST_THROW_EXCEPTION(std::runtime_error("Could not convert imaginary number to scalar."));
   }
   eval_convert_to(result, val.real_data());
}

template <class Backend, class T>
inline void assign_components(complex_adaptor<Backend>& result, const T& a, const T& b)
{
   result.real_data() = a;
   result.imag_data() = b;
}

//
// Native non-member operations:
//
template <class Backend>
inline void eval_sqrt(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& val)
{
   // Use the following:
   // sqrt(z) = (s, zi / 2s)       for zr >= 0
   //           (|zi| / 2s, +-s)   for zr <  0
   // where s = sqrt{ [ |zr| + sqrt(zr^2 + zi^2) ] / 2 },
   // and the +- sign is the same as the sign of zi.
   using default_ops::eval_abs;
   using default_ops::eval_add;
   using default_ops::eval_divide;
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;

   if (eval_is_zero(val.imag_data()) && (eval_get_sign(val.real_data()) >= 0))
   {
      static const typename mpl::front<typename Backend::unsigned_types>::type zero = 0u;
      eval_sqrt(result.real_data(), val.real_data());
      result.imag_data() = zero;
      return;
   }

   const bool __my_real_part_is_neg(eval_get_sign(val.real_data()) < 0);

   Backend __my_real_part_fabs(val.real_data());
   if (__my_real_part_is_neg)
      __my_real_part_fabs.negate();

   Backend t, __my_sqrt_part;
   eval_abs(__my_sqrt_part, val);
   eval_add(__my_sqrt_part, __my_real_part_fabs);
   eval_ldexp(t, __my_sqrt_part, -1);
   eval_sqrt(__my_sqrt_part, t);

   if (__my_real_part_is_neg == false)
   {
      eval_ldexp(t, __my_sqrt_part, 1);
      eval_divide(result.imag_data(), val.imag_data(), t);
      result.real_data() = __my_sqrt_part;
   }
   else
   {
      const bool __my_imag_part_is_neg(eval_get_sign(val.imag_data()) < 0);

      Backend __my_imag_part_fabs(val.imag_data());
      if (__my_imag_part_is_neg)
         __my_imag_part_fabs.negate();

      eval_ldexp(t, __my_sqrt_part, 1);
      eval_divide(result.real_data(), __my_imag_part_fabs, t);
      if (__my_imag_part_is_neg)
         __my_sqrt_part.negate();
      result.imag_data() = __my_sqrt_part;
   }
}

template <class Backend>
inline void eval_abs(Backend& result, const complex_adaptor<Backend>& val)
{
   Backend t1, t2;
   eval_multiply(t1, val.real_data(), val.real_data());
   eval_multiply(t2, val.imag_data(), val.imag_data());
   eval_add(t1, t2);
   eval_sqrt(result, t1);
}

template <class Backend>
inline void eval_pow(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& b, const complex_adaptor<Backend>& e)
{
   using default_ops::eval_acos;
   using default_ops::eval_cos;
   using default_ops::eval_exp;
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_multiply;
   using default_ops::eval_sin;

   if (eval_is_zero(e))
   {
      typename mpl::front<typename Backend::unsigned_types>::type one(1);
      result = one;
      return;
   }
   else if (eval_is_zero(b))
   {
      if (eval_is_zero(e.real_data()))
      {
         Backend n          = std::numeric_limits<number<Backend> >::quiet_NaN().backend();
         result.real_data() = n;
         result.imag_data() = n;
      }
      else if (eval_get_sign(e.real_data()) < 0)
      {
         Backend n          = std::numeric_limits<number<Backend> >::infinity().backend();
         result.real_data() = n;
         typename mpl::front<typename Backend::unsigned_types>::type zero(0);
         if (eval_is_zero(e.imag_data()))
            result.imag_data() = zero;
         else
            result.imag_data() = n;
      }
      else
      {
         typename mpl::front<typename Backend::unsigned_types>::type zero(0);
         result = zero;
      }
      return;
   }
   complex_adaptor<Backend> t;
   eval_log(t, b);
   eval_multiply(t, e);
   eval_exp(result, t);
}

template <class Backend>
inline void eval_exp(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_cos;
   using default_ops::eval_exp;
   using default_ops::eval_is_zero;
   using default_ops::eval_multiply;
   using default_ops::eval_sin;

   if (eval_is_zero(arg.imag_data()))
   {
      eval_exp(result.real_data(), arg.real_data());
      typename mpl::front<typename Backend::unsigned_types>::type zero(0);
      result.imag_data() = zero;
      return;
   }
   eval_cos(result.real_data(), arg.imag_data());
   eval_sin(result.imag_data(), arg.imag_data());
   Backend e;
   eval_exp(e, arg.real_data());
   if (eval_is_zero(result.real_data()))
      eval_multiply(result.imag_data(), e);
   else if (eval_is_zero(result.imag_data()))
      eval_multiply(result.real_data(), e);
   else
      eval_multiply(result, e);
}

template <class Backend>
inline void eval_log(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_add;
   using default_ops::eval_atan2;
   using default_ops::eval_get_sign;
   using default_ops::eval_is_zero;
   using default_ops::eval_log;
   using default_ops::eval_multiply;

   if (eval_is_zero(arg.imag_data()) && (eval_get_sign(arg.real_data()) >= 0))
   {
      eval_log(result.real_data(), arg.real_data());
      typename mpl::front<typename Backend::unsigned_types>::type zero(0);
      result.imag_data() = zero;
      return;
   }

   Backend t1, t2;
   eval_multiply(t1, arg.real_data(), arg.real_data());
   eval_multiply(t2, arg.imag_data(), arg.imag_data());
   eval_add(t1, t2);
   eval_log(t2, t1);
   eval_ldexp(result.real_data(), t2, -1);
   eval_atan2(result.imag_data(), arg.imag_data(), arg.real_data());
}

template <class Backend>
inline void eval_log10(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_divide;
   using default_ops::eval_log;

   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;

   Backend ten;
   ten = ui_type(10);
   Backend l_ten;
   eval_log(l_ten, ten);
   eval_log(result, arg);
   eval_divide(result, l_ten);
}

template <class Backend>
inline void eval_sin(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_cos;
   using default_ops::eval_cosh;
   using default_ops::eval_sin;
   using default_ops::eval_sinh;

   Backend t1, t2;
   eval_sin(t1, arg.real_data());
   eval_cosh(t2, arg.imag_data());
   eval_multiply(result.real_data(), t1, t2);

   eval_cos(t1, arg.real_data());
   eval_sinh(t2, arg.imag_data());
   eval_multiply(result.imag_data(), t1, t2);
}

template <class Backend>
inline void eval_cos(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_cos;
   using default_ops::eval_cosh;
   using default_ops::eval_sin;
   using default_ops::eval_sinh;

   Backend t1, t2;
   eval_cos(t1, arg.real_data());
   eval_cosh(t2, arg.imag_data());
   eval_multiply(result.real_data(), t1, t2);

   eval_sin(t1, arg.real_data());
   eval_sinh(t2, arg.imag_data());
   eval_multiply(result.imag_data(), t1, t2);
   result.imag_data().negate();
}

template <class Backend>
inline void eval_tan(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   complex_adaptor<Backend> c;
   eval_cos(c, arg);
   eval_sin(result, arg);
   eval_divide(result, c);
}

template <class Backend>
inline void eval_asin(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_add;
   using default_ops::eval_multiply;

   if (eval_is_zero(arg))
   {
      result = arg;
      return;
   }

   complex_adaptor<Backend> t1, t2;
   assign_components(t1, arg.imag_data(), arg.real_data());
   t1.real_data().negate();
   eval_asinh(t2, t1);

   assign_components(result, t2.imag_data(), t2.real_data());
   result.imag_data().negate();
}

template <class Backend>
inline void eval_acos(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;

   using default_ops::eval_asin;

   Backend half_pi, t1;
   t1 = static_cast<ui_type>(1u);
   eval_asin(half_pi, t1);
   eval_asin(result, arg);
   result.negate();
   eval_add(result.real_data(), half_pi);
}

template <class Backend>
inline void eval_atan(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   ui_type                                                             one = (ui_type)1u;

   using default_ops::eval_add;
   using default_ops::eval_is_zero;
   using default_ops::eval_log;
   using default_ops::eval_subtract;

   complex_adaptor<Backend> __my_z_times_i, t1, t2, t3;
   assign_components(__my_z_times_i, arg.imag_data(), arg.real_data());
   __my_z_times_i.real_data().negate();

   eval_add(t1, __my_z_times_i, one);
   eval_log(t2, t1);
   eval_subtract(t1, one, __my_z_times_i);
   eval_log(t3, t1);
   eval_subtract(t1, t3, t2);

   eval_ldexp(result.real_data(), t1.imag_data(), -1);
   eval_ldexp(result.imag_data(), t1.real_data(), -1);
   if (!eval_is_zero(result.real_data()))
      result.real_data().negate();
}

template <class Backend>
inline void eval_sinh(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_cos;
   using default_ops::eval_cosh;
   using default_ops::eval_sin;
   using default_ops::eval_sinh;

   Backend t1, t2;
   eval_cos(t1, arg.imag_data());
   eval_sinh(t2, arg.real_data());
   eval_multiply(result.real_data(), t1, t2);

   eval_cosh(t1, arg.real_data());
   eval_sin(t2, arg.imag_data());
   eval_multiply(result.imag_data(), t1, t2);
}

template <class Backend>
inline void eval_cosh(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_cos;
   using default_ops::eval_cosh;
   using default_ops::eval_sin;
   using default_ops::eval_sinh;

   Backend t1, t2;
   eval_cos(t1, arg.imag_data());
   eval_cosh(t2, arg.real_data());
   eval_multiply(result.real_data(), t1, t2);

   eval_sin(t1, arg.imag_data());
   eval_sinh(t2, arg.real_data());
   eval_multiply(result.imag_data(), t1, t2);
}

template <class Backend>
inline void eval_tanh(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_divide;
   complex_adaptor<Backend> s, c;
   eval_sinh(s, arg);
   eval_cosh(c, arg);
   eval_divide(result, s, c);
}

template <class Backend>
inline void eval_asinh(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   ui_type                                                             one = (ui_type)1u;

   using default_ops::eval_add;
   using default_ops::eval_log;
   using default_ops::eval_multiply;

   complex_adaptor<Backend> t1, t2;
   eval_multiply(t1, arg, arg);
   eval_add(t1, one);
   eval_sqrt(t2, t1);
   eval_add(t2, arg);
   eval_log(result, t2);
}

template <class Backend>
inline void eval_acosh(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   ui_type                                                             one = (ui_type)1u;

   using default_ops::eval_add;
   using default_ops::eval_divide;
   using default_ops::eval_log;
   using default_ops::eval_multiply;
   using default_ops::eval_subtract;

   complex_adaptor<Backend> __my_zp(arg);
   eval_add(__my_zp.real_data(), one);
   complex_adaptor<Backend> __my_zm(arg);
   eval_subtract(__my_zm.real_data(), one);

   complex_adaptor<Backend> t1, t2;
   eval_divide(t1, __my_zm, __my_zp);
   eval_sqrt(t2, t1);
   eval_multiply(t2, __my_zp);
   eval_add(t2, arg);
   eval_log(result, t2);
}

template <class Backend>
inline void eval_atanh(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   ui_type                                                             one = (ui_type)1u;

   using default_ops::eval_add;
   using default_ops::eval_divide;
   using default_ops::eval_log;
   using default_ops::eval_multiply;
   using default_ops::eval_subtract;

   complex_adaptor<Backend> t1, t2, t3;
   eval_add(t1, arg, one);
   eval_log(t2, t1);
   eval_subtract(t1, one, arg);
   eval_log(t3, t1);
   eval_subtract(t2, t3);

   eval_ldexp(result.real_data(), t2.real_data(), -1);
   eval_ldexp(result.imag_data(), t2.imag_data(), -1);
}

template <class Backend>
inline void eval_conj(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   result = arg;
   result.imag_data().negate();
}

template <class Backend>
inline void eval_proj(complex_adaptor<Backend>& result, const complex_adaptor<Backend>& arg)
{
   using default_ops::eval_get_sign;

   typedef typename mpl::front<typename Backend::unsigned_types>::type ui_type;
   ui_type                                                             zero = (ui_type)0u;

   int c1 = eval_fpclassify(arg.real_data());
   int c2 = eval_fpclassify(arg.imag_data());
   if (c1 == FP_INFINITE)
   {
      result.real_data() = arg.real_data();
      if (eval_get_sign(result.real_data()) < 0)
         result.real_data().negate();
      result.imag_data() = zero;
      if (eval_get_sign(arg.imag_data()) < 0)
         result.imag_data().negate();
   }
   else if (c2 == FP_INFINITE)
   {
      result.real_data() = arg.imag_data();
      if (eval_get_sign(result.real_data()) < 0)
         result.real_data().negate();
      result.imag_data() = zero;
      if (eval_get_sign(arg.imag_data()) < 0)
         result.imag_data().negate();
   }
   else
      result = arg;
}

template <class Backend>
inline void eval_real(Backend& result, const complex_adaptor<Backend>& arg)
{
   result = arg.real_data();
}
template <class Backend>
inline void eval_imag(Backend& result, const complex_adaptor<Backend>& arg)
{
   result = arg.imag_data();
}

template <class Backend, class T>
inline void eval_set_imag(complex_adaptor<Backend>& result, const T& arg)
{
   result.imag_data() = arg;
}

template <class Backend, class T>
inline void eval_set_real(complex_adaptor<Backend>& result, const T& arg)
{
   result.real_data() = arg;
}

template <class Backend>
inline std::size_t hash_value(const complex_adaptor<Backend>& val)
{
   std::size_t result  = hash_value(val.real_data());
   std::size_t result2 = hash_value(val.imag_data());
   boost::hash_combine(result, result2);
   return result;
}

} // namespace backends

using boost::multiprecision::backends::complex_adaptor;

template <class Backend>
struct number_category<complex_adaptor<Backend> > : public boost::mpl::int_<boost::multiprecision::number_kind_complex>
{};

template <class Backend, expression_template_option ExpressionTemplates>
struct component_type<number<complex_adaptor<Backend>, ExpressionTemplates> >
{
   typedef number<Backend, ExpressionTemplates> type;
};

template <class Backend, expression_template_option ExpressionTemplates>
struct complex_result_from_scalar<number<Backend, ExpressionTemplates> >
{
   typedef number<complex_adaptor<Backend>, ExpressionTemplates> type;
};

}

} // namespace boost::multiprecision

#endif

/* complex_adaptor.hpp
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
*/