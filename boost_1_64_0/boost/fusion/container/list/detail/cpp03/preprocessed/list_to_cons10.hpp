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
b/g+yub8Bxef/Byb3vD9k83YBvJnPzVGPl/yccp5LeA30/o+bBnwsCAftldfM33YbPVJCKyNLz+gO+QHlPCmWR+rq3KL+69txrYDg3yVsyy+yvKTssVG0HrUyjPaVt9O8l0/V9fvTF2/1NfN+lr99VrcP83wYUrkmtQgj/J59OuN+zwZxydxrrPZ1uWNxn2eAm1RpbY4WG3RT21R9LbZFhY37pb31TPK2k1lHaeh6tGaF3CS5gUkV9WXlWkBjfrfBa1V3qT5ANa2zNCN5nv5Ca6WP26ZWT6r32PrxNRICfJ7TLX6PQbNw+ggv/lTVJ8x8nsseTlQn9b3eTwsTJ9H05ezvXP8jOpXzDrxe9B6927ju5xAu69ErvaRXm08foZxfCL1Mspx86te/AzP37F5/R0f8Ps1ph83/bsz9996+Xs5z7ffqe3Ym6L3a0xY4h6X4nn5jT0L4/TZ9MMLke9l5XtR+fisfEiU58sMke815XtF+V6z+uFFeb6cKPKV+PTcqefRlCD/i+Plf3GC/GtOlH/NSbAI5sjPY5T8a0bDZXAsXA3HwV/hePm9nCz/m1PgNrAAjoVFsACeqnKV+/T8qOdKyuVfm6pU5bpG5ZoF94TXwd5wjuIq3wDHwRvhbDgX4oNGfsoLb5Hfx23y+7gdHgbnwTx4BzwX3gmvhHfBubAclsF74B3wXrMd9fwHz3Vox6kq72nyYzldcaCnwVvg2XABPAc+D6fDD+C5cBUs1vr958Ff4PlaN/8Ctd/FcCq8RPW71PQb1LOYntFSgvwG71e5KlSuB+BV8BF4B3wUPgkXwtfgY7AaPg4/hE/In/Bp+RM+Y64fr+cqODp4/Xj5DSXDL2F3WCO/nlUwC66GR8Ov4XD4HTwJ1lr8nMqk/3uHuDC9Va/9FBdmf/kd9VO/PEB6sn16HoGnSE8c7C89b0pPtfyc3pKf0zvwcPkH58IVcAz81OwPeiaAGUH9IdgPK1V+WP3gIfACeBi8Gh4Ob4UD4QPwCPgsHARfkn/UG/KPWi7/qGTOd4z8oI6F6XCoZd39echS/DZqkfg/4hr4NCWzLQMJ+DZl83/8myLyX2ou36W/22+ppX2WvDgzzn5K4+hjM5AyZBGyFFmDJPwZ50tFspEipAQpR6qQlX96vkde8pKXvOQlL3nJS17yUnOkWOS0v9f+P3pcLv/SUkcWTSw4o3t6as86b4Dm8QdI9fsDBE7BOHxg+whjXKzBqf12+xcsdvsjXOzrRS+btt+AkrBsv/2kt8JFb7FFb3DhwrWz95ONIl5260/jqC9cDA0bRe1D/nM00C9rRVBsBuf4NUV18WuaMU5DQX5hvc1Z24rYyDau2bmM+870X8sz8ydNrLdj7NfFb1czThwUf2NS/gTZQR6OqYsJuAF5fCF1t9hbyv3lmZI/oYhjZUfa369zPFa2wrzxuYWmveMgtev1atcjtU7+Ycgiw/bzlFu7FuTnFk4tako8qGRbXe3XuVR292Fc331Ew56Z+bRzeRT0LKzrPE3XeTOugd/e9WKg/TbaYuu6/3c+4si0Xj5tW/ucuS0tsK3U3Na9d2Bbr/ptPQPbjq80t6UHtu1av43Lje2Rbbc8E9i2r//zfU8HPvdw748OdtkyB7tsuc0u69jP/H2qtC3tS7sbx9zlL0+wDS9v8hR9H3W8Pwbg5sa44vP1x48L6oO6/vru5ObmWb4TUy3fk+A+OU/29ydQ3B3eBQ0ba+UDzn3AtLiqH2Q30g8y1Q9c7ZSW7zZaZadsaH+d5mR/dWjfMtqqrF3d3OLJD9a3V0pQewX7IVRrKKiM9t4ZzoV+n4wFlnZogfU3irRtpsP9LRP26SJbtezpqeb1LbQ=
*/