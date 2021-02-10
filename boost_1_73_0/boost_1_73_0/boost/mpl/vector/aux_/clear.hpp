
#ifndef BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED
#define BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

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
#include <boost/mpl/vector/aux_/vector0.hpp>
#include <boost/mpl/vector/aux_/tag.hpp>
#include <boost/mpl/aux_/config/typeof.hpp>
#include <boost/mpl/aux_/config/ctps.hpp>

namespace boost { namespace mpl {

#if defined(BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES)

template<>
struct clear_impl< aux::vector_tag >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#else

#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

template< long N >
struct clear_impl< aux::vector_tag<N> >
{
    template< typename Vector > struct apply
    {
        typedef vector0<> type;
    };
};

#endif // BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#endif // BOOST_MPL_CFG_TYPEOF_BASED_SEQUENCES

}}

#endif // BOOST_MPL_VECTOR_AUX_CLEAR_HPP_INCLUDED

/* clear.hpp
ODlVVAUAAbZIJGDtWFtv4jgUfo/Ef3Bn1JfZSUOAajtsiuRACqmAcglU7MvIGOcCIWYSp5n0189xwqW729Xs7FZqVxoLJXZyfM53rj7BECwRlCSspRhB5HK4bVie8XiVtJSe44yKC+paTjkZOv0BIqnwFZeHIc9CTokIeKQY2mmfoZWs3qMpix9YrCbBiilGzHZh3lIU40xVUcSRsSKCtFAQIeEHCZJIUBJElKGMIZ88sFKaG/MtUDCUCBILRXEkMfySdLfjCVshwdGSoZiJNI5gmfksKukL4chjIkEEuUGcCAUDdB4HjwXoZikgDCKGdiQBXiqAOcqjYcAigVRVYpZY9WpVL62i6Rc6alR1NOQZ8oLtlsEOAvAZ5dEKsHxJpTbcRTQmu4pS2qGJBgGNecJdodr2VLu8qFaUNo8EiFGdfMeaYISvQvPFNvwNUZ/ECRPXQcLVq6vLT6p+Iu6zyBN+E9UbFeX+/l6VasHzAJzB9lo54WTgzIfODOM2lsODe0dO2l3PszC91PFi3vHyIcXH0W3gpYdzOR1XB7BvjMeZCbssbHnmDbYyPB2bDrYsPJbrmzGeypemhxeZucbtBiZjuHdn+Hdshri3wH3PTHEPUGQ4kc+X2Nzh3gAvxmYg1ytscrnvu/uLcX1d
*/