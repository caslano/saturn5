
#ifndef BOOST_MPL_BACK_HPP_INCLUDED
#define BOOST_MPL_BACK_HPP_INCLUDED

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

#include <boost/mpl/back_fwd.hpp>
#include <boost/mpl/aux_/back_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct back
    : back_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,back,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, back)

}}

#endif // BOOST_MPL_BACK_HPP_INCLUDED

/* back.hpp
lTkU9+lROT71F+AV7mtn9X77+/SrPecHMsJl1JAQUUJ9SwobMDPrseXJd0uDS9azzf2663xzMjd6scfQXGPm/6Vyausx3sv8mdRBZ/NvoCembKFt//4il5DdorOMMVjLXyzl46U4CL+8ULchiz29DvN+NACOLN5oGc6h45+c7/qQDEKOn94ou149onOT0f00KtWlUxfED0aXnfzdr82Gv7/+SFnt96e4JuG9OuF90CP+99KE920J7+se9b+f73+nrmFSDmE7H99AJFvnzskgebXuY5az4XHWNSnTmeKu0KI/CUxoHWk4weUlFsaspfgdXJJjFqNub/sfWNWCP8kzZFm17tBKoxn2TP+w6279SD5i2HQIyPlv8UFq9cSE4oflP4wZ7LR7Ybmv3WXyyjiXhGJytCccmyBm3X3fb5nL+O8lyytTFgvpd9WO8NYs3wCG0QS86VIryRI9jZrhD4VSSzJYrMSGwurGDHlxXGZDM1kU2KFg+Cy1DyKMRhM9RGHUigbsI68xBKz/Cl5S1D67Lw2JIjTnySsT3EXwvR1/tytuTjQX6/dPLC0/p8Xyr/F3++SE8onnn64y9qwmEfPIa0geRt3OsigT8FTXP0sDd3A0ovJOcllpxdxl/Shj/J14LUJYdVj3MCv3neOd6DVIrw/xa1o8eCA8wLE376WeADNNlLeMbwF0l0H2kjyXDeZa7wbcIZ0uQ3raxcJJxzAy7RwPnC0BMYo38WDFlOzV0xjOCM6HDpywwokYOI0BUyxDiv2qq1usIbnYGzOl2CYVXPrc5F00qdDnTqFZWugBU2ipSijdrnUloiqNXaNmxWfGILcIOwwxGExC4ywDcYRgX3EdEa/QXnqaxO9hitixCSGW7cqGWu20POScB8+RDcL2wSTaphiorPW4YXWacADsizEoBgyXnOGZtYxhVjKGa2cIrBXaLWExM4w7wZEJxvJmIlw2e1gRB0KmQrhKIMTPQZ2dfUtd6UmAGRGY9ce7MCOAGWGYPZJhHj7Ds7BFMOZCWN5+MOufsrz9w39OfOoq2qN2Dlc7q8Rg+yhSvNx958GeQdBOSPS3C1VQfAcHFphXDE8pYyaBhaCvGOLiufgQKMumDzhOm2UUAfuUK5ED0+O1S1XGnIyRf+HZPhlzEKYuz3+oDx/r13qM4XpaX8S+rEYK52EQ1bolKGHPAfhK0UGh3TbRQI8VU9HdblGMVNm9vmewHt9N/VrPErbSH86q966ueufM0J1oPAiLLjtHz+qDF4eJF5/i3v9MKR0p5QQT3KGykBIClNDHBFFIdVIO0SugHTA50VOlj8dam0S+O+wClbOnYPWPuOEzIKWc2amfkVM6OxWGccQ/2C8WkPsdXNwiLAxMyugX69jGQ74H8PPSb6nSr+tFhn6/udBDvxOS6Nc7iX6dfPQDbYYobZ5LkfH/LaVNT6GNRtvw0Katp5lbnp+DsP8b5flZnWBfctdDXSvFRIE9f5pjh4nMWDECPt8ZbEW4No058AXORJ5ttZeJPFgaUvcX2nfChj2ddD8ehTJoQpceLQfHK+nkO33ojjepJAuVsNhHp+MZ+CXJwF89T4Avb48ZKAWCJDcqVHi0p4lt110cr3AgpSqkSgNpIiAJfrB8FDlo4MT1Oguw3GVxdjKskwysL9pxk1GUSs4co6vtgvJdPFSyFr0c1AxEQpxgstnUUrOgvOZW+jSvt3WzQrc4FqxW8OZ0qeCuduwsM84rqyx1WanmXmNyf4fRKbSxJ7DzJA8yDwUZmWfRwbYh9u3JxLYMnKMEDkh7ybHuboddmUFBPOeRDL8zZX5v6ycO6jEP6r0NkHfIQIjmmnNLU11T4hZ82ik2xhWeD48=
*/