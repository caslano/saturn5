/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct vector_n_chooser
    {
        typedef vector10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> type;
    };
    template <>
    struct vector_n_chooser<void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector0<> type;
    };
    template <typename T0>
    struct vector_n_chooser<
        T0
        , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector1<T0> type;
    };
    template <typename T0 , typename T1>
    struct vector_n_chooser<
        T0 , T1
        , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector2<T0 , T1> type;
    };
    template <typename T0 , typename T1 , typename T2>
    struct vector_n_chooser<
        T0 , T1 , T2
        , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector3<T0 , T1 , T2> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3
        , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector4<T0 , T1 , T2 , T3> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4
        , void_ , void_ , void_ , void_ , void_>
    {
        typedef vector5<T0 , T1 , T2 , T3 , T4> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5
        , void_ , void_ , void_ , void_>
    {
        typedef vector6<T0 , T1 , T2 , T3 , T4 , T5> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6
        , void_ , void_ , void_>
    {
        typedef vector7<T0 , T1 , T2 , T3 , T4 , T5 , T6> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7
        , void_ , void_>
    {
        typedef vector8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> type;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    struct vector_n_chooser<
        T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8
        , void_>
    {
        typedef vector9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> type;
    };
}}}

/* vector_chooser10.hpp
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
*/