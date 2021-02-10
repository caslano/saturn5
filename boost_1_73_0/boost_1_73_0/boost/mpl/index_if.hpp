
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
j5/WyZzORj1emcJ7a6I4c/R+Ktu4mQ6/LVaj6RMdovDyHQZLa+IZ1NzAppLFllytereL12FYyI2PH97hxPqV9+/B3lnt8zvnBRHX+z1T24bPbhjeeliTRffW07N4WiVh5+ELBFWdD4IyXT/xmozyq1yxh6CNZbi4iUojToXn+e4cFi45RuHVAI+dOgBTfxFGpkfwjQMsdZ7NM4s5s/gdwdJ9sLl2H0j0XtvWwbTTXBd9goRCDfVc1hYZY7wu/COh1nc/NX+7w7Hv/lhPJvT7A+/FMxIR0Ayxd+vUwtuX0Wo9eZqjc85Fidufwk/+svh8zxij8AI8vH7P/wJQSwMECgAAAAgALWdKUiSJz9aCAQAAiQIAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNTkwVVQFAAG2SCRgVVJNi9swEL0L8h+GDWVPQV1KDg3CbAld2kPp0obeFXmMRSSN0chJ/e87st1se5Ke5n3MDDIFuTjL2CjjU0dyXHC6UW65UV+/fXpVx4A2wwl/F/Xy+XT8oox+Yxi9iNRWbeEn5ivmHfsWlck4hEkIrS22US+Z4gEiPjNFvPWYcaNOdIDOXvA50fqyUWdqp3rudhsFMNGYGdgnJ+UgBaMXu9nV9eguzfr2F/Dc
*/