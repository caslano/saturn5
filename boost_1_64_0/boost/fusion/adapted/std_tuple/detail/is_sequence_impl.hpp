/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_09242011_1744

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct std_tuple_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<std_tuple_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
owqNZ54I9Ur/shVgT0bMTN6BPRUx80EdeX9aMT1GfSbQuf5x3p4NmNRB3GEa8dg/f4tsnA+I/z3BORKO4x8BD+ok2fwztpFkIC//im2QDP6u+O+Qp+sn+ew/gS3qKLHnUmwex7HBZjGL6yqHs2FkKz57XsiCNvr8kIs3yF8bBTyo1zyPGtugbotPN07Y6Ha1ScCpTuLZTSOGeg6+WcRR18E3jzjqO/rZLZjT28HNnWqNKjr7ekutu0rObKuArSXIfn6Rz7QTib/Y5+IcxLt1yDlsnjPVLKz0ds40sAnfAdsGHNFTXdxOsx6V3d2Rqm25spO+faTPo7TvEOsqadxnv2x9NrTSh+121HbJBsN53UnbIaNu357HJBrLd/b4aFSOu4RcGgLxXUOO+K3/dtOcKiqneXetuwbAbA/NXOVn9grNXMXntOyZZKaAj+O07KW5+iazd6i7y6ey6jR8vE9kY9oQnt83xfC49fMrQxvX1pjvl+BrVZvYP+a6rMjmgJRNUB8OTNlwPFTnDgp52P6Q54MTduH7b1bCxibnIMNnRzzdFt0cbGjP7ZHSMyfNUAr8/CFJm3mU77lpprNEfcehsV3cfmF7WGwbt2GUy7zQFo5y96ZGPC6TI2IbnXzy+ZHrsal02tV6o1g0LetAXhXZj0b17tWxje4nyOY1sU30TnhtaENtmP1zVMzQZzDvjzn6DebzY47+gdM3kOboPzh9g8aGrwEz8Y4tKvcvoBUXxErC5vcvLHu/aRcErGHPmfV1Ny+6SPRiJ5Cs0ICfhmLu5myPjpn7rXyMY3ysbr3Ozyz2dbOWorFmEt9Nlggr8mvTT21mOGKYyDHzQvPMD0k7h7B0PXara/k8W9dGetnRFBXbHNvbpj2Fdjfay4ajs1uQKH/lyFbmEcYixtM0OIaPbJatxyaHzfKkDZwEm+OSNnAQbFb0sMmrE5mNa2Xahn+Gw+Z1SRt/7v34Xja4L+qEJDdzdJPUAVIYJyZt5J6k10dc1pJUIibzMCc5RktDzCxZsYWymErgdlX1OGWL54B9faLdyJr1qXVNPEw2td42xTdAqs/13jb0LdC2+8yzkzVKE74+1TIfZAx0a94nPU7FSz5ZFeu5javhGOo6/Hiy093OvNzERb8TVjsm35CnRCsOHJuuwqfTWu/MKgDpTU+nak/xtmK9CJDyP+Mz7T9K1ymO07QGaW2nyX6zXGvZNDIoa7k7ATfLjND2uT50Az5jvomRV00ttn3tGrExbiOfmKrC7NSYmSrCbG3EqGoQWyfMuLEyU2w3bXb4t9tpjsm67Dd42kw1x5jxdKdz0qvdzipUCornjIDPHEabEOjZN0bMeIYwx3mm5u3cvXvOUvp4VvH2lJ7tGGa/4ac3eXp3hgn2jgrrNv1cEH9LxJELPP/WkEtOKO63OY7VFhQ5+/rtllWWLFwwm/PwDmhz3SsS+0edrl+RzN7lGH+hrtDGZZwTm2KV8qJ+xPcex407yT+Ye430SmONnXuNWc4FwWG+X/MC47kPhPqsYrNKy62H+KDiq+sTnBo8+yHH1vijBLxTPqw4UiMmCP8c2BxW6R8bG6VVgqbhYe+oz5aXRocWrKyoM2EdHxxaaNdYI78fCxnGZB/XerAO+ROOlYbpul21DvSTEZN0fCpist7t05oVGynHStg+y/zcJJf9zZ9Jcllnep7iy82KzRG1LvOzEZN36fkRk3WZn3MMt2r2Dw/iZk2cc8J2F/S28/YwfL63nUkQ21zY28aNgS9yNqMlM79QcetmEc/FKT6JKo18X5KwcftdAxaurb00xfPM1YPLLKdqXBrU9fHykKE+fjHQdXxX+GxUMoyzXCOuM8x95VVJG6k=
*/