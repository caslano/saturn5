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
            typename K0 = void_ , typename K1 = void_ , typename K2 = void_ , typename K3 = void_ , typename K4 = void_ , typename K5 = void_ , typename K6 = void_ , typename K7 = void_ , typename K8 = void_ , typename K9 = void_
          , typename D0 = void_ , typename D1 = void_ , typename D2 = void_ , typename D3 = void_ , typename D4 = void_ , typename D5 = void_ , typename D6 = void_ , typename D7 = void_ , typename D8 = void_ , typename D9 = void_
          , typename Extra = void_
        >
        struct make_map;
        template <>
        struct make_map<>
        {
            typedef map<> type;
        };
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<>
    make_map()
    {
        return map<>();
    }
    namespace result_of
    {
        template <
            typename K0
          , typename D0
        >
        struct make_map<K0, D0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> > type;
        };
    }
    template <
        typename K0
      , typename D0
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> >
    make_map(D0 const& arg0)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> >(
            fusion::make_pair<K0>(arg0));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1
          , typename D0 , typename D1
        >
        struct make_map<K0 , K1, D0 , D1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> > type;
        };
    }
    template <
        typename K0 , typename K1
      , typename D0 , typename D1
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> >
    make_map(D0 const& arg0 , D1 const& arg1)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2
          , typename D0 , typename D1 , typename D2
        >
        struct make_map<K0 , K1 , K2, D0 , D1 , D2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2
      , typename D0 , typename D1 , typename D2
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> >
    make_map(D0 const& arg0 , D1 const& arg1 , D2 const& arg2)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1) , fusion::make_pair<K2>(arg2));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3
          , typename D0 , typename D1 , typename D2 , typename D3
        >
        struct make_map<K0 , K1 , K2 , K3, D0 , D1 , D2 , D3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3
      , typename D0 , typename D1 , typename D2 , typename D3
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> >
    make_map(D0 const& arg0 , D1 const& arg1 , D2 const& arg2 , D3 const& arg3)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1) , fusion::make_pair<K2>(arg2) , fusion::make_pair<K3>(arg3));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4
        >
        struct make_map<K0 , K1 , K2 , K3 , K4, D0 , D1 , D2 , D3 , D4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> >
    make_map(D0 const& arg0 , D1 const& arg1 , D2 const& arg2 , D3 const& arg3 , D4 const& arg4)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1) , fusion::make_pair<K2>(arg2) , fusion::make_pair<K3>(arg3) , fusion::make_pair<K4>(arg4));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5
        >
        struct make_map<K0 , K1 , K2 , K3 , K4 , K5, D0 , D1 , D2 , D3 , D4 , D5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> >
    make_map(D0 const& arg0 , D1 const& arg1 , D2 const& arg2 , D3 const& arg3 , D4 const& arg4 , D5 const& arg5)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1) , fusion::make_pair<K2>(arg2) , fusion::make_pair<K3>(arg3) , fusion::make_pair<K4>(arg4) , fusion::make_pair<K5>(arg5));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6
        >
        struct make_map<K0 , K1 , K2 , K3 , K4 , K5 , K6, D0 , D1 , D2 , D3 , D4 , D5 , D6 , void_ , void_ , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> >
    make_map(D0 const& arg0 , D1 const& arg1 , D2 const& arg2 , D3 const& arg3 , D4 const& arg4 , D5 const& arg5 , D6 const& arg6)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1) , fusion::make_pair<K2>(arg2) , fusion::make_pair<K3>(arg3) , fusion::make_pair<K4>(arg4) , fusion::make_pair<K5>(arg5) , fusion::make_pair<K6>(arg6));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7
        >
        struct make_map<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , void_ , void_ , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> >
    make_map(D0 const& arg0 , D1 const& arg1 , D2 const& arg2 , D3 const& arg3 , D4 const& arg4 , D5 const& arg5 , D6 const& arg6 , D7 const& arg7)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1) , fusion::make_pair<K2>(arg2) , fusion::make_pair<K3>(arg3) , fusion::make_pair<K4>(arg4) , fusion::make_pair<K5>(arg5) , fusion::make_pair<K6>(arg6) , fusion::make_pair<K7>(arg7));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8
        >
        struct make_map<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , void_ , void_ , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> , fusion::pair< K8 , typename detail::as_fusion_element<D8>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> , fusion::pair< K8 , typename detail::as_fusion_element<D8>::type> >
    make_map(D0 const& arg0 , D1 const& arg1 , D2 const& arg2 , D3 const& arg3 , D4 const& arg4 , D5 const& arg5 , D6 const& arg6 , D7 const& arg7 , D8 const& arg8)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> , fusion::pair< K8 , typename detail::as_fusion_element<D8>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1) , fusion::make_pair<K2>(arg2) , fusion::make_pair<K3>(arg3) , fusion::make_pair<K4>(arg4) , fusion::make_pair<K5>(arg5) , fusion::make_pair<K6>(arg6) , fusion::make_pair<K7>(arg7) , fusion::make_pair<K8>(arg8));
    }
    namespace result_of
    {
        template <
            typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9
          , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9
        >
        struct make_map<K0 , K1 , K2 , K3 , K4 , K5 , K6 , K7 , K8 , K9, D0 , D1 , D2 , D3 , D4 , D5 , D6 , D7 , D8 , D9 , void_>
        {
            typedef map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> , fusion::pair< K8 , typename detail::as_fusion_element<D8>::type> , fusion::pair< K9 , typename detail::as_fusion_element<D9>::type> > type;
        };
    }
    template <
        typename K0 , typename K1 , typename K2 , typename K3 , typename K4 , typename K5 , typename K6 , typename K7 , typename K8 , typename K9
      , typename D0 , typename D1 , typename D2 , typename D3 , typename D4 , typename D5 , typename D6 , typename D7 , typename D8 , typename D9
    >
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> , fusion::pair< K8 , typename detail::as_fusion_element<D8>::type> , fusion::pair< K9 , typename detail::as_fusion_element<D9>::type> >
    make_map(D0 const& arg0 , D1 const& arg1 , D2 const& arg2 , D3 const& arg3 , D4 const& arg4 , D5 const& arg5 , D6 const& arg6 , D7 const& arg7 , D8 const& arg8 , D9 const& arg9)
    {
        return map<fusion::pair< K0 , typename detail::as_fusion_element<D0>::type> , fusion::pair< K1 , typename detail::as_fusion_element<D1>::type> , fusion::pair< K2 , typename detail::as_fusion_element<D2>::type> , fusion::pair< K3 , typename detail::as_fusion_element<D3>::type> , fusion::pair< K4 , typename detail::as_fusion_element<D4>::type> , fusion::pair< K5 , typename detail::as_fusion_element<D5>::type> , fusion::pair< K6 , typename detail::as_fusion_element<D6>::type> , fusion::pair< K7 , typename detail::as_fusion_element<D7>::type> , fusion::pair< K8 , typename detail::as_fusion_element<D8>::type> , fusion::pair< K9 , typename detail::as_fusion_element<D9>::type> >(
            fusion::make_pair<K0>(arg0) , fusion::make_pair<K1>(arg1) , fusion::make_pair<K2>(arg2) , fusion::make_pair<K3>(arg3) , fusion::make_pair<K4>(arg4) , fusion::make_pair<K5>(arg5) , fusion::make_pair<K6>(arg6) , fusion::make_pair<K7>(arg7) , fusion::make_pair<K8>(arg8) , fusion::make_pair<K9>(arg9));
    }
}}

/* make_map10.hpp
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
*/