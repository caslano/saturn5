
#ifndef BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace mpl {

template< int dummy_ = 0 >
struct multiset0
{
    typedef aux::multiset_tag tag;

    typedef int_<1> count_;
    static char (& key_count(...) )[count_::value];
    static char (& ref_key_count(...) )[count_::value];
};

}}

#endif // BOOST_MPL_MULTISET_AUX_MULTISET0_HPP_INCLUDED

/* multiset0.hpp
Zn9MbcnGfaDf/M47zepk1b3ucschkh2/VKrEkP6tRhjAn/4pSr0urpI2cbfWLd/7KCHtbMKEcxRPQJguuf83gqReZca7QuKZdp9RGdBvPYxCRf1GFvPLuYCb4trSWXq0fW7deDp7Gl57Tco3ePuxmb11o6oCbTlubO5UkTTeDOqtlibLIucoFIenRPPXl/2eoXsp1Ef0cc6c+3Izzqie6Lu47ZyQ89H5UWmhlo4qVO6wqyLHeY4/Dd8UpMtd1uGD81jYeYo9hKn35DhQXqJ8OT6Lwov2774rZKT9VqysI0tHeqhzwJaemzUqbQhMGEA55tDv4xqSc2aetSoictBlIMdL5TLM/iM9sLJSgw+HO6gYJUMS3zzq8TPprot6616vVO2H/O7vq5+StxfHBW6KJSKIxh9MD/10p4IFMwigUdGkQSI3dcoORMEGiBJbJIGQrjdGDmQs3V893tNsZV6w3PTJXpB5fCALYDyIJfd757WregNS7I0/sFDs299Cu2DyJswKqcqt8iXthGPt4d3SvrB9IPMm90URDdDPRYYRVvaBLnh977wbLJhyHrQ1JaA+YWEPIBNoIR80NKIvGrR0S0+Io5fguFXFgVGVdOkQHRHyJyHmk6m3CPO2hc7gNK1J+0tExOIkx6XgKZrcVJcapItA8npb0jfzZm7+u9CCAHvD16I9SkzBkZSyrIduTHzoliePckalqhpdeQL3
*/