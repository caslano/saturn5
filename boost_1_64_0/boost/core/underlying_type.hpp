//  underlying_type.hpp  ---------------------------------------------------------//

//  Copyright Beman Dawes, 2009
//  Copyright (C) 2011-2012 Vicente J. Botet Escriba
//  Copyright (C) 2012 Anthony Williams
//  Copyright (C) 2014 Andrey Semashev

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CORE_UNDERLYING_TYPE_HPP
#define BOOST_CORE_UNDERLYING_TYPE_HPP

#include <boost/config.hpp>

// GCC 4.7 and later seem to provide std::underlying_type
#if !defined(BOOST_NO_CXX11_HDR_TYPE_TRAITS) || (defined(BOOST_GCC) && BOOST_GCC >= 40700 && defined(__GXX_EXPERIMENTAL_CXX0X__))
#include <type_traits>
#define BOOST_DETAIL_HAS_STD_UNDERLYING_TYPE
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

namespace detail {

template< typename EnumType, typename Void = void >
struct underlying_type_impl;

#if defined(BOOST_NO_CXX11_SCOPED_ENUMS)

// Support for boost/core/scoped_enum.hpp
template< typename EnumType >
struct underlying_type_impl< EnumType, typename EnumType::is_boost_scoped_enum_tag >
{
    /**
     * The member typedef type names the underlying type of EnumType. It is EnumType::underlying_type when the EnumType is an emulated scoped enum,
     */
    typedef typename EnumType::underlying_type type;
};

#endif

#if defined(BOOST_DETAIL_HAS_STD_UNDERLYING_TYPE)

template< typename EnumType, typename Void >
struct underlying_type_impl
{
    typedef typename std::underlying_type< EnumType >::type type;
};

#endif

} // namespace detail

#if !defined(BOOST_NO_CXX11_SCOPED_ENUMS) && !defined(BOOST_DETAIL_HAS_STD_UNDERLYING_TYPE)
#define BOOST_NO_UNDERLYING_TYPE
#endif

/**
 * Meta-function to get the underlying type of a scoped enum.
 *
 * Requires EnumType must be an enum type or the emulation of a scoped enum.
 * If BOOST_NO_UNDERLYING_TYPE is defined, the implementation will not be able
 * to deduce the underlying type of enums. The user is expected to specialize
 * this trait in this case.
 */
template< typename EnumType >
struct underlying_type :
    public detail::underlying_type_impl< EnumType >
{
};

} // namespace boost

#endif  // BOOST_CORE_UNDERLYING_TYPE_HPP

/* underlying_type.hpp
lLdZ+4zE94270T7xjjDaBhn3aEsahm+U3GjlVa8g8e1m/15qSIP3Um8KeYBdS7ahxLP5r1wZ4EqEufI7bzj9wJSv87UG+Vz6my29EtOk/5jnYBqz4/BPOR10aGS7DTCov43PYXCU35Z5B8xlsMw7OV0q8zeASWX+zuBYZmOxYdD+6nVpvXJXh3T29ffB2KU/kYoJzn/+YOnUkXk6+dFHMwuy9TzNA2WasVqJTk5M7p1iQrten05HHbTUsqoBftP1sU3Yx/+MtPyKEo3zTryYeywN1TGuIv0xZeT6K+HaEx4eHuzdvGM4q3WhRi4s628uH5TL8Lp3Dr1iH71vvT3zQ3XPqHoh/g8zt1fVohrFR1Catol8rSrF4xrrkOMtGtkHNmdVwbbP33ikgykVzygdmnjKtt6EKfXGTdXsGJqviXOLCVHeB922pyN4cCcmaAc+QKbJDI+HuO1VROaRSB9DC7DYoFzsEcKU3Fw2eQ2W57xORy5n7eqAzjS5FDezkmP6woFp9HTAd1Npyjmbc5BbrvpgGnkfR1g0oTeK/DX+gwGDPQLD9xDA/fX9+WGZjt/+RIPriIgJz8NMOtcHxqYFpjyoNl8LQV/kCIlOV87wapVoTCUtrydJdF78jUWgByMO6OkowtUVD2UNusOTHvyzqXwoNclzjNEDn2bPN93HyWWRxv1zRb/4WFtedbSY08Z2X9O+uGpLocxXdzQbhwx4Uj+R+v5rw3rI44361Nj9mU47vhKQUd8Xs1/SGeRVsOGNedUgpjLvh44mSlEkvashjmXLjUz65D32oY5Ou4dGZmfqscLk4VOYsfnYfKsIV8zU2KJ8FbPHY9LJUIF+PabDnn1G7kPTZfATNko0vNmX0JzYKX0b1TKw7a8niTTr9cACY4TMSwnu8jtZpDPntY3+n9zpjPUR0bQAht8Ihdm9GJE/D87Qvk/HsYNUh2U/EzGlsua/8+XpunSm8DLR1jZbmcn2Y6MxWJYwxVfCtmA+qiOBxha3WoySaTu1GBXxTsOznHFuuqqonJhBbrnjlaie45dsm/UhaKon9bsPibro68S5BeVUsS0B48QcMTbrcAOUTk9zKSWYucsg0JIRGtsZdtOj/RhHqpvEdY+r/5+xtrqpKPG8RtTRTtbRJr1KWB1t3j4jqrvQJp+x5cF+43NTfR7tJHFMQ54zct8sWd9vV1p++mdSjXeYl0+fYP7T5D7NhcOeTkAnzxueL49BsTRmv6QzmKPYWE6J/g3UtP5peJDa+3qvveW5CX0/jZ3nSJZRFXKmov37JM9IJ86b3TXzvIuNYTzXYifPfYV844yZfE3aOX306AiPVO8bOpo+W0A8T95N4pEVnBzGERH1+GKSf3NvfOxGD+6u7fEaWakp/+vk3VS+WmrqlOr1fcFXwrLUBDeOgMRrSiK+MzvYe+ppXmy5yc6Epqd3ixgP0MVxjbKMeYV4gBWDZ/vi9zCCuHce7slW9fN799BriOe6+/uGs31cBuggpOFyDE0k8fHWVaeBZidFoRoI4tJ5uBeXbibMrwowY+OswXuHhnbQaaiuvh4V86q3axvEb4eyZFoqFO6hpfN07slfZ9aEB7N0Fisnxw8MaTB+4JmdIe7bw0sMjTLVbI9ka4ijrb3Uy+vfX37D4YjzabLAFgQazxbO7gxouCJW/+c4NK5BIC8sD+mwj77c44XGEY4parkW9s5M3oLzRuy5Sbq+P6qe6Te8zoMx+2Ro39dyOvZnJ56XwaE/Ql98E+LYj6CMC5HGVNXa69sAF2zW2NpFQIf2hvJezDRoM9g2lyCObQ11upRphPYx+nw/fMtQn5dDuqTPKwGX9PlBwNP0+WGgkfT5UcAlfS4=
*/