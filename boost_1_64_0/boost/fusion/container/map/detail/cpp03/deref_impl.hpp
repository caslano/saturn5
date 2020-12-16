/*=============================================================================
    Copyright (c) 2009 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_IMPL_HPP
#define BOOST_FUSION_CONTAINER_MAP_DETAIL_DEREF_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace fusion { namespace extension
{
    template <typename>
    struct deref_impl;

    template <>
    struct deref_impl<map_iterator_tag>
    {
        template <typename It>
        struct apply
        {
            typedef typename
                result_of::at<
                    typename mpl::if_<
                        is_const<typename It::seq_type>
                      , typename It::seq_type::storage_type const
                      , typename It::seq_type::storage_type
                    >::type
                  , typename It::index
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(It const& it)
            {
                return fusion::at<typename It::index>(it.seq->get_data());
            }
        };
    };
}}}

#endif

/* deref_impl.hpp
wpL2/Er6UvwJ8EzRtwEcI/oukH69EO4C58OD4EVSfx0cCy+GXngJPBHWwxlwQTjPSnwEcFukrynP6mbDcfly3C5ij/G4Sw3HNXdwHPcSOU7mryAzit6c82Kzzx/jcc0xHtcmxw2xOG5/o32zpb4ox/ljPK5ZjsuMclyrHLdZlONcc2LT657TcXuzutAneVq+nbMeQGfl13WUW9czv3uH+XVZ+d2TzrFLNr9u9OHrr5EcuzWVX/dfyq2LNa9uOONkDDIdWYqsRD5AuhfQJiQXCSCNSAvyGvIT0ncyfYQUI03ISmQ10rOwu2sYMgapRhqQFchbyG+Fa3ce3t8V/6/wVBT4PFoCQHLxfy3Gn2qI8feVv1dBcJP38JqUOHhpeYFHTMgjHBFD/D3k/3hsHbv5rt38Pv75t7Ufwm7+ajc/jt+/Yj2ftvPf2M3v7fwudv4SO/+HnZ/Dzr9i7y+ZWaTtz9y5buXsxbu1fjW3971bH/b5ecF5fzYiY0OXZv63LkyXk18q8/4yyPcVoj6z7Z/X6rOa57Q8o5VnszyHLZ/Bls/dMYbnrcuNDcgo5KftI9fZWYkYn6OvybNzOCLPTJ6V0Z+PkxCrZ2I24pFnH8885RknzzblmTZeeY5ZPcOU55Y8s5TnlfqMUp9N8iyyf/aMhukw8nnT8bMmBzE8U8LPk3TP2n1vdzZnczZnczZnczZnczZn+6fm/9rSN/rsP8n8f23+33WgK7yGV47FN/3KtfyfauZ4xhz/oA/AX1EyDUvyiqp8hYGScl9UP4DVumsHmnL/e4vuXqI79WRr3VWTjaqj+yCsdB8iuoeuG6nbj+6cCN2cJ1JiS7xaZixJaUnqD/ldUiVH3o2yTLgnXMJxuYr+cJ8XkPpE46OvSxSxtpiyDqDWf6RBSx5zPrxct62qRF9Rqdzj6qesTVRIquLkgsKp5OgGCsK5L80oIteGyoL5toefEvQHLDV9g+E7aeOB0sZ9pY2tpyhtlHNbWlKoN3HtbOO7p0obTeuq9ZF3B/aQNu4Cb+CYmunmNpoHUvztTJF2LgvmP4XXlrp2ULAdeR5feG2pxwfq9muKwrnxEzfT9+mNSpPc+Osoy77ygHy/Q9tfY9Nns2z6TOufm04L9s+NlFOu8a6R685VaNe4+n5P0vcX6SPdztTgeeJnrU6tyrwil3k9zm4SnxW7MsQut2pX0vce4xhV7aJKzNLziMWmtyxsCmCT32yT5XhKvM9Ctt0Ytk2rusj53oGzNtYaz3nrrNy2u3Sf9ePdRp8yu+33P/r/4c/aduNTR0XPYWurtstFg5IbtjVMgYNgsJz8jQJ7W5QbIuW2gb3gtuFySAfldpByOVJuRynXjORKObfkGm2i3UsMOWyZcA84BO4JD4N7wTFwH5gP3dAH94WnwP3gIrg/vBIeAG+GB8J74UHwXXgw/BAeCruhfzRMgYfBneARcFd4JNwTHtVutzzrqdPC7nFi97Fi9wSxe5LYfbzYnSd254vdBWL3ZLHbI3Z7YQssgh/AKXA1LIE90X8C7AOnwuGwDI6A5XBf6Be7a13y/IZ7iN3a+DhL7J4mdleL3SeL3aeK3aeJ3TPE7tPF7hqxe6bYfZbYfbbYfY7YPUvsng13Qf9cw5pWqTPsvx+RKjmQvWBf2BsOgJsYyrulfKZF+TQpvxnsD/vCDLi5oby/g/IDpfwWUj5DymfCleu5nDyPJPI8Ys3xWJPrJyWb2+HkdazdeR11HnIykO+QbC95HEg1shR5CelS5MTrnM3ZnM3ZnM3ZnM3ZnM3ZnM3ZnO3/uf1d8X8poaUAJBX/H8j6f1qctG0svmdJ7w9VroVNt5Tf/2T1e19Bmb4GFsccS1w=
*/