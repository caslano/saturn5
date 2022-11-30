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
//  12 Nov 20  Fix operators to work with C++20 rules (Glen Joseph Fernandes)
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
      return !a.operator>(b);
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
      return !a.operator<(b);
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
      return !a.operator==(b);
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
      return a.operator>(b);
}
template <class Arg, class IntType>
BOOST_CXX14_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, bool>::type
   operator > (const Arg& b, const rational<IntType>& a)
{
      return a.operator<(b);
}
template <class Arg, class IntType>
BOOST_CONSTEXPR
inline typename boost::enable_if_c <
   rational_detail::is_compatible_integer<Arg, IntType>::value, bool>::type
   operator == (const Arg& b, const rational<IntType>& a)
{
      return a.operator==(b);
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