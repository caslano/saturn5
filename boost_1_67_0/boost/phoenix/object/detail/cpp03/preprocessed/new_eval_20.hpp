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