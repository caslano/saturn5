/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_AT_IMPL_27122005_1241)
#define BOOST_FUSION_AT_IMPL_27122005_1241

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>

#include <boost/mpl/if.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename T>
        struct at_impl;

        template<>
        struct at_impl<boost_array_tag>
        {
            template<typename Sequence, typename N>
            struct apply
            {
                typedef typename mpl::if_<
                    is_const<Sequence>, 
                    typename Sequence::const_reference, 
                    typename Sequence::reference>::type type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& seq)
                {
                    return seq[N::value];
                }
            };
        };
    }
}}

#endif

/* at_impl.hpp
e4R3Ory38VlR/w/Hn3HB6nXQp/J1ekr2f1Nf+b38H4iHD4r/rSP9475v6fV4FcdzBHF9J3n97C2f99pXnAe+bn/zfoKGvd/SePhCpbZy/Z3I6yGTqHBK2Zf6NJjvLyrcohxIvavsSH2rcrm+woFyVuo7lFPCXcoF6a+s7Ag7I6pfr1e4UTnF/JSLUt+iHAi7yplaeX1Wzsr5BWEcMv9O5bKcX1J2pX2Pckn6c0aSk1LfqJyV+ibllPTXLIxD2meV01Lvgfn+UfJVLkt/BWVH2ncqu1JfUvZlPuYkzade9lu5KNyk7Mn5GeVAzs8pu9K+VdkXbq+2Fy4qF4RL1fa1ks+XtD4h+Sh7zEfZ5X5W64Vd5VRC8qm231XyUfalfVE5Kf13Vc8XLisH3M8vk9NSn1TOMD8y3vhIfsoh10u5JOwpl4XbhHFIfx3KDvNTLnC9WnQ85qccSvtG5Uyd5KecFc4op3m/VlnWy1cuSX8F5VDGK1a5TvIT3ulYwZfsbtaPJidOFr6crL8PcQW5gfVzyU3kVeQW8i3kPHkpuZV8DrmdfAE5JE8j6+9PjCH3sP5SsvMV4evI+v8DXE9Osf5r5Ax5Edkle2SfvFjzI19ELpJvIOvfi9xM7mL9uZoveYqu3ynCbWT9/Yp2XU/WX6vns34JWf8+ezU5w/Z5co68geyRryIHZF/nQx5H1t+HOJtcYv2VZP375wu1nnwZucz2azTfUXx/rvMnX6L5k68hu+SVuv/ki8kd5Am63uSArH//e7Xmw/ob9fo+VXgOOUleR06TJ5Kz5HnkPHm+5keepOtDPk/vL/ICsnOa8Cy9v8gLyRnyTWSXPJnsn/bu9wv+G4/kYv4/MkX+PmUoHr4k93dysuxr8VgpLxVZ70p56lV+n3yK8E5Hurbyfjjrsj4j7AnvdIzm+2d9/owhB2w/ltzhvr3rTdsOfY+R+y4p/tpXxfUYtqi/MN9LHhT/q0r5+iNRuX/6DuDrn7DZm5wRdpQD4aRyVrhJ2RVuVvaEW4R3OsbyLWuO9WPI+b0HvK31eNND8qt8vyQ8WPMT7lb2hBONZF84qZwRblIOhDPKBWFXuSjcqpyqq3CgHEp9h3JS6kPlEvNTTku9+TC5LPUNylmpbxLe6RjD7xdlez+vRfJn+7laT55H9shzyAF5HLmDPJ/cRc4J442+8HhyA3kSuYk8WfMhLyHnyGeR9fMzPHKe9VPIPtklF8nTND/ydHIPeSY5eYjwLLJ+/sYCzZf1CzVf8iKyS55NbiXnyXo9Lya3H/IOXd//6qNcV1+Zb5Pmm6hwVtkRdpWTwp5ySrhN2ZP+Csq+cKiclvbblDPCPcpZ4cQR5JKcn1QOhVPKrrRPK3vCGWWf81EOOB8w73+Zj3JW2Fd2hQNlT7ij2r9wqJwW7lYOhM2R5IKwo1wUTimHwukqcz7V9sy/2l+d5KtckvpCtb3UdwrjEC4pO8Jl5aSw+aT2L/05yimuv3JauFk5I5wTfrPXy0p9K+vHkPX90lhywPpx5AJ5BrlIzpG7yDPJZfIs7X8I72dykjyd3ESeTc6S82SP7JH1/y+bo/myfi65gzxP8yMv1vzI4zW/TwlPIDeQJ5IbyZM0X/JkcjN5PjlHXqD5k6eQfbKr+ZOXkAvkqWT9+n0auZP1C8ndn/oved69w8do/vyn4zi+npJD8hjh3r/PJXeTx5HLbJ8nm+OFc+RG8nhyM3kC2SVPJHvkSWSfPJkckM8iF8lTyF3kqeQe8jSyc4LwdHKSPEPzI88k58izyK3k2eR24e0Peb5W6ju1viDcpRwKl5UDYZMhF4WTYD6fKpxWLkl9VrksnFdOS3ufjDtV8lVOSn1ROSU=
*/