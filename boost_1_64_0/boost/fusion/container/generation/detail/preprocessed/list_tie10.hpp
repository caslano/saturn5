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
        struct list_tie;
    }
    namespace result_of
    {
        template <typename T0>
        struct list_tie< T0 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0&> type;
        };
    }
    template <typename T0>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0&>
    list_tie(T0 & arg0)
    {
        return list<T0&>(
            arg0);
    }
    namespace result_of
    {
        template <typename T0 , typename T1>
        struct list_tie< T0 , T1 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1&> type;
        };
    }
    template <typename T0 , typename T1>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1&>
    list_tie(T0 & arg0 , T1 & arg1)
    {
        return list<T0& , T1&>(
            arg0 , arg1);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2>
        struct list_tie< T0 , T1 , T2 , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2)
    {
        return list<T0& , T1& , T2&>(
            arg0 , arg1 , arg2);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3>
        struct list_tie< T0 , T1 , T2 , T3 , void_ , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3)
    {
        return list<T0& , T1& , T2& , T3&>(
            arg0 , arg1 , arg2 , arg3);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , void_ , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4)
    {
        return list<T0& , T1& , T2& , T3& , T4&>(
            arg0 , arg1 , arg2 , arg3 , arg4);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , void_ , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , void_ , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , void_ , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , void_ , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8);
    }
    namespace result_of
    {
        template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
        struct list_tie< T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , void_ >
        {
            typedef list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&> type;
        };
    }
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>
    list_tie(T0 & arg0 , T1 & arg1 , T2 & arg2 , T3 & arg3 , T4 & arg4 , T5 & arg5 , T6 & arg6 , T7 & arg7 , T8 & arg8 , T9 & arg9)
    {
        return list<T0& , T1& , T2& , T3& , T4& , T5& , T6& , T7& , T8& , T9&>(
            arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9);
    }
}}

/* list_tie10.hpp
flviBFxBvsM22vKdFp7kxfGhmoNEcw9lnub22NBeq+q1HfB9ZeJxneuPrLRMzg/q/Sv1IlTnXB6sbqNITJ8i8cg1saRd4lcfY6nnyPhEGfc8n7BSKafNqnJSjjEvrg84jpzKKkanrGJ1rstD7Pm0/BhJ+WnSL98Ptn8+I5uPnfZ93ybWRA31Y/gRhuNq8lRpzRMZUn405F6wmmuAIrkGUK5Dv33Rfs7IypZ0lPi51o2Nfs75DZTfdfvvYXpKfkq6dd1tOtcAZZprgBid3/swR53QvrcxNzE7V9pG9Muur6ru8bHUce1zCL4N04kzhLLMItMjX3BcBxTpXAeY3VwHxLm5Dohycx0wQ+KhTJzme4okPmXZIdeyrxPWKM8EvKTep0pF9fwcpq2ncajdbwmot99SddonzZr2yUid+hzmZp9EaOqzug2rVPLeXZ776UwIVPL+si3vtW2/c5RBpKYM1OmIIXJl6SnpCJV0FNnTUdu2NP10aM9Z+yQdyYQWhHjC46SjzJqObH7LaE9IyvQmfu3cY5GaNgLbefhIS8tvufM5tJm090kb4xOEJ5X984o6PckzsrKTq23fkHscl/QA6XFuPwpQ/fap02Nm8Lvt3T0tsSuWkJ6wrZb0zMjm8SEaKTx67snt75+6nUL/90/TrjDFcf+mKdcwzX1uiKYtIsZNW0SUti1CU0/8mlszMkJ+22II6yiHkldV5aBUFC/qiaYcVPmzbEZzbuNI1lyPLZE0rZB28eWE9aSpwWvqNEllMVXfHiZl6pKuEHt9SZ5hOz8B5yPX+lLRQq6VpL5MwGdIU7k6TdmO+lJQTXoKddIzW6e9pkinviQ42jSc64a0icbotJ0E67TZBOm02cg5Xt3OUm1bmHN9TNG01Ui7izyjVVzH/bM6+s8+Hb9ntPSfuXL/bJX+M1Tun/XSfxbL/bNV+s9iuX/2Sf8ZNvfPaOk/K+X+2S39Z6KO3zNd3j5bpf8Mlbtnutw/+1dvtPL5wM633//Z69/m5Rd/+sjErlH5VT+Ltc0k/bhYJs8YBSrt9HIgf8Tw9q74MUbgp9gPP8fxWIHX4wG8Bb/E+fgVrsdDuBkP45v4NR7Cb/AIfouBxPsdtsLvsRMewUH4A6bijzgVf8bF+Cs+g7/hZvwdrc+WSZ8qhuo8W5bjQ3yYi50wD23fK5Pvtdf53nWs1wivx9Y4y/496ceEHjrfK5D4ZmIXvFr1vSj5Xked790o8d2EbfFm+d5GH+k7lD5FM0HZL49LH/2PVL8W+BN2xZ8xAn/BfngUh+BvOBV/xxz8A2/Gv3AemohviQKuxjr4BPriVvTDN7Aufoqn4Rd4Ov6BZyDfMdXDengWtsf6GIJnYzdsgIOxIQ7FxjgGm+BEDMREbIo52AwLsDkuxxa4Alvhk9gG38QgfAvb4iFsh3Uoq/bohx3wHOyIrbATdsMQjMCuGIehmITdMB27Yz72wEIMwznYExdiOD6AvXA1RuAaPE+1/6Qfkv5J1/13Aeu1wAuxK/bBCOyLo7Af3oL9cR5G4XKMxhIcgJtwoOynQbgHB+P7OAQ/x4vxMMZgJV4i+2koNsRhGILDZT+NwD54KY7Cy3AcxmImjsQcHIVzcDTOxzH4KI6V/XM5bsNxsn/i8Eu8Ar/G8WiiTCZgG7wS+2A8DsUEHIOJmIxJmInJeDem4DKcjCtxCpZgKm7CNNyKU3EXTsOPMR0PYwb+hJn4F2ahj7KfZP8VmKSvEq+R47Yepque7WyO92AnXIzn4RLsiw/gQFyOl+IjOA5X4hW4GhPwUZyKazEf15mk/hCkn5G6aY2/sVJ/JP4PpP58hOfjxxiD5ZiIn2IefoY3YQWuxQP4FH4=
*/