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
            typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_ , typename T10 = void_ , typename T11 = void_ , typename T12 = void_ , typename T13 = void_ , typename T14 = void_ , typename T15 = void_ , typename T16 = void_ , typename T17 = void_ , typename T18 = void_ , typename T19 = void_
          , typename Extra = void_
        >
        struct make_vector;
        template <>
        struct make_vector<>
        {
            typedef vector0<> type;
        };
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector0<>
    make_vector()
    {
        return vector0<>();
    }
    namespace result_of
    {
        template <typename T0>
        struct make_vector< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector1<typename detail::as_fusion_element<T0>::type> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector1<typename detail::as_fusion_element<T0>::type>
    make_vector(T0 const& arg0)
    {
        return vector1<typename detail::as_fusion_element<T0>::type>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct make_vector< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector2<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector2<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>
    make_vector(T0 const& arg0 , T1 const& arg1)
    {
        return vector2<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct make_vector< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector3<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector3<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2)
    {
        return vector3<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct make_vector< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector4<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector4<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3)
    {
        return vector4<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector5<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector5<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4)
    {
        return vector5<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector6<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector6<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5)
    {
        return vector6<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector7<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector7<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6)
    {
        return vector7<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector8<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector8<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7)
    {
        return vector8<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector9<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector9<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8)
    {
        return vector9<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector10<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector10<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9)
    {
        return vector10<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector11<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector11<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10)
    {
        return vector11<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector12<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector12<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11)
    {
        return vector12<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector13<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector13<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12)
    {
        return vector13<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector14<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector14<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13)
    {
        return vector14<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector15<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector15<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14)
    {
        return vector15<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector16<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector16<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15)
    {
        return vector16<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ >
        {
            typedef vector17<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector17<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16)
    {
        return vector17<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ >
        {
            typedef vector18<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector18<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17)
    {
        return vector18<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ >
        {
            typedef vector19<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector19<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17 , T18 const& arg18)
    {
        return vector19<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
        struct make_vector< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ >
        {
            typedef vector20<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector20<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type>
    make_vector(T0 const& arg0 , T1 const& arg1 , T2 const& arg2 , T3 const& arg3 , T4 const& arg4 , T5 const& arg5 , T6 const& arg6 , T7 const& arg7 , T8 const& arg8 , T9 const& arg9 , T10 const& arg10 , T11 const& arg11 , T12 const& arg12 , T13 const& arg13 , T14 const& arg14 , T15 const& arg15 , T16 const& arg16 , T17 const& arg17 , T18 const& arg18 , T19 const& arg19)
    {
        return vector20<typename detail::as_fusion_element<T0>::type , typename detail::as_fusion_element<T1>::type , typename detail::as_fusion_element<T2>::type , typename detail::as_fusion_element<T3>::type , typename detail::as_fusion_element<T4>::type , typename detail::as_fusion_element<T5>::type , typename detail::as_fusion_element<T6>::type , typename detail::as_fusion_element<T7>::type , typename detail::as_fusion_element<T8>::type , typename detail::as_fusion_element<T9>::type , typename detail::as_fusion_element<T10>::type , typename detail::as_fusion_element<T11>::type , typename detail::as_fusion_element<T12>::type , typename detail::as_fusion_element<T13>::type , typename detail::as_fusion_element<T14>::type , typename detail::as_fusion_element<T15>::type , typename detail::as_fusion_element<T16>::type , typename detail::as_fusion_element<T17>::type , typename detail::as_fusion_element<T18>::type , typename detail::as_fusion_element<T19>::type>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19);
    }
}}

/* make_vector20.hpp
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
*/