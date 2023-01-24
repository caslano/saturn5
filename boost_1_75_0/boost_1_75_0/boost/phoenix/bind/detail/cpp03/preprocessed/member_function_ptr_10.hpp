/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<1>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0>
            RT operator()(Class& obj, A0 & a0) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0);
            }
            template <typename Class, typename A0>
            RT operator()(Class* obj, A0 & a0) const
            {
                return (obj->*fp)(a0);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<2>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1>
            RT operator()(Class& obj, A0 & a0 , A1 & a1) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1);
            }
            template <typename Class, typename A0 , typename A1>
            RT operator()(Class* obj, A0 & a0 , A1 & a1) const
            {
                return (obj->*fp)(a0 , a1);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<3>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2);
            }
            template <typename Class, typename A0 , typename A1 , typename A2>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2) const
            {
                return (obj->*fp)(a0 , a1 , a2);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<4>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<5>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<6>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<7>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<8>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<9>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<10>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
            FP fp;
        };
    };

/* member_function_ptr_10.hpp
r15Ix/DnIxFWpyHFTWM39KKow2oYl4kwPJ6d0yIPrqU0ZH0CZ+FI/mjewpO5Wt6iIYvH8haYrWrp+50EYydpRQipwDEDT7EZeUrCGR3TzuIwfCdAniwcgzw9o5FneZgih8X+moCxp4ZxEFsOYR2pS+DAJzwQo3DmaZHzTg71+SUzQALoMDICJRRlcTCPRn10VB896KNwbpIhT+4lPA33hpwY7o8nNDRTyAXlpcBQmoTmUXMq4biY0PT/H8N9UXrHIkyndXq7HOZIqYpyEYUzKeVqGl6gCjtUYauqNlcH1G9wjvMMmOor2sKzZciTJ0Zh+F9aBcZyDCoSAsMID9F+dGIWhnclohx3utLfB9Pr1bB/zsGE1fDBBKS/n4aeQQd6a8k/R+Ke/m9U/gv01BGf0eDIKh3Cz7QIhdH9ybQkBOvZm+dSfF6W/GTCfPeGYb5pYZjvJ0mSVhx5PFOCPGmJQc6Hsmipw8PJHmIih9KxV+JYlQIwjIwDGEOKKJxMYTmFNRQupHAZhTaACcRJw6dR2E3hOgo3AEyFVTVKvprCpwFaiJM7lJ5N1nGY79Ucct5IY0fxz+rzAS7JnghzkkPp0wBazVVkN4TnAVwxUg9wkjEG4D8AHgL6UghfGbuC1PCH0lvIR1TOHgr3UXiAwoX8uzBu1fD3ZLSTZcDpA8qpCWsAbjdBKYByFoT3xp5PnPzfx1wC4bPTN5FufgGs
*/