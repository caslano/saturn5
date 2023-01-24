
#ifndef BOOST_MPL_COPY_IF_HPP_INCLUDED
#define BOOST_MPL_COPY_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
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

#include <boost/mpl/fold.hpp>
#include <boost/mpl/reverse_fold.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/protect.hpp>
#include <boost/mpl/aux_/inserter_algorithm.hpp>
#include <boost/mpl/aux_/config/forwarding.hpp>

namespace boost { namespace mpl {

namespace aux {

template<
      typename Operation
    , typename Predicate
    >
struct copy_if_op
{
    template< typename Sequence, typename T > struct apply
#if !defined(BOOST_MPL_CFG_NO_NESTED_FORWARDING)
        : eval_if<
              typename apply1<Predicate,T>::type
            , apply2<Operation,Sequence,T>
            , identity<Sequence>
            >
    {
#else
    {
        typedef typename eval_if<
              typename apply1<Predicate,T>::type
            , apply2<Operation,Sequence,T>
            , identity<Sequence>
            >::type type;
#endif
    };
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct copy_if_impl
    : fold<
          Sequence
        , typename Inserter::state
        , protect< aux::copy_if_op<
              typename Inserter::operation
            , Predicate
            > >
        >
{
};

template<
      typename Sequence
    , typename Predicate
    , typename Inserter
    >
struct reverse_copy_if_impl
    : reverse_fold<
          Sequence
        , typename Inserter::state
        , protect< aux::copy_if_op<
              typename Inserter::operation
            , Predicate
            > >
        >
{
};

} // namespace aux

BOOST_MPL_AUX_INSERTER_ALGORITHM_DEF(3, copy_if)

}}

#endif // BOOST_MPL_COPY_IF_HPP_INCLUDED

/* copy_if.hpp
l36dqPHcpibIpsD8gW/Cu+hl7FRkwuhSogSwcZJzYnje7EUT3TAYQe/mwwrREQ5AEtOqX6K6seOcJCxTXqvF6NhZTuFcNrTPTC0pPxiks7ljkzQfltQTXaMfHl37uMLi4aUVwKlV61tv+v6+fhsG/ht1XVtvd1Rs9n7gsXWDRmV7pHHjNglETXsZAq5vujRiX3B7OVhZjSXifHYF1S/EhPvbJ1mHWRAEYzyJ4lExPoQIoykhy8GVwlHMfVxBNqR0wGbGp2Y77biHrtcprg/q0iEFsZsbKWAFEBsHF6UFRV8wpial35rSxaVgRT3ZsK6mZLbtqF3eUvnfmeTKw0RFjxvZ0f96EdEn6UKr4f6JFSIePeyzDYe7r8FKYTeZIZXlDufPgtUI/1h0L7CE2dpyEfHAvYHJFjLPy437XAPUNR+r23rq7ZlyHOIxe0668CdzYJuFvryQKfTtFTAw8anLiSCUqMYbIPmQWSS/xQB4sRXlBctcw22tC29G77GzbvrOyx1q6nMa9ByrGybbIMP6PBXq65+emxVupEcAJvTX+hwH001C+x7zngs8PCfNhwr6UDDNTcVGMyQJJelLWSdk2nj0Pm/zkzucc4B3evO9d6An0McQ5oqGMi0gBEi6LWjIUv+RGoEWZ9JuuDLgNbAEyJqPp/ml+oM6LIdcL0C93wClGmYJ9iyA11CgHmblsy0sJ9saiFkdlf2DOhB+
*/