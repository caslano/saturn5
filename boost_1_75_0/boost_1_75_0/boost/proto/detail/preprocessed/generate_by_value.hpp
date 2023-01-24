    ///////////////////////////////////////////////////////////////////////////////
    /// \file generate_by_value.hpp
    /// Contains definition of by_value_generator_\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Tag , typename Arg0 >
    struct by_value_generator_<
        proto::expr<Tag, list1<Arg0>, 1>
    >
    {
        typedef
            list1<Arg0>
        src_args;
        typedef
            list1<
                typename uncvref<Arg0 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 1> src_type;
        typedef proto::expr<Tag, dst_args, 1> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list1<Arg0>, 1>
    >
    {
        typedef
            list1<Arg0>
        src_args;
        typedef
            list1<
                typename uncvref<Arg0 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 1> src_type;
        typedef proto::basic_expr<Tag, dst_args, 1> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 >
    struct by_value_generator_<
        proto::expr<Tag, list2<Arg0 , Arg1>, 2>
    >
    {
        typedef
            list2<Arg0 , Arg1>
        src_args;
        typedef
            list2<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 2> src_type;
        typedef proto::expr<Tag, dst_args, 2> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list2<Arg0 , Arg1>, 2>
    >
    {
        typedef
            list2<Arg0 , Arg1>
        src_args;
        typedef
            list2<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 2> src_type;
        typedef proto::basic_expr<Tag, dst_args, 2> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 >
    struct by_value_generator_<
        proto::expr<Tag, list3<Arg0 , Arg1 , Arg2>, 3>
    >
    {
        typedef
            list3<Arg0 , Arg1 , Arg2>
        src_args;
        typedef
            list3<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 3> src_type;
        typedef proto::expr<Tag, dst_args, 3> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list3<Arg0 , Arg1 , Arg2>, 3>
    >
    {
        typedef
            list3<Arg0 , Arg1 , Arg2>
        src_args;
        typedef
            list3<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 3> src_type;
        typedef proto::basic_expr<Tag, dst_args, 3> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 >
    struct by_value_generator_<
        proto::expr<Tag, list4<Arg0 , Arg1 , Arg2 , Arg3>, 4>
    >
    {
        typedef
            list4<Arg0 , Arg1 , Arg2 , Arg3>
        src_args;
        typedef
            list4<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 4> src_type;
        typedef proto::expr<Tag, dst_args, 4> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list4<Arg0 , Arg1 , Arg2 , Arg3>, 4>
    >
    {
        typedef
            list4<Arg0 , Arg1 , Arg2 , Arg3>
        src_args;
        typedef
            list4<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 4> src_type;
        typedef proto::basic_expr<Tag, dst_args, 4> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 >
    struct by_value_generator_<
        proto::expr<Tag, list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>, 5>
    >
    {
        typedef
            list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>
        src_args;
        typedef
            list5<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 5> src_type;
        typedef proto::expr<Tag, dst_args, 5> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>, 5>
    >
    {
        typedef
            list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>
        src_args;
        typedef
            list5<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 5> src_type;
        typedef proto::basic_expr<Tag, dst_args, 5> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 >
    struct by_value_generator_<
        proto::expr<Tag, list6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>, 6>
    >
    {
        typedef
            list6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>
        src_args;
        typedef
            list6<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 6> src_type;
        typedef proto::expr<Tag, dst_args, 6> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>, 6>
    >
    {
        typedef
            list6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>
        src_args;
        typedef
            list6<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 6> src_type;
        typedef proto::basic_expr<Tag, dst_args, 6> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 >
    struct by_value_generator_<
        proto::expr<Tag, list7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>, 7>
    >
    {
        typedef
            list7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>
        src_args;
        typedef
            list7<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type , typename uncvref<Arg6 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 7> src_type;
        typedef proto::expr<Tag, dst_args, 7> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5 , e.child6
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>, 7>
    >
    {
        typedef
            list7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>
        src_args;
        typedef
            list7<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type , typename uncvref<Arg6 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 7> src_type;
        typedef proto::basic_expr<Tag, dst_args, 7> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5 , e.child6
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 >
    struct by_value_generator_<
        proto::expr<Tag, list8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>, 8>
    >
    {
        typedef
            list8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>
        src_args;
        typedef
            list8<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type , typename uncvref<Arg6 >::type , typename uncvref<Arg7 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 8> src_type;
        typedef proto::expr<Tag, dst_args, 8> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5 , e.child6 , e.child7
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>, 8>
    >
    {
        typedef
            list8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>
        src_args;
        typedef
            list8<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type , typename uncvref<Arg6 >::type , typename uncvref<Arg7 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 8> src_type;
        typedef proto::basic_expr<Tag, dst_args, 8> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5 , e.child6 , e.child7
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 >
    struct by_value_generator_<
        proto::expr<Tag, list9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8>, 9>
    >
    {
        typedef
            list9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8>
        src_args;
        typedef
            list9<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type , typename uncvref<Arg6 >::type , typename uncvref<Arg7 >::type , typename uncvref<Arg8 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 9> src_type;
        typedef proto::expr<Tag, dst_args, 9> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5 , e.child6 , e.child7 , e.child8
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8>, 9>
    >
    {
        typedef
            list9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8>
        src_args;
        typedef
            list9<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type , typename uncvref<Arg6 >::type , typename uncvref<Arg7 >::type , typename uncvref<Arg8 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 9> src_type;
        typedef proto::basic_expr<Tag, dst_args, 9> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5 , e.child6 , e.child7 , e.child8
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 >
    struct by_value_generator_<
        proto::expr<Tag, list10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9>, 10>
    >
    {
        typedef
            list10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9>
        src_args;
        typedef
            list10<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type , typename uncvref<Arg6 >::type , typename uncvref<Arg7 >::type , typename uncvref<Arg8 >::type , typename uncvref<Arg9 >::type
            >
        dst_args;
        typedef proto::expr<Tag, src_args, 10> src_type;
        typedef proto::expr<Tag, dst_args, 10> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5 , e.child6 , e.child7 , e.child8 , e.child9
            };
            return that;
        }
    };
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9 >
    struct by_value_generator_<
        proto::basic_expr<Tag, list10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9>, 10>
    >
    {
        typedef
            list10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9>
        src_args;
        typedef
            list10<
                typename uncvref<Arg0 >::type , typename uncvref<Arg1 >::type , typename uncvref<Arg2 >::type , typename uncvref<Arg3 >::type , typename uncvref<Arg4 >::type , typename uncvref<Arg5 >::type , typename uncvref<Arg6 >::type , typename uncvref<Arg7 >::type , typename uncvref<Arg8 >::type , typename uncvref<Arg9 >::type
            >
        dst_args;
        typedef proto::basic_expr<Tag, src_args, 10> src_type;
        typedef proto::basic_expr<Tag, dst_args, 10> type;
        BOOST_FORCEINLINE
        static type const call(src_type const &e)
        {
            type that = {
                e.child0 , e.child1 , e.child2 , e.child3 , e.child4 , e.child5 , e.child6 , e.child7 , e.child8 , e.child9
            };
            return that;
        }
    };

/* generate_by_value.hpp
WspzRYDkdeFBqItwUvlw5MOwloy8EO4wWZac8q7PGtqy25HlkZbBsYNC8iafEE3zCEcwtoBbcuRHNvFo5gZk20FiTx97ohXfyVgiT4XdNX8aE1ZHuiINVsu4+Nz9gI0/6N3PUSIK34jSnDlutXkN8/3KKUI9zpe/zAqar8M9QjHi0590y81drV9jtMUw/rSvHONmMDLmmwC9eRhWeB66w+22od75EKFCF/a9i3yxdc6cdRR8PyCCCPEolLWXWGKnMlCo3l1QWuxi/dsigKr0vqeGLtHmUQ1zoftQYsjuFJEHd3HbsmJxpNR3S4qqPmwgS1WJsp68/ZFMtkvzjnBriJcFDbYGPXgEpkGp81DkEfvWLlJlZv09/kFgaOTDZOTSiwjU5PTNgdTpS03kDCj1i/CLOa636owmtA3qD5V/oKq0ziOsvT6QlnqSxr255ocZ/jm0sgiVagvpe9UHtgeO5y8reqGDLp2+fS6mZpxAS0bgztc1Sca4tjKL0viy9N16RlZ4YvTOQoVPpXK/JS5B/G3F/Xl69I4RwaDIr+0OOu12mDzBhcjk7r0w0Kei/2vYV23zjBM771lorYloiYNGuXlmRFp7+vkQFRszvNvdsYS/VsKwqmqW19ahQdmgoykxp3jckePOJKQziP9SdCX8t/hCfuO0l1PskyONvdJZ4EK5SGWjA8FSwYRtaYOh7c8+MFj3ZIZV5dHz94y+
*/