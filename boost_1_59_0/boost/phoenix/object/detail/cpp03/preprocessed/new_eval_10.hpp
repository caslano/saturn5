/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1, typename Context>
        struct result<This(A0 , A1, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1, typename Context>
        typename result<new_eval(A0 const& , A1 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2, typename Context>
        struct result<This(A0 , A1 , A2, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        struct result<This(A0 , A1 , A2 , A3, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx)
                );
        }

/* new_eval_10.hpp
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
*/