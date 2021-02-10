
#ifndef BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED
#define BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, < 0x561)
// agurt, 12/nov/02: to suppress the bogus "Cannot have both a template class 
// and function named 'xxx'" diagnostic
#   define BOOST_MPL_AUX_COMMON_NAME_WKND(name) \
namespace name_##wknd { \
template< typename > void name(); \
} \
/**/

#else

#   define BOOST_MPL_AUX_COMMON_NAME_WKND(name) /**/

#endif // __BORLANDC__

#endif // BOOST_MPL_AUX_COMMON_NAME_WKND_HPP_INCLUDED

/* common_name_wknd.hpp
K8knuWg1FCgNUMhpZvEAYUn8KJFRymVOPLTK5wdg6jgWxqR1DuJBxDXJBjOtnlvgsa2R6ZzO4+mWFy2ugGXlruRRHtbFGLH1ftQUwMjLrC1xZ7mEiFK2rmDIdcxz+O3ywiX1YFv55V1RBpQgOHU+iMEaEAyCtXE/8jZ1GO5e/3rKcj11UZv9KNZFQUIuysJXOmgEPcAvqeK8TgSWfRAUS14UacDYEoyRnFRprZUHMboiUrRNpWVoH6MuglExNLfbAoVZJS3SgolIXaIpT0t+Va0Mykxurr7974ZGptHrhyIHlNS4+7RboQ9CxTpBuYZ+bdPgyH+NbqvQK9cuueJhZYY+JQcvOZvNVtiiaulqynxKFfHAXAJ8yyjRM5VrnhAr8kQPxJepjDnp6ywQZdxkYPE9D/0i6fujmQio5gLXaQKs3wCfp8bnif2CfIOy0vf4mpKI0fIxisl4p3/oj/qdo+Nj0Q3To1B0e8fhYbeT9MP+Yb/bCXuinU76k7AzSXi71w57Ry/DXiyOeSiSMJwc8W7a38CP2CPi0bL6DBT8IV51KtSr7S9I1VW+4EQS+lBWIsUGomK0HIf+aCHs7vur2/H59WCXqvr66mbMSLGI4fFF9FUsJzMjnUl5tpA+Ysu80HezG2EftE7DkVcK
*/