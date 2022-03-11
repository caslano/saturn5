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
            typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_
          , typename Extra = void_
        >
        struct vector_tie;
    }
    namespace result_of
    {
        template <typename T0>
        struct vector_tie< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ >
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
        struct vector_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ >
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
}}

/* vector_tie10.hpp
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
*/