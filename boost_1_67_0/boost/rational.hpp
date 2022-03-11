//  Boost rational.hpp header file  ------------------------------------------//

//  (C) Copyright Paul Moore 1999. Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or
//  implied warranty, and with no claim as to its suitability for any purpose.

// boostinspect:nolicense (don't complain about the lack of a Boost license)
// (Paul Moore hasn't been in contact for years, so there's no way to change the
// license.)

//  See http://www.boost.org/libs/rational for documentation.

//  Credits:
//  Thanks to the boost mailing list in general for useful comments.
//  Particular contributions included:
//    Andrew D Jewell, for reminding me to take care to avoid overflow
//    Ed Brey, for many comments, including picking up on some dreadful typos
//    Stephen Silver contributed the test suite and comments on user-defined
//    IntType
//    Nickolay Mladenov, for the implementation of operator+=

//  Revision History
//  02 Sep 13  Remove unneeded forward declarations; tweak private helper
//             function (Daryle Walker)
//  30 Aug 13  Improve exception safety of "assign"; start modernizing I/O code
//             (Daryle Walker)
//  27 Aug 13  Add cross-version constructor template, plus some private helper
//             functions; add constructor to exception class to take custom
//             messages (Daryle Walker)
//  25 Aug 13  Add constexpr qualification wherever possible (Daryle Walker)
//  05 May 12  Reduced use of implicit gcd (Mario Lang)
//  05 Nov 06  Change rational_cast to not depend on division between different
//             types (Daryle Walker)
//  04 Nov 06  Off-load GCD and LCM to Boost.Integer; add some invariant checks;
//             add std::numeric_limits<> requirement to help GCD (Daryle Walker)
//  31 Oct 06  Recoded both operator< to use round-to-negative-infinity
//             divisions; the rational-value version now uses continued fraction
//             expansion to avoid overflows, for bug #798357 (Daryle Walker)
//  20 Oct 06  Fix operator bool_type for CW 8.3 (Joaquín M López Muñoz)
//  18 Oct 06  Use EXPLICIT_TEMPLATE_TYPE helper macros from Boost.Config
//             (Joaquín M López Muñoz)
//  27 Dec 05  Add Boolean conversion operator (Daryle Walker)
//  28 Sep 02  Use _left versions of operators from operators.hpp
//  05 Jul 01  Recode gcd(), avoiding std::swap (Helmut Zeisel)
//  03 Mar 01  Workarounds for Intel C++ 5.0 (David Abrahams)
//  05 Feb 01  Update operator>> to tighten up input syntax
//  05 Feb 01  Final tidy up of gcd code prior to the new release
//  27 Jan 01  Recode abs() without relying on abs(IntType)
//  21 Jan 01  Include Nickolay Mladenov's operator+= algorithm,
//             tidy up a number of areas, use newer features of operators.hpp
//             (reduces space overhead to zero), add operator!,
//             introduce explicit mixed-mode arithmetic operations
//  12 Jan 01  Include fixes to handle a user-defined IntType better
//  19 Nov 00  Throw on divide by zero in operator /= (John (EBo) David)
//  23 Jun 00  Incorporate changes from Mark Rodgers for Borland C++
//  22 Jun 00  Change _MSC_VER to BOOST_MSVC so other compilers are not
//             affected (Beman Dawes)
//   6 Mar 00  Fix operator-= normalization, #include <string> (Jens Maurer)
//  14 Dec 99  Modifications based on comments from the boost list
//  09 Dec 99  Initial Version (Paul Moore)

#ifndef BOOST_RATIONAL_HPP
#define BOOST_RATIONAL_HPP

#include <boost/config.hpp>      // for BOOST_NO_STDC_NAMESPACE, BOOST_MSVC, etc
#ifndef BOOST_NO_IOSTREAM
#include <iomanip>               // for std::setw
#include <ios>                   // for std::noskipws, streamsize
#include <istream>               // for std::istream
#include <ostream>               // for std::ostream
#include <sstream>               // for std::ostringstream
#endif
#include <cstddef>               // for NULL
#include <stdexcept>             // for std::domain_error
#include <string>                // for std::string implicit constructor
#include <boost/operators.hpp>   // for boost::addable etc
#include <cstdlib>               // for std::abs
#include <boost/call_traits.hpp> // for boost::call_traits
#include <boost/detail/workaround.hpp> // for BOOST_WORKAROUND
#include <boost/assert.hpp>      // for BOOST_ASSERT
#include <boost/integer/common_factor_rt.hpp> // for boost::integer::gcd, lcm
#include <limits>                // for std::numeric_limits
#include <boost/static_assert.hpp>  // for BOOST_STATIC_ASSERT
#include <boost/throw_exception.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_array.hpp>

// Control whether depreciated GCD and LCM functions are included (default: yes)
#ifndef BOOST_CONTROL_RATIONAL_HAS_GCD
#define BOOST_CONTROL_RATIONAL_HAS_GCD  1
#endif

namespace boost {

#if BOOST_CONTROL_RATIONAL_HAS_GCD
template <typename IntType>
IntType gcd(IntType n, IntType m)
{
    // Defer to the version in Boost.Integer
    return integer::gcd( n, m );
}

template <typename IntType>
IntType lcm(IntType n, IntType m)
{
    // Defer to the version in Boost.Integer
    return integer::lcm( n, m );
}
#endif  // BOOST_CONTROL_RATIONAL_HAS_GCD

namespace rational_detail{

   template <class FromInt, class ToInt, typename Enable = void>
   struct is_compatible_integer;

   template <class FromInt, class ToInt>
   struct is_compatible_integer<FromInt, ToInt, typename enable_if_c<!is_array<FromInt>::value>::type>
   {
      BOOST_STATIC_CONSTANT(bool, value = ((std::numeric_limits<FromInt>::is_specialized && std::numeric_limits<FromInt>::is_integer
         && (std::numeric_limits<FromInt>::digits <= std::numeric_limits<ToInt>::digits)
         && (std::numeric_limits<FromInt>::radix == std::numeric_limits<ToInt>::radix)
         && ((std::numeric_limits<FromInt>::is_signed == false) || (std::numeric_limits<ToInt>::is_signed == true))
         && is_convertible<FromInt, ToInt>::value)
         || is_same<FromInt, ToInt>::value)
         || (is_class<ToInt>::value && is_class<FromInt>::value && is_convertible<FromInt, ToInt>::value));
   };

   template <class FromInt, class ToInt>
   struct is_compatible_integer<FromInt, ToInt, typename enable_if_c<is_array<FromInt>::value>::type>
   {
      BOOST_STATIC_CONSTANT(bool, value = false);
   };

   template <class FromInt, class ToInt, typename Enable = void>
   struct is_backward_compatible_integer;

   template <class FromInt, class ToInt>
   struct is_backward_compatible_integer<FromInt, ToInt, typename enable_if_c<!is_array<FromInt>::value>::type>
   {
      BOOST_STATIC_CONSTANT(bool, value = (std::numeric_limits<FromInt>::is_specialized && std::numeric_limits<FromInt>::is_integer
         && !is_compatible_integer<FromInt, ToInt>::value
         && (std::numeric_limits<FromInt>::radix == std::numeric_limits<ToInt>::radix)
         && is_convertible<FromInt, ToInt>::value));
   };

   template <class FromInt, class ToInt>
   struct is_backward_compatible_integer<FromInt, ToInt, typename enable_if_c<is_array<FromInt>::value>::type>
   {
      BOOST_STATIC_CONSTANT(bool, value = false);
   };
}

class bad_rational : public std::domain_error
{
public:
    explicit bad_rational() : std::domain_error("bad rational: zero denominator") {}
    explicit bad_rational( char const *what ) : std::domain_error( what ) {}
};

template <typename IntType>
class rational
{
    // Class-wide pre-conditions
    BOOST_STATIC_ASSERT( ::std::numeric_limits<IntType>::is_specialized );

    // Helper types
    typedef typename boost::call_traits<IntType>::param_type param_type;

    struct helper { IntType parts[2]; };
    typedef IntType (helper::* bool_type)[2];

public:
    // Component type
    typedef IntType int_type;

    BOOST_CONSTEXPR
    rational() : num(0), den(1) {}

    template <class T>//, typename enable_if_c<!is_array<T>::value>::type>
    BOOST_CONSTEXPR rational(const T& n, typename enable_if_c<
       rational_detail::is_compatible_integer<T, IntType>::value
    >::type const* = 0) : num(n), den(1) {}

    template <class T, class U>
    BOOST_CXX14_CONSTEXPR rational(const T& n, const U& d, typename enable_if_c<
       rational_detail::is_compatible_integer<T, IntType>::value && rational_detail::is_compatible_integer<U, IntType>::value
    >::type const* = 0) : num(n), den(d) {
       normalize();
    }

    template < typename NewType >
    BOOST_CONSTEXPR explicit
       rational(rational<NewType> const &r, typename enable_if_c<rational_detail::is_compatible_integer<NewType, IntType>::value>::type const* = 0)
       : num(r.numerator()), den(is_normalized(int_type(r.numerator()),
       int_type(r.denominator())) ? r.denominator() :
       (BOOST_THROW_EXCEPTION(bad_rational("bad rational: denormalized conversion")), 0)){}

    template < typename NewType >
    BOOST_CONSTEXPR explicit
       rational(rational<NewType> const &r, typename disable_if_c<rational_detail::is_compatible_integer<NewType, IntType>::value>::type const* = 0)
       : num(r.numerator()), den(is_normalized(int_type(r.numerator()),
       int_type(r.denominator())) && is_safe_narrowing_conversion(r.denominator()) && is_safe_narrowing_conversion(r.numerator()) ? r.denominator() :
       (BOOST_THROW_EXCEPTION(bad_rational("bad rational: denormalized conversion")), 0)){}
    // Default copy constructor and assignment are fine

    // Add assignment from IntType
    template <class T>
    BOOST_CXX14_CONSTEXPR typename enable_if_c<
       rational_detail::is_compatible_integer<T, IntType>::value, rational &
    >::type operator=(const T& n) { return assign(static_cast<IntType>(n), static_cast<IntType>(1)); }

    // Assign in place
    template <class T, class U>
    BOOST_CXX14_CONSTEXPR typename enable_if_c<
       rational_detail::is_compatible_integer<T, IntType>::value && rational_detail::is_compatible_integer<U, IntType>::value, rational &
    >::type assign(const T& n, const U& d)
    {
       return *this = rational<IntType>(static_cast<IntType>(n), static_cast<IntType>(d));
    }
    //
    // The following overloads should probably *not* be provided - 
    // but are provided for backwards compatibity reasons only.
    // These allow for construction/assignment from types that
    // are wider than IntType only if there is an implicit
    // conversion from T to IntType, they will throw a bad_rational
    // if the conversion results in loss of precision or undefined behaviour.
    //
    template <class T>//, typename enable_if_c<!is_array<T>::value>::type>
    BOOST_CXX14_CONSTEXPR rational(const T& n, typename enable_if_c<
       rational_detail::is_backward_compatible_integer<T, IntType>::value
    >::type const* = 0)
    {
       assign(n, static_cast<T>(1));
    }
    template <class T, class U>
    BOOST_CXX14_CONSTEXPR rational(const T& n, const U& d, typename enable_if_c<
       (!rational_detail::is_compatible_integer<T, IntType>::value
       || !rational_detail::is_compatible_integer<U, IntType>::value)
       && std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_integer
       && (std::numeric_limits<T>::radix == std::numeric_limits<IntType>::radix)
       && is_convertible<T, IntType>::value &&
       std::numeric_limits<U>::is_specialized && std::numeric_limits<U>::is_integer
       && (std::numeric_limits<U>::radix == std::numeric_limits<IntType>::radix)
       && is_convertible<U, IntType>::value
    >::type const* = 0)
    {
       assign(n, d);
    }
    template <class T>
    BOOST_CXX14_CONSTEXPR typename enable_if_c<
       std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_integer
       && !rational_detail::is_compatible_integer<T, IntType>::value
       && (std::numeric_limits<T>::radix == std::numeric_limits<IntType>::radix)
       && is_convertible<T, IntType>::value,
       rational &
    >::type operator=(const T& n) { return assign(n, static_cast<T>(1)); }

    template <class T, class U>
    BOOST_CXX14_CONSTEXPR typename enable_if_c<
       (!rational_detail::is_compatible_integer<T, IntType>::value
          || !rational_detail::is_compatible_integer<U, IntType>::value)
       && std::numeric_limits<T>::is_specialized && std::numeric_limits<T>::is_integer
       && (std::numeric_limits<T>::radix == std::numeric_limits<IntType>::radix)
       && is_convertible<T, IntType>::value &&
       std::numeric_limits<U>::is_specialized && std::numeric_limits<U>::is_integer
       && (std::numeric_limits<U>::radix == std::numeric_limits<IntType>::radix)
       && is_convertible<U, IntType>::value,
       rational &
    >::type assign(const T& n, const U& d)
    {
       if(!is_safe_narrowing_conversion(n) || !is_safe_narrowing_conversion(d))
          BOOST_THROW_EXCEPTION(bad_rational());
       return *this = rational<IntType>(static_cast<IntType>(n), static_cast<IntType>(d));
    }

    // Access to representation
    BOOST_CONSTEXPR
    const IntType& numerator() const { return num; }
    BOOST_CONSTEXPR
    const IntType& denominator() const { return den; }

    // Arithmetic assignment operators
    BOOST_CXX14_CONSTEXPR rational& operator+= (const rational& r);
    BOOST_CXX14_CONSTEXPR rational& operator-= (const rational& r);
    BOOST_CXX14_CONSTEXPR rational& operator*= (const rational& r);
    BOOST_CXX14_CONSTEXPR rational& operator/= (const rational& r);

    template <class T>
    BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<rational_detail::is_compatible_integer<T, IntType>::value, rational&>::type operator+= (const T& i)
    {
       num += i * den;
       return *this;
    }
    template <class T>
    BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<rational_detail::is_compatible_integer<T, IntType>::value, rational&>::type operator-= (const T& i)
    {
       num -= i * den;
       return *this;
    }
    template <class T>
    BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<rational_detail::is_compatible_integer<T, IntType>::value, rational&>::type operator*= (const T& i)
    {
       // Avoid overflow and preserve normalization
       IntType gcd = integer::gcd(static_cast<IntType>(i), den);
       num *= i / gcd;
       den /= gcd;
       return *this;
    }
    template <class T>
    BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<rational_detail::is_compatible_integer<T, IntType>::value, rational&>::type operator/= (const T& i)
    {
       // Avoid repeated construction
       IntType const zero(0);

       if(i == zero) BOOST_THROW_EXCEPTION(bad_rational());
       if(num == zero) return *this;

       // Avoid overflow and preserve normalization
       IntType const gcd = integer::gcd(num, static_cast<IntType>(i));
       num /= gcd;
       den *= i / gcd;

       if(den < zero) {
          num = -num;
          den = -den;
       }

       return *this;
    }

    // Increment and decrement
    BOOST_CXX14_CONSTEXPR const rational& operator++() { num += den; return *this; }
    BOOST_CXX14_CONSTEXPR const rational& operator--() { num -= den; return *this; }

    BOOST_CXX14_CONSTEXPR rational operator++(int)
    {
       rational t(*this);
       ++(*this);
       return t;
    }
    BOOST_CXX14_CONSTEXPR rational operator--(int)
    {
       rational t(*this);
       --(*this);
       return t;
    }

    // Operator not
    BOOST_CONSTEXPR
    bool operator!() const { return !num; }

    // Boolean conversion
    
#if BOOST_WORKAROUND(__MWERKS__,<=0x3003)
    // The "ISO C++ Template Parser" option in CW 8.3 chokes on the
    // following, hence we selectively disable that option for the
    // offending memfun.
#pragma parse_mfunc_templ off
#endif

    BOOST_CONSTEXPR
    operator bool_type() const { return operator !() ? 0 : &helper::parts; }

#if BOOST_WORKAROUND(__MWERKS__,<=0x3003)
#pragma parse_mfunc_templ reset
#endif

    // Comparison operators
    BOOST_CXX14_CONSTEXPR bool operator< (const rational& r) const;
    BOOST_CXX14_CONSTEXPR bool operator> (const rational& r) const { return r < *this; }
    BOOST_CONSTEXPR
    bool operator== (const rational& r) const;

    template <class T>
    BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<rational_detail::is_compatible_integer<T, IntType>::value, bool>::type operator< (const T& i) const
    {
       // Avoid repeated construction
       int_type const  zero(0);

       // Break value into mixed-fraction form, w/ always-nonnegative remainder
       BOOST_ASSERT(this->den > zero);
       int_type  q = this->num / this->den, r = this->num % this->den;
       while(r < zero)  { r += this->den; --q; }

       // Compare with just the quotient, since the remainder always bumps the
       // value up.  [Since q = floor(n/d), and if n/d < i then q < i, if n/d == i
       // then q == i, if n/d == i + r/d then q == i, and if n/d >= i + 1 then
       // q >= i + 1 > i; therefore n/d < i iff q < i.]
       return q < i;
    }
    template <class T>
    BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<rational_detail::is_compatible_integer<T, IntType>::value, bool>::type operator>(const T& i) const
    {
       return operator==(i) ? false : !operator<(i);
    }
    template <class T>
    BOOST_CONSTEXPR typename boost::enable_if_c<rational_detail::is_compatible_integer<T, IntType>::value, bool>::type operator== (const T& i) const
    {
       return ((den == IntType(1)) && (num == i));
    }

private:
    // Implementation - numerator and denominator (normalized).
    // Other possibilities - separate whole-part, or sign, fields?
    IntType num;
    IntType den;

    // Helper functions
    static BOOST_CONSTEXPR
    int_type inner_gcd( param_type a, param_type b, int_type const &zero =
     int_type(0) )
    { return b == zero ? a : inner_gcd(b, a % b, zero); }

    static BOOST_CONSTEXPR
    int_type inner_abs( param_type x, int_type const &zero = int_type(0) )
    { return x < zero ? -x : +x; }

    // Representation note: Fractions are kept in normalized form at all
    // times. normalized form is defined as gcd(num,den) == 1 and den > 0.
    // In particular, note that the implementation of abs() below relies
    // on den always being positive.
    BOOST_CXX14_CONSTEXPR bool test_invariant() const;
    BOOST_CXX14_CONSTEXPR void normalize();

    static BOOST_CONSTEXPR
    bool is_normalized( param_type n, param_type d, int_type const &zero =
     int_type(0), int_type const &one = int_type(1) )
    {
        return d > zero && ( n != zero || d == one ) && inner_abs( inner_gcd(n,
         d, zero), zero ) == one;
    }
    //
    // Conversion checks:
    //
    // (1) From an unsigned type with more digits than IntType:
    //
    template <class T>
    BOOST_CONSTEXPR static typename boost::enable_if_c<(std::numeric_limits<T>::digits > std::numeric_limits<IntType>::digits) && (std::numeric_limits<T>::is_signed == false), bool>::type is_safe_narrowing_conversion(const T& val)
    {
       return val < (T(1) << std::numeric_limits<IntType>::digits);
    }
    //
    // (2) From a signed type with more digits than IntType, and IntType also signed:
    //
    template <class T>
    BOOST_CONSTEXPR static typename boost::enable_if_c<(std::numeric_limits<T>::digits > std::numeric_limits<IntType>::digits) && (std::numeric_limits<T>::is_signed == true) && (std::numeric_limits<IntType>::is_signed == true), bool>::type is_safe_narrowing_conversion(const T& val)
    {
       // Note that this check assumes IntType has a 2's complement representation,
       // we don't want to try to convert a std::numeric_limits<IntType>::min() to
       // a T because that conversion may not be allowed (this happens when IntType
       // is from Boost.Multiprecision).
       return (val < (T(1) << std::numeric_limits<IntType>::digits)) && (val >= -(T(1) << std::numeric_limits<IntType>::digits));
    }
    //
    // (3) From a signed type with more digits than IntType, and IntType unsigned:
    //
    template <class T>
    BOOST_CONSTEXPR static typename boost::enable_if_c<(std::numeric_limits<T>::digits > std::numeric_limits<IntType>::digits) && (std::numeric_limits<T>::is_signed == true) && (std::numeric_limits<IntType>::is_signed == false), bool>::type is_safe_narrowing_conversion(const T& val)
    {
       return (val < (T(1) << std::numeric_limits<IntType>::digits)) && (val >= 0);
    }
    //
    // (4) From a signed type with fewer digits than IntType, and IntType unsigned:
    //
    template <class T>
    BOOST_CONSTEXPR static typename boost::enable_if_c<(std::numeric_limits<T>::digits <= std::numeric_limits<IntType>::digits) && (std::numeric_limits<T>::is_signed == true) && (std::numeric_limits<IntType>::is_signed == false), bool>::type is_safe_narrowing_conversion(const T& val)
    {
       return val >= 0;
    }
    //
    // (5) From an unsigned type with fewer digits than IntType, and IntType signed:
    //
    template <class T>
    BOOST_CONSTEXPR static typename boost::enable_if_c<(std::numeric_limits<T>::digits <= std::numeric_limits<IntType>::digits) && (std::numeric_limits<T>::is_signed == false) && (std::numeric_limits<IntType>::is_signed == true), bool>::type is_safe_narrowing_conversion(const T&)
    {
       return true;
    }
    //
    // (6) From an unsigned type with fewer digits than IntType, and IntType unsigned:
    //
    template <class T>
    BOOST_CONSTEXPR static typename boost::enable_if_c<(std::numeric_limits<T>::digits <= std::numeric_limits<IntType>::digits) && (std::numeric_limits<T>::is_signed == false) && (std::numeric_limits<IntType>::is_signed == false), bool>::type is_safe_narrowing_conversion(const T&)
    {
       return true;
    }
    //
    // (7) From an signed type with fewer digits than IntType, and IntType signed:
    //
    template <class T>
    BOOST_CONSTEXPR static typename boost::enable_if_c<(std::numeric_limits<T>::digits <= std::numeric_limits<IntType>::digits) && (std::numeric_limits<T>::is_signed == true) && (std::numeric_limits<IntType>::is_signed == true), bool>::type is_safe_narrowing_conversion(const T&)
    {
       return true;
    }
};

// Unary plus and minus
template <typename IntType>
BOOST_CONSTEXPR
inline rational<IntType> operator+ (const rational<IntType>& r)
{
    return r;
}

template <typename IntType>
BOOST_CXX14_CONSTEXPR
inline rational<IntType> operator- (const rational<IntType>& r)
{
    return rational<IntType>(static_cast<IntType>(-r.numerator()), r.denominator());
}

// Arithmetic assignment operators
template <typename IntType>
BOOST_CXX14_CONSTEXPR rational<IntType>& rational<IntType>::operator+= (const rational<IntType>& r)
{
    // This calculation avoids overflow, and minimises the number of expensive
    // calculations. Thanks to Nickolay Mladenov for this algorithm.
    //
    // Proof:
    // We have to compute a/b + c/d, where gcd(a,b)=1 and gcd(b,c)=1.
    // Let g = gcd(b,d), and b = b1*g, d=d1*g. Then gcd(b1,d1)=1
    //
    // The result is (a*d1 + c*b1) / (b1*d1*g).
    // Now we have to normalize this ratio.
    // Let's assume h | gcd((a*d1 + c*b1), (b1*d1*g)), and h > 1
    // If h | b1 then gcd(h,d1)=1 and hence h|(a*d1+c*b1) => h|a.
    // But since gcd(a,b1)=1 we have h=1.
    // Similarly h|d1 leads to h=1.
    // So we have that h | gcd((a*d1 + c*b1) , (b1*d1*g)) => h|g
    // Finally we have gcd((a*d1 + c*b1), (b1*d1*g)) = gcd((a*d1 + c*b1), g)
    // Which proves that instead of normalizing the result, it is better to
    // divide num and den by gcd((a*d1 + c*b1), g)

    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    IntType g = integer::gcd(den, r_den);
    den /= g;  // = b1 from the calculations above
    num = num * (r_den / g) + r_num * den;
    g = integer::gcd(num, g);
    num /= g;
    den *= r_den/g;

    return *this;
}

template <typename IntType>
BOOST_CXX14_CONSTEXPR rational<IntType>& rational<IntType>::operator-= (const rational<IntType>& r)
{
    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    // This calculation avoids overflow, and minimises the number of expensive
    // calculations. It corresponds exactly to the += case above
    IntType g = integer::gcd(den, r_den);
    den /= g;
    num = num * (r_den / g) - r_num * den;
    g = integer::gcd(num, g);
    num /= g;
    den *= r_den/g;

    return *this;
}

template <typename IntType>
BOOST_CXX14_CONSTEXPR rational<IntType>& rational<IntType>::operator*= (const rational<IntType>& r)
{
    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    // Avoid overflow and preserve normalization
    IntType gcd1 = integer::gcd(num, r_den);
    IntType gcd2 = integer::gcd(r_num, den);
    num = (num/gcd1) * (r_num/gcd2);
    den = (den/gcd2) * (r_den/gcd1);
    return *this;
}

template <typename IntType>
BOOST_CXX14_CONSTEXPR rational<IntType>& rational<IntType>::operator/= (const rational<IntType>& r)
{
    // Protect against self-modification
    IntType r_num = r.num;
    IntType r_den = r.den;

    // Avoid repeated construction
    IntType zero(0);

    // Trap division by zero
    if (r_num == zero)
        BOOST_THROW_EXCEPTION(bad_rational());
    if (num == zero)
        return *this;

    // Avoid overflow and preserve normalization
    IntType gcd1 = integer::gcd(num, r_num);
    IntType gcd2 = integer::gcd(r_den, den);
    num = (num/gcd1) * (r_den/gcd2);
    den = (den/gcd2) * (r_num/gcd1);

    if (den < zero) {
        num = -num;
        den = -den;
    }
    return *this;
}


//
// Non-member operators: previously these were provided by Boost.Operator, but these had a number of
// drawbacks, most notably, that in order to allow inter-operability with IntType code such as this:
//
// rational<int> r(3);
// assert(r == 3.5); // compiles and passes!!
//
// Happens to be allowed as well :-(
//
// There are three possible cases for each operator:
// 1) rational op rational.
// 2) rational op integer
// 3) integer op rational
// Cases (1) and (2) are folded into the one function.
//
template <class IntType, class Arg>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value || is_same<rational<IntType>, Arg>::value, rational<IntType> >::type
   operator + (const rational<IntType>& a, const Arg& b)
{
      rational<IntType> t(a);
      return t += b;
}
template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, rational<IntType> >::type
   operator + (const Arg& b, const rational<IntType>& a)
{
      rational<IntType> t(a);
      return t += b;
}

template <class IntType, class Arg>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value || is_same<rational<IntType>, Arg>::value, rational<IntType> >::type
   operator - (const rational<IntType>& a, const Arg& b)
{
      rational<IntType> t(a);
      return t -= b;
}
template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, rational<IntType> >::type
   operator - (const Arg& b, const rational<IntType>& a)
{
      rational<IntType> t(a);
      return -(t -= b);
}

template <class IntType, class Arg>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value || is_same<rational<IntType>, Arg>::value, rational<IntType> >::type
   operator * (const rational<IntType>& a, const Arg& b)
{
      rational<IntType> t(a);
      return t *= b;
}
template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, rational<IntType> >::type
   operator * (const Arg& b, const rational<IntType>& a)
{
      rational<IntType> t(a);
      return t *= b;
}

template <class IntType, class Arg>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value || is_same<rational<IntType>, Arg>::value, rational<IntType> >::type
   operator / (const rational<IntType>& a, const Arg& b)
{
      rational<IntType> t(a);
      return t /= b;
}
template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, rational<IntType> >::type
   operator / (const Arg& b, const rational<IntType>& a)
{
      rational<IntType> t(b);
      return t /= a;
}

template <class IntType, class Arg>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value || is_same<rational<IntType>, Arg>::value, bool>::type
   operator <= (const rational<IntType>& a, const Arg& b)
{
      return !(a > b);
}
template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, bool>::type
   operator <= (const Arg& b, const rational<IntType>& a)
{
      return a >= b;
}

template <class IntType, class Arg>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value || is_same<rational<IntType>, Arg>::value, bool>::type
   operator >= (const rational<IntType>& a, const Arg& b)
{
      return !(a < b);
}
template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, bool>::type
   operator >= (const Arg& b, const rational<IntType>& a)
{
      return a <= b;
}

template <class IntType, class Arg>
BOOST_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value || is_same<rational<IntType>, Arg>::value, bool>::type
   operator != (const rational<IntType>& a, const Arg& b)
{
      return !(a == b);
}
template <class Arg, class IntType>
BOOST_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, bool>::type
   operator != (const Arg& b, const rational<IntType>& a)
{
      return !(b == a);
}

template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, bool>::type
   operator < (const Arg& b, const rational<IntType>& a)
{
      return a > b;
}
template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, bool>::type
   operator > (const Arg& b, const rational<IntType>& a)
{
      return a < b;
}
template <class Arg, class IntType>
BOOST_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, bool>::type
   operator == (const Arg& b, const rational<IntType>& a)
{
      return a == b;
}

// Comparison operators
template <typename IntType>
BOOST_CXX14_CONSTEXPR
bool rational<IntType>::operator< (const rational<IntType>& r) const
{
    // Avoid repeated construction
    int_type const  zero( 0 );

    // This should really be a class-wide invariant.  The reason for these
    // checks is that for 2's complement systems, INT_MIN has no corresponding
    // positive, so negating it during normalization keeps it INT_MIN, which
    // is bad for later calculations that assume a positive denominator.
    BOOST_ASSERT( this->den > zero );
    BOOST_ASSERT( r.den > zero );

    // Determine relative order by expanding each value to its simple continued
    // fraction representation using the Euclidian GCD algorithm.
    struct { int_type  n, d, q, r; }
     ts = { this->num, this->den, static_cast<int_type>(this->num / this->den),
     static_cast<int_type>(this->num % this->den) },
     rs = { r.num, r.den, static_cast<int_type>(r.num / r.den),
     static_cast<int_type>(r.num % r.den) };
    unsigned  reverse = 0u;

    // Normalize negative moduli by repeatedly adding the (positive) denominator
    // and decrementing the quotient.  Later cycles should have all positive
    // values, so this only has to be done for the first cycle.  (The rules of
    // C++ require a nonnegative quotient & remainder for a nonnegative dividend
    // & positive divisor.)
    while ( ts.r < zero )  { ts.r += ts.d; --ts.q; }
    while ( rs.r < zero )  { rs.r += rs.d; --rs.q; }

    // Loop through and compare each variable's continued-fraction components
    for ( ;; )
    {
        // The quotients of the current cycle are the continued-fraction
        // components.  Comparing two c.f. is comparing their sequences,
        // stopping at the first difference.
        if ( ts.q != rs.q )
        {
            // Since reciprocation changes the relative order of two variables,
            // and c.f. use reciprocals, the less/greater-than test reverses
            // after each index.  (Start w/ non-reversed @ whole-number place.)
            return reverse ? ts.q > rs.q : ts.q < rs.q;
        }

        // Prepare the next cycle
        reverse ^= 1u;

        if ( (ts.r == zero) || (rs.r == zero) )
        {
            // At least one variable's c.f. expansion has ended
            break;
        }

        ts.n = ts.d;         ts.d = ts.r;
        ts.q = ts.n / ts.d;  ts.r = ts.n % ts.d;
        rs.n = rs.d;         rs.d = rs.r;
        rs.q = rs.n / rs.d;  rs.r = rs.n % rs.d;
    }

    // Compare infinity-valued components for otherwise equal sequences
    if ( ts.r == rs.r )
    {
        // Both remainders are zero, so the next (and subsequent) c.f.
        // components for both sequences are infinity.  Therefore, the sequences
        // and their corresponding values are equal.
        return false;
    }
    else
    {
#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable:4800)
#endif
        // Exactly one of the remainders is zero, so all following c.f.
        // components of that variable are infinity, while the other variable
        // has a finite next c.f. component.  So that other variable has the
        // lesser value (modulo the reversal flag!).
        return ( ts.r != zero ) != static_cast<bool>( reverse );
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif
    }
}

template <typename IntType>
BOOST_CONSTEXPR
inline bool rational<IntType>::operator== (const rational<IntType>& r) const
{
    return ((num == r.num) && (den == r.den));
}

// Invariant check
template <typename IntType>
BOOST_CXX14_CONSTEXPR
inline bool rational<IntType>::test_invariant() const
{
    return ( this->den > int_type(0) ) && ( integer::gcd(this->num, this->den) ==
     int_type(1) );
}

// Normalisation
template <typename IntType>
BOOST_CXX14_CONSTEXPR void rational<IntType>::normalize()
{
    // Avoid repeated construction
    IntType zero(0);

    if (den == zero)
       BOOST_THROW_EXCEPTION(bad_rational());

    // Handle the case of zero separately, to avoid division by zero
    if (num == zero) {
        den = IntType(1);
        return;
    }

    IntType g = integer::gcd(num, den);

    num /= g;
    den /= g;

    if (den < -(std::numeric_limits<IntType>::max)()) {
        BOOST_THROW_EXCEPTION(bad_rational("bad rational: non-zero singular denominator"));
    }

    // Ensure that the denominator is positive
    if (den < zero) {
        num = -num;
        den = -den;
    }

    BOOST_ASSERT( this->test_invariant() );
}

#ifndef BOOST_NO_IOSTREAM
namespace detail {

    // A utility class to reset the format flags for an istream at end
    // of scope, even in case of exceptions
    struct resetter {
        resetter(std::istream& is) : is_(is), f_(is.flags()) {}
        ~resetter() { is_.flags(f_); }
        std::istream& is_;
        std::istream::fmtflags f_;      // old GNU c++ lib has no ios_base
    };

}

// Input and output
template <typename IntType>
std::istream& operator>> (std::istream& is, rational<IntType>& r)
{
    using std::ios;

    IntType n = IntType(0), d = IntType(1);
    char c = 0;
    detail::resetter sentry(is);

    if ( is >> n )
    {
        if ( is.get(c) )
        {
            if ( c == '/' )
            {
                if ( is >> std::noskipws >> d )
                    try {
                        r.assign( n, d );
                    } catch ( bad_rational & ) {        // normalization fail
                        try { is.setstate(ios::failbit); }
                        catch ( ... ) {}  // don't throw ios_base::failure...
                        if ( is.exceptions() & ios::failbit )
                            throw;   // ...but the original exception instead
                        // ELSE: suppress the exception, use just error flags
                    }
            }
            else
                is.setstate( ios::failbit );
        }
    }

    return is;
}

// Add manipulators for output format?
template <typename IntType>
std::ostream& operator<< (std::ostream& os, const rational<IntType>& r)
{
    // The slash directly precedes the denominator, which has no prefixes.
    std::ostringstream  ss;

    ss.copyfmt( os );
    ss.tie( NULL );
    ss.exceptions( std::ios::goodbit );
    ss.width( 0 );
    ss << std::noshowpos << std::noshowbase << '/' << r.denominator();

    // The numerator holds the showpos, internal, and showbase flags.
    std::string const   tail = ss.str();
    std::streamsize const  w =
        os.width() - static_cast<std::streamsize>( tail.size() );

    ss.clear();
    ss.str( "" );
    ss.flags( os.flags() );
    ss << std::setw( w < 0 || (os.flags() & std::ios::adjustfield) !=
                     std::ios::internal ? 0 : w ) << r.numerator();
    return os << ss.str() + tail;
}
#endif  // BOOST_NO_IOSTREAM

// Type conversion
template <typename T, typename IntType>
BOOST_CONSTEXPR
inline T rational_cast(const rational<IntType>& src)
{
    return static_cast<T>(src.numerator())/static_cast<T>(src.denominator());
}

// Do not use any abs() defined on IntType - it isn't worth it, given the
// difficulties involved (Koenig lookup required, there may not *be* an abs()
// defined, etc etc).
template <typename IntType>
BOOST_CXX14_CONSTEXPR
inline rational<IntType> abs(const rational<IntType>& r)
{
    return r.numerator() >= IntType(0)? r: -r;
}

namespace integer {

template <typename IntType>
struct gcd_evaluator< rational<IntType> >
{
    typedef rational<IntType> result_type,
                              first_argument_type, second_argument_type;
    result_type operator() (  first_argument_type const &a
                           , second_argument_type const &b
                           ) const
    {
        return result_type(integer::gcd(a.numerator(), b.numerator()),
                           integer::lcm(a.denominator(), b.denominator()));
    }
};

template <typename IntType>
struct lcm_evaluator< rational<IntType> >
{
    typedef rational<IntType> result_type,
                              first_argument_type, second_argument_type;
    result_type operator() (  first_argument_type const &a
                           , second_argument_type const &b
                           ) const
    {
        return result_type(integer::lcm(a.numerator(), b.numerator()),
                           integer::gcd(a.denominator(), b.denominator()));
    }
};

} // namespace integer

} // namespace boost

#endif  // BOOST_RATIONAL_HPP

/* rational.hpp
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
*/