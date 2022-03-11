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