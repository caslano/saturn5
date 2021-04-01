/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_END_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct end_impl;

    template <>
    struct end_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
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
olK5Qg9+0cy+1wiTyBXJfkQmjgSb+I+0R1vIX6FCfef2aIv2OxlJ3d5YPc3dAKODdUEeueMWL/wDQPlE4wEtHnlNOf3iEYEZcp6i3BPL+kecGpjtg5WwXdSOZRQ7s27bp60WxF7V17gMkRgcxhAtFPfEzbhvFMrD1MTFjrqO8vGamLtw9UnBkPzAeyUn+MNA22hDlvD6mBO3sJOUUmJEUQvHeGscx+TtxciHatdRruSoDmz9lxAVrQN97qFCO2Mxu/Z2w/NRk8/RzN7dOS5qwvV0J7TlFImaon4+hu5eXws80pKhL3G/kc0Z1Nd1CHWIy1YYztzVDTp73GDxEAj0uyzZhN3kjnQZDTbdo3qjx94EPgSg1bcgkCrL5dFsgROaiQTHMCjrUOF3qCe0Jmf48RVaMn0YAj0Uvz/v9lkduNMHPBz+K+sMWjuQm5sFp1XuDOH6J/iV6QFcaPBegmda/g262UfSw9BpzWOsRulVGKT7+WydMy/2QduqkuEWwJPBSOW0j3A1WX/BQSa/4RLbghHCxqdjuMHaLqltVcF0aXptBeQ81+QOEUWF1Q==
*/