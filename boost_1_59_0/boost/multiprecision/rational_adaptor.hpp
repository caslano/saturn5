///////////////////////////////////////////////////////////////
//  Copyright 2020 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MULTIPRECISION_RATIONAL_ADAPTOR_HPP
#define BOOST_MULTIPRECISION_RATIONAL_ADAPTOR_HPP

#include <boost/multiprecision/number.hpp>
#include <boost/multiprecision/detail/hash.hpp>
#include <boost/multiprecision/detail/float128_functions.hpp>
#include <boost/multiprecision/detail/no_exceptions_support.hpp>

namespace boost {
namespace multiprecision {
namespace backends {

template <class Backend>
struct rational_adaptor
{
   //
   // Each backend need to declare 3 type lists which declare the types
   // with which this can interoperate.  These lists must at least contain
   // the widest type in each category - so "long long" must be the final
   // type in the signed_types list for example.  Any narrower types if not
   // present in the list will get promoted to the next wider type that is
   // in the list whenever mixed arithmetic involving that type is encountered.
   //
   typedef typename Backend::signed_types    signed_types;
   typedef typename Backend::unsigned_types  unsigned_types;
   typedef typename Backend::float_types     float_types;

   typedef typename std::tuple_element<0, unsigned_types>::type ui_type;

   static Backend get_one()
   {
      Backend t;
      t = static_cast<ui_type>(1);
      return t;
   }
   static Backend get_zero()
   {
      Backend t;
      t = static_cast<ui_type>(0);
      return t;
   }

   static const Backend& one()
   {
      static const Backend result(get_one());
      return result;
   }
   static const Backend& zero()
   {
      static const Backend result(get_zero());
      return result;
   }

   void normalize()
   {
      using default_ops::eval_gcd;
      using default_ops::eval_eq;
      using default_ops::eval_divide;

      Backend g, t;
      eval_gcd(g, m_num, m_denom);
      if (!eval_eq(g, one()))
      {
         eval_divide(t, m_num, g);
         m_num.swap(t);
         eval_divide(t, m_denom, g);
         m_denom = std::move(t);
      }
   }

   // We must have a default constructor:
   rational_adaptor()
      : m_num(zero()), m_denom(one()) {}

   rational_adaptor(const rational_adaptor& o) : m_num(o.m_num), m_denom(o.m_denom) {}
   rational_adaptor(rational_adaptor&& o) = default;

   // Optional constructors, we can make this type slightly more efficient
   // by providing constructors from any type we can handle natively.
   // These will also cause number<> to be implicitly constructible
   // from these types unless we make such constructors explicit.
   //
   template <class Arithmetic>
   rational_adaptor(const Arithmetic& val, typename std::enable_if<std::is_constructible<Backend, Arithmetic>::value && !std::is_floating_point<Arithmetic>::value>::type const* = nullptr)
      : m_num(val), m_denom(one()) {}

   //
   // Pass-through 2-arg construction of components:
   //
   template <class T, class U>
   rational_adaptor(const T& a, const U& b, typename std::enable_if<std::is_constructible<Backend, T const&>::value && std::is_constructible<Backend, U const&>::value>::type const* = nullptr)
      : m_num(a), m_denom(b) 
   {
      normalize();
   }
   template <class T, class U>
   rational_adaptor(T&& a, const U& b, typename std::enable_if<std::is_constructible<Backend, T>::value && std::is_constructible<Backend, U>::value>::type const* = nullptr)
      : m_num(static_cast<T&&>(a)), m_denom(b) 
   {
      normalize();
   }
   template <class T, class U>
   rational_adaptor(T&& a, U&& b, typename std::enable_if<std::is_constructible<Backend, T>::value && std::is_constructible<Backend, U>::value>::type const* = nullptr)
      : m_num(static_cast<T&&>(a)), m_denom(static_cast<U&&>(b)) 
   {
      normalize();
   }
   template <class T, class U>
   rational_adaptor(const T& a, U&& b, typename std::enable_if<std::is_constructible<Backend, T>::value && std::is_constructible<Backend, U>::value>::type const* = nullptr)
      : m_num(a), m_denom(static_cast<U&&>(b)) 
   {
      normalize();
   }
   //
   // In the absense of converting constructors, operator= takes the strain.
   // In addition to the usual suspects, there must be one operator= for each type
   // listed in signed_types, unsigned_types, and float_types plus a string constructor.
   //
   rational_adaptor& operator=(const rational_adaptor& o) = default;
   rational_adaptor& operator=(rational_adaptor&& o) = default;
   template <class Arithmetic>
   inline typename std::enable_if<!std::is_floating_point<Arithmetic>::value, rational_adaptor&>::type operator=(const Arithmetic& i)
   {
      m_num = i;
      m_denom = one();
      return *this;
   }
   rational_adaptor& operator=(const char* s)
   {
      using default_ops::eval_eq;

      std::string                        s1;
      multiprecision::number<Backend>    v1, v2;
      char                               c;
      bool                               have_hex = false;
      const char* p = s; // saved for later

      while ((0 != (c = *s)) && (c == 'x' || c == 'X' || c == '-' || c == '+' || (c >= '0' && c <= '9') || (have_hex && (c >= 'a' && c <= 'f')) || (have_hex && (c >= 'A' && c <= 'F'))))
      {
         if (c == 'x' || c == 'X')
            have_hex = true;
         s1.append(1, c);
         ++s;
      }
      v1.assign(s1);
      s1.erase();
      if (c == '/')
      {
         ++s;
         while ((0 != (c = *s)) && (c == 'x' || c == 'X' || c == '-' || c == '+' || (c >= '0' && c <= '9') || (have_hex && (c >= 'a' && c <= 'f')) || (have_hex && (c >= 'A' && c <= 'F'))))
         {
            if (c == 'x' || c == 'X')
               have_hex = true;
            s1.append(1, c);
            ++s;
         }
         v2.assign(s1);
      }
      else
         v2 = 1;
      if (*s)
      {
         BOOST_MP_THROW_EXCEPTION(std::runtime_error(std::string("Could not parse the string \"") + p + std::string("\" as a valid rational number.")));
      }
      multiprecision::number<Backend> gcd;
      eval_gcd(gcd.backend(), v1.backend(), v2.backend());
      if (!eval_eq(gcd.backend(), one()))
      {
         v1 /= gcd;
         v2 /= gcd;
      }
      num() = std::move(std::move(v1).backend());
      denom() = std::move(std::move(v2).backend());
      return *this;
   }
   template <class Float>
   typename std::enable_if<std::is_floating_point<Float>::value, rational_adaptor&>::type operator=(Float i)
   {
      using default_ops::eval_eq;
      BOOST_MP_FLOAT128_USING using std::floor; using std::frexp; using std::ldexp;

      int   e;
      Float f = frexp(i, &e);
#ifdef BOOST_HAS_FLOAT128
      f = ldexp(f, std::is_same<float128_type, Float>::value ? 113 : std::numeric_limits<Float>::digits);
      e -= std::is_same<float128_type, Float>::value ? 113 : std::numeric_limits<Float>::digits;
#else
      f = ldexp(f, std::numeric_limits<Float>::digits);
      e -= std::numeric_limits<Float>::digits;
#endif
      number<Backend> num(f);
      number<Backend> denom(1u);
      if (e > 0)
      {
         num <<= e;
      }
      else if (e < 0)
      {
         denom <<= -e;
      }
      number<Backend> gcd;
      eval_gcd(gcd.backend(), num.backend(), denom.backend());
      if (!eval_eq(gcd.backend(), one()))
      {
         num /= gcd;
         denom /= gcd;
      }
      this->num() = std::move(std::move(num).backend());
      this->denom() = std::move(std::move(denom).backend());
      return *this;
   }

   void swap(rational_adaptor& o)
   {
      m_num.swap(o.m_num);
      m_denom.swap(o.m_denom);
   }
   std::string str(std::streamsize digits, std::ios_base::fmtflags f) const
   {
      using default_ops::eval_eq;
      //
      // We format the string ourselves so we can match what GMP's mpq type does:
      //
      std::string result = num().str(digits, f);
      if (!eval_eq(denom(), one()))
      {
         result.append(1, '/');
         result.append(denom().str(digits, f));
      }
      return result;
   }
   void negate()
   {
      m_num.negate();
   }
   int compare(const rational_adaptor& o) const
   {
      std::ptrdiff_t s1 = eval_get_sign(*this);
      std::ptrdiff_t s2 = eval_get_sign(o);
      if (s1 != s2)
      {
         return s1 < s2 ? -1 : 1;
      }
      else if (s1 == 0)
         return 0; // both zero.

      bool neg = false;
      if (s1 >= 0)
      {
         s1 = eval_msb(num()) + eval_msb(o.denom());
         s2 = eval_msb(o.num()) + eval_msb(denom());
      }
      else
      {
         Backend t(num());
         t.negate();
         s1 = eval_msb(t) + eval_msb(o.denom());
         t = o.num();
         t.negate();
         s2 = eval_msb(t) + eval_msb(denom());
         neg = true;
      }
      s1 -= s2;
      if (s1 < -1)
         return neg ? 1 : -1;
      else if (s1 > 1)
         return neg ? -1 : 1;

      Backend t1, t2;
      eval_multiply(t1, num(), o.denom());
      eval_multiply(t2, o.num(), denom());
      return t1.compare(t2);
   }
   //
   // Comparison with arithmetic types, default just constructs a temporary:
   //
   template <class A>
   typename std::enable_if<boost::multiprecision::detail::is_arithmetic<A>::value, int>::type compare(A i) const
   {
      rational_adaptor t;
      t = i;  //  Note: construct directly from i if supported.
      return compare(t);
   }

   Backend& num() { return m_num; }
   const Backend& num()const { return m_num; }
   Backend& denom() { return m_denom; }
   const Backend& denom()const { return m_denom; }

   #ifndef BOOST_MP_STANDALONE
   template <class Archive>
   void serialize(Archive& ar, const std::integral_constant<bool, true>&)
   {
      // Saving
      number<Backend> n(num()), d(denom());
      ar& boost::make_nvp("numerator", n);
      ar& boost::make_nvp("denominator", d);
   }
   template <class Archive>
   void serialize(Archive& ar, const std::integral_constant<bool, false>&)
   {
      // Loading
      number<Backend> n, d;
      ar& boost::make_nvp("numerator", n);
      ar& boost::make_nvp("denominator", d);
      num() = n.backend();
      denom() = d.backend();
   }
   template <class Archive>
   void serialize(Archive& ar, const unsigned int /*version*/)
   {
      using tag = typename Archive::is_saving;
      using saving_tag = std::integral_constant<bool, tag::value>;
      serialize(ar, saving_tag());
   }
   #endif // BOOST_MP_STANDALONE
   
 private:
   Backend m_num, m_denom;
};

//
// Helpers:
//
template <class T>
inline constexpr typename std::enable_if<std::numeric_limits<T>::is_specialized && !std::numeric_limits<T>::is_signed, bool>::type
is_minus_one(const T&)
{
   return false;
}
template <class T>
inline constexpr typename std::enable_if<!std::numeric_limits<T>::is_specialized || std::numeric_limits<T>::is_signed, bool>::type
is_minus_one(const T& val)
{
   return val == -1;
}

//
// Required non-members:
//
template <class Backend> 
inline void eval_add(rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   eval_add_subtract_imp(a, a, b, true);
}
template <class Backend> 
inline void eval_subtract(rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   eval_add_subtract_imp(a, a, b, false);
}

template <class Backend> 
inline void eval_multiply(rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   eval_multiply_imp(a, a, b.num(), b.denom());
}

template <class Backend> 
void eval_divide(rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   using default_ops::eval_divide;
   rational_adaptor<Backend> t;
   eval_divide(t, a, b);
   a = std::move(t);
}
//
// Conversions:
//
template <class R, class IntBackend>
inline typename std::enable_if<number_category<R>::value == number_kind_floating_point>::type eval_convert_to(R* result, const rational_adaptor<IntBackend>& backend)
{
   //
   // The generic conversion is as good as anything we can write here:
   //
   ::boost::multiprecision::detail::generic_convert_rational_to_float(*result, backend);
}

template <class R, class IntBackend>
inline typename std::enable_if<(number_category<R>::value != number_kind_integer) && (number_category<R>::value != number_kind_floating_point) && !std::is_enum<R>::value>::type eval_convert_to(R* result, const rational_adaptor<IntBackend>& backend)
{
   using default_ops::eval_convert_to;
   R d;
   eval_convert_to(result, backend.num());
   eval_convert_to(&d, backend.denom());
   *result /= d;
}

template <class R, class Backend>
inline typename std::enable_if<number_category<R>::value == number_kind_integer>::type eval_convert_to(R* result, const rational_adaptor<Backend>& backend)
{
   using default_ops::eval_divide;
   using default_ops::eval_convert_to;
   Backend t;
   eval_divide(t, backend.num(), backend.denom());
   eval_convert_to(result, t);
}

//
// Hashing support, not strictly required, but it is used in our tests:
//
template <class Backend>
inline std::size_t hash_value(const rational_adaptor<Backend>& arg)
{
   std::size_t result = hash_value(arg.num());
   std::size_t result2 = hash_value(arg.denom());
   boost::multiprecision::detail::hash_combine(result, result2);
   return result;
}
//
// assign_components:
//
template <class Backend>
void assign_components(rational_adaptor<Backend>& result, Backend const& a, Backend const& b)
{
   using default_ops::eval_gcd;
   using default_ops::eval_divide;
   using default_ops::eval_eq;

   Backend g;
   eval_gcd(g, a, b);
   if (eval_eq(g, rational_adaptor<Backend>::one()))
   {
      result.num() = a;
      result.denom() = b;
   }
   else
   {
      eval_divide(result.num(), a, g);
      eval_divide(result.denom(), b, g);
   }
}
//
// Again for arithmetic types, overload for whatever arithmetic types are directly supported:
//
template <class Backend, class Arithmetic1, class Arithmetic2>
inline void assign_components(rational_adaptor<Backend>& result, const Arithmetic1& a, const Arithmetic2& b)
{
   using default_ops::eval_gcd;
   using default_ops::eval_divide;
   using default_ops::eval_eq;

   Backend g;
   result.num()   = a;
   eval_gcd(g, result.num(), b);
   if (eval_eq(g, rational_adaptor<Backend>::one()))
   {
      result.denom() = b;
   }
   else
   {
      eval_divide(result.num(), g);
      eval_divide(result.denom(), b, g);
   }
}
//
// Optional comparison operators:
//
template <class Backend>
inline bool eval_is_zero(const rational_adaptor<Backend>& arg)
{
   using default_ops::eval_is_zero;
   return eval_is_zero(arg.num());
}

template <class Backend>
inline int eval_get_sign(const rational_adaptor<Backend>& arg)
{
   using default_ops::eval_get_sign;
   return eval_get_sign(arg.num());
}

template <class Backend>
inline bool eval_eq(const rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   using default_ops::eval_eq;
   return eval_eq(a.num(), b.num()) && eval_eq(a.denom(), b.denom());
}

template <class Backend, class Arithmetic>
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value&& std::is_integral<Arithmetic>::value, bool>::type 
   eval_eq(const rational_adaptor<Backend>& a, Arithmetic b)
{
   using default_ops::eval_eq;
   return eval_eq(a.denom(), rational_adaptor<Backend>::one()) && eval_eq(a.num(), b);
}

template <class Backend, class Arithmetic>
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value&& std::is_integral<Arithmetic>::value, bool>::type 
   eval_eq(Arithmetic b, const rational_adaptor<Backend>& a)
{
   using default_ops::eval_eq;
   return eval_eq(a.denom(), rational_adaptor<Backend>::one()) && eval_eq(a.num(), b);
}

//
// Arithmetic operations, starting with addition:
//
template <class Backend, class Arithmetic> 
void eval_add_subtract_imp(rational_adaptor<Backend>& result, const Arithmetic& arg, bool isaddition)
{
   using default_ops::eval_multiply;
   using default_ops::eval_divide;
   using default_ops::eval_add;
   using default_ops::eval_gcd;
   Backend t;
   eval_multiply(t, result.denom(), arg);
   if (isaddition)
      eval_add(result.num(), t);
   else
      eval_subtract(result.num(), t);
   //
   // There is no need to re-normalize here, we have 
   // (a + bm) / b
   // and gcd(a + bm, b) = gcd(a, b) = 1
   //
   /*
   eval_gcd(t, result.num(), result.denom());
   if (!eval_eq(t, rational_adaptor<Backend>::one()) != 0)
   {
      Backend t2;
      eval_divide(t2, result.num(), t);
      t2.swap(result.num());
      eval_divide(t2, result.denom(), t);
      t2.swap(result.denom());
   }
   */
}

template <class Backend, class Arithmetic> 
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && (std::is_integral<Arithmetic>::value || std::is_same<Arithmetic, Backend>::value)>::type
   eval_add(rational_adaptor<Backend>& result, const Arithmetic& arg)
{
   eval_add_subtract_imp(result, arg, true);
}

template <class Backend, class Arithmetic> 
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && (std::is_integral<Arithmetic>::value || std::is_same<Arithmetic, Backend>::value)>::type
   eval_subtract(rational_adaptor<Backend>& result, const Arithmetic& arg)
{
   eval_add_subtract_imp(result, arg, false);
}

template <class Backend>
void eval_add_subtract_imp(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b, bool isaddition)
{
   using default_ops::eval_eq;
   using default_ops::eval_multiply;
   using default_ops::eval_divide;
   using default_ops::eval_add;
   using default_ops::eval_subtract;
   //
   // Let  a = an/ad
   //      b = bn/bd
   //      g = gcd(ad, bd)
   // result = rn/rd
   //
   // Then:
   // rn = an * (bd/g) + bn * (ad/g)
   // rd = ad * (bd/g)
   //    = (ad/g) * (bd/g) * g
   //
   // And the whole thing can then be rescaled by
   //      gcd(rn, g)
   //
   Backend gcd, t1, t2, t3, t4;
   //
   // Begin by getting the gcd of the 2 denominators:
   //
   eval_gcd(gcd, a.denom(), b.denom());
   //
   // Do we have gcd > 1:
   //
   if (!eval_eq(gcd, rational_adaptor<Backend>::one()))
   {
      //
      // Scale the denominators by gcd, and put the results in t1 and t2:
      //
      eval_divide(t1, b.denom(), gcd);
      eval_divide(t2, a.denom(), gcd);
      //
      // multiply the numerators by the scale denominators and put the results in t3, t4:
      //
      eval_multiply(t3, a.num(), t1);
      eval_multiply(t4, b.num(), t2);
      //
      // Add them up:
      //
      if (isaddition)
         eval_add(t3, t4);
      else
         eval_subtract(t3, t4);
      //
      // Get the gcd of gcd and our numerator (t3):
      //
      eval_gcd(t4, t3, gcd);
      if (eval_eq(t4, rational_adaptor<Backend>::one()))
      {
         result.num() = t3;
         eval_multiply(result.denom(), t1, a.denom());
      }
      else
      {
         //
         // Uncommon case where gcd is not 1, divide the numerator
         // and the denominator terms by the new gcd.  Note we perform division
         // on the existing gcd value as this is the smallest of the 3 denominator
         // terms we'll be multiplying together, so there's a good chance it's a
         // single limb value already:
         //
         eval_divide(result.num(), t3, t4);
         eval_divide(t3, gcd, t4);
         eval_multiply(t4, t1, t2);
         eval_multiply(result.denom(), t4, t3);
      }
   }
   else
   {
      //
      // Most common case (approx 60%) where gcd is one:
      //
      eval_multiply(t1, a.num(), b.denom());
      eval_multiply(t2, a.denom(), b.num());
      if (isaddition)
         eval_add(result.num(), t1, t2);
      else
         eval_subtract(result.num(), t1, t2);
      eval_multiply(result.denom(), a.denom(), b.denom());
   }
}


template <class Backend>
inline void eval_add(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   eval_add_subtract_imp(result, a, b, true);
}
template <class Backend>
inline void eval_subtract(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   eval_add_subtract_imp(result, a, b, false);
}

template <class Backend, class Arithmetic>
void eval_add_subtract_imp(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const Arithmetic& b, bool isaddition)
{
   using default_ops::eval_add;
   using default_ops::eval_subtract;
   using default_ops::eval_multiply;

   if (&result == &a)
      return eval_add_subtract_imp(result, b, isaddition);

   eval_multiply(result.num(), a.denom(), b);
   if (isaddition)
      eval_add(result.num(), a.num());
   else
      BOOST_IF_CONSTEXPR(std::numeric_limits<Backend>::is_signed == false)
   {
      Backend t;
      eval_subtract(t, a.num(), result.num());
      result.num() = std::move(t);
   }
   else
   {
      eval_subtract(result.num(), a.num());
      result.negate();
   }
   result.denom() = a.denom();
   //
   // There is no need to re-normalize here, we have 
   // (a + bm) / b
   // and gcd(a + bm, b) = gcd(a, b) = 1
   //
}
template <class Backend, class Arithmetic>
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && (std::is_integral<Arithmetic>::value || std::is_same<Arithmetic, Backend>::value)>::type
   eval_add(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const Arithmetic& b)
{
   eval_add_subtract_imp(result, a, b, true);
}
template <class Backend, class Arithmetic>
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && (std::is_integral<Arithmetic>::value || std::is_same<Arithmetic, Backend>::value)>::type
   eval_subtract(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const Arithmetic& b)
{
   eval_add_subtract_imp(result, a, b, false);
}

//
// Multiplication:
//
template <class Backend> 
void eval_multiply_imp(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const Backend& b_num, const Backend& b_denom)
{
   using default_ops::eval_multiply;
   using default_ops::eval_divide;
   using default_ops::eval_gcd;
   using default_ops::eval_get_sign;
   using default_ops::eval_eq;

   Backend gcd_left, gcd_right, t1, t2;
   eval_gcd(gcd_left, a.num(), b_denom);
   eval_gcd(gcd_right, b_num, a.denom());
   //
   // Unit gcd's are the most likely case:
   //
   bool b_left = eval_eq(gcd_left, rational_adaptor<Backend>::one());
   bool b_right = eval_eq(gcd_right, rational_adaptor<Backend>::one());

   if (b_left && b_right)
   {
      eval_multiply(result.num(), a.num(), b_num);
      eval_multiply(result.denom(), a.denom(), b_denom);
   }
   else if (b_left)
   {
      eval_divide(t2, b_num, gcd_right);
      eval_multiply(result.num(), a.num(), t2);
      eval_divide(t1, a.denom(), gcd_right);
      eval_multiply(result.denom(), t1, b_denom);
   }
   else if (b_right)
   {
      eval_divide(t1, a.num(), gcd_left);
      eval_multiply(result.num(), t1, b_num);
      eval_divide(t2, b_denom, gcd_left);
      eval_multiply(result.denom(), a.denom(), t2);
   }
   else
   {
      eval_divide(t1, a.num(), gcd_left);
      eval_divide(t2, b_num, gcd_right);
      eval_multiply(result.num(), t1, t2);
      eval_divide(t1, a.denom(), gcd_right);
      eval_divide(t2, b_denom, gcd_left);
      eval_multiply(result.denom(), t1, t2);
   }
   //
   // We may have b_denom negative if this is actually division, if so just correct things now:
   //
   if (eval_get_sign(b_denom) < 0)
   {
      result.num().negate();
      result.denom().negate();
   }
}

template <class Backend> 
void eval_multiply(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   using default_ops::eval_multiply;

   if (&a == &b)
   {
      // squaring, gcd's are 1:
      eval_multiply(result.num(), a.num(), b.num());
      eval_multiply(result.denom(), a.denom(), b.denom());
      return;
   }
   eval_multiply_imp(result, a, b.num(), b.denom());
}

template <class Backend, class Arithmetic> 
void eval_multiply_imp(Backend& result_num, Backend& result_denom, Arithmetic arg)
{
   if (arg == 0)
   {
      result_num = rational_adaptor<Backend>::zero();
      result_denom = rational_adaptor<Backend>::one();
      return;
   }
   else if (arg == 1)
      return;

   using default_ops::eval_multiply;
   using default_ops::eval_divide;
   using default_ops::eval_gcd;
   using default_ops::eval_convert_to;

   Backend gcd, t;
   Arithmetic integer_gcd;
   eval_gcd(gcd, result_denom, arg);
   eval_convert_to(&integer_gcd, gcd);
   arg /= integer_gcd;
   if (boost::multiprecision::detail::unsigned_abs(arg) > 1)
   {
      eval_multiply(t, result_num, arg);
      result_num = std::move(t);
   }
   else if (is_minus_one(arg))
      result_num.negate();
   if (integer_gcd > 1)
   {
      eval_divide(t, result_denom, integer_gcd);
      result_denom = std::move(t);
   }
}
template <class Backend> 
void eval_multiply_imp(Backend& result_num, Backend& result_denom, Backend arg)
{
   using default_ops::eval_multiply;
   using default_ops::eval_divide;
   using default_ops::eval_gcd;
   using default_ops::eval_convert_to;
   using default_ops::eval_is_zero;
   using default_ops::eval_eq;
   using default_ops::eval_get_sign;

   if (eval_is_zero(arg))
   {
      result_num = rational_adaptor<Backend>::zero();
      result_denom = rational_adaptor<Backend>::one();
      return;
   }
   else if (eval_eq(arg, rational_adaptor<Backend>::one()))
      return;

   Backend gcd, t;
   eval_gcd(gcd, result_denom, arg);
   if (!eval_eq(gcd, rational_adaptor<Backend>::one()))
   {
      eval_divide(t, arg, gcd);
      arg = t;
   }
   else
      t = arg;
   if (eval_get_sign(arg) < 0)
      t.negate();

   if (!eval_eq(t, rational_adaptor<Backend>::one()))
   {
      eval_multiply(t, result_num, arg);
      result_num = std::move(t);
   }
   else if (eval_get_sign(arg) < 0)
      result_num.negate();
   if (!eval_eq(gcd, rational_adaptor<Backend>::one()))
   {
      eval_divide(t, result_denom, gcd);
      result_denom = std::move(t);
   }
}

template <class Backend, class Arithmetic> 
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && (std::is_integral<Arithmetic>::value || std::is_same<Arithmetic, Backend>::value)>::type
   eval_multiply(rational_adaptor<Backend>& result, const Arithmetic& arg)
{
   eval_multiply_imp(result.num(), result.denom(), arg);
}

template <class Backend, class Arithmetic> 
typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && std::is_integral<Arithmetic>::value>::type
   eval_multiply_imp(rational_adaptor<Backend>& result, const Backend& a_num, const Backend& a_denom, Arithmetic b)
{
   if (b == 0)
   {
      result.num() = rational_adaptor<Backend>::zero();
      result.denom() = rational_adaptor<Backend>::one();
      return;
   }
   else if (b == 1)
   {
      result.num() = a_num;
      result.denom() = a_denom;
      return;
   }

   using default_ops::eval_multiply;
   using default_ops::eval_divide;
   using default_ops::eval_gcd;
   using default_ops::eval_convert_to;

   Backend gcd;
   Arithmetic integer_gcd;
   eval_gcd(gcd, a_denom, b);
   eval_convert_to(&integer_gcd, gcd);
   b /= integer_gcd;
   if (boost::multiprecision::detail::unsigned_abs(b) > 1)
      eval_multiply(result.num(), a_num, b);
   else if (is_minus_one(b))
   {
      result.num() = a_num;
      result.num().negate();
   }
   else
      result.num() = a_num;
   if (integer_gcd > 1)
      eval_divide(result.denom(), a_denom, integer_gcd);
   else
      result.denom() = a_denom;
}
template <class Backend> 
inline void eval_multiply_imp(rational_adaptor<Backend>& result, const Backend& a_num, const Backend& a_denom, const Backend& b)
{
   result.num() = a_num;
   result.denom() = a_denom;
   eval_multiply_imp(result.num(), result.denom(), b);
}

template <class Backend, class Arithmetic> 
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && (std::is_integral<Arithmetic>::value || std::is_same<Arithmetic, Backend>::value)>::type
   eval_multiply(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const Arithmetic& b)
{
   if (&result == &a)
      return eval_multiply(result, b);

   eval_multiply_imp(result, a.num(), a.denom(), b);
}

template <class Backend, class Arithmetic> 
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && (std::is_integral<Arithmetic>::value || std::is_same<Arithmetic, Backend>::value)>::type
   eval_multiply(rational_adaptor<Backend>& result, const Arithmetic& b, const rational_adaptor<Backend>& a)
{
   return eval_multiply(result, a, b);
}

//
// Division:
//
template <class Backend>
inline void eval_divide(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, const rational_adaptor<Backend>& b)
{
   using default_ops::eval_multiply;
   using default_ops::eval_get_sign;

   if (eval_get_sign(b.num()) == 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
      return;
   }
   if (&a == &b)
   {
      // Huh? Really?
      result.num() = result.denom() = rational_adaptor<Backend>::one();
      return;
   }
   if (&result == &b)
   {
      rational_adaptor<Backend> t(b);
      return eval_divide(result, a, t);
   }
   eval_multiply_imp(result, a, b.denom(), b.num());
}

template <class Backend, class Arithmetic> 
inline typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && (std::is_integral<Arithmetic>::value || std::is_same<Arithmetic, Backend>::value)>::type
   eval_divide(rational_adaptor<Backend>& result, const Arithmetic& b, const rational_adaptor<Backend>& a)
{
   using default_ops::eval_get_sign;

   if (eval_get_sign(a.num()) == 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
      return;
   }
   if (&a == &result)
   {
      eval_multiply_imp(result.denom(), result.num(), b);
      result.num().swap(result.denom());
   }
   else
      eval_multiply_imp(result, a.denom(), a.num(), b);

   if (eval_get_sign(result.denom()) < 0)
   {
      result.num().negate();
      result.denom().negate();
   }
}

template <class Backend, class Arithmetic>
typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && std::is_integral<Arithmetic>::value>::type
eval_divide(rational_adaptor<Backend>& result, Arithmetic arg)
{
   if (arg == 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
      return;
   }
   else if (arg == 1)
      return;
   else if (is_minus_one(arg))
   {
      result.negate();
      return;
   }
   if (eval_get_sign(result) == 0)
   {
      return;
   }


   using default_ops::eval_multiply;
   using default_ops::eval_gcd;
   using default_ops::eval_convert_to;
   using default_ops::eval_divide;

   Backend gcd, t;
   Arithmetic integer_gcd;
   eval_gcd(gcd, result.num(), arg);
   eval_convert_to(&integer_gcd, gcd);
   arg /= integer_gcd;

   eval_multiply(t, result.denom(), boost::multiprecision::detail::unsigned_abs(arg));
   result.denom() = std::move(t);
   if (arg < 0)
   {
      result.num().negate();
   }
   if (integer_gcd > 1)
   {
      eval_divide(t, result.num(), integer_gcd);
      result.num() = std::move(t);
   }
}
template <class Backend>
void eval_divide(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, Backend arg)
{
   using default_ops::eval_multiply;
   using default_ops::eval_gcd;
   using default_ops::eval_convert_to;
   using default_ops::eval_divide;
   using default_ops::eval_is_zero;
   using default_ops::eval_eq;
   using default_ops::eval_get_sign;

   if (eval_is_zero(arg))
   {
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
      return;
   }
   else if (eval_eq(a, rational_adaptor<Backend>::one()) || (eval_get_sign(a) == 0))
   {
      if (&result != &a)
         result = a;
      return;
   }

   Backend gcd, u_arg, t;
   eval_gcd(gcd, a.num(), arg);
   bool has_unit_gcd = eval_eq(gcd, rational_adaptor<Backend>::one());
   if (!has_unit_gcd)
   {
      eval_divide(u_arg, arg, gcd);
      arg = u_arg;
   }
   else
      u_arg = arg;
   if (eval_get_sign(u_arg) < 0)
      u_arg.negate();

   eval_multiply(t, a.denom(), u_arg);
   result.denom() = std::move(t);
   
   if (!has_unit_gcd)
   {
      eval_divide(t, a.num(), gcd);
      result.num() = std::move(t);
   }
   else if (&result != &a)
      result.num() = a.num();

   if (eval_get_sign(arg) < 0)
   {
      result.num().negate();
   }
}
template <class Backend>
void eval_divide(rational_adaptor<Backend>& result, Backend arg)
{
   eval_divide(result, result, arg);
}

template <class Backend, class Arithmetic>
typename std::enable_if<std::is_convertible<Arithmetic, Backend>::value && std::is_integral<Arithmetic>::value>::type
   eval_divide(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& a, Arithmetic arg)
{
   if (&result == &a)
      return eval_divide(result, arg);
   if (arg == 0)
   {
      BOOST_MP_THROW_EXCEPTION(std::overflow_error("Integer division by zero"));
      return;
   }
   else if (arg == 1)
   {
      result = a;
      return;
   }
   else if (is_minus_one(arg))
   {
      result = a;
      result.num().negate();
      return;
   }

   if (eval_get_sign(a) == 0)
   {
      result = a;
      return;
   }

   using default_ops::eval_multiply;
   using default_ops::eval_divide;
   using default_ops::eval_gcd;
   using default_ops::eval_convert_to;

   Backend gcd;
   Arithmetic integer_gcd;
   eval_gcd(gcd, a.num(), arg);
   eval_convert_to(&integer_gcd, gcd);
   arg /= integer_gcd;
   eval_multiply(result.denom(), a.denom(), boost::multiprecision::detail::unsigned_abs(arg));

   if (integer_gcd > 1)
   {
      eval_divide(result.num(), a.num(), integer_gcd);
   }
   else
      result.num() = a.num();
   if (arg < 0)
   {
      result.num().negate();
   }
}

//
// Increment and decrement:
//
template <class Backend> 
inline void eval_increment(rational_adaptor<Backend>& arg)
{
   using default_ops::eval_add;
   eval_add(arg.num(), arg.denom());
}
template <class Backend> 
inline void eval_decrement(rational_adaptor<Backend>& arg)
{
   using default_ops::eval_subtract;
   eval_subtract(arg.num(), arg.denom());
}

//
// abs:
//
template <class Backend> 
inline void eval_abs(rational_adaptor<Backend>& result, const rational_adaptor<Backend>& arg)
{
   using default_ops::eval_abs;
   eval_abs(result.num(), arg.num());
   result.denom() = arg.denom();
}

} // namespace backends

//
// Import the backend into this namespace:
//
using boost::multiprecision::backends::rational_adaptor;
//
// Define a category for this number type, one of:
// 
//    number_kind_integer
//    number_kind_floating_point
//    number_kind_rational
//    number_kind_fixed_point
//    number_kind_complex
//
template<class Backend>
struct number_category<rational_adaptor<Backend> > : public std::integral_constant<int, number_kind_rational>
{};

template <class IntBackend>
struct expression_template_default<backends::rational_adaptor<IntBackend> > : public expression_template_default<IntBackend>
{};

template <class Backend, expression_template_option ExpressionTemplates>
struct component_type<number<rational_adaptor<Backend>, ExpressionTemplates> >
{
   typedef number<Backend, ExpressionTemplates> type;
};

template <class IntBackend, expression_template_option ET>
inline number<IntBackend, ET> numerator(const number<rational_adaptor<IntBackend>, ET>& val)
{
   return val.backend().num();
}
template <class IntBackend, expression_template_option ET>
inline number<IntBackend, ET> denominator(const number<rational_adaptor<IntBackend>, ET>& val)
{
   return val.backend().denom();
}

template <class Backend>
struct is_unsigned_number<rational_adaptor<Backend> > : public is_unsigned_number<Backend>
{};


}} // namespace boost::multiprecision

namespace std {

   template <class IntBackend, boost::multiprecision::expression_template_option ExpressionTemplates>
   class numeric_limits<boost::multiprecision::number<boost::multiprecision::rational_adaptor<IntBackend>, ExpressionTemplates> > : public std::numeric_limits<boost::multiprecision::number<IntBackend, ExpressionTemplates> >
   {
      using base_type = std::numeric_limits<boost::multiprecision::number<IntBackend> >;
      using number_type = boost::multiprecision::number<boost::multiprecision::rational_adaptor<IntBackend> >;

   public:
      static constexpr bool is_integer = false;
      static constexpr bool is_exact = true;
      static constexpr      number_type(min)() { return (base_type::min)(); }
      static constexpr      number_type(max)() { return (base_type::max)(); }
      static constexpr number_type lowest() { return -(max)(); }
      static constexpr number_type epsilon() { return base_type::epsilon(); }
      static constexpr number_type round_error() { return epsilon() / 2; }
      static constexpr number_type infinity() { return base_type::infinity(); }
      static constexpr number_type quiet_NaN() { return base_type::quiet_NaN(); }
      static constexpr number_type signaling_NaN() { return base_type::signaling_NaN(); }
      static constexpr number_type denorm_min() { return base_type::denorm_min(); }
   };

   template <class IntBackend, boost::multiprecision::expression_template_option ExpressionTemplates>
   constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::rational_adaptor<IntBackend>, ExpressionTemplates> >::is_integer;
   template <class IntBackend, boost::multiprecision::expression_template_option ExpressionTemplates>
   constexpr bool numeric_limits<boost::multiprecision::number<boost::multiprecision::rational_adaptor<IntBackend>, ExpressionTemplates> >::is_exact;

} // namespace std

#endif

/* rational_adaptor.hpp
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
*/