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
7t32IG6W3fq/DYMFX0s861KX9Wctb47oUDzj18WJo75ZC7IBkcCmg36hmpzfnpbVTuIvGNpNTq3OIABfLgJh3RsvGVXj5QNlM+5ln0VtBneJlZ0O2taKCOv0OeBge3Q/lfVuae+R6DXyYA6jOnFl1h5BljUAbo7cTGt8W4noZi5pO6ThbX0773yVQLhahfeO9+BBDejJOajcYIcHde3EolsqOkjIc0UOsTMq4UUJGoJB4mNaZpmH5ersh0/Yyj/MiPhhigkyRzs65fbMnKdUhNLy3LZD+x0zzRP0GryE7+c1WOctrMH7IrHSE4zKouxfG3pKneX3nngy3TfH1I9P2bcYpG/jem/UMSvWr7i3JG1ByFCdN2yM3Fg/0O+Pji0UtOxzXfqMDx49Ehl9z/zOIA3XaqY8NBZ+b2zcf2Ybv2/TlBYA9VdJgVMD2KLkIOJLlxuPHM4HCVXYIyk9bnDdlLQsIZwAm5JapL0+9CwpzAk6iTjMHhcd4SSfEgt7CSs3bV55+4ZKmvmkDt245k6omi5x8W4U++fUJ8uU6plElpAU2GaQnq4c5x37hg==
*/