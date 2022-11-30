//  boost quaternion.hpp header file

//  (C) Copyright Hubert Holin 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_QUATERNION_HPP
#define BOOST_QUATERNION_HPP

#include <boost/math_fwd.hpp>
#include <boost/math/tools/config.hpp>
#include <locale>                                    // for the "<<" operator

#include <complex>
#include <iosfwd>                                    // for the "<<" and ">>" operators
#include <sstream>                                    // for the "<<" operator

#include <boost/math/special_functions/sinc.hpp>    // for the Sinus cardinal
#include <boost/math/special_functions/sinhc.hpp>    // for the Hyperbolic Sinus cardinal
#include <boost/math/tools/cxx03_warn.hpp>

#include <type_traits>

namespace boost
{
   namespace math
   {

      namespace detail {

         template <class T>
         struct is_trivial_arithmetic_type_imp
         {
            typedef std::integral_constant<bool,
               noexcept(std::declval<T&>() += std::declval<T>())
               && noexcept(std::declval<T&>() -= std::declval<T>())
               && noexcept(std::declval<T&>() *= std::declval<T>())
               && noexcept(std::declval<T&>() /= std::declval<T>())
            > type;
         };

         template <class T>
         struct is_trivial_arithmetic_type : public is_trivial_arithmetic_type_imp<T>::type {};
      }

#ifndef BOOST_NO_CXX14_CONSTEXPR
      namespace constexpr_detail
      {
         template <class T>
         constexpr void swap(T& a, T& b)
         {
            T t(a);
            a = b;
            b = t;
         }
       }
#endif

       template<typename T>
        class quaternion
        {
        public:
            
            typedef T value_type;
            
            
            // constructor for H seen as R^4
            // (also default constructor)
            
            constexpr explicit            quaternion( T const & requested_a = T(),
                                            T const & requested_b = T(),
                                            T const & requested_c = T(),
                                            T const & requested_d = T())
            :   a(requested_a),
                b(requested_b),
                c(requested_c),
                d(requested_d)
            {
                // nothing to do!
            }
            
            
            // constructor for H seen as C^2
                
            constexpr explicit            quaternion( ::std::complex<T> const & z0,
                                            ::std::complex<T> const & z1 = ::std::complex<T>())
            :   a(z0.real()),
                b(z0.imag()),
                c(z1.real()),
                d(z1.imag())
            {
                // nothing to do!
            }
            
            
            // UNtemplated copy constructor
            constexpr quaternion(quaternion const & a_recopier)
               : a(a_recopier.R_component_1()),
               b(a_recopier.R_component_2()),
               c(a_recopier.R_component_3()),
               d(a_recopier.R_component_4()) {}

            constexpr quaternion(quaternion && a_recopier)
               : a(std::move(a_recopier.R_component_1())),
               b(std::move(a_recopier.R_component_2())),
               c(std::move(a_recopier.R_component_3())),
               d(std::move(a_recopier.R_component_4())) {}
            
            // templated copy constructor
            
            template<typename X>
            constexpr explicit            quaternion(quaternion<X> const & a_recopier)
            :   a(static_cast<T>(a_recopier.R_component_1())),
                b(static_cast<T>(a_recopier.R_component_2())),
                c(static_cast<T>(a_recopier.R_component_3())),
                d(static_cast<T>(a_recopier.R_component_4()))
            {
                // nothing to do!
            }
            
            
            // destructor
            // (this is taken care of by the compiler itself)
            
            
            // accessors
            //
            // Note:    Like complex number, quaternions do have a meaningful notion of "real part",
            //            but unlike them there is no meaningful notion of "imaginary part".
            //            Instead there is an "unreal part" which itself is a quaternion, and usually
            //            nothing simpler (as opposed to the complex number case).
            //            However, for practicality, there are accessors for the other components
            //            (these are necessary for the templated copy constructor, for instance).
            
            constexpr T real() const
            {
               return(a);
            }

            constexpr quaternion<T> unreal() const
            {
               return(quaternion<T>(static_cast<T>(0), b, c, d));
            }

            constexpr T R_component_1() const
            {
               return(a);
            }

            constexpr T R_component_2() const
            {
               return(b);
            }

            constexpr T R_component_3() const
            {
               return(c);
            }

            constexpr T R_component_4() const
            {
               return(d);
            }

            constexpr ::std::complex<T> C_component_1() const
            {
               return(::std::complex<T>(a, b));
            }

            constexpr ::std::complex<T> C_component_2() const
            {
               return(::std::complex<T>(c, d));
            }

            BOOST_CXX14_CONSTEXPR void swap(quaternion& o)
            {
#ifndef BOOST_NO_CXX14_CONSTEXPR
               using constexpr_detail::swap;
#else
               using std::swap;
#endif
               swap(a, o.a);
               swap(b, o.b);
               swap(c, o.c);
               swap(d, o.d);
            }

            // assignment operators
            
            template<typename X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator = (quaternion<X> const  & a_affecter)
            {
               a = static_cast<T>(a_affecter.R_component_1());
               b = static_cast<T>(a_affecter.R_component_2());
               c = static_cast<T>(a_affecter.R_component_3());
               d = static_cast<T>(a_affecter.R_component_4());

               return(*this);
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator = (quaternion<T> const & a_affecter)
            {
               a = a_affecter.a;
               b = a_affecter.b;
               c = a_affecter.c;
               d = a_affecter.d;

               return(*this);
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator = (quaternion<T> && a_affecter)
            {
               a = std::move(a_affecter.a);
               b = std::move(a_affecter.b);
               c = std::move(a_affecter.c);
               d = std::move(a_affecter.d);

               return(*this);
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator = (T const & a_affecter)
            {
               a = a_affecter;

               b = c = d = static_cast<T>(0);

               return(*this);
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator = (::std::complex<T> const & a_affecter)
            {
               a = a_affecter.real();
               b = a_affecter.imag();

               c = d = static_cast<T>(0);

               return(*this);
            }

            // other assignment-related operators
            //
            // NOTE:    Quaternion multiplication is *NOT* commutative;
            //            symbolically, "q *= rhs;" means "q = q * rhs;"
            //            and "q /= rhs;" means "q = q * inverse_of(rhs);"
            //
            // Note2:   Each operator comes in 2 forms - one for the simple case where
            //          type T throws no exceptions, and one exception-safe version
            //          for the case where it might.
         private:
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(T const & rhs, const std::true_type&)
            {
               a += rhs;
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(T const & rhs, const std::false_type&)
            {
               quaternion<T> result(a + rhs, b, c, d); // exception guard
               swap(result);
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(std::complex<T> const & rhs, const std::true_type&)
            {
               a += std::real(rhs);
               b += std::imag(rhs);
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(std::complex<T> const & rhs, const std::false_type&)
            {
               quaternion<T> result(a + std::real(rhs), b + std::imag(rhs), c, d); // exception guard
               swap(result);
               return *this;
            }
            template <class X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(quaternion<X> const & rhs, const std::true_type&)
            {
               a += rhs.R_component_1();
               b += rhs.R_component_2();
               c += rhs.R_component_3();
               d += rhs.R_component_4();
               return *this;
            }
            template <class X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(quaternion<X> const & rhs, const std::false_type&)
            {
               quaternion<T> result(a + rhs.R_component_1(), b + rhs.R_component_2(), c + rhs.R_component_3(), d + rhs.R_component_4()); // exception guard
               swap(result);
               return *this;
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(T const & rhs, const std::true_type&)
            {
               a -= rhs;
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(T const & rhs, const std::false_type&)
            {
               quaternion<T> result(a - rhs, b, c, d); // exception guard
               swap(result);
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(std::complex<T> const & rhs, const std::true_type&)
            {
               a -= std::real(rhs);
               b -= std::imag(rhs);
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(std::complex<T> const & rhs, const std::false_type&)
            {
               quaternion<T> result(a - std::real(rhs), b - std::imag(rhs), c, d); // exception guard
               swap(result);
               return *this;
            }
            template <class X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(quaternion<X> const & rhs, const std::true_type&)
            {
               a -= rhs.R_component_1();
               b -= rhs.R_component_2();
               c -= rhs.R_component_3();
               d -= rhs.R_component_4();
               return *this;
            }
            template <class X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(quaternion<X> const & rhs, const std::false_type&)
            {
               quaternion<T> result(a - rhs.R_component_1(), b - rhs.R_component_2(), c - rhs.R_component_3(), d - rhs.R_component_4()); // exception guard
               swap(result);
               return *this;
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_multiply(T const & rhs, const std::true_type&)
            {
               a *= rhs;
               b *= rhs;
               c *= rhs;
               d *= rhs;
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_multiply(T const & rhs, const std::false_type&)
            {
               quaternion<T> result(a * rhs, b * rhs, c * rhs, d * rhs); // exception guard
               swap(result);
               return *this;
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_divide(T const & rhs, const std::true_type&)
            {
               a /= rhs;
               b /= rhs;
               c /= rhs;
               d /= rhs;
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_divide(T const & rhs, const std::false_type&)
            {
               quaternion<T> result(a / rhs, b / rhs, c / rhs, d / rhs); // exception guard
               swap(result);
               return *this;
            }
         public:

            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator += (T const & rhs) { return do_add(rhs, detail::is_trivial_arithmetic_type<T>()); }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator += (::std::complex<T> const & rhs) { return do_add(rhs, detail::is_trivial_arithmetic_type<T>()); }
            template<typename X> BOOST_CXX14_CONSTEXPR quaternion<T> & operator += (quaternion<X> const & rhs) { return do_add(rhs, detail::is_trivial_arithmetic_type<T>()); }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator -= (T const & rhs) { return do_subtract(rhs, detail::is_trivial_arithmetic_type<T>()); }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator -= (::std::complex<T> const & rhs) { return do_subtract(rhs, detail::is_trivial_arithmetic_type<T>()); }
            template<typename X> BOOST_CXX14_CONSTEXPR quaternion<T> & operator -= (quaternion<X> const & rhs) { return do_subtract(rhs, detail::is_trivial_arithmetic_type<T>()); }
            
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator *= (T const & rhs) { return do_multiply(rhs, detail::is_trivial_arithmetic_type<T>()); }
            
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator *= (::std::complex<T> const & rhs)
            {
                T    ar = rhs.real();
                T    br = rhs.imag();
                quaternion<T> result(a*ar - b*br, a*br + b*ar, c*ar + d*br, -c*br+d*ar);
                swap(result);
                return(*this);
            }
            
            template<typename X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator *= (quaternion<X> const & rhs)
            {
                T    ar = static_cast<T>(rhs.R_component_1());
                T    br = static_cast<T>(rhs.R_component_2());
                T    cr = static_cast<T>(rhs.R_component_3());
                T    dr = static_cast<T>(rhs.R_component_4());
                
                quaternion<T> result(a*ar - b*br - c*cr - d*dr, a*br + b*ar + c*dr - d*cr, a*cr - b*dr + c*ar + d*br, a*dr + b*cr - c*br + d*ar);
                swap(result);
                return(*this);
            }
            
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator /= (T const & rhs) { return do_divide(rhs, detail::is_trivial_arithmetic_type<T>()); }
            
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator /= (::std::complex<T> const & rhs)
            {
                T    ar = rhs.real();
                T    br = rhs.imag();
                T    denominator = ar*ar+br*br;
                quaternion<T> result((+a*ar + b*br) / denominator, (-a*br + b*ar) / denominator, (+c*ar - d*br) / denominator, (+c*br + d*ar) / denominator);
                swap(result);
                return(*this);
            }
            
            template<typename X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator /= (quaternion<X> const & rhs)
            {
                T    ar = static_cast<T>(rhs.R_component_1());
                T    br = static_cast<T>(rhs.R_component_2());
                T    cr = static_cast<T>(rhs.R_component_3());
                T    dr = static_cast<T>(rhs.R_component_4());
                
                T    denominator = ar*ar+br*br+cr*cr+dr*dr;
                quaternion<T> result((+a*ar+b*br+c*cr+d*dr)/denominator, (-a*br+b*ar-c*dr+d*cr)/denominator, (-a*cr+b*dr+c*ar-d*br)/denominator, (-a*dr-b*cr+c*br+d*ar)/denominator);
                swap(result);
                return(*this);
            }
        private:
           T a, b, c, d;
            
        };

// swap:
template <class T>
BOOST_CXX14_CONSTEXPR void swap(quaternion<T>& a, quaternion<T>& b) { a.swap(b); }
        
// operator+
template <class T1, class T2>
inline constexpr typename std::enable_if<std::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator + (const quaternion<T1>& a, const T2& b)
{
   return quaternion<T1>(static_cast<T1>(a.R_component_1() + b), a.R_component_2(), a.R_component_3(), a.R_component_4());
}
template <class T1, class T2>
inline constexpr typename std::enable_if<std::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator + (const T1& a, const quaternion<T2>& b)
{
   return quaternion<T2>(static_cast<T2>(b.R_component_1() + a), b.R_component_2(), b.R_component_3(), b.R_component_4());
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator + (const quaternion<T1>& a, const std::complex<T2>& b)
{
   return quaternion<T1>(a.R_component_1() + std::real(b), a.R_component_2() + std::imag(b), a.R_component_3(), a.R_component_4());
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator + (const std::complex<T1>& a, const quaternion<T2>& b)
{
   return quaternion<T1>(b.R_component_1() + std::real(a), b.R_component_2() + std::imag(a), b.R_component_3(), b.R_component_4());
}
template <class T>
inline constexpr quaternion<T> operator + (const quaternion<T>& a, const quaternion<T>& b)
{
   return quaternion<T>(a.R_component_1() + b.R_component_1(), a.R_component_2() + b.R_component_2(), a.R_component_3() + b.R_component_3(), a.R_component_4() + b.R_component_4());
}
// operator-
template <class T1, class T2>
inline constexpr typename std::enable_if<std::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator - (const quaternion<T1>& a, const T2& b)
{
   return quaternion<T1>(static_cast<T1>(a.R_component_1() - b), a.R_component_2(), a.R_component_3(), a.R_component_4());
}
template <class T1, class T2>
inline constexpr typename std::enable_if<std::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator - (const T1& a, const quaternion<T2>& b)
{
   return quaternion<T2>(static_cast<T2>(a - b.R_component_1()), -b.R_component_2(), -b.R_component_3(), -b.R_component_4());
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator - (const quaternion<T1>& a, const std::complex<T2>& b)
{
   return quaternion<T1>(a.R_component_1() - std::real(b), a.R_component_2() - std::imag(b), a.R_component_3(), a.R_component_4());
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator - (const std::complex<T1>& a, const quaternion<T2>& b)
{
   return quaternion<T1>(std::real(a) - b.R_component_1(), std::imag(a) - b.R_component_2(), -b.R_component_3(), -b.R_component_4());
}
template <class T>
inline constexpr quaternion<T> operator - (const quaternion<T>& a, const quaternion<T>& b)
{
   return quaternion<T>(a.R_component_1() - b.R_component_1(), a.R_component_2() - b.R_component_2(), a.R_component_3() - b.R_component_3(), a.R_component_4() - b.R_component_4());
}

// operator*
template <class T1, class T2>
inline constexpr typename std::enable_if<std::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator * (const quaternion<T1>& a, const T2& b)
{
   return quaternion<T1>(static_cast<T1>(a.R_component_1() * b), a.R_component_2() * b, a.R_component_3() * b, a.R_component_4() * b);
}
template <class T1, class T2>
inline constexpr typename std::enable_if<std::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator * (const T1& a, const quaternion<T2>& b)
{
   return quaternion<T2>(static_cast<T2>(a * b.R_component_1()), a * b.R_component_2(), a * b.R_component_3(), a * b.R_component_4());
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator * (const quaternion<T1>& a, const std::complex<T2>& b)
{
   quaternion<T1> result(a);
   result *= b;
   return result;
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator * (const std::complex<T1>& a, const quaternion<T2>& b)
{
   quaternion<T1> result(a);
   result *= b;
   return result;
}
template <class T>
inline BOOST_CXX14_CONSTEXPR quaternion<T> operator * (const quaternion<T>& a, const quaternion<T>& b)
{
   quaternion<T> result(a);
   result *= b;
   return result;
}

// operator/
template <class T1, class T2>
inline constexpr typename std::enable_if<std::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator / (const quaternion<T1>& a, const T2& b)
{
   return quaternion<T1>(a.R_component_1() / b, a.R_component_2() / b, a.R_component_3() / b, a.R_component_4() / b);
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator / (const T1& a, const quaternion<T2>& b)
{
   quaternion<T2> result(a);
   result /= b;
   return result;
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator / (const quaternion<T1>& a, const std::complex<T2>& b)
{
   quaternion<T1> result(a);
   result /= b;
   return result;
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename std::enable_if<std::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator / (const std::complex<T1>& a, const quaternion<T2>& b)
{
   quaternion<T2> result(a);
   result /= b;
   return result;
}
template <class T>
inline BOOST_CXX14_CONSTEXPR quaternion<T> operator / (const quaternion<T>& a, const quaternion<T>& b)
{
   quaternion<T> result(a);
   result /= b;
   return result;
}
        
        
        template<typename T>
        inline constexpr const quaternion<T>&             operator + (quaternion<T> const & q)
        {
            return q;
        }
        
        
        template<typename T>
        inline constexpr quaternion<T>                    operator - (quaternion<T> const & q)
        {
            return(quaternion<T>(-q.R_component_1(),-q.R_component_2(),-q.R_component_3(),-q.R_component_4()));
        }
        
        
        template<typename R, typename T>
        inline constexpr typename std::enable_if<std::is_convertible<R, T>::value, bool>::type operator == (R const & lhs, quaternion<T> const & rhs)
        {
            return    (
                        (rhs.R_component_1() == lhs)&&
                        (rhs.R_component_2() == static_cast<T>(0))&&
                        (rhs.R_component_3() == static_cast<T>(0))&&
                        (rhs.R_component_4() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T, typename R>
        inline constexpr typename std::enable_if<std::is_convertible<R, T>::value, bool>::type operator == (quaternion<T> const & lhs, R const & rhs)
        {
           return rhs == lhs;
        }
        
        
        template<typename T>
        inline constexpr bool                                operator == (::std::complex<T> const & lhs, quaternion<T> const & rhs)
        {
            return    (
                        (rhs.R_component_1() == lhs.real())&&
                        (rhs.R_component_2() == lhs.imag())&&
                        (rhs.R_component_3() == static_cast<T>(0))&&
                        (rhs.R_component_4() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T>
        inline constexpr bool                                operator == (quaternion<T> const & lhs, ::std::complex<T> const & rhs)
        {
           return rhs == lhs;
        }
        
        
        template<typename T>
        inline constexpr bool                                operator == (quaternion<T> const & lhs, quaternion<T> const & rhs)
        {
            return    (
                        (rhs.R_component_1() == lhs.R_component_1())&&
                        (rhs.R_component_2() == lhs.R_component_2())&&
                        (rhs.R_component_3() == lhs.R_component_3())&&
                        (rhs.R_component_4() == lhs.R_component_4())
                    );
        }
                
        template<typename R, typename T> inline constexpr bool operator != (R const & lhs, quaternion<T> const & rhs) { return !(lhs == rhs); }
        template<typename T, typename R> inline constexpr bool operator != (quaternion<T> const & lhs, R const & rhs) { return !(lhs == rhs); }
        template<typename T> inline constexpr bool operator != (::std::complex<T> const & lhs, quaternion<T> const & rhs) { return !(lhs == rhs); }
        template<typename T> inline constexpr bool operator != (quaternion<T> const & lhs, ::std::complex<T> const & rhs) { return !(lhs == rhs); }
        template<typename T> inline constexpr bool operator != (quaternion<T> const & lhs, quaternion<T> const & rhs) { return !(lhs == rhs); }
        
        
        // Note:    we allow the following formats, with a, b, c, and d reals
        //            a
        //            (a), (a,b), (a,b,c), (a,b,c,d)
        //            (a,(c)), (a,(c,d)), ((a)), ((a),c), ((a),(c)), ((a),(c,d)), ((a,b)), ((a,b),c), ((a,b),(c)), ((a,b),(c,d))
        template<typename T, typename charT, class traits>
        ::std::basic_istream<charT,traits> &    operator >> (    ::std::basic_istream<charT,traits> & is,
                                                                quaternion<T> & q)
        {
            const ::std::ctype<charT> & ct = ::std::use_facet< ::std::ctype<charT> >(is.getloc());
            
            T    a = T();
            T    b = T();
            T    c = T();
            T    d = T();
            
            ::std::complex<T>    u = ::std::complex<T>();
            ::std::complex<T>    v = ::std::complex<T>();
            
            charT    ch = charT();
            char    cc;
            
            is >> ch;                                        // get the first lexeme
            
            if    (!is.good())    goto finish;
            
            cc = ct.narrow(ch, char());
            
            if    (cc == '(')                            // read "(", possible: (a), (a,b), (a,b,c), (a,b,c,d), (a,(c)), (a,(c,d)), ((a)), ((a),c), ((a),(c)), ((a),(c,d)), ((a,b)), ((a,b),c), ((a,b),(c)), ((a,b,),(c,d,))
            {
                is >> ch;                                    // get the second lexeme
                
                if    (!is.good())    goto finish;
                
                cc = ct.narrow(ch, char());
                
                if    (cc == '(')                        // read "((", possible: ((a)), ((a),c), ((a),(c)), ((a),(c,d)), ((a,b)), ((a,b),c), ((a,b),(c)), ((a,b,),(c,d,))
                {
                    is.putback(ch);
                    
                    is >> u;                                // we extract the first and second components
                    a = u.real();
                    b = u.imag();
                    
                    if    (!is.good())    goto finish;
                    
                    is >> ch;                                // get the next lexeme
                    
                    if    (!is.good())    goto finish;
                    
                    cc = ct.narrow(ch, char());
                    
                    if        (cc == ')')                    // format: ((a)) or ((a,b))
                    {
                        q = quaternion<T>(a,b);
                    }
                    else if    (cc == ',')                // read "((a)," or "((a,b),", possible: ((a),c), ((a),(c)), ((a),(c,d)), ((a,b),c), ((a,b),(c)), ((a,b,),(c,d,))
                    {
                        is >> v;                            // we extract the third and fourth components
                        c = v.real();
                        d = v.imag();
                        
                        if    (!is.good())    goto finish;
                        
                        is >> ch;                                // get the last lexeme
                        
                        if    (!is.good())    goto finish;
                        
                        cc = ct.narrow(ch, char());
                        
                        if    (cc == ')')                    // format: ((a),c), ((a),(c)), ((a),(c,d)), ((a,b),c), ((a,b),(c)) or ((a,b,),(c,d,))
                        {
                            q = quaternion<T>(a,b,c,d);
                        }
                        else                            // error
                        {
                            is.setstate(::std::ios_base::failbit);
                        }
                    }
                    else                                // error
                    {
                        is.setstate(::std::ios_base::failbit);
                    }
                }
                else                                // read "(a", possible: (a), (a,b), (a,b,c), (a,b,c,d), (a,(c)), (a,(c,d))
                {
                    is.putback(ch);
                    
                    is >> a;                                // we extract the first component
                    
                    if    (!is.good())    goto finish;
                    
                    is >> ch;                                // get the third lexeme
                    
                    if    (!is.good())    goto finish;
                    
                    cc = ct.narrow(ch, char());
                    
                    if        (cc == ')')                    // format: (a)
                    {
                        q = quaternion<T>(a);
                    }
                    else if    (cc == ',')                // read "(a,", possible: (a,b), (a,b,c), (a,b,c,d), (a,(c)), (a,(c,d))
                    {
                        is >> ch;                            // get the fourth lexeme
                        
                        if    (!is.good())    goto finish;
                        
                        cc = ct.narrow(ch, char());
                        
                        if    (cc == '(')                // read "(a,(", possible: (a,(c)), (a,(c,d))
                        {
                            is.putback(ch);
                            
                            is >> v;                        // we extract the third and fourth component
                            
                            c = v.real();
                            d = v.imag();
                            
                            if    (!is.good())    goto finish;
                            
                            is >> ch;                        // get the ninth lexeme
                            
                            if    (!is.good())    goto finish;
                            
                            cc = ct.narrow(ch, char());
                            
                            if    (cc == ')')                // format: (a,(c)) or (a,(c,d))
                            {
                                q = quaternion<T>(a,b,c,d);
                            }
                            else                        // error
                            {
                                is.setstate(::std::ios_base::failbit);
                            }
                        }
                        else                        // read "(a,b", possible: (a,b), (a,b,c), (a,b,c,d)
                        {
                            is.putback(ch);
                            
                            is >> b;                        // we extract the second component
                            
                            if    (!is.good())    goto finish;
                            
                            is >> ch;                        // get the fifth lexeme
                            
                            if    (!is.good())    goto finish;
                            
                            cc = ct.narrow(ch, char());
                            
                            if    (cc == ')')                // format: (a,b)
                            {
                                q = quaternion<T>(a,b);
                            }
                            else if    (cc == ',')        // read "(a,b,", possible: (a,b,c), (a,b,c,d)
                            {
                                is >> c;                    // we extract the third component
                                
                                if    (!is.good())    goto finish;
                                
                                is >> ch;                    // get the seventh lexeme
                                
                                if    (!is.good())    goto finish;
                                
                                cc = ct.narrow(ch, char());
                                
                                if        (cc == ')')        // format: (a,b,c)
                                {
                                    q = quaternion<T>(a,b,c);
                                }
                                else if    (cc == ',')    // read "(a,b,c,", possible: (a,b,c,d)
                                {
                                    is >> d;                // we extract the fourth component
                                    
                                    if    (!is.good())    goto finish;
                                    
                                    is >> ch;                // get the ninth lexeme
                                    
                                    if    (!is.good())    goto finish;
                                    
                                    cc = ct.narrow(ch, char());
                                    
                                    if    (cc == ')')        // format: (a,b,c,d)
                                    {
                                        q = quaternion<T>(a,b,c,d);
                                    }
                                    else                // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                                else                    // error
                                {
                                    is.setstate(::std::ios_base::failbit);
                                }
                            }
                            else                        // error
                            {
                                is.setstate(::std::ios_base::failbit);
                            }
                        }
                    }
                    else                                // error
                    {
                        is.setstate(::std::ios_base::failbit);
                    }
                }
            }
            else                                        // format:    a
            {
                is.putback(ch);
                
                is >> a;                                    // we extract the first component
                
                if    (!is.good())    goto finish;
                
                q = quaternion<T>(a);
            }
            
            finish:
            return(is);
        }
        
        
        template<typename T, typename charT, class traits>
        ::std::basic_ostream<charT,traits> &    operator << (    ::std::basic_ostream<charT,traits> & os,
                                                                quaternion<T> const & q)
        {
            ::std::basic_ostringstream<charT,traits>    s;

            s.flags(os.flags());
            s.imbue(os.getloc());
            s.precision(os.precision());
            
            s << '('    << q.R_component_1() << ','
                        << q.R_component_2() << ','
                        << q.R_component_3() << ','
                        << q.R_component_4() << ')';
            
            return os << s.str();
        }
        
        
        // values
        
        template<typename T>
        inline constexpr T real(quaternion<T> const & q)
        {
            return(q.real());
        }
        
        
        template<typename T>
        inline constexpr quaternion<T> unreal(quaternion<T> const & q)
        {
            return(q.unreal());
        }
                
        template<typename T>
        inline T sup(quaternion<T> const & q)
        {
            using    ::std::abs;
            return (std::max)((std::max)(abs(q.R_component_1()), abs(q.R_component_2())), (std::max)(abs(q.R_component_3()), abs(q.R_component_4())));
        }
        
        
        template<typename T>
        inline T l1(quaternion<T> const & q)
        {
           using    ::std::abs;
           return abs(q.R_component_1()) + abs(q.R_component_2()) + abs(q.R_component_3()) + abs(q.R_component_4());
        }
        
        
        template<typename T>
        inline T abs(quaternion<T> const & q)
        {
            using    ::std::abs;
            using    ::std::sqrt;
            
            T            maxim = sup(q);    // overflow protection
            
            if    (maxim == static_cast<T>(0))
            {
                return(maxim);
            }
            else
            {
                T    mixam = static_cast<T>(1)/maxim;    // prefer multiplications over divisions
                
                T a = q.R_component_1() * mixam;
                T b = q.R_component_2() * mixam;
                T c = q.R_component_3() * mixam;
                T d = q.R_component_4() * mixam;

                a *= a;
                b *= b;
                c *= c;
                d *= d;
                
                return(maxim * sqrt(a + b + c + d));
            }
            
            //return(sqrt(norm(q)));
        }
        
        
        // Note:    This is the Cayley norm, not the Euclidean norm...
        
        template<typename T>
        inline BOOST_CXX14_CONSTEXPR T norm(quaternion<T>const  & q)
        {
            return(real(q*conj(q)));
        }
        
        
        template<typename T>
        inline constexpr quaternion<T> conj(quaternion<T> const & q)
        {
            return(quaternion<T>(   +q.R_component_1(),
                                    -q.R_component_2(),
                                    -q.R_component_3(),
                                    -q.R_component_4()));
        }
        
        
        template<typename T>
        inline quaternion<T>                    spherical(  T const & rho,
                                                            T const & theta,
                                                            T const & phi1,
                                                            T const & phi2)
        {
            using ::std::cos;
            using ::std::sin;
            
            //T    a = cos(theta)*cos(phi1)*cos(phi2);
            //T    b = sin(theta)*cos(phi1)*cos(phi2);
            //T    c = sin(phi1)*cos(phi2);
            //T    d = sin(phi2);
            
            T    courrant = static_cast<T>(1);
            
            T    d = sin(phi2);
            
            courrant *= cos(phi2);
            
            T    c = sin(phi1)*courrant;
            
            courrant *= cos(phi1);
            
            T    b = sin(theta)*courrant;
            T    a = cos(theta)*courrant;
            
            return(rho*quaternion<T>(a,b,c,d));
        }
        
        
        template<typename T>
        inline quaternion<T>                    semipolar(  T const & rho,
                                                            T const & alpha,
                                                            T const & theta1,
                                                            T const & theta2)
        {
            using ::std::cos;
            using ::std::sin;
            
            T    a = cos(alpha)*cos(theta1);
            T    b = cos(alpha)*sin(theta1);
            T    c = sin(alpha)*cos(theta2);
            T    d = sin(alpha)*sin(theta2);
            
            return(rho*quaternion<T>(a,b,c,d));
        }
        
        
        template<typename T>
        inline quaternion<T>                    multipolar( T const & rho1,
                                                            T const & theta1,
                                                            T const & rho2,
                                                            T const & theta2)
        {
            using ::std::cos;
            using ::std::sin;
            
            T    a = rho1*cos(theta1);
            T    b = rho1*sin(theta1);
            T    c = rho2*cos(theta2);
            T    d = rho2*sin(theta2);
            
            return(quaternion<T>(a,b,c,d));
        }
        
        
        template<typename T>
        inline quaternion<T>                    cylindrospherical(  T const & t,
                                                                    T const & radius,
                                                                    T const & longitude,
                                                                    T const & latitude)
        {
            using ::std::cos;
            using ::std::sin;
            
            
            
            T    b = radius*cos(longitude)*cos(latitude);
            T    c = radius*sin(longitude)*cos(latitude);
            T    d = radius*sin(latitude);
            
            return(quaternion<T>(t,b,c,d));
        }
        
        
        template<typename T>
        inline quaternion<T>                    cylindrical(T const & r,
                                                            T const & angle,
                                                            T const & h1,
                                                            T const & h2)
        {
            using ::std::cos;
            using ::std::sin;
            
            T    a = r*cos(angle);
            T    b = r*sin(angle);
            
            return(quaternion<T>(a,b,h1,h2));
        }
        
        
        // transcendentals
        // (please see the documentation)
        
        
        template<typename T>
        inline quaternion<T>                    exp(quaternion<T> const & q)
        {
            using    ::std::exp;
            using    ::std::cos;
            
            using    ::boost::math::sinc_pi;
            
            T    u = exp(real(q));
            
            T    z = abs(unreal(q));
            
            T    w = sinc_pi(z);
            
            return(u*quaternion<T>(cos(z),
                w*q.R_component_2(), w*q.R_component_3(),
                w*q.R_component_4()));
        }
        
        
        template<typename T>
        inline quaternion<T>                    cos(quaternion<T> const & q)
        {
            using    ::std::sin;
            using    ::std::cos;
            using    ::std::cosh;
            
            using    ::boost::math::sinhc_pi;
            
            T    z = abs(unreal(q));
            
            T    w = -sin(q.real())*sinhc_pi(z);
            
            return(quaternion<T>(cos(q.real())*cosh(z),
                w*q.R_component_2(), w*q.R_component_3(),
                w*q.R_component_4()));
        }
        
        
        template<typename T>
        inline quaternion<T>                    sin(quaternion<T> const & q)
        {
            using    ::std::sin;
            using    ::std::cos;
            using    ::std::cosh;
            
            using    ::boost::math::sinhc_pi;
            
            T    z = abs(unreal(q));
            
            T    w = +cos(q.real())*sinhc_pi(z);
            
            return(quaternion<T>(sin(q.real())*cosh(z),
                w*q.R_component_2(), w*q.R_component_3(),
                w*q.R_component_4()));
        }
        
        
        template<typename T>
        inline quaternion<T>                    tan(quaternion<T> const & q)
        {
            return(sin(q)/cos(q));
        }
        
        
        template<typename T>
        inline quaternion<T>                    cosh(quaternion<T> const & q)
        {
            return((exp(+q)+exp(-q))/static_cast<T>(2));
        }
        
        
        template<typename T>
        inline quaternion<T>                    sinh(quaternion<T> const & q)
        {
            return((exp(+q)-exp(-q))/static_cast<T>(2));
        }
        
        
        template<typename T>
        inline quaternion<T>                    tanh(quaternion<T> const & q)
        {
            return(sinh(q)/cosh(q));
        }
        
        
        template<typename T>
        quaternion<T>                            pow(quaternion<T> const & q,
                                                    int n)
        {
            if        (n > 1)
            {
                int    m = n>>1;
                
                quaternion<T>    result = pow(q, m);
                
                result *= result;
                
                if    (n != (m<<1))
                {
                    result *= q; // n odd
                }
                
                return(result);
            }
            else if    (n == 1)
            {
                return(q);
            }
            else if    (n == 0)
            {
                return(quaternion<T>(static_cast<T>(1)));
            }
            else    /* n < 0 */
            {
                return(pow(quaternion<T>(static_cast<T>(1))/q,-n));
            }
        }
    }
}

#endif /* BOOST_QUATERNION_HPP */

/* quaternion.hpp
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
*/