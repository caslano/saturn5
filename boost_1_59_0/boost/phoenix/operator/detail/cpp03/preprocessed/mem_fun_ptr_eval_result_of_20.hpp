/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1>
        struct mem_fun_ptr_eval<Context, A0 , A1>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1;
            typedef
                typename boost::result_of<
                    child1(
                        child1
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19
                    )
                >::type
                type;
        };

/* mem_fun_ptr_eval_result_of_20.hpp
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
*/