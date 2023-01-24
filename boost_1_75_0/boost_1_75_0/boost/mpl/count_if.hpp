
#ifndef BOOST_MPL_COUNT_IF_HPP_INCLUDED
#define BOOST_MPL_COUNT_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2002
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/fold.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/aux_/msvc_eti_base.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template< typename Predicate >
struct next_if
{
    template<
          typename N
        , typename T
        >
    struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : eval_if<
              typename apply1<Predicate,T>::type
            , next<N>
            , identity<N>
            >
    {
#else
    {
        typedef typename eval_if<
              typename apply1<Predicate,T>::type
            , next<N>
            , identity<N>
            >::type type;
#endif
    };
};

} // namespace aux


template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct count_if
    : aux::msvc_eti_base< typename fold<
          Sequence
        , integral_c<unsigned long,0>
        , protect< aux::next_if<Predicate> >
        >::type >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,count_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2, count_if)

}}

#endif // BOOST_MPL_COUNT_IF_HPP_INCLUDED

/* count_if.hpp
fozrzrn5CRH5jOFu9XzxKkPqfC5Jw+hn4eQNOEnaQt7IQKVj8A94zvmaULZe/2HVh/LSPstaHdEcgHDOKAmOAm664w+fB4QG/9z0oBMKd52XexCGZ9eYQWCn/H0vyaL3KTFV/pqw5u3L++GClStniws3F5M2eYa8DhaDTG9BQzbY67RT12gS9qbH6YgHfQstrmjydY8K9EOIU642nxiftiNRNpdSyiJrPKRmDi2tj8p0HhYhAjNCRXiyYS8CjGUm6cTaRN3lDaSnHQcTxVPMR4KJpEyTOixBh4N+9HtIMHp19G1qdvHfBylVHFZYXT/ZFWwn1HuVDYXBVzZ2l1SqoVQdn9lFXqXzLQfbVS5doNxX4nGAv4TmLbU1C8P/4V4+vzAizp609rEg+i6eDQMR0fUPCc4BWg8bDebi1U90k9RJyRIJirUfJ4MAX1o/9x3sqO9Emak7eLxytWiVo0eVm65rz8tRbjxcjQ9EsGl8I7aQnsqdLHSm+t2RtOcz+kkINy0rsU8425jq6Gbevv2EXy455IFaStnhYVI0KzK6W/ebxmDMxhSBY6ZC5y/k91GuOSfkPuoapk+FtrloaWGq7kT7mby03yt8RmglbKdwWJ0SRA+QUDYSa2UDTpIWLsU3opU7p792qgyPCvSO43MQES+miOokWf1GJgNEtKM8D5Z0wkYr9Br5m6p+cq8vKYk+iwp0Kj1uinenrNcZ
*/