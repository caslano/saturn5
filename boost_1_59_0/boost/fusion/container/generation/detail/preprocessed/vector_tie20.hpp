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
        struct vector_tie;
    }
    namespace result_of
    {
        template <typename T0>
        struct vector_tie< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0&> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0&>
    vector_tie(T0 & arg0)
    {
        return vector<T0&>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct vector_tie< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1&> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1&>
    vector_tie(T0 & arg0 , T1 & arg1)
    {
        return vector<T0& , T1&>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct vector_tie< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2)
    {
        return vector<T0& , T1& , T2&>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct vector_tie< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3)
    {
        return vector<T0& , T1& , T2& , T3&>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4)
    {
        return vector<T0& , T1& , T2& , T3& , T4&>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19);
    }
}}

/* vector_tie20.hpp
+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
*/