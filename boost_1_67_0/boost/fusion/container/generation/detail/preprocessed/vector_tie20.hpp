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
dB8qhtDUniNQrkOAQWc3H6sxOi8O2uwHYx3ohsiiDPK08A4euZ3xr+FOTTokMrf9Xks+OTj5Z1pyMyX36skbyW+TanWKXcOrrQaamjhcpL3d3A2f8ZswR7i0EOcCT0JmvENYz6mSU/cQMx7dL1FUHQeiRug5WeTp3mDGo6eYtOwerXPBPjjOeuJBNTbUnf8+r7jAG5eS/3ugdvAGZp2KJ1PI1+9jcqQ987627tCnuTvfORMarYlgFnRSoU1p+X5Cqrk7G/4GB/6dM42ZgPs8/BsI82Tb6ZAshEBYMcAGoC69/wyBX4l1/ImJPY8aLV2lpM9p3p4Nvb4PVYiwPFAgISkCWebtZZmRPVC1PfSRuA/O4IsXf8+C8vkMkXQuUwi5f2chEWqpZEbjWgzcSVQ5hvD4IWSZtxsLEgCJXK62osJKX7Y2fmjP3LqJfo2DXwo5V8beOEX/IT84EfOCZvP22ZmRTuiUATv1V3T7KnpxMWC/xkylzlDJ87F31VJU+j0rlSJFOzIUaYe59VGhK2ZnFqXoZn/u295KX2LiXpgDKMRQsdG6DvUv7+uSJpO/ZHa2bzyQONhdaJAc2G433odiozmJRCJ2glBF8oq4L36rrOB83rUEt2T1EkArDp55EUrUoqW1yRUtON2WaLkUmzS9JDo+yYgy9UfNBvLN+ln4L9B1kWMjV94N5qSy+wLYdPUxXqcuWtJVWks3aSnFEUiCF/Kx7Lb2ltlAKcKfHJS/lemzELyYyQJ2ObVqwlaBjLstfAj4BpFzB7X6j/FoDFlmIokJpc+nGEIHx+P9bkkl+yi5E5Jxf/v5L8YPkydH+u/ShSklzlo6DEv9jbXo1APFD+wUfxAquT4PmV19obFAYnwWQ5uUPgnfpaAx5jexeVaK8fnbskvWlTgvW1829eud+Ciz3o8O/O3r502Jwglbh1qOc5yXAyF0hSEoQckriEhHH8kO37paZz78uwH+3Qj/CsQJgH0vBrLaqAmN+Jnx5I6+AVBpwT5+MAv1Ae8aFP9g6yD50BaK1sFepNeVxlp6YZrjYTH+b+PgRBwPjW87FBrDxtOoSsgYoQRmFt/I51lgVB4Y1UTo64L1ZZNb22FUc9b7MapF1fp5k2DbVcCoamBUd8KoFopRLVT8dhRxL2l0eCC1ASm/b+N/GvE/92ckRwbcUYUY3W6hpDvHy6fg6Oh13BNIvAtzI/sCjCcmburQ+ZFudEYcwFftAZMIzQK9rGisJdm4n79hSnp+ogn6nYSyna2pBxcRWTE1P1q0Oewwi3kqYUwzRHNsMz3hsZ0FxyOHjcDoc4zwaQmOgR+hMcrc7L6s35E4fWfksClyRgqOi5yRYYdUOZdiFPBIt4yMVMkqUnN+dRUxkFPRJnXRQuggNgvdm0Ld+4LikIhHKw+sUTbU2IxzkJi4DnpySFivxW9qIgqkGf9700lBHlUAF4jeFW38w3FELtg096wV/D0todGCETDR4avDy58fS5LN64EvNJk3/sVAUpWZeb9WpF+LOBjLMMnCdioNw/Hz7nfOnG6lWXEzbm7NNpDOppVlIDLPHnZf6NdBnkTXgYGug/yx4jowt55Es6b5EorvmfTUl9wHWAdP7vExgvUx/Zh1KDWZ9zELlToApTrfOcP2UyrGDruP2SjnEORA33zvnPEiDIwq4EeNBth7MGVIRuZFdlmre7r9B+Hs8k/H0mQVenjfWLoDCz2wCO5V5GfI6a32w9ecJFM8E8NL8/uxTzCPfaUA0VSNkiRfTzeB+3kS3Fb4haA245YqR8xK7o+qcXNsgLQ+GQMMY5A7BEKR5br5t0T1fMYho4bXjCX5bA6qkMAqVRk7jB9hOE7EWD7hnmuvF0ouTUyUInC29hgKjrtuoSXecCnMMjS1izaguXXFeZj0m+LwVV1dXZn4k2u3ecO3IC1aLrd8QwyuA69M2cPXjMYp11DyTrJ58kXLTXwZpM98wBQth5syD6q6dofGHrsCYUDiAzBI9IKcw+abPKzc4oFx/on8BGrun6IBKxp+RMtt0fn2aACjxqA4kNCZEMdmG5JngvCzRaiIOQAwxvCOZps3LsYYe9SvNkmwhTHZoKWskdC8V2LZaN27Uya2EK17ZXNrFrp77jS39ovb1qkWW5QHnHCKLNFFNrg0q+FulNVqixpwR+tr1ECFWu9RAzPUgGfmNPPGF4SKsoN5TIekgwBVKRISs8/jTUuMCWOi7ZBqN2NuyUEJsiE1dlitnSmj1Kvq6xZWAZeFvN40dp1pQigPCqhwItzqIvQOqS5Chw7qIgslqzZMqqGkGkvfVQigx/iBr7qaK6+iY2l0BoUuBaC+B8YOaUhXoo7xNPOGmpQD4nqkty2drjfSmOCXRxET7OpMY4KfhbTotGidFK2ThXdxrFa/SKTowZgtuB7qrAp/fHEeOwlEq+40MjhbneWOL3bqvj9vRrcNMqCZG1quKmhnXkmVMo37e3bCxlSn4GdJpqxUZco9HZF2uzrFdUMYHX321HWm2RfY/AF2vuPvUu55nFp2UqnfXdDu6qGoONNabuBHP9aeb/8tuRcuzRI2e29mixBSoQlJaZypUxNPvj9YzIlxIX6YLcJ5Baq9vM5AQipg6dVRKH204XqUy8rshLoA1xG4d3wvklSf5fdEm25AT5EUD5n15H74B9SFyf1YmV9I4eMxzLZEcc+XyXukazLV4qNsmaTac/C/xf3GmFqbI8PvyE7YIDkWLFVyzflM1YD5tTl2KgbosAk+tuFHVc6rotAAwKJsey6rg0JOtda2H39V2XpYHZSYkIAShRgkGgVqMb2cO9IBwGz9oug/IdOm3H/e9b55QzUaS767cqYivU/zsxPnB2W70phMVSrEebDL+N+SQnRuodbK+AXr53pXrZL/GX6P1kDtabghC4nw+Vm6G3ht/lP0ViGtb4U/oJFuuGqysjKBEdHzuSVL3A8YRDZYpEjHteBcfv6RpB/xKlroan5USsYEzAtNFXmBLETN+yVDShRb2KmByd2tLTpKWx38qSTARRrAxyUtIJQtlCtyMExmJV+dLHk3gf/uYPAkNUVWojxZ7lsaxGIpGfysJPQNtH4R+Y1ZFAknWf5+aueS5PdSamf0kHaQAkQ+7UMjbVmPKPtdasvL3zdqvc8JzRc5wSwU3nYahd2NSAtRy78y6i09RC0/nfx+mFp+zDjyCO8VsLSWw9Syjy/UW3aG7kE1OpH7SBZS36VJyKuoNzeJvmu9WZ2FpP5lyTKPUm8uSn5HqDeGIb3BFz7szQeZRAJqvVmXJe6CNzOT0R0fpjh9lMuope2Z4ioVaRtoLn6WqbemUA8fF1C1Hm6kUTySLPMY9fCB5Pcm6mF95sjzdROkCx/C6jSlPIGoI6sB/bRzMnIPz1QCn3d8lGl8RymzKCZ0EJARA6zoiHxkiN+1v+es6unp+Qj/HBZ/OP2pORmKud5eOQGKdhhcb8eXvHUSUmvfOhM+rsag7Tni9VEpdsbalUAick6KLxk40wUzhQ30not1q/YBwCDxy3SH/7Hu+Hh1qpoRv1vuwZ8LZfOGA3hk3kBHBMiCRjo+7ziWCe2hdZ5iUkgFYL/SYmOdkOJRZ1lR9SXuNES6HJGdTYC1IoD/DADtrk3x+fvVmhfVWS/GfxoEPINpWyhtmzqrPb54HSa8GJ/fo9bsVWftjS/ehAnbKGG/OiseX/wcJuyNzz+s1hxVZx2NL34RE/ZTQr8660x8cTsmHI3P53B5ZsYX78XPfvyskc1t9QkK4j6HyAjYva4PVi4dhOiUKpuMLBt7N/cdpUQ+Cr9nkCeFGaq7EJAcgAaASzKPYu24CSkaq3rnGdXthFYgZzFlRHCCtVz0GGCfGYaJmRLePsgIXJVkbC6+RCaYtqNx04Bqt6klMqb1U1o/pk1RJRtgaDtmZgLWlpX6hDLbAHuIGLMNuwRBgu6Z8xSruNbexRAkCt2vY46iRCEXM8O9J7Vl9MAa4nJ9FlPsTHWLNZtviXwMO64pwnHNYAi/JM8NNQ3qKvLWOj8//kvx1tqkABYs6dO6G+Lzc+KNcItcBB9N9NGs1lSpJRfBhyPeWKXW5KvuKvpdq9YUqu78+HxbvLFQrbHCZNJvt1pjD63WV6TtUHgh+jYYdDUb98MaoDGnXSmxoG1qXi78jtKKWMUq9GJn7ZE+Q4Tb2w7Fr6HlgkZKeuV4RWF8aaYdmlm5Hz14fCwC6M2h6VJzP8wNAyxg9fACxNcfDK4HaXNyVfgqgq+c3PMYbRzTMcZeu52+PbSB3kdLarys6HK3qMVnIHmGap9gPKuiYohqn463ruo+Gumwq3cehdrQ03yD6t6vTldLjEeRvYjfHe/pVt170e047C61dsJR1RC/+ygm7heJ/QgIOqcWx+NLRh2Fn56e1+PuvXE3FJ+M30VAUcQvw8T9cXe/Wms+am77doICTeE+d6o9iI3RlRdi3NgJaLgq3h1pl9sScODdZ2CvlWbAfwxw9GfhwcePUrm3Gx2UAQrYOEkE57OpWXehNsM5RJ2RzsLcf2CEz9xzMJUHsZ3c97XFstEv1Hh3sDfx7REXDG77fPb+a/gCsHr3pmyK4IbEUb6ybAD+FB1C1gCWsudUrD1uuhrFkaJviDwk/IazdlSVRmkdlIzQQSlHWZbA2lhTvbMfgVwIwJRh9UVFfEZ1XLBl+wgtG1ItOy/QsnpnIVRGMEMBZKYAuL+q63dWjdADYwpA7VcCaBoBgJQC0PxVAH5M+GA4jCyEIRQyBAiEt3on6pVcoDebRoCUnerNlq8czosjABiVArAtsmcMwsBtdkE4e0eAMxA5X6Teud+8sR44Wjy5HXh4Z2Cw8PPkZMUNhwqFZCW6cPc9IhDqzgmeUqS9T8TG7ecy0oiNPxGxcfM5nV35gIiNK89lpBEbPQTrYgErT6TFCNbAWb3eQSI4TpzNSOlDIskxxD7bhk/yuzsOS7m7teC8+Dr/IYpIgH+6iz/3Z41/ysrUAY+Do6mUGlFcvv4saim4PkbfJEGt/xdlI3lVyZdhHrJXV4h0azaOo+5smvIDsFv0Pt/3c2SYI+1GxdSWDGJ9OZQcdF35kAsznaUxA3blC5YLV/WVAWRy86o5OX8gNRPgyoAXnoKsWbkMHCnc7sCFxE4Ag4aklVfnyvZdkCuz/P/AlVkuxJVZ07gyXMz/EWdmSOPMDGmcWV42cmYvf6av97W0cM9/ljEyp6bvp7zYiUrWo1Y5TZHORDXMdFs7KgagGM0SWJkdz9qEfh7hLle8ibYDSEVBjlXP6D2rFEMNlEqaNz6BKwK8H4oa1WoMUnlIrZa1dz58980JV8LdVUL3lhtDUKB7ShTX2Z2eRqOf/wTxEJxZ1MDcZUX/15/g6xbFtCrv730dbjW88ABQyx/guoNO0WNgd2S3nahRddFRdVE/PlbGS0hUajO3fU/YZkCjyV2pSpsU+H9d8wi9lNSrtT84imFqTD+oUxf0Jw9e3lB7Rwo4hPrxqK8VuhXPMV6Rh6QfYLOpQBuTD5X8QNIkJiFTjIvpt3SqPbET+m9AN06Yjzxm3a6YshX7Y+yOL1yvh+ayXNfS7VLwT/AbNQfyRZTvQKQ94VH8Bqb60H84/y4MDPEgzFRu7XZgAZz56K4KknJ6z/Z2JxsEAGysAAEQXHO2SwFPKJ995EeUynM1KKzyCwAUh2ub7vhhYJD7U8oM7JiHqv1zQFTLhY5CC+jpJSd+LHnd522HrYY0ADAjr5MmJK5xwOvnrwx8eXvQVu/Zhb24yLImj9rhr66u/mypU64Uz4/sHw2nYV93nJhu/Eej5Oft/8wQOujZdaSC3na6ZVyAvUVhktjnn/xHPTHVqARV6efTheKJOB6GUWj3cpK3IoQ9epgGwK8YDgX9EZ4sSBQcKmh3vY0uE1pGs46Ow1nGDmM76UAV8FmqhmFrAcNWC5hfG4U4tHE2vxqBomnrhEX11LE0pPnuTERTtejfzZhJgRMAWzRUYVU4r3/5hBBlTpJaVqyrNT/JVmZfV+3jZ4WvnF9nrrOOUktR/jmY/xDYolSOdOliHBRryWqVjK5QSYV8UAVlbiFgr3XW6YgpAUXZbYS1+ld3COdwRpkQF8w9lKpyGdTVDjxSkFZrtOOf1Tkokqw1OkW5PFEuU11dlCxXSOVKRDm3KFchyhnV1TV6OVsVlbtLlKsV5ZaIcpAeTMJronJhUa4ZPzYbSQONimapxZswbauR1GNxNFvgY7P2sdm4NVk0Wy1+URR9QS+6DT5eShbdkSw6Si3eK4ru0ovuh499yaLvkUWYnEUe5QCrw974mYhIbQWMB0iCmR4lH3ftBpdwSmc1b0gg2eHXxPAlsAn2ZGZXR2/jx0/pUU3JHEHH23COq3XR2uJRFIcFhfmz/5EhotXbC46TjtlsQ8EBuDLDdyPxoXzPAPdFx4lMZb6sWNEAPfn+jVxMe1NswZlIhyNywqCuwjmNLYir7k2xBYdV95bYAkCLL8YWcNW9LbagH1ia2IKTwMPEFvwztNP17sNXUQMmcXe9rvxfWCcrUhhEAIBDS+19fXzT1b1/nigBAolaMIzMZRpdt9TdzrJdWOpdgFKqFEzSNi2jPOyOuRqZVk2kaqnUb1sIp1/AwRQvCOrwXtx16iYyHDr7AC3lSUAdCU0QHc6DRVcUSxEhv8/nc77fPEDxeu99/X5//YCQfM/z0/eczznn83m/DcviGlilolWHB8QS5T4Jv7+8/wTb19QNO1NaVhZngSAEG44/I/G58x2oU9MhpDNHMCAkOVf9WQeSm9+ChyZDqRWtyIo+zSDt1MYrT6Ki4/lJWFvzIwiRJxqlfiiugnef0qh8LXMgXGoSj8LUUor/+eNDBnBh65PnfglNdcFgbnmWDKrEKYg8DVoKlQE0UQ2e15zQRvZE2yPFkaNtIHNWRqLu4+DgjsFWjhxiUfexyO5oR6SYC4djGGJ31H0SCajQ4XjU3SfSUELwqPs0pnFSTeNkFETYPRRMOPRF3V+iw2nV4bS56Vd4kPvX+37A9suFhw1OyAFkAWOyfKeVgJjU7qhGzXwgdBjN9UZAF8OG+sQIfHGOzI1HZscjHYPg57OpRlZskE5OkL3npC9GlVaYl5YSrORv3JLOIjTV0QhEKNfKlfb4klxFbbrnAKHBz5utwESTR+8hcdSg6DfHlzQKbTVL3F3H5pgEWWUdtDOmcMshAotMpbAmPWaLGpPS6G1jM0xor+jln75F1h6paAXaJNELprwkW9XxXmISZUVUF/4Q5WZTo7FiO/M4mLtaOmb3FtjZVJMvZOHNpzGQUQ3Ef/RhxrMSaSqh5tx6NqMc5FfN3A7Eu5hq4usyvedtQ6wE5UG+RfP5IzpLHrTx8QadxQK/rfDxwSesfNDvHuVb/VwBn9ZHBN4hIQtcbOTw9MeaSxQjZXAbTDFybjqa9t69XrkhG9EC5UcH0O5FnmT3yF6L3JCnI7v6BjKHD79NkHEWYZQ5KxOPFtWHKwIFnlI+6mNBrC4/JEDGPnuWhYzOEHKoOGcYWOcTeCMcnlLJ2uAXnjHgUxUufgjPiOeSxHvnFnDmqBsW5ShqjY7uUcHCs3D66NVF21FRTNDWaUOjmrrj0eDweAQFV9KeRjzP0ALXqcX/hOGPfhrtjpdWoy9E2q1yeA0/eio+uzo+pbr3FkJChx/uI3heU1qDsdKDjsSgNfEpNRCh9xoRmn5fmUx/djXFnV2Dk3R8ioEZnTOQkSE8fT5aCXgMznKD/J8EDLydVrLPw6ULeJyMKEwx0h2TXyZonO2rFP3OVpKWYRzGCL03vprY4qdqYqPiq8k6JEv1eEnxMMdX43oWJ2S86LE4bLjmRY/NBa858XWYXHR/fB1eeUGLrjtA3DHx1QQIu3qA/keNrfhqMixZTVYfq3Pw/3V59D/JC+u40Gdd10dPRvJBnfooj6+bcBHcGNo/wDxjirZG34uNxkoK7HkLbg4gwregANfg6hcb3Zf0zCbPT+LfUrkkRYDazACKZyqFb1YnA4wS8SED4SW0UbMd/IGTUNpvxQ0OHsJf11yyYZJOFsQ1pbHbC8rlFdhgpJIOs4oDh+XthUSE6SaK09jtJR5kEkEiXD51z4VEvChbqp+ggbgxZBAtskH4GLKIYpwiR6woD6KAw3jY34w3N/6QiD9U/UBdfo8yxh8cG490DaW1O9I1zSAYbVBGL+iIF+Wh7dvR3R4YWEfPxmZWx8uIyTUx+rVHUA8RqhODWVToFN4Q++YyahG8XMY8YEvnRkXGXR8RPiUenRl7b4COuSTc9RTuqbRwODmjITsUwYuqDVCAWNDhjs2sieNZ+sVFUBgFvnu5IkxNS/rEN7ElLluKb6QH/ZSaBQ33ofI+3PT8Txqg68TXa4CNJy5qANSOLqrxKA3wVTW/bN7Tv2be16WFY3eROrDzrvncBM56Hv4ndleV864F/Dy8jE4evtswh3XQEJGXEYLwEDcZufxLt2JZmRzk8cnV0kkHvByqduGD18Yn16hDb0yPVvBSXtMzyYDq4HMt0g5HB5s83zm5Uq8NGxxsclWPweGcvCB2b7VzElo2GMDVKz9CGXpRCSZ2b018cnbsXwuOfqSovU+2xf618OgJWuAn58UmO2L/WkKPdm7aBS/OZEFzGUMmlGvik/GtMUHuUEqRf8b7mYdov3WOEtdDpvrq/P6J9xnqs9kUu6sTFr8lTbD43ebhq/6OcBI2qTvhGujSI7pe+D5D+D5j+D5TeLolfJ+9Xse6XJ2XenVNyS7/XfnvIETXFNpJBUeGp9h6jaX8t4+dT+T3uy7QvV94uuPhYfmtqDq5I68j/2PXBVQqNK/4D3Glg5o9lt5h8gKHYNCbiJ5NyHswMegoC12Ld57MtBmWQLdrORnKzGaPqJbLj6ChDNSmGI8tiPSLNI74+50X8PyykLUjmxMvPZdINLWG9OEpjoBR0B/xjWvO491BSX5/U+tiYxJZGnVLduIOwfUPLJi55ZdJOAsqf8b5h7nhJAKZqzAcRweD4ehWYDiIMs76ARo6J7H5fj9YhLVJ3A6jl394nFTMkdYc4dG3CI1zZLakZQwaRUYLAJg5ffBQEtBEdwdgT+iYj3r1Vi+41fhJA7yOdOQFOhw4rFfNq3LAjawnBKkmDEKF2FNQevJteDS8w9qwA586tqFFkvI7hU/QovCdJmE9rB6ecxxBTCw=
*/