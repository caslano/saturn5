
#ifndef BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED
#define BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

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

#include <boost/mpl/push_back_fwd.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/list/aux_/tag.hpp>

namespace boost { namespace mpl {

template< typename Tag > struct has_push_back_impl;

template<>
struct has_push_back_impl< aux::list_tag >
{
    template< typename Seq > struct apply
        : false_
    {
    };
};

}}

#endif // BOOST_MPL_LIST_AUX_PUSH_BACK_HPP_INCLUDED

/* push_back.hpp
AoVffH37Fn6EQyOS26PNCEGPgk3MXVTFeqAR+lfPNDy64ktevQhxuxj0paJ9BD45SUU2/3H+apKsXgzmDwoEU3yI+uBgxqkF3N0nozQRtlXqgFbNjICdmOPuv7zDJ8ONnj8bn3yvIPNzJmsWxw3OE6BHqONGxxby/ZoS5zjF0m/U2XYK1xTYQsv/YXFRL+tYBApZHn4g4EPvFFH/ww0R3MKYhVs7FvYg5BTjdnk8OUb0pxP+qbBY/IEwu/8tH6+w20aakSddM/Myv1pwD3EJpMVhhGfOcLwSQR+2dDfbeNatY+yhbuKVwOVMT/QNkTjB7QmpIDXgyij+YdZQsqAJYNUvog+mIKbjr9QnHpcoCBswA9WPej5zNYFxzXi+vMF8Y8ft00DSajodKbyCs405/Hikp12YTr/vsP8PhhiyKF+F3njGFBJiOtRhbYVoLrt9LmukI2lAEnG4j/4X+dPBUPcIKET4P6UW0zr++mqTBB+KgKfkisuCaxRmtuKXcusqiQu6HyfZMqBw+vr3l+Hyfx4yNViZN2cKMf9xOhTqvRzycYKKQAi7wgohTA==
*/