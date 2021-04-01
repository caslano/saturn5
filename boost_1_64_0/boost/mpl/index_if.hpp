
#ifndef BOOST_MPL_INDEX_IF_HPP_INCLUDED
#define BOOST_MPL_INDEX_IF_HPP_INCLUDED

// Copyright Eric Friedman 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/find_if_pred.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/iter_fold_if.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct index_if
{
    typedef typename iter_fold_if<
          Sequence
        , int_<0>
        , next<>
        , aux::find_if_pred<Predicate>
        >::type result_;

    typedef typename end<Sequence>::type not_found_;
    typedef typename first<result_>::type result_index_;
    typedef typename second<result_>::type result_iterator_;

    typedef typename if_<
          is_same< result_iterator_,not_found_ >
        , void_
        , result_index_
        >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,index_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2, index_if)

}}

#endif // BOOST_MPL_INDEX_IF_HPP_INCLUDED

/* index_if.hpp
1+E6p+WmPfkZ6LIA2wIJXQXqWzTfgjMmDauIzbAnSXI4fsUBrPHGFZ/rVSMc7TVfqZ38t4FnpwpHPXNwmUedGxeQ49qautyZKPsizNFe/SYcbnGJ07EJopNDYMz39bt3T9JvP7AxpaIRmhOcIa6KlNeS9oACBSY3kaZ5iWVcYi0IF546TRty0MZNg+QYmCgk+ZViNWlAFCuGSQ8ElW2ygEHSF9I1EQhnjcPtBKV5HP6GaiLd63nMNOblyPLvwnBS3imQ+xYtVhmsHAD701H4HugqkPdJPjSgalo4aOnegWc4Mj5Y7agAk/ykQ3eZKbVtGMEafT3oRJQuZ/o8ehWYDkn7NmyofzyvWDM64IgGYt8V3geYku3wtoRIGNMvi3zLW46SWnptuVo3MSImK31rt//blp4s9gNaveb6H36i8Q1wicKjLbaGBwU5Xa2pwA5turcYAPzGfcdtQ4JZmqO5bQqbROGSs/nc7ASHc75yRT+3/mUteXtws92mFAeXhKc1w3LEX+VENprsTr4t0ZNbT5PWb9QBcruoGEsCRORlc2aO2u98FJOjpu5n8w==
*/