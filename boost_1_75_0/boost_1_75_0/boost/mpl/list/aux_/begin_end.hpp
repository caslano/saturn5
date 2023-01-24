
#ifndef BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

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

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/list/aux_/iterator.hpp>
#include <boost/mpl/list/aux_/tag.hpp>
#include <boost/mpl/list/aux_/item.hpp>

namespace boost { namespace mpl {

template<>
struct begin_impl< aux::list_tag >
{
    template< typename List > struct apply
    {
        typedef l_iter<typename List::type> type;
    };
};

template<>
struct end_impl< aux::list_tag >
{
    template< typename > struct apply
    {
        typedef l_iter<l_end> type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
ABo2BhIufw1UzurH9XY/2rZB17XcEM3+8l5GwDscXnTO9K7rwlE02iqk8I75u/0OBt9h3r2/wbA0Z2hKsfn3KxfCefO9cNRK4uF+6XRGYiIK851y40+rfyVbBXEaUAzpzQdDFblFGjaS2Cx3jl8N95MOFZBffGX6LrxVsnGxRK2BdKZfQm1lFj643JD19z8Pti1h/158LjDMIap1qy7vTbJ34PT9M0RkW4fBjMEMaa6IrvutaNMa8vEp0WcOlkN1t3p000l+8c7pl/KufW6YQPn9gy/Wz2AISYx31rgAY/8qzteswUdsMnP4c3y0YnmJqYRGJJcjtCDZLpX+zY2hy06OIyrjITVH0NX2uXcdSxPyK4Sx2ZHh3KeiO3lOH/490Qyc9SdKNLUyrkhNK871DJC3LbIZn1piPkn7aJodfg+I5SiaKTTa/i3DqaRgL5pGLLoRijgMdVca3ojgs72uNLArTmI56qb+pGKhrOUJjr6T8RYVS2I89Y5BVnME5zSqKIwpM5fviO3WsQnGjF7v3+li5Il82dJSialgXrZ9fmEUS4LVhHRkgNwFSI4OXLitkiWvZ46tpI7ldyI7c3a1bnRviNuS0r+IDHUyumfmFeTtNbr/HjcNU2mixUrI2vumihP4tYr1q/9X8/kwt5AqnD/+sAR/XnARld0VnRdyWyA6Za7uylJmOFbMKGbqghcbY41jJZvLq+K2Xdjl
*/