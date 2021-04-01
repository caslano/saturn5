
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
l5E+2TNNMuNJGpQNgwA9IkSaZI5ZUajb18K+pwYeQ1skUIJnCuFntxqqAa1X/HgfFSiCC/Qr4gkmfRLl+R+uprnj/OIGA67C16BhRBWjWlZMp9i1PS+Jqpfd0NW10zU0K2qCaNNmnWr0ckSSLXPVtbWLHh9+NQCPToc6zO6MfrV17X9xjVo0IdjM49Sqx/sknNhkItNnhfApuAvFl+bENLmwkf9k7PC+nc5CHMppc11u90JmP8c1k+5YONBBd6QabYD+NLqh0rDd+NnOaYAufVXRak+7JHZNwAA0CRsEamLYdzROZxFux53cgyGXgdZcAvEEtAXrdUsiVmgpwKo9Dc4jbGdxVNVzObIIqTcw/IgTQvYthK9KK9umfjMDt96H2Cwj+6qiiYYDy3ZeqpVVIpWGoTSxBP0xxUsQzJO4FK8+nZ6aL18vkPxBz4t8Eeshcad/eSdTHuLQNgs4OLHT0QlnVy/ZcFFQIz0jhHkYBmBHBdAL+C1OEY1oRHmdD+fkggYEU4qJP+KTcm25JkrzUYyKJ8hdHT9Q6IxMUqMieT2F11NqCeTZNLlcDg==
*/