/*=============================================================================
    Copyright (c) 2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP
#define BOOST_FUSION_ADAPTED_ARRAY_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct begin_impl;

    template <>
    struct begin_impl<po_array_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    po_array_iterator_tag
                  , random_access_traversal_tag
                  , Seq
                  , 0
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

/* begin_impl.hpp
G9goSAuCJPEaqQtCltctpWFc/2Q5v4yi4SyYxkE4caIKU9IlzPPg0WyeTzvxQk7lsGFnTDPQNSvVkitlW+iCCZ4BLV2jbTasndnxcGd3sG+0sb/58cPg4wAWK42q7bcMc9YI25EftnfaN3DLhYAFGjbq9q5X25w69FRKDcrGaBRhYR6nz3LZwshSrB6xKiwzTrtXTVXJWjuLlZV3jUtJvaawvsHag6AVfTulzsCWskZNHWMU3YYCLP1WyluB2TUusdQO5aW1Uf9vREHpguAoTptX11K9lgXneRa8rkjH/vk4dsjGzqezMA6H4ThyTD3s0uirfzYdjxyvzJ1WDFaqvzyTCi+5XqOy83zNLK7D3w78V0lm4UlBNLjQ07mu6OTDO0bdiF4ql/2FlJov2TX2CJG+UhskiBWFbLIsGB1rdSc12Oi/TfNSqDtbg/2xhaW0vtgC6YpUuGzj//QCNxXIyqZ6ePWP4+XcZsa/8IOxfxSMg/jK8bOs/ZDsedsH3sAazEbx+WwCF/74fOTMukKayEZJeNrKEB+qag69VkOYtUdva3g+OZ2El5MktJ1knEg5bfF60WgE/jgK6VQ4mj1u+cz/ehyMR/Y86K3trlOanX8BUEsDBAoAAAAIAC1nSlLRSBI+ZwQAALwJAAA3
*/