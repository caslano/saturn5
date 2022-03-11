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
j4ReAfBvUM2ZOJ59aPJTH5Skzahe2KC47PXnnlu0IY05aRg0mMfe77+Xoio86a/GTi//oUmgOvJd+izT7marohqXI9Pb7sqynU2BcNRikJyQPcF6wGIjf1+YRD6EFSO8ISY6sPYJH+H7IT1QsCZRs04iVzcFtUaWkQVgaBnPU1AX8gGjRJ5HCPdp1gqXC5vd+QvgM4auMY2dVjA/WtRJMCqb45Q3bLovwSXtPFP4mTaWcREU4DpFpCWLTp1hfSuflzRINE7xGkqoF5M93satF1QPlAenq8yRcoWuD1wOTrkook7R0XYUoIKiKxen0d2fd8+DBiaTFPEqpSH5KlIODeU+r/dDtsCXnmKuCcT6pgWXeddf3qk0PpoR0F4s++UGfcxdhOo91Fy2PYVWs6uFQlo4Yu9aaOS8XW6HM4qRre51srpf3folhMcuvEGJG+qjmGdOW+3Q0bOlFkde4XNn92YO+oDJd4HV1iCS/3Q7bfV1mwCz3wj5NspBDnoaHRnzDH7itbfEHoTQFYvpoiSf4KCLyYLVUwh1P4lFsGcrmO9z+oK+qgzHRjcFDBC6JQRMdM2FkW0JZfU7c2F4YK8yzEQOtf2WA4l2GJgH5ISlcH6OJrhPM84aa1FFPU3k3ijeI9ww8OvQLRSrp0vMUcfm6Cst55ZWzIMD8lrZ5Qj5ygo72RM/YqZzG6IVoEwVa4hktL1+GOrwHmMa9jR4KAUrHM/DBDJNhFB2Dn3W3TXwVLX54N7dnDB/+EWnaK2TcYC+VEbWSVt8v5mhJxmEG5V4Wx71jgVXFQ9UtoGvo9ksaQ8WDLq4W5l1uWxhXEbGYT57bHcZPjBbsyZuJYK8tNyRuX5tMqwum6yzSCaCK6+LECu4MZX2klqLwpFbSDvISFNYqBfmtUK6nIAZmBRiqWEGjt0eK/xHjMmQh5FGJYCEQsf1NJHhfztRNupnU7Smatv3GPYxJq4epN99HUV8UlBR+xVm4znPEP7KWPQ+Jk79PDIqsNSgKdXqeZzVMIzqwJtl7vD+rJ+saJdNbuyLKTnCsCpSGD9uxG0oyqrl/R3iulm7bocZrX6YPB0bwjSjhpmqglhnTYj95oS51irT/d+aDK9rnfMBXWirdAbQJDvUSQhCGhw7xElL5eB/FOre6wQVbT99vRznmMCh77U9DqDLMVkSvoF0uwOxWrSa46/aK+HwBPjcFnnYszbdAJq7cNWVkrqkhbjRXRnqLux5WG/IKL4ifPaabj+8skfdxL9cXaNchB0O9wqFFrSI7tuGV8nwHVFX1d1VhZW1cNUwSLXhJIUQOe+JCF2zX5Ygt7VINZJ3K7+NIvkT4L/MV3GkWlicHDz8jpk/zScOtYtaj6RmMh+rGZ8h1xvT1j3/blZjbOrUhs9x1m8YLHd93nkeOHQpFthic6cp8DRblQaKmIomMCOIMi9oau4YKGVlDTwePr59Zj2kuchIbn/WP2lroLt4+UcdmiKJis1rIhOiCS1NQtljPMdZ/aFXDjFyc4B3aYb/E+cWTWjWizkL8dHudECps0Nvisn5Z2lEGgpYCuTVPskuEUhcDxB5Nsk1DM7GlZMI6jRIXerC3nUUD6XacSEDRC8WeNpC9S8f7RojtwS+fB4ZSHXMxVvhU7Stet67N4H2gpcFs/iuRs3DouZAyOr4zZINYbImk8rs31p9pZxqB+uUZ2DLpkb/Xv18JksriMrh9lQIrWTb/LK5z1hYaSW+HvM3fzE1itLRPlNk/O3yP7AYfTLh9gdytF3pKloA2kNUJGfAlkbZxbhphHUkJHNPh25NuDH6HFfQl7Jgn6tm2iLQOqaV60OUw07gOtHiyydya4LKbLYMej7kcZPOJRbNkFMe/xj07fVK0NsJJdC1uyCm3mT9liXfCavrVi1H8zPLfeh2cGn5xFRP8U3zfZ0FM3mQ5EwvjkNhlxfan+QsEEZzIF4lF1Jn311unhsfSGv9JfOmIYd24A4ur+CiiShaFuXwitECpX1NZYlkGFpW1XXlWMHyAqhp5eCKUrFyCgXuYQnl+ov0aqXpGJXpZxFux8WT21GXITRMUHwmnrpCtNwrKHOfnJ2lttG6GlHfBPH7tOx6t5qgg+KbxYURHISGpLFC0Olf884DMtDJA0UJw3EkLo5I2Slo0ugHpy6qwgg8VVDXL/kyiJs2PKUxERQY2Bn4GL7NdBbRK6Sx8OSw2zA1wm8n7K0ocG+nk6LeWEwl64tKwmSN3pVtd3hmlINf0ITF1h0khf8/xdwNo4W82s7G1ckJBUw1VQFPH2AgVMivmbAM0pCHR2WA3BhUR0nP96ASX3WiS8iY0URFg2GGTrLodit9a22zyLJSwmrtsbnFwnwiqb46GVovskSCLi2AWJs+jR4oobec7J57OkVlwONx+/u9vTsZu/74nXXrmOM488hfb10G61rEGena5FNVLzZBqjWjM8nTjGx81JK/90//N82OPdEbSJjXcp1XXRFsWnco74MUsgGI734vaWFfqhMMVEchCHgSpLDind9ugf5U7pG7iO2SMMk/VZCssPJsUrCbKggn4G3DaTdTD+SoLSRyjbcjRMqYpZpgAtyeuD5Rz7fAjtFY7vQlKR6r5U72+UIw/aZ/sXxztOm5f9wDRhXyVN+ZGTIAABZLOSo0PzRi4KEfi8tzworsRCdKtdIZ/oNf+8xgyK1+poSGmCVM+ObBpvkpguopiOPWMh7/X7S8QtCk8DTkwDHKVWwlcxcmTGe/23Kz/eAXw/en7GrzLZtXL/0AnUzJvsp+JUhvmeSvwbnhuUGdz+HHZy7L6fjh2ya/z+aYrd8XC65ohkhBxFxhWRDInu7dHUa8ZGNjGJ94rEKaDNE0LFm4mXwJAfazPxVBE3sTo563W+Bo6saO8ujobb7cjUdW4yYurfPtADzutUqXmFlb5bukl0DVvum7WWwb+mAS8SooXQ9WMp1DFtvHS9HtThO/xCB8fA6RkzEkf8ddqSeLtdnP1PzrBhc0Fy1ooKGKvl1J0xktHLTtBt6iNuI3IZFPnytMZFwZ5GdjhCatK9/RyU9H3AN+xDftln+tSRbz1zxVBEHih/LUBMYWQ/OdvF/vdAwHYHUZqxa7D1JPPv8JmGwMTQhFwoUsQb8vfr8Q/cazfA/2ASkSXs+Xcxh4D1C8kHxJ3lRt0jpy86UOWecDgxDHuz1Z02no7m5b/ujG50cJjCOL9VbdZd9lWeMl/JdEJt0exNrORljLoZ7lABmwHuS1lw2c+wSzpSjmI1AmC9NMIO7xv38iEyKkwTONH4T2Y6WWmo3k6xzezPL1wlwlQ1xS6KL5MKWq78T7vWWztF/kPNHSBK0y9BRBSlsBcqvMElHSKFC5IWTY6WvEXv0zouN0ezYJCex17keiBTP51IphIOpklXYxLjQjZNK5q8wpBvxQdXnEyDuDTDUCsQ5PbdFuTblak8OU6WWQSLt/i5kkIikpquAfR6seboQgMGY0zC1Z2jnkyVWmqvjgFrLd9OGuLaaZ9QqK0DCat8QGgD3QOtpvzRrvOgotcQrTiY/LAQPP8fS5+N/2LbA2UoSsZVYqeLFnh/dhiLPYoGz7angZTxBBK/FO9vFgG67aG6LRhpYWCM0L5BHnAzHZqx55/Mpu4Rg7iDd39Gy8WI2keM2i3FzoIO9CoUvcv30eh9yagfh41saBdPzlg8bVcIh0HtDAe0545ojU3BARsXLOsj5o7g43oKcjdCeffNFpPwX+jHcQLv8pTa8SZgG0TO6gIedIydB6fch1xeE5DgQkRfoukAudJ2tn0QbFQDeMXNqRzH7I9m1Wx66dYdZL4kBMYrctCWoOSzH6wzDop8UkDUjyofT6C1X/yxFI5qXw/8C3cIodEDAKCy6RAQy3g7gN+d5Ft1P9pAjwZOW9SPZYLAj4OpL7nrUqz7p1a8kwuHCMW3hQ2bL/0yuiag8zbK52MZbBF46GXVqSviWgfaffn9HpUy3S2SeU3EtI7y3cb/Wj3Yqg0E05EtpoTmnXYS3pdiqdqV4aLOV7QgPSknhR3nI5CF5uodqnXlIOR4420OpGDmheM1Ww86zoP8XJXbdfyCe/glbKkkuURd1CtSGlKUf8RkT8LwZ5HaQGDJPkM6Ik3i8DU6lSwQYL8p8WTZRjZ7jptgQYw3ieWO4U4rPIU/EbOSE/Y+qBipQIvK1MBDzERkEq14TWw4zGCZE7C+85I2WuMSLxa3kJJjnIpm3sT1www1dQa3M8gyYCWuiaP8dyIZOOyIGdYGbyw+dkkGNQF7GsFJ5dJNeEb96aXtgTsJm+VbUvFR2byJdKWLEMSYBdnMkxgteA9RjfciJLRB/BLW1lQ/r8N1vlO9C4V2n4r4wBGuvrDLj0V9bQohZJFsANFcvjYp/jQjachhvnFf+AD8c9k6/Sgp7NbdrOMq8ackLTX+eZtiWZRwYARJoQkMDCz3rCNjRMosY6XH1c0N1AiE44PfDgPHXvh7kgXgH4wo8j3UMBSXHMnTlP0UA1tphrJpRWZ3uZ7fHcVKlac0ND6hTCgbiTNbjiD2pjhmaHCKX/gs0aN2UcWX9QMYMOFO7wxQ6nLnSPR5mY1X2spIyPRmsqUN/ryRpWse5KnWUobDgnqi/TOrbGDrIsUEr/cTONizJgsIsnjjx+QBzQWmDt2+BsyzpkRJGMV4gKyaCW8CzlaXakZpbbi3qXDdJBstZHxk9K+8ULPFo3io/TXvO3/+dU7xG7BDWK4QRGS3918xOvEEsuN1oMshIrj40yD7uqnKsuDVHVK+HcVz7ZJFIjttSaLyEAAtW4l5sVhIxIjvUhYActmXXd8BxM0uRqjB8xl6oPYiVuDVPojf/TlBnmu7iepXPO1yn+AXFvv4HNAXL8TNCao+Rv1acgd9HqxDnawjAD8flWKPczj7NgV95fp/62RqBl0DLV+8ZVMJlMxvHODI088ISaSWdW/2Sxfp257edpPBkN3wU81bi3heCXuzvoCtKz/p1tj32fbVwSc1wyw8Dod61mg9pBLQAH6GP2X1tXAGaspEF6kE3jnOGIWi9GbLNgrCIYfYrhWCLS4i6MCKBX5J4mgC6LF8Zd8YDp4EPqz1uT2seSOR3K3zcb4I46hU8X2vcfmCP6FEQaAl2hnogx5rKSXAq+JNEKIqaKG6PXtBrZkz2987N3PrZaR7hL90kIXNJ9x4pfSdhwcrtmoYOjz5LZ75Xlda7X88Gj/JjrGc6U6xNI04Pja9zHyMdhwg4u+xpuvMQCLro7ODDv457j4Kq6Sfr2bv1WAybAbrSeqyxA5DHDQO3zPHvjHaj5Nynp0BY9Po5Qx4rqKdUAmprWy/2nHnk3zktt/xu3F+3gK5gX+B4nyK79G0936JMkWJMjWNq5Xklg+j8TijQXumu9jb4m/3G/cT/xQHHdXVqPTzllLFa6u+LB1jwLgd4k9bwlpA//ttrbwHCf1efNoPeQJLuj8wey1q35YCFTnfMEu/SdBrsnkCv//xIXdxF6vUB91S9gYBlS8DBd6GAFbAUU7e3RdIOK6CBSdkHtxxAD2hr9jarebeOgX2K7pId+FwfW9lqUCtQB69I48rHkiSD4HcDrXeAF1kl10sKikSV/FmcEhCZamIE54IcOw9WwnilUnVM2+ANY6452jOIqF98WLdoPiaiQ4d8nsQzYxOv9vY8DbSdhdAd7brTpAFcogFeMvJrQlQQ4Lone7iS5eEwIekDJ5z5PvqSE5NvTcY5jzoN4I6xnhTnCxOsDrDr4RXfAegPa4JVy5B16hq4z5jooJkX7cB6kFXHE+pjabiDBQ3xdBnhfGsHGmVHZjCz9Cr/DQwtxP0JlubhI2kOKLyDy+CagBuOI+eeSPzjzTMzNquft3c+9ZkD5SrO3pYNfyYZd83A0OjfDvhglpdQB46cLSMfER+q035C6jFKssQtgwT+0mSBVmhYX4hTYom47nD3G4wmtlFL/08Eh0DKSmKeTuKnFt3sz0u0goJ9rLtITSLFZD67Ty8NMIikWSm5R7fBzlRa/Hdg7tPmkXt9O5FC8MXr3nEhJdUzPJs9WfPxwVz21UCxdBWEhpWmru6Iw+UESovHQV++Xz3S8323LLF6WH8cKVnvponU3CoX1MQFPZb+VPNIoKHFdhgL2oxO4AS/CImK5xfs1Z0/NcY3BpTolafYJ+rS8HH27vDr91YDdSxat89dnyL+xNcbmmFDEvejUMMjXCMzXnSruw4UdjfCOaeEuAXuP668okEwUyFKTbMR/zDr6qOo3/0bC6c/ak+u7R+ToAY5h3HsD5jDxPzS0+4LFLt9DBxmFOgvbff8PvULSRrcIwZzfxWGyzH7RfkvWBv4rNP8avnTleX2Is0MJCm8Mp3YK7kYQfnZQ95smSOF0BErxqz2KF+ELoz8X6o3xSAVI7S+Tsb7wzFBlkFTRsTHFUZGXoyFg8QCihc7HyqVOnIkiTgDpi6wal2o4bYqmGFrin3F8TSoKNzWVkji/K6YOktXFwkb1kELLjakTBCANMBjon68OMOBRcZdHimaUOUnF/tdBJMiZNrpkUGc41t3h4O/T/Cv0a/oNLE76rg+BGyBgLNZdRmT6FFXsKxmBdGBt2DLEiX+jsmgxKl/+acPj89Q9D7jPbWGt/e1Wvo8sz5FDD8idUz891oY2u5ag46Tp2/ZLNN4Gx9AjxiBDilEaY2rFytCCgbFavfwOq+e9/WV9ecmlpQuT04/cNfR9CV+Fu89oos2yTcbgC5crWuvz2KycbD07uqn5S96wk7MKVwczZkv7Uag8cWFuxP6f3UudtRtGLW5Ea/WDUjvKKZVh+16VwTU582yhHQbRC7kpnGukEiJ1qPL8evcwlTPhYR95MQhqE8WxBIfDBSyAHzRBNCn3rm+ELuRxZKA2wMrvfXTfYbdPsHBdYy/g1Tpt/C9yTGzoAmQkhXrH7WDxJm/fLohf7aYOl/Khnuq5HnHQVEtv+H8KwW1ejda//Gpu7UyGkL64qD93s1JF+OJIgljXDVic/zZ7ssYY0LdY1tk7kucZGWI+WtQGdZawWNZ57um8tqILjCqSFtg/qD2FnnD5Cw5240NGtCvOfc4D8yQKL+oPMXcrvbhm4wD76clQtkGrdYqvsgpbOd52Bm5i4GAXCi7j5vmCfN+TFlijMJ+d0KHEbc7l4By6ah60fB3zgCm+KPAWFmJlARxJMv3kS90qagDpNJKe+rQcnAGlJ1nPpieW3ZPUy0USC2awnIt3cubolslK+vyf5NfiMFadN1Q9oAFKMAASuSfiyUHwdq/PPiZiMBdf8JB77jdKYEpQUSuODLckHoS3DJSdLk6zZDrU0ImSHCaXC69uOFOgDKGKHbOU0Sf3zZ04ZUb01ryaRNmd/AHENspJd6igCcaVG6R+pXp6ryBI5HZRa2iSBLrcnQDYe56k7ZEkFPqVGezKy8ip7cgryWO+XwlHeaDEP7FFgXGnuUr4rrFFnzlFlTzX+ItuF8Xs9DeceXdYWYovVjFBOefPzy6lakAdYSc4oWiEaD9rnMcgM7YgekFcN58BSjRzJNU0kZJKFeJxRbcLiukBXFY5tp41URWXaljpNiKE1spsHfpmOzb3SmWCETVf93IahuZPoR+gHhLnlx9KRKa+jLoYj6olsISUPBLxxq3j4h2gjAo24A0ja5Ve/GRhrlg6OOAJ5EE4sI1RmmPvIAXwgQqW2gfSILG2pnabGuV7PaX8rPk4AwIG5XjWS+mHebUvLJx6V4HK1tLEndbdhlRv7gaYBJ6qvEH61d7a0c9lPQgmqVKl7zbJbBSgWQT1BA3GjQm1oFksTv0dj8jDJEkQjaE8IRtDlN9Hh4UK4KqvwCULRTqOxizduAt3/fe0R483n23WVzhSWrE0QCTTlzhawK53AzssV5QBqvWbpkwY718hQK9D6xaUddRbu2NGtXgqJcblIGOIRh4VjxqUcjF00w5WwozP3wYSqahRLheGUUW0CFbmYaorrU/EyfSsqmeSBNrouLRQdcyik4g327G4JE5OM1DNxHhImYoUB7QkzPSgjZ+qTVUxqkJZRHNVq9AvsuRXXBSq2ChV/vMXjrTWxJaV/yTrm9MhjIUYVxgGNCD0CfilGuZJB5YHUm3IKAWp4ergDt7GuoBmGlghgm4QSxy4sYZy8WNEzw8W6zrj6ONBiBkUrXzpZdn7xHjACquhmV+G0gSsQhczP+HA+ZENA84DIY50/BcRrElGBs3a2JWVCU3T8s0KD20JhfTTbpM/KHuJqqgGJJlHgAnBW/OZNhibP5us+bZO5i2qjir7AeFgeOxB+Ex2xAVfIxQ/u9f9Sp0OO1Y8LLpE1xMV/Bj9xCjm4UjlHZRsmvCEQO0FLI7ZnoIcMEiSYAPaSmdXHJ+J0dYQnonc1hBtDadJTtGPC+NrRNy+OQjcQUz5xfI3r82pIjB1ibCXhLp63oEFwAd+F5ZhFS/f+WVS3Q/b8A1sdBJqJtAW09Fr6DK2xmT1E97jHPSawATe8pAfr9r4DKLIDJ7V6hjYSzkXI4N8jemxL0lA70qd7D4U8OYL0wclcYcdltnD9J01IjLWJk9gSVmIvCpT6j61HHA/7vzLwEJddqMYWQeWxmmTcqy+qUWRTr1BmnUngjD8K+BDKhdAI2iXh9boOD0lWXdjxzfZZshEXjx/lDUncEsBwfMijiraCERQQ55yRNyniA8ScULkj77KDyVFoZ3wXUG6mGCaHA63IRX4qVKLevjQWSqkoajDVYp7Wfekr2ZsZWod+BRa0mfbptz8mW9Ko7UJmVkbgAzPhJSYxiJ/AmZHhTNbgSUb13YAFouEfsFzu0+mUoxRD/v1Dxlr8rboM6Wc6NhYmckbo5X0GZ1VlLeSG4B8zeEaYo2+KzqrGw+xnTFwL8iF0L9mtl6OBQOESsLqH4iLHevxEH/jauH+gn/f5T00bTF292FE0IVATohQoJD32m8r4SlhSjgIlDopEXo01/0/qdq0nvv/+c3KI+KCLpU9Q8sfhSE2kuOI09wZV4BBBWjkzRWmulFpjzHSQUhP4jPWNiCCjocujr25hVlzBhyK1DdYl421aJnW0JxS2Ie04AtKs791Cx30JX2vBX27nJlUGQI6PAX/WkRERx1+jNGFgIzmBclLxnvwkKL7+BNF0hWtwuVPhSOoMgFsB6TOb31n1whu18w6nE/grJJ3bV3blV84EII=
*/