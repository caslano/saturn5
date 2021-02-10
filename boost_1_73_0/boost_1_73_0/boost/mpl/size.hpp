
#ifndef BOOST_MPL_SIZE_HPP_INCLUDED
#define BOOST_MPL_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/size_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct size
    : aux::msvc_eti_base<
        typename size_impl< typename sequence_tag<Sequence>::type >
            ::template apply< Sequence >::type
      >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, size, (Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, size)

}}

#endif // BOOST_MPL_SIZE_HPP_INCLUDED

/* size.hpp
HkZjOvYT6BAUFg5BNZTNFjLesFUBZYbEdAXRHC1EGp8qNq5M8eanxqV4qfd1beWSm/hjGN6prOqCBgi9YratCPNhYAgCF0SClQysK+cL1vy9RS0n/ABQSwMECgAAAAgALWdKUkJ77wPSAAAAWwEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxOTEyVVQFAAG2SCRgRVAxbsMwDNz5CiKdUyPdCghe8oQCXQNGpishimSIjAv9vrSd1BOPvOPpRKcs6km4BxfzWKzcuP2WOkgP/lHThUnapUwaSwZtE/vA/gau22Wu2zbhDb+4zlyPEgcGV3lKbaGfwPhzipz1yfu1MYGsWz3kkm3cvVqX6W65zrWI4EwpDqSMGkjxx/vjfxi8kzeNFfXBeMYtLi4KeTfHzchpKamHFK+nz9OHjbfewCuJJfzmGseG9hQhjcp1NVyuhIEEr8wZDxKKHsDNq3b54Y72e/4BUEsDBAoAAAAIAC1nSlIH5oU+QwEAAAcCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTkxM1VUBQABtkgkYE1RXWvCMBR9z6+4bPg2yWTINgl9mHMoyFq0G7iXEZtbG0wTl0TFf79rW9Sn3I9zTs7hioghFjJg
*/