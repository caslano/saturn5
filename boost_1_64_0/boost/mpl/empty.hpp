
#ifndef BOOST_MPL_EMPTY_HPP_INCLUDED
#define BOOST_MPL_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/empty_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct empty
    : empty_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,empty,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, empty)

}}

#endif // BOOST_MPL_EMPTY_HPP_INCLUDED

/* empty.hpp
FTXSheZ2y79Syq7f8Ktq5Zek1r2ChsBBr9wTDprcYIxrRbm8FxOM0Td4MlITaxul+43Qp6r7AABrYaSsnZ4J+tIG5vdQ/zNsy52S5km1+tac8eLHlVjBKJKWdhs/DJlkBXdKj43DuTcDmngQq6Xel5tiK3lP6cO0VitOACWwmIAOrpGFGYiAUXe9aX5QRiDf1fpC2DH8qPv7SznX8WiIprgMdCPQ+h6OLlinvSJD1rDkKcOjMj54F4axrfNaTnxawq2B+c3YVse2NNrBWFts7MfMUHUwOkhjCeyi0b2CfwN723XDvPtsZLZd3S+1FbwJCI+JQIla2TPY5KUMcW+34KkU/ZZSDO2m310T4Gc4dxZbcijdtAsttbxau9s0ZP+hy4Orck0w3MCf7yBUMrEHIGSe+gBZQhU3G1rRUtjhK9TfDlXk6dFcLI5guTVe4XGhhIZAXvUf1b765hsIM9cmOrzFIV2mXv6oJWPUfybn3L/0vg7SHWxTbznjrHUMXOrYDsCr6vs7JoEqicj9p4CD9dmgi9sgJP9gc/j0xp2EqwLLPLbDPIbzUjE2ng==
*/