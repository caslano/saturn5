
#ifndef BOOST_MPL_CLEAR_HPP_INCLUDED
#define BOOST_MPL_CLEAR_HPP_INCLUDED

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

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/aux_/clear_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct clear
    : clear_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,clear,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, clear)

}}

#endif // BOOST_MPL_CLEAR_HPP_INCLUDED

/* clear.hpp
Z4Hmuaj1f/oi+kXe9L4GvP+/6n3hV6gt+TN/N/b9/X8RPgFQSwMECgAAAAgALWdKUjibVbTnAAAAegEAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTMwVVQFAAG2SCRgfVDBTsMwDL3nKyzxAQEhtIvXSygSYkonSM9T27hatJJMiQfa3+NRle3EIbKeX97zs5Gp8NAVqhSGOCYpBzp/p+xLpUz7vmm2btdsa/vRmLfavbTWuNfGKtTXb6hnpcJhChRZOoXyF+VKxRRJ+AXiSB2fMoloz3wU5tpATmmq1BT6h6fHe6FmDBi7T/ovC2QSi1ig7zyUNByIRaVnGeolk7qDwFD26TR56Ak8MQ1MHrp4eUA5p3zDZzqmLLxCiR7GcyUGK1iv4ZKk3pmm3TxbJ9Xa2jiFv/oheRm6krE3EPXiIEv9nfsHUEsDBAoAAAAIAC1nSlKJ5ToDUwEAACgCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUzMVVUBQABtkgkYG1SXUsDMRD0OXD/YVF8KdSjiCAlHogftFDooedzSZM9L5jLHsnW8/z1pta2gj6EZGd2Z2cgkjGyVhELIa2vKV1vOPQUTCzE3cvTYllWq3L5XD3OHxb3
*/