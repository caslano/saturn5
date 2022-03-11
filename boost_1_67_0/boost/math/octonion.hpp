//    boost octonion.hpp header file

//  (C) Copyright Hubert Holin 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

// See http://www.boost.org for updates, documentation, and revision history.


#ifndef BOOST_OCTONION_HPP
#define BOOST_OCTONION_HPP

#include <boost/math/quaternion.hpp>
#include <valarray>


namespace boost
{
    namespace math
    {
    
#define    BOOST_OCTONION_ACCESSOR_GENERATOR(type)                      \
            type                        real() const                    \
            {                                                           \
                return(a);                                              \
            }                                                           \
                                                                        \
            octonion<type>                unreal() const                \
            {                                                           \
                return( octonion<type>(static_cast<type>(0),b,c,d,e,f,g,h));   \
            }                                                           \
                                                                        \
            type                            R_component_1() const       \
            {                                                           \
                return(a);                                              \
            }                                                           \
                                                                        \
            type                            R_component_2() const       \
            {                                                           \
                return(b);                                              \
            }                                                           \
                                                                        \
            type                            R_component_3() const       \
            {                                                           \
                return(c);                                              \
            }                                                           \
                                                                        \
            type                            R_component_4() const       \
            {                                                           \
                return(d);                                              \
            }                                                           \
                                                                        \
            type                            R_component_5() const       \
            {                                                           \
                return(e);                                              \
            }                                                           \
                                                                        \
            type                            R_component_6() const       \
            {                                                           \
                return(f);                                              \
            }                                                           \
                                                                        \
            type                            R_component_7() const       \
            {                                                           \
                return(g);                                              \
            }                                                           \
                                                                        \
            type                            R_component_8() const       \
            {                                                           \
                return(h);                                              \
            }                                                           \
                                                                        \
            ::std::complex<type>            C_component_1() const       \
            {                                                           \
                return(::std::complex<type>(a,b));                      \
            }                                                           \
                                                                        \
            ::std::complex<type>            C_component_2() const       \
            {                                                           \
                return(::std::complex<type>(c,d));                      \
            }                                                           \
                                                                        \
            ::std::complex<type>            C_component_3() const       \
            {                                                           \
                return(::std::complex<type>(e,f));                      \
            }                                                           \
                                                                        \
            ::std::complex<type>            C_component_4() const       \
            {                                                           \
                return(::std::complex<type>(g,h));                      \
            }                                                           \
                                                                        \
            ::boost::math::quaternion<type>    H_component_1() const    \
            {                                                           \
                return(::boost::math::quaternion<type>(a,b,c,d));       \
            }                                                           \
                                                                        \
            ::boost::math::quaternion<type>    H_component_2() const    \
            {                                                           \
                return(::boost::math::quaternion<type>(e,f,g,h));       \
            }
        
    
#define    BOOST_OCTONION_MEMBER_ASSIGNMENT_GENERATOR(type)                                         \
            template<typename X>                                                                    \
            octonion<type> &        operator = (octonion<X> const & a_affecter)                     \
            {                                                                                       \
                a = static_cast<type>(a_affecter.R_component_1());                                  \
                b = static_cast<type>(a_affecter.R_component_2());                                  \
                c = static_cast<type>(a_affecter.R_component_3());                                  \
                d = static_cast<type>(a_affecter.R_component_4());                                  \
                e = static_cast<type>(a_affecter.R_component_5());                                  \
                f = static_cast<type>(a_affecter.R_component_6());                                  \
                g = static_cast<type>(a_affecter.R_component_7());                                  \
                h = static_cast<type>(a_affecter.R_component_8());                                  \
                                                                                                    \
                return(*this);                                                                      \
            }                                                                                       \
                                                                                                    \
            octonion<type> &        operator = (octonion<type> const & a_affecter)                  \
            {                                                                                       \
                a = a_affecter.a;                                                                   \
                b = a_affecter.b;                                                                   \
                c = a_affecter.c;                                                                   \
                d = a_affecter.d;                                                                   \
                e = a_affecter.e;                                                                   \
                f = a_affecter.f;                                                                   \
                g = a_affecter.g;                                                                   \
                h = a_affecter.h;                                                                   \
                                                                                                    \
                return(*this);                                                                      \
            }                                                                                       \
                                                                                                    \
            octonion<type> &        operator = (type const & a_affecter)                            \
            {                                                                                       \
                a = a_affecter;                                                                     \
                                                                                                    \
                b = c = d = e = f= g = h = static_cast<type>(0);                                    \
                                                                                                    \
                return(*this);                                                                      \
            }                                                                                       \
                                                                                                    \
            octonion<type> &        operator = (::std::complex<type> const & a_affecter)            \
            {                                                                                       \
                a = a_affecter.real();                                                              \
                b = a_affecter.imag();                                                              \
                                                                                                    \
                c = d = e = f = g = h = static_cast<type>(0);                                       \
                                                                                                    \
                return(*this);                                                                      \
            }                                                                                       \
                                                                                                    \
            octonion<type> &        operator = (::boost::math::quaternion<type> const & a_affecter) \
            {                                                                                       \
                a = a_affecter.R_component_1();                                                     \
                b = a_affecter.R_component_2();                                                     \
                c = a_affecter.R_component_3();                                                     \
                d = a_affecter.R_component_4();                                                     \
                                                                                                    \
                e = f = g = h = static_cast<type>(0);                                               \
                                                                                                    \
                return(*this);                                                                      \
            }
        
        
#define    BOOST_OCTONION_MEMBER_DATA_GENERATOR(type) \
            type    a;                                \
            type    b;                                \
            type    c;                                \
            type    d;                                \
            type    e;                                \
            type    f;                                \
            type    g;                                \
            type    h;                                \
        
        
        template<typename T>
        class octonion
        {
        public:
            
            typedef T value_type;
            
            // constructor for O seen as R^8
            // (also default constructor)
            
            explicit                octonion(   T const & requested_a = T(),
                                                T const & requested_b = T(),
                                                T const & requested_c = T(),
                                                T const & requested_d = T(),
                                                T const & requested_e = T(),
                                                T const & requested_f = T(),
                                                T const & requested_g = T(),
                                                T const & requested_h = T())
            :   a(requested_a),
                b(requested_b),
                c(requested_c),
                d(requested_d),
                e(requested_e),
                f(requested_f),
                g(requested_g),
                h(requested_h)
            {
                // nothing to do!
            }
            
            
            // constructor for H seen as C^4
                
            explicit                octonion(   ::std::complex<T> const & z0,
                                                ::std::complex<T> const & z1 = ::std::complex<T>(),
                                                ::std::complex<T> const & z2 = ::std::complex<T>(),
                                                ::std::complex<T> const & z3 = ::std::complex<T>())
            :   a(z0.real()),
                b(z0.imag()),
                c(z1.real()),
                d(z1.imag()),
                e(z2.real()),
                f(z2.imag()),
                g(z3.real()),
                h(z3.imag())
            {
                // nothing to do!
            }
            
            
            // constructor for O seen as H^2
                
            explicit                octonion(   ::boost::math::quaternion<T> const & q0,
                                                ::boost::math::quaternion<T> const & q1 = ::boost::math::quaternion<T>())
            :   a(q0.R_component_1()),
                b(q0.R_component_2()),
                c(q0.R_component_3()),
                d(q0.R_component_4()),
                e(q1.R_component_1()),
                f(q1.R_component_2()),
                g(q1.R_component_3()),
                h(q1.R_component_4())
            {
                // nothing to do!
            }
            
            
            // UNtemplated copy constructor
            // (this is taken care of by the compiler itself)
            
            
            // templated copy constructor
            
            template<typename X>
            explicit                octonion(octonion<X> const & a_recopier)
            :   a(static_cast<T>(a_recopier.R_component_1())),
                b(static_cast<T>(a_recopier.R_component_2())),
                c(static_cast<T>(a_recopier.R_component_3())),
                d(static_cast<T>(a_recopier.R_component_4())),
                e(static_cast<T>(a_recopier.R_component_5())),
                f(static_cast<T>(a_recopier.R_component_6())),
                g(static_cast<T>(a_recopier.R_component_7())),
                h(static_cast<T>(a_recopier.R_component_8()))
            {
                // nothing to do!
            }
            
            
            // destructor
            // (this is taken care of by the compiler itself)
            
            
            // accessors
            //
            // Note:    Like complex number, octonions do have a meaningful notion of "real part",
            //            but unlike them there is no meaningful notion of "imaginary part".
            //            Instead there is an "unreal part" which itself is an octonion, and usually
            //            nothing simpler (as opposed to the complex number case).
            //            However, for practicality, there are accessors for the other components
            //            (these are necessary for the templated copy constructor, for instance).
            
            BOOST_OCTONION_ACCESSOR_GENERATOR(T)
            
            // assignment operators
            
            BOOST_OCTONION_MEMBER_ASSIGNMENT_GENERATOR(T)
            
            // other assignment-related operators
            //
            // NOTE:    Octonion multiplication is *NOT* commutative;
            //            symbolically, "q *= rhs;" means "q = q * rhs;"
            //            and "q /= rhs;" means "q = q * inverse_of(rhs);";
            //            octonion multiplication is also *NOT* associative
            
            octonion<T> &            operator += (T const & rhs)
            {
                T    at = a + rhs;    // exception guard
                
                a = at;
                
                return(*this);
            }
            
            
            octonion<T> &            operator += (::std::complex<T> const & rhs)
            {
                T    at = a + rhs.real();    // exception guard
                T    bt = b + rhs.imag();    // exception guard
                
                a = at; 
                b = bt;
                
                return(*this);
            }
            
            
            octonion<T> &            operator += (::boost::math::quaternion<T> const & rhs)
            {
                T    at = a + rhs.R_component_1();    // exception guard
                T    bt = b + rhs.R_component_2();    // exception guard
                T    ct = c + rhs.R_component_3();    // exception guard
                T    dt = d + rhs.R_component_4();    // exception guard
                
                a = at; 
                b = bt;
                c = ct;
                d = dt;
                
                return(*this);
            }
            
            
            template<typename X>
            octonion<T> &            operator += (octonion<X> const & rhs)
            {
                T    at = a + static_cast<T>(rhs.R_component_1());    // exception guard
                T    bt = b + static_cast<T>(rhs.R_component_2());    // exception guard
                T    ct = c + static_cast<T>(rhs.R_component_3());    // exception guard
                T    dt = d + static_cast<T>(rhs.R_component_4());    // exception guard
                T    et = e + static_cast<T>(rhs.R_component_5());    // exception guard
                T    ft = f + static_cast<T>(rhs.R_component_6());    // exception guard
                T    gt = g + static_cast<T>(rhs.R_component_7());    // exception guard
                T    ht = h + static_cast<T>(rhs.R_component_8());    // exception guard
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            
            octonion<T> &            operator -= (T const & rhs)
            {
                T    at = a - rhs;    // exception guard
                
                a = at;
                
                return(*this);
            }
            
            
            octonion<T> &            operator -= (::std::complex<T> const & rhs)
            {
                T    at = a - rhs.real();    // exception guard
                T    bt = b - rhs.imag();    // exception guard
                
                a = at; 
                b = bt;
                
                return(*this);
            }
            
            
            octonion<T> &            operator -= (::boost::math::quaternion<T> const & rhs)
            {
                T    at = a - rhs.R_component_1();    // exception guard
                T    bt = b - rhs.R_component_2();    // exception guard
                T    ct = c - rhs.R_component_3();    // exception guard
                T    dt = d - rhs.R_component_4();    // exception guard
                
                a = at; 
                b = bt;
                c = ct;
                d = dt;
                
                return(*this);
            }
            
            
            template<typename X>
            octonion<T> &            operator -= (octonion<X> const & rhs)
            {
                T    at = a - static_cast<T>(rhs.R_component_1());    // exception guard
                T    bt = b - static_cast<T>(rhs.R_component_2());    // exception guard
                T    ct = c - static_cast<T>(rhs.R_component_3());    // exception guard
                T    dt = d - static_cast<T>(rhs.R_component_4());    // exception guard
                T    et = e - static_cast<T>(rhs.R_component_5());    // exception guard
                T    ft = f - static_cast<T>(rhs.R_component_6());    // exception guard
                T    gt = g - static_cast<T>(rhs.R_component_7());    // exception guard
                T    ht = h - static_cast<T>(rhs.R_component_8());    // exception guard
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            octonion<T> &            operator *= (T const & rhs)
            {
                T    at = a * rhs;    // exception guard
                T    bt = b * rhs;    // exception guard
                T    ct = c * rhs;    // exception guard
                T    dt = d * rhs;    // exception guard
                T    et = e * rhs;    // exception guard
                T    ft = f * rhs;    // exception guard
                T    gt = g * rhs;    // exception guard
                T    ht = h * rhs;    // exception guard
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            octonion<T> &            operator *= (::std::complex<T> const & rhs)
            {
                T    ar = rhs.real();
                T    br = rhs.imag();
                
                T    at = +a*ar-b*br;
                T    bt = +a*br+b*ar;
                T    ct = +c*ar+d*br;
                T    dt = -c*br+d*ar;
                T    et = +e*ar+f*br;
                T    ft = -e*br+f*ar;
                T    gt = +g*ar-h*br;
                T    ht = +g*br+h*ar;
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            octonion<T> &            operator *= (::boost::math::quaternion<T> const & rhs)
            {
                T    ar = rhs.R_component_1();
                T    br = rhs.R_component_2();
                T    cr = rhs.R_component_2();
                T    dr = rhs.R_component_2();
                
                T    at = +a*ar-b*br-c*cr-d*dr;
                T    bt = +a*br+b*ar+c*dr-d*cr;
                T    ct = +a*cr-b*dr+c*ar+d*br;
                T    dt = +a*dr+b*cr-c*br+d*ar;
                T    et = +e*ar+f*br+g*cr+h*dr;
                T    ft = -e*br+f*ar-g*dr+h*cr;
                T    gt = -e*cr+f*dr+g*ar-h*br;
                T    ht = -e*dr-f*cr+g*br+h*ar;
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            template<typename X>
            octonion<T> &            operator *= (octonion<X> const & rhs)
            {
                T    ar = static_cast<T>(rhs.R_component_1());
                T    br = static_cast<T>(rhs.R_component_2());
                T    cr = static_cast<T>(rhs.R_component_3());
                T    dr = static_cast<T>(rhs.R_component_4());
                T    er = static_cast<T>(rhs.R_component_5());
                T    fr = static_cast<T>(rhs.R_component_6());
                T    gr = static_cast<T>(rhs.R_component_7());
                T    hr = static_cast<T>(rhs.R_component_8());
                
                T    at = +a*ar-b*br-c*cr-d*dr-e*er-f*fr-g*gr-h*hr;
                T    bt = +a*br+b*ar+c*dr-d*cr+e*fr-f*er-g*hr+h*gr;
                T    ct = +a*cr-b*dr+c*ar+d*br+e*gr+f*hr-g*er-h*fr;
                T    dt = +a*dr+b*cr-c*br+d*ar+e*hr-f*gr+g*fr-h*er;
                T    et = +a*er-b*fr-c*gr-d*hr+e*ar+f*br+g*cr+h*dr;
                T    ft = +a*fr+b*er-c*hr+d*gr-e*br+f*ar-g*dr+h*cr;
                T    gt = +a*gr+b*hr+c*er-d*fr-e*cr+f*dr+g*ar-h*br;
                T    ht = +a*hr-b*gr+c*fr+d*er-e*dr-f*cr+g*br+h*ar;
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            octonion<T> &            operator /= (T const & rhs)
            {
                T    at = a / rhs;    // exception guard
                T    bt = b / rhs;    // exception guard
                T    ct = c / rhs;    // exception guard
                T    dt = d / rhs;    // exception guard
                T    et = e / rhs;    // exception guard
                T    ft = f / rhs;    // exception guard
                T    gt = g / rhs;    // exception guard
                T    ht = h / rhs;    // exception guard
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            octonion<T> &            operator /= (::std::complex<T> const & rhs)
            {
                T    ar = rhs.real();
                T    br = rhs.imag();
                
                T    denominator = ar*ar+br*br;
                
                T    at = (+a*ar-b*br)/denominator;
                T    bt = (-a*br+b*ar)/denominator;
                T    ct = (+c*ar-d*br)/denominator;
                T    dt = (+c*br+d*ar)/denominator;
                T    et = (+e*ar-f*br)/denominator;
                T    ft = (+e*br+f*ar)/denominator;
                T    gt = (+g*ar+h*br)/denominator;
                T    ht = (+g*br+h*ar)/denominator;
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            octonion<T> &            operator /= (::boost::math::quaternion<T> const & rhs)
            {
                T    ar = rhs.R_component_1();
                T    br = rhs.R_component_2();
                T    cr = rhs.R_component_2();
                T    dr = rhs.R_component_2();
                
                T    denominator = ar*ar+br*br+cr*cr+dr*dr;
                
                T    at = (+a*ar+b*br+c*cr+d*dr)/denominator;
                T    bt = (-a*br+b*ar-c*dr+d*cr)/denominator;
                T    ct = (-a*cr+b*dr+c*ar-d*br)/denominator;
                T    dt = (-a*dr-b*cr+c*br+d*ar)/denominator;
                T    et = (+e*ar-f*br-g*cr-h*dr)/denominator;
                T    ft = (+e*br+f*ar+g*dr-h*cr)/denominator;
                T    gt = (+e*cr-f*dr+g*ar+h*br)/denominator;
                T    ht = (+e*dr+f*cr-g*br+h*ar)/denominator;
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
            template<typename X>
            octonion<T> &            operator /= (octonion<X> const & rhs)
            {
                T    ar = static_cast<T>(rhs.R_component_1());
                T    br = static_cast<T>(rhs.R_component_2());
                T    cr = static_cast<T>(rhs.R_component_3());
                T    dr = static_cast<T>(rhs.R_component_4());
                T    er = static_cast<T>(rhs.R_component_5());
                T    fr = static_cast<T>(rhs.R_component_6());
                T    gr = static_cast<T>(rhs.R_component_7());
                T    hr = static_cast<T>(rhs.R_component_8());
                
                T    denominator = ar*ar+br*br+cr*cr+dr*dr+er*er+fr*fr+gr*gr+hr*hr;
                
                T    at = (+a*ar+b*br+c*cr+d*dr+e*er+f*fr+g*gr+h*hr)/denominator;
                T    bt = (-a*br+b*ar-c*dr+d*cr-e*fr+f*er+g*hr-h*gr)/denominator;
                T    ct = (-a*cr+b*dr+c*ar-d*br-e*gr-f*hr+g*er+h*fr)/denominator;
                T    dt = (-a*dr-b*cr+c*br+d*ar-e*hr+f*gr-g*fr+h*er)/denominator;
                T    et = (-a*er+b*fr+c*gr+d*hr+e*ar-f*br-g*cr-h*dr)/denominator;
                T    ft = (-a*fr-b*er+c*hr-d*gr+e*br+f*ar+g*dr-h*cr)/denominator;
                T    gt = (-a*gr-b*hr-c*er+d*fr+e*cr-f*dr+g*ar+h*br)/denominator;
                T    ht = (-a*hr+b*gr-c*fr-d*er+e*dr+f*cr-g*br+h*ar)/denominator;
                
                a = at;
                b = bt;
                c = ct;
                d = dt;
                e = et;
                f = ft;
                g = gt;
                h = ht;
                
                return(*this);
            }
            
            
        protected:
            
            BOOST_OCTONION_MEMBER_DATA_GENERATOR(T)
            
            
        private:
            
        };
        
        
        // declaration of octonion specialization
        
        template<>    class octonion<float>;
        template<>    class octonion<double>;
        template<>    class octonion<long double>;
        
        
        // helper templates for converting copy constructors (declaration)
        
        namespace detail
        {
            
            template<   typename T,
                        typename U
                    >
            octonion<T>    octonion_type_converter(octonion<U> const & rhs);
        }
        
        
        // implementation of octonion specialization
        
        
#define    BOOST_OCTONION_CONSTRUCTOR_GENERATOR(type)                                                                               \
            explicit                    octonion(   type const & requested_a = static_cast<type>(0),                                \
                                                    type const & requested_b = static_cast<type>(0),                                \
                                                    type const & requested_c = static_cast<type>(0),                                \
                                                    type const & requested_d = static_cast<type>(0),                                \
                                                    type const & requested_e = static_cast<type>(0),                                \
                                                    type const & requested_f = static_cast<type>(0),                                \
                                                    type const & requested_g = static_cast<type>(0),                                \
                                                    type const & requested_h = static_cast<type>(0))                                \
            :   a(requested_a),                                                                                                     \
                b(requested_b),                                                                                                     \
                c(requested_c),                                                                                                     \
                d(requested_d),                                                                                                     \
                e(requested_e),                                                                                                     \
                f(requested_f),                                                                                                     \
                g(requested_g),                                                                                                     \
                h(requested_h)                                                                                                      \
            {                                                                                                                       \
            }                                                                                                                       \
                                                                                                                                    \
            explicit                    octonion(   ::std::complex<type> const & z0,                                                \
                                                    ::std::complex<type> const & z1 = ::std::complex<type>(),                       \
                                                    ::std::complex<type> const & z2 = ::std::complex<type>(),                       \
                                                    ::std::complex<type> const & z3 = ::std::complex<type>())                       \
            :   a(z0.real()),                                                                                                       \
                b(z0.imag()),                                                                                                       \
                c(z1.real()),                                                                                                       \
                d(z1.imag()),                                                                                                       \
                e(z2.real()),                                                                                                       \
                f(z2.imag()),                                                                                                       \
                g(z3.real()),                                                                                                       \
                h(z3.imag())                                                                                                        \
            {                                                                                                                       \
            }                                                                                                                       \
                                                                                                                                    \
            explicit                    octonion(   ::boost::math::quaternion<type> const & q0,                                     \
                                                    ::boost::math::quaternion<type> const & q1 = ::boost::math::quaternion<type>()) \
            :   a(q0.R_component_1()),                                                                                              \
                b(q0.R_component_2()),                                                                                              \
                c(q0.R_component_3()),                                                                                              \
                d(q0.R_component_4()),                                                                                              \
                e(q1.R_component_1()),                                                                                              \
                f(q1.R_component_2()),                                                                                              \
                g(q1.R_component_3()),                                                                                              \
                h(q1.R_component_4())                                                                                               \
            {                                                                                                                       \
            }
        
    
#define    BOOST_OCTONION_MEMBER_ADD_GENERATOR_1(type)                  \
            octonion<type> &            operator += (type const & rhs)  \
            {                                                           \
                a += rhs;                                               \
                                                                        \
                return(*this);                                          \
            }
    
#define    BOOST_OCTONION_MEMBER_ADD_GENERATOR_2(type)                                  \
            octonion<type> &            operator += (::std::complex<type> const & rhs)  \
            {                                                                           \
                a += rhs.real();                                                        \
                b += rhs.imag();                                                        \
                                                                                        \
                return(*this);                                                          \
            }
    
#define    BOOST_OCTONION_MEMBER_ADD_GENERATOR_3(type)                                              \
            octonion<type> &            operator += (::boost::math::quaternion<type> const & rhs)   \
            {                                                                                       \
                a += rhs.R_component_1();                                                           \
                b += rhs.R_component_2();                                                           \
                c += rhs.R_component_3();                                                           \
                d += rhs.R_component_4();                                                           \
                                                                                                    \
                return(*this);                                                                      \
            }
    
#define    BOOST_OCTONION_MEMBER_ADD_GENERATOR_4(type)                          \
            template<typename X>                                                \
            octonion<type> &            operator += (octonion<X> const & rhs)   \
            {                                                                   \
                a += static_cast<type>(rhs.R_component_1());                    \
                b += static_cast<type>(rhs.R_component_2());                    \
                c += static_cast<type>(rhs.R_component_3());                    \
                d += static_cast<type>(rhs.R_component_4());                    \
                e += static_cast<type>(rhs.R_component_5());                    \
                f += static_cast<type>(rhs.R_component_6());                    \
                g += static_cast<type>(rhs.R_component_7());                    \
                h += static_cast<type>(rhs.R_component_8());                    \
                                                                                \
                return(*this);                                                  \
            }
    
#define    BOOST_OCTONION_MEMBER_SUB_GENERATOR_1(type)                  \
            octonion<type> &            operator -= (type const & rhs)  \
            {                                                           \
                a -= rhs;                                               \
                                                                        \
                return(*this);                                          \
            }
    
#define    BOOST_OCTONION_MEMBER_SUB_GENERATOR_2(type)                                  \
            octonion<type> &            operator -= (::std::complex<type> const & rhs)  \
            {                                                                           \
                a -= rhs.real();                                                        \
                b -= rhs.imag();                                                        \
                                                                                        \
                return(*this);                                                          \
            }
    
#define    BOOST_OCTONION_MEMBER_SUB_GENERATOR_3(type)                                              \
            octonion<type> &            operator -= (::boost::math::quaternion<type> const & rhs)   \
            {                                                                                       \
                a -= rhs.R_component_1();                                                           \
                b -= rhs.R_component_2();                                                           \
                c -= rhs.R_component_3();                                                           \
                d -= rhs.R_component_4();                                                           \
                                                                                                    \
                return(*this);                                                                      \
            }
    
#define    BOOST_OCTONION_MEMBER_SUB_GENERATOR_4(type)                        \
            template<typename X>                                              \
            octonion<type> &            operator -= (octonion<X> const & rhs) \
            {                                                                 \
                a -= static_cast<type>(rhs.R_component_1());                  \
                b -= static_cast<type>(rhs.R_component_2());                  \
                c -= static_cast<type>(rhs.R_component_3());                  \
                d -= static_cast<type>(rhs.R_component_4());                  \
                e -= static_cast<type>(rhs.R_component_5());                  \
                f -= static_cast<type>(rhs.R_component_6());                  \
                g -= static_cast<type>(rhs.R_component_7());                  \
                h -= static_cast<type>(rhs.R_component_8());                  \
                                                                              \
                return(*this);                                                \
            }
    
#define    BOOST_OCTONION_MEMBER_MUL_GENERATOR_1(type)                   \
            octonion<type> &            operator *= (type const & rhs)   \
            {                                                            \
                a *= rhs;                                                \
                b *= rhs;                                                \
                c *= rhs;                                                \
                d *= rhs;                                                \
                e *= rhs;                                                \
                f *= rhs;                                                \
                g *= rhs;                                                \
                h *= rhs;                                                \
                                                                         \
                return(*this);                                           \
            }
    
#define    BOOST_OCTONION_MEMBER_MUL_GENERATOR_2(type)                                  \
            octonion<type> &            operator *= (::std::complex<type> const & rhs)  \
            {                                                                           \
                type    ar = rhs.real();                                                \
                type    br = rhs.imag();                                                \
                                                                                        \
                type    at = +a*ar-b*br;                                                \
                type    bt = +a*br+b*ar;                                                \
                type    ct = +c*ar+d*br;                                                \
                type    dt = -c*br+d*ar;                                                \
                type    et = +e*ar+f*br;                                                \
                type    ft = -e*br+f*ar;                                                \
                type    gt = +g*ar-h*br;                                                \
                type    ht = +g*br+h*ar;                                                \
                                                                                        \
                a = at;                                                                 \
                b = bt;                                                                 \
                c = ct;                                                                 \
                d = dt;                                                                 \
                e = et;                                                                 \
                f = ft;                                                                 \
                g = gt;                                                                 \
                h = ht;                                                                 \
                                                                                        \
                return(*this);                                                          \
            }
    
#define    BOOST_OCTONION_MEMBER_MUL_GENERATOR_3(type)                                                    \
            octonion<type> &            operator *= (::boost::math::quaternion<type> const & rhs)   \
            {                                                                                       \
                type    ar = rhs.R_component_1();                                                   \
                type    br = rhs.R_component_2();                                                   \
                type    cr = rhs.R_component_2();                                                   \
                type    dr = rhs.R_component_2();                                                   \
                                                                                                    \
                type    at = +a*ar-b*br-c*cr-d*dr;                                                  \
                type    bt = +a*br+b*ar+c*dr-d*cr;                                                  \
                type    ct = +a*cr-b*dr+c*ar+d*br;                                                  \
                type    dt = +a*dr+b*cr-c*br+d*ar;                                                  \
                type    et = +e*ar+f*br+g*cr+h*dr;                                                  \
                type    ft = -e*br+f*ar-g*dr+h*cr;                                                  \
                type    gt = -e*cr+f*dr+g*ar-h*br;                                                  \
                type    ht = -e*dr-f*cr+g*br+h*ar;                                                  \
                                                                                                    \
                a = at;                                                                             \
                b = bt;                                                                             \
                c = ct;                                                                             \
                d = dt;                                                                             \
                e = et;                                                                             \
                f = ft;                                                                             \
                g = gt;                                                                             \
                h = ht;                                                                             \
                                                                                                    \
                return(*this);                                                                      \
            }
    
#define    BOOST_OCTONION_MEMBER_MUL_GENERATOR_4(type)                          \
            template<typename X>                                                \
            octonion<type> &            operator *= (octonion<X> const & rhs)   \
            {                                                                   \
                type    ar = static_cast<type>(rhs.R_component_1());            \
                type    br = static_cast<type>(rhs.R_component_2());            \
                type    cr = static_cast<type>(rhs.R_component_3());            \
                type    dr = static_cast<type>(rhs.R_component_4());            \
                type    er = static_cast<type>(rhs.R_component_5());            \
                type    fr = static_cast<type>(rhs.R_component_6());            \
                type    gr = static_cast<type>(rhs.R_component_7());            \
                type    hr = static_cast<type>(rhs.R_component_8());            \
                                                                                \
                type    at = +a*ar-b*br-c*cr-d*dr-e*er-f*fr-g*gr-h*hr;          \
                type    bt = +a*br+b*ar+c*dr-d*cr+e*fr-f*er-g*hr+h*gr;          \
                type    ct = +a*cr-b*dr+c*ar+d*br+e*gr+f*hr-g*er-h*fr;          \
                type    dt = +a*dr+b*cr-c*br+d*ar+e*hr-f*gr+g*fr-h*er;          \
                type    et = +a*er-b*fr-c*gr-d*hr+e*ar+f*br+g*cr+h*dr;          \
                type    ft = +a*fr+b*er-c*hr+d*gr-e*br+f*ar-g*dr+h*cr;          \
                type    gt = +a*gr+b*hr+c*er-d*fr-e*cr+f*dr+g*ar-h*br;          \
                type    ht = +a*hr-b*gr+c*fr+d*er-e*dr-f*cr+g*br+h*ar;          \
                                                                                \
                a = at;                                                         \
                b = bt;                                                         \
                c = ct;                                                         \
                d = dt;                                                         \
                e = et;                                                         \
                f = ft;                                                         \
                g = gt;                                                         \
                h = ht;                                                         \
                                                                                \
                return(*this);                                                  \
            }
    
// There is quite a lot of repetition in the code below. This is intentional.
// The last conditional block is the normal form, and the others merely
// consist of workarounds for various compiler deficiencies. Hopefully, when
// more compilers are conformant and we can retire support for those that are
// not, we will be able to remove the clutter. This is makes the situation
// (painfully) explicit.
    
#define    BOOST_OCTONION_MEMBER_DIV_GENERATOR_1(type)                  \
            octonion<type> &            operator /= (type const & rhs)  \
            {                                                           \
                a /= rhs;                                               \
                b /= rhs;                                               \
                c /= rhs;                                               \
                d /= rhs;                                               \
                                                                        \
                return(*this);                                          \
            }
    
#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    #define    BOOST_OCTONION_MEMBER_DIV_GENERATOR_2(type)                              \
            octonion<type> &            operator /= (::std::complex<type> const & rhs)  \
            {                                                                           \
                using    ::std::valarray;                                               \
                using    ::std::abs;                                                    \
                                                                                        \
                valarray<type>    tr(2);                                                \
                                                                                        \
                tr[0] = rhs.real();                                                     \
                tr[1] = rhs.imag();                                                     \
                                                                                        \
                type            mixam = static_cast<type>(1)/(abs(tr).max)();           \
                                                                                        \
                tr *= mixam;                                                            \
                                                                                        \
                valarray<type>    tt(8);                                                \
                                                                                        \
                tt[0] = +a*tr[0]-b*tr[1];                                               \
                tt[1] = -a*tr[1]+b*tr[0];                                               \
                tt[2] = +c*tr[0]-d*tr[1];                                               \
                tt[3] = +c*tr[1]+d*tr[0];                                               \
                tt[4] = +e*tr[0]-f*tr[1];                                               \
                tt[5] = +e*tr[1]+f*tr[0];                                               \
                tt[6] = +g*tr[0]+h*tr[1];                                               \
                tt[7] = +g*tr[1]+h*tr[0];                                               \
                                                                                        \
                tr *= tr;                                                               \
                                                                                        \
                tt *= (mixam/tr.sum());                                                 \
                                                                                        \
                a = tt[0];                                                              \
                b = tt[1];                                                              \
                c = tt[2];                                                              \
                d = tt[3];                                                              \
                e = tt[4];                                                              \
                f = tt[5];                                                              \
                g = tt[6];                                                              \
                h = tt[7];                                                              \
                                                                                        \
                return(*this);                                                          \
            }
#else
    #define    BOOST_OCTONION_MEMBER_DIV_GENERATOR_2(type)                              \
            octonion<type> &            operator /= (::std::complex<type> const & rhs)  \
            {                                                                           \
                using    ::std::valarray;                                               \
                                                                                        \
                valarray<type>    tr(2);                                                \
                                                                                        \
                tr[0] = rhs.real();                                                     \
                tr[1] = rhs.imag();                                                     \
                                                                                        \
                type            mixam = static_cast<type>(1)/(abs(tr).max)();           \
                                                                                        \
                tr *= mixam;                                                            \
                                                                                        \
                valarray<type>    tt(8);                                                \
                                                                                        \
                tt[0] = +a*tr[0]-b*tr[1];                                               \
                tt[1] = -a*tr[1]+b*tr[0];                                               \
                tt[2] = +c*tr[0]-d*tr[1];                                               \
                tt[3] = +c*tr[1]+d*tr[0];                                               \
                tt[4] = +e*tr[0]-f*tr[1];                                               \
                tt[5] = +e*tr[1]+f*tr[0];                                               \
                tt[6] = +g*tr[0]+h*tr[1];                                               \
                tt[7] = +g*tr[1]+h*tr[0];                                               \
                                                                                        \
                tr *= tr;                                                               \
                                                                                        \
                tt *= (mixam/tr.sum());                                                 \
                                                                                        \
                a = tt[0];                                                              \
                b = tt[1];                                                              \
                c = tt[2];                                                              \
                d = tt[3];                                                              \
                e = tt[4];                                                              \
                f = tt[5];                                                              \
                g = tt[6];                                                              \
                h = tt[7];                                                              \
                                                                                        \
                return(*this);                                                          \
            }
#endif /* BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP */
    
#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    #define    BOOST_OCTONION_MEMBER_DIV_GENERATOR_3(type)                                           \
            octonion<type> &            operator /= (::boost::math::quaternion<type> const & rhs)    \
            {                                                                                        \
                using    ::std::valarray;                                                            \
                using    ::std::abs;                                                                 \
                                                                                                     \
                valarray<type>    tr(4);                                                             \
                                                                                                     \
                tr[0] = static_cast<type>(rhs.R_component_1());                                      \
                tr[1] = static_cast<type>(rhs.R_component_2());                                      \
                tr[2] = static_cast<type>(rhs.R_component_3());                                      \
                tr[3] = static_cast<type>(rhs.R_component_4());                                      \
                                                                                                     \
                type            mixam = static_cast<type>(1)/(abs(tr).max)();                        \
                                                                                                     \
                tr *= mixam;                                                                         \
                                                                                                     \
                valarray<type>    tt(8);                                                             \
                                                                                                     \
                tt[0] = +a*tr[0]+b*tr[1]+c*tr[2]+d*tr[3];                                            \
                tt[1] = -a*tr[1]+b*tr[0]-c*tr[3]+d*tr[2];                                            \
                tt[2] = -a*tr[2]+b*tr[3]+c*tr[0]-d*tr[1];                                            \
                tt[3] = -a*tr[3]-b*tr[2]+c*tr[1]+d*tr[0];                                            \
                tt[4] = +e*tr[0]-f*tr[1]-g*tr[2]-h*tr[3];                                            \
                tt[5] = +e*tr[1]+f*tr[0]+g*tr[3]-h*tr[2];                                            \
                tt[6] = +e*tr[2]-f*tr[3]+g*tr[0]+h*tr[1];                                            \
                tt[7] = +e*tr[3]+f*tr[2]-g*tr[1]+h*tr[0];                                            \
                                                                                                     \
                tr *= tr;                                                                            \
                                                                                                     \
                tt *= (mixam/tr.sum());                                                              \
                                                                                                     \
                a = tt[0];                                                                           \
                b = tt[1];                                                                           \
                c = tt[2];                                                                           \
                d = tt[3];                                                                           \
                e = tt[4];                                                                           \
                f = tt[5];                                                                           \
                g = tt[6];                                                                           \
                h = tt[7];                                                                           \
                                                                                                     \
                return(*this);                                                                       \
            }
#else
    #define    BOOST_OCTONION_MEMBER_DIV_GENERATOR_3(type)                                           \
            octonion<type> &            operator /= (::boost::math::quaternion<type> const & rhs)    \
            {                                                                                        \
                using    ::std::valarray;                                                            \
                                                                                                     \
                valarray<type>    tr(4);                                                             \
                                                                                                     \
                tr[0] = static_cast<type>(rhs.R_component_1());                                      \
                tr[1] = static_cast<type>(rhs.R_component_2());                                      \
                tr[2] = static_cast<type>(rhs.R_component_3());                                      \
                tr[3] = static_cast<type>(rhs.R_component_4());                                      \
                                                                                                     \
                type            mixam = static_cast<type>(1)/(abs(tr).max)();                        \
                                                                                                     \
                tr *= mixam;                                                                         \
                                                                                                     \
                valarray<type>    tt(8);                                                             \
                                                                                                     \
                tt[0] = +a*tr[0]+b*tr[1]+c*tr[2]+d*tr[3];                                            \
                tt[1] = -a*tr[1]+b*tr[0]-c*tr[3]+d*tr[2];                                            \
                tt[2] = -a*tr[2]+b*tr[3]+c*tr[0]-d*tr[1];                                            \
                tt[3] = -a*tr[3]-b*tr[2]+c*tr[1]+d*tr[0];                                            \
                tt[4] = +e*tr[0]-f*tr[1]-g*tr[2]-h*tr[3];                                            \
                tt[5] = +e*tr[1]+f*tr[0]+g*tr[3]-h*tr[2];                                            \
                tt[6] = +e*tr[2]-f*tr[3]+g*tr[0]+h*tr[1];                                            \
                tt[7] = +e*tr[3]+f*tr[2]-g*tr[1]+h*tr[0];                                            \
                                                                                                     \
                tr *= tr;                                                                            \
                                                                                                     \
                tt *= (mixam/tr.sum());                                                              \
                                                                                                     \
                a = tt[0];                                                                           \
                b = tt[1];                                                                           \
                c = tt[2];                                                                           \
                d = tt[3];                                                                           \
                e = tt[4];                                                                           \
                f = tt[5];                                                                           \
                g = tt[6];                                                                           \
                h = tt[7];                                                                           \
                                                                                                     \
                return(*this);                                                                       \
            }
#endif /* BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP */
    
#if defined(BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP)
    #define    BOOST_OCTONION_MEMBER_DIV_GENERATOR_4(type)                                           \
            template<typename X>                                                                     \
            octonion<type> &            operator /= (octonion<X> const & rhs)                        \
            {                                                                                        \
                using    ::std::valarray;                                                            \
                using    ::std::abs;                                                                 \
                                                                                                     \
                valarray<type>    tr(8);                                                             \
                                                                                                     \
                tr[0] = static_cast<type>(rhs.R_component_1());                                      \
                tr[1] = static_cast<type>(rhs.R_component_2());                                      \
                tr[2] = static_cast<type>(rhs.R_component_3());                                      \
                tr[3] = static_cast<type>(rhs.R_component_4());                                      \
                tr[4] = static_cast<type>(rhs.R_component_5());                                      \
                tr[5] = static_cast<type>(rhs.R_component_6());                                      \
                tr[6] = static_cast<type>(rhs.R_component_7());                                      \
                tr[7] = static_cast<type>(rhs.R_component_8());                                      \
                                                                                                     \
                type            mixam = static_cast<type>(1)/(abs(tr).max)();                        \
                                                                                                     \
                tr *= mixam;                                                                         \
                                                                                                     \
                valarray<type>    tt(8);                                                             \
                                                                                                     \
                tt[0] = +a*tr[0]+b*tr[1]+c*tr[2]+d*tr[3]+e*tr[4]+f*tr[5]+g*tr[6]+h*tr[7];            \
                tt[1] = -a*tr[1]+b*tr[0]-c*tr[3]+d*tr[2]-e*tr[5]+f*tr[4]+g*tr[7]-h*tr[6];            \
                tt[2] = -a*tr[2]+b*tr[3]+c*tr[0]-d*tr[1]-e*tr[6]-f*tr[7]+g*tr[4]+h*tr[5];            \
                tt[3] = -a*tr[3]-b*tr[2]+c*tr[1]+d*tr[0]-e*tr[7]+f*tr[6]-g*tr[5]+h*tr[4];            \
                tt[4] = -a*tr[4]+b*tr[5]+c*tr[6]+d*tr[7]+e*tr[0]-f*tr[1]-g*tr[2]-h*tr[3];            \
                tt[5] = -a*tr[5]-b*tr[4]+c*tr[7]-d*tr[6]+e*tr[1]+f*tr[0]+g*tr[3]-h*tr[2];            \
                tt[6] = -a*tr[6]-b*tr[7]-c*tr[4]+d*tr[5]+e*tr[2]-f*tr[3]+g*tr[0]+h*tr[1];            \
                tt[7] = -a*tr[7]+b*tr[6]-c*tr[5]-d*tr[4]+e*tr[3]+f*tr[2]-g*tr[1]+h*tr[0];            \
                                                                                                     \
                tr *= tr;                                                                            \
                                                                                                     \
                tt *= (mixam/tr.sum());                                                              \
                                                                                                     \
                a = tt[0];                                                                           \
                b = tt[1];                                                                           \
                c = tt[2];                                                                           \
                d = tt[3];                                                                           \
                e = tt[4];                                                                           \
                f = tt[5];                                                                           \
                g = tt[6];                                                                           \
                h = tt[7];                                                                           \
                                                                                                     \
                return(*this);                                                                       \
            }
#else
    #define    BOOST_OCTONION_MEMBER_DIV_GENERATOR_4(type)                                           \
            template<typename X>                                                                     \
            octonion<type> &            operator /= (octonion<X> const & rhs)                        \
            {                                                                                        \
                using    ::std::valarray;                                                            \
                                                                                                     \
                valarray<type>    tr(8);                                                             \
                                                                                                     \
                tr[0] = static_cast<type>(rhs.R_component_1());                                      \
                tr[1] = static_cast<type>(rhs.R_component_2());                                      \
                tr[2] = static_cast<type>(rhs.R_component_3());                                      \
                tr[3] = static_cast<type>(rhs.R_component_4());                                      \
                tr[4] = static_cast<type>(rhs.R_component_5());                                      \
                tr[5] = static_cast<type>(rhs.R_component_6());                                      \
                tr[6] = static_cast<type>(rhs.R_component_7());                                      \
                tr[7] = static_cast<type>(rhs.R_component_8());                                      \
                                                                                                     \
                type            mixam = static_cast<type>(1)/(abs(tr).max)();                        \
                                                                                                     \
                tr *= mixam;                                                                         \
                                                                                                     \
                valarray<type>    tt(8);                                                             \
                                                                                                     \
                tt[0] = +a*tr[0]+b*tr[1]+c*tr[2]+d*tr[3]+e*tr[4]+f*tr[5]+g*tr[6]+h*tr[7];            \
                tt[1] = -a*tr[1]+b*tr[0]-c*tr[3]+d*tr[2]-e*tr[5]+f*tr[4]+g*tr[7]-h*tr[6];            \
                tt[2] = -a*tr[2]+b*tr[3]+c*tr[0]-d*tr[1]-e*tr[6]-f*tr[7]+g*tr[4]+h*tr[5];            \
                tt[3] = -a*tr[3]-b*tr[2]+c*tr[1]+d*tr[0]-e*tr[7]+f*tr[6]-g*tr[5]+h*tr[4];            \
                tt[4] = -a*tr[4]+b*tr[5]+c*tr[6]+d*tr[7]+e*tr[0]-f*tr[1]-g*tr[2]-h*tr[3];            \
                tt[5] = -a*tr[5]-b*tr[4]+c*tr[7]-d*tr[6]+e*tr[1]+f*tr[0]+g*tr[3]-h*tr[2];            \
                tt[6] = -a*tr[6]-b*tr[7]-c*tr[4]+d*tr[5]+e*tr[2]-f*tr[3]+g*tr[0]+h*tr[1];            \
                tt[7] = -a*tr[7]+b*tr[6]-c*tr[5]-d*tr[4]+e*tr[3]+f*tr[2]-g*tr[1]+h*tr[0];            \
                                                                                                     \
                tr *= tr;                                                                            \
                                                                                                     \
                tt *= (mixam/tr.sum());                                                              \
                                                                                                     \
                a = tt[0];                                                                           \
                b = tt[1];                                                                           \
                c = tt[2];                                                                           \
                d = tt[3];                                                                           \
                e = tt[4];                                                                           \
                f = tt[5];                                                                           \
                g = tt[6];                                                                           \
                h = tt[7];                                                                           \
                                                                                                     \
                return(*this);                                                                       \
            }
#endif /* BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP */
    
    
#define    BOOST_OCTONION_MEMBER_ADD_GENERATOR(type)       \
        BOOST_OCTONION_MEMBER_ADD_GENERATOR_1(type)        \
        BOOST_OCTONION_MEMBER_ADD_GENERATOR_2(type)        \
        BOOST_OCTONION_MEMBER_ADD_GENERATOR_3(type)        \
        BOOST_OCTONION_MEMBER_ADD_GENERATOR_4(type)
        
#define    BOOST_OCTONION_MEMBER_SUB_GENERATOR(type)       \
        BOOST_OCTONION_MEMBER_SUB_GENERATOR_1(type)        \
        BOOST_OCTONION_MEMBER_SUB_GENERATOR_2(type)        \
        BOOST_OCTONION_MEMBER_SUB_GENERATOR_3(type)        \
        BOOST_OCTONION_MEMBER_SUB_GENERATOR_4(type)
        
#define    BOOST_OCTONION_MEMBER_MUL_GENERATOR(type)       \
        BOOST_OCTONION_MEMBER_MUL_GENERATOR_1(type)        \
        BOOST_OCTONION_MEMBER_MUL_GENERATOR_2(type)        \
        BOOST_OCTONION_MEMBER_MUL_GENERATOR_3(type)        \
        BOOST_OCTONION_MEMBER_MUL_GENERATOR_4(type)
        
#define    BOOST_OCTONION_MEMBER_DIV_GENERATOR(type)       \
        BOOST_OCTONION_MEMBER_DIV_GENERATOR_1(type)        \
        BOOST_OCTONION_MEMBER_DIV_GENERATOR_2(type)        \
        BOOST_OCTONION_MEMBER_DIV_GENERATOR_3(type)        \
        BOOST_OCTONION_MEMBER_DIV_GENERATOR_4(type)
        
#define    BOOST_OCTONION_MEMBER_ALGEBRAIC_GENERATOR(type) \
        BOOST_OCTONION_MEMBER_ADD_GENERATOR(type)          \
        BOOST_OCTONION_MEMBER_SUB_GENERATOR(type)          \
        BOOST_OCTONION_MEMBER_MUL_GENERATOR(type)          \
        BOOST_OCTONION_MEMBER_DIV_GENERATOR(type)
        
        
        template<>
        class octonion<float>
        {
        public:
            
            typedef float value_type;
            
            BOOST_OCTONION_CONSTRUCTOR_GENERATOR(float)
            
            // UNtemplated copy constructor
            // (this is taken care of by the compiler itself)
            
            // explicit copy constructors (precision-losing converters)
            
            explicit                    octonion(octonion<double> const & a_recopier)
            {
                *this = detail::octonion_type_converter<float, double>(a_recopier);
            }
            
            explicit                    octonion(octonion<long double> const & a_recopier)
            {
                *this = detail::octonion_type_converter<float, long double>(a_recopier);
            }
            
            // destructor
            // (this is taken care of by the compiler itself)
            
            // accessors
            //
            // Note:    Like complex number, octonions do have a meaningful notion of "real part",
            //            but unlike them there is no meaningful notion of "imaginary part".
            //            Instead there is an "unreal part" which itself is an octonion, and usually
            //            nothing simpler (as opposed to the complex number case).
            //            However, for practicality, there are accessors for the other components
            //            (these are necessary for the templated copy constructor, for instance).
            
            BOOST_OCTONION_ACCESSOR_GENERATOR(float)
            
            // assignment operators
            
            BOOST_OCTONION_MEMBER_ASSIGNMENT_GENERATOR(float)
            
            // other assignment-related operators
            //
            // NOTE:    Octonion multiplication is *NOT* commutative;
            //            symbolically, "q *= rhs;" means "q = q * rhs;"
            //            and "q /= rhs;" means "q = q * inverse_of(rhs);";
            //            octonion multiplication is also *NOT* associative
            
            BOOST_OCTONION_MEMBER_ALGEBRAIC_GENERATOR(float)
            
            
        protected:
            
            BOOST_OCTONION_MEMBER_DATA_GENERATOR(float)
            
            
        private:
            
        };
        
        
        template<>
        class octonion<double>
        {
        public:
            
            typedef double value_type;
            
            BOOST_OCTONION_CONSTRUCTOR_GENERATOR(double)
            
            // UNtemplated copy constructor
            // (this is taken care of by the compiler itself)
            
            // converting copy constructor
            
            explicit                    octonion(octonion<float> const & a_recopier)
            {
                *this = detail::octonion_type_converter<double, float>(a_recopier);
            }
            
            // explicit copy constructors (precision-losing converters)
            
            explicit                    octonion(octonion<long double> const & a_recopier)
            {
                *this = detail::octonion_type_converter<double, long double>(a_recopier);
            }
            
            // destructor
            // (this is taken care of by the compiler itself)
            
            // accessors
            //
            // Note:    Like complex number, octonions do have a meaningful notion of "real part",
            //            but unlike them there is no meaningful notion of "imaginary part".
            //            Instead there is an "unreal part" which itself is an octonion, and usually
            //            nothing simpler (as opposed to the complex number case).
            //            However, for practicality, there are accessors for the other components
            //            (these are necessary for the templated copy constructor, for instance).
            
            BOOST_OCTONION_ACCESSOR_GENERATOR(double)
            
            // assignment operators
            
            BOOST_OCTONION_MEMBER_ASSIGNMENT_GENERATOR(double)
            
            // other assignment-related operators
            //
            // NOTE:    Octonion multiplication is *NOT* commutative;
            //            symbolically, "q *= rhs;" means "q = q * rhs;"
            //            and "q /= rhs;" means "q = q * inverse_of(rhs);";
            //            octonion multiplication is also *NOT* associative
            
            BOOST_OCTONION_MEMBER_ALGEBRAIC_GENERATOR(double)
            
            
        protected:
            
            BOOST_OCTONION_MEMBER_DATA_GENERATOR(double)
            
            
        private:
            
        };
        
        
        template<>
        class octonion<long double>
        {
        public:
            
            typedef long double value_type;
            
            BOOST_OCTONION_CONSTRUCTOR_GENERATOR(long double)
            
            // UNtemplated copy constructor
            // (this is taken care of by the compiler itself)
            
            // converting copy constructor
            
            explicit                            octonion(octonion<float> const & a_recopier)
            {
                *this = detail::octonion_type_converter<long double, float>(a_recopier);
            }
            
            
            explicit                            octonion(octonion<double> const & a_recopier)
            {
                *this = detail::octonion_type_converter<long double, double>(a_recopier);
            }
            
            
            // destructor
            // (this is taken care of by the compiler itself)
            
            // accessors
            //
            // Note:    Like complex number, octonions do have a meaningful notion of "real part",
            //            but unlike them there is no meaningful notion of "imaginary part".
            //            Instead there is an "unreal part" which itself is an octonion, and usually
            //            nothing simpler (as opposed to the complex number case).
            //            However, for practicality, there are accessors for the other components
            //            (these are necessary for the templated copy constructor, for instance).
            
            BOOST_OCTONION_ACCESSOR_GENERATOR(long double)
            
            // assignment operators
            
            BOOST_OCTONION_MEMBER_ASSIGNMENT_GENERATOR(long double)
            
            // other assignment-related operators
            //
            // NOTE:    Octonion multiplication is *NOT* commutative;
            //            symbolically, "q *= rhs;" means "q = q * rhs;"
            //            and "q /= rhs;" means "q = q * inverse_of(rhs);";
            //            octonion multiplication is also *NOT* associative
            
            BOOST_OCTONION_MEMBER_ALGEBRAIC_GENERATOR(long double)
            
            
        protected:
            
            BOOST_OCTONION_MEMBER_DATA_GENERATOR(long double)
            
            
        private:
            
        };
        
        
#undef    BOOST_OCTONION_CONSTRUCTOR_GENERATOR
        
#undef    BOOST_OCTONION_MEMBER_ALGEBRAIC_GENERATOR
    
#undef    BOOST_OCTONION_MEMBER_ADD_GENERATOR
#undef    BOOST_OCTONION_MEMBER_SUB_GENERATOR
#undef    BOOST_OCTONION_MEMBER_MUL_GENERATOR
#undef    BOOST_OCTONION_MEMBER_DIV_GENERATOR
    
#undef    BOOST_OCTONION_MEMBER_ADD_GENERATOR_1
#undef    BOOST_OCTONION_MEMBER_ADD_GENERATOR_2
#undef    BOOST_OCTONION_MEMBER_ADD_GENERATOR_3
#undef    BOOST_OCTONION_MEMBER_ADD_GENERATOR_4
#undef    BOOST_OCTONION_MEMBER_SUB_GENERATOR_1
#undef    BOOST_OCTONION_MEMBER_SUB_GENERATOR_2
#undef    BOOST_OCTONION_MEMBER_SUB_GENERATOR_3
#undef    BOOST_OCTONION_MEMBER_SUB_GENERATOR_4
#undef    BOOST_OCTONION_MEMBER_MUL_GENERATOR_1
#undef    BOOST_OCTONION_MEMBER_MUL_GENERATOR_2
#undef    BOOST_OCTONION_MEMBER_MUL_GENERATOR_3
#undef    BOOST_OCTONION_MEMBER_MUL_GENERATOR_4
#undef    BOOST_OCTONION_MEMBER_DIV_GENERATOR_1
#undef    BOOST_OCTONION_MEMBER_DIV_GENERATOR_2
#undef    BOOST_OCTONION_MEMBER_DIV_GENERATOR_3
#undef    BOOST_OCTONION_MEMBER_DIV_GENERATOR_4
    
    
#undef    BOOST_OCTONION_MEMBER_DATA_GENERATOR
    
#undef    BOOST_OCTONION_MEMBER_ASSIGNMENT_GENERATOR
    
#undef    BOOST_OCTONION_ACCESSOR_GENERATOR
        
        
        // operators
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR_BODY(op) \
        {                                             \
            octonion<T>    res(lhs);                  \
            res op##= rhs;                            \
            return(res);                              \
        }
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR_1_L(op)                                                                              \
        template<typename T>                                                                                                      \
        inline octonion<T>                        operator op (T const & lhs, octonion<T> const & rhs)                            \
        BOOST_OCTONION_OPERATOR_GENERATOR_BODY(op)
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR_1_R(op)                                                                              \
        template<typename T>                                                                                                      \
        inline octonion<T>                        operator op (octonion<T> const & lhs, T const & rhs)                            \
        BOOST_OCTONION_OPERATOR_GENERATOR_BODY(op)
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR_2_L(op)                                                                              \
        template<typename T>                                                                                                      \
        inline octonion<T>                        operator op (::std::complex<T> const & lhs, octonion<T> const & rhs)            \
        BOOST_OCTONION_OPERATOR_GENERATOR_BODY(op)
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR_2_R(op)                                                                              \
        template<typename T>                                                                                                      \
        inline octonion<T>                        operator op (octonion<T> const & lhs, ::std::complex<T> const & rhs)            \
        BOOST_OCTONION_OPERATOR_GENERATOR_BODY(op)
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR_3_L(op)                                                                              \
        template<typename T>                                                                                                      \
        inline octonion<T>                        operator op (::boost::math::quaternion<T> const & lhs, octonion<T> const & rhs) \
        BOOST_OCTONION_OPERATOR_GENERATOR_BODY(op)
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR_3_R(op)                                                                              \
        template<typename T>                                                                                                      \
        inline octonion<T>                        operator op (octonion<T> const & lhs, ::boost::math::quaternion<T> const & rhs) \
        BOOST_OCTONION_OPERATOR_GENERATOR_BODY(op)
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR_4(op)                                                                                \
        template<typename T>                                                                                                      \
        inline octonion<T>                        operator op (octonion<T> const & lhs, octonion<T> const & rhs)                  \
        BOOST_OCTONION_OPERATOR_GENERATOR_BODY(op)
        
#define    BOOST_OCTONION_OPERATOR_GENERATOR(op)     \
        BOOST_OCTONION_OPERATOR_GENERATOR_1_L(op)    \
        BOOST_OCTONION_OPERATOR_GENERATOR_1_R(op)    \
        BOOST_OCTONION_OPERATOR_GENERATOR_2_L(op)    \
        BOOST_OCTONION_OPERATOR_GENERATOR_2_R(op)    \
        BOOST_OCTONION_OPERATOR_GENERATOR_3_L(op)    \
        BOOST_OCTONION_OPERATOR_GENERATOR_3_R(op)    \
        BOOST_OCTONION_OPERATOR_GENERATOR_4(op)
        
        
        BOOST_OCTONION_OPERATOR_GENERATOR(+)
        BOOST_OCTONION_OPERATOR_GENERATOR(-)
        BOOST_OCTONION_OPERATOR_GENERATOR(*)
        BOOST_OCTONION_OPERATOR_GENERATOR(/)
        
        
#undef    BOOST_OCTONION_OPERATOR_GENERATOR
        
#undef    BOOST_OCTONION_OPERATOR_GENERATOR_1_L
#undef    BOOST_OCTONION_OPERATOR_GENERATOR_1_R
#undef    BOOST_OCTONION_OPERATOR_GENERATOR_2_L
#undef    BOOST_OCTONION_OPERATOR_GENERATOR_2_R
#undef    BOOST_OCTONION_OPERATOR_GENERATOR_3_L
#undef    BOOST_OCTONION_OPERATOR_GENERATOR_3_R
#undef    BOOST_OCTONION_OPERATOR_GENERATOR_4
    
#undef    BOOST_OCTONION_OPERATOR_GENERATOR_BODY
        
        
        template<typename T>
        inline octonion<T>                        operator + (octonion<T> const & o)
        {
            return(o);
        }
        
        
        template<typename T>
        inline octonion<T>                        operator - (octonion<T> const & o)
        {
            return(octonion<T>(-o.R_component_1(),-o.R_component_2(),-o.R_component_3(),-o.R_component_4(),-o.R_component_5(),-o.R_component_6(),-o.R_component_7(),-o.R_component_8()));
        }
        
        
        template<typename T>
        inline bool                                operator == (T const & lhs, octonion<T> const & rhs)
        {
            return(
                        (rhs.R_component_1() == lhs)&&
                        (rhs.R_component_2() == static_cast<T>(0))&&
                        (rhs.R_component_3() == static_cast<T>(0))&&
                        (rhs.R_component_4() == static_cast<T>(0))&&
                        (rhs.R_component_5() == static_cast<T>(0))&&
                        (rhs.R_component_6() == static_cast<T>(0))&&
                        (rhs.R_component_7() == static_cast<T>(0))&&
                        (rhs.R_component_8() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T>
        inline bool                                operator == (octonion<T> const & lhs, T const & rhs)
        {
            return(
                        (lhs.R_component_1() == rhs)&&
                        (lhs.R_component_2() == static_cast<T>(0))&&
                        (lhs.R_component_3() == static_cast<T>(0))&&
                        (lhs.R_component_4() == static_cast<T>(0))&&
                        (lhs.R_component_5() == static_cast<T>(0))&&
                        (lhs.R_component_6() == static_cast<T>(0))&&
                        (lhs.R_component_7() == static_cast<T>(0))&&
                        (lhs.R_component_8() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T>
        inline bool                                operator == (::std::complex<T> const & lhs, octonion<T> const & rhs)
        {
            return(
                        (rhs.R_component_1() == lhs.real())&&
                        (rhs.R_component_2() == lhs.imag())&&
                        (rhs.R_component_3() == static_cast<T>(0))&&
                        (rhs.R_component_4() == static_cast<T>(0))&&
                        (rhs.R_component_5() == static_cast<T>(0))&&
                        (rhs.R_component_6() == static_cast<T>(0))&&
                        (rhs.R_component_7() == static_cast<T>(0))&&
                        (rhs.R_component_8() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T>
        inline bool                                operator == (octonion<T> const & lhs, ::std::complex<T> const & rhs)
        {
            return(
                        (lhs.R_component_1() == rhs.real())&&
                        (lhs.R_component_2() == rhs.imag())&&
                        (lhs.R_component_3() == static_cast<T>(0))&&
                        (lhs.R_component_4() == static_cast<T>(0))&&
                        (lhs.R_component_5() == static_cast<T>(0))&&
                        (lhs.R_component_6() == static_cast<T>(0))&&
                        (lhs.R_component_7() == static_cast<T>(0))&&
                        (lhs.R_component_8() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T>
        inline bool                                operator == (::boost::math::quaternion<T> const & lhs, octonion<T> const & rhs)
        {
            return(
                        (rhs.R_component_1() == lhs.R_component_1())&&
                        (rhs.R_component_2() == lhs.R_component_2())&&
                        (rhs.R_component_3() == lhs.R_component_3())&&
                        (rhs.R_component_4() == lhs.R_component_4())&&
                        (rhs.R_component_5() == static_cast<T>(0))&&
                        (rhs.R_component_6() == static_cast<T>(0))&&
                        (rhs.R_component_7() == static_cast<T>(0))&&
                        (rhs.R_component_8() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T>
        inline bool                                operator == (octonion<T> const & lhs, ::boost::math::quaternion<T> const & rhs)
        {
            return(
                        (lhs.R_component_1() == rhs.R_component_1())&&
                        (lhs.R_component_2() == rhs.R_component_2())&&
                        (lhs.R_component_3() == rhs.R_component_3())&&
                        (lhs.R_component_4() == rhs.R_component_4())&&
                        (lhs.R_component_5() == static_cast<T>(0))&&
                        (lhs.R_component_6() == static_cast<T>(0))&&
                        (lhs.R_component_7() == static_cast<T>(0))&&
                        (lhs.R_component_8() == static_cast<T>(0))
                    );
        }
        
        
        template<typename T>
        inline bool                                operator == (octonion<T> const & lhs, octonion<T> const & rhs)
        {
            return(
                        (rhs.R_component_1() == lhs.R_component_1())&&
                        (rhs.R_component_2() == lhs.R_component_2())&&
                        (rhs.R_component_3() == lhs.R_component_3())&&
                        (rhs.R_component_4() == lhs.R_component_4())&&
                        (rhs.R_component_5() == lhs.R_component_5())&&
                        (rhs.R_component_6() == lhs.R_component_6())&&
                        (rhs.R_component_7() == lhs.R_component_7())&&
                        (rhs.R_component_8() == lhs.R_component_8())
                    );
        }
        
        
#define    BOOST_OCTONION_NOT_EQUAL_GENERATOR \
        {                                     \
            return(!(lhs == rhs));            \
        }
        
        template<typename T>
        inline bool                                operator != (T const & lhs, octonion<T> const & rhs)
        BOOST_OCTONION_NOT_EQUAL_GENERATOR
        
        template<typename T>
        inline bool                                operator != (octonion<T> const & lhs, T const & rhs)
        BOOST_OCTONION_NOT_EQUAL_GENERATOR
        
        template<typename T>
        inline bool                                operator != (::std::complex<T> const & lhs, octonion<T> const & rhs)
        BOOST_OCTONION_NOT_EQUAL_GENERATOR
        
        template<typename T>
        inline bool                                operator != (octonion<T> const & lhs, ::std::complex<T> const & rhs)
        BOOST_OCTONION_NOT_EQUAL_GENERATOR
        
        template<typename T>
        inline bool                                operator != (::boost::math::quaternion<T> const & lhs, octonion<T> const & rhs)
        BOOST_OCTONION_NOT_EQUAL_GENERATOR
        
        template<typename T>
        inline bool                                operator != (octonion<T> const & lhs, ::boost::math::quaternion<T> const & rhs)
        BOOST_OCTONION_NOT_EQUAL_GENERATOR
        
        template<typename T>
        inline bool                                operator != (octonion<T> const & lhs, octonion<T> const & rhs)
        BOOST_OCTONION_NOT_EQUAL_GENERATOR
        
    #undef    BOOST_OCTONION_NOT_EQUAL_GENERATOR
        
        
        // Note:    the default values in the constructors of the complex and quaternions make for
        //            a very complex and ambiguous situation; we have made choices to disambiguate.
        template<typename T, typename charT, class traits>
        ::std::basic_istream<charT,traits> &    operator >> (    ::std::basic_istream<charT,traits> & is,
                                                                octonion<T> & o)
        {
#ifdef     BOOST_NO_STD_LOCALE
#else
            const ::std::ctype<charT> & ct = ::std::use_facet< ::std::ctype<charT> >(is.getloc());
#endif /* BOOST_NO_STD_LOCALE */
            
            T    a = T();
            T    b = T();
            T    c = T();
            T    d = T();
            T    e = T();
            T    f = T();
            T    g = T();
            T    h = T();
            
            ::std::complex<T>    u = ::std::complex<T>();
            ::std::complex<T>    v = ::std::complex<T>();
            ::std::complex<T>    x = ::std::complex<T>();
            ::std::complex<T>    y = ::std::complex<T>();
            
            ::boost::math::quaternion<T>    p = ::boost::math::quaternion<T>();
            ::boost::math::quaternion<T>    q = ::boost::math::quaternion<T>();
            
            charT    ch = charT();
            char    cc;
            
            is >> ch;                                        // get the first lexeme
            
            if    (!is.good())    goto finish;
            
#ifdef    BOOST_NO_STD_LOCALE
            cc = ch;
#else
            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
            
            if    (cc == '(')                            // read "("
            {
                is >> ch;                                    // get the second lexeme
                
                if    (!is.good())    goto finish;
                
#ifdef    BOOST_NO_STD_LOCALE
                cc = ch;
#else
                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                
                if    (cc == '(')                                // read "(("
                {
                    is >> ch;                                    // get the third lexeme
                    
                    if    (!is.good())    goto finish;
                    
#ifdef    BOOST_NO_STD_LOCALE
                    cc = ch;
#else
                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                        
                    if    (cc == '(')                                // read "((("
                    {
                        is.putback(ch);
                        
                        is >> u;                                // read "((u"
                        
                        if    (!is.good())    goto finish;
                        
                        is >> ch;                                // get the next lexeme
                        
                        if    (!is.good())    goto finish;
                        
#ifdef    BOOST_NO_STD_LOCALE
                        cc = ch;
#else
                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                        
                        if        (cc == ')')                        // read "((u)"
                        {
                            is >> ch;                                // get the next lexeme
                            
                            if    (!is.good())    goto finish;
                            
#ifdef    BOOST_NO_STD_LOCALE
                            cc = ch;
#else
                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                            
                            if        (cc == ')')                        // format: (((a))), (((a,b)))
                            {
                                o = octonion<T>(u);
                            }
                            else if    (cc == ',')                        // read "((u),"
                            {
                                p = ::boost::math::quaternion<T>(u);
                                
                                is >> q;                                // read "((u),q"
                                
                                if    (!is.good())    goto finish;
                                
                                is >> ch;                                // get the next lexeme
                                
                                if    (!is.good())    goto finish;
                                
#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
                                if        (cc == ')')                        // format: (((a)),q), (((a,b)),q)
                                {
                                    o = octonion<T>(p,q);
                                }
                                else                                    // error
                                {
                                    is.setstate(::std::ios_base::failbit);
                                }
                            }
                            else                                    // error
                            {
                                is.setstate(::std::ios_base::failbit);
                            }
                        }
                        else if    (cc ==',')                        // read "((u,"
                        {
                            is >> v;                                // read "((u,v"
                            
                            if    (!is.good())    goto finish;
                            
                            is >> ch;                                // get the next lexeme
                            
                            if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                            cc = ch;
#else
                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                            
                            if        (cc == ')')                        // read "((u,v)"
                            {
                                p = ::boost::math::quaternion<T>(u,v);
                                
                                is >> ch;                                // get the next lexeme
                                
                                if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
                                if        (cc == ')')                        // format: (((a),v)), (((a,b),v))
                                {
                                    o = octonion<T>(p);
                                }
                                else if    (cc == ',')                        // read "((u,v),"
                                {
                                    is >> q;                                // read "(p,q"
                                    
                                    if    (!is.good())    goto finish;
                                    
                                    is >> ch;                                // get the next lexeme
                                    
                                    if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == ')')                        // format: (((a),v),q), (((a,b),v),q)
                                    {
                                        o = octonion<T>(p,q);
                                    }
                                    else                                    // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                                else                                    // error
                                {
                                    is.setstate(::std::ios_base::failbit);
                                }
                            }
                            else                                    // error
                            {
                                is.setstate(::std::ios_base::failbit);
                            }
                        }
                        else                                    // error
                        {
                            is.setstate(::std::ios_base::failbit);
                        }
                    }
                    else                                        // read "((a"
                    {
                        is.putback(ch);
                        
                        is >> a;                                    // we extract the first component
                        
                        if    (!is.good())    goto finish;
                        
                        is >> ch;                                    // get the next lexeme
                        
                        if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                        cc = ch;
#else
                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                        
                        if        (cc == ')')                            // read "((a)"
                        {
                            is >> ch;                                    // get the next lexeme
                            
                            if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                            cc = ch;
#else
                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                            
                            if        (cc == ')')                            // read "((a))"
                            {
                                o = octonion<T>(a);
                            }
                            else if    (cc == ',')                            // read "((a),"
                            {
                                is >> ch;                                    // get the next lexeme
                                
                                if    (!is.good())    goto finish;
                                
#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
                                if        (cc == '(')                            // read "((a),("
                                {
                                    is >> ch;                                    // get the next lexeme
                                    
                                    if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == '(')                            // read "((a),(("
                                    {
                                        is.putback(ch);
                                        
                                        is.putback(ch);                                // we backtrack twice, with the same value!
                                        
                                        is >> q;                                    // read "((a),q"
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                        
                                        if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "((a),q)"
                                        {
                                            p = ::boost::math::quaternion<T>(a);
                                            
                                            o = octonion<T>(p,q);
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else                                        // read "((a),(c" or "((a),(e"
                                    {
                                        is.putback(ch);
                                        
                                        is >> c;
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                        
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "((a),(c)" (ambiguity resolution)
                                        {
                                            is >> ch;                                    // get the next lexeme
                                            
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                        // read "((a),(c))"
                                            {
                                                o = octonion<T>(a,b,c);
                                            }
                                            else if    (cc == ',')                        // read "((a),(c),"
                                            {
                                                u = ::std::complex<T>(a);
                                                
                                                v = ::std::complex<T>(c);
                                                
                                                is >> x;                            // read "((a),(c),x"
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                // get the next lexeme
                                                
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                        // read "((a),(c),x)"
                                                {
                                                    o = octonion<T>(u,v,x);
                                                }
                                                else if    (cc == ',')                        // read "((a),(c),x,"
                                                {
                                                    is >> y;                                // read "((a),(c),x,y"
                                                    
                                                    if    (!is.good())    goto finish;
                                                    
                                                    is >> ch;                                // get the next lexeme
                                                    
                                                    if    (!is.good())    goto finish;
                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == ')')                        // read "((a),(c),x,y)"
                                                    {
                                                        o = octonion<T>(u,v,x,y);
                                                    }
                                                    else                                    // error
                                                    {
                                                        is.setstate(::std::ios_base::failbit);
                                                    }
                                                }
                                                else                                    // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                            else                                    // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else if    (cc == ',')                            // read "((a),(c," or "((a),(e,"
                                        {
                                            is >> ch;                                // get the next lexeme
                                            
                                            if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == '(')                        // read "((a),(e,(" (ambiguity resolution)
                                            {
                                                p = ::boost::math::quaternion<T>(a);
                                                
                                                x = ::std::complex<T>(c);                // "c" was actually "e"
                                                
                                                is.putback(ch);                            // we can only backtrace once
                                                
                                                is >> y;                                // read "((a),(e,y"
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                // get the next lexeme
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                        // read "((a),(e,y)"
                                                {
                                                    q = ::boost::math::quaternion<T>(x,y);
                                                    
                                                    is >> ch;                                // get the next lexeme

#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == ')')                        // read "((a),(e,y))"
                                                    {
                                                        o = octonion<T>(p,q);
                                                    }
                                                    else                                    // error
                                                    {
                                                        is.setstate(::std::ios_base::failbit);
                                                    }
                                                }
                                                else                                    // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                            else                                    // read "((a),(c,d" or "((a),(e,f"
                                            {
                                                is.putback(ch);
                                                
                                                is >> d;
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                // get the next lexeme
                                                
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                        // read "((a),(c,d)" (ambiguity resolution)
                                                {
                                                    is >> ch;                                // get the next lexeme
                                                    
                                                    if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == ')')                        // read "((a),(c,d))"
                                                    {
                                                        o = octonion<T>(a,b,c,d);
                                                    }
                                                    else if    (cc == ',')                        // read "((a),(c,d),"
                                                    {
                                                        u = ::std::complex<T>(a);
                                                        
                                                        v = ::std::complex<T>(c,d);
                                                        
                                                        is >> x;                                // read "((a),(c,d),x"
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
                                                        is >> ch;                                // get the next lexeme
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
#ifdef    BOOST_NO_STD_LOCALE
                                                        cc = ch;
#else
                                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                        
                                                        if        (cc == ')')                        // read "((a),(c,d),x)"
                                                        {
                                                            o = octonion<T>(u,v,x);
                                                        }
                                                        else if    (cc == ',')                        // read "((a),(c,d),x,"
                                                        {
                                                            is >> y;                                // read "((a),(c,d),x,y"
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
                                                            is >> ch;                                // get the next lexeme
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
#ifdef    BOOST_NO_STD_LOCALE
                                                            cc = ch;
#else
                                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                            
                                                            if        (cc == ')')                        // read "((a),(c,d),x,y)"
                                                            {
                                                                o = octonion<T>(u,v,x,y);
                                                            }
                                                            else                                    // error
                                                            {
                                                                is.setstate(::std::ios_base::failbit);
                                                            }
                                                        }
                                                        else                                    // error
                                                        {
                                                            is.setstate(::std::ios_base::failbit);
                                                        }
                                                    }
                                                    else                                    // error
                                                    {
                                                        is.setstate(::std::ios_base::failbit);
                                                    }
                                                }
                                                else if    (cc == ',')                        // read "((a),(e,f," (ambiguity resolution)
                                                {
                                                    p = ::boost::math::quaternion<T>(a);
                                                    
                                                    is >> g;                                // read "((a),(e,f,g" (too late to backtrack)
                                                    
                                                    if    (!is.good())    goto finish;
                                                    
                                                    is >> ch;                                // get the next lexeme
                                                    
                                                    if    (!is.good())    goto finish;
                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == ')')                        // read "((a),(e,f,g)"
                                                    {
                                                        q = ::boost::math::quaternion<T>(c,d,g);        // "c" was actually "e", and "d" was actually "f"
                                                        
                                                        is >> ch;                                // get the next lexeme
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
#ifdef    BOOST_NO_STD_LOCALE
                                                        cc = ch;
#else
                                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                        
                                                        if        (cc == ')')                        // read "((a),(e,f,g))"
                                                        {
                                                            o = octonion<T>(p,q);
                                                        }
                                                        else                                    // error
                                                        {
                                                            is.setstate(::std::ios_base::failbit);
                                                        }
                                                    }
                                                    else if    (cc == ',')                        // read "((a),(e,f,g,"
                                                    {
                                                        is >> h;                                // read "((a),(e,f,g,h"
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
                                                        is >> ch;                                // get the next lexeme
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
#ifdef    BOOST_NO_STD_LOCALE
                                                        cc = ch;
#else
                                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                        
                                                        if        (cc == ')')                        // read "((a),(e,f,g,h)"
                                                        {
                                                            q = ::boost::math::quaternion<T>(c,d,g,h);    // "c" was actually "e", and "d" was actually "f"
                                                            
                                                            is >> ch;                                // get the next lexeme
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
#ifdef    BOOST_NO_STD_LOCALE
                                                            cc = ch;
#else
                                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                            
                                                            if        (cc == ')')                        // read "((a),(e,f,g,h))"
                                                            {
                                                                o = octonion<T>(p,q);
                                                            }
                                                            else                                    // error
                                                            {
                                                                is.setstate(::std::ios_base::failbit);
                                                            }
                                                        }
                                                        else                                    // error
                                                        {
                                                            is.setstate(::std::ios_base::failbit);
                                                        }
                                                    }
                                                    else                                    // error
                                                    {
                                                        is.setstate(::std::ios_base::failbit);
                                                    }
                                                }
                                                else                                    // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                }
                                else                                        // read "((a),c" (ambiguity resolution)
                                {
                                    is.putback(ch);
                                    
                                    is >> c;                                    // we extract the third component
                                    
                                    if    (!is.good())    goto finish;
                                    
                                    is >> ch;                                    // get the next lexeme
                                    
                                    if    (!is.good())    goto finish;
                                    
#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == ')')                            // read "((a),c)"
                                    {
                                        o = octonion<T>(a,b,c);
                                    }
                                    else if    (cc == ',')                            // read "((a),c,"
                                    {
                                        is >> x;                                    // read "((a),c,x"
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                        
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "((a),c,x)"
                                        {
                                            o = octonion<T>(a,b,c,d,x.real(),x.imag());
                                        }
                                        else if    (cc == ',')                            // read "((a),c,x,"
                                        {
                                            is >> y;if    (!is.good())    goto finish;        // read "((a),c,x,y"
                                            
                                            is >> ch;                                    // get the next lexeme
                                            
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "((a),c,x,y)"
                                            {
                                                o = octonion<T>(a,b,c,d,x.real(),x.imag(),y.real(),y.imag());
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else                                        // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                            }
                            else                                        // error
                            {
                                is.setstate(::std::ios_base::failbit);
                            }
                        }
                        else if    (cc ==',')                            // read "((a,"
                        {
                            is >> ch;                                    // get the next lexeme
                            
                            if    (!is.good())    goto finish;
                            
#ifdef    BOOST_NO_STD_LOCALE
                            cc = ch;
#else
                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                            
                            if        (cc == '(')                            // read "((a,("
                            {
                                u = ::std::complex<T>(a);
                                
                                is.putback(ch);                                // can only backtrack so much
                                
                                is >> v;                                    // read "((a,v"
                                
                                if    (!is.good())    goto finish;
                                
                                is >> ch;                                    // get the next lexeme
                                
                                if    (!is.good())    goto finish;
                                
#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
                                if        (cc == ')')                            // read "((a,v)"
                                {
                                    is >> ch;                                    // get the next lexeme
                                    
                                    if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == ')')                            // read "((a,v))"
                                    {
                                        o = octonion<T>(u,v);
                                    }
                                    else if    (cc == ',')                            // read "((a,v),"
                                    {
                                        p = ::boost::math::quaternion<T>(u,v);
                                        
                                        is >> q;                                    // read "((a,v),q"
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                        
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "((a,v),q)"
                                        {
                                            o = octonion<T>(p,q);
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else                                        // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                                else                                        // error
                                {
                                    is.setstate(::std::ios_base::failbit);
                                }
                            }
                            else
                            {
                                is.putback(ch);
                                
                                is >> b;                                    // read "((a,b"
                                
                                if    (!is.good())    goto finish;
                                
                                is >> ch;                                    // get the next lexeme
                                
                                if    (!is.good())    goto finish;
                                
#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
                                if        (cc == ')')                            // read "((a,b)"
                                {
                                    is >> ch;                                    // get the next lexeme
                                    
                                    if    (!is.good())    goto finish;
                                    
#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == ')')                            // read "((a,b))"
                                    {
                                        o = octonion<T>(a,b);
                                    }
                                    else if    (cc == ',')                            // read "((a,b),"
                                    {
                                        is >> ch;                                    // get the next lexeme
                                        
                                        if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == '(')                            // read "((a,b),("
                                        {
                                            is >> ch;                                    // get the next lexeme
                                            
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == '(')                            // read "((a,b),(("
                                            {
                                                p = ::boost::math::quaternion<T>(a,b);
                                                
                                                is.putback(ch);
                                                
                                                is.putback(ch);                            // we backtrack twice, with the same value
                                                
                                                is >> q;                                // read "((a,b),q"
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                    // get the next lexeme
                                                
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                            // read "((a,b),q)"
                                                {
                                                    o = octonion<T>(p,q);
                                                }
                                                else                                        // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                            else                                        // read "((a,b),(c" or "((a,b),(e"
                                            {
                                                is.putback(ch);
                                                
                                                is >> c;
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                    // get the next lexeme
                                                
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                            // read "((a,b),(c)" (ambiguity resolution)
                                                {
                                                    is >> ch;                                    // get the next lexeme
                                                    
                                                    if    (!is.good())    goto finish;
                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == ')')                            // read "((a,b),(c))"
                                                    {
                                                        o = octonion<T>(a,b,c);
                                                    }
                                                    else if    (cc == ',')                            // read "((a,b),(c),"
                                                    {
                                                        u = ::std::complex<T>(a,b);
                                                        
                                                        v = ::std::complex<T>(c);
                                                        
                                                        is >> x;                                    // read "((a,b),(c),x"
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
                                                        is >> ch;                                    // get the next lexeme
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
#ifdef    BOOST_NO_STD_LOCALE
                                                        cc = ch;
#else
                                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                        
                                                        if        (cc == ')')                            // read "((a,b),(c),x)"
                                                        {
                                                            o = octonion<T>(u,v,x);
                                                        }
                                                        else if    (cc == ',')                            // read "((a,b),(c),x,"
                                                        {
                                                            is >> y;                                    // read "((a,b),(c),x,y"
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
                                                            is >> ch;                                    // get the next lexeme
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
#ifdef    BOOST_NO_STD_LOCALE
                                                            cc = ch;
#else
                                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                            
                                                            if        (cc == ')')                            // read "((a,b),(c),x,y)"
                                                            {
                                                                o = octonion<T>(u,v,x,y);
                                                            }
                                                            else                                        // error
                                                            {
                                                                is.setstate(::std::ios_base::failbit);
                                                            }
                                                        }
                                                        else                                        // error
                                                        {
                                                            is.setstate(::std::ios_base::failbit);
                                                        }
                                                    }
                                                    else                                        // error
                                                    {
                                                        is.setstate(::std::ios_base::failbit);
                                                    }
                                                }
                                                else if    (cc == ',')                            // read "((a,b),(c," or "((a,b),(e,"
                                                {
                                                    is >> ch;                                    // get the next lexeme
                                                    
                                                    if    (!is.good())    goto finish;
                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == '(')                            // read "((a,b),(e,(" (ambiguity resolution)
                                                    {
                                                        u = ::std::complex<T>(a,b);
                                                        
                                                        x = ::std::complex<T>(c);                    // "c" is actually "e"
                                                        
                                                        is.putback(ch);
                                                        
                                                        is >> y;                                    // read "((a,b),(e,y"
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
                                                        is >> ch;                                    // get the next lexeme
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
#ifdef    BOOST_NO_STD_LOCALE
                                                        cc = ch;
#else
                                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                        
                                                        if        (cc == ')')                            // read "((a,b),(e,y)"
                                                        {
                                                            is >> ch;                                    // get the next lexeme
                                                            
                                                            if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                                            cc = ch;
#else
                                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                            
                                                            if        (cc == ')')                            // read "((a,b),(e,y))"
                                                            {
                                                                o = octonion<T>(u,v,x,y);
                                                            }
                                                            else                                        // error
                                                            {
                                                                is.setstate(::std::ios_base::failbit);
                                                            }
                                                        }
                                                        else                                        // error
                                                        {
                                                            is.setstate(::std::ios_base::failbit);
                                                        }
                                                    }
                                                    else                                        // read "((a,b),(c,d" or "((a,b),(e,f"
                                                    {
                                                        is.putback(ch);
                                                        
                                                        is >> d;
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
                                                        is >> ch;                                    // get the next lexeme
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
#ifdef    BOOST_NO_STD_LOCALE
                                                        cc = ch;
#else
                                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                        
                                                        if        (cc == ')')                            // read "((a,b),(c,d)" (ambiguity resolution)
                                                        {
                                                            u = ::std::complex<T>(a,b);
                                                            
                                                            v = ::std::complex<T>(c,d);
                                                            
                                                            is >> ch;                                    // get the next lexeme
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
#ifdef    BOOST_NO_STD_LOCALE
                                                            cc = ch;
#else
                                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                            
                                                            if        (cc == ')')                            // read "((a,b),(c,d))"
                                                            {
                                                                o = octonion<T>(u,v);
                                                            }
                                                            else if    (cc == ',')                            // read "((a,b),(c,d),"
                                                            {
                                                                is >> x;                                    // read "((a,b),(c,d),x
                                                                
                                                                if    (!is.good())    goto finish;
                                                                
                                                                is >> ch;                                    // get the next lexeme
                                                                
                                                                if    (!is.good())    goto finish;
                                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                                cc = ch;
#else
                                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                                
                                                                if        (cc == ')')                            // read "((a,b),(c,d),x)"
                                                                {
                                                                    o = octonion<T>(u,v,x);
                                                                }
                                                                else if    (cc == ',')                            // read "((a,b),(c,d),x,"
                                                                {
                                                                    is >> y;                                    // read "((a,b),(c,d),x,y"
                                                                    
                                                                    if    (!is.good())    goto finish;
                                                                    
                                                                    is >> ch;                                    // get the next lexeme
                                                                    
                                                                    if    (!is.good())    goto finish;
                                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                                    cc = ch;
#else
                                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                                    
                                                                    if        (cc == ')')                            // read "((a,b),(c,d),x,y)"
                                                                    {
                                                                        o = octonion<T>(u,v,x,y);
                                                                    }
                                                                    else                                        // error
                                                                    {
                                                                        is.setstate(::std::ios_base::failbit);
                                                                    }
                                                                }
                                                                else                                        // error
                                                                {
                                                                    is.setstate(::std::ios_base::failbit);
                                                                }
                                                            }
                                                            else                                        // error
                                                            {
                                                                is.setstate(::std::ios_base::failbit);
                                                            }
                                                        }
                                                        else if    (cc == ',')                            // read "((a,b),(e,f," (ambiguity resolution)
                                                        {
                                                            p = ::boost::math::quaternion<T>(a,b);                // too late to backtrack
                                                            
                                                            is >> g;                                    // read "((a,b),(e,f,g"
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
                                                            is >> ch;                                    // get the next lexeme
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
#ifdef    BOOST_NO_STD_LOCALE
                                                            cc = ch;
#else
                                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                            
                                                            if        (cc == ')')                            // read "((a,b),(e,f,g)"
                                                            {
                                                                is >> ch;                                    // get the next lexeme
                                                                
                                                                if    (!is.good())    goto finish;
                                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                                cc = ch;
#else
                                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                                
                                                                if        (cc == ')')                            // read "((a,b),(e,f,g))"
                                                                {
                                                                    q = ::boost::math::quaternion<T>(c,d,g);            // "c" is actually "e" and "d" is actually "f"
                                                                    
                                                                    o = octonion<T>(p,q);
                                                                }
                                                                else                                        // error
                                                                {
                                                                    is.setstate(::std::ios_base::failbit);
                                                                }
                                                            }
                                                            else if    (cc == ',')                            // read "((a,b),(e,f,g,"
                                                            {
                                                                is >> h;                                    // read "((a,b),(e,f,g,h"
                                                                
                                                                if    (!is.good())    goto finish;
                                                                
                                                                is >> ch;                                    // get the next lexeme
                                                                
                                                                if    (!is.good())    goto finish;
                                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                                cc = ch;
#else
                                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                                
                                                                if        (cc == ')')                            // read "((a,b),(e,f,g,h)"
                                                                {
                                                                    is >> ch;                                    // get the next lexeme
                                                                    
                                                                    if    (!is.good())    goto finish;
                                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                                    cc = ch;
#else
                                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                                    
                                                                    if        (cc == ')')                            // read ((a,b),(e,f,g,h))"
                                                                    {
                                                                        q = ::boost::math::quaternion<T>(c,d,g,h);            // "c" is actually "e" and "d" is actually "f"
                                                                        
                                                                        o = octonion<T>(p,q);
                                                                    }
                                                                    else                                        // error
                                                                    {
                                                                        is.setstate(::std::ios_base::failbit);
                                                                    }
                                                                }
                                                                else                                        // error
                                                                {
                                                                    is.setstate(::std::ios_base::failbit);
                                                                }
                                                            }
                                                            else                                        // error
                                                            {
                                                                is.setstate(::std::ios_base::failbit);
                                                            }
                                                        }
                                                        else                                        // error
                                                        {
                                                            is.setstate(::std::ios_base::failbit);
                                                        }
                                                    }
                                                }
                                                else                                        // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else                                        // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                                else if    (cc == ',')                            // read "((a,b,"
                                {
                                    is >> c;                                    // read "((a,b,c"
                                    
                                    if    (!is.good())    goto finish;
                                    
                                    is >> ch;                                    // get the next lexeme
                                                                
                                    if    (!is.good())    goto finish;
                                    
#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == ')')                            // read "((a,b,c)"
                                    {
                                        is >> ch;                                    // get the next lexeme
                                                                    
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "((a,b,c))"
                                        {
                                            o = octonion<T>(a,b,c);
                                        }
                                        else if    (cc == ',')                            // read "((a,b,c),"
                                        {
                                            p = ::boost::math::quaternion<T>(a,b,c);
                                            
                                            is >> q;                                    // read "((a,b,c),q"
                                            
                                            if    (!is.good())    goto finish;
                                            
                                            is >> ch;                                    // get the next lexeme
                                                                        
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "((a,b,c),q)"
                                            {
                                                o = octonion<T>(p,q);
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else if    (cc == ',')                            // read "((a,b,c,"
                                    {
                                        is >> d;                                    // read "((a,b,c,d"
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                                                    
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "((a,b,c,d)"
                                        {
                                            is >> ch;                                    // get the next lexeme
                                                                        
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "((a,b,c,d))"
                                            {
                                                o = octonion<T>(a,b,c,d);
                                            }
                                            else if    (cc == ',')                            // read "((a,b,c,d),"
                                            {
                                                p = ::boost::math::quaternion<T>(a,b,c,d);
                                                
                                                is >> q;                                    // read "((a,b,c,d),q"
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                    // get the next lexeme
                                                                            
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                            // read "((a,b,c,d),q)"
                                                {
                                                    o = octonion<T>(p,q);
                                                }
                                                else                                        // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else                                        // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                                else                                        // error
                                {
                                    is.setstate(::std::ios_base::failbit);
                                }
                            }
                        }
                        else                                        // error
                        {
                            is.setstate(::std::ios_base::failbit);
                        }
                    }
                }
                else                                        // read "(a"
                {
                    is.putback(ch);
                    
                    is >> a;                                    // we extract the first component
                    
                    if    (!is.good())    goto finish;
                    
                    is >> ch;                                    // get the next lexeme
                                                
                    if    (!is.good())    goto finish;
                    
#ifdef    BOOST_NO_STD_LOCALE
                    cc = ch;
#else
                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                    
                    if        (cc == ')')                            // read "(a)"
                    {
                        o = octonion<T>(a);
                    }
                    else if    (cc == ',')                            // read "(a,"
                    {
                        is >> ch;                                    // get the next lexeme
                                                    
                        if    (!is.good())    goto finish;
                        
#ifdef    BOOST_NO_STD_LOCALE
                        cc = ch;
#else
                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                        
                        if        (cc == '(')                            // read "(a,("
                        {
                            is >> ch;                                    // get the next lexeme
                                                        
                            if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                            cc = ch;
#else
                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                            
                            if        (cc == '(')                            // read "(a,(("
                            {
                                p = ::boost::math::quaternion<T>(a);
                                
                                is.putback(ch);
                                
                                is.putback(ch);                                // we backtrack twice, with the same value
                                
                                is >> q;                                    // read "(a,q"
                                
                                if    (!is.good())    goto finish;
                                
                                is >> ch;                                    // get the next lexeme
                                                            
                                if    (!is.good())    goto finish;
                                
#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
                                if        (cc == ')')                            // read "(a,q)"
                                {
                                    o = octonion<T>(p,q);
                                }
                                else                                        // error
                                {
                                    is.setstate(::std::ios_base::failbit);
                                }
                            }
                            else                                        // read "(a,(c" or "(a,(e"
                            {
                                is.putback(ch);
                                
                                is >> c;
                                
                                if    (!is.good())    goto finish;
                                
                                is >> ch;                                    // get the next lexeme
                                                            
                                if    (!is.good())    goto finish;
                                
#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
                                if        (cc == ')')                            // read "(a,(c)" (ambiguity resolution)
                                {
                                    is >> ch;                                    // get the next lexeme
                                                                
                                    if    (!is.good())    goto finish;
                                    
#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == ')')                            // read "(a,(c))"
                                    {
                                        o = octonion<T>(a,b,c);
                                    }
                                    else if    (cc == ',')                            // read "(a,(c),"
                                    {
                                        u = ::std::complex<T>(a);
                                        
                                        v = ::std::complex<T>(c);
                                        
                                        is >> x;                                // read "(a,(c),x"
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                                                    
                                        if    (!is.good())    goto finish;

#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "(a,(c),x)"
                                        {
                                            o = octonion<T>(u,v,x);
                                        }
                                        else if    (cc == ',')                            // read "(a,(c),x,"
                                        {
                                            is >> y;                                    // read "(a,(c),x,y"
                                            
                                            if    (!is.good())    goto finish;
                                            
                                            is >> ch;                                    // get the next lexeme
                                                                        
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "(a,(c),x,y)"
                                            {
                                                o = octonion<T>(u,v,x,y);
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else                                        // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                                else if    (cc == ',')                            // read "(a,(c," or "(a,(e,"
                                {
                                    is >> ch;                                    // get the next lexeme
                                                                
                                    if    (!is.good())    goto finish;
                                    
#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == '(')                            // read "(a,(e,(" (ambiguity resolution)
                                    {
                                        u = ::std::complex<T>(a);
                                        
                                        x = ::std::complex<T>(c);                // "c" is actually "e"
                                        
                                        is.putback(ch);                            // we backtrack
                                        
                                        is >> y;                                // read "(a,(e,y"
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                                                    
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "(a,(e,y)"
                                        {
                                            is >> ch;                                    // get the next lexeme
                                                                        
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "(a,(e,y))"
                                            {
                                                o = octonion<T>(u,v,x,y);
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else                                        // read "(a,(c,d" or "(a,(e,f"
                                    {
                                        is.putback(ch);
                                        
                                        is >> d;
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                                                    
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "(a,(c,d)" (ambiguity resolution)
                                        {
                                            is >> ch;                                    // get the next lexeme
                                                                        
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "(a,(c,d))"
                                            {
                                                o = octonion<T>(a,b,c,d);
                                            }
                                            else if    (cc == ',')                            // read "(a,(c,d),"
                                            {
                                                u = ::std::complex<T>(a);
                                                
                                                v = ::std::complex<T>(c,d);
                                                
                                                is >> x;                                // read "(a,(c,d),x"
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                    // get the next lexeme
                                                                            
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                            // read "(a,(c,d),x)"
                                                {
                                                    o = octonion<T>(u,v,x);
                                                }
                                                else if    (cc == ',')                            // read "(a,(c,d),x,"
                                                {
                                                    is >> y;                                    // read "(a,(c,d),x,y"
                                                    
                                                    if    (!is.good())    goto finish;
                                                    
                                                    is >> ch;                                    // get the next lexeme
                                                                                
                                                    if    (!is.good())    goto finish;
                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == ')')                            // read "(a,(c,d),x,y)"
                                                    {
                                                        o = octonion<T>(u,v,x,y);
                                                    }
                                                    else                                        // error
                                                    {
                                                        is.setstate(::std::ios_base::failbit);
                                                    }
                                                }
                                                else                                        // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else if    (cc == ',')                            // read "(a,(e,f," (ambiguity resolution)
                                        {
                                            p = ::boost::math::quaternion<T>(a);
                                            
                                            is >> g;                                    // read "(a,(e,f,g"
                                            
                                            if    (!is.good())    goto finish;
                                            
                                            is >> ch;                                    // get the next lexeme
                                                                        
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "(a,(e,f,g)"
                                            {
                                                is >> ch;                                    // get the next lexeme
                                                                            
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                            // read "(a,(e,f,g))"
                                                {
                                                    q = ::boost::math::quaternion<T>(c,d,g);            // "c" is actually "e" and "d" is actually "f"
                                                    
                                                    o = octonion<T>(p,q);
                                                }
                                                else                                        // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                            else if    (cc == ',')                            // read "(a,(e,f,g,"
                                            {
                                                is >> h;                                    // read "(a,(e,f,g,h"
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                    // get the next lexeme
                                                                            
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                            // read "(a,(e,f,g,h)"
                                                {
                                                    is >> ch;                                    // get the next lexeme
                                                                                
                                                    if    (!is.good())    goto finish;
                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == ')')                            // read "(a,(e,f,g,h))"
                                                    {
                                                        q = ::boost::math::quaternion<T>(c,d,g,h);            // "c" is actually "e" and "d" is actually "f"
                                                        
                                                        o = octonion<T>(p,q);
                                                    }
                                                    else                                        // error
                                                    {
                                                        is.setstate(::std::ios_base::failbit);
                                                    }
                                                }
                                                else                                        // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                }
                                else                                        // error
                                {
                                    is.setstate(::std::ios_base::failbit);
                                }
                            }
                        }
                        else                                        // read "(a,b" or "(a,c" (ambiguity resolution)
                        {
                            is.putback(ch);
                            
                            is >> b;
                            
                            if    (!is.good())    goto finish;
                            
                            is >> ch;                                    // get the next lexeme
                                                        
                            if    (!is.good())    goto finish;
                            
#ifdef    BOOST_NO_STD_LOCALE
                            cc = ch;
#else
                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                            
                            if        (cc == ')')                            // read "(a,b)" (ambiguity resolution)
                            {
                                o = octonion<T>(a,b);
                            }
                            else if    (cc == ',')                            // read "(a,b," or "(a,c,"
                            {
                                is >> ch;                                    // get the next lexeme
                                                            
                                if    (!is.good())    goto finish;
                                
#ifdef    BOOST_NO_STD_LOCALE
                                cc = ch;
#else
                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                
                                if        (cc == '(')                            // read "(a,c,(" (ambiguity resolution)
                                {
                                    u = ::std::complex<T>(a);
                                    
                                    v = ::std::complex<T>(b);                    // "b" is actually "c"
                                    
                                    is.putback(ch);                                // we backtrack
                                    
                                    is >> x;                                    // read "(a,c,x"
                                    
                                    if    (!is.good())    goto finish;
                                    
                                    is >> ch;                                    // get the next lexeme
                                                                
                                    if    (!is.good())    goto finish;
                                    
#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == ')')                            // read "(a,c,x)"
                                    {
                                        o = octonion<T>(u,v,x);
                                    }
                                    else if    (cc == ',')                            // read "(a,c,x,"
                                    {
                                        is >> y;                                    // read "(a,c,x,y"                                    // read "(a,c,x"
                                        
                                        if    (!is.good())    goto finish;
                                        
                                        is >> ch;                                    // get the next lexeme
                                                                    
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == ')')                            // read "(a,c,x,y)"
                                        {
                                            o = octonion<T>(u,v,x,y);
                                        }
                                        else                                        // error
                                        {
                                            is.setstate(::std::ios_base::failbit);
                                        }
                                    }
                                    else                                        // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                                else                                        // read "(a,b,c" or "(a,c,e"
                                {
                                    is.putback(ch);
                                    
                                    is >> c;
                                    
                                    if    (!is.good())    goto finish;
                                    
                                    is >> ch;                                    // get the next lexeme
                                                                
                                    if    (!is.good())    goto finish;
                                    
#ifdef    BOOST_NO_STD_LOCALE
                                    cc = ch;
#else
                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                    
                                    if        (cc == ')')                            // read "(a,b,c)" (ambiguity resolution)
                                    {
                                        o = octonion<T>(a,b,c);
                                    }
                                    else if    (cc == ',')                            // read "(a,b,c," or "(a,c,e,"
                                    {
                                        is >> ch;                                    // get the next lexeme
                                                                    
                                        if    (!is.good())    goto finish;
                                        
#ifdef    BOOST_NO_STD_LOCALE
                                        cc = ch;
#else
                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                        
                                        if        (cc == '(')                            // read "(a,c,e,(") (ambiguity resolution)
                                        {
                                            u = ::std::complex<T>(a);
                                            
                                            v = ::std::complex<T>(b);                    // "b" is actually "c"
                                            
                                            x = ::std::complex<T>(c);                    // "c" is actually "e"
                                            
                                            is.putback(ch);                                // we backtrack
                                            
                                            is >> y;                                    // read "(a,c,e,y"
                                            
                                            if    (!is.good())    goto finish;
                                            
                                            is >> ch;                                    // get the next lexeme
                                                                        
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "(a,c,e,y)"
                                            {
                                                o = octonion<T>(u,v,x,y);
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                        else                                        // read "(a,b,c,d" (ambiguity resolution)
                                        {
                                            is.putback(ch);                                // we backtrack
                                            
                                            is >> d;
                                            
                                            if    (!is.good())    goto finish;
                                            
                                            is >> ch;                                    // get the next lexeme
                                                                        
                                            if    (!is.good())    goto finish;
                                            
#ifdef    BOOST_NO_STD_LOCALE
                                            cc = ch;
#else
                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                            
                                            if        (cc == ')')                            // read "(a,b,c,d)"
                                            {
                                                o = octonion<T>(a,b,c,d);
                                            }
                                            else if    (cc == ',')                            // read "(a,b,c,d,"
                                            {
                                                is >> e;                                    // read "(a,b,c,d,e"
                                                
                                                if    (!is.good())    goto finish;
                                                
                                                is >> ch;                                    // get the next lexeme
                                                                            
                                                if    (!is.good())    goto finish;
                                                
#ifdef    BOOST_NO_STD_LOCALE
                                                cc = ch;
#else
                                                cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                
                                                if        (cc == ')')                            // read "(a,b,c,d,e)"
                                                {
                                                    o = octonion<T>(a,b,c,d,e);
                                                }
                                                else if    (cc == ',')                            // read "(a,b,c,d,e,"
                                                {
                                                    is >> f;                                    // read "(a,b,c,d,e,f"
                                                    
                                                    if    (!is.good())    goto finish;
                                                    
                                                    is >> ch;                                    // get the next lexeme
                                                                                
                                                    if    (!is.good())    goto finish;
                                                    
#ifdef    BOOST_NO_STD_LOCALE
                                                    cc = ch;
#else
                                                    cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                    
                                                    if        (cc == ')')                            // read "(a,b,c,d,e,f)"
                                                    {
                                                        o = octonion<T>(a,b,c,d,e,f);
                                                    }
                                                    else if    (cc == ',')                            // read "(a,b,c,d,e,f,"
                                                    {
                                                        is >> g;                                    // read "(a,b,c,d,e,f,g"                                    // read "(a,b,c,d,e,f"
                                                        
                                                        if    (!is.good())    goto finish;
                                                        
                                                        is >> ch;                                    // get the next lexeme
                                                                                    
                                                        if    (!is.good())    goto finish;
                                                        
#ifdef    BOOST_NO_STD_LOCALE
                                                        cc = ch;
#else
                                                        cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                        
                                                        if        (cc == ')')                            // read "(a,b,c,d,e,f,g)"
                                                        {
                                                            o = octonion<T>(a,b,c,d,e,f,g);
                                                        }
                                                        else if    (cc == ',')                            // read "(a,b,c,d,e,f,g,"
                                                        {
                                                            is >> h;                                    // read "(a,b,c,d,e,f,g,h"                                    // read "(a,b,c,d,e,f,g"                                    // read "(a,b,c,d,e,f"
                                                            
                                                            if    (!is.good())    goto finish;
                                                            
                                                            is >> ch;                                    // get the next lexeme
                                                                                        
                                                            if    (!is.good())    goto finish;
                                                            
#ifdef    BOOST_NO_STD_LOCALE
                                                            cc = ch;
#else
                                                            cc = ct.narrow(ch, char());
#endif /* BOOST_NO_STD_LOCALE */
                                                            
                                                            if        (cc == ')')                            // read "(a,b,c,d,e,f,g,h)"
                                                            {
                                                                o = octonion<T>(a,b,c,d,e,f,g,h);
                                                            }
                                                            else                                        // error
                                                            {
                                                                is.setstate(::std::ios_base::failbit);
                                                            }
                                                        }
                                                        else                                        // error
                                                        {
                                                            is.setstate(::std::ios_base::failbit);
                                                        }
                                                    }
                                                    else                                        // error
                                                    {
                                                        is.setstate(::std::ios_base::failbit);
                                                    }
                                                }
                                                else                                        // error
                                                {
                                                    is.setstate(::std::ios_base::failbit);
                                                }
                                            }
                                            else                                        // error
                                            {
                                                is.setstate(::std::ios_base::failbit);
                                            }
                                        }
                                    }
                                    else                                        // error
                                    {
                                        is.setstate(::std::ios_base::failbit);
                                    }
                                }
                            }
                            else                                        // error
                            {
                                is.setstate(::std::ios_base::failbit);
                            }
                        }
                    }
                    else                                        // error
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
                
                o = octonion<T>(a);
            }
            
            finish:
            return(is);
        }
        
        
        template<typename T, typename charT, class traits>
        ::std::basic_ostream<charT,traits> &    operator << (    ::std::basic_ostream<charT,traits> & os,
                                                                octonion<T> const & o)
        {
            ::std::basic_ostringstream<charT,traits>    s;
            
            s.flags(os.flags());
#ifdef    BOOST_NO_STD_LOCALE
#else
            s.imbue(os.getloc());
#endif /* BOOST_NO_STD_LOCALE */
            s.precision(os.precision());
            
            s << '('    << o.R_component_1() << ','
                        << o.R_component_2() << ','
                        << o.R_component_3() << ','
                        << o.R_component_4() << ','
                        << o.R_component_5() << ','
                        << o.R_component_6() << ','
                        << o.R_component_7() << ','
                        << o.R_component_8() << ')';
            
            return os << s.str();
        }
        
        
        // values
        
        template<typename T>
        inline T                                real(octonion<T> const & o)
        {
            return(o.real());
        }
        
        
        template<typename T>
        inline octonion<T>                        unreal(octonion<T> const & o)
        {
            return(o.unreal());
        }
        
        
#define    BOOST_OCTONION_VALARRAY_LOADER   \
            using    ::std::valarray;       \
                                            \
            valarray<T>    temp(8);         \
                                            \
            temp[0] = o.R_component_1();    \
            temp[1] = o.R_component_2();    \
            temp[2] = o.R_component_3();    \
            temp[3] = o.R_component_4();    \
            temp[4] = o.R_component_5();    \
            temp[5] = o.R_component_6();    \
            temp[6] = o.R_component_7();    \
            temp[7] = o.R_component_8();
        
        
        template<typename T>
        inline T                                sup(octonion<T> const & o)
        {
#ifdef    BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
            using    ::std::abs;
#endif    /* BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP */
            
            BOOST_OCTONION_VALARRAY_LOADER
            
            return((abs(temp).max)());
        }
        
        
        template<typename T>
        inline T                                l1(octonion<T> const & o)
        {
#ifdef    BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
            using    ::std::abs;
#endif    /* BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP */
            
            BOOST_OCTONION_VALARRAY_LOADER
            
            return(abs(temp).sum());
        }
        
        
        template<typename T>
        inline T                                abs(const octonion<T> & o)
        {
#ifdef    BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
            using    ::std::abs;
#endif    /* BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP */
            
            using    ::std::sqrt;
            
            BOOST_OCTONION_VALARRAY_LOADER
            
            T            maxim = (abs(temp).max)();    // overflow protection
            
            if    (maxim == static_cast<T>(0))
            {
                return(maxim);
            }
            else
            {
                T    mixam = static_cast<T>(1)/maxim;    // prefer multiplications over divisions
                
                temp *= mixam;
                
                temp *= temp;
                
                return(maxim*sqrt(temp.sum()));
            }
            
            //return(::std::sqrt(norm(o)));
        }
        
        
#undef    BOOST_OCTONION_VALARRAY_LOADER
        
        
        // Note:    This is the Cayley norm, not the Euclidean norm...
        
        template<typename T>
        inline T                                norm(octonion<T> const & o)
        {
            return(real(o*conj(o)));
        }
        
        
        template<typename T>
        inline octonion<T>                        conj(octonion<T> const & o)
        {
            return(octonion<T>( +o.R_component_1(),
                                -o.R_component_2(),
                                -o.R_component_3(),
                                -o.R_component_4(),
                                -o.R_component_5(),
                                -o.R_component_6(),
                                -o.R_component_7(),
                                -o.R_component_8()));
        }
        
        
        // Note:    There is little point, for the octonions, to introduce the equivalents
        //            to the complex "arg" and the quaternionic "cylindropolar".
        
        
        template<typename T>
        inline octonion<T>                        spherical(T const & rho,
                                                            T const & theta,
                                                            T const & phi1,
                                                            T const & phi2,
                                                            T const & phi3,
                                                            T const & phi4,
                                                            T const & phi5,
                                                            T const & phi6)
        {
            using ::std::cos;
            using ::std::sin;
            
            //T    a = cos(theta)*cos(phi1)*cos(phi2)*cos(phi3)*cos(phi4)*cos(phi5)*cos(phi6);
            //T    b = sin(theta)*cos(phi1)*cos(phi2)*cos(phi3)*cos(phi4)*cos(phi5)*cos(phi6);
            //T    c = sin(phi1)*cos(phi2)*cos(phi3)*cos(phi4)*cos(phi5)*cos(phi6);
            //T    d = sin(phi2)*cos(phi3)*cos(phi4)*cos(phi5)*cos(phi6);
            //T    e = sin(phi3)*cos(phi4)*cos(phi5)*cos(phi6);
            //T    f = sin(phi4)*cos(phi5)*cos(phi6);
            //T    g = sin(phi5)*cos(phi6);
            //T    h = sin(phi6);
            
            T    courrant = static_cast<T>(1);
            
            T    h = sin(phi6);
            
            courrant *= cos(phi6);
            
            T    g = sin(phi5)*courrant;
            
            courrant *= cos(phi5);
            
            T    f = sin(phi4)*courrant;
            
            courrant *= cos(phi4);
            
            T    e = sin(phi3)*courrant;
            
            courrant *= cos(phi3);
            
            T    d = sin(phi2)*courrant;
            
            courrant *= cos(phi2);
            
            T    c = sin(phi1)*courrant;
            
            courrant *= cos(phi1);
            
            T    b = sin(theta)*courrant;
            T    a = cos(theta)*courrant;
            
            return(rho*octonion<T>(a,b,c,d,e,f,g,h));
        }
        
        
        template<typename T>
        inline octonion<T>                        multipolar(T const & rho1,
                                                             T const & theta1,
                                                             T const & rho2,
                                                             T const & theta2,
                                                             T const & rho3,
                                                             T const & theta3,
                                                             T const & rho4,
                                                             T const & theta4)
        {
            using ::std::cos;
            using ::std::sin;
            
            T    a = rho1*cos(theta1);
            T    b = rho1*sin(theta1);
            T    c = rho2*cos(theta2);
            T    d = rho2*sin(theta2);
            T    e = rho3*cos(theta3);
            T    f = rho3*sin(theta3);
            T    g = rho4*cos(theta4);
            T    h = rho4*sin(theta4);
            
            return(octonion<T>(a,b,c,d,e,f,g,h));
        }
        
        
        template<typename T>
        inline octonion<T>                        cylindrical(T const & r,
                                                              T const & angle,
                                                              T const & h1,
                                                              T const & h2,
                                                              T const & h3,
                                                              T const & h4,
                                                              T const & h5,
                                                              T const & h6)
        {
            using ::std::cos;
            using ::std::sin;
            
            T    a = r*cos(angle);
            T    b = r*sin(angle);
            
            return(octonion<T>(a,b,h1,h2,h3,h4,h5,h6));
        }
        
        
        template<typename T>
        inline octonion<T>                        exp(octonion<T> const & o)
        {
            using    ::std::exp;
            using    ::std::cos;
            
            using    ::boost::math::sinc_pi;
            
            T    u = exp(real(o));
            
            T    z = abs(unreal(o));
            
            T    w = sinc_pi(z);
            
            return(u*octonion<T>(cos(z),
                w*o.R_component_2(), w*o.R_component_3(),
                w*o.R_component_4(), w*o.R_component_5(),
                w*o.R_component_6(), w*o.R_component_7(),
                w*o.R_component_8()));
        }
        
        
        template<typename T>
        inline octonion<T>                        cos(octonion<T> const & o)
        {
            using    ::std::sin;
            using    ::std::cos;
            using    ::std::cosh;
            
            using    ::boost::math::sinhc_pi;
            
            T    z = abs(unreal(o));
            
            T    w = -sin(o.real())*sinhc_pi(z);
            
            return(octonion<T>(cos(o.real())*cosh(z),
                w*o.R_component_2(), w*o.R_component_3(),
                w*o.R_component_4(), w*o.R_component_5(),
                w*o.R_component_6(), w*o.R_component_7(),
                w*o.R_component_8()));
        }
        
        
        template<typename T>
        inline octonion<T>                        sin(octonion<T> const & o)
        {
            using    ::std::sin;
            using    ::std::cos;
            using    ::std::cosh;
            
            using    ::boost::math::sinhc_pi;
            
            T    z = abs(unreal(o));
            
            T    w = +cos(o.real())*sinhc_pi(z);
            
            return(octonion<T>(sin(o.real())*cosh(z),
                w*o.R_component_2(), w*o.R_component_3(),
                w*o.R_component_4(), w*o.R_component_5(),
                w*o.R_component_6(), w*o.R_component_7(),
                w*o.R_component_8()));
        }
        
        
        template<typename T>
        inline octonion<T>                        tan(octonion<T> const & o)
        {
            return(sin(o)/cos(o));
        }
        
        
        template<typename T>
        inline octonion<T>                        cosh(octonion<T> const & o)
        {
            return((exp(+o)+exp(-o))/static_cast<T>(2));
        }
        
        
        template<typename T>
        inline octonion<T>                        sinh(octonion<T> const & o)
        {
            return((exp(+o)-exp(-o))/static_cast<T>(2));
        }
        
        
        template<typename T>
        inline octonion<T>                        tanh(octonion<T> const & o)
        {
            return(sinh(o)/cosh(o));
        }
        
        
        template<typename T>
        octonion<T>                                pow(octonion<T> const & o,
                                                    int n)
        {
            if        (n > 1)
            {
                int    m = n>>1;
                
                octonion<T>    result = pow(o, m);
                
                result *= result;
                
                if    (n != (m<<1))
                {
                    result *= o; // n odd
                }
                
                return(result);
            }
            else if    (n == 1)
            {
                return(o);
            }
            else if    (n == 0)
            {
                return(octonion<T>(static_cast<T>(1)));
            }
            else    /* n < 0 */
            {
                return(pow(octonion<T>(static_cast<T>(1))/o,-n));
            }
        }
        
        
        // helper templates for converting copy constructors (definition)
        
        namespace detail
        {
            
            template<   typename T,
                        typename U
                    >
            octonion<T>    octonion_type_converter(octonion<U> const & rhs)
            {
                return(octonion<T>( static_cast<T>(rhs.R_component_1()),
                                    static_cast<T>(rhs.R_component_2()),
                                    static_cast<T>(rhs.R_component_3()),
                                    static_cast<T>(rhs.R_component_4()),
                                    static_cast<T>(rhs.R_component_5()),
                                    static_cast<T>(rhs.R_component_6()),
                                    static_cast<T>(rhs.R_component_7()),
                                    static_cast<T>(rhs.R_component_8())));
            }
        }
    }
}

#endif /* BOOST_OCTONION_HPP */

/* octonion.hpp
+GJN/ZKYBZqlwTb3yXE4rFR8ZSTiba1v6+5NTcEN6tpzJffz2X7m8OCdcIOHWQZHyrXt4JPcxU6EAp/v+kfWjyZ5Q/kYweaWPThK9/OLAJ9wONjsphdeljO/mYndwr+7gU3KHIJf9vaREPOviAQCcM2CM4KekmBEhRKxgCI13DYZgW8lTUy+8XzEUPveDQHZrPeT05/HpPW4O+5r8Po1hubfPWZ/jLvodWf0680kuqxzhujGaqLI+058SQNpQXa15uytWOvNuirBvuK/+JXm5sg3NwKlqcO20c7h8SneVIpssn8DkbsQtC0rlaQTHmh1JJLcc6tIs8rvPz/EwDOLULEKNVJ8iKdQ+RAv9+Par7CGndjj/pfj0E60+YtDlw104ULYc/3JYknFG3UhNd7TEzWVS/dsBLfKif3sXwdANEdeNmLZ8yIELDnRGsvs4WigocdqP5ArsOjfScNMHmm7p4bPH6iDtjbGyl3ADv9GGEtxL+iFezkhuY/XZz0LyRHzK8vyF2et0SBuHgai+6JPBYlSIZHR0K0tHpJdFuMTrSaQAYPA7T2wINTqyI7sZPFl/fKTXALiNy2NwFS50eT2GrpvQLcv7QmOY0x0n/ek4XfBIRQ/0ot9W15SoB25DitRtRQ2qYCsPwe1n6QsFxlRTtKFkk9fSHwBzGsEmfEp9RIDijGwyVPKjguR03UwkcYLeCUMtcq7mBbvRqOmNs+scTZEmB3dbOCvJhKpW0vuTr3ooKh8/+RvzORAovsuzN2u+aGvHQ+6wgtRKytg7FL+ZkWHZ3ZJB65ZRfBhsMhJW6Ofr86xdKaJ46dku80KugUZGiQpW+H86gForFDeMMGx6SqNQkdbAjBBnViY+4R92QZ31wZMddWdGo2jgpOPgjdISIxwqpMWqKFbxeB2AFwxNbxWCCdG8OqqKdCzR6kYcyMmJ1JGp9BI5M1v6fFs2TKmMyidJGkUeIl1DkNoBjcUjnCmdysYZK6MYXCgywkBL655zC2ieQKnLwjRScjggr1UX13Spf49FcRpUbIpGo9ZaantSqyJroACHU2p6Hq8KgLwx4+EEr8m2DQKlsVWDeixAjW9Z6qBTowjO/ytEELZe4gy95g6KTmHNdTxMAtnb0Fc+qO852ReTmQNTgc9jXcHorpC/nX+eUyB5xWWLKceANySnQzRWIGXE+/6bPkJCqsdfQx5+ifPQ0rZwrzKJfC34mlGPtXoRTZTc5HR2YTU8sVspewbxJKu30x/OaQvfbjtiFwSGtuIir8oU4xhxZLh889kBc/3groggwd2N7VexKtfrLkx6k+OLinUZ287ZR4u+byOAoSqHmmPyt82+4c2ytu/1CwKe5KqeUCCLZJkuJ9iIPNiY2zTIQRbTdAtEZ33RmZoZ99KSLbSVfn91dLaLxe2X790jnbX+2QNbxgl8AQQBXyTgSvPz5H7DKwBfICgRcn240bHH2FPTqJaM55xf/a/TirNTPAKLQJxzstZ8esxzRZsqizFZjqz6elRJj9CUtAAf1MKYG0eBSKNSZb6sk/Hi9HcDNVBrXs7RLqii7rs+TNG9yoO9LSwRjlUT9Q+kw6SE8eTD88LE3/SprGlHq4XnaL/Zf1fR6Obj9KgX5d3+yx3IsPgH32E9J5tS0wX2aVhSxyyRwZFioHi4cl5gOHipevsOWUcMFIITSPj9OAiU81IevZ5KuCUjmqxUdRnmrhzCFYIobn6bwcZnmfEVvg6wJdNJFcPmCRA6fHJcG8HyeYUaIC1LsWV1moFP0OzS79mI5g3v2OYD+1abLJbzWN87Ih6sE2GpJ1Q/5v/SUBlV5fXnsxQ4XiRw03kyqfU5WO6tkStfQbEuwNYgzJcnM8/mQSq5aiBHsngqgnizSp9l9hXR/Yq2RmobVXO2vD3K5PfisLDaWOTASRyZqurSUut5XI2Q6PL/9TeJ4s3zDJVC51MQya0ms9xFbo1XdHENa26K4fk6kK2gmJG+DxschRti1uEkgY/M6/Ry+laH84o0NAE2H5+BtUsCLzyXM9gILXMeX481d5Wdb6oB4AAgENLAQCA/3/114fnCcwmOkqac7dHDV5c0ncr2ZMzXWYjonQ1NfGcHPq10ah7fWXY6Luzpqq3jrKvJqziF3OLUt1W7/61+JysQ1+wmABcpVrkEf1wEKbXicGRocUqevDjPcJkAuj/d0DwTvz8fu1XNNMx4VwJMdDmCJVOedRCQDaFi1lppAWKsvZR3ysAfyJU8A7oAVRxhj/Lt/k6mBpln1h2+S0NNN1K6liIbYmsQjpMorVbRRiLweOU5o15OSzNOI0HYDnpzwuSH5Aso2+Mo2+3S42gEFFjeqhpfiJJjTV3pG9tbG7g4a0uHFPSNYgeNpc6vK2kzzuaSNFWYPYS+uF/K3RQrPDkO3OPzyNUhLVVEY/YefFDpgoWca0PYHXpf/8DkbQtukov5ngZhXW88Mi87fekTCZLAVLZ5niQcXHV4NsZMqmBHxgcdfAzPBbtXN2DMzfBLK4rjn3Y8IkULMQvuguGhtWC/G83m9G+bmXeye8RFhy/lzwIK3yaCChvIeVpyiOatCz3goO+S2bp03ktVbyWm+v2a/QpQoMZ2Voavan4x0W/eCb+ubUQmDNo8zXbAQT4khT6CMWJLXiFHeKgk1PUaHmCP3ag2ItT1YqVBJHVxjL4YhGXekuXpaqsI8z9XFyb0kIyNoynReqbid5JDSOE6tsf5J54bvKIqh6Jf8Y1z7t8yr3rGiaMQjayPlaEkNerQNYs7Wgmb4LmD9FK0wyTrrV+DZmN8TrgCISwRhsUqnuNKDuTFAWtN8TC9VoL2TLC8Dl0+ypXMGGj/LsbwOf7CVrbMUKDXJJqjRk80kXoHDwk1ljmLVjX35/u+WlJJCQUS2K+6M00FGoe1e+6YDXibAYWOTays4C/laxx8bY41NoNoeYmoeHQjEY3eHic672f4hpixKT027BocP/9bIbHhZl/lKYzqRkEzgjxgLWRD/IEkLbf5eE46VVPZNl/Wdan4S/aAhRaW+Hl/Kzr+Mci1fzT8M/w2Jow/NsJfAUPQ+/UQ/Ire2syoodX0i11V+wGkIx70cwcjxgBjPMbvU9cWnwf1PvDohgT3w3o6Q3hGb+Vk0qKM6myLtiIsaNX8322y4gqelWbBimP6cCb8MIP4qQtOlmS2IL6RYxN96qh8EFqsKJ9d0/d/i85VXDFzuAW5UZX7lcdfTWeZ329PB1A1qZ1nscwTNfYHs/efHbeLHMvz57vJrQo5qXau/z5vKa9y7gXY9a64B4MN8s62paJzI2+xQUoxhyrf4dTuQQT69j4e4xctIjdNY3uumOHxkrWHLHM/XUMocLghV8X50dOqPra6KFxdhMuyGdXmhn05EWg1Ns0QpJJnfLSTuSwH3unRJrCHct91qLlDUpzAsizG9v8YPfOy8fylSu3Ee7yF+6fye2QR6KbHQJdVrSm1hmuL5a58XmmTa5aGagvhJJKTM8p3KZ2oFoKwfKeHAngFF/xcrwc7+ZbhcbgiDG5pj66lbuPozpR49K3vFFFKqUaKYCCmVxX0qmxts9F92FzIFpGWIylLa/ivest39oFrjKZvMsCYV+HH3c7qONiaplCUKiknEsO5cHgVmfXtFbYcf/DgX5EgdpaLW7Rb1CXWIg3R1OUu7ZRcizbf1oI69qKsd/qiEDV6YL5lEIzilZw6GP62lQ0u2Vv41gtk47NN9c7R73O4TEJTg1syO/cPS49sJf8yrGOVVk6gbuxQ/ldoiN7ajFqfnOT32Q2SvOqARZcTI9/X05ERE3p62r2q9/BVLq5l9Wvq4pM6unYcHphiaKPFluWXHdLSnYtDeHxfJhEBaTigICRqA0rbaJpqkTWLiHt8VwE8Wm+FpeKMEG3FBlQCIbC+yyS39xiLzn5AzJx13fNsP2vr1ewG9DoZcWv1hdUDDzxArD3SO2J6h5MY2v4Iro7F5kDFfBiqPH3LUFWWHUjtJng7bTvB3J/7pZ6vDy08hqwPvHoEDsnnqL5tT1QA6EerZJ/0ywTiUrj8iROXwQJn3kcI9Lc12C2HOIGDMrvXzR4BNJWGVvCa+bRE9vuC/RKofWPJ+Td4mK0tG/l7fbVKhDjjkmZVjXg7XSQUe666LlhhkYvda0WuUlsbUbkpYVmrEITKCGPTN9SV8QNSgjqwA7sESXwdhGFvq6i7ELetT5FWR0rLl3MrGVam1cknHjft1aIRQ1/29oINVTkbtB0WtZu8L/hRRw+0c+EITvAKSGlG5b1EYyXfuMjFx+D9eVyKKTt6hwYbpC2G+v2RRu+6ptUOD+VfP3nUof0qaSMh6Y13OB52DhstRdi9K/mmaGcbjmzghMrxPB5XCSE29TpNKgR78Y173r6NnMCAy1AItVGBopgJb5+EBppelw4FCjj7rgGz6jfusmTyIoRnmVVmx49sc5KlDbP7nv4y44xvaMIJRa++aD2eNUIuLi2Mcm19U1l6LmP/RjygAqEWprN87Z8kJu7+jS4iZa45DuGmgvgjpC2YFtKoJ5Bc1JeeCwkk3lAgAEbn34XEIfvd+gYORLaHhKTe6cM6CeYNBIysbJJOIkU4hV9dIcPFqnyZBzoLpglB7u6DYhqdCaTgbkfKJ0/boGVw8E2hxbvxr1tbJnblj6cezKN4NGhQWrAi3v8LF0UZfMB8MIUUDvDH8/5DjDjDr7+NzuQ8z6G0TGYG/nyOYaX0uwu8LwwVDCfcUI+/f/xkMjJlglDPVgwEQuz2TfUAOEbNh/hIUzZVlJDBIYC8UbBSQlX8EMdSFAeGEGc73vxEGtDDyr8AJ0qZzR85/0MDgWr132bTobXblpfFrl+f2gvEDNVhnQ++aGvaL+nPzfesOMkmKIgtwqx8JF6N/DpXYnOgXwoSjnHp/1xZxWlvLtznPhIfJb6pIQqoLET6RSyr2sikFNEpPXd3TeMYApGtiH+71ehumhxR6EVF0ZUSuVApB+9X/iFIW7ks6r3XDPqzpvKyUlbEZ+X4QXthlaImJfKZ5ruRhg/qMPzB2T77igmg4BCdiJbUOhjZZxsHSo5dazA5ImLDm0rgd9G9Ga8Ddfzjwu6qKW8pVwxNg8b9cJpqj/jyPehp90bGsuB0sjxBWgDyTKGhhNKj0TKlPDSf0OOYI6YhbfGjFKLEXEdRI2rgZUR8QqtApyGXMHN3fY3bo9cDrFA0P/dohuhkv53Aqn3G3S4/f9jNICCKXQExgH5GawKyepz+5hQASGFjSiKA5ai+aRpNcVVBqW7M+okdKg5abcbqylpTFn13Krtp2br10Y3t70hDgjn39ktmu+dyukRNVjgBeGNZH2DDl5G3OUx/Rs+VA+McL08dBAZUldyAFjWSdf2vv1Bm178fKiPfqvnP/PupVdHZcEP2E/PC7ir4uebdfrv9+kZMMY5yRBpIVNJltlvgPr5eA55E1nifze8pUlbzX8Hp+Jn+/iz43v7dQy/fm/y1LH8nMLKBtfWa0XwpNXd//dptyyR+mH+u7IC0PXHpUsH7cUFz/bPVjeJ2nwR/W9UXm7I2Up5fyRvWtB17qxkuvI+bFIzo/esuqPecyu6Cmdmx17Cw6z4nnTdl/jFePwhmNjSotX06qTb+dct/0RQwoVsfX2WxVW5OndOGVe5mb+x7+lDx70buC0dXAt1T5/iXiez7d5BnwaW5jC4CsHvu9GjdHi1h5l6SA97cjXtyiNXrr3PmWvwOsO1Cpx3UlaqJfljEs+5uJ25wJaNHIGUVH93ZtfFqug3a2ex1bllaN7Pb7y+MbfK4GcxvYpcbuaTlbBDBb0IdalCOwWTK0/cXYuJ/x3BKAce4uoojkJSdXNXX5+vO33WWksQWJ/YFvUdnTNFoilHNUsxy0uriyysQQO2NfhwieAlf6FGiU+Ki0ePPaFhf0YfSGgyKEz/EmP6K63AVRVdDPX5BuByoA3PqHiVqzMu/yUr7kwtlabZ0psQZr2yCAZGRl2tbMXnWzvxQrvr18nb2Qn6aXDs+h65ePPlt9mWO54IQ+95MJvfu3LQJXNB0w66PTG7aboEMR4s/7tvkyHgpHoco7JBjTpdiEXxg9iqtifWarPmo0o3DwrvWpJ5a4j2ZEIKUTQsKiS3MTCfjIuyzaOJ89N5wrRufTr1LYf8MwSPExZsZ4bpzDT6Qwy+NmNkeoUtsRd/qp1pM4xWrT+4W+s73WLdCamTz97TeNCxrQQkfi4fXsLTYunWkQjHy6VZQvQZWuNulbsqIkIL0Af8Oo+20b20tcHdFf30l+xqJLR0/qs0AfiAgKUYiV7iAJOYxAlmUDGzMrJ/A+9eO3nsUR/IG/TkQ3q9Toh9/ATtwY91WpMo98pIDXOSx25DIUBBWOMfvHCBDhZcnkYteG4rMiRNlxhSCdtwS6WRQtLi6ivKq1fD2mn0ujr8YNLsTyws1bWGPPzMZh7C7k4umliqqJ9ovK5RwdI3iMdIK2/1A5Vy8gaVpHZlM20VL9gEdwqh1HAbYeWb7ZI97q+haCdv2o42EXhWLwJmdFf5wRMGedorsenrKu/RwiIp6rQdGkujzQD3FhgnbZe5v+kh5Xrh/XqAQK6L+Fb2eXa/7VEUmkHQLD24u+0VYLAsM17rLBUS+WmUVLi0nvy3DEgveLO088lyTRfEb9TMC8v7Cjf9FNFXfRU1oGHtgj7iSmzki9tIjh+EYtz1lZ9KRuZeAuyh+ZX8NtGLobgYZrmKiku+Agk6Pxzz5LkJyWvlXeR3zOAlV/r29bmci+7kkOim2PVMs6/o1Dhn8qlSWF8qj11Yf92yGOFAaV2dLT04PX1G2SGbXI3dmwjDfUW+JCM1lZ1lPdQEGBVYdGmTtuxXt6tq7/3UzfpqMR5YupHHSSussPgRLdxLqrjca3Ab9Eh3+OQYWWQ60qf/oISoPk8ykhUJI5EW8BrGAAZPlftwbwUy4zMVLftUiIAQCgiFwFaNnnROVi3+DyaLyoRxAiZsSHKwnKKPgOMWyg6z1W0kd/7hKqeOtoLa3UKTqe+pItJ3VTyIk6fII+rRMYesg/hmpxZ46JNJ8zg0m5v0nbHEmlFaoIMY6D4buxNTpRgfTs3VCPLg7ZbyJMMFAIC3dCnrs8+qDeSsh7e3YpQpFAqcLbbuhdxqDO5iaQ0HimFU3pC6V8UeybkQfR1QalYp6Gn9gh9TXF4chlb6rU17LAviTTWOUmtc4tDLW1i+7tBmrod6m8Gn+1nv7f35SXqbFBxODpuIwa4pyyTGu7Rzms8sNRNrZ5Vr170lm4p2D8W2lptNe6eIZnd5EOtUKD1cWJAslsxW6DDOVVoijTLfWEGPGODom/VYL2YwNPYc3F7rmEPYqiGNP3QevBFB87IY5dXVfHcGfilsQ9xdIiFmY+v5EDgRanT9tyX9deTcey5WihkX5dgH5Do+HCwJo/YjVeC7Fv5kX2BsJGUbIV3js0pz+egTnBxg71qj7izas5U0tJBWnv6cfPCd0htCaNtY2MivtUIMSppldbTSM0ipEyzroC5Hz05PyUYxJZx2103+C0ttHdandmmiAIA2ePvm0rs51QxIoEvngoOGpzs6ZC23sbHIuGrxa+nUq1h9i32leJYdExQODFHMzq52cQruRXcOTxVx46ri67pNipXRREOofsy8xuFM/2Fjih8c4zt58Rln+3Y4X1V2tCS+NwO/lJTFmhwRMLCI4UNeS3/88XvfkymvpVWN2fPlUqaFwX8g8zxJ8VXhrzarS6jK0qz/dxjbekO1s1a+CvrGmTRGyvecbw1DkmT3EzFYOPDw3vqMyJ0wS/hxHPFxU8/E0z5GyHjybt1s4E7tqt6zSc0jy2Nk6XqxsErQp12uMsVcCrkgLnC4qPIYbxReTKfWzQnWbz8jFSNgcrWc6GnhFKl2WqxndDtrPLneLGi/3iMdhjnmKeGGtIfldDIcdONxBem2ucRWygApRTfp7JAJm1yFdgryHdFzPg0Tq2DcAuqoa04eu/ZkK36HGgVeo8R8p3G6BP8rbsQvQaaqUzkL2te/XTxWjwhbgpk8zJ7YolPyPEOVL+HTyuefBKE+3mOVixE/EavgsjM435mk3LOAGe3d1Oc3AvacaW/p/ruzzu5w5ERf/KkBWmW72FxFzNXv7QfkvHXh2rJs+KcEX/MVK+r07LHcEQJ1tQMRJyGRprRGJ43gfoEIYNuNuMnoou8RJqKKKOKz4BjlPMW+ne4jZLZvJf0smllMBOasDimrL+ELBc/S0GtcMNrnrtiiIPFzMhBYRMGwqMjFM8QwTIOqsWYTdCRHiEnd7bi2KJCXFtWKZGujbQ9GS4n0snYxS6vMgaoFhhSUFafWMJ38RstoVdFi4TTCtjI4ZI0Cxv02ry30oruqB5Hl1ixD273WpXwkcWihFfPQX+v6mYg1RFiChei5XbnZhXcEM2tRuLtirlN4q3VCpuA9nvZMWyxQC2CwNDI7cRlLx3P9BoRrdS5FT33v5FCKu+3esmGd69OCJiaieUYE4y45Wx/NWJw+ZJCP7dvURuriPS4NE9TpkgkaHOsUfNOniR2IHFzRmexlM/jI1Vl5S8I11fCfvmkhWHQM99/qs13zcIOnUmezVFtuQPhWVUAYv8/xm2nze40Aevajz2siE/mEoKtp5h6OePMbK/r13VL6MYhZHrAYokyJnJ0xEiIMCi33f8S9j1Doo+grIL/uBJFALPPClaJMt4aoKMeY5Y64c9GnpLOx8IZr25qmfr+BInlwIvlP1lzTkbMsvz/3EHZ76FnR1Q1xVxShs2YKDfk6r8Z98LwaV353b7VumAgHIpqHA4TGXjUVErxt4sVuihtl/R1K/8TlXdbRJjsLRK8woIt1J0/GA98P2oDHVwTY0wvOnsTlbS+Unz0vo7zj4ydpPOo+jUu/WjPHvNAHuO3CMM6f7+NnfNqd85SA1OvQV+e/z5Z35XOP7TmD3HWuhoJBUKgeRqcNS1K58ZD6TDB+cSkL4rszctEW0aMMeEcasDSSEimm5yx/gsCLL6BwfdAQPFyUIQP0IVzm+zZ+ul6GEYW0GDyKHLxxcO8Hu7tqQyl3iw/mYY/SkHZPVkdWo0Ivjw4xfKSU5uP+s/Y/cwD/VtfTO9V8AffO51pvOQvJhtVX/PDoDtdpFCB1ktvndfx68yTo09woCK7d2Esm0kT6W3LON21XyT95WBc=
*/