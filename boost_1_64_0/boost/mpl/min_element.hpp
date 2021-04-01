
#ifndef BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

// Copyright David Abrahams 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/max_element.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(min_element)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct min_element
    : max_element<
          Sequence
        , mpl::not_<Predicate>
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, min_element)

}}

#endif // BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

/* min_element.hpp
a5jEB6mR9DgEteS1JekX/gR094OGns1LbPVnfMCIjiLag/+xcXxTa/wAhMZTR8dEVQKKsb5eXOv3fLmjggGonvjDlJ1kZ+TEHD2vgeMKQ/QfFiXcAw51D6G9TxUXp4mPlFeMlSzdiIvkH3x1vV4TwXSmTwL7iPL8Wox+7lnfTgYg8ijL5e/dKoj4QrZZIz8jpak8R3RvBY6uvSMzWbDUun+bFK6uv04NfQX/w9F0SNoUWWUaOLyrIDahkCYWQ1bwrQF4a7Z3ZXt/1SvEIlHr7xUHbv2qsa6wBUvHKinRcisC1u9LBjsSpzpuejCMf732zH9znjxrN5ZVFj5+7in0CWpHNDIMjR9HzYk3yfpKOC7p3Ffv4eoO5/xlJ1gxxv8aa0AmdFtpvKuJ6R9nZEsIdCH3yOfQiQ8Tj+oik+iHnNMwSZRrHqWE+q23JoDvL/5DxpFE38Zk0R1jO4fU7vnE4L96jb5AqbjVuN6qtaE0tY4X0+TgQQGOtM3PXHUh65KPek/xB+8x0maoeHYJwx6vAK6PyWn+fCezgvpNbJI1M8re/S/ugOi/RYj/IA==
*/