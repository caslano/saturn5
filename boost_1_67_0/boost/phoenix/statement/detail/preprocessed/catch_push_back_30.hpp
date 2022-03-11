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
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
*/