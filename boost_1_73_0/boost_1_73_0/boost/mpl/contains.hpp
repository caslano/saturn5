
#ifndef BOOST_MPL_CONTAINS_HPP_INCLUDED
#define BOOST_MPL_CONTAINS_HPP_INCLUDED

// Copyright Eric Friedman 2002
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/contains_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct contains
    : contains_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,contains,(Sequence,T))
};

BOOST_MPL_AUX_NA_SPEC(2, contains)

}}

#endif // BOOST_MPL_CONTAINS_HPP_INCLUDED

/* contains.hpp
FMZ9QfHDVAH4dw4hMVN1Z2foRgpttdCerpd6FHUF85r3VaPUYvg4a41IZUxz1mfjRso6IjV/8++mU5sYv0PBdjiqhJabCv666cBEaS/AgQ2VkgrUhXDsFRZyt7MLR4SA0uuFPc3nJLjupySrdUaPCOeF9vWIb2V9R8U3HQyHwTYGFZgKh12Diml4QxQw0ZU0E7s4i9OsZ8vT1/k8TlPgeuQqZIng33okPAz97JBzPCJDgr4LhI2SRhaytucvsK25wJMDei/CgAwnMzhkIbUJ4IMyhzwUBTY2dUNvPh7s9BLKusZahjVNzYvBTvSX27atu5Fq5+5VjaIHs95y/gMQxti/wGAtc7JJ79mzsejlp/YHUEsDBAoAAAAIAC1nSlK/vp0wjgEAAHQCAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTUzNFVUBQABtkgkYGWSYWvbMBCGvwv8H46EUijLJK8bY0YLjJA22ZIltN6+DlU+z6KOFKRLQ/79znbWDAbG9vke3nv1njVhImsSToV2vg78eMbTMcQqTcWiLLf9De7npdDy0tFygMVYjOER4wvGSXIVCh1x354YqAwZ8ME2aJ8/j06YRoOezN8qeKcUbL5BOibbhoSZWJlEk3WoXO2wKqBs
*/