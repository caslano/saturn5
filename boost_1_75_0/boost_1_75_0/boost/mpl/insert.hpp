
#ifndef BOOST_MPL_INSERT_HPP_INCLUDED
#define BOOST_MPL_INSERT_HPP_INCLUDED

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

#include <boost/mpl/insert_fwd.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/insert_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Pos_or_T)
    , typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct insert
    : insert_impl< typename sequence_tag<Sequence>::type >
        ::template apply< Sequence,Pos_or_T,T >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,insert,(Sequence,Pos_or_T,T))
};

BOOST_MPL_AUX_NA_SPEC(3, insert)

}}

#endif // BOOST_MPL_INSERT_HPP_INCLUDED

/* insert.hpp
nLHDDvokPR8GDtEPJ7PElDIvYryNF7fxSkR42MHf8Wvq90vaiq+T6ByuCe1n+A3b2kWOgNT40xdEOdEB7FN03+TqDIZDT+k43UX7EaaTtRa8HrV3djEwOW5fu5Nwqq274Q2vpb7rQrAKLchhgcSkl6JVWnJjv5Nk8VJmPaqTaFXLN9BhuIGD7s5pfHNxcVTmfNSImOAa3AkVmKHbvlq/HtY94579zhbm/8Z6SncsRlo/wf+P94xUfUNLBHKBys7OQIMTrvYvblgPDmgH0KIJRVEf8s+beNe7SkrcNr9bWjM6ZsBZSWJLDYcE3tCZncCSajTp9Ff4Bp9WdxAOOXOA/RDWvUGOHRvgnp2hci20/sVSf7Hj6+YuWjI84qtXQJmZkap/3HdNwQNVAJ9NHlqkniylN6XATk/RMkDD8cbxEWkwkKHzK2HNUnLjTs1AIzBaY9+lgN8pjhLjAeAhgWx6SXu1vwVLoITNVgcH+rakv1riQQmq1+/j3gVh39MHUw+vA7jJRQIkLnS5C3teXbmnbjE+6K3FYmpfYn4fWLdTzQp2X3N5bbuzqYWkmpL7CsAIoJ1yhSDxjHw5f3GTXpHkV+iACets+TyAEKZgvRo5KYhLsFMN6a7Qbxu18z6oDAsn6OCq+c3f6MQUIDiaiycUfdV6A6bYktUzOFBHrz/uVrxav0HpLZsHFMMc2rTgHep9EacYeRaRHzZxHp4E
*/