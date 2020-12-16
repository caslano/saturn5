/*=============================================================================
    Copyright (c) 2005-2013 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_MAP_END_IMPL_02042013_0857)
#define BOOST_FUSION_MAP_END_IMPL_02042013_0857

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map_iterator.hpp>

namespace boost { namespace fusion
{
    struct map_tag;

    namespace extension
    {
        template<typename T>
        struct end_impl;

        template<>
        struct end_impl<map_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef map_iterator<Sequence, Sequence::size::value> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    return type(seq);
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
DxyAPSX+DJ18f+JBib8azpb4B0q8gyTeIeiHQ7E9PoT34TB8EEMxEkdgND6MT2IYzsRR+CqG40qMwA8wCj9GA+7FaMxFGWed406+HyFf8lkdF0g+YyWfj0k+4yV/47ErTsD7MQFDMRFjMAlTcRK+hJNxDibjKnwCN+MUyd/TuBtT5T7LqXgan8VzOA2pozbVQ3q1cC+TukjGUS+z+kjGWv+/qJNkXPf/WL3kzTyH+2brJh2pl/TnOAwmGAlphAzCekIu4XwLZx2kc3JOzsk5OSfn5Jyck3NyTs7JOTkn51Sa6bY//5+WT+4vNg8AqLu15/9b+gB4aPoAELn0AfiaStB2JYwBkKEr7AMgowI62A9A+ha4SrxE0hjL4Wu+1BkXxstDZi0xl75dT3kdWvicc+t9ZW6m98eaXsfIa8u92EZru1i09f77/XVN60ufhMI26jmaew+7VGvpQr5leeV1pvW1PFtd2v+Ou9ru/+Bt3m52QpEOEA60p/6VfSDOSNv1c+gt7iDO9IIakv/CfhvJN8qz9HmYfY31VK/jeG3pA7Hv9xqW+7jb62TevMJ51r4NDxbOa2uZFyDz1PeAT/6tRrH+E20L53WwzLtw1TqvnaWvxErrvC6m162trztr4o58NDI2XvZJapF9kmZjn6Tb6D8x10b/iQCcU+we0eL3e/uj+p7XUDt9J4r2kwiW+KVPhLXt+HVzmuHM1N4DXl6OA8lDqvQFMP5pPQ6UjhKlPHYj5T5eS15Ga+//ljQvSJpnJc2A69Y06YBQ8ufFbv8DbRlr0navKM9EJQ9eOAy3kHbuT9a0lQ4IDhz3to6L4v0P0m30PwjQtNvbOxdxXKiOgdqac4FpqA+lA4jsX+1xoIxbcZjtcmNbr/Pe4stsm8TZxxrHY6Y4g6yv6WMSbh1fRTPuyGUpsw1y7/gauXc84gdLmUlnB50jfaZs9Ucq3t8h1UZ/B38b5RZ4o3KT+8c7FPksBdvpDxF6E/0hnP0elH4Pf//+DadqK/O9Os56t8qAbx/a5nZ11/ZBTSeUff+GDF1h/4YCF23/hnulf0MPrIg9VfeyZVnWc1HW097Ltlzu/XgP9bgK/TELe+JqHIRr8Flch8/jBnwdN+JOzMY9uBm/xC14HXNQ+V23VXVvqLfkZ4xsh7q/xXS5N/R5bIpp2A5nYFeciT1wFvbDl3AUvoKR+Kqk4+4qv0fk94mSjrLeNVSm5nJvaAv0xTYSvx6DsC2GYDt8GDvgm9gJl2NnXIv+eAG7SrrdsA5pdEcv7IHNsSe2xV44DO/Dh7EPGrEvTsZ+uAD740K8H9fiA7gJB+ApDMJzGIwF+CBWZZuHYC0cig0xBL1xGLbE4dgZQ7E3jsBYDMOJOApT8BGcipE4HaNxBY7BLIzBbIzFrTgWv8Q4LMBxWJ4DNB4roxHr4AT0xQTsionYEydiEE7Ch3EyxmIyTsTH8XF8AmfjFJyPKbgcn8SV+DR+gc/gQXxW9ksywfinHA9y3FXBODnuQqUfxcNYD8OwIT6CrTAcO2IEdsHR2B+jMAoNOB6jcQo+iqkYg6RPPx75jYIXJP27cFqRfih9sTX2w07YH+/F+3EAPoDDcQDGYxAm4CB8CgfjDAzGbfgg7scheBJD8Cw+JPma6yq/X+R3DfliXT5froXP7/fCOPRBI7bBCZK/BAzEJByJE/ExnIQT8HF8Gp/A2TgFF2IKrsQn8RA+hd/g0/gbpko/panog89gR3wWA3AaBmEaPoIvYDTOwHH4Ck7BV3E6voYzcQ6+ha/jYfwH/oJz8Rq+If2N5mEtnI+t8U3sghkYhAsxFBfhU7gYZ+ASfB2X4lxchhswEzfjctyGK/AAvo8=
*/