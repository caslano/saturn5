
#ifndef BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date: 2004-09-02 10:41:37 -0500 (Thu, 02 Sep 2004) $
// $Revision: 24874 $

#include <boost/mpl/aux_/config/workaround.hpp>

#if    !defined(BOOST_MPL_CFG_BCC590_WORKAROUNDS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE) \
    && BOOST_WORKAROUND(__BORLANDC__, >= 0x590) \
    && BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x610))

#   define BOOST_MPL_CFG_BCC590_WORKAROUNDS

#endif

#endif // BOOST_MPL_AUX_CONFIG_BCC_HPP_INCLUDED

/* bcc.hpp
PJ8QMsfYrJTHB/kiZ7g+kZpGkzTFVlrF2COXf1YDFzoobqwTfP61/JrIbjLZcAYP3nOK0WPbFF6JFLZFrCtwR0MwOaxuZv9QhFr28QGp6XUdJFiCvD2ysWYpcCxwbLOxQ8p+gTza7VsjA4t21uwfRZvalQjwGU+bjhHPxZa118jsG9lq7RNfEVC3swfbBXGPfZy2AGN2Q9yOL96QzSNwbrpMubbIg5+/iXbRiA/AP/eOM9HDGzuho88necdoI00OitYlfqVSEz7S3kNHd/78SQn6cmp5BT2XoTtHx+bwEvUUTYKpcnrlev4YAQwMZXTodAR24HvdgLjLumEgK70vXqVbu6gBNYQRWse3pq8irgIp6Lwch89R7h6oOU16jmIGveEfyxUpX4eG3+MnauXEVUBz+ry7VZv272LKfphYkcGkXctbLEaaE0/vs3dVAlQF3qOTR+pn51+IyRkn/Tw37PraTzhF3fWaEQ4rW+0QLUKiiPvBT2N3jzlC4i9ZF74eX8HY8VGQ7sbUz0rDasPFxMKXjALMXpSwrueVsa4cSa3OjyUDHNF01tkyvFIhi78t61N/HoygBGJgi3ncic45UDTs6K5isTYN0mXObNtrI6ra581fXqfLv9muj1nyTHQa3fC/hT6XDDgOunBMrp9chhQEZPTmapXNmbPwk2B+o40v7TDcDXPjYke0DT8ccomSKJw4weBLqrTQ5oti
*/