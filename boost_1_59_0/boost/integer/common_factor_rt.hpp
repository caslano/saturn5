//  (C) Copyright Jeremy William Murphy 2016.

//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt)

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
            while (T(0) == (val & 1u))
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