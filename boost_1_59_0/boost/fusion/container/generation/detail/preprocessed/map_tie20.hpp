/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct void_;
    namespace result_of
    {
        template <
            typename K0 = void_ , typename K1 = void_ , typename K2 = void_ , typename K3 = void_ , typename K4 = void_ , typename K5 = void_ , typename K6 = void_ , typename K7 = void_ , typename K8 = void_ , typename K9 = void_ , typename K10 = void_ , typename K11 = void_ , typename K12 = void_ , typename K13 = void_ , typename K14 = void_ , typename K15 = void_ , typename K16 = void_ , typename K17 = void_ , typename K18 = void_ , typename K19 = void_
          , typename D0 = void_ , typename D1 = void_ , typename D2 = void_ , typename D3 = void_ , typename D4 = void_ , typename D5 = void_ , typename D6 = void_ , typename D7 = void_ , typename D8 = void_ , typename D9 = void_ , typename D10 = void_ , typename D11 = void_ , typename D12 = void_ , typename D13 = void_ , typename D14 = void_ , typename D15 = void_ , typename D16 = void_ , typename D17 = void_ , typename D18 = void_ , typename D19 = void_
          , typename Extra = void_
        >
        struct map_tie;
        template <>
        struct map_tie<>
        {
            typedef map<> type;
        };
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<>
    map_tie()
    {
        return map<>();
    }
    namespace result_of
    {
        template <
            typename K0
          , typename D0
        >
        struct map_tie<K0, D0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> > type;
        };
    }
    template <
        typename K0
      , typename D0
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> >
    map_tie(D0 & arg0)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> >(
            fusion::pair_tie<K0>(arg0));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1
          , typename D0 , typename D1
        >
        struct map_tie<K0 , K1, D0 , D1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> > type;
        };
    }
    template <
        typename K0 , typename K1
      , typename D0 , typename D1
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> >
    map_tie(D0 & arg0 , D1 & arg1)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2
          , typename D0 , typename D1 , typename D2
        >
        struct map_tie<K0 , K1 , K2, D0 , D1 , D2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2
      , typename D0 , typename D1 , typename D2
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3
          , typename D0 , typename D1 , typename D2 , typename D3
        >
        struct map_tie<K0 , K1 , K2 , K3, D0 , D1 , D2 , D3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3
      , typename D0 , typename D1 , typename D2 , typename D3
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4, D0 , D1 , D2 , D3 , D4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5, D0 , D1 , D2 , D3 , D4 , D5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6, D0 , D1 , D2 , D3 , D4 , D5 , D6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11 , K12, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , D12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11 , D12 & arg12)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11) , fusion::pair_tie<K12>(arg12));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11 , K12 , K13, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , D12 , D13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11 , D12 & arg12 , D13 & arg13)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11) , fusion::pair_tie<K12>(arg12) , fusion::pair_tie<K13>(arg13));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11 , K12 , K13 , K14, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , D12 , D13 , D14 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11 , D12 & arg12 , D13 & arg13 , D14 & arg14)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11) , fusion::pair_tie<K12>(arg12) , fusion::pair_tie<K13>(arg13) , fusion::pair_tie<K14>(arg14));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11 , K12 , K13 , K14 , K15, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , D12 , D13 , D14 , D15 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11 , D12 & arg12 , D13 & arg13 , D14 & arg14 , D15 & arg15)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11) , fusion::pair_tie<K12>(arg12) , fusion::pair_tie<K13>(arg13) , fusion::pair_tie<K14>(arg14) , fusion::pair_tie<K15>(arg15));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15 , typename K16
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15 , typename D16
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11 , K12 , K13 , K14 , K15 , K16, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , D12 , D13 , D14 , D15 , D16 , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15 , typename K16
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15 , typename D16
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11 , D12 & arg12 , D13 & arg13 , D14 & arg14 , D15 & arg15 , D16 & arg16)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11) , fusion::pair_tie<K12>(arg12) , fusion::pair_tie<K13>(arg13) , fusion::pair_tie<K14>(arg14) , fusion::pair_tie<K15>(arg15) , fusion::pair_tie<K16>(arg16));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15 , typename K16 , typename K17
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15 , typename D16 , typename D17
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11 , K12 , K13 , K14 , K15 , K16 , K17, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , D12 , D13 , D14 , D15 , D16 , D17 , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15 , typename K16 , typename K17
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15 , typename D16 , typename D17
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11 , D12 & arg12 , D13 & arg13 , D14 & arg14 , D15 & arg15 , D16 & arg16 , D17 & arg17)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11) , fusion::pair_tie<K12>(arg12) , fusion::pair_tie<K13>(arg13) , fusion::pair_tie<K14>(arg14) , fusion::pair_tie<K15>(arg15) , fusion::pair_tie<K16>(arg16) , fusion::pair_tie<K17>(arg17));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15 , typename K16 , typename K17 , typename K18
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15 , typename D16 , typename D17 , typename D18
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11 , K12 , K13 , K14 , K15 , K16 , K17 , K18, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , D12 , D13 , D14 , D15 , D16 , D17 , D18 , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> , fusion::pair< K18 , typename add_reference<D18>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15 , typename K16 , typename K17 , typename K18
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15 , typename D16 , typename D17 , typename D18
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> , fusion::pair< K18 , typename add_reference<D18>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11 , D12 & arg12 , D13 & arg13 , D14 & arg14 , D15 & arg15 , D16 & arg16 , D17 & arg17 , D18 & arg18)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> , fusion::pair< K18 , typename add_reference<D18>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11) , fusion::pair_tie<K12>(arg12) , fusion::pair_tie<K13>(arg13) , fusion::pair_tie<K14>(arg14) , fusion::pair_tie<K15>(arg15) , fusion::pair_tie<K16>(arg16) , fusion::pair_tie<K17>(arg17) , fusion::pair_tie<K18>(arg18));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15 , typename K16 , typename K17 , typename K18 , typename K19
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15 , typename D16 , typename D17 , typename D18 , typename D19
        >
        struct map_tie<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9 , K10 , K11 , K12 , K13 , K14 , K15 , K16 , K17 , K18 , K19, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , D10 , D11 , D12 , D13 , D14 , D15 , D16 , D17 , D18 , D19 , void_>
        {
            typedef map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> , fusion::pair< K18 , typename add_reference<D18>::type> , fusion::pair< K19 , typename add_reference<D19>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9 , typename K10 , typename K11 , typename K12 , typename K13 , typename K14 , typename K15 , typename K16 , typename K17 , typename K18 , typename K19
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9 , typename D10 , typename D11 , typename D12 , typename D13 , typename D14 , typename D15 , typename D16 , typename D17 , typename D18 , typename D19
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> , fusion::pair< K18 , typename add_reference<D18>::type> , fusion::pair< K19 , typename add_reference<D19>::type> >
    map_tie(D0 & arg0 , D1 & arg1 , D2 & arg2 , D3 & arg3 , D4 & arg4 , D5 & arg5 , D6 & arg6 , D7 & arg7 , D8 & arg8 , D9 & arg9 , D10 & arg10 , D11 & arg11 , D12 & arg12 , D13 & arg13 , D14 & arg14 , D15 & arg15 , D16 & arg16 , D17 & arg17 , D18 & arg18 , D19 & arg19)
    {
        return map<fusion::pair< K0 , typename add_reference<D0>::type> , fusion::pair< K1 , typename add_reference<D1>::type> , fusion::pair< K2 , typename add_reference<D2>::type> , fusion::pair< K3 , typename add_reference<D3>::type> , fusion::pair< K4 , typename add_reference<D4>::type> , fusion::pair< K5 , typename add_reference<D5>::type> , fusion::pair< K6 , typename add_reference<D6>::type> , fusion::pair< K7 , typename add_reference<D7>::type> , fusion::pair< K8 , typename add_reference<D8>::type> , fusion::pair< K9 , typename add_reference<D9>::type> , fusion::pair< K10 , typename add_reference<D10>::type> , fusion::pair< K11 , typename add_reference<D11>::type> , fusion::pair< K12 , typename add_reference<D12>::type> , fusion::pair< K13 , typename add_reference<D13>::type> , fusion::pair< K14 , typename add_reference<D14>::type> , fusion::pair< K15 , typename add_reference<D15>::type> , fusion::pair< K16 , typename add_reference<D16>::type> , fusion::pair< K17 , typename add_reference<D17>::type> , fusion::pair< K18 , typename add_reference<D18>::type> , fusion::pair< K19 , typename add_reference<D19>::type> >(
            fusion::pair_tie<K0>(arg0) , fusion::pair_tie<K1>(arg1) , fusion::pair_tie<K2>(arg2) , fusion::pair_tie<K3>(arg3) , fusion::pair_tie<K4>(arg4) , fusion::pair_tie<K5>(arg5) , fusion::pair_tie<K6>(arg6) , fusion::pair_tie<K7>(arg7) , fusion::pair_tie<K8>(arg8) , fusion::pair_tie<K9>(arg9) , fusion::pair_tie<K10>(arg10) , fusion::pair_tie<K11>(arg11) , fusion::pair_tie<K12>(arg12) , fusion::pair_tie<K13>(arg13) , fusion::pair_tie<K14>(arg14) , fusion::pair_tie<K15>(arg15) , fusion::pair_tie<K16>(arg16) , fusion::pair_tie<K17>(arg17) , fusion::pair_tie<K18>(arg18) , fusion::pair_tie<K19>(arg19));
    }
}}

/* map_tie20.hpp
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
*/