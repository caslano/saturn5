
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
qUt99nzHTH8YE5R/Wh6rKLyWSJ/vXMpHpv1fg57JsVbPc2wukJ52S4F4u7m+QPyLrCuQHncriHJAtRVIz7u9QFomHQWiK44VyMt6Q4HY3XcWSA88rmeITLYPe7JjBhZFNmhlK6hWz5zdR+WF/znXod4bVmk1Na+lEApRv0BrPot777Cn6aUOTNeBopCak1VoZiYJ+iE8UOVZG1LtxhVb97TsSSGiT0VJTdPY0hPAOc0KFTwYs/Px0KHXR2SwIyY=
*/