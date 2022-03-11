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