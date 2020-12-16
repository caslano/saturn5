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
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 21>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 21>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 21>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 22>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 22>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 22>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 23>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 23>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 23>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 24>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 24>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 24>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 25>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 25>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 25>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 26>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 26>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 26>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 27>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 27>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 27>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 28>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 28>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 28>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 29>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 29>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 29>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 30>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 30>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 30>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    

/* catch_push_back_30.hpp
BzAU38BELMBleBBX4yFci4dRva9Rnu+KfSVdua/R4X7B2zAVm2MadsB07I1zNPcNGpifq34H02R+07E2RqL5OCVTpgtxcpzymtwvnY+Ncb/k4wDejm9gIBbgADyIpuNDNJ+3KLHM3/G8xZsy/7exLR7BXvgODsSjOAjflfkeQ7Wfhjw3FW930k9jppR3FjbDRKm3JDRvj5kyfSsn22Ox5OsMeuPn2ARLsCuelfx8gcPxHM7Br3AxnscH8AJm4be4DksxBy/iY1iGW/AH3I6XcCeW4z78Cd/Cn/F9vIwn8Rf8DK/iV3gN3ZXCmNpxwHpYHf3QA5tjDZTzJfIcVTlHY3e+pJVy/gDb4m3YDptje+yEHbALdsQ+2AnvxM44BbvidAxEue9Snouq1J3jfZfN5Xi4BTbFltgF/bEHtsJB2BpnYBuMxQBMxnY4H9vjZuyAT2NH3I6dMA+7YBF2xTMYiLI9ynNMGeZke4yW9SkGG6IOfVGPHTEWu2Kc+f4nZnRc5neH9CNU2jVv+X78XMr7JTbDc3g7/hX74HkcgRdwLH6D0fgtLsVS3IgX8c/4He7D7/EtLMMT+AN+gpfwW/wRK/BnOc9dgX5YrR7bB1bH/lgTx2AtnI61cTZ64lKsixvRC5/F+ngUG+BpbIjXsBEqxys+2AubYD9sKu1glps84xSPSr3Xw4VS78eknt7DxviB1NNx7IUfYX88gUPwY5yBf5F6Oonr8JTU1ye4FT/Fg3ha6qsYLecrW6r5YTqH85Wn5f7nYvTFM9gJP8PB+DlOwhKMw7O4AL/Atfglqv1w5fmlGOCkH+4i2R9Yjt74AHbDB7E3ZuFAXIEzcBWm42pcimswG9fis5iN23E97saHsRQ34A+4Eeso57OwPm7CppiD/vgoyveFPD9U+U5y/L4okPt2D2ELPIwDsBAH45s4HN/CUHwbdXgE5b5gedan0gY73hf8ntTLcWyIH2ITPIEdsUjq6WPsgyclvVM4GT/Fu/E0TsdiTMIzuAg/w2X4OW7AEszBs2g6D4u78Et8Ec/hm/hXfA/P4wn8Bk/ht5ZyybNAMdjJ/c4vSb/rV7Eb7sWh+BpOwdcxCfNxCe7HjXgAN+FBfBYP4St4GD/EQjyFb+KneARL8R1Uvifexfp4DBvi+9gIP8BW+CF2wBPYH4twIH6Ml9SyyPNDaaukXMr3eC9p5zbL9puL3vgU+uPT2Bu34gR8BqfjszgLt+ED+Byux+2YizvwJdyJB/B5PIov4DHchWcxDy/ji3gVX0IPZf8fG+IebI0vYwC+grfjqxiIe3Ewvobj8HVMwXxMx/24Dg/gJnwD/4QFeAAPYgEewrexEE/gm/g5voXn8G1pdy4Qme1tjw+amLYBOZ6S/dBHsBFuwmaYg73xURyAj+FQ/BPG4mZcjY/jHnwSCzAX38Sn8C/4NJ7HLViKz+AlfBaV/Yg/YxPchu3wOeyA2zEEd2AY7sQI3IUx+BLOw924APeg2o7Is0FxkZN25EG5z30FtsKVOAQfwuG4CsfgapyIa9CAa1HO66rP8YTJTvrxD5J2JAR9cDi2wBEYgCOxL4biaByHE3E8RmAY6nECpuAknIN34X0Yga/hDDyJUaisdzrsjrEYiXGoxwRchTOxCGfhRUzES5iEv2Iy+lMWAwZiKvZDIw7CdByGc3A0zsVxOA/DcD5eUrdVeaYmeZD66a+2h6af1dLPei02xWxsjeuxIz6MQbgRh+AjOA43oQ4fxxR8AudgLq7Ep3AdPo2P4FbcgdvwBG7HT3EHfo7PYxm+gD/jLqzAF9FL2W7RB1/F5rgXW+M+7Ij52A0P4kA8hMPwMI7CN3EyHsN78D2cgR9gBn4=
*/