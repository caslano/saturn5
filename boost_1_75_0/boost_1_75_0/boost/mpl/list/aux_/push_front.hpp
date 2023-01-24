
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
m8aw1RboC4jO88jo1WEq0euZZspLW2JJW2I8qNpXO/AhiGfRHJfaeaDXcxl/6Nj3WbnvYgran0HiHn7XxRQ14uYJlM05gfveLh/Qp0BTnTxfEbCppDdboeWmu5+7UVOF4xoZm9Xl2F9JePSrnLc0wIBWyYGBWzkgaJbVCjXqKcjigGUBm3noXH2ip/DHXgbkh/PVsPpSiTZbEoC37W9tt1ExFulqx925L95RnO7eaX5G3f32Ug2P0FM1Bt1j2wJhXLFpghnDPdUUO7s/T2o94bNXfrusNwXYxAVSyTs1flR9YOBMSrRZqjZpAehY+IRJGFM238r5WKhH4ptobZddfyWT8I4u7HIpo98trTIn8rYEif/eILKM1WyoJmqI0m1MenjiOsTfWrI/aN+c0Y5wKHZ7ilo1WI+k8e77BlM5w5OhVsxDgVzXh4+bfpVXzBrwCyO+eCrB3EV5gBufJFSvuP2KZAe1V0zN1zLXzXo1kNZ4GzOe9ax/6FWyLTd3dbyDKXsQx7VnZRBfV4PmWBvnIW2EmmnV3J6HmMH7TbyOWrlhRoOulny+CmpNQDB3NzHEIM6Xdib/SDdOrcxPcGiMWKs87eKsuVYL3iZwMerYrf3bRbYXSMYgpQ2/0mARNuJ52qzIKaJ3EG3K5AkOvV/6eX7axlmtH/Ymj7zZydgMbVBcTK0vqckM77c4dhEEmJHtonUHAOTyREzyWq+9
*/