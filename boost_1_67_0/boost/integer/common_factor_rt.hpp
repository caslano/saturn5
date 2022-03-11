//  (C) Copyright Jeremy William Murphy 2016.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_INTEGER_COMMON_FACTOR_RT_HPP
#define BOOST_INTEGER_COMMON_FACTOR_RT_HPP

#include <boost/assert.hpp>
#include <boost/core/enable_if.hpp>

#include <boost/config.hpp>  // for BOOST_NESTED_TEMPLATE, etc.
#include <boost/limits.hpp>  // for std::numeric_limits
#include <climits>           // for CHAR_MIN
#include <boost/detail/workaround.hpp>
#include <iterator>
#include <algorithm>
#include <limits>
#ifndef BOOST_NO_CXX11_HDR_TYPE_TRAITS
#include <type_traits>
#endif
#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL
#include <functional>
#endif

#if ((defined(BOOST_MSVC) && (BOOST_MSVC >= 1600)) || (defined(__clang__) && defined(__c2__)) || (defined(BOOST_INTEL) && defined(_MSC_VER))) && (defined(_M_IX86) || defined(_M_X64))
#include <intrin.h>
#endif

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4127 4244)  // Conditional expression is constant
#endif

#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS) && !defined(BOOST_NO_CXX11_NOEXCEPT)
#define BOOST_GCD_NOEXCEPT(T) noexcept(std::is_arithmetic<T>::value)
#else
#define BOOST_GCD_NOEXCEPT(T)
#endif

namespace boost {

   template <class I>
   class rational;

   namespace integer {

      namespace gcd_detail{

         //
         // some helper functions which really should be constexpr already, but sadly aren't:
         //
#ifndef BOOST_NO_CXX14_CONSTEXPR
         template <class T>
         inline constexpr T constexpr_min(T const& a, T const& b) BOOST_GCD_NOEXCEPT(T)
         {
            return a < b ? a : b;
         }
         template <class T>
         inline constexpr auto constexpr_swap(T&a, T& b) BOOST_GCD_NOEXCEPT(T) -> decltype(a.swap(b))
         {
            return a.swap(b);
         }
         template <class T, class U>
         inline constexpr void constexpr_swap(T&a, U& b...) BOOST_GCD_NOEXCEPT(T)
         {
            T t(static_cast<T&&>(a));
            a = static_cast<T&&>(b);
            b = static_cast<T&&>(t);
         }
#else
         template <class T>
         inline T constexpr_min(T const& a, T const& b) BOOST_GCD_NOEXCEPT(T)
         {
            return a < b ? a : b;
         }
         template <class T>
         inline void constexpr_swap(T&a, T& b) BOOST_GCD_NOEXCEPT(T)
         {
            using std::swap;
            swap(a, b);
         }
#endif

      template <class T, bool a =
#ifndef BOOST_NO_CXX11_HDR_TYPE_TRAITS
         std::is_unsigned<T>::value ||
#endif
         (std::numeric_limits<T>::is_specialized && !std::numeric_limits<T>::is_signed)>
      struct gcd_traits_abs_defaults
      {
         inline static BOOST_CXX14_CONSTEXPR const T& abs(const T& val) BOOST_GCD_NOEXCEPT(T) { return val; }
      };
      template <class T>
      struct gcd_traits_abs_defaults<T, false>
      {
         inline static T BOOST_CXX14_CONSTEXPR abs(const T& val) BOOST_GCD_NOEXCEPT(T)
         {
            // This sucks, but std::abs is not constexpr :(
            return val < T(0) ? -val : val;
         }
      };

      enum method_type
      {
         method_euclid = 0,
         method_binary = 1,
         method_mixed = 2
      };

      struct any_convert
      {
         template <class T>
         any_convert(const T&);
      };

      struct unlikely_size
      {
         char buf[9973];
      };

      unlikely_size operator <<= (any_convert, any_convert);
      unlikely_size operator >>= (any_convert, any_convert);

      template <class T>
      struct gcd_traits_defaults : public gcd_traits_abs_defaults<T>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(T& val) BOOST_GCD_NOEXCEPT(T)
         {
            unsigned r = 0;
            while(0 == (val & 1u))
            {
#ifdef _MSC_VER  // VC++ can't handle operator >>= in constexpr code for some reason
               val = val >> 1;
#else
               val >>= 1;
#endif
               ++r;
            }
            return r;
         }
         inline static BOOST_CXX14_CONSTEXPR bool less(const T& a, const T& b) BOOST_GCD_NOEXCEPT(T)
         {
            return a < b;
         }

         static T& get_value();

#ifndef BOOST_NO_SFINAE
         static const bool has_operator_left_shift_equal = sizeof(get_value() <<= 2) != sizeof(unlikely_size);
         static const bool has_operator_right_shift_equal = sizeof(get_value() >>= 2) != sizeof(unlikely_size);
#else
         static const bool has_operator_left_shift_equal = true;
         static const bool has_operator_right_shift_equal = true;
#endif
         static const method_type method = std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_integer && has_operator_left_shift_equal && has_operator_right_shift_equal ? method_mixed : method_euclid;
      };
      //
      // Default gcd_traits just inherits from defaults:
      //
      template <class T>
      struct gcd_traits : public gcd_traits_defaults<T> {};

      //
      // Some platforms have fast bitscan operations, that allow us to implement
      // make_odd much more efficiently, unfortunately we can't use these if we want
      // the functions to be constexpr as the compiler intrinsics aren't constexpr.
      //
#if defined(BOOST_NO_CXX14_CONSTEXPR) && ((defined(BOOST_MSVC) && (BOOST_MSVC >= 1600)) || (defined(__clang__) && defined(__c2__)) || (defined(BOOST_INTEL) && defined(_MSC_VER))) && (defined(_M_IX86) || defined(_M_X64))
#pragma intrinsic(_BitScanForward,)
      template <>
      struct gcd_traits<unsigned long> : public gcd_traits_defaults<unsigned long>
      {
         BOOST_FORCEINLINE static unsigned find_lsb(unsigned long val) BOOST_NOEXCEPT
         {
            unsigned long result;
            _BitScanForward(&result, val);
            return result;
         }
         BOOST_FORCEINLINE static unsigned make_odd(unsigned long& val) BOOST_NOEXCEPT
         {
            unsigned result = find_lsb(val);
            val >>= result;
            return result;
         }
      };

#ifdef _M_X64
#pragma intrinsic(_BitScanForward64)
      template <>
      struct gcd_traits<unsigned __int64> : public gcd_traits_defaults<unsigned __int64>
      {
         BOOST_FORCEINLINE static unsigned find_lsb(unsigned __int64 mask) BOOST_NOEXCEPT
         {
            unsigned long result;
            _BitScanForward64(&result, mask);
            return result;
         }
         BOOST_FORCEINLINE static unsigned make_odd(unsigned __int64& val) BOOST_NOEXCEPT
         {
            unsigned result = find_lsb(val);
            val >>= result;
            return result;
         }
      };
#endif
      //
      // Other integer type are trivial adaptations of the above,
      // this works for signed types too, as by the time these functions
      // are called, all values are > 0.
      //
      template <> struct gcd_traits<long> : public gcd_traits_defaults<long>
      { BOOST_FORCEINLINE static unsigned make_odd(long& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
      template <> struct gcd_traits<unsigned int> : public gcd_traits_defaults<unsigned int>
      { BOOST_FORCEINLINE static unsigned make_odd(unsigned int& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
      template <> struct gcd_traits<int> : public gcd_traits_defaults<int>
      { BOOST_FORCEINLINE static unsigned make_odd(int& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
      template <> struct gcd_traits<unsigned short> : public gcd_traits_defaults<unsigned short>
      { BOOST_FORCEINLINE static unsigned make_odd(unsigned short& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
      template <> struct gcd_traits<short> : public gcd_traits_defaults<short>
      { BOOST_FORCEINLINE static unsigned make_odd(short& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
      template <> struct gcd_traits<unsigned char> : public gcd_traits_defaults<unsigned char>
      { BOOST_FORCEINLINE static unsigned make_odd(unsigned char& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
      template <> struct gcd_traits<signed char> : public gcd_traits_defaults<signed char>
      { BOOST_FORCEINLINE static unsigned make_odd(signed char& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
      template <> struct gcd_traits<char> : public gcd_traits_defaults<char>
      { BOOST_FORCEINLINE static unsigned make_odd(char& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
      template <> struct gcd_traits<wchar_t> : public gcd_traits_defaults<wchar_t>
      { BOOST_FORCEINLINE static unsigned make_odd(wchar_t& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; } };
#endif
#ifdef _M_X64
      template <> struct gcd_traits<__int64> : public gcd_traits_defaults<__int64>
      { BOOST_FORCEINLINE static unsigned make_odd(__int64& val)BOOST_NOEXCEPT{ unsigned result = gcd_traits<unsigned __int64>::find_lsb(val); val >>= result; return result; } };
#endif

#elif defined(BOOST_GCC) || defined(__clang__) || (defined(BOOST_INTEL) && defined(__GNUC__))

      template <>
      struct gcd_traits<unsigned> : public gcd_traits_defaults<unsigned>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned find_lsb(unsigned mask)BOOST_NOEXCEPT
         {
            return __builtin_ctz(mask);
         }
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(unsigned& val)BOOST_NOEXCEPT
         {
            unsigned result = find_lsb(val);
            val >>= result;
            return result;
         }
      };
      template <>
      struct gcd_traits<unsigned long> : public gcd_traits_defaults<unsigned long>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned find_lsb(unsigned long mask)BOOST_NOEXCEPT
         {
            return __builtin_ctzl(mask);
         }
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(unsigned long& val)BOOST_NOEXCEPT
         {
            unsigned result = find_lsb(val);
            val >>= result;
            return result;
         }
      };
      template <>
      struct gcd_traits<boost::ulong_long_type> : public gcd_traits_defaults<boost::ulong_long_type>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned find_lsb(boost::ulong_long_type mask)BOOST_NOEXCEPT
         {
            return __builtin_ctzll(mask);
         }
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(boost::ulong_long_type& val)BOOST_NOEXCEPT
         {
            unsigned result = find_lsb(val);
            val >>= result;
            return result;
         }
      };
      //
      // Other integer type are trivial adaptations of the above,
      // this works for signed types too, as by the time these functions
      // are called, all values are > 0.
      //
      template <> struct gcd_traits<boost::long_long_type> : public gcd_traits_defaults<boost::long_long_type>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(boost::long_long_type& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<boost::ulong_long_type>::find_lsb(val); val >>= result; return result; }
      };
      template <> struct gcd_traits<long> : public gcd_traits_defaults<long>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(long& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; }
      };
      template <> struct gcd_traits<int> : public gcd_traits_defaults<int>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(int& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<unsigned long>::find_lsb(val); val >>= result; return result; }
      };
      template <> struct gcd_traits<unsigned short> : public gcd_traits_defaults<unsigned short>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(unsigned short& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<unsigned>::find_lsb(val); val >>= result; return result; }
      };
      template <> struct gcd_traits<short> : public gcd_traits_defaults<short>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(short& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<unsigned>::find_lsb(val); val >>= result; return result; }
      };
      template <> struct gcd_traits<unsigned char> : public gcd_traits_defaults<unsigned char>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(unsigned char& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<unsigned>::find_lsb(val); val >>= result; return result; }
      };
      template <> struct gcd_traits<signed char> : public gcd_traits_defaults<signed char>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(signed char& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<unsigned>::find_lsb(val); val >>= result; return result; }
      };
      template <> struct gcd_traits<char> : public gcd_traits_defaults<char>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(char& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<unsigned>::find_lsb(val); val >>= result; return result; }
      };
#ifndef BOOST_NO_INTRINSIC_WCHAR_T
      template <> struct gcd_traits<wchar_t> : public gcd_traits_defaults<wchar_t>
      {
         BOOST_FORCEINLINE static BOOST_CXX14_CONSTEXPR unsigned make_odd(wchar_t& val)BOOST_NOEXCEPT { unsigned result = gcd_traits<unsigned>::find_lsb(val); val >>= result; return result; }
      };
#endif
#endif
   //
   // The Mixed Binary Euclid Algorithm
   // Sidi Mohamed Sedjelmaci
   // Electronic Notes in Discrete Mathematics 35 (2009) 169-176
   //
   template <class T>
   BOOST_CXX14_CONSTEXPR T mixed_binary_gcd(T u, T v) BOOST_GCD_NOEXCEPT(T)
   {
      if(gcd_traits<T>::less(u, v))
         constexpr_swap(u, v);

      unsigned shifts = 0;

      if(u == T(0))
         return v;
      if(v == T(0))
         return u;

      shifts = constexpr_min(gcd_traits<T>::make_odd(u), gcd_traits<T>::make_odd(v));

      while(gcd_traits<T>::less(1, v))
      {
         u %= v;
         v -= u;
         if(u == T(0))
            return v << shifts;
         if(v == T(0))
            return u << shifts;
         gcd_traits<T>::make_odd(u);
         gcd_traits<T>::make_odd(v);
         if(gcd_traits<T>::less(u, v))
            constexpr_swap(u, v);
      }
      return (v == 1 ? v : u) << shifts;
   }

    /** Stein gcd (aka 'binary gcd')
     *
     * From Mathematics to Generic Programming, Alexander Stepanov, Daniel Rose
     */
    template <typename SteinDomain>
    BOOST_CXX14_CONSTEXPR SteinDomain Stein_gcd(SteinDomain m, SteinDomain n) BOOST_GCD_NOEXCEPT(SteinDomain)
    {
        BOOST_ASSERT(m >= 0);
        BOOST_ASSERT(n >= 0);
        if (m == SteinDomain(0))
            return n;
        if (n == SteinDomain(0))
            return m;
        // m > 0 && n > 0
        unsigned d_m = gcd_traits<SteinDomain>::make_odd(m);
        unsigned d_n = gcd_traits<SteinDomain>::make_odd(n);
        // odd(m) && odd(n)
        while (m != n)
        {
            if (n > m)
               constexpr_swap(n, m);
            m -= n;
            gcd_traits<SteinDomain>::make_odd(m);
        }
        // m == n
        m <<= constexpr_min(d_m, d_n);
        return m;
    }


    /** Euclidean algorithm
     *
     * From Mathematics to Generic Programming, Alexander Stepanov, Daniel Rose
     *
     */
    template <typename EuclideanDomain>
    inline BOOST_CXX14_CONSTEXPR EuclideanDomain Euclid_gcd(EuclideanDomain a, EuclideanDomain b) BOOST_GCD_NOEXCEPT(EuclideanDomain)
    {
        while (b != EuclideanDomain(0))
        {
            a %= b;
            constexpr_swap(a, b);
        }
        return a;
    }


    template <typename T>
    inline BOOST_CXX14_CONSTEXPR BOOST_DEDUCED_TYPENAME enable_if_c<gcd_traits<T>::method == method_mixed, T>::type
       optimal_gcd_select(T const &a, T const &b) BOOST_GCD_NOEXCEPT(T)
    {
       return gcd_detail::mixed_binary_gcd(a, b);
    }

    template <typename T>
    inline BOOST_CXX14_CONSTEXPR BOOST_DEDUCED_TYPENAME enable_if_c<gcd_traits<T>::method == method_binary, T>::type
       optimal_gcd_select(T const &a, T const &b) BOOST_GCD_NOEXCEPT(T)
    {
       return gcd_detail::Stein_gcd(a, b);
    }

    template <typename T>
    inline BOOST_CXX14_CONSTEXPR BOOST_DEDUCED_TYPENAME enable_if_c<gcd_traits<T>::method == method_euclid, T>::type
       optimal_gcd_select(T const &a, T const &b) BOOST_GCD_NOEXCEPT(T)
    {
       return gcd_detail::Euclid_gcd(a, b);
    }

    template <class T>
    inline BOOST_CXX14_CONSTEXPR T lcm_imp(const T& a, const T& b) BOOST_GCD_NOEXCEPT(T)
    {
       T temp = boost::integer::gcd_detail::optimal_gcd_select(a, b);
#if BOOST_WORKAROUND(BOOST_GCC_VERSION, < 40500)
       return (temp != T(0)) ? T(a / temp * b) : T(0);
#else
       return temp != T(0) ? T(a / temp * b) : T(0);
#endif
    }

} // namespace detail


template <typename Integer>
inline BOOST_CXX14_CONSTEXPR Integer gcd(Integer const &a, Integer const &b) BOOST_GCD_NOEXCEPT(Integer)
{
    if(a == (std::numeric_limits<Integer>::min)())
       return a == static_cast<Integer>(0) ? gcd_detail::gcd_traits<Integer>::abs(b) : boost::integer::gcd(static_cast<Integer>(a % b), b);
    else if (b == (std::numeric_limits<Integer>::min)())
       return b == static_cast<Integer>(0) ? gcd_detail::gcd_traits<Integer>::abs(a) : boost::integer::gcd(a, static_cast<Integer>(b % a));
    return gcd_detail::optimal_gcd_select(static_cast<Integer>(gcd_detail::gcd_traits<Integer>::abs(a)), static_cast<Integer>(gcd_detail::gcd_traits<Integer>::abs(b)));
}

template <typename Integer>
inline BOOST_CXX14_CONSTEXPR Integer lcm(Integer const &a, Integer const &b) BOOST_GCD_NOEXCEPT(Integer)
{
   return gcd_detail::lcm_imp(static_cast<Integer>(gcd_detail::gcd_traits<Integer>::abs(a)), static_cast<Integer>(gcd_detail::gcd_traits<Integer>::abs(b)));
}
#ifndef BOOST_NO_CXX11_VARIADIC_TEMPLATES
//
// This looks slightly odd, but the variadic forms must have 3 or more arguments, and the variadic argument pack may be empty.
// This matters not at all for most compilers, but Oracle C++ selects the wrong overload in the 2-arg case unless we do this.
//
template <typename Integer, typename... Args>
inline BOOST_CXX14_CONSTEXPR Integer gcd(Integer const &a, Integer const &b, const Integer& c, Args const&... args) BOOST_GCD_NOEXCEPT(Integer)
{
   Integer t = gcd(b, c, args...);
   return t == 1 ? 1 : gcd(a, t);
}

template <typename Integer, typename... Args>
inline BOOST_CXX14_CONSTEXPR Integer lcm(Integer const &a, Integer const &b, Integer const& c, Args const&... args) BOOST_GCD_NOEXCEPT(Integer)
{
   return lcm(a, lcm(b, c, args...));
}
#endif
//
// Special handling for rationals:
//
template <typename Integer>
inline typename boost::enable_if_c<std::numeric_limits<Integer>::is_specialized, boost::rational<Integer> >::type gcd(boost::rational<Integer> const &a, boost::rational<Integer> const &b)
{
   return boost::rational<Integer>(static_cast<Integer>(gcd(a.numerator(), b.numerator())), static_cast<Integer>(lcm(a.denominator(), b.denominator())));
}

template <typename Integer>
inline typename boost::enable_if_c<std::numeric_limits<Integer>::is_specialized, boost::rational<Integer> >::type lcm(boost::rational<Integer> const &a, boost::rational<Integer> const &b)
{
   return boost::rational<Integer>(static_cast<Integer>(lcm(a.numerator(), b.numerator())), static_cast<Integer>(gcd(a.denominator(), b.denominator())));
}
/**
 * Knuth, The Art of Computer Programming: Volume 2, Third edition, 1998
 * Chapter 4.5.2, Algorithm C: Greatest common divisor of n integers.
 *
 * Knuth counts down from n to zero but we naturally go from first to last.
 * We also return the termination position because it might be useful to know.
 *
 * Partly by quirk, partly by design, this algorithm is defined for n = 1,
 * because the gcd of {x} is x. It is not defined for n = 0.
 *
 * @tparam  I   Input iterator.
 * @return  The gcd of the range and the iterator position at termination.
 */
template <typename I>
std::pair<typename std::iterator_traits<I>::value_type, I>
gcd_range(I first, I last) BOOST_GCD_NOEXCEPT(I)
{
    BOOST_ASSERT(first != last);
    typedef typename std::iterator_traits<I>::value_type T;

    T d = *first;
    ++first;
    while (d != T(1) && first != last)
    {
        d = gcd(d, *first);
        ++first;
    }
    return std::make_pair(d, first);
}
template <typename I>
std::pair<typename std::iterator_traits<I>::value_type, I>
lcm_range(I first, I last) BOOST_GCD_NOEXCEPT(I)
{
    BOOST_ASSERT(first != last);
    typedef typename std::iterator_traits<I>::value_type T;

    T d = *first;
    ++first;
    while (d != T(0) && first != last)
    {
        d = lcm(d, *first);
        ++first;
    }
    return std::make_pair(d, first);
}

template < typename IntegerType >
class gcd_evaluator
#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL
   : public std::binary_function<IntegerType, IntegerType, IntegerType>
#endif
{
public:
#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
   typedef IntegerType first_argument_type;
   typedef IntegerType second_argument_type;
   typedef IntegerType result_type;
#endif
   IntegerType operator()(IntegerType const &a, IntegerType const &b) const
   {
      return boost::integer::gcd(a, b);
   }
};

template < typename IntegerType >
class lcm_evaluator
#ifdef BOOST_NO_CXX11_HDR_FUNCTIONAL
   : public std::binary_function<IntegerType, IntegerType, IntegerType>
#endif
{
public:
#ifndef BOOST_NO_CXX11_HDR_FUNCTIONAL
   typedef IntegerType first_argument_type;
   typedef IntegerType second_argument_type;
   typedef IntegerType result_type;
#endif
   IntegerType operator()(IntegerType const &a, IntegerType const &b)const
   {
      return boost::integer::lcm(a, b);
   }
};

}  // namespace integer
}  // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif  // BOOST_INTEGER_COMMON_FACTOR_RT_HPP

/* common_factor_rt.hpp
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
*/