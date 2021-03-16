
#ifndef BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

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

#include <boost/mpl/push_front_fwd.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/list/aux_/item.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct push_front_impl< aux::list_tag >
{
    template< typename List, typename T > struct apply
    {
        typedef l_item<
              typename next<typename List::size>::type
            , T
            , typename List::type
            > type;
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_FRONT_HPP_INCLUDED

/* push_front.hpp
u4o5hsJiVrnLK6sZkXdIypRQKnc6VC2SRlCbJEwtuMxmIt/kGT6pHe6UpWN6aEeuoj1rx2fptcPyO+8hpqms4JgGkjC2B0mw8owPhoKRM2QghT45afsYnYXV2uzMPB1B6Kk9WBeFJax7GXX3NTQF/A1IIpGzTzxCzm6lGGeRTFVwiO4jMa2mQG5MSmdHtGpFOGNh0MrmeCjJhK14U0Up2oSo8xziTMSXabzCebNJ0UtZ/hEOyeSIbHlpgUwPxvQ=
*/