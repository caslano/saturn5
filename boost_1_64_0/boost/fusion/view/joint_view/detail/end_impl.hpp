/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_0128)
#define FUSION_END_IMPL_07162005_0128

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    struct joint_view_tag;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        template <>
        struct end_impl<joint_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::concat_last_type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return s.concat_last();
                }
            };
        };
    }
}}

#endif

/* end_impl.hpp
D+zZ6fWZK8qp4ravENPa30fkB3tnJELtL5Bp8VBoIqWdKNO4ok5p3VRaWSWl/S7pgEYYp7RbZT4eQYnSdpNpPPAC8bi9TKuKwCUNet1byXTivSojF9OjVcl9snSZJoIl6HnPEulwxXuYhVTeOSKtdLKomUZvelSmyzhIyfRHRbq4z6VPLy3/UzKdd6QwF2CK5xBT6SKZ0ksoXYR+ozlotUovg4Cb4Z499L51OGKhhFi89uisxkptDEndLaYY0Vqe5ndhoR4qf7qWPwI7ArVJn52ZqVgEdBM1Fmt0dK85hS9tCtfmyZkG3rRNWI91Pt3Iv9Vd64Di432Sj+Or5Vsk3r8h06s05kfUM3siFoaREOwUPZVMVcl0XrlkzBatTk3vZCdl9VD5PMg1LzbJxwVaGdpON9nLFhp4o93uiKpLg5Gvyd1/qssKWZeKCSBeXB2n8dkoQ5Rfp/TqiHwGPXErxJm40knxydJNmNWqfF83nU94AQNM+WqbzieL0/Jd3GS+Ksqn9N3NvF/SXn+0XMg6jOSKP6tF286mCb4JvaGW/f/z/8//P////P/z/89//DOM28Dyi8ftwCaxZQ8/v7fcKunOZk712PteEhs159WpCtt0NqxItec6Hr3mBXoOLnJapmGZx7z6lcBAI5t5DuwOINYCNK6DH/SfVhg712Nr0pNY6W/vj6bnLgbLsfYcm/d5D3ruErA4a9gPU7+bprAYYJM07P7JZ/VSWP4Mjy3UsFYjWnygsE2AnahhHQfduVRh4y712EEa1uPQ00cobCFgR+h1ubzzzkTvMo9dpmElLX48TmGrADtSw+obftqgsILLPfaml8RmD9rxKIU1XOGxr7Xn5n068kCJResWXgnR7BCD+0Ui6866u15hRVeJ5wg7pOchyxQWuxp+a9jPXffJUBi7RrwHwvh7oOcAW5aWxI4/7ZACqsscj8cCJmzCWeFNCht3i8c+0cpcvPb5VxTWcCvwzEtiqz+9LEIYBFD8SHvuji/P+kRhc2/3WB8NG7h60BiJBdgmwPZFrCWkhCetOERhBfM9truGnfJFx+UKGwdYbw076fuzhipsIWD9sZ6tIOXvmRvHK6wIHLMmalhude+lCsu/y2NTNOyrIbNaUD3v9tgbSK81eDc/VFgwR2HsXo8NDSaxJfOXdaR6Pgj3yGpYzwvOR1kCS8MjHjsUy2wDnxfePvANhS3dCpb/qMc2atjo9MPTFVb0GKyMNazXuuXDqUzAZmtYu/Of+0JhDY8LWSKMy5LCNgGW4SexH7565Ad67kno74Ekttus89spbOEzHjvKS2KVY2t3VljxMo9drpWZ1vqxvxQ283khS4R9vXJ+NyrzBY9V6m04uo7aUPAiyGdaEnvkhqVphL3msV80em2W9fiG2vcG7ORpZZ4y/KpyhY2Dzl6qYTtFp65R2FrAFiPWFr7v3bdbrcJWvQUWbw07t/Ldm6kub3vsIg1rNe/bRVQmYBka9sCSB1ZTPQFr6SWx4IxdbiB+vuuxFtpz7eb3nk9yBlgb7bnzD17+OtVztRwjCfttR3quYA30TcJk36QyAdudMOqbApu7lefWbgXr9J7H9tGwzk9+1oXew3smvRt2fTOT5AWwwzTssy+Kbid6gB1HbYcyntj1LnruA4/toj03q6pjLfUVwPpr2C8ZvQfROPGhx7pgme3g+5IlLa5QWMNHYu4g7OqK9AyFrQVstoa1uq/NGoXN/Vi0nbArM1dMoOcAy9SwN4t3GkDjEmAdNWzj04e+pbBOa8FqqWHvrvzrNBojATtQwyr6vLsblQnYTA27c/yG1fTcJx67Tmv74nemvkLYZ3wMIUyMIVSXz4XME/b3eYmeCls=
*/