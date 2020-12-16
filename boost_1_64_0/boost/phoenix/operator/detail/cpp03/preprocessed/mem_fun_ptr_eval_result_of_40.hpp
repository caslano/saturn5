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
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31; typedef typename evaluator::impl< A32 , Context , proto::empty_env >::result_type child32;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31 , child32
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31; typedef typename evaluator::impl< A32 , Context , proto::empty_env >::result_type child32; typedef typename evaluator::impl< A33 , Context , proto::empty_env >::result_type child33;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31 , child32 , child33
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31; typedef typename evaluator::impl< A32 , Context , proto::empty_env >::result_type child32; typedef typename evaluator::impl< A33 , Context , proto::empty_env >::result_type child33; typedef typename evaluator::impl< A34 , Context , proto::empty_env >::result_type child34;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31 , child32 , child33 , child34
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31; typedef typename evaluator::impl< A32 , Context , proto::empty_env >::result_type child32; typedef typename evaluator::impl< A33 , Context , proto::empty_env >::result_type child33; typedef typename evaluator::impl< A34 , Context , proto::empty_env >::result_type child34; typedef typename evaluator::impl< A35 , Context , proto::empty_env >::result_type child35;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31 , child32 , child33 , child34 , child35
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31; typedef typename evaluator::impl< A32 , Context , proto::empty_env >::result_type child32; typedef typename evaluator::impl< A33 , Context , proto::empty_env >::result_type child33; typedef typename evaluator::impl< A34 , Context , proto::empty_env >::result_type child34; typedef typename evaluator::impl< A35 , Context , proto::empty_env >::result_type child35; typedef typename evaluator::impl< A36 , Context , proto::empty_env >::result_type child36;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31 , child32 , child33 , child34 , child35 , child36
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31; typedef typename evaluator::impl< A32 , Context , proto::empty_env >::result_type child32; typedef typename evaluator::impl< A33 , Context , proto::empty_env >::result_type child33; typedef typename evaluator::impl< A34 , Context , proto::empty_env >::result_type child34; typedef typename evaluator::impl< A35 , Context , proto::empty_env >::result_type child35; typedef typename evaluator::impl< A36 , Context , proto::empty_env >::result_type child36; typedef typename evaluator::impl< A37 , Context , proto::empty_env >::result_type child37;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31 , child32 , child33 , child34 , child35 , child36 , child37
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31; typedef typename evaluator::impl< A32 , Context , proto::empty_env >::result_type child32; typedef typename evaluator::impl< A33 , Context , proto::empty_env >::result_type child33; typedef typename evaluator::impl< A34 , Context , proto::empty_env >::result_type child34; typedef typename evaluator::impl< A35 , Context , proto::empty_env >::result_type child35; typedef typename evaluator::impl< A36 , Context , proto::empty_env >::result_type child36; typedef typename evaluator::impl< A37 , Context , proto::empty_env >::result_type child37; typedef typename evaluator::impl< A38 , Context , proto::empty_env >::result_type child38;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31 , child32 , child33 , child34 , child35 , child36 , child37 , child38
                    )
                >::type
                type;
        };
    
    
    
    
    
    
    
        template <typename Context, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        struct mem_fun_ptr_eval<Context, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39>
        {
            typedef typename evaluator::impl< A0 , Context , proto::empty_env >::result_type child0; typedef typename evaluator::impl< A1 , Context , proto::empty_env >::result_type child1; typedef typename evaluator::impl< A2 , Context , proto::empty_env >::result_type child2; typedef typename evaluator::impl< A3 , Context , proto::empty_env >::result_type child3; typedef typename evaluator::impl< A4 , Context , proto::empty_env >::result_type child4; typedef typename evaluator::impl< A5 , Context , proto::empty_env >::result_type child5; typedef typename evaluator::impl< A6 , Context , proto::empty_env >::result_type child6; typedef typename evaluator::impl< A7 , Context , proto::empty_env >::result_type child7; typedef typename evaluator::impl< A8 , Context , proto::empty_env >::result_type child8; typedef typename evaluator::impl< A9 , Context , proto::empty_env >::result_type child9; typedef typename evaluator::impl< A10 , Context , proto::empty_env >::result_type child10; typedef typename evaluator::impl< A11 , Context , proto::empty_env >::result_type child11; typedef typename evaluator::impl< A12 , Context , proto::empty_env >::result_type child12; typedef typename evaluator::impl< A13 , Context , proto::empty_env >::result_type child13; typedef typename evaluator::impl< A14 , Context , proto::empty_env >::result_type child14; typedef typename evaluator::impl< A15 , Context , proto::empty_env >::result_type child15; typedef typename evaluator::impl< A16 , Context , proto::empty_env >::result_type child16; typedef typename evaluator::impl< A17 , Context , proto::empty_env >::result_type child17; typedef typename evaluator::impl< A18 , Context , proto::empty_env >::result_type child18; typedef typename evaluator::impl< A19 , Context , proto::empty_env >::result_type child19; typedef typename evaluator::impl< A20 , Context , proto::empty_env >::result_type child20; typedef typename evaluator::impl< A21 , Context , proto::empty_env >::result_type child21; typedef typename evaluator::impl< A22 , Context , proto::empty_env >::result_type child22; typedef typename evaluator::impl< A23 , Context , proto::empty_env >::result_type child23; typedef typename evaluator::impl< A24 , Context , proto::empty_env >::result_type child24; typedef typename evaluator::impl< A25 , Context , proto::empty_env >::result_type child25; typedef typename evaluator::impl< A26 , Context , proto::empty_env >::result_type child26; typedef typename evaluator::impl< A27 , Context , proto::empty_env >::result_type child27; typedef typename evaluator::impl< A28 , Context , proto::empty_env >::result_type child28; typedef typename evaluator::impl< A29 , Context , proto::empty_env >::result_type child29; typedef typename evaluator::impl< A30 , Context , proto::empty_env >::result_type child30; typedef typename evaluator::impl< A31 , Context , proto::empty_env >::result_type child31; typedef typename evaluator::impl< A32 , Context , proto::empty_env >::result_type child32; typedef typename evaluator::impl< A33 , Context , proto::empty_env >::result_type child33; typedef typename evaluator::impl< A34 , Context , proto::empty_env >::result_type child34; typedef typename evaluator::impl< A35 , Context , proto::empty_env >::result_type child35; typedef typename evaluator::impl< A36 , Context , proto::empty_env >::result_type child36; typedef typename evaluator::impl< A37 , Context , proto::empty_env >::result_type child37; typedef typename evaluator::impl< A38 , Context , proto::empty_env >::result_type child38; typedef typename evaluator::impl< A39 , Context , proto::empty_env >::result_type child39;
            typedef
                typename boost::result_of<
                    child1(
                        child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9 , child10 , child11 , child12 , child13 , child14 , child15 , child16 , child17 , child18 , child19 , child20 , child21 , child22 , child23 , child24 , child25 , child26 , child27 , child28 , child29 , child30 , child31 , child32 , child33 , child34 , child35 , child36 , child37 , child38 , child39
                    )
                >::type
                type;
        };

/* mem_fun_ptr_eval_result_of_40.hpp
HVzo4L85pMS4iBYkpv/AF8BsOWOmVkV6dJnv0Z5Phr7Wc2Gd3/aDyMHYB8jTrTTyt/c4aeMi3OBp8tIfaV0pmJ3oik8G7ryQ3Rs5Q1fuxxSz881SzOjYGvJQLMW8eY/VjuwM1zjQ5GzHuN9qktgbLWL4eQWwKywux5ci+bseVkMUrPR00G2WfgWX3uxD6RlZ1XehcXegOxpRC4Pz6op3lBqLFIPoGRzHmCPPs4/u4WH9/F+rj6Lqf/apk2NCTZtZFetsVFsYVeTb+JCiJr3ERO0bPkLtAkFtSuy92LbtwrC7EjXk03pB9D6MUZ/0/7c/KA/WgNtlDrjQwAKKuIBDXhSQmVVdhVuphySXNQ123csOLTUW/3hgXWMhvJiJF9osz3ktN6Gxi/j02MhS3Djy9/fIg5hPmOYc6Q1eQuaNgow/q/oij9l/VliTS9mDzn5XY5bUYOqT/5m+yH24RL0yZfi+j6JGGm7wy3ZrA7ZbrT9BDPgYX/mwek2bYWyicPj62KAHnvzDldplg5RhAlITjoYPMpqiGWXdTiMNp6OMkvGjBx1T0n6yf/uQk2YPeySqsZloLvfs6uhqjfHLh5Ry3cSnG+esd9rXFpsDmrK8wRQndkfHwbz0B24zecBO9n3HG0RH3fv2K3XyIGqcI5GdNTyf/SGwnwc6eROSfvh+J0kz6D1sEM/Sqqz+GEc1Dj9g1qErMp4pbmtWpwnFEau3UavWxVU7rxJVA91rlO6ioZ+NUu54QBXNMcI2ui36K7PQ6aMfprHKWEGKlnQsR1kBPXXr/JUL/SwUm52q1l2QshS1TKFYVgedwNPhVyjWgBsjUeG9Fk5Xe3fnUs5jYmfTLAPK4e2PZpp9HfjzrJS4im1w6mmbzutX6MQxl1pDRuLPfyS0Qit84n4dQH16XviJCyhruHNjlj/aeX6yvx88wBZrQs50NG1iKaQpb4FEwwCNCy1d06k4AZyOCRK+Gj0W/7vUzU72Tf539WngIl/7vPY5PR/aX8CjnvHL817oF1f1erXIuYewWGhVrInM195tuU7DjmDOqpQdwWJnWmXazRRshfVF3arEs/lWKxjzd/9QZ0t/52/Sxcql4ZNZurDosMkOXiyT7acDJjs/ZSYmYotHMd9/LMDrS4/k3L/b4tOPgs1MCsf/rB3+IIWzJIBWEXk3+ofK7OVKeFcp1qE33W/bnb4k3VxPhbM/HywGc/aw5C/3enrMO2x4twwSTfDxPcLHY8rSS6H3THeu7velo0kw+Y4HerYWXFqaebXwQsxJV6P8NF7kVqdwzR9GHu3I46gfaUZnVb+otjR4ybz4+7rQis67+7IyIypLt0nLc5ysfKPzxuTBimaX2S9Wa78YINOmffgnxBjTGisGi/2PIxTSd80Nlsk5DW8sUtmur1rcP4o34mKeiOowoDip04X12kgpnebdlEvnT30gw5TYWgd3OFe5Q7vpRuYFMwQp6l8lZh/UJkBP/JjE6vA7hhAa4q2CgT82x2LG+odK+S1NWaEpsyTl2KzqH+ihREQOKe7Wk7Qo6nNeZJdSG+SNgp248+P2Bjlqb5CvpypfH1/PB2RAoizyPU0MxujtN+qGPM4ZSblIn7ov6PUJ22RdOeQ4tPfZiuSdS6nrUr9nbiOreq7ko3wEB011p6g2HdICbIJ8gQrAIPx5F2aFrIebBo771cDBOqk4zMyb4lRX3E9j+NDAU4tDOLUQ31Ip9Tmf8or8MoWOTaDjWz4mPfoJfZd1P2VtvO7jNp2alE5Ng+l01EvVvb+snxA5JIg0gVAbPo/0cB7cL86DB+o+dWZ60ANCWdVn8mtxd/fgcq/Nb5u0+igFsTVB0Oul7+oYvxS873c=
*/