
#ifndef BOOST_MPL_CLEAR_HPP_INCLUDED
#define BOOST_MPL_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/clear_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct clear
    : clear_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,clear,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, clear)

}}

#endif // BOOST_MPL_CLEAR_HPP_INCLUDED

/* clear.hpp
dCJAPdd+ODzUdIT9heM9O0meKqHcwnBCl8mYv/+lCruJi9ICWoXK8nmdcWzNZMZ422EnjTWti6zLu3SdR19zk8p0KG9hnMDEWTtOe8p2ZAlIk5fc5QEdtIKyEvGQpACQ1PU83svm7EsciT6PZqvXdYc1r3BLnqrdK2kayRYXX+2FG16RINCvmS+eNkdvaeTu7FU/DUCvsiaADizKdLaAywdcrcr6DlvuLySPsNaf11nsN9P0plQgWKmAnHNERl21PZ7BiovHUFNEOB70tTbL0IbtYDCdY7HaLC7vxfjJ5/b+9OrRMHppr+CZ/BEVcPV1VTH2TNpa2TRXFfTdEJpO54wVySBIZAmGBh7eKcjxVzYguob4IZnywNPdRzBDBQ/GLBCJnnPawmDZodXzRIvFGrXNdI2Q3OiA9LGLe4ySJpqNV7qsENRGKH80QkQNMw7S0oPrOSdRAXDHYZ/6Z/sTD0VX7GQLCdfhzI9G+Ynx+WVEObwEyD/88GcW/7gFjCAzBM+75lKEr04V6AZY5JPfmEvLZCH1WVpBntRRFbkrsV+zU3VdVLo+37QPTw==
*/