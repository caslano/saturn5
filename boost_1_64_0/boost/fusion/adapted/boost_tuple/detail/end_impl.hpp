/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_END_IMPL_09272006_0721)
#define BOOST_FUSION_END_IMPL_09272006_0721

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_const.hpp>

namespace boost { namespace tuples
{
    struct null_type;
}}
    
namespace boost { namespace fusion
{
    struct boost_tuple_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef 
                    boost_tuple_iterator<
                        typename mpl::if_<
                            is_const<Sequence>
                          , tuples::null_type const
                          , tuples::null_type
                        >::type
                    > 
                type;

                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
SD8SwgPwcdIFj8KviE9rgPKNR8bpfNiPhHU+/IAYOgfO+x9/v2oN8LZdfFd4GJ79LX3EE7D7Xo8M0WfhRNJH3xcuISYeh3tJttYPu7XwTeF+OJrk4GHY+B3fG+v49rEPqcFDsPx7ovXAfinugO4F55KIvjs8SGpx2c/faz9y5/Hoz/wuHeNu48E/WIM04TH45V/cYV3zb/7OPcVd1XeBgX+4z7ov3Era9d3h1af5XnQcdu1gyik8CS/ubErGAfbKNMXrMMWOB7IYd5pi4mF4nGTjPsOUF0gfPA7Xu0w5pjW7TWknOYz7PaZ0Mk3J1XXgMpKHJ2H72abk44kuphhdTSnQ+XAGKcRj8MxzTBmj43B/tinFWlt3U273mVKCG71MSfcxpRRPn2dK9fmmlOn68MYLTKnQmuH/SCUufU0ZQYp0HEYvMiWh73KxKZNzeAd9Fn7Tz5RmHe9vynK/KTV4cIApRy9lDzw00JR9eaa06HsNM2VKwJRWfRfY7Wr6oOPwEXJK/RpTVpJ2PJJvyhXX8e6t1ADXkTF4EtZeT3/wNOx7A33AAzB4E/3EfTebMpLk6rPwbVKAJ6DrVs4Cj8PzbuMc8SAsJ9l4DG4jdjwFdwc5U11zhClfkzJcbjdlDanQOdB+J33TZ+GOu3h3nX83+5IarRm23mdKndY81pTXHzClHjeKTHGPM6VJ5483ZcAE+olH4KXF9E3XhJ9O4nmd/wh8jP7o/BJT7nucHuq7QPNp7sdB7sAzvHsp74jH4Zjn6AluRDjPGfQEl+dNuWcmPcTTcGYFfdZnX+YsSAEegRLlGdYPwWlzuVd4Eq57lXul7wIr5nGvtJ4FpnR+jXPEZbEp975pSgMeiZlykNTigSWmLCCFWhtsXEp9Wttbpjxbw154Cm5/m710/L8m/3k0e+k4zF3OXngUrlrBWeCy0pTDpAL31dJXUqnvBZeu4izwJJzxLmeh+8KWOPXg4dWmLFnDueCBOmoj9ToHNn5A/VrDWmpbxxlpDXD7es5IxzdQ20bW0nG4pp6zwf2bTEkmOCM8sdmUp7dwRloP3PGFKZmHqOdLU3p8xX3DA7DqG84Lj+4y5W8yBPftNuV5EsBj8JU97KfPwsy93HU8BHe0cN64/ztT3ttnSgg3vjdl035TxuHhH0x5/4ApYfVWU64/aEobHoETDpkyFY/DysOmRHR9WNbG94AnYLef+P51PlzbTq148Igpl/xqSkyfhX1+4zdLn4Wjj5usp/9Zgynnn+C3Qp89aYrjFL8hOh8OOk0P8Ris+5ffJp0vXtlDMg5Tfwev9O3oFTsehsvO8IqJS4ZXHunklWzcf6ZXniF98BhcR4rwBNxFivEU/JOU4NLZK2eTHNwHB5MxeADeTXLxEHyS5OERuJDk6/pwHSnQ9eEuUqjrwxGZXinVOmGKVOJi8cpIq1eq8Tj8j80rcTyqtHtlvc5xeOWxLK8k8CTc4vRKo44bXgm4vJLE0/A+t1cqtB54gJTpHI9X7iK7dV9YT1I6H64wvdKmtcE9Z3vlhNbfxSuxbl4x2pif7ZU1pC+ehD9394ofD/TwyuqeXhmCGz6v/EsCOt6LPvf2ynAdP9craRLE/X1Y73zeE4/B433ZA49e6JVzLvJKlTrc3c8rUTze3yuHSBiXS7zSn4zT9eF4EtL58NAAr5TjkUu94hzolYg6HD7IK1N138HsSdbjYdhxKD1Uh3PJMq0HbiNxPAU/vYLe6l55XrngSvb9kbOGVWQkHod7yHA8rWNXUScegbcP433xKBwWoE48AbtcTa9wPywnATwGTxIfblxDP26gz+o3emUW8ete8AgxcLmJOQWshQdv4b6RE9or2OFWrwg=
*/