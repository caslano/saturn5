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

/* function_eval_20.hpp
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
*/