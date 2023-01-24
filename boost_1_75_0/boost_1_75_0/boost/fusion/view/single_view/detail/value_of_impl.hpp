/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SINGLE_VIEW_VALUE_OF_IMPL_05052005_0324)
#define BOOST_FUSION_SINGLE_VIEW_VALUE_OF_IMPL_05052005_0324

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/equal_to.hpp>

namespace boost { namespace fusion
{
    struct single_view_iterator_tag;

    namespace extension
    {
        template <typename Tag>
        struct value_of_impl;

        template <>
        struct value_of_impl<single_view_iterator_tag>
        {
            template <typename Iterator>
            struct apply
            {
                BOOST_MPL_ASSERT((mpl::equal_to<typename Iterator::position, mpl::int_<0> >));
                typedef typename Iterator::value_type type;
            };
        };
    }
}}

#endif



/* value_of_impl.hpp
i/7L5Rs/g/0F50VHB+9qC+OR3LmGtsdfAwsIdnGV1qoz+YhAB/2cGZ/mePV+tG9wPxb5q420NAiDOYyPncL1Vc9YchYAFso9yPzn8nUB44KnUHUxv/L+3nz+1hhg0BpF5TBWO1fVhnsAiY5HVUJaZQqGFGHm52+Ujcd3JSJ4On//JvE5XatU0B1hNOH+80bxJSw5/OsalfIKYCZAUObxPhFdp/vWyRbyJt1vYDQf6KNKsSDx+XJ5Xs4qHUZmOBjlX4HZsv/iyU+w5+HHMglpvMjnWQk+YUb5fJr+c1gVQe2ZX76VV09/LfFlHWdPZqUnXXTa5tfK1z1bPnDHvXI9/MbJL++3NqT9GmTpxqBKPcsHvZ6/LWBscAWwDPf/3vd/vMl8P1iTyOYsYe4O9y+M0YZRoqB36vTOKj0tOPccf3qVb3u2fI1sFRzz4K+2MB+Ao14yKNR/6fwdFYWQQ5ou8sFY0hwWsQj3s5fygsgnjuHubyOwsfxT5k/2ii+xIVQAd2Wt4OOutb/Gs5JXBoPHDuf8YXvA6X7OV6M6YH2w6b4VQQ8ljNC99DCZ15yPltomXY51eD6i+8uMKZqO7BE4WfgAyqTtmC6Ry0fuqJM/Pinb4Xp3rf0gM9ulcwJvJpH1Fjm/FNliOphaxYOTohjmH02Rz6+ALwbcxiQ9m+PX8DXoWgYhtAY99OQTyclwal192AMG0SW9GW7w6T/D
*/