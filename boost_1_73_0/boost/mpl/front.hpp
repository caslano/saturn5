
#ifndef BOOST_MPL_FRONT_HPP_INCLUDED
#define BOOST_MPL_FRONT_HPP_INCLUDED

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

#include <boost/mpl/front_fwd.hpp>
#include <boost/mpl/aux_/front_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct front
    : front_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,front,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, front)

}}

#endif // BOOST_MPL_FRONT_HPP_INCLUDED

/* front.hpp
WZ17twlmfw/e21ZeK1JurvXvOqFhTfmlJQ7TZtinhVjGh9jHgy3j4fbx1pbxXvbxVpbxzvbxlvbymJ70RyfG6D2k7S6DpMHfx7neIFDePR5KKEnoLc+QM7ydy4eW7bc0Mfbn2j60lXNjSZdlWZr6i1OywCDuXf3EsfxRo7irdCRRU2JNR2gBvlsIKutcP9FAM15VM+5bVt1fm8vY8rZFsIdMG6JOa2mbVkmd1sw2Lb2UbVrz
*/