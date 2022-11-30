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

/* function_ptr_10.hpp
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
*/