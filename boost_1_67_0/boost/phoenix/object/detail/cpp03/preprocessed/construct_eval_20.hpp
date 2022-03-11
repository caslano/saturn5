/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1, typename Context>
        struct result<This(A0 , A1, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2, typename Context>
        struct result<This(A0 , A1 , A2, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        struct result<This(A0 , A1 , A2 , A3, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx)
                );
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19, Context)>
            : detail::result_of::target<A0>
        {
        };
        
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        typename detail::result_of::target<A0>::type
        operator()(
            A0 const&
          , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19
          , Context const & ctx
        ) const
        {
            return
                typename detail::result_of::target<A0>::type(
                    boost::phoenix::eval(a1, ctx) , boost::phoenix::eval(a2, ctx) , boost::phoenix::eval(a3, ctx) , boost::phoenix::eval(a4, ctx) , boost::phoenix::eval(a5, ctx) , boost::phoenix::eval(a6, ctx) , boost::phoenix::eval(a7, ctx) , boost::phoenix::eval(a8, ctx) , boost::phoenix::eval(a9, ctx) , boost::phoenix::eval(a10, ctx) , boost::phoenix::eval(a11, ctx) , boost::phoenix::eval(a12, ctx) , boost::phoenix::eval(a13, ctx) , boost::phoenix::eval(a14, ctx) , boost::phoenix::eval(a15, ctx) , boost::phoenix::eval(a16, ctx) , boost::phoenix::eval(a17, ctx) , boost::phoenix::eval(a18, ctx) , boost::phoenix::eval(a19, ctx)
                );
        }

/* construct_eval_20.hpp
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
*/