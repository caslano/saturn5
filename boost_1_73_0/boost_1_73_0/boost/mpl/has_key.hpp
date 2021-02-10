
#ifndef BOOST_MPL_HAS_KEY_HPP_INCLUDED
#define BOOST_MPL_HAS_KEY_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/has_key_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/has_key_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(AssociativeSequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Key)
    >
struct has_key
    : has_key_impl< typename sequence_tag<AssociativeSequence>::type >
        ::template apply<AssociativeSequence,Key>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,has_key,(AssociativeSequence,Key))
};

BOOST_MPL_AUX_NA_SPEC(2, has_key)

}}

#endif // BOOST_MPL_HAS_KEY_HPP_INCLUDED

/* has_key.hpp
cf1Q1sYS0NDjYglUYQcGX/aNMrBJHlgZHKWStG5C0dTPl1ffvrPXsS8nrlD4HHEdBOe/1mm2iq/P2TteJ1ng5DdHex8+0LDl7OW+pxXwyrZo6nKAcc9VSWgcJrhzhUpZeEZm9m2lyRfyMGqZqzeadO4QN2mUgOp0N7R6bz134KkDucN/qu0b/MqxPPr7hyfcro8CfmdPcQRLb7wa4ADfFVaeSFd/oqlwonncrDKP+d/yZTBDWSr0nj51VT51u/7nueOaf4NXUEsDBAoAAAAIAC1nSlLGo68uxQEAANsCAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU3VVQFAAG2SCRgZZJRb9MwFIXfLeU/XA1V2ialXgvTRjCVqjHRvaxVG/Zu3FtsltrBdhrCr+c66VokXhI7uT7nu+daRAxRyYAzJozdOXq9Ytc6vw0ztijLVf+Ar48ly3NpO9lEzQQ/1wg+HGPvYIP+gD4PZotMeKyrjn5vZZSDEp+MJzC9uYFnB3OScd78kdE4C2v81RiPWwhtUJULmLFBq4B5LZVGOvp+PL2Dyy/St8ZewWqx4h/Gk/E0Yw/ORrQxL7saC4j4O3Id99UnUFr6gPGzCS6/v7/9mE/6YosqmRZwdMoYNQceFZoD
*/