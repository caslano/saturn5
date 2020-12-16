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
3XL26u1K3z5VOaCV9O1zJVTi5spRb7vhCWFhsq9Od9mmq3pfVXUCjQzxCCf9pfxpeo43Oio2TBu30zpxK0vc4vXiFmNIlBLHrWHh88X3GLfCvOIp9UQCfyO+3OTushy3gNC42BLlFfV2TsgGKhMqSLvtLLaTZ3k7hu6vJdlOFU2fRWNOrsY8e9N+x0TFGmZrx4XytNXf9/y7xCkqKJqVhd41Xuo8kKWzrX2cFwV620pODAstwX6r1+9b+I4GyWP9JY/ZtNdZ/zjDvpS4XsU8j3nr5DFfdR6TeY6mcychjL+Z6jbyidAIgn2pgs59HZKdZmbsqNFhZoX823R8u+OizK+1e0LGrYZ+H76U0nPz9O1vH7Fc51HHVZm/PvN1r2m2ZW53DmmzIfabNlw13Qx1J7fO7im/ZNKU2d2/uBEUNbSxMiCMYf6VDMdlzffF3ppydc0HU9fUowPS74b4xOfFTP+54KlDx+d2cXA577Hzr69TWWhY//Dt49fYn6y2tufUi8Oib/pl/vV1LRGGdOvWJ6TWeb/rLhXiHfInt7q503KdU+PBhu0eG3+m5rUvvqq3ZPKAvzVzqUq9i2G7x8YfP3Tn51nXx75Sr/o7GUM55lcN1zn5zZHfA6VPYhlsRGAy9OMqi3vQTp6pL/ye/R98L0u+t1G+96bqe47yvVY633tZ+rsuQ1dcofpe/B98L0a+N0G+N0n1PblOsrzZ96SuSTEQS2OQ6nt58r3KOt/rxHIVsB9Wwv6q7+X/wfZCZXuRsr0Rqu8VWPwen+V7OfK99+R73jZy/QA/+V457CDfmyLpMhVbYRp2xBelTmQ69pd+h2uUZ8CblbY5QrhFcHWm3wthPmEX4SYhnfnq+oPrBHvqDhwJ7gRvQjQhlTCfkE3YZVbH4CT1DCmEdMI6wlbCQUK+1D9UfYblCAMIoYQkwkGpk3CgLsKF0IHgT4gmqOspThCuEG4RKrdgPYQBhAmEDMI+wgnCBcJ1gq0b2yMU1mskEdIIWYRswj7CCYJNS5YjNCJ0IExQ1X/kEfIJ1wnl3Y31IR0I0YTZZnUj9q1IL4IrIZAQT0glzCa4UGcygDCBkEXYR7hCqBrKe/4IkaHWOhXrZJ2sk3V6KOX/0OCIB1X+f7cBdf1SFnCQMvjjsg/2hMfouJzfVl0WUCLA41nRdy9nSPmqsCxFx4Wie3nP0pbvAfXvkS3f804qo8xfOfCA7SPTf3urQc7JBk6v9Xz23u9t/11lAv17Z8tlAv17cMtlhSOllfmdHMNuTPSPcC4zOqLShH+EHadtzDD/1JzzhzqHRWVOuTYueEuD9WUtlyH0y1KWyxb9Dff+bUZnvjF5yKWBH679cITPjIzqlstwJyso8/dXfiI3wN1977NlnduOqtu1tsWynZQVJH9Kvs1X36NKX25bTEF7zDU+Q3LX+8k1qnvKJLmvPP2Q7y2zVfeXt/7EPWao6j5z0x/caza6j/vNQLnnzCjBfaePhXvPm2b3n54696AZ1ntM62SdrJN1sk7WyTpZJ+v0Hzr95eX/kOiEB1H+r2VT+fFdyvvYI5QyEyvm3TsBxmHaDHUDWwrrBlTPoLeQ98q4EN52ok3FWPbq69u1T//+PsQsLCg2MezPtZGb+llLP+jDUr4jrqp+zpbK939929u9trHpl5st1UNYrg+YYihPO96aHOh1rZpzzRHv1Exu8b1bYTlYjoUcowIbVTlY+qNWl2fXXbAmRuOmUDuzvpcYalfi/pcl7Xt51lp+s07WyTpZJ+tknayTdbJO1sk6/Q9OtoTgv7D8/yDK/nUp+yexjq2Gsr/Sr3dMQEhyYlIcC1J8N9QNlKMf8C7D3ws7McfER8vfKvA=
*/