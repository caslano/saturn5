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
B0upE3hR83qZvNPjNhu4M7FrI5JZA45afhx9HD6hJ5VZ54a1SnoPrzoFoS2VEnsxJ45CPWuO5KRfxZFdO6zJMvNYOUcGgHSbpNLA723lbiH2Gah5/4z7r578dafMUtmYE2UVryFKBMj1kW0OOLAbGlXyVzd4c31QAtP1icn7GP/M6B6FO03/6gQFwqcgVQNZ8d4QOLGhftMK+xa71OnJz7EtfvB4SM4NZe7NUOVhJBYaYQNAO8AQzM0W78zz2kgmOhfShtRoJZ6tptFWASikVWrYFrMRxOSeG1NmWzRljDXabQ7Mbowviv+LGIPBpqiTOFsVxlHLZDH+jdjLkMg5nLaRSCobmy/S4D1bZyLYpoT0pg9hBH/QttHlcfYizY3LkPfGkrqeproLiy1xEvGvJk64fFNVaB31Tm9L24ClPp1SvunNXzNU2kfk1lj3/3obdbrNih/Fua2RQKK/HK45u77ssamyCxP2k6DPmINp+IXQFDRE2QdRY+8B2kJGDpqPGPTt4udYDpNgbHBO74bNQrBlLdwSjuZdxDMLnDGzGH7k9052sah9oOmMod7+R+uGBP5+Rj8dStgltkdoZs4fvHUBeOm5iXqlfPAaqjR0TqvNdwXVMX4OTAQMOKQQnmo9ysrto3eyd4tWXP/FaP81VKfrKn1MRLr4OtY2nQo4PCZp+mQwxtDh1tk8dTa/qC+5xLpHHFshSNzaIr9P
*/