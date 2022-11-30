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
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A31 , Context ) >::type >::type >::type a31;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A31 , Context ) >::type >::type >::type a31; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A32 , Context ) >::type >::type >::type a32;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A31 , Context ) >::type >::type >::type a31; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A32 , Context ) >::type >::type >::type a32; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A33 , Context ) >::type >::type >::type a33;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A31 , Context ) >::type >::type >::type a31; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A32 , Context ) >::type >::type >::type a32; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A33 , Context ) >::type >::type >::type a33; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A34 , Context ) >::type >::type >::type a34;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A31 , Context ) >::type >::type >::type a31; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A32 , Context ) >::type >::type >::type a32; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A33 , Context ) >::type >::type >::type a33; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A34 , Context ) >::type >::type >::type a34; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A35 , Context ) >::type >::type >::type a35;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a35, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a35, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A31 , Context ) >::type >::type >::type a31; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A32 , Context ) >::type >::type >::type a32; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A33 , Context ) >::type >::type >::type a33; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A34 , Context ) >::type >::type >::type a34; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A35 , Context ) >::type >::type >::type a35; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A36 , Context ) >::type >::type >::type a36;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a35, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a36, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a35, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a36, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A31 , Context ) >::type >::type >::type a31; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A32 , Context ) >::type >::type >::type a32; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A33 , Context ) >::type >::type >::type a33; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A34 , Context ) >::type >::type >::type a34; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A35 , Context ) >::type >::type >::type a35; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A36 , Context ) >::type >::type >::type a36; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A37 , Context ) >::type >::type >::type a37;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a35, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a36, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a37, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a35, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a36, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a37, ctx)));
            }
    
    
    
    
    
    
    
            template <
                typename This
              , typename F
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38
              , typename Context
            >
            struct result<This(F, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38, Context)>
            {
                typedef typename
                    remove_reference<
                        typename boost::result_of<evaluator(F, Context)>::type
                    >::type
                    fn;
                typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A0 , Context ) >::type >::type >::type a0; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A1 , Context ) >::type >::type >::type a1; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A2 , Context ) >::type >::type >::type a2; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A3 , Context ) >::type >::type >::type a3; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A4 , Context ) >::type >::type >::type a4; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A5 , Context ) >::type >::type >::type a5; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A6 , Context ) >::type >::type >::type a6; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A7 , Context ) >::type >::type >::type a7; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A8 , Context ) >::type >::type >::type a8; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A9 , Context ) >::type >::type >::type a9; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A10 , Context ) >::type >::type >::type a10; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A11 , Context ) >::type >::type >::type a11; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A12 , Context ) >::type >::type >::type a12; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A13 , Context ) >::type >::type >::type a13; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A14 , Context ) >::type >::type >::type a14; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A15 , Context ) >::type >::type >::type a15; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A16 , Context ) >::type >::type >::type a16; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A17 , Context ) >::type >::type >::type a17; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A18 , Context ) >::type >::type >::type a18; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A19 , Context ) >::type >::type >::type a19; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A20 , Context ) >::type >::type >::type a20; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A21 , Context ) >::type >::type >::type a21; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A22 , Context ) >::type >::type >::type a22; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A23 , Context ) >::type >::type >::type a23; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A24 , Context ) >::type >::type >::type a24; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A25 , Context ) >::type >::type >::type a25; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A26 , Context ) >::type >::type >::type a26; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A27 , Context ) >::type >::type >::type a27; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A28 , Context ) >::type >::type >::type a28; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A29 , Context ) >::type >::type >::type a29; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A30 , Context ) >::type >::type >::type a30; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A31 , Context ) >::type >::type >::type a31; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A32 , Context ) >::type >::type >::type a32; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A33 , Context ) >::type >::type >::type a33; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A34 , Context ) >::type >::type >::type a34; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A35 , Context ) >::type >::type >::type a35; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A36 , Context ) >::type >::type >::type a36; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A37 , Context ) >::type >::type >::type a37; typedef typename boost::add_reference< typename boost::add_const< typename boost::result_of< boost::phoenix::evaluator( A38 , Context ) >::type >::type >::type a38;
                typedef typename
                    boost::result_of<fn(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38)>::type
                    type;
                
            };
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38, typename Context>
            typename result<
                function_eval(
                    F const &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 &
                  , Context const &
                )
            >::type
            operator()(F const & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37 , A38 & a38, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a35, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a36, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a37, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a38, ctx)));
            }
            template <typename F, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38, typename Context>
            typename result<
                function_eval(
                    F &
                  , A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 &
                  , Context const &
                )
            >::type
            operator()(F & f, A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37 , A38 & a38, Context const & ctx) const
            {
                return boost::phoenix::eval(f, ctx)(help_rvalue_deduction(boost::phoenix::eval(a0, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a1, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a2, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a3, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a4, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a5, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a6, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a7, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a8, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a9, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a10, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a11, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a12, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a13, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a14, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a15, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a16, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a17, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a18, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a19, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a20, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a21, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a22, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a23, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a24, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a25, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a26, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a27, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a28, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a29, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a30, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a31, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a32, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a33, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a34, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a35, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a36, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a37, ctx)) , help_rvalue_deduction(boost::phoenix::eval(a38, ctx)));
            }

/* function_eval_40.hpp
YdgrMF1leDrpX5/7cYp3OT4CsnqUGCzaLwJexcdVEgBFr8v9wPYg7TQ+KB28V/96s41iI6Sbfd9s5OHGb57tPT2D2oZ5BVVxj5ZUmfVbk8LmaZ4JbXdYyzYR9BHiKzAzsOflBdkKk9aQ+v/IoP7/MBrLo0XkxbsPcFEZqdQ4zBe2ymxzAe1P7EHmEMTw7jFDOPIfBosC+b2vDzCE0IiB+UO3I5GIsXO3Oqq4uUWxlu6fjmCa183qs8XeAAaiGlyLRjwOde1tyaNAlGJWrepPkCG2nceDRF3BnQ+NUBGJuUzg5go4jmzudv6ayffu+oqDiAXPrO5jS739hg1K08eNvJbsPb28Ybc/h4ipn/DOgOOjGFxr/ME1HBoeTz2QKfjBZNT+YfhrDf0aBtxrmgLEVvVasLty5Dg8M/8b6CeorD0OG+jwdDu2mrkO4l1jXIt3p9K8Mg727DsbveVKsZNJhlXfUjw7x7GutfofgfaDA/M/H7f/rNYlHvDdkIgQ6qz3aNV9BfqknYgwgT69mYmqLO/yfVIM8Sqbaiu4zUokEe7jQcBXZoyz3XXWX01azaK8aJqzn9LMQs7v/lydKP/uGU93Pa+Ylo9aRHV69cL00AjWVXJtUqin/wxmqIf9SRGZ0GoJiM6hM3ypt6J+qVyNR2+s13yX3iaf4M7mnVhaGI4Krczn2QwNUaIZINjv8juFEgtB8SFITjniikJ51gnDXjZHevm8JUvhvvL820OQK/J6nWLbZggIerSjyAZX5/eiEj15/QVLFG3Xl67tWFnSJXc6f8qXgXBsn9Rnr++uxQu9v3TzWL1vSIGhHkyJoM6hkb8LhxlW9QoTXS5r3H6wWwlzNQkfmJMVfpx6nLMbd/15o0R1XVWRfPkqTPb0uKcy4NbSxBsWhdcoO2UiL7OBV5/p2pB2u/e8G959OuA/EdC4ywpDNJuGmSrpMpQpdaH7ExkAWf9TUG0T7leP4k+/2ge+d7qxt0VsshTCQzUV2nziTZZichiy8VhmfoES75VWXDDsRRHz/PzI2kkSJRh14has1Po8nPRkMJWUrEFn1R9IHzRgABpPTjaas0cxsyaNNsyr6zGNm8lbT+XXF/MWob5fFbPv5x2Fy+3XnlAl+n1R6i14+v2W9hYD/q39oMyPq/JRuhovu03jv67xrp+UVfZk+NRqbZVvuQEQjtK4+OSLFj4+Tbdc+Wx4NLmDbxfh+MTBPa+pjlrJydKv8J+7r6zSjpLNCRFGfsXosrwxs2eK6iUh3rJEG3qpfzXVbGB/TW18/d69Wu7IqtkwnfCDbGY8FfPcFaKJ8/qf0rlflWW3Noe5T9DWd4t9GSoEwBbXEvKEHmf0Teflv0HBaSLZEeaax/odOvrECqs4ZqenpUi8k867BLqezqtmukff7/hCMsad4FNY//CoSj/Zz4RZGLhhyu5bocypyo7odOWJ+2VH3GBg0cU51KNhrF1IHfNm5ZJHl8A8c2wE8Nd9ivI/jIp9zsqQuLDIhi6o9ujN1J7HortHyg69q5i6nqNcY49QZPu0E58r47ESs5xBMksphagVRP9Tj6yGW2XcBtJHaapyN4fO6Hjho6iKcwmutr2BPuzLg15Bz6wjQzFLGI0gZdUPQ2fBjLwsBWuYsoXMKqhtxWyklMlPeVG4WAe2OGxHJShX7CMyVXzpAp9kyuWEvCwxz0Qs6pj5AEgpDs+nKos9mYcCzXLAB4mK9P39DexZPkDAwsXerUO7B/8xwvVK2FnMnYlmP27U9ZRXcWLKC5bHQmPJj8FU3mC0kTZuRX9dKJgdtuVz5TKKspRi2jeAwJuNO345o+MAdE/MGysbuT1ibEG9EZ3+vPeMvHaJi0PqW/HW4UJnauqUNdZ6MSxJ+2fc3WXRFI0UuRynRM1fVW9Sbn+5wYmrxngf1RHDTgB9UlrEbV1TAOa5+FN/foM3daxLcs/m0ZfFJw0IUn9ZWdC2KuVf/mAB7taNPLUWfOTKiPwYHfnr6spmoc+7ze4RO4o6fN2y5wHVK0vOLUpmZwlQP3lDfmGQIusGN6rpKONx7nZ+NSG5bv2WvQCvZ6foe2HsHXB7v/jYJCPlqkPR6T0pZn8uBCt1Bbiggzrjb/Ff/KRnbUQl0IU6mm+UDW7/o/MZBcE0HD1LUnXiVrcCn3hfE4E+U3AtJ7dS0ib7BA/BDNafoY9pB+FreS/mRu3hYEInA9r/CNbXgeg7lC9BJPj0P8bV7j1cMIP4v3PU2XoSD7birRwZe2sZZGrVIq/h7fDg64gMtgrQUYqwpqTuRoGVT5MD7IRMbHpyMFr16UxBbsC0ZZGqsonHKPOd7nQ87c/6bLa9Hy9Jw+2sfhu6IL2o2bS3AisBkbCR7Tg7JUB0Zxbhh205OBTW9/8WTtYLX0bibKGwptbn3n/g4n7R1PzS0vLF7eEL4OjbVGYFQkte6/5MUt4KgoXiiRgILsEP39byuH+DT984F6vPxxI2Wx8/nUcZC7ftT1BnJ7eHh1VAFEBLu6sNzsPbHYrMwV4oobtEeOq9i3Wq8T38ElRwZrR5Z5yhJaLN6w/P5MwNo/zYv3N5Q9+6bLXLpt3xZHrlRvR1yyDIOARCrt2yCO3TrTgGoaj7E0J/D9w/EybUZM2BZvSlGfxdS18Xaajc6UwDXdUQjOK3XOdUggNd/UEc+H5hDJhlW+kyx7dd5cAO5MkSH2thrzMdNVtpBzBAO6QjJBoRddRE1PSjuPzNoXBDJ7WAMjbe+F22cx9b57vv08HNo9GA3xPPFJDuq4SOs/tNtXPT2P/JpAP2D2TGHP1+GHEF7xJuLsFmty/3BzpeK/rePq74wFdDXpcxNMzB5bl38fFX7v7dd10Kdm70eVS5HZlE6Hll29B9OHcxiz1S3oQuPGely9ANdcPZH7/KbgcoINrEZpbEwV3RHrw5GfCWN4UFO45M2LkyfweqoOlmZAIGzql4s9JgS3QMxXQuVct5c1APwbHiTnP0dJ0/TaxZfH7Ff8WhPrlaylBoc2ZB6hFWno+8zT81EdZIyS44a2LonQibYJR0vKj83qbqhNHT/ht6KaXE8XZEss2vOrpmd+BH3w8Qy2BrK8PuJY/h4HvWL0eIEvVGrztKT6c+isjiRnCYu8OCa39cby9aHNlmWFkcWd+C9PZ/LRvCxZY/Hdn0z+47rapB664GDj69MZGzIC86ISz9zfnEFlovcakHDgr/C/5YtoHeBycnX1nTwnY6JmzgdcsxGfaxdFkNbq2TqNfnWNtYD3IjOQcTkwv04J0hHjH2ccVwk6Nu4wj2Ce4p0b6JqSllUTyFxvdVfExi4jYWcqPpf7E02TAXJcHG/tgcwbIy8Ef40UxmuKev8iX1SgaqqqrBFBqYDV7fVetZfn5xyyy4Vjux2HQyzo5cvbANShCNKvIr7RFkFzYgBIk/dpeo7u6KQv3geqtAVGb2Ymo3NnN2dvbx6YqpqblcYSubIST0paJI7ge6wK/lJYody86nBNcsdLjaoMREvKm3EWJ6sVozYMRjk22nlL3um2J61VEK58uG5VTQj8vKyi6Y39nrCcsESjspG21T/KCmph6vrKxBdf9sumIrjttTVgRt/8TPdoF5J4SiKggWP0a5cyuVHVXhkNZS9wYZSoBaZTYXxLWkXXozf6/DGBfEbqg+RYuv5SKYTktnxbH7o52QoZIKevT99bs0LhAWmnvPEyfEC0chDd7SIcRrFeHm4MjGbx+SkKBFVttcrraT0RwdlwMgHBkCFZ1Dr6t1IX0N5JjwQbre6r99hL8NTixvstOqitkuEn+U+02b5YquLWVYNCcvpsf8frvNgiect5BYqKJBVhOhzK1h2cjDzQjVyUmWgA7271Nl5hpcUOMOAdwJEaGqhbJ9qgz8PCszNvntzOrL7E2le5o0T4UsHB2x9d26qoTi8Y2muPQUgxJ3xxXOOhKbWWub/F70ayjS+fGYtH8A1DA0bilq3mzm5qRfueztlHyS44OtqKiokZGoML0Kpq4gzCy5KhGlweT888peS3hsb8pxdDpLqiq6tspPF9/1xXduMz0o9TJnbfM9K8UOoAXseKxO6hdu7i+NlgDt4X7RpL3kjHDVUtcyb0diMAX310jFDaE1LJ95GEGhdt/BFlyh/pkGHt7pS7QZN6jjHuKh7zNKZIFh3mRXjxDlvS+oYejIgfiDlgl8TIb8pG9dNP1r5uow0Rg7AlDLzzr9UoHsLXC8P3f4sVba+rEDA0PFZkuv64TMiG21eVDcLtPhRc/AgWaV1X8pqfpr6kyzBPrRbo2Ux0zCkalXKCwwhlHZBXwomBazLi9E39CxDtHg/lts8wZSmFC+UbDb8xWPX4nr3XnJRK78ZJeQm8KVSQr9edOPzuv189voAlW8kzNRNj99wGBE547EgD1vggTbUBrGzfv4qCl8aDhF+vdvN/P7YxBoXl85uUconGyFv5x8xKljtCBwg/pJT/7AhgbdjELI/AalirYj/MyBPwJeVCKvrdMlVXKOfNg8knT+kxjNMH7ajfJASmMZfMtYwcreH2tUvfZsBK1a9C7VbDTDFByVLqeYnRiHCeAgKG0Go8tJdMUw+Glv/R9im64vzuUG1cqeFM5Gr3zdcI4NtuFG5y1KGPvlRuHT3q576+4oBIIRff2zD5/Vsff2NsxFsZ0h+tpN6PkTQWkO9ImdBeu7VnFy61/nObSJNxWNsGLhlrWVRmVNSHgSZHysZuereJavGKp/19nG+ngxXwQwTBt/yd9mtOren9jJz1e8FUGD1/7YfqiB/jfxBynvtS4emrp+iKK5kGPxV6y1deZafmGFdqQVYiA93iy5xlA6jGobeoDjbahs+F9yhvD8MZjheNEa2In8eKjEJXVigwVvh+r3GeHPvs/tr03L3jbdzW8gfqSPzzfwuW/p+8V7Xjdwc4fHoeBVF941SWp4VLJcg4symgGtKdiZFI58OeLaqfbFkSBpu5iaV6/ZS4id3a9q2jZzl2fRR2e2FAWgoqTT+S8JC0ukrt7TfIFJ/rYsMOgbj7224FjslIaNVejEyEipFivSLWggMP5JcEK5S6paSYlUiuyRo9VxoyMFc5sNUxdDjnNvdF0wAsIqvefX8qCwO2/VgtbYDz7CPYLMRtM/EOdlTr/b2rY9Tk+PwNiRxApxn7CDJbm5NwCImxYW4su1p+KVrVGyW9FpPNSCI+sL0+aHp+GKyZcKKO4V0o8N2nnoZGUDLE4NlC0FPiM3tHmlKGYENq8q1+/ptI+CBSANW75fii2OhgXnT9+wTBfTE9B5QoRyzaZF4raa5as1FzBngo73P4IGuom7jvcPMjixrCZbpxzD85TD3BJpNiIFxTnPL8p0aK32qstWe/GVnzOwI/PmbMVznOJDX3sCFDOPjKTbMvo/M8xGO0a2YstpXrGWdrRk2V4s1X/2LzjUoAMe0rxHStQy3UMOM+ofDzznORAxlfKMczqtN9GIHG4/Xru63zVZQ43DDeWzec/FNsSy1lxxwn5dXmoODQbRlPxw0jWXh8BFOhUzpq1Nmsi0Qq9g+X8mIFfOuo2kq0UDRbvEqhDvcqS5HdJHd5N7KRFQMuUGvuXISJAPk0Uqsy9exiC7G7UFezQJbYSsNtdjVMqaFMNFrLeErvXIJWIfSgrHXZu1NeleSKslfksX6hRh/Fv8J3DcTxF6XAmNut271XmlUVkSlQSe4tlTtTifPJJ4XIEKrtE9sUvvx3AKlZoMu7SuglOZI9pwKpeaaqLkv9jD+N/MI5kWbMQVA7fscrcyKMOYQ+j6dux8WiPGMoMZmGqGWkN1Re1H2NbzKUlHt8QGO+34zHiVMur7Oqicv10OvNRJrG0qKHl+e05Z2VDxAAIs/dOsZ5ULrYnZq1b1eRS9krSObQq0jtU+QiLarmpFPjzMvIU7PgRjd9G66bD3w0MKWU9q68jF88poFrAlDbPQbF8yuwvJgfe6dX3T08YdC2EAA7IifFFDN4D3+rTd8804KhkykVj4cNREc8tgTs5FVY5w9laRCMHFRUn2n9X1ibfDw6bwwLv0k4tDE2tre2HP5xvJdyarZ9dL1t33pEat2NM4t+Eh4dTUVKFpss/1J1Wuzryiov1Ez9QjyEzOfe4tHcxJ74BlTtxjX4BcXLPNxoiKhffTLNxCqeccHBY6LY7cy46pu9wy1NnZ9VHjoKDvCLLBkZDvVbEortlQ4/4IShZbumD9bLR2VxG5uBWW1A5wDq2fi8UzSyKXIVyvh+EAaPbYlP1y86nVhTIiclXPyaSYZYVPSTmN5yNp7qqAve+gLdaLDyVCQI8SYYi8pY78F3qJH36jSeVuDv2sFDKTaT/+IHjNs+W0LTFB2RPljeA3QYCOUQetlyP198Pzug1ywOVPF+zw8sUHpJBySPme4yQ8RfYEbmGsc1uCbmkNur/xXXAiVxx++DIrHQgWDbMzaTrpNLBPyq85p8sGkQYsPJ9csbxMKVCdab839dKFiu32SOS3wKt0Sivl9Uhf/LCysTMS1LN+UdoJoL6LK+Xte6OFJh3g9l85eWx/QSnnc4I/nYyLEDwoGe5/01Gu9ynO6fQWKIqhN3q3JfAtQDlG0vMulTkPy6tp/tYsn9/dnPCseXw761yTeBGi2glX/g6Fx6jkKJjNZCZ4rEQcurbfrqKePHiceuiHwgsro0sIoHyAuqDdAJ081b/3DkARua/NsDwyn7TlMownXNfxLBEpYdMIo6PhjD6IaqyIrWrDC7q4cxP2hvKz/MiG+XMbIZhdy/etcgMbvduURuW9jwqtM6m73zqC+vxFbHUVDZN0xWcHXIxB1qJ358vvxxXzPLLV+d4YDWe4LfrTVfDq7hxlGMZwzCPfjdP2jgglChdDu+7vz+FrhSJTiowk/vf7uA9YrV4HIz+q3o1Omz7xyJGUuVGJe8XwyGzUtDPgzxdSEUcdaxgyFproHucY/bTbr6AjyzzeMRBZjnubJdNLKdHurtm4FscLoz68Cgl+dhqGo/P3776/FvfswWapFpXRwrECL8Hq3r3ypILdLy7yvW8eXq1n3384RbE/l0uK4PwLyzyg4LN2Srvb3IR16eQu+pY2vjd9Z851Qx6FtePJ68S0G7BGhndhmxhGQsHY1m4p8SAD8nc1T4gOW1xstn0XGnvaf3t8N2PiWs7l2tkVijR+aaPrhia2aVMZfvCCbHx8/U5ZpuIVGVaobMf9ZPX8hR+Pw0yQ3FfdDnytEyZs2wba8GpHFL4n+VZTEykiud0f8HdfjHHl0TV8bDA3RxeaLN71xZkMDN08ueL3+Fi9hI7Hg/edcsvsIm6DG6ZlDhsnxJ82SG119G8PkJY16HMEVE6c+cWvZ7/f8t1DGyKE2pVsumskReuWRqwUYh51bsZOy4unTmcn7k9tfS4D9uFNJKMvgpyuvRawMYpwzv38lFnFoYurPg4Mi9W94HjpXLzk0NkkQZuCU1f+KABKXKxioU2J254TJ/iJ61d8NUjf+3pPJw2nq/Mpf/QT7iVPEB5tLdFManv9laDII0DQKLshOUwfgWj1jfMwKcYmKKqyY5MZrY1by38DjoOTJ2uIiR7NdYka1qsaoZe+eudzngRNVnbGcd8rSLYr/kbF2YXV5ZFIbiovtIXM11LCsIfFw6p3zkxDk2j/
*/