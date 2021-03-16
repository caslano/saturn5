
#ifndef BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace boost { namespace mpl { namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

}}}

#endif // BOOST_MSVC

#endif // BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

/* msvc_never_true.hpp
lWCY1pXCPV+a9fdWgmFaVwm3Vkix2mcSDNO6Wri1NOtLMwmGaV0j3GPoV6zTZhIM0/p34R5DzcrMJBim9W1Btd49/9LvH6ZYkzMJhmldK6jWgb6R1zXr0pkEw7SuE1SrfNbZ+3yKtWsmwTCt6wXVavvXzd2a9dJMgmFaN0hWu7DegVt/bKWvTbGmzSIYpvUdQbU+H/zL9zRr0SyCYVrfFe75Olyx1swiGKb1PUG1LvraRQdo1tZZBMO0vi/cWjM=
*/