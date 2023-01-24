
#ifndef BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/count_if.hpp>
#include <boost/mpl/same_as.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/traits_lambda_spec.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct count_impl
{
    template< typename Sequence, typename T > struct apply
#if BOOST_WORKAROUND(__BORLANDC__,BOOST_TESTED_AT(0x561))
    {
        typedef typename count_if< Sequence,same_as<T> >::type type;
        BOOST_STATIC_CONSTANT(int, value = BOOST_MPL_AUX_VALUE_WKND(type)::value);
#else
        : count_if< Sequence,same_as<T> >
    {
#endif
    };
};

BOOST_MPL_ALGORITM_TRAITS_LAMBDA_SPEC(2,count_impl)

}}

#endif // BOOST_MPL_AUX_COUNT_IMPL_HPP_INCLUDED

/* count_impl.hpp
YHF3W9zd3SkOi7t7ocXdrTiLFu/i7lqsuLuV4lCkWM9yv+9+vEneS96XTDKTyTgqmxky2QfIP+hiBW1e/gH3b8dbcLrDjub/JrZB/zoGusoWNh42Hi4WNi4uFgFCApwezvY2tnbLhptumwq4ITipn3Ejxfziey0wQKfm2mW+ZHryL1oPYURG+RwMGPRZY2gv1xSTTYVr3DLt0rWn8kfpW4XNvN4n03/vDsbbKPrqG8zfXt7Wf9v3b+1wDvsnLP4ZHDw2KQ2fSGOYW7fF3ZADCyuD43Sc0CvyuvtvNr9pntg/1Di/PrZDHmuu/OV5TbC6m9zsGzcELpe7NrCav4yepRyU5hUSkr2dn/wontEU3Gww46i58l32FJDM7b+Rtyh0eylxyDP0d1DuNm8n6xVL+uVRuIO1XPltU72/x8zn2cmzS+yb4NTq+2NKwicjtynX37brfIe0kmZ++tor+QnNbXWkpiOuCW4g9bzPIIEsOXRNcrlhCrRS2jVLnj9yUU0bmGVDPmurX5rvg3qe99+enPjJuX2y5vbTww71IpTUoOMMyMpVXxij6cWLAdvXZ5VvpqmoHIUPRIkt+GlM2MkwuJ1mOY5jse5fjX//MThtpi8eDVbhrFPBNZKL9Et0IAZOOCRCBNA4JaNvbFfdat06hj6a+ou/drK1bVpr2DL2Nq94THBbi6lO2+cjIc/00uuwTR4SHAi3qEdIJ6JQ
*/