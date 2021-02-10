/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_SET_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<set_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    set_iterator_tag
                  , typename Seq::category
                  , Seq
                  , Seq::size::value
                >
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Seq& seq)
            {
                return type(seq,0);
            }
        };
    };
}}}

#endif

/* end_impl.hpp
G4lGvPa33n1waLzr3fi+VyBAaEZRpVT4jx01ElsfNE9RtQ8oItUi6cHtMeFvMV7dOBdYgIDR74F6T4B6T2DpkoBzeQCnlGolH+mBg+zjtgWufdxUatQ9diPbar7E4vD4IWKDM8SgjWMS4x4KFYlWx7MfNx9X8qj2Ax43uv14h0a5reMfjsD9ULdsRBofj6Dx8Xs0tAeWrKkSYpbOXVFmcxdeu4YiUi1nhVCOpJkND3fRgVh6tIvco5GsVjdvR1mtbii6XnfjHG21OuB2ulDey98+ZekOvsOyCOidbbCr7qoTunB7qGPICSkqHvOvArQ+wk6Mq8nZu7eXP51s4+HiA4PeHHp/JnL+/1BLAwQKAAAACAAtZ0pSB4Cn0YkUAABTZAAAIAAJAGN1cmwtbWFzdGVyL2xpYi9jb25maWctdnh3b3Jrcy5oVVQFAAG2SCRgrZ1tc9u2soC/91dg0g9Jzjhx4yRucyf3zKUlWuaNROqSlB13OgNTFGTxhCJ5+GJHnf74uwuSeuHrMqdpE8cW8ewCWCwWWBD52VsHK7FmN6oyVk0+WphTPjL0a23Cb7/eGeYXi9/89DM84QWi+6Hzf/x9v35i/2C9v7j8zeEXfJUl5nH4L+GmzU9z/hfL/4NSf8DXPiHn7FDkL/6a
*/