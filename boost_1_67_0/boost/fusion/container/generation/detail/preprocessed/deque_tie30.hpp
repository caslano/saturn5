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
        struct deque_tie;
    }
    namespace result_of
    {
        template <typename T0>
        struct deque_tie< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0&> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0&>
    deque_tie(T0 & arg0)
    {
        return deque<T0&>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct deque_tie< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1&> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1&>
    deque_tie(T0 & arg0 , T1 & arg1)
    {
        return deque<T0& , T1&>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct deque_tie< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2)
    {
        return deque<T0& , T1& , T2&>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct deque_tie< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3)
    {
        return deque<T0& , T1& , T2& , T3&>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4)
    {
        return deque<T0& , T1& , T2& , T3& , T4&>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , void_ , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25 , T26 & arg26)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , void_ , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25 , T26 & arg26 , T27 & arg27)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , void_ , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25 , T26 & arg26 , T27 & arg27 , T28 & arg28)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27 , arg28);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29>
        struct deque_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , void_ >
        {
            typedef deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28& , T29&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28& , T29&>
    deque_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9 , T10 & arg10 , T11 & arg11 , T12 & arg12 , T13 & arg13 , T14 & arg14 , T15 & arg15 , T16 & arg16 , T17 & arg17 , T18 & arg18 , T19 & arg19 , T20 & arg20 , T21 & arg21 , T22 & arg22 , T23 & arg23 , T24 & arg24 , T25 & arg25 , T26 & arg26 , T27 & arg27 , T28 & arg28 , T29 & arg29)
    {
        return deque<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9& , T10& , T11& , T12& , T13& , T14& , T15& , T16& , T17& , T18& , T19& , T20& , T21& , T22& , T23& , T24& , T25& , T26& , T27& , T28& , T29&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19 , arg20 , arg21 , arg22 , arg23 , arg24 , arg25 , arg26 , arg27 , arg28 , arg29);
    }
}}

/* deque_tie30.hpp
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
*/