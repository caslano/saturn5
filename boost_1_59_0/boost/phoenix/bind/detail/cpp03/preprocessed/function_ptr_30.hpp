/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<2, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1>
            RT operator()(A0 & a0 , A1 & a1) const
            {
                return fp(a0 , a1);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<3, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2) const
            {
                return fp(a0 , a1 , a2);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<4, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3) const
            {
                return fp(a0 , a1 , a2 , a3);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<5, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
            {
                return fp(a0 , a1 , a2 , a3 , a4);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<6, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<7, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<8, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<9, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<10, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<11, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<12, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<13, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<14, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<15, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<16, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<17, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<18, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<19, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<20, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<21, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<22, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<23, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<24, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<25, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<26, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<27, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<28, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<29, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28);
            }
            FP fp;
        };
    };
    
    
    
    
    
    
    
    template <typename Dummy>
    struct function_ptr_impl<30, Dummy>
    {
        template <typename RT, typename FP>
        struct impl
        {
            typedef RT result_type;
            impl(FP fp_)
                : fp(fp_) {}
            template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
            RT operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29) const
            {
                return fp(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29);
            }
            FP fp;
        };
    };

/* function_ptr_30.hpp
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
*/