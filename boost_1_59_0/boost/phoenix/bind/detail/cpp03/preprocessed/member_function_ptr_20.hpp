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
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<11>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<12>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<13>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<14>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<15>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<16>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<17>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<18>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<19>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <>
    struct member_function_ptr_impl<20>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
            RT operator()(Class& obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19) const
            {
                BOOST_PROTO_USE_GET_POINTER();
                typedef typename proto::detail::class_member_traits<FP>::class_type class_type;
                return (BOOST_PROTO_GET_POINTER(class_type, obj)->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19);
            }
            template <typename Class, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
            RT operator()(Class* obj, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19) const
            {
                return (obj->*fp)(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19);
            }
            FP fp;
        };
    };

/* member_function_ptr_20.hpp
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
*/