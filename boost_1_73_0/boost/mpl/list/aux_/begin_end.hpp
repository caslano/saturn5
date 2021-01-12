
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
qmXjqw8sSeO5XuTw2soSwy96HZxgy6z5dZ+aR6Z6/9GKkaEhrTF7e9/YJy6i16PXGMLwtwkhLR1Pr0iuN9xEb39tDMlcYjYONhhbzAMNUb0KYsz74l6Ic5jHOapNve6utZ8Mf+gJa/+siJ8YehnbDdGD00c6IqqXD3AazA0DllHMeaB5vKHN0LJpkKE6Mj0ioyWz44letmjXiEfSHhqUtt1QHV9tiLAansjLMfOIcHD1OMsT
*/