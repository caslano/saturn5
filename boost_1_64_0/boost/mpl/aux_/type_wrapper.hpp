
#ifndef BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED
#define BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Peter Dimov 2000-2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename T > struct type_wrapper
{
    typedef T type;
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// agurt 08/may/03: a complicated way to extract the wrapped type; need it 
// mostly for the sake of GCC (3.2.x), which ICEs if you try to extract the 
// nested 'type' from 'type_wrapper<T>' when the latter was the result of a
// 'typeof' expression
template< typename T > struct wrapped_type;

template< typename T > struct wrapped_type< type_wrapper<T> >
{
    typedef T type;
};
#else
template< typename W > struct wrapped_type
{
    typedef typename W::type type;
};
#endif

}}}

#endif // BOOST_MPL_AUX_TYPE_WRAPPER_HPP_INCLUDED

/* type_wrapper.hpp
rRi1bafe1ujNYr/wITuAd/Fu+dN+CHRjBap9eKW4xm2m1OUrwvyNU/g3ZQbLA9pJnT6SWvGraH2Ab/mKNnCOAOF0WcGjrx/wjPwZMgX4iKpEjVlraX+od11FRZsew3EbIRsIkL3J3GODxcfkGIGSa1kiweplzr5Z9J8iQLJQlcPnmOnhSojyiJZ/NDWvbdenxXYuBMDzf99qsQS5EqeuPwoCryNv07aZ0mWMlgO+w2J3pcBgs0K/SBevaSPq55wfmDksmG8MkCscaNke6UkqKxJ00WUeXupDEM9WdpxvlvayoaPYHZJD3zAI9pVfNdVFEAqI2Ji1zzdemhctFN8Gz9ctbovcPvjGbOKcPjhOijBOjcgeSS4B9akVAzkbs+cSyGq8aJeffApSdDZj2ST3ibTN2unQzZxSrAjo/wdn3agrncmA1jXfxhjcRVg2B6fsjAmDymCfeBOzJzpT3Wd+nfLuhgyqufRgoPlAJe9CaMVjlpJTXpoydd6Ui+mjvS7yUA5b29YiHpgXha+MVf1CGMLgOEtBXSjEv/KUUL5Tg7GRj76KX6oly767lw==
*/