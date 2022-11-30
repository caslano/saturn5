/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct list_to_cons
    {
        typedef T0 head_type;
        typedef list_to_cons<
            T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9, void_>
        tail_list_to_cons;
        typedef typename tail_list_to_cons::type tail_type;
        typedef cons<head_type, tail_type> type;
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0)
    {
        return type(arg0
            );
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1));
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1 , arg2));
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1 , arg2 , arg3));
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1 , arg2 , arg3 , arg4));
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1 , arg2 , arg3 , arg4 , arg5));
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1 , arg2 , arg3 , arg4 , arg5 , arg6));
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7));
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8));
    }
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    static type
    call(typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
    {
        return type(arg0
            , tail_list_to_cons::call(arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9));
    }
    };
    template <>
    struct list_to_cons<void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef nil_ type;
    };
}}}

/* list_to_cons10.hpp
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
*/