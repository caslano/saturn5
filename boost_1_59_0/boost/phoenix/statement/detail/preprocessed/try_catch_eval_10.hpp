/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename Try, typename A0, typename Context>
        typename boost::enable_if<
            proto::matches<
                A0
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); }
        }
        template <typename Try, typename A0, typename Context>
        typename boost::disable_if<
            proto::matches<
                A0
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a0
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1, typename Context>
        typename boost::enable_if<
            proto::matches<
                A1
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1, typename Context>
        typename boost::disable_if<
            proto::matches<
                A1
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a1
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2, typename Context>
        typename boost::enable_if<
            proto::matches<
                A2
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2, typename Context>
        typename boost::disable_if<
            proto::matches<
                A2
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a2
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        typename boost::enable_if<
            proto::matches<
                A3
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3, typename Context>
        typename boost::disable_if<
            proto::matches<
                A3
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a3
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        typename boost::enable_if<
            proto::matches<
                A4
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4, typename Context>
        typename boost::disable_if<
            proto::matches<
                A4
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a4
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        typename boost::enable_if<
            proto::matches<
                A5
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5, typename Context>
        typename boost::disable_if<
            proto::matches<
                A5
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a5
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        typename boost::enable_if<
            proto::matches<
                A6
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6, typename Context>
        typename boost::disable_if<
            proto::matches<
                A6
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a6
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        typename boost::enable_if<
            proto::matches<
                A7
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7, typename Context>
        typename boost::disable_if<
            proto::matches<
                A7
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a7
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        typename boost::enable_if<
            proto::matches<
                A8
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8, typename Context>
        typename boost::disable_if<
            proto::matches<
                A8
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a8
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        typename boost::enable_if<
            proto::matches<
                A9
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9, typename Context>
        typename boost::disable_if<
            proto::matches<
                A9
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a9
                    )
                  , ctx);
            }
        }

/* try_catch_eval_10.hpp
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
*/