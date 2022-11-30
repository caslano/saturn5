    ///////////////////////////////////////////////////////////////////////////////
    /// \file callable_eval.hpp
    /// Contains specializations of the callable_eval\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 1>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 1>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 2>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 2>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 3>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_) , proto::child_c< 2>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 3>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1; typedef typename proto::result_of::child_c< Expr const &, 2>::type child2;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1 , child2
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr) , proto::child_c< 2>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 4>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_) , proto::child_c< 2>( sexpr_) , proto::child_c< 3>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 4>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1; typedef typename proto::result_of::child_c< Expr const &, 2>::type child2; typedef typename proto::result_of::child_c< Expr const &, 3>::type child3;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1 , child2 , child3
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr) , proto::child_c< 2>( expr) , proto::child_c< 3>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 5>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_) , proto::child_c< 2>( sexpr_) , proto::child_c< 3>( sexpr_) , proto::child_c< 4>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 5>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1; typedef typename proto::result_of::child_c< Expr const &, 2>::type child2; typedef typename proto::result_of::child_c< Expr const &, 3>::type child3; typedef typename proto::result_of::child_c< Expr const &, 4>::type child4;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1 , child2 , child3 , child4
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr) , proto::child_c< 2>( expr) , proto::child_c< 3>( expr) , proto::child_c< 4>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 6>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_) , proto::child_c< 2>( sexpr_) , proto::child_c< 3>( sexpr_) , proto::child_c< 4>( sexpr_) , proto::child_c< 5>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 6>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1; typedef typename proto::result_of::child_c< Expr const &, 2>::type child2; typedef typename proto::result_of::child_c< Expr const &, 3>::type child3; typedef typename proto::result_of::child_c< Expr const &, 4>::type child4; typedef typename proto::result_of::child_c< Expr const &, 5>::type child5;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1 , child2 , child3 , child4 , child5
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr) , proto::child_c< 2>( expr) , proto::child_c< 3>( expr) , proto::child_c< 4>( expr) , proto::child_c< 5>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 7>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_) , proto::child_c< 2>( sexpr_) , proto::child_c< 3>( sexpr_) , proto::child_c< 4>( sexpr_) , proto::child_c< 5>( sexpr_) , proto::child_c< 6>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 7>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1; typedef typename proto::result_of::child_c< Expr const &, 2>::type child2; typedef typename proto::result_of::child_c< Expr const &, 3>::type child3; typedef typename proto::result_of::child_c< Expr const &, 4>::type child4; typedef typename proto::result_of::child_c< Expr const &, 5>::type child5; typedef typename proto::result_of::child_c< Expr const &, 6>::type child6;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1 , child2 , child3 , child4 , child5 , child6
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr) , proto::child_c< 2>( expr) , proto::child_c< 3>( expr) , proto::child_c< 4>( expr) , proto::child_c< 5>( expr) , proto::child_c< 6>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 8>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_) , proto::child_c< 2>( sexpr_) , proto::child_c< 3>( sexpr_) , proto::child_c< 4>( sexpr_) , proto::child_c< 5>( sexpr_) , proto::child_c< 6>( sexpr_) , proto::child_c< 7>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 8>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1; typedef typename proto::result_of::child_c< Expr const &, 2>::type child2; typedef typename proto::result_of::child_c< Expr const &, 3>::type child3; typedef typename proto::result_of::child_c< Expr const &, 4>::type child4; typedef typename proto::result_of::child_c< Expr const &, 5>::type child5; typedef typename proto::result_of::child_c< Expr const &, 6>::type child6; typedef typename proto::result_of::child_c< Expr const &, 7>::type child7;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1 , child2 , child3 , child4 , child5 , child6 , child7
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr) , proto::child_c< 2>( expr) , proto::child_c< 3>( expr) , proto::child_c< 4>( expr) , proto::child_c< 5>( expr) , proto::child_c< 6>( expr) , proto::child_c< 7>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 9>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_) , proto::child_c< 2>( sexpr_) , proto::child_c< 3>( sexpr_) , proto::child_c< 4>( sexpr_) , proto::child_c< 5>( sexpr_) , proto::child_c< 6>( sexpr_) , proto::child_c< 7>( sexpr_) , proto::child_c< 8>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 9>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1; typedef typename proto::result_of::child_c< Expr const &, 2>::type child2; typedef typename proto::result_of::child_c< Expr const &, 3>::type child3; typedef typename proto::result_of::child_c< Expr const &, 4>::type child4; typedef typename proto::result_of::child_c< Expr const &, 5>::type child5; typedef typename proto::result_of::child_c< Expr const &, 6>::type child6; typedef typename proto::result_of::child_c< Expr const &, 7>::type child7; typedef typename proto::result_of::child_c< Expr const &, 8>::type child8;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr) , proto::child_c< 2>( expr) , proto::child_c< 3>( expr) , proto::child_c< 4>( expr) , proto::child_c< 5>( expr) , proto::child_c< 6>( expr) , proto::child_c< 7>( expr) , proto::child_c< 8>( expr)
                );
            }
        };
    }
    namespace detail
    {
        template<typename Expr, typename Context>
        struct is_expr_handled<Expr, Context, 10>
        {
            static callable_context_wrapper<Context> &sctx_;
            static Expr &sexpr_;
            static typename Expr::proto_tag &stag_;
            static const bool value =
                sizeof(yes_type) ==
                sizeof(
                    detail::check_is_expr_handled(
                        (sctx_(
                            stag_
                            , proto::child_c< 0>( sexpr_) , proto::child_c< 1>( sexpr_) , proto::child_c< 2>( sexpr_) , proto::child_c< 3>( sexpr_) , proto::child_c< 4>( sexpr_) , proto::child_c< 5>( sexpr_) , proto::child_c< 6>( sexpr_) , proto::child_c< 7>( sexpr_) , proto::child_c< 8>( sexpr_) , proto::child_c< 9>( sexpr_)
                        ), 0)
                    )
                );
            typedef mpl::bool_<value> type;
        };
    }
    namespace context
    {
        
        
        
        
        
        
        
        
        
        
        
        
        template<typename Expr, typename Context>
        struct callable_eval<Expr, Context, 10>
        {
            typedef typename proto::result_of::child_c< Expr const &, 0>::type child0; typedef typename proto::result_of::child_c< Expr const &, 1>::type child1; typedef typename proto::result_of::child_c< Expr const &, 2>::type child2; typedef typename proto::result_of::child_c< Expr const &, 3>::type child3; typedef typename proto::result_of::child_c< Expr const &, 4>::type child4; typedef typename proto::result_of::child_c< Expr const &, 5>::type child5; typedef typename proto::result_of::child_c< Expr const &, 6>::type child6; typedef typename proto::result_of::child_c< Expr const &, 7>::type child7; typedef typename proto::result_of::child_c< Expr const &, 8>::type child8; typedef typename proto::result_of::child_c< Expr const &, 9>::type child9;
            typedef
                typename BOOST_PROTO_RESULT_OF<
                    Context(
                        typename Expr::proto_tag
                        , child0 , child1 , child2 , child3 , child4 , child5 , child6 , child7 , child8 , child9
                    )
                >::type
            result_type;
            
            
            
            result_type operator ()(Expr &expr, Context &context) const
            {
                return context(
                    typename Expr::proto_tag()
                    , proto::child_c< 0>( expr) , proto::child_c< 1>( expr) , proto::child_c< 2>( expr) , proto::child_c< 3>( expr) , proto::child_c< 4>( expr) , proto::child_c< 5>( expr) , proto::child_c< 6>( expr) , proto::child_c< 7>( expr) , proto::child_c< 8>( expr) , proto::child_c< 9>( expr)
                );
            }
        };
    }

/* callable_eval.hpp
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
*/