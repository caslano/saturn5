
#ifndef BOOST_MPL_AUX_YES_NO_HPP_INCLUDED
#define BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

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

#include <boost/mpl/aux_/nttp_decl.hpp>
#include <boost/mpl/aux_/config/arrays.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>


namespace boost { namespace mpl { namespace aux {

typedef char (&no_tag)[1];
typedef char (&yes_tag)[2];

template< bool C_ > struct yes_no_tag
{
    typedef no_tag type;
};

template<> struct yes_no_tag<true>
{
    typedef yes_tag type;
};


template< BOOST_MPL_AUX_NTTP_DECL(long, n) > struct weighted_tag
{
#if !BOOST_WORKAROUND(BOOST_MSVC, < 1300)
    typedef char (&type)[n];
#else
    char buf[n];
    typedef weighted_tag type;
#endif
};

#if defined(BOOST_MPL_CFG_NO_DEPENDENT_ARRAY_TYPES)
template<> struct weighted_tag<0>
{
    typedef char (&type)[1];
};
#endif

}}}

#endif // BOOST_MPL_AUX_YES_NO_HPP_INCLUDED

/* yes_no.hpp
zRHc3EMuDNwiKvBMrq3H4kW7t22itlrqss9o9GFd+oPi/EiK2zfyqfzNCPTYBakZwTdbeuyGHMfP7ohMBJJK83c+Dq9nl5Nxj51JiRXBr/xXPTZ1svNtryK4Qqz4WUki9FjvxyTczP4qIs5iG2VoSmxK991vv65+yz0U0nP4/aFoWf0wARF1V8ZaPlo+Gc/f/iF9AVBLAwQKAAAACAAtZ0pS3GSWEk4BAABDAgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwNDhVVAUAAbZIJGBdkk1PwzAMhu/5FRbTjmkmxAGmqJcxARKIaa24Z6lLI9qkStJO+/e42Rfj0DRWHr/260RGDFGrgDmTxtaOfj942DtfhZy9luWmSCu8rEu2WX+ARh9NbbSKyKS4olIcs9mMzaBAP6LnwVQEeezbwwScNolYtQZtPBE6BYTUqOLgkeSK4n36emOtsd+UfD2SIannrImxD+dardOqbVwgzTHrsaOUMyet6sjepIVVP+yoabCOdyrqBrohRKiVaQFHtLBvaDE2oKZipHFMldp1nbJVzjg/HwLnWk3TgHmxXT2/bcUUBLGusF0Nvt06F4nINBGc3xS/TfhvILM2eRh2WYUeksulEJfz5Txdy+ZzW4r7xcMj
*/