    ///////////////////////////////////////////////////////////////////////////////
    /// \file expand_pack.hpp
    /// Contains helpers for pseudo-pack expansion.
    //
    //  Copyright 2012 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
        template<typename Tfx, typename Ret >
        struct expand_pattern_helper<Tfx, Ret()>
        {
            typedef Ret (*type)();
            typedef mpl::bool_< false> applied;
        };
        template<typename Tfx, typename Ret , typename A0>
        struct expand_pattern_helper<Tfx, Ret(A0)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1 , typename A2>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1 , A2)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type , typename expand_pattern_helper<Tfx, A2>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || expand_pattern_helper<Tfx, A2>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1 , typename A2 , typename A3>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1 , A2 , A3)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type , typename expand_pattern_helper<Tfx, A2>::type , typename expand_pattern_helper<Tfx, A3>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || expand_pattern_helper<Tfx, A2>::applied::value || expand_pattern_helper<Tfx, A3>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1 , A2 , A3 , A4)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type , typename expand_pattern_helper<Tfx, A2>::type , typename expand_pattern_helper<Tfx, A3>::type , typename expand_pattern_helper<Tfx, A4>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || expand_pattern_helper<Tfx, A2>::applied::value || expand_pattern_helper<Tfx, A3>::applied::value || expand_pattern_helper<Tfx, A4>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1 , A2 , A3 , A4 , A5)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type , typename expand_pattern_helper<Tfx, A2>::type , typename expand_pattern_helper<Tfx, A3>::type , typename expand_pattern_helper<Tfx, A4>::type , typename expand_pattern_helper<Tfx, A5>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || expand_pattern_helper<Tfx, A2>::applied::value || expand_pattern_helper<Tfx, A3>::applied::value || expand_pattern_helper<Tfx, A4>::applied::value || expand_pattern_helper<Tfx, A5>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type , typename expand_pattern_helper<Tfx, A2>::type , typename expand_pattern_helper<Tfx, A3>::type , typename expand_pattern_helper<Tfx, A4>::type , typename expand_pattern_helper<Tfx, A5>::type , typename expand_pattern_helper<Tfx, A6>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || expand_pattern_helper<Tfx, A2>::applied::value || expand_pattern_helper<Tfx, A3>::applied::value || expand_pattern_helper<Tfx, A4>::applied::value || expand_pattern_helper<Tfx, A5>::applied::value || expand_pattern_helper<Tfx, A6>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type , typename expand_pattern_helper<Tfx, A2>::type , typename expand_pattern_helper<Tfx, A3>::type , typename expand_pattern_helper<Tfx, A4>::type , typename expand_pattern_helper<Tfx, A5>::type , typename expand_pattern_helper<Tfx, A6>::type , typename expand_pattern_helper<Tfx, A7>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || expand_pattern_helper<Tfx, A2>::applied::value || expand_pattern_helper<Tfx, A3>::applied::value || expand_pattern_helper<Tfx, A4>::applied::value || expand_pattern_helper<Tfx, A5>::applied::value || expand_pattern_helper<Tfx, A6>::applied::value || expand_pattern_helper<Tfx, A7>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type , typename expand_pattern_helper<Tfx, A2>::type , typename expand_pattern_helper<Tfx, A3>::type , typename expand_pattern_helper<Tfx, A4>::type , typename expand_pattern_helper<Tfx, A5>::type , typename expand_pattern_helper<Tfx, A6>::type , typename expand_pattern_helper<Tfx, A7>::type , typename expand_pattern_helper<Tfx, A8>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || expand_pattern_helper<Tfx, A2>::applied::value || expand_pattern_helper<Tfx, A3>::applied::value || expand_pattern_helper<Tfx, A4>::applied::value || expand_pattern_helper<Tfx, A5>::applied::value || expand_pattern_helper<Tfx, A6>::applied::value || expand_pattern_helper<Tfx, A7>::applied::value || expand_pattern_helper<Tfx, A8>::applied::value || false> applied;
        };
        template<typename Tfx, typename Ret , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct expand_pattern_helper<Tfx, Ret(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
        {
            typedef Ret (*type)(typename expand_pattern_helper<Tfx, A0>::type , typename expand_pattern_helper<Tfx, A1>::type , typename expand_pattern_helper<Tfx, A2>::type , typename expand_pattern_helper<Tfx, A3>::type , typename expand_pattern_helper<Tfx, A4>::type , typename expand_pattern_helper<Tfx, A5>::type , typename expand_pattern_helper<Tfx, A6>::type , typename expand_pattern_helper<Tfx, A7>::type , typename expand_pattern_helper<Tfx, A8>::type , typename expand_pattern_helper<Tfx, A9>::type);
            typedef mpl::bool_<expand_pattern_helper<Tfx, A0>::applied::value || expand_pattern_helper<Tfx, A1>::applied::value || expand_pattern_helper<Tfx, A2>::applied::value || expand_pattern_helper<Tfx, A3>::applied::value || expand_pattern_helper<Tfx, A4>::applied::value || expand_pattern_helper<Tfx, A5>::applied::value || expand_pattern_helper<Tfx, A6>::applied::value || expand_pattern_helper<Tfx, A7>::applied::value || expand_pattern_helper<Tfx, A8>::applied::value || expand_pattern_helper<Tfx, A9>::applied::value || false> applied;
        };

/* expand_pack.hpp
aj3rxcWetWGdwMAN4IB2CbUl09eDh7BuXBc7i5U2BNDADgjbier0QOIpS00r4e2Q8YMYd0pPcwbtfzDWoc0tTbEyH+JZ+x7qWecexuWj96aeRekx/dKAh2gOQfjwKCyb7V1B2y2zMDmRpT55BNKOwMjTkbCDkJW0jbvchuXWnFSXhSL+CtgBpLt7usK4RxEsciEI3NGEs0twso04hnE97gx1pYW3doVprgrDVC/HBvnrTDcG7XicCUc3clAQ8Dveg9P5PCHKS8DvxEgugvp9tgmjwU14ddDenc2wfXgO6lW6WMTzJMCM6UhPa6Y3IxsprZnOdDhGpIO+27W+d11zG+SoIYSBptHjX7EphBlXiF2ZyK9EBnsjGxBeE+5rILzWjXEWamDrgjG6uxtjdLPzD2HxJ4d7JcoP5PoALofspmbb5GC6Mx22V0vQXulNvR3NHRkZjTPBONGK/KWbpKOgXtvUXky7DdvbmivCtDocbHkIOyWCBfE6A/kVQBDuQtgQmHA3wpYx8tljYRBKwDYEee/uQXhj5JMyE42lm4J+1SRH1pk1MvkY2KnKpuU0GuetYQXiPlfBe9eku0UgLO70aOxeYXk+LxzvcUb//ECepEfKWXm3qFhrA3hv0GYtHW1B+AWQj+6OXiEUuUH994X8WtMyk7l5dPMe8JZMOH59cb7lFbNV+RJgbe2u3a6OYK5NriEYt921BOd2/jLgdjcPsK9EtCKArYFdxldd/ObG9ZloPLkugKN2pXEgY9cD3pJZm248tTMjFWf53BCDi3yj/m4EvL3NdtzIVuqmKF2KAdzXgIOZiIXdHMKa16ZbpEgG9vUAhmUjMKjrW0Jcj+QfcvwNwIysNFlEAP8m4NidtbBvARbO8gb2bcDsoNfQ2b4e8b8Txm935ftuAIO9xT5bpX22SvtslaZjq3TfLAPbFOs7vwMstCO8H2HWiX8PGJfrAYYFembC5pvis63Ggy4dC7Z5BIzfTPpwaLeU41nH8bwHZlpAZEcEpN32SuR1hsLZAVlwa2gv7DbshZkVunkhvHc0eGp6cGA8SDkLEucttNY1BObdcPf2udmrTpp9rC0Dmye38Z1vWX0PDMsmRnjc8nC0Bv4xr4Gxft9j5U5r9jVT+0BmB7KWgReDfZSfYA2fA8/Q2abjqTHg+TPw3Iq6+qktn0l43ObJwO60ewNhRNoXie7AWBh8624Z2No3OTTRSz52I1ibPYOZLfX4c6rH0hz2MDYgf0twntK7tW/H4FDgA6uyyHph7BXoaN+W5RZWYtvRwvqGBrdFPk6qhLYwol2RCM/RflER870hXq6wlzky1rcN1aiA8JXq9fcbeQORX9n96P0D6Zj9q3srnB+RM2J+DbZt7bWuULb29aN9DG2egW9z78bXSdlfZ2Bbd4xsIbuhNxiYOL4YH+u3dfdLiXuRgY0PDZp9sbDNfsVnjTMs416x55F0bb4ZEGuzOuU7dxK2SsabS4jPExmRfkZ7bBIm3zTfkLQLE8PSuWRvEvn5DcvQM9ibXDllm0iNrrTRGRDtp92HflNPZYTvCldG+KsJfTDez2eUGDv6hkaHafxwwL3u+5niDJxtX0FDZAeZ6n2zrkZxgC6rEhslDNh0Loz3MSkuepngQvjMAG43RCO7M9AOjbzQHBZY+OnFUsYAbuouok0FsPH+EXEUORiML3+oUHDxgzLZP5FYiT3TB6neqnNoH+yVyzmi/w7+Q9hb3x2dCcwutvdPJG74O1kt8x7q4xGb/mkjw+gzf7LhloGdA0MJ1wc39A1NDkQ+oB/ls/Ep6vz4KWzKhrfyIbmCSew1U8jVsHzG8m6EOChMxMefh5H+8VHz9t3kwHgkYQo=
*/