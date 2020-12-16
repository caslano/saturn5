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
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 31>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 31>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 31>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 32>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 32>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 32>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 33>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 33>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 33>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 34>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 34>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 34>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 35>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 35>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 35>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 36>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 36>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 36>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 37>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 37>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 37>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 38>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 38>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 38>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 39>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 39>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 39>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 40>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 40>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 40>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 41>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 41>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 41>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 42>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 42>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 42>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 43>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 43>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 43>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 44>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 44>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 44>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 45>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 45>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 45>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 46>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 46>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 46>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 47>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 47>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 47>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 48>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 48>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 48>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 49>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type , typename proto::result_of::child_c<TryCatch, 48>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch) , proto::child_c< 48>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 49>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type , typename proto::result_of::child_c<TryCatch, 48>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch) , proto::child_c< 48>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 49>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type , typename proto::result_of::child_c<TryCatch, 48>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch) , proto::child_c< 48>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    
    
    
    
    
    
    
        template <typename TryCatch, typename Exception, typename Capture, typename Expr>
        struct catch_push_back<TryCatch, Exception, Capture, Expr, 50>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type , typename proto::result_of::child_c<TryCatch, 48>::type , typename proto::result_of::child_c<TryCatch, 49>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch) , proto::child_c< 48>(try_catch) , proto::child_c< 49>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), capture, catch_)
                    );
            }
        };
        template <typename TryCatch, typename Exception, typename Expr>
        struct catch_push_back<TryCatch, Exception, void, Expr, 50>
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
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type , typename proto::result_of::child_c<TryCatch, 48>::type , typename proto::result_of::child_c<TryCatch, 49>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch) , proto::child_c< 48>(try_catch) , proto::child_c< 49>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_
                          , proto::basic_default_domain
                        >(catch_exception<Exception>(), catch_)
                    );
            }
        };
        template <typename TryCatch, typename Expr>
        struct catch_all_push_back<TryCatch, Expr, 50>
        {
            typedef
                typename proto::result_of::make_expr<
                    phoenix::tag::catch_all
                  , proto::basic_default_domain
                  , Expr
                >::type
                catch_expr;
            typedef phoenix::expression::try_catch<
                typename proto::result_of::child_c<TryCatch, 0>::type , typename proto::result_of::child_c<TryCatch, 1>::type , typename proto::result_of::child_c<TryCatch, 2>::type , typename proto::result_of::child_c<TryCatch, 3>::type , typename proto::result_of::child_c<TryCatch, 4>::type , typename proto::result_of::child_c<TryCatch, 5>::type , typename proto::result_of::child_c<TryCatch, 6>::type , typename proto::result_of::child_c<TryCatch, 7>::type , typename proto::result_of::child_c<TryCatch, 8>::type , typename proto::result_of::child_c<TryCatch, 9>::type , typename proto::result_of::child_c<TryCatch, 10>::type , typename proto::result_of::child_c<TryCatch, 11>::type , typename proto::result_of::child_c<TryCatch, 12>::type , typename proto::result_of::child_c<TryCatch, 13>::type , typename proto::result_of::child_c<TryCatch, 14>::type , typename proto::result_of::child_c<TryCatch, 15>::type , typename proto::result_of::child_c<TryCatch, 16>::type , typename proto::result_of::child_c<TryCatch, 17>::type , typename proto::result_of::child_c<TryCatch, 18>::type , typename proto::result_of::child_c<TryCatch, 19>::type , typename proto::result_of::child_c<TryCatch, 20>::type , typename proto::result_of::child_c<TryCatch, 21>::type , typename proto::result_of::child_c<TryCatch, 22>::type , typename proto::result_of::child_c<TryCatch, 23>::type , typename proto::result_of::child_c<TryCatch, 24>::type , typename proto::result_of::child_c<TryCatch, 25>::type , typename proto::result_of::child_c<TryCatch, 26>::type , typename proto::result_of::child_c<TryCatch, 27>::type , typename proto::result_of::child_c<TryCatch, 28>::type , typename proto::result_of::child_c<TryCatch, 29>::type , typename proto::result_of::child_c<TryCatch, 30>::type , typename proto::result_of::child_c<TryCatch, 31>::type , typename proto::result_of::child_c<TryCatch, 32>::type , typename proto::result_of::child_c<TryCatch, 33>::type , typename proto::result_of::child_c<TryCatch, 34>::type , typename proto::result_of::child_c<TryCatch, 35>::type , typename proto::result_of::child_c<TryCatch, 36>::type , typename proto::result_of::child_c<TryCatch, 37>::type , typename proto::result_of::child_c<TryCatch, 38>::type , typename proto::result_of::child_c<TryCatch, 39>::type , typename proto::result_of::child_c<TryCatch, 40>::type , typename proto::result_of::child_c<TryCatch, 41>::type , typename proto::result_of::child_c<TryCatch, 42>::type , typename proto::result_of::child_c<TryCatch, 43>::type , typename proto::result_of::child_c<TryCatch, 44>::type , typename proto::result_of::child_c<TryCatch, 45>::type , typename proto::result_of::child_c<TryCatch, 46>::type , typename proto::result_of::child_c<TryCatch, 47>::type , typename proto::result_of::child_c<TryCatch, 48>::type , typename proto::result_of::child_c<TryCatch, 49>::type
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
                        proto::child_c< 0>(try_catch) , proto::child_c< 1>(try_catch) , proto::child_c< 2>(try_catch) , proto::child_c< 3>(try_catch) , proto::child_c< 4>(try_catch) , proto::child_c< 5>(try_catch) , proto::child_c< 6>(try_catch) , proto::child_c< 7>(try_catch) , proto::child_c< 8>(try_catch) , proto::child_c< 9>(try_catch) , proto::child_c< 10>(try_catch) , proto::child_c< 11>(try_catch) , proto::child_c< 12>(try_catch) , proto::child_c< 13>(try_catch) , proto::child_c< 14>(try_catch) , proto::child_c< 15>(try_catch) , proto::child_c< 16>(try_catch) , proto::child_c< 17>(try_catch) , proto::child_c< 18>(try_catch) , proto::child_c< 19>(try_catch) , proto::child_c< 20>(try_catch) , proto::child_c< 21>(try_catch) , proto::child_c< 22>(try_catch) , proto::child_c< 23>(try_catch) , proto::child_c< 24>(try_catch) , proto::child_c< 25>(try_catch) , proto::child_c< 26>(try_catch) , proto::child_c< 27>(try_catch) , proto::child_c< 28>(try_catch) , proto::child_c< 29>(try_catch) , proto::child_c< 30>(try_catch) , proto::child_c< 31>(try_catch) , proto::child_c< 32>(try_catch) , proto::child_c< 33>(try_catch) , proto::child_c< 34>(try_catch) , proto::child_c< 35>(try_catch) , proto::child_c< 36>(try_catch) , proto::child_c< 37>(try_catch) , proto::child_c< 38>(try_catch) , proto::child_c< 39>(try_catch) , proto::child_c< 40>(try_catch) , proto::child_c< 41>(try_catch) , proto::child_c< 42>(try_catch) , proto::child_c< 43>(try_catch) , proto::child_c< 44>(try_catch) , proto::child_c< 45>(try_catch) , proto::child_c< 46>(try_catch) , proto::child_c< 47>(try_catch) , proto::child_c< 48>(try_catch) , proto::child_c< 49>(try_catch)
                      , proto::make_expr<
                            phoenix::tag::catch_all
                          , proto::basic_default_domain
                        >(catch_)
                    );
            }
        };
    

/* catch_push_back_50.hpp
jdGrv6YldolOT0jUdenetXvXwNguc9J6BHbva/lbRlCfLuqbebro9NHpcea/87cIY3fltStdU6I5PaCc0xpY381fuebckOubr0e5WRybEJOakpYSa/TvMLGj/3gDbzxNmJ+QHOc/jNeBJSTqU7n+F1p/tReHVPJumm1ybmw8Ic9kd/vBh32pFUq/ZPdJk0Ijh00Oj4zS6SLV1w/xypM0Y4rpJcpVeaenZ315H4f5XWoEs5A3flvf/6T8Z0os2vquEG+GKe8QZaDlXSHVPdTxolLjTPNsxjBfxjNEpaaZRuRHGe6vjivDlbFN76uwll/O5fSW8veU8uc5lF/ezvM/Vn7uJeHH9v2xP/rw30qb8vPGLMflX5X33SR4Xb/82vduXZA8LVDyJJaTpxnWPFlf1a28nykl1ajXVSYvLAV+jijz0XwusHyuUT/P9DuHyuN6yXv2nOe1j+R1ofQZHiZ91Qfj35T6e8iUV2tlKauQ2+9775z1nbTKCmheV+Qdhbz0RvteHX8qIJGt3ijz8kOjsq4kWt979LOPqTzMnnEs70Czvj+nzMn75TuQYJLeSBcLef85yyicsivn+eIoq/YdW3UZV3nPcgPNO9j4zJtu1GkvkNZkph2jbH8yrY/mHU0x0ZFkhRdtSl2b329zQsal8KbPHVbzWbYP7ftuOshzVifJ+jOeuEKZS1bbL5PYhGTdjd9X2ECWyS/WenO1Hkt9uq4/+/UnX/I6RvI6kviNdMLW2Oc1ITnBWPm8apax03d3X7bLk/Z9UqdqqTP0clfz5InXlDbRIU/K1KzYVajDnytRh//KtrCepi549fsNl9cFKeQZWV6fEO6+1FW2fd2YUqn0+9hdb+/yLi0n9eSjeZeWMlz7PmQ/zfimd6ZJWs3s2oNyu/bAsfzqtnZOKZ/Uq7Y+dHXUwoTJ9+c4ReojcJ1dffD9kWKYV+nvSyVPujS1PfKUbS8tNcbme4L73E0/BlkWiZJ2rvO0I9VXqlf+Hfku8uBQRwyz3e6ljYyvo9yjr/blO23Kk9S5Zlrmr5TJpk53SrmaS502lTYhcL1DuZRN4YZ16mzbk3d2cU+dq3dqVf2dSM7fweXqXUmu3m3l6h1Krt4Z5erdSq7eOebq3WJVf1eY83dMVf3dX87f5VX1d445f/da1d/N5fzdX67eweXqnWCu3mnm6p1vrt5d5vqdbNzHzPDz+QXVohr7Zh8/9t7Mrw9tedj1O8HUa2tybCP7BXvtrq2dlz6R32FjLMPmeAnHYrn2XU4yn94yH23f5CsynwrsiVct08m+NYQ4me6M9NH9DIPxczTne4ZMt8BJvt3lWnc1DENfnIqNcRo2tdzjIPumss+61+4eh/GSfhgOwok4AqdgHN6FyTgV0zEcl+Dd+CBOx/UYiRswCh/HaHwSdbgN9bgLY/E0xuNZTMALOBO/w1n4Iyahsh+SjA0xBSehAVfhbFyPqfgspuEuzMByXITKNefF6ImZ/OuCS7AHLsX+eD8OxmWWvuSy34iTpN61fQwaSH15YyNshAPQR+rNF8egH47Fxjgem1iWq+zr4Rgny9Vf5t9a5t9G5h+AI7Etyr05sn+mrPvMx+7enN0yn9dkvd6H/vgG9sGDeAcelnwXSn7fwih8G+PxCGbju/gIHsPH8H18Gj/AF/E4HsQP8Sh+hCfwBBZjEX6FH+P3+Be8jCexljvlkeX9CarPeJF9LNn32mv3jJdOUr7OOAi74gQMxKnYHadjD9RhX0zBIMzAfrgQ70DTPclSzsG4AYfgFhyGOzEEd+MI/ARHWtYX2ffBMCfry5+kXdiMnvg4dsdc7IdPyXJ4GkfjVhyHz6C5j3uuzN8g89f2cV8=
*/