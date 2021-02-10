
#ifndef BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

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

#include <boost/mpl/empty_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct empty_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
        : is_same<
              typename Vector::lower_bound_
            , typename Vector::upper_bound_
            >
    {
    };
};

#else

template<>
struct empty_impl< aux::vector_tag<0> >
{
    template< typename Vector > struct apply
        : true_
    {
    };
};

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct empty_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
        : false_
    {
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_EMPTY_HPP_INCLUDED

/* empty.hpp
USrHEIi4KDwVMxKCBz2GWADr+AxC8OQwiMN/FTPlWjoUOPx44BxjpvYkZuoQMwAm8iAkYwZBCRxg615sSCB4kiyhIYD8XtREjJZY9tT9fSo2kZbzVLv6BMpXpbWOtqj9wRYSaZEUqEhMRFwBEEpzroK45H5QQv+Hgc9TuP4M+9cOe/31w15/Gva1avWlwv4/RE1NGvEmiEgY5h/LQ2efB0dLPjFh7VD2qc/o5mfdfwMJ8Kpl9Gf5eyve/99Vk30FgdWhB36P2kW13LfGZemEztllBGozgyZaulOZTvvK2XQ6spUVW6YeMDgRGKW+LcUXYgdvDktkRGTLynqFMjgY9k07WKXs2dVj044MraRFwAy0e5A9OzTfLo+hC+dpjHgWIZ9DSZN0H6WVocWXbQJHW7JhhbpF474FJUs/rNiOwQVOgvZs0v8Mnw69u6kzxAPrmqZxKLmVUkScSz5pUrLpdz6PJlb/Dneg+acbEOYWJx1Bhe5omQbhSjlRXZ+P7jtaGCylfO0CJolcSf4S7EXCpX4HvZBB+XYLRijt1dS0cwnLHjXPpaFGdxMHch2paaEOYIqbciKPOfgCiES4RWofrHzkYuygRSr9Sv3NQSo6qmhoJwLYtncwaD5nceDmSMbFk56rMKJPEjif4Ux+
*/