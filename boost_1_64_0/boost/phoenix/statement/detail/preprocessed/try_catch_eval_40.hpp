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
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30, typename Context>
        typename boost::enable_if<
            proto::matches<
                A30
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30, typename Context>
        typename boost::disable_if<
            proto::matches<
                A30
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a30
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31, typename Context>
        typename boost::enable_if<
            proto::matches<
                A31
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31, typename Context>
        typename boost::disable_if<
            proto::matches<
                A31
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a31
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32, typename Context>
        typename boost::enable_if<
            proto::matches<
                A32
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32, typename Context>
        typename boost::disable_if<
            proto::matches<
                A32
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a32
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33, typename Context>
        typename boost::enable_if<
            proto::matches<
                A33
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33, typename Context>
        typename boost::disable_if<
            proto::matches<
                A33
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a33
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34, typename Context>
        typename boost::enable_if<
            proto::matches<
                A34
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34, typename Context>
        typename boost::disable_if<
            proto::matches<
                A34
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a34
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35, typename Context>
        typename boost::enable_if<
            proto::matches<
                A35
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35, typename Context>
        typename boost::disable_if<
            proto::matches<
                A35
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a35
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36, typename Context>
        typename boost::enable_if<
            proto::matches<
                A36
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type &e ) { eval_catch_body(a36, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36, typename Context>
        typename boost::disable_if<
            proto::matches<
                A36
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a36
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37, typename Context>
        typename boost::enable_if<
            proto::matches<
                A37
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type &e ) { eval_catch_body(a36, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type &e ) { eval_catch_body(a37, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37, typename Context>
        typename boost::disable_if<
            proto::matches<
                A37
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type &e ) { eval_catch_body(a36, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a37
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38, typename Context>
        typename boost::enable_if<
            proto::matches<
                A38
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type &e ) { eval_catch_body(a36, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type &e ) { eval_catch_body(a37, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A38 , 0 >::type >::type::type &e ) { eval_catch_body(a38, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38, typename Context>
        typename boost::disable_if<
            proto::matches<
                A38
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type &e ) { eval_catch_body(a36, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type &e ) { eval_catch_body(a37, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a38
                    )
                  , ctx);
            }
        }
    
    
    
    
    
    
    
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39, typename Context>
        typename boost::enable_if<
            proto::matches<
                A39
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39, Context const & ctx
            BOOST_PHOENIX_SFINAE_AND_OVERLOADS) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type &e ) { eval_catch_body(a36, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type &e ) { eval_catch_body(a37, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A38 , 0 >::type >::type::type &e ) { eval_catch_body(a38, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A39 , 0 >::type >::type::type &e ) { eval_catch_body(a39, e, ctx); }
        }
        template <typename Try, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39, typename Context>
        typename boost::disable_if<
            proto::matches<
                A39
              , rule::catch_
            >
          , result_type
        >::type
        operator()(Try const & try_, A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39, Context const & ctx) const
        {
            try
            {
                boost::phoenix::eval(proto::child_c<0>(try_), ctx);
            }
            catch( typename proto::result_of::value< typename proto::result_of::child_c< A0 , 0 >::type >::type::type &e ) { eval_catch_body(a0, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A1 , 0 >::type >::type::type &e ) { eval_catch_body(a1, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A2 , 0 >::type >::type::type &e ) { eval_catch_body(a2, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A3 , 0 >::type >::type::type &e ) { eval_catch_body(a3, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A4 , 0 >::type >::type::type &e ) { eval_catch_body(a4, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A5 , 0 >::type >::type::type &e ) { eval_catch_body(a5, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A6 , 0 >::type >::type::type &e ) { eval_catch_body(a6, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A7 , 0 >::type >::type::type &e ) { eval_catch_body(a7, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A8 , 0 >::type >::type::type &e ) { eval_catch_body(a8, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A9 , 0 >::type >::type::type &e ) { eval_catch_body(a9, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A10 , 0 >::type >::type::type &e ) { eval_catch_body(a10, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A11 , 0 >::type >::type::type &e ) { eval_catch_body(a11, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A12 , 0 >::type >::type::type &e ) { eval_catch_body(a12, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A13 , 0 >::type >::type::type &e ) { eval_catch_body(a13, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A14 , 0 >::type >::type::type &e ) { eval_catch_body(a14, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A15 , 0 >::type >::type::type &e ) { eval_catch_body(a15, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A16 , 0 >::type >::type::type &e ) { eval_catch_body(a16, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A17 , 0 >::type >::type::type &e ) { eval_catch_body(a17, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A18 , 0 >::type >::type::type &e ) { eval_catch_body(a18, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A19 , 0 >::type >::type::type &e ) { eval_catch_body(a19, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A20 , 0 >::type >::type::type &e ) { eval_catch_body(a20, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A21 , 0 >::type >::type::type &e ) { eval_catch_body(a21, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A22 , 0 >::type >::type::type &e ) { eval_catch_body(a22, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A23 , 0 >::type >::type::type &e ) { eval_catch_body(a23, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A24 , 0 >::type >::type::type &e ) { eval_catch_body(a24, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A25 , 0 >::type >::type::type &e ) { eval_catch_body(a25, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A26 , 0 >::type >::type::type &e ) { eval_catch_body(a26, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A27 , 0 >::type >::type::type &e ) { eval_catch_body(a27, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A28 , 0 >::type >::type::type &e ) { eval_catch_body(a28, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A29 , 0 >::type >::type::type &e ) { eval_catch_body(a29, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A30 , 0 >::type >::type::type &e ) { eval_catch_body(a30, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A31 , 0 >::type >::type::type &e ) { eval_catch_body(a31, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A32 , 0 >::type >::type::type &e ) { eval_catch_body(a32, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A33 , 0 >::type >::type::type &e ) { eval_catch_body(a33, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A34 , 0 >::type >::type::type &e ) { eval_catch_body(a34, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A35 , 0 >::type >::type::type &e ) { eval_catch_body(a35, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A36 , 0 >::type >::type::type &e ) { eval_catch_body(a36, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A37 , 0 >::type >::type::type &e ) { eval_catch_body(a37, e, ctx); } catch( typename proto::result_of::value< typename proto::result_of::child_c< A38 , 0 >::type >::type::type &e ) { eval_catch_body(a38, e, ctx); }
            catch(...)
            {
                boost::phoenix::eval(
                    proto::child_c<0>(
                        a39
                    )
                  , ctx);
            }
        }

/* try_catch_eval_40.hpp
2HykmcTJZJknK2SX5Hja70tL5YiT1bJLIh20ikstmSjzZblsl4NSXSN1kWSZLvNkkWyQHZLlYnWTZtJNrpa5slA2yA45KHVb2NdkgMyUJbJOdslBiW3pM1naSKLcLstlh2RppW5SS5pJJxkjs2WRbJFDEnOJOkpd6SKTZb6skz1ySEq1VidpKb1kjMyVpbJB9skRKdtGW0s3mRhZd5wu82WFHJFSbU0jXWSATJfVcrvpt/OgxLZTbmkm3WS+7JMjkv9S85BG0l6myzxZLXvkkJRs7+fSTSbK7bJctkhsB+WU+tJGhsh0WSRb5KDk6GgZ0ki6yGRZJLNlhWyWA5L7MtuBVJH60kYSZarMlgWyQrbJQcndyXqXZhInyVLlOuXjUtkuWS5Xfmkk3WSyzJfVskV2yREp7sBWXRrJAJkqc2WRbJGDEnuFekhd6SaJMlUWyQY5KLm7mJdUl5YSJ7NluWyQHXJQclyp3aSlxMlkWSBbZJ9kucqypLq0l16SLFNlvmyWfZKlq/rLEJkuC2WFbJEDEun8FCN1pY0siux7nChzZaEslw1yUGK6W67Ukk4yRKbLXFkqW+Sg5O+hXaXR08omE2WuLJVtclBin/FzGSLTZaFsln2Sf4l1Jy0lUWbKItkmh6T4H5VZuslkWSCb5YDEPmv7kESZK5slx3PekwFyu6yTI1J9qfaTMTJPVsguyf+8bUXaS7LcLktkixyS4su0gXSSRJkuC2SzHJGyL/iZTJRFskNyL/c7EiczZbXsk5gXvS9dZLIskA1yRMq+ZD4vZfnt32//fvv3279092IdlCVryj0163VLSHTXwISRI/rGp/w3aUjVPiMHDomrWqNajWrV+1UdlVSzeo06aT8bU7d21aQBvUfEx1WNi+8zsn/qz/2sW8oTXwMevNWnWkKfQb5PqH9allKR/vKFnba/0DtLmm0H9h2RkJTQL7lUhY4VS12amDxw6MBxbmtWqqnb4g0cEj/i6D0TLy7mGHdv5J5mkduwpd6RNbl35J66Zfy8hZ8nHv153PET+JcrS5vTPC8o7Rlt3bIe/6y7zkUdV18/+vzp9o2btm7e6ehNzU/+2WVtwv3bop+Tti4sJ19YTh7paLp56ZYTuRnswGEq/SuXFZPy7OFs4e8tKSB75Dw/WZSyLCvnfM9MSXkI76955lahcJ+6Y/d2P/65W5H7Aw7ZbHlefxuT/v56JcN4huJZU8oXy7bW247Nx8rn3s2JI8NTuNwXcODJPXs58/vphefMhDKmf27KoQzP33rxjexpz32IXn8rQpnvC216t0wqbLo/Hytzcm93x/XQopN7Xljmzwd71uvIQ2fjR4RnvEU/oyiUcf3RZfo7vlj6dq0VVmK1sI1VCc/OiXkztYw9e7vX6ujoO43+mufmRG9ri8IyHwrtcr+0LyZpy0xZh7aTX7StdTP3MVHrcFnRyHae/hk9vXKm/OKbUlA2hfqW2pI9/bPmwlHARj96WP8RvePij79/cY6TWD+RddFB3UbFH3ueyqHw3tEDTFg/zx5dvv07wzOF4kK/8k2hrdaH/bL6W1HlTUhIig+3xUwt98ndK//E+2iYzQnrcDBdHVLu5xqnbdsr7+Ve33u0fMfuObnHMobGJw9IiEt/j303tUy7V+gLb2XeBrefknHfD894fjtDG4SHC2Vsg1K/sA1Opr6nRz0DIuNST4+qX8a1UjTq3sBxA5Mic0u7H+4AbTdRXft4vfXtE7ZfWntl2xraK8PzZtaFg8gZob2KsZNp5m1Na6/+8cmpG8zQgcMcgMakFfFknkOR0mb9QpsVjXqeormlzalo1P26o5cQXackH1waNDxzJLqef3//ybiNHgw=
*/