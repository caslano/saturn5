
#ifndef BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED
#define BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

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

#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

struct forward_iterator_tag       : int_<0> { typedef forward_iterator_tag type; };
struct bidirectional_iterator_tag : int_<1> { typedef bidirectional_iterator_tag type; };
struct random_access_iterator_tag : int_<2> { typedef random_access_iterator_tag type; };

}}

#endif // BOOST_MPL_ITERATOR_TAG_HPP_INCLUDED

/* iterator_tags.hpp
6qTqFuO4w3rYGBthG2yCnbApRuF/2LsTOK2mBQDgpSLa97RpVykllbK006qdFmWaZqYaTTU1M1pRFKEIIcuzFeJRIR4qipTtEVI8IUteyBOK7O//zZzZvjfIe89bv/tz/Ofe7nLOuefe795z7z2nJcfwWE5lK85iG17ItlzJ4/koT+IGtudGduRmduLL7MLt7MYv2IPfcBDPE884Xs14LuYoZrYTdlB4zzO891mV3QT7LnNY
*/