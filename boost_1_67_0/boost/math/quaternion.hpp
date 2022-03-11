//  boost quaternion.hpp header file

//  (C) Copyright Hubert Holin 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.

#ifndef BOOST_QUATERNION_HPP
#define BOOST_QUATERNION_HPP

#include <boost/config.hpp> // for BOOST_NO_STD_LOCALE
#include <boost/math_fwd.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/utility/enable_if.hpp>
#ifndef    BOOST_NO_STD_LOCALE
#  include <locale>                                    // for the "<<" operator
#endif /* BOOST_NO_STD_LOCALE */

#include <complex>
#include <iosfwd>                                    // for the "<<" and ">>" operators
#include <sstream>                                    // for the "<<" operator

#include <boost/math/special_functions/sinc.hpp>    // for the Sinus cardinal
#include <boost/math/special_functions/sinhc.hpp>    // for the Hyperbolic Sinus cardinal
#include <boost/math/tools/cxx03_warn.hpp>

#if defined(BOOST_NO_CXX11_NOEXCEPT) || defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || defined(BOOST_NO_SFINAE_EXPR)
#include <boost/type_traits/is_pod.hpp>
#endif

namespace boost
{
   namespace math
   {

      namespace detail {

#if !defined(BOOST_NO_CXX11_NOEXCEPT) && !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_SFINAE_EXPR)

         template <class T>
         struct is_trivial_arithmetic_type_imp
         {
            typedef boost::integral_constant<bool,
               noexcept(std::declval<T&>() += std::declval<T>())
               && noexcept(std::declval<T&>() -= std::declval<T>())
               && noexcept(std::declval<T&>() *= std::declval<T>())
               && noexcept(std::declval<T&>() /= std::declval<T>())
            > type;
         };

         template <class T>
         struct is_trivial_arithmetic_type : public is_trivial_arithmetic_type_imp<T>::type {};
#else

         template <class T>
         struct is_trivial_arithmetic_type : public boost::is_pod<T> {};

#endif

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
            
            BOOST_CONSTEXPR explicit            quaternion( T const & requested_a = T(),
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
                
            BOOST_CONSTEXPR explicit            quaternion( ::std::complex<T> const & z0,
                                            ::std::complex<T> const & z1 = ::std::complex<T>())
            :   a(z0.real()),
                b(z0.imag()),
                c(z1.real()),
                d(z1.imag())
            {
                // nothing to do!
            }
            
            
            // UNtemplated copy constructor
            BOOST_CONSTEXPR quaternion(quaternion const & a_recopier)
               : a(a_recopier.R_component_1()),
               b(a_recopier.R_component_2()),
               c(a_recopier.R_component_3()),
               d(a_recopier.R_component_4()) {}
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            BOOST_CONSTEXPR quaternion(quaternion && a_recopier)
               : a(std::move(a_recopier.R_component_1())),
               b(std::move(a_recopier.R_component_2())),
               c(std::move(a_recopier.R_component_3())),
               d(std::move(a_recopier.R_component_4())) {}
#endif
            
            // templated copy constructor
            
            template<typename X>
            BOOST_CONSTEXPR explicit            quaternion(quaternion<X> const & a_recopier)
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
            
            BOOST_CONSTEXPR T real() const
            {
               return(a);
            }

            BOOST_CONSTEXPR quaternion<T> unreal() const
            {
               return(quaternion<T>(static_cast<T>(0), b, c, d));
            }

            BOOST_CONSTEXPR T R_component_1() const
            {
               return(a);
            }

            BOOST_CONSTEXPR T R_component_2() const
            {
               return(b);
            }

            BOOST_CONSTEXPR T R_component_3() const
            {
               return(c);
            }

            BOOST_CONSTEXPR T R_component_4() const
            {
               return(d);
            }

            BOOST_CONSTEXPR ::std::complex<T> C_component_1() const
            {
               return(::std::complex<T>(a, b));
            }

            BOOST_CONSTEXPR ::std::complex<T> C_component_2() const
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
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            BOOST_CXX14_CONSTEXPR quaternion<T> &        operator = (quaternion<T> && a_affecter)
            {
               a = std::move(a_affecter.a);
               b = std::move(a_affecter.b);
               c = std::move(a_affecter.c);
               d = std::move(a_affecter.d);

               return(*this);
            }
#endif
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
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(T const & rhs, const boost::true_type&)
            {
               a += rhs;
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(T const & rhs, const boost::false_type&)
            {
               quaternion<T> result(a + rhs, b, c, d); // exception guard
               swap(result);
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(std::complex<T> const & rhs, const boost::true_type&)
            {
               a += std::real(rhs);
               b += std::imag(rhs);
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(std::complex<T> const & rhs, const boost::false_type&)
            {
               quaternion<T> result(a + std::real(rhs), b + std::imag(rhs), c, d); // exception guard
               swap(result);
               return *this;
            }
            template <class X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(quaternion<X> const & rhs, const boost::true_type&)
            {
               a += rhs.R_component_1();
               b += rhs.R_component_2();
               c += rhs.R_component_3();
               d += rhs.R_component_4();
               return *this;
            }
            template <class X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_add(quaternion<X> const & rhs, const boost::false_type&)
            {
               quaternion<T> result(a + rhs.R_component_1(), b + rhs.R_component_2(), c + rhs.R_component_3(), d + rhs.R_component_4()); // exception guard
               swap(result);
               return *this;
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(T const & rhs, const boost::true_type&)
            {
               a -= rhs;
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(T const & rhs, const boost::false_type&)
            {
               quaternion<T> result(a - rhs, b, c, d); // exception guard
               swap(result);
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(std::complex<T> const & rhs, const boost::true_type&)
            {
               a -= std::real(rhs);
               b -= std::imag(rhs);
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(std::complex<T> const & rhs, const boost::false_type&)
            {
               quaternion<T> result(a - std::real(rhs), b - std::imag(rhs), c, d); // exception guard
               swap(result);
               return *this;
            }
            template <class X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(quaternion<X> const & rhs, const boost::true_type&)
            {
               a -= rhs.R_component_1();
               b -= rhs.R_component_2();
               c -= rhs.R_component_3();
               d -= rhs.R_component_4();
               return *this;
            }
            template <class X>
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_subtract(quaternion<X> const & rhs, const boost::false_type&)
            {
               quaternion<T> result(a - rhs.R_component_1(), b - rhs.R_component_2(), c - rhs.R_component_3(), d - rhs.R_component_4()); // exception guard
               swap(result);
               return *this;
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_multiply(T const & rhs, const boost::true_type&)
            {
               a *= rhs;
               b *= rhs;
               c *= rhs;
               d *= rhs;
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_multiply(T const & rhs, const boost::false_type&)
            {
               quaternion<T> result(a * rhs, b * rhs, c * rhs, d * rhs); // exception guard
               swap(result);
               return *this;
            }

            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_divide(T const & rhs, const boost::true_type&)
            {
               a /= rhs;
               b /= rhs;
               c /= rhs;
               d /= rhs;
               return *this;
            }
            BOOST_CXX14_CONSTEXPR quaternion<T> &        do_divide(T const & rhs, const boost::false_type&)
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
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator + (const quaternion<T1>& a, const T2& b)
{
   return quaternion<T1>(static_cast<T1>(a.R_component_1() + b), a.R_component_2(), a.R_component_3(), a.R_component_4());
}
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator + (const T1& a, const quaternion<T2>& b)
{
   return quaternion<T2>(static_cast<T2>(b.R_component_1() + a), b.R_component_2(), b.R_component_3(), b.R_component_4());
}
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator + (const quaternion<T1>& a, const std::complex<T2>& b)
{
   return quaternion<T1>(a.R_component_1() + std::real(b), a.R_component_2() + std::imag(b), a.R_component_3(), a.R_component_4());
}
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator + (const std::complex<T1>& a, const quaternion<T2>& b)
{
   return quaternion<T1>(b.R_component_1() + real(a), b.R_component_2() + imag(a), b.R_component_3(), b.R_component_4());
}
template <class T>
inline BOOST_CONSTEXPR quaternion<T> operator + (const quaternion<T>& a, const quaternion<T>& b)
{
   return quaternion<T>(a.R_component_1() + b.R_component_1(), a.R_component_2() + b.R_component_2(), a.R_component_3() + b.R_component_3(), a.R_component_4() + b.R_component_4());
}
// operator-
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator - (const quaternion<T1>& a, const T2& b)
{
   return quaternion<T1>(static_cast<T1>(a.R_component_1() - b), a.R_component_2(), a.R_component_3(), a.R_component_4());
}
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator - (const T1& a, const quaternion<T2>& b)
{
   return quaternion<T2>(static_cast<T2>(a - b.R_component_1()), -b.R_component_2(), -b.R_component_3(), -b.R_component_4());
}
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator - (const quaternion<T1>& a, const std::complex<T2>& b)
{
   return quaternion<T1>(a.R_component_1() - std::real(b), a.R_component_2() - std::imag(b), a.R_component_3(), a.R_component_4());
}
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator - (const std::complex<T1>& a, const quaternion<T2>& b)
{
   return quaternion<T1>(real(a) - b.R_component_1(), imag(a) - b.R_component_2(), -b.R_component_3(), -b.R_component_4());
}
template <class T>
inline BOOST_CONSTEXPR quaternion<T> operator - (const quaternion<T>& a, const quaternion<T>& b)
{
   return quaternion<T>(a.R_component_1() - b.R_component_1(), a.R_component_2() - b.R_component_2(), a.R_component_3() - b.R_component_3(), a.R_component_4() - b.R_component_4());
}

// operator*
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator * (const quaternion<T1>& a, const T2& b)
{
   return quaternion<T1>(static_cast<T1>(a.R_component_1() * b), a.R_component_2() * b, a.R_component_3() * b, a.R_component_4() * b);
}
template <class T1, class T2>
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator * (const T1& a, const quaternion<T2>& b)
{
   return quaternion<T2>(static_cast<T2>(a * b.R_component_1()), a * b.R_component_2(), a * b.R_component_3(), a * b.R_component_4());
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator * (const quaternion<T1>& a, const std::complex<T2>& b)
{
   quaternion<T1> result(a);
   result *= b;
   return result;
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T1, T2>::value, quaternion<T2> >::type
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
inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator / (const quaternion<T1>& a, const T2& b)
{
   return quaternion<T1>(a.R_component_1() / b, a.R_component_2() / b, a.R_component_3() / b, a.R_component_4() / b);
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T1, T2>::value, quaternion<T2> >::type
operator / (const T1& a, const quaternion<T2>& b)
{
   quaternion<T2> result(a);
   result /= b;
   return result;
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T2, T1>::value, quaternion<T1> >::type
operator / (const quaternion<T1>& a, const std::complex<T2>& b)
{
   quaternion<T1> result(a);
   result /= b;
   return result;
}
template <class T1, class T2>
inline BOOST_CXX14_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<T1, T2>::value, quaternion<T2> >::type
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
        inline BOOST_CONSTEXPR const quaternion<T>&             operator + (quaternion<T> const & q)
        {
            return q;
        }
        
        
        template<typename T>
        inline BOOST_CONSTEXPR quaternion<T>                    operator - (quaternion<T> const & q)
        {
            return(quaternion<T>(-q.R_component_1(),-q.R_component_2(),-q.R_component_3(),-q.R_component_4()));
        }
        
        
        template<typename R, typename T>
        inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<R, T>::value, bool>::type operator == (R const & lhs, quaternion<T> const & rhs)
        {
            return    (
                        (rhs.R_component_1() == lhs)&&
                        (rhs.R_component_2() == static_cast<T>(0))&&
                        (rhs.R_component_3() == static_cast<T>(0))&&
                        (rhs.R_component_4() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T, typename R>
        inline BOOST_CONSTEXPR typename boost::enable_if_c<boost::is_convertible<R, T>::value, bool>::type operator == (quaternion<T> const & lhs, R const & rhs)
        {
           return rhs == lhs;
        }
        
        
        template<typename T>
        inline BOOST_CONSTEXPR bool                                operator == (::std::complex<T> const & lhs, quaternion<T> const & rhs)
        {
            return    (
                        (rhs.R_component_1() == lhs.real())&&
                        (rhs.R_component_2() == lhs.imag())&&
                        (rhs.R_component_3() == static_cast<T>(0))&&
                        (rhs.R_component_4() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T>
        inline BOOST_CONSTEXPR bool                                operator == (quaternion<T> const & lhs, ::std::complex<T> const & rhs)
        {
           return rhs == lhs;
        }
        
        
        template<typename T>
        inline BOOST_CONSTEXPR bool                                operator == (quaternion<T> const & lhs, quaternion<T> const & rhs)
        {
            return    (
                        (rhs.R_component_1() == lhs.R_component_1())&&
                        (rhs.R_component_2() == lhs.R_component_2())&&
                        (rhs.R_component_3() == lhs.R_component_3())&&
                        (rhs.R_component_4() == lhs.R_component_4())
                    );
        }
                
        template<typename R, typename T> inline BOOST_CONSTEXPR bool operator != (R const & lhs, quaternion<T> const & rhs) { return !(lhs == rhs); }
        template<typename T, typename R> inline BOOST_CONSTEXPR bool operator != (quaternion<T> const & lhs, R const & rhs) { return !(lhs == rhs); }
        template<typename T> inline BOOST_CONSTEXPR bool operator != (::std::complex<T> const & lhs, quaternion<T> const & rhs) { return !(lhs == rhs); }
        template<typename T> inline BOOST_CONSTEXPR bool operator != (quaternion<T> const & lhs, ::std::complex<T> const & rhs) { return !(lhs == rhs); }
        template<typename T> inline BOOST_CONSTEXPR bool operator != (quaternion<T> const & lhs, quaternion<T> const & rhs) { return !(lhs == rhs); }
        
        
        // Note:    we allow the following formats, with a, b, c, and d reals
        //            a
        //            (a), (a,b), (a,b,c), (a,b,c,d)
        //            (a,(c)), (a,(c,d)), ((a)), ((a),c), ((a),(c)), ((a),(c,d)), ((a,b)), ((a,b),c), ((a,b),(c)), ((a,b),(c,d))
        template<typename T, typename charT, class traits>
        ::std::basic_istream<charT,traits> &    operator >> (    ::std::basic_istream<charT,traits> & is,
                                                                quaternion<T> & q)
        {
            
#ifdef    BOOST_NO_STD_LOCALE
#else
            const ::std::ctype<charT> & ct = ::std::use_facet< ::std::ctype<charT> >(is.getloc());
#endif /* BOOST_NO_STD_LOCALE */
            
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
            
#ifdef    BOOST_NO_STD_LOCALE
            cc = ch;
#else
            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
            
            if    (cc == '(')                            // read "(", possible: (a), (a,b), (a,b,c), (a,b,c,d), (a,(c)), (a,(c,d)), ((a)), ((a),c), ((a),(c)), ((a),(c,d)), ((a,b)), ((a,b),c), ((a,b),(c)), ((a,b,),(c,d,))
            {
                is >> ch;                                    // get the second lexeme
                
                if    (!is.good())    goto finish;
                
#ifdef    BOOST_NO_STD_LOCALE
                cc = ch;
#else
                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                
                if    (cc == '(')                        // read "((", possible: ((a)), ((a),c), ((a),(c)), ((a),(c,d)), ((a,b)), ((a,b),c), ((a,b),(c)), ((a,b,),(c,d,))
                {
                    is.putback(ch);
                    
                    is >> u;                                // we extract the first and second components
                    a = u.real();
                    b = u.imag();
                    
                    if    (!is.good())    goto finish;
                    
                    is >> ch;                                // get the next lexeme
                    
                    if    (!is.good())    goto finish;
                    
#ifdef    BOOST_NO_STD_LOCALE
                    cc = ch;
#else
                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                    
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
                        
#ifdef    BOOST_NO_STD_LOCALE
                        cc = ch;
#else
                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                        
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
                    
#ifdef    BOOST_NO_STD_LOCALE
                    cc = ch;
#else
                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                    
                    if        (cc == ')')                    // format: (a)
                    {
                        q = quaternion<T>(a);
                    }
                    else if    (cc == ',')                // read "(a,", possible: (a,b), (a,b,c), (a,b,c,d), (a,(c)), (a,(c,d))
                    {
                        is >> ch;                            // get the fourth lexeme
                        
                        if    (!is.good())    goto finish;
                        
#ifdef    BOOST_NO_STD_LOCALE
                        cc = ch;
#else
                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                        
                        if    (cc == '(')                // read "(a,(", possible: (a,(c)), (a,(c,d))
                        {
                            is.putback(ch);
                            
                            is >> v;                        // we extract the third and fourth component
                            
                            c = v.real();
                            d = v.imag();
                            
                            if    (!is.good())    goto finish;
                            
                            is >> ch;                        // get the ninth lexeme
                            
                            if    (!is.good())    goto finish;
                            
#ifdef    BOOST_NO_STD_LOCALE
                            cc = ch;
#else
                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                            
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
                            
#ifdef    BOOST_NO_STD_LOCALE
                            cc = ch;
#else
                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                            
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
                                
#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
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
                                    
#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
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
#ifdef    BOOST_NO_STD_LOCALE
#else
            s.imbue(os.getloc());
#endif /* BOOST_NO_STD_LOCALE */
            s.precision(os.precision());
            
            s << '('    << q.R_component_1() << ','
                        << q.R_component_2() << ','
                        << q.R_component_3() << ','
                        << q.R_component_4() << ')';
            
            return os << s.str();
        }
        
        
        // values
        
        template<typename T>
        inline BOOST_CONSTEXPR T real(quaternion<T> const & q)
        {
            return(q.real());
        }
        
        
        template<typename T>
        inline BOOST_CONSTEXPR quaternion<T> unreal(quaternion<T> const & q)
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
        inline BOOST_CONSTEXPR quaternion<T> conj(quaternion<T> const & q)
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