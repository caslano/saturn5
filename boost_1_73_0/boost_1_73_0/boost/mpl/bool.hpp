
#ifndef BOOST_MPL_BOOL_HPP_INCLUDED
#define BOOST_MPL_BOOL_HPP_INCLUDED

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

#include <boost/mpl/bool_fwd.hpp>
#include <boost/mpl/integral_c_tag.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN

template< bool C_ > struct bool_
{
    BOOST_STATIC_CONSTANT(bool, value = C_);
    typedef integral_c_tag tag;
    typedef bool_ type;
    typedef bool value_type;
    BOOST_CONSTEXPR operator bool() const { return this->value; }
};

#if !defined(BOOST_NO_INCLASS_MEMBER_INITIALIZATION)
template< bool C_ >
bool const bool_<C_>::value;
#endif

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

#endif // BOOST_MPL_BOOL_HPP_INCLUDED

/* bool.hpp
CIPapFLjhImiyhV93vD4rppMT9giSdb2gLt54i6z1XI5n3VG3ag/R2ZPs68qLJkILtkicIDsCl6wOWDj6yJDJhqsyyO5U0UpqXFlgmgQQRyGsHrw2E/0ZYMcNkplHvMI6RwrMmnkPymg33VaKo0e+yoNZSZ7/AThGJbqQCFRCNGQD8ecgu+eEo85Phxa8b62RpDLN0p/lPTypLIiLzDrcKIbuN9XbSnCiXkUnnHmidxw6MVRGI/8LP3i34yHn+Ph+LbnsZmqDFbGf8RqY7YcRh5j2qia1DgNdOlacQWzsmhjXYNSa5BWx2zCtsbU9vBdx0Vw8gijVDlhZfEajeJbcjgbRCV3NNIXrGVDDSmPoGtMrSg3tQ4BtigzbDRoqghFBdK57cBBBA4GaFa7nawyurY0eBCYLQ5UmQ12SvF+O4316jkJWhLQX6xekm9r3l8/r379bt/tADsAkaM0+wZpQU5iLi8U12mnnvzApsiP0DYLZG6ILBW1I4Ot1PCKWEFPb5XpMXGwsQRgMSeM6P8H09MWeWyhtOHwYajHpmmKNbmvg2uPrdsC/sztY6EqDg+ItT8tiwOtz3dqqz/dkAQOC6oP9n7K+tgbuxXvmIvgrCW4/Jt/AVBLAwQKAAAACAAtZ0pSCvaj6FYBAAA0
*/