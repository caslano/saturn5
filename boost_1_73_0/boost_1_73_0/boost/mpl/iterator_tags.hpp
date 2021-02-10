
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
T+ODIfHx7/MHUEsDBAoAAAAIAC1nSlKDNxwCfgAAAMwAAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTYyMFVUBQABtkgkYE2PQQpCMQxE9zlF4a81FwjduHUleIDSn0Lxm0LSKt7efovW1TDzhgyhylZjMPZAWVLpcuPXs+hqHprkunO4Xs5AOAHh6MICizttmaUeLK8MFD+mN4z1wepBivQYv5YSh9qU/68TztCRhDsP6HZqLhV1Tbdj7BAHJfzt4HzgDVBLAwQKAAAACAAtZ0pS0EeOHJAAAADzAAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDE2MjFVVAUAAbZIJGBdjzEOwjAMRXefwlJnlAtYXViZkDhAlDgiok0q2wVxe1IiKGKyvv2+/U3GasErj0C5pNrKjZ+PKlFHWEu2bQ5qkpcgHLlY9pMCuZ0i140wwIDHKTfmoDkyUHiLRijLnWWEUktru4+kxN5W4d9TV7Nl27+PkIqfuSO4MYqpCv5nwiR1xsv51AyuO8h9E7j9zxdQSwMECgAAAAgALWdKUud+QY9UAgAAAAUAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNjNVVAUAAbZIJGC1VGFr
*/