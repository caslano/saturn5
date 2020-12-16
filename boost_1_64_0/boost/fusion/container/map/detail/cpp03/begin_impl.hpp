/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_BEGIN_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/basic_iterator.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct begin_impl;

    template <>
    struct begin_impl<map_tag>
    {
        template <typename Seq>
        struct apply
        {
            typedef
                basic_iterator<
                    map_iterator_tag
                  , typename Seq::category
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
DkC3xG4dAGk6di3VVdLwsVMHoF9iuw6ABG7punSunTqAjCX26gAcT9NeHYCXjTqAE0o5LtVcf5d6nxWtA9hl2ofKcWWqBNBsd3o5O+WszUORfXlrdQBuduoAMpbaqwMgSQeuxW9UBxBnpw4gb6n9OgBH03XWATjrAP4udQB3RCvz9xorxzRuVFC379xoP7fPnhpTch1A3uKbqwPQLbm5OgD9krKpA8hYcmt1ALqlt1YHoF9aNnUAGUtvrg4gb2np6wBSuI6YO9hZB+CsA3DWAfw31gFk8dnMJRQQvILddX0IBsIswppgZx2Ac3JOboT423/9bxyrXFEpNQBl8BwApQ4g0FQHYBwb/bjpWs1aEaBc709sSBqW6za5Bn9cxkVKIhxm/YsZRa/BrXGVOI6ZjIFtvX6ScXVkHBxqHVRjjuysoRo/XK675pmuMxmGRJ6Z32YheZH56rGDq8i1djNCNblHIrs527TQbt7DzUVe8rWY5EWdZ821Z6pr8XqSI6SdYz/tRF0p2t+lvkQzbug1O3ULeQvt1i1YE3dkLL5/s3cmcFFUYQDfSs3MCM3IFA2KFMuKysrKaisrKysqNVMLkF2EhGWDxajMyC5TSzIKNFJKK7uprOymsvu+76Tbbrrv4z+z3y7zZmfYC8tq5tfXX4Z57/vemzczvO/75o3Jx6D09VPryTiRuXZA5vfuK6x0G/TGsO6debxoa9O50LcCOZL9x2s6DGNmbLqcEypPU89TVVmevj+8hnnFFeGxo/RlUxfr9rReYeevCDcpprX8rNr0HO2Z2yXYpj+SaFPvJaE2qWMyq2ukH+hNbTKyRGlTwmNS2iJrjIWvU2WcNHa19sk0L7HxyYRNib7mmskvo7S9qVvwwHmid7bobVti8MsYlOlLRiVwHq3W9MoJ38e4jcvaik30w3RsKtXqkDlvmvq9Cf9U7bTK/uzwGAjvDp/vLaU8/a3/PGWpeUzLupTrW/ummpfa+6bi6X/HP+X4p/4t/im37p+a6/po7Le/Dt3rvlsHV56aucF6Hfuncl3yd488F5qM72WLXyYNHgy3hofAg+ChcCo8DJbDI2AA5ob9J/I3CRxk9p+In6sX3A9mwv0N5Vout/eXjRF/2ViYAscZ/E2tl9v7qwaLv2YbmAO3hSPgUCj9wHPdoh9s/GYD4O5wIHTDLaQftpJ+yDLU29pBvTtIvTlS705S785S7zCpd7jUu7uhvTVL7P1rE8S/NhH2hZPgAHicoZ+bl8TvFxuPtEm5eVLO+J6wV8oVS3umSntK4TGwDM6APjgL+uFsWGG0a2l8freVHDD+SMfn5vjcHJ/b2uhzq+babEQeQz5H0o+iHUgAaUBWIp8f5fjenM3ZnM3ZnM3ZnM3ZnM3ZnM3ZnM3Z/s7tb4r/ewsJw+jh/yTj/6E1AIYHv2Mvgf/2/P+3UiLz/6dGyf9/mfpaFpnj2gfsH0/sMJ78/9ZFNvn/6Iz1Xepo+f+pi63i1iiIMU4eb/5/zWK7GH3sOuPJ/39V60dFZ2Xc58yc/399lv5zoSwBEFP+f2qTYoNyLmP5XqdVX+8RZQ2AmibrWDMqo44dyxizxFc9Nrn/LU328dVYdDpxVSeu+m+Jq56kx1VLvxsw/5XJB048of+On31dO+r+6Hn/LYsSy/tvXZRY3n/q4s7J+69ZnFzef+vi5PL+U5s6J++/pin++KZ+3priiz+2cED60ay9erQTg3RikE4Mcm2MQY7m2ixG5iLNyGvId0jfMbR/jBN7dDZn+5vf//d05vp/2cG5f8T6f69ZzP0Loqz/9wL11Taa5+Mj41pLLp71/5ob7eb+Iztt/b/WRsu5+MhY1+KLd/2/3Mvs5v4=
*/