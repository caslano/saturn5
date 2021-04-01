
#ifndef BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED
#define BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED

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

#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(next)
BOOST_MPL_AUX_COMMON_NAME_WKND(prior)

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct next
{
    typedef typename T::next type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,next,(T))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct prior
{
    typedef typename T::prior type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,prior,(T))
};

BOOST_MPL_AUX_NA_SPEC(1, next)
BOOST_MPL_AUX_NA_SPEC(1, prior)

}}

#endif // BOOST_MPL_NEXT_PRIOR_HPP_INCLUDED

/* next_prior.hpp
tg5hLJqU0eIsSbGF5OiQM8vZ8u6P8ZVcCOodZC81XG3UFeYL88EYTTKZLCgr0eodvr3M7WW18GfdR7Y8UEDPkkPeexSHdUzKuXCsytmYtrMnQZ4a5dL8u35EeKCar9VLRExCFWc4ofh+SbtsGt1NwzYG8BMQ/TIqUcf13wzTjgZkwsWvLV8vJP0zkE65JNgDvLkRpmdevQSF4/KT8Rb73pNABYuIMryyryIWu+DlZlvLgsGQ7uiDCYAa+DOmUD87KWldQPEt/QD19TNl2InqX28GIhnMQCjNPhV3F+jqveMehHdZUz6hyPWC9emnb/WV6OUKuVVSeey5sbZFw/lB31Xv1JR0fr3O5W/JuPwP1EoH6kthcl46gVfofrTbbmSzQMoaauploQHjVLSloMnAETKSXpGsjLWe1ihymq9XEpvGoRKgRVwCkzKGKLbYi6wRcgvX/bsZMLWsbIW+N3cMl7FSyqx9QQL0op9l+sQBwc3mCVT/CwPBr6UszqP0mRaRk5xHX2EY3jz0OzpmlsDd1OL1bDzyZccZs8+/58qkhc5MwAcyqbQvgp5mjg==
*/