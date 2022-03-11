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