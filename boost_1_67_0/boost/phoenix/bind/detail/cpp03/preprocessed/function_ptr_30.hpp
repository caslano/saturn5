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