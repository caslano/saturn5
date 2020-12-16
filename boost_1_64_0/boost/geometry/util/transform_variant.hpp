// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_TRANSFORM_VARIANT_HPP
#define BOOST_GEOMETRY_UTIL_TRANSFORM_VARIANT_HPP


#include <boost/mpl/transform.hpp>
#include <boost/variant/variant_fwd.hpp>


namespace boost { namespace geometry
{


/*!
    \brief Meta-function that takes a Sequence type, an MPL lambda
        expression and an optional Inserter and returns a variant type over
        the same types as the initial variant type, each transformed using
        the lambda expression.
    \ingroup utility
    \par Example
    \code
        typedef boost::mpl::vector<int, float, long> types;
        typedef transform_variant<types, add_pointer<_> > transformed;
        typedef variant<int*, float*, long*> result;
        BOOST_MPL_ASSERT(( equal<result, transformed> ));
    \endcode
*/
template <typename Sequence, typename Op, typename In = boost::mpl::na>
struct transform_variant:
    make_variant_over<
        typename boost::mpl::transform<
            Sequence,
            Op,
            In
        >::type
    >
{};


/*!
    \brief Meta-function that takes a boost::variant type and an MPL lambda
        expression and returns a variant type over the same types as the
        initial variant type, each transformed using the lambda expression.
    \ingroup utility
    \par Example
    \code
        typedef variant<int, float, long> variant_type;
        typedef transform_variant<variant_type, add_pointer<_> > transformed;
        typedef variant<int*, float*, long*> result;
        BOOST_MPL_ASSERT(( equal<result, transformed> ));
    \endcode
*/
template <BOOST_VARIANT_ENUM_PARAMS(typename T), typename Op>
struct transform_variant<variant<BOOST_VARIANT_ENUM_PARAMS(T)>, Op, boost::mpl::na> :
    make_variant_over<
        typename boost::mpl::transform<
            typename variant<BOOST_VARIANT_ENUM_PARAMS(T)>::types,
            Op
        >::type
    >
{};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_TRANSFORM_VARIANT_HPP

/* transform_variant.hpp
IAYkAhvIAvmgCJSCGlAHGkAb6ARXQP+R0B+EAivIALmgBJSDSlANasER0ARaQRfwGgX9QTCIA0kgHThBISgGjaAFtIOLQDbM/iAIxIBEYAP5oAhsB1WgBtSBZtAGfIKhKwgEUcAKUkAucIFyUAmqQS04AppAF/AKgZ4gHMSBJJAOnKAQlIH9oB40ghZwEVhGw8bAHwSBMBADbCAL5IMiUAqqQA2oAw2gGbSBTuBzL3QHgSAKWEEKyAC5wAVKQCU4AppAK+gAXqHwExAAgkE4iANJIB04QSEoAxWgHjSCFtAOLgLLGPQD+IMgEAYmg0RgA1kgHxSB7aAK1IA60ACaQRvoBD5j0RcQAaKAFaSADJALasER4Pst6AyCQTiIBHEgCaQDJygExaAM7AH1oBG0gIvAEga9w5CAySAG5IMiUAq2gypQA+pAA2gGbeAK8BkHXUEgCAURIApYQQrIALnABUpAOagGtaAJtIIO0AW8xqM/IBiEg0gQB5JAOnCCMlAB9oBG0ALawUUQNgF9ADEgEeSDIlAKqkANqAMNoBm0gSsgNBx6gyhgBSkgA7hAJagGteAIaAKtoAv4ToSuIBwkgXTgBMWgDFSAPWA/qAeNoAW0A8t9sDvwB2HABvJBKdgOqkANqAMNoBm0gU5wBfh8G3YHoSACRIEM4AIloBxUgmpQC5pAB+gCXhHQHQSAYBAO4kASSAdOUAjKQAXYA/aDetAI2oFlEvQH/iAIhIHJIAYkAhvIAkWgGbSBTnAF+HwHuoNQEAGiQArIALnABUpAOagE1aAWHAFdwOu70B8EgGAQCZJAOnCCQlAMykAF2A/qQQu4CPpOhs4gDEwGicAGskARKAU1oA1cAT5ToC8IBREgClhBCsgAucAFSkA5qATVoBZ0gC7g9T3oDAJAMAgHkSAOpINCUAwawUVg+T70BP4gCISBGJAIbCAflIIqUAPqQANoBm2gE1wB/SMxN0EoiABRwApSQAbIBS5QAipBNagFR0ATCJgKXUEkiANJwAkKQTEoAxVgD9gP6kEjaAHt4CKwTENfgD8IAmEgBiQCG8gCRaAUVIE60ACaQSe4Anymoy8gEISCCBAFrCAFZIBc4AIloBrUgiOgCXQB3yj0BwSDcBAJ4kASSAdOUAiKQRnYA/aDetACLoK+0egHCAJhYDJIBDaQD4pAKdgOqkAdaABtoBNcAT4z0BcQCiJAFEgBGSAXlIByUAmqQS1oAq2gA3QBr/vRHxAAkkAhKAZ7wH5QDxpBC7gILDHQHfiDIBAGJoMYkAhsIAvkgyJQCraDKlAD6kAz6ARXgE8sxgKEgihgBSkgA+QCFygB5aAS1IIm0Ao6QBfwmok+gACQDgpBGagAe0A9aAQtoB30nQX9QRCIAYnABvJBKagCdaABNIM20AlC46AjSAG5wAVKQDmoBrXgCGgCHaALeMVDNxAMwkEkiANJIB04QSGoAPWgEbQA/9mwLZgMYoAN5IMiUAq2gypQBxpAM2gDV4DPHNgURAErSAG5oASUg0pQDWrBEdAEWkEH6AJeVugMAkAwCAeRIAmkAycoBMVgD9gP6kEjaAHtICwBuoMYYAP5oAiUgipQA+pAA2gGbaAT+MyF7iACRAEryAC5wAXKQSVoAq2gA3QBr3nQGQSDcBAJ4kA6cIJCUAwqwH7QCFpAO7gI5BKwL/AHQSAMTAYxIBFkgXxQBLaDBtAM2kAnuAJ85mM+gkAQAawgBWSAXOACJaAcVIJqUAtaQQfoAl4LYHcQDMJBJIgDSSAdOEEhKAMVYA/YDxpBC2gHF4FlIfoDYoANZIF8UARKwXZQBWpAHWgAzaANdAKfJPQFRAArSAEZIBe4QAk=
*/