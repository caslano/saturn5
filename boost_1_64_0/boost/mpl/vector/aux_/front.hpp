
#ifndef BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/vector/aux_/at.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct front_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : v_at<Vector,0>
    {
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< BOOST_MPL_AUX_NTTP_DECL(long, n_) >
struct front_impl< aux::vector_tag<n_> >
{
    template< typename Vector > struct apply
    {
        typedef typename Vector::item0 type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_FRONT_HPP_INCLUDED

/* front.hpp
8Bm2jWI0oxejiPks1xJZKEIFqlGHDvRjHHMKOG4UogoNaMcwZm1g21iDAhSjDDVoRicGMITEz3H8KEU16tCEDgwi5fPsC+nIRCHKUYtu9CGMWYXsE2tQhhrUow29hUGSj31hGfJRiib0YBzxX2A/SEU68lCIKjSgD8MIfZGywxoUoBL1aEYbOpFYxPVGGpYhF0WoQBN6MI45m9gXcpCHKrQjjDEkfYnzQjbWoBhlqEcbejGEGZu5ZliGLOSjFHXoQD9SitkfUpGJQpSgAd3owzDGMGsLdRlrUIl69GIAo8GEzZ3sD2moQBNa0YMRxH+ZfSEdeShHFVrQjT4MI6mEskQGatCGASRuZfvIRykq0IQO9GMEc77CuSATeahCO7oxjNBdbB9rUIBitGEAo4gpZR9IwzLkogjVaEIP4rexfeShCrVoQTv6MIbir3JN0IyYr7FNLEM+qtGKQcwpY1vIQSFq0YIwkrZT3liDSjSjDZ3B4uSvUx6YhzQUoQ79GME4UndQ1shBCcpRhW70IYxQOWWNNShAMWrQjF6MInEn+8EyFKEC1WjCIOLv5jyQijyUoAp9CCP0Dc4DGchGAcpQiRrUYwhBgmIeslCEOrSiB+NI2cV+kI4q1KIdYSTdw3kgGwUoRg3a0IleDGAUM+5lH8hFESrQj0GkVHIeyEEhylGFdnQjjGGEdrNPLEA2ilGJerShF4n3sR+Uogk96Mc4Uu/nPFCIdnQjjFAV28MaVKIZA0jcQ9kgC9VoQgd6MIJxzHmAuoRClKMWDWjBMDIeZLuoRD3a0IshxFSzfSxDPipQhw70I34vx4wc5KEQJahFO8IIfZMywSwsQAaKUYYadGIUiQ9xDZCFfBShAnXoQA9SatgfMlGOKrSjD8MI7WNfWINK1KATQ0j8FvcE+hH/bcoFmchBCarQgj6EMYykWo4bC7AY2ShADerRi6HaIKlNGSEXFajGnO9wLZGHEpSjCrVoQTfCGMashykPVKINvRjCKObVsV3koxp16MAgRpB6gPNAHspRiwZ0I4wxhL7LPrAGlejFKGY8QpmgFBVoQg/GEV/POSAdmchDCcrRgIKDbAv1aMMAYr7H8SINuchHKerQhFb0YBCp32e7KEQVatGAdvRhGAsa2A/K0IZeDGEUMxrZD3KRj1JUow4d6MEg4n/AeaAK7ejDMEI/5PpiFhYgG2tQgErUow29SGzivJCGfFSjCR0YRPwhzgeZyEEeClGOBrRjGEk/Yl/IRjFq0IsBDGEUMT9mX1iGUlSjDj0YwTjim7kXMAepyEMhSlCOKrSgHWGMIXSYc8ViZKAAZahEPZrRhk70YgiJP+FYkIsmdGAQI0j5KftGOjKRg3I0oAXt6MYYMlooW5ShDZ3oxSgSj3AtMQ9ZyEURqtGEVnSgH4MYR8qj7BeZyEEJWhBG6GeUMzJQhmZ0ohcDGEViK9cSy5CFfBShGq3oQD8GMY45RzlXZCIP5ejGrJ9TnshGMerRhl4MIfEX7Ae5KEIFqtGKfsS3sV1kogRVaEE3ko5RV5CNMlSiE70YQOIvOX5kIR8VqEYTWjGC+F+xfRSiBLVoQR/CGEaonf2gAJVoQy8GkHica4Ms5KMCTejBCMaR+muuAfJQiBJUoR1jCJ3gXJCBYtSgGZ3oRUwH+8A8FKECTejAIMaRfpIyQiHKUYt2dKMPod9wLbAA2ShAG3oxgCHM+y3ngX6MIL6T64pU5KAEtWhBO7oRRlIX20UGKlGPTvRiIHgRzGNcB+SjAk1oxSBGkPI7jh15KEctupHUzTZRhma0oRejSDxFmWAe0pCFIlSjB/2If5xjRyZyUIIqdKMPYwj9nnLBAixGBrJRgEo=
*/