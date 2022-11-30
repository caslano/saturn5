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
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19, Context)>
        {
            typedef
                typename proto::detail::uncvref<
                    typename proto::result_of::value<A0>::type
                >::type
            target_type;
            typedef typename target_type::type construct_type;
            typedef typename target_type::type * type;
        };
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        typename result<new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&, Context &)>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19
          , Context const & ctx
        ) const
        {
            return
                new typename result<
                    new_eval(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&, Context &)
                    >::construct_type(
                        boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx)
                );
        }

/* new_eval_20.hpp
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
*/