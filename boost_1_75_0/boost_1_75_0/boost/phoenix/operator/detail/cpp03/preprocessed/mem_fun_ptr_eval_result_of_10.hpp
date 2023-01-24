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
/sLb6cyVylq4e+PDlq3t1JJ2/hOlbbJ2uJDA1lWj6Xvgj5uPFTyNcvK5/YHhs74rtwq5w+7UV/rUywnQtR6pXMgJyeHKiUvhxAEhDlDstkDtCYoHzLstV7P1S8AD1nhj3pKuVNJlaiIyXUVZo49GG9m8ZbZWo5AlbazxCRl6Y/UKufpXbUZyvJnRfWNeTHM0yt8lKznTydcZqDWtr22Ek0/XIov2GkxWx7CwIhgURlPLKDjSirZ4elenOISTvlC7j0n0nCqVo+Mg8n43pCR9T4t9p7BcZgjH28vQerclGtYQ+TuAtC4P+nb+Sr/vYbMhcmaEkD0/ENx8cxDzdXAjIIgi7mli+PczN92V43gDhUpdVt++aGD24MWw/SVTrj/4OWUDX7wr2CXgeTwyR8uyji6rk4DqHj/vROLgKrLv/mD61/Qv2c/boQes5Zp+tkv5u+VUUZD4yk1Xss2Ed7i+nO4L4CR+hkBtu2mdOkUjTv7o0lYOMj4Ldpsx7rGU7J1Yro/+OpFHNV8vHjOGaEBF9zxg8aPqCftsOx6vquqc0kg6erOWGcJjD8dVUSdMp1M0GbuB9p3lSf96mqs3CGLgX8euDk/ypEZM/e8ycuVYea59M+rRhxfxlnCYVOfriACcw15swMFqo5Ji/6ML8b4arr+zuIHDx4lnA+Vl/pMPtELKtxYdDpNV3TzipfQkSobFtXgfTSTPehAIPSp8
*/