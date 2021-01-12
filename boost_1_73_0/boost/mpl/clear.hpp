
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
g/DfGIG30XbfkirrW+ui/ODlxXqwCNbCohiExfBxLIndsDSGYRkci2XRhD6YjOVwCpbHmVgRX0I/XIz+eBnzCR3HSflB9ksVwnlbeZh4NbAa1sfq2ARrYHusib2wFg7CejgMAzAFH8P12BD3YCP8DBvjEQxC5Xhohv7YHKtjC6yJrbELhmAotsER2BZHYzuciB3wWeyIs7EzvoJdMA2741rsIdvN/bW8T8S1SspNzQjL5boU
*/