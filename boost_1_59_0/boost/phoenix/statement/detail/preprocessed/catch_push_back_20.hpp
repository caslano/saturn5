/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 2>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 2>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 2>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 3>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 3>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 3>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 4>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 4>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 4>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 5>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 5>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 5>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 6>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 6>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 6>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 7>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 7>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 7>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 8>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 8>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 8>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 9>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 9>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 9>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 10>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 10>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 10>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 11>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 11>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 11>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 12>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 12>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 12>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 13>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 13>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 13>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 14>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 14>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 14>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 15>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 15>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 15>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 16>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 16>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 16>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 17>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 17>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 17>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 18>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 18>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 18>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 19>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 19>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 19>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 20>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Capture
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Capture const& capture
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 20>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_
                  , proto::basic_default_domain
                  , catch_exception<Exception>
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 20>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type
              , catch_expr> gen_type;
            typedef typename gen_type::type type;
            static type
            make(
                TryCatch const& try_catch
              , Expr const& catch_
            )
            {
                return
                    gen_type::make(
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    

/* catch_push_back_20.hpp
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
*/