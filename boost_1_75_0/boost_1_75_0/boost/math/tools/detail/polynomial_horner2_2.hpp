//  (C) Copyright John Maddock 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//  This file is machine generated, do not edit by hand

// Polynomial evaluation using second order Horners rule
#ifndef BOOST_MATH_TOOLS_POLY_EVAL_2_HPP
#define BOOST_MATH_TOOLS_POLY_EVAL_2_HPP

namespace boost{ namespace math{ namespace tools{ namespace detail{

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T*, const V&, const boost::integral_constant<int, 0>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(0);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V&, const boost::integral_constant<int, 1>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 2>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(a[1] * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 3>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>((a[2] * x + a[1]) * x + a[0]);
}

template <class T, class V>
inline V evaluate_polynomial_c_imp(const T* a, const V& x, const boost::integral_constant<int, 4>*) BOOST_MATH_NOEXCEPT(V)
{
   return static_cast<V>(((a[3] * x + a[2]) * x + a[1]) * x + a[0]);
}


}}}} // namespaces

#endif // include guard


/* polynomial_horner2_2.hpp
HciZmB8q23o1LMls6Co8B+zkGw2n8evBu1uLvbJvdC5bbgYvz1GG/xt7gS3U0SzPcAdKO8KjNbrAJagylv3NQPOZ8INIFBCVxqlSagKSPB4Ib3+LPCOPCKp46JgyAC0loHF4f4vqKYTuyP6tAfVVtTF095fFMImB+DWjpehDTks4Jygvb0lgAP0XcAvhV6rnTAkRicfM1EZzMo9fvgcvqWzyHf5pIzyYtAkGMeSi+B/Pp4jG2PmStmGqX2xytilNDDupAA4XWUZuhCOTIIX0WarnBmg62miPNn6NLht5OJNkbo9Az+UoBwAMezgmUstFqQGyxv2J2oQvJHkwF9HdRG/+S6qzrDjbjcNmwmz9sBFpe4wz5j2C7DTASt74jWk+IT/bJ9z+mtGyfasrejrbtRrxSXhSwW5X7c81PF+nXTzIF+ER+CcX/wwt2B0+n96h4zjh/9momTgAtbyAeCIxnbcG2kNPJv5kgjCMhjPBfcZBVspLL6CX+vOV9JxCUziJHlKSlxihM+Q3Vc88wMFJYKo8c0meBQh6zrUECYp8KAUWEse0A2Wndny8pF1s0y6e1i4CgAzpoky7iGnHGh/4MA4RNgLIshiaWqN/2MIxDh7tvJLh4VyfvNsXLz8tgkipntvHsGlLDRAnMw8hWcei8yy0JPjdGBQFz1SY2FSUGJ5bh/jD8+EdxeWF38Tl0KMX+Kh5gUkxuxSfwedM
*/