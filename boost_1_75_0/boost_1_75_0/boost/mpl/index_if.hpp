
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
Ows8FNnTPcAmss2PO/YhT43Zuojc12EOB7rA76Xz65rAnGQLg0ozkxVnpb/rmhR925/PyqYT6v7qVS9klc0nXet4vTtbzqjKoYQihoSj5iKipFPqzibPpRY6Xh9gI7913u4w4eWVpmvkauTjOS4Nr14J0ROF+mx8rTzkbU4JHYA0ZTBRcU4fGf2ds7sKioO9wgD84xDcnS0hhOAOwd3dAsEWl2A/EGSxheJuwd1DCO5OAgT3xd3dYRfb3cp02mmnMtP77+Kbc3fmnfO8S7TASioEylp0z/fQCAp9h0QfmgvFiaCeRY6Mt0/jWPhchZgb2iYDmxTlgOpcEe2PkkTcWykcFa6i5FMae8Yzn05zRTuVB9plVRNse5RBLzVW51z8Rsqtz53+8x+1EpiqJCfAsCugXemmZxcCEwkXQZ4f9HITlEgJad5+DB9xBO8UaReIB+kMyJ/u+zaZLMbyKgR81znDxuL+wD6U0l65qMMqaWKW9sesLiutrqCZorvVKf5uOZG3Wk3sLd9pavXAln3JQeo3UBE7hioodKN471BFVYHhJ7v0wqOqWYfOJO8Finqu6KnypacRrzoye44FAY/B83gH1tcySzZNcC5oxvVsmo+9268+FxRPWHd/GmfGplcUYgGi2EYqv4mgQfd8FGM9sCpmFWVOfKZYQUuoWbtoNZgv0lf44rf3UTB+RIMyvNSKMRpWB3VjHVzxoe3d
*/