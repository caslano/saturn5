/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_VALUE_AT_IMPL_HPP

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct value_at_impl;

    template <>
    struct value_at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<typename remove_const<Seq>::type, N::value>
        {};
    };

    template <>
    struct value_at_impl<assoc_struct_tag>
      : value_at_impl<struct_tag>
    {};
}}}

#endif

/* value_at_impl.hpp
8Gf8hKeBJvrYXq+wTU/+ZvhDBcvbE6KeMMfrum6CeWy74tQMbhqUw9afEed6FDIy5pIsIFcG8NTQq9LbR+tZBhWfXvz1hhJRvIEY2/ay+AeNsn3wp+ZSLiezWp+e6GiKuqvmZmVJ87hCPni/JFTxiIMuo/rwdXFR+UP4Cx+/7T9Nh+xpnZKsyVKCr3FOdh/E2yNk3s6IpZusqi9j89pQwMLHxRZjldc5JsYtiHkr2ZVMjoaIAwmZJ+2wFhjjwoH5DtIn64PNE2svVcFgEvn+afQk/sVdMOX1lb6Z0NhcdImWrd36KIAGYDUTV7iwNauvnfkQufoqgwTs7MqxkAJWspDja2pziZxpGNTgeyPzXzP1JiJp8No+yAi/Quw8QdArycuofH93jeeUr84GGSvsMeZNudrYyD/tQryQmxGJXp9J6h7rPiQLzxQv17vcjzJrV8rV935uvSMX86ChT8PWfdtdUlWl3VHy6H14OQOGyhLO4J96EAaTXZaAkmGQYiwLSw/JaDj9ukzQiTo5oQHsC8VkJUHRQ0txP3sfRZpNSPTESW/w3cAP59Ak+g==
*/