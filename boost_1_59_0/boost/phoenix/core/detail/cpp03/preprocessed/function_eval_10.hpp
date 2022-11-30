/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
        
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0
              , typename Context
            >
            struct result<This(F, A0, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0;
                typedef typename
                    boost::result_of<fn(a0)>::type
                    type;
                
            };
            template <typename F, typename A0, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)));
            }
            template <typename F, typename A0, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1
              , typename Context
            >
            struct result<This(F, A0 , A1, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1;
                typedef typename
                    boost::result_of<fn(a0 , a1)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)));
            }
            template <typename F, typename A0 , typename A1, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)));
            }

/* function_eval_10.hpp
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
*/