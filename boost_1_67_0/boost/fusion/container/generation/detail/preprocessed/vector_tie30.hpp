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
            typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_ , typename T10 = void_ , typename T11 = void_ , typename T12 = void_ , typename T13 = void_ , typename T14 = void_ , typename T15 = void_ , typename T16 = void_ , typename T17 = void_ , typename T18 = void_ , typename T19 = void_ , typename T20 = void_ , typename T21 = void_ , typename T22 = void_ , typename T23 = void_ , typename T24 = void_ , typename T25 = void_ , typename T26 = void_ , typename T27 = void_ , typename T28 = void_ , typename T29 = void_
          , typename Extra = void_
        >
        struct vector_tie;
    }
    namespace result_of
    {
        template <typename T0>
        struct vector_tie< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , void_ , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25 , T26 & arg26)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , void_ , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25 , T26 & arg26 , T27 & arg27)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , void_ , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25 , T26 & arg26 , T27 & arg27 , T28 & arg28)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27 , arg28);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29>
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , void_ >
        {
            typedef vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28& , T29&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28& , T29&>
    vector_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25 , T26 & arg26 , T27 & arg27 , T28 & arg28 , T29 & arg29)
    {
        return vector<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28& , T29&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27 , arg28 , arg29);
    }
}}

/* vector_tie30.hpp
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
*/