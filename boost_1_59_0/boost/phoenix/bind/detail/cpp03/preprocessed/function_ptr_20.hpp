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

/* function_ptr_20.hpp
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
*/