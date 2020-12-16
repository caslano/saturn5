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
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        typename boost::enable_if<
            proto::matches<
                A10
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10, typename Context>
        typename boost::disable_if<
            proto::matches<
                A10
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a10
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        typename boost::enable_if<
            proto::matches<
                A11
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11, typename Context>
        typename boost::disable_if<
            proto::matches<
                A11
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a11
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        typename boost::enable_if<
            proto::matches<
                A12
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12, typename Context>
        typename boost::disable_if<
            proto::matches<
                A12
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a12
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        typename boost::enable_if<
            proto::matches<
                A13
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13, typename Context>
        typename boost::disable_if<
            proto::matches<
                A13
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a13
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        typename boost::enable_if<
            proto::matches<
                A14
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14, typename Context>
        typename boost::disable_if<
            proto::matches<
                A14
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a14
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        typename boost::enable_if<
            proto::matches<
                A15
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15, typename Context>
        typename boost::disable_if<
            proto::matches<
                A15
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a15
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        typename boost::enable_if<
            proto::matches<
                A16
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16, typename Context>
        typename boost::disable_if<
            proto::matches<
                A16
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a16
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        typename boost::enable_if<
            proto::matches<
                A17
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17, typename Context>
        typename boost::disable_if<
            proto::matches<
                A17
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a17
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        typename boost::enable_if<
            proto::matches<
                A18
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18, typename Context>
        typename boost::disable_if<
            proto::matches<
                A18
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a18
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        typename boost::enable_if<
            proto::matches<
                A19
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19, typename Context>
        typename boost::disable_if<
            proto::matches<
                A19
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a19
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20, typename Context>
        typename boost::enable_if<
            proto::matches<
                A20
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20, typename Context>
        typename boost::disable_if<
            proto::matches<
                A20
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a20
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21, typename Context>
        typename boost::enable_if<
            proto::matches<
                A21
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21, typename Context>
        typename boost::disable_if<
            proto::matches<
                A21
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a21
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22, typename Context>
        typename boost::enable_if<
            proto::matches<
                A22
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22, typename Context>
        typename boost::disable_if<
            proto::matches<
                A22
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a22
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23, typename Context>
        typename boost::enable_if<
            proto::matches<
                A23
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23, typename Context>
        typename boost::disable_if<
            proto::matches<
                A23
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a23
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24, typename Context>
        typename boost::enable_if<
            proto::matches<
                A24
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24, typename Context>
        typename boost::disable_if<
            proto::matches<
                A24
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a24
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25, typename Context>
        typename boost::enable_if<
            proto::matches<
                A25
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25, typename Context>
        typename boost::disable_if<
            proto::matches<
                A25
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a25
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26, typename Context>
        typename boost::enable_if<
            proto::matches<
                A26
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26, typename Context>
        typename boost::disable_if<
            proto::matches<
                A26
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a26
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27, typename Context>
        typename boost::enable_if<
            proto::matches<
                A27
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27, typename Context>
        typename boost::disable_if<
            proto::matches<
                A27
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a27
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28, typename Context>
        typename boost::enable_if<
            proto::matches<
                A28
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28, typename Context>
        typename boost::disable_if<
            proto::matches<
                A28
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a28
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29, typename Context>
        typename boost::enable_if<
            proto::matches<
                A29
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29, typename Context>
        typename boost::disable_if<
            proto::matches<
                A29
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a29
                    )
                  , ctx);
            }
        }

/* try_catch_eval_30.hpp
L6fwFG1yA/PzJhbhNHbiDA7nzbyVt3AWZ/Jp3sUtvIfZI9cZGMuFrMkn2Z2LOYhLOZoreAtX8mWu4Uqu5Xa+xo+5nlki1wuYjZuYh5t5Nt9gGW4L63udpIzx9rvhc6Co/y8P58M9wudAHC9kPJuwH3uxP/tzIG/mID7KwVzEoeF4NYxfMIEFIu3PWI5gbSaxN5OZxJG8maN4G8fyAY7jixzPlZzAV3k9w/fPYfy3v9Uz+f45W7gunJ1nMAfL8BRWZF7WYT52ZH5ewdM4i4V4FwtzKWP5IovxDZbgDzw9fA9yBsvwTJ7LUqzK0mzCMmzJc9iXZTmA5ZnEczmOFTiblXgPq3Axq3IDq/ENVuc21uD7PJ9f8gIeYW1Gjtt1WJoXsjzrsQLrsxl/xz5sxIFszGFsxlvYnLezBeewFRfyEj7N1lzLNvyY7fgp2/MAO7CA7bUjY3kZS/Byns/OvJBXsBG7sAevYl/24Hj25B/Yi0+yD//EvnyfA7iLA/kZB/FzDuVPHMbIeXAii3E4K3AEKzOJR7+XOyWMXw/j2iPb1YeR9R+eLZsUvn9OZixH8gyOZRmOZ0VOYgNOZitO4WWcwyTex5s5j7P4IB/hQ1zDh7meC7iZj3E/H+c3XMgckfMAxvApFuJiVufTvIBLWIfPsz2X8Qq+wJFcznFczWlcw7l8lV9xHb/ja/ye65kt8ncLc3MTy/F1NuAWtubb7MitvILvsTc/4Tzu5kvcyzX8lOv5OTdzP7fyC37DAzzMbxnZPg7xah7mdfyeU/kTH2TWHK6PMBcP8xQWifQ7YEnmYWnmZ1UWYE3GcABPYwILcQYL8zYW5cMsxidYnH9iCW5mSX7IM/kNz+IRns3Tc9q2eDbPZU1WYBNWZBtW42iexwmszrmswftZi0+xDlfzQr7HevyU9XlmLvs1y7Ihm7AxW7ApW7E5h/JiJrMFb2NL3slL+Ajb8I9sy9Vsx/W8lLvZnt+wA4+wI7OeYn9mPg5kZQ5hAw5lEw5jMyawB8dyFMdzEq/mVF7DGZzAWziR9/NaPswpfI03cBOn8T1O507O4Le8jafndj2CVTmbdTmHDXkXG3Mum/IetuIDbM8HOYwPMYmPchIf41w+zme4kH/kE3yOT/FlLuarfJq7+Az38jke5FLmzmM/ZXkuY2W+ygu5lh24jp25gZO4kTfydc7hZn7ALdzLt/g932bBvM4HWITv8XJ+yK7cyT78iBO5i9dzN+/kHj7KvVzPT7mdn/EHHmSBfPZPnsNDvIBH2Jw/sC9/4gBmy2m+zM5nmYMrmJOvMxffYG6+yTzcybyMfAGcnzl5Ks9mDOvwNF7IQryIhdmUsbyERTiAxTiUxTmCJTiep/MGnsHFPJNLWYpvszS/ZhkWKuDznGeyLOuwHDuyPK/kuezKiuzOSuzLyoxnFQ5iVSayGq9ldU5lY97B5nyJLfg2W3IPW3E/L+E3bM2YgvZbFmI7luClrMj2bMEObMXLeTk7sxu7cBiv4jh24xR251T2ZLiOE+7xoC6ZXMfZF84nP2csD7A8v2YrHmQ7/pWdeYj9+B2H8jCn8Qhn8ic+zCyR603IynXMxo3Mzj8zB99lTn7FXPyWpzDy91lunsU8PId5eT7zsTXzsy0L8AoWZAJP5XDGcDxP4ywW4h0szDsZy3tZhMtZjC/xdK5hSf6JZ/J9ns1Iv+lSLMEyLMdzeC7LMqUfRLgnBZ/JpB9E99A/bRCbczD7cgjjmcBJTOR0DufNTOZdHMX7OYZPcCyf4jguyWk9NLatNnH+JTNltRyQCk0dq590PJXVstR0+5jDL5eVltJLxsjtskS2yL6Ips2ySN2lkQyR6bJA1skeyb0=
*/