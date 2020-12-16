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

/* mem_fun_ptr_eval_result_of_10.hpp
gwXMVU+SmyYoAhqJWp8i0nlMpNPFowD+LjeM19Ta0h7fflK09JP2+xLbb4tvv023gpxopG19NyUJCGhaz1SQ8s4jlXf2Ur6LpuYunJqpGVtbk2LlQgkHHFVZhcKbMUp1ZVrYrJ0tIZBMfIMq2mgaNrXD9pAuC3QxVbtFVYu/4U5Vo6KqUVVpwDuyOjLQwed4V1JHnvyodORkL3UkHjpwQzQZm2MAOYt2Ujd4vJogiK41LjH3iofk/w7CzQACJKuJoI1ZBNOeqCkC+tp1cdyWlhq1bos+wSgz20c68yWvEjlo02vQpnc1EOJ+B7psagBOXs6TUOx6ylZV2YD1LRztn5NMgZN+IRSYODB5IDYAzyhGzBzYCyP2tzBCA6DeAyMRUHtvjLSipKHWoY3H2CXGcuaFqt+bvNAA9KERtc6O0vtt0Yp1GLlAJqGbrhPbVmzB7AGoJll3eCnR4vJkWkz8udBi+ABNiyyhxbro/H7pRc8RMT729MIOmdb+xKsmJbtVaGMUAKynZq0Hz3OUZ1ukZH1RyboFZ/pdNge6hlbyk9tE5jrNrGs3OLDjY4u4tzAr3g0A6awDX6mG3bHvQ7bJgMq7LnADx3HKe+LMOsClF86s67HsEQvSBFlHIxulkhElDgGnHpBfOV0KnURjmnTNwYkW04tG9rdpMb1oovNvB+/+uRBNBD+XyzTreWK4T3uGIUdYLkhaIXMFJnmfIHPLFcIIZG5Z8wgRHcutQLjhqkYBQ/jU4U/ejnZmsptTqUNMuMT6gy0V9r7MACWdTG2wCdr/B3thpYUCocihnrC+0YULCcxSSUOzw1wjr83sZWiOsQytjh7HZccRByViuXAilLfGPGi0yZQU22tOSR2QPfEmk1f7MHTi1ub0hFtJ3uUn23nr85TVz+Eq9nOovZKHS1dVVa76+DB03vfS7TjdLZun7NIqzlcmgs28TVmA515gfToqpBc1EKVK+mneVaSRRUgN4wHWzQ6YRxAPu8IEpgy9PkUkYukXLqYtAp9BgEQp1roWWOuoekfCctdCy10LVdQCxf/B3tXAV1lW8fu5XcYdu4M7mDB0ykgUFBQ0dFBIrMhYbcSMytIK7TapTO5F8ge6MWa7jiUWFBUVJSYl1SrSYdMGEkyjAly2bNWwqe+6q5atvMzpOud/3vO+790HA0P78u63c+/7vM/Hec7zdZ7znOec4dOeKCFo3U60RtdhKaObrE55HEY8u3RL04UluQtdfwOWyawek0fsoraA/yPr1bIek1PczoqT2+n2A9idgGk/9jbwf+nwm04bJNFabkt8EUOvBh14RrmMGH4iv+f1juSitvGQJI8Xt/AoaHGJw3JvWVtlb7eeYn8h3VqRw7oit9Deq25ZaJS5Kq9OH2Ea9ltzEDZtLXXL3MMzSG2UP9XGfyLehLN1ux1rc9twU2LbCafEE7bNquestvkklQzHOV0ys2wARb//nLaQNTzZ7gAaa/l3ldpE4L3HB3WsenSs1gGVrEcl61HJ+s4P47Zby7DsW8uJSMQ769XjxWKF1Qd2fAdYqalBmtcPoafcrBqPFfwYi5iz3GiZ5aqSPrTzp/0Dh+3s1GEbtUo/4eh2WdHQWdtknbiQvtRwVgWCqidxkEwj42UawRTUzpjvTSs8AqySvhGmXXvyBCWQevj1145xIuqCghxvuG6s70/Y/azaSBu1WYx2wc90teJFGwhRoeqMbLlXNCMHmaIMqynKz77LsuPlki1hWdNSU8P7pavpnVyiiszzD+K+7rtbuS82EjxwEm8iJsqcxCu8I0ziYxzUatIhMKgTN52YzE2ljLplyvsKB/JLBiP/568r8k/RBAzetEnorPolh8ENlJQ=
*/