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