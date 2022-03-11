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
cTe/z+G6+4Iho8y2wy9KzZe+vpARsH3ECacZ5omr6XoAOfz2gD4xCK8PVU7Mf6Ej75tg3g7/7IC4j5NzoI6S+u2A26w3M3BurpdnQpc7V/O16b5xmq81f+cW+F/XvK9ovjcQNcDXp/l2Iz4Dgks2+Bm7mIEIfM3i1AlgqlfYF3HWAuxQXveJViKnnfRXvpVOlzgJPR3g6Ad4b5bRIN6iMmQYciOrZC2/XC+ep5chGxQn4IsZbzJbTkMTxEK9x3YMz1W+tvyG/H2ed6HSsY2gdeIP+4yCOa2qjTqCSNRqizZns6bWs8T2Q1cd7Gxm079EPS1iKjrwoNN40GE8aDfyDXW3kdVKH8uSu5TDXcoe0KWypA4Zaid74mA/+NCiQQnJrW8Rgb2IhN6mF9p1X6tnul296Iwu14vXjssur/dDOQJvzj0jk+In/HmzqToxFw710qO+9lLwTdJUXtwGN6rSQ0urdNtfeYPlNkvCST+Q33Z0j9JedgKMwGZCNvUqV0vvbGcW2gZLxP/LQqlx7Fv1fXQEbMCbXcA3GH4bzYL43ft4bAEI0dSIX/BjAxAaQZZ4mB+bgcEJ3MR978eVUNYTGIpyehSf/pXwVa4J8XMcnlJntTuyr8qp09AMulG3qL1AiDhKqq8bPcpt2vp8j6O6NZkJR3WhHHEsQAgWsocQpA+NtF4a8xsSni0T+uBZ+sTYMAjmZznET1JYmVCqg8e+Qx08ruTtjCt5e0AdSyVvJ5S8e5KVvJ1Syfu7dLuXOCKITVS6AC7P7+xjjaXHWnuTFL1NT59QGBgRLYLz+jzdgcPW7DZKNpkdANySqc13avPd7EXOLj6Gjtr8TDjwFCfm9xm7m6wYko5XsWH2K9sfZa3zDyhBtBjndt2y3IbDVG6Rm9o3y6nVuNV0U5fePMmz1+e+T1imaD1UhOSZRZeFS3qUSkJDGyLHadlSgZ/rRY6wcPvFmIOgNhzhBvc8zaan0az5+pq8iKNjocHwbFVSafZiNu0WB1zOzEMzG8Xm9f06MNK1H/VBxE73H02WzfmOo0lpplAGS+L40eRlH6BHCKOUqlWhnhqHVmOPn02ecag5Ojln9/u933+oKVUseCgP0QAMhkMeDFQsLxCklSP2QtxG2LoLIPVHlFRs55ImUkkP2rUlcOU3n/0Qx4Msdf0lgyOWmSekOB/NhR3Enrf72A5iCE5HaYhaftAnj0e/jE0Xn+Bjq/jVAjO00i3UXUwMLdrRMsSSeO1OM9rSHjHEgFnEZ2YAo/2Heg0x+1Wp/WU24l5uBJYCFfbXNlkYsrJVI+fTu8TvKKe+Q4xM5L3+Qsp7uZnXGfU5xeJ4XoznHrGbsztl9ttk9oN/kScX5mqMsGdRt0U52/Wq1x1usPvFpDI+DHHAD6xmZYOl84nq2R3ZqQwL6FeUCh8n2EODcbSisf4NApLGyiP018hyP8uavakdXxGNVdmCszMjy0kvcWh+ojVu2YIopuMh6/QLK5UVvnu8ZZ5eNEm++XI23kyyzEu2InGUKJeXKBeVlChjw8KujAwLhzKEIJ3dnWeHHLGhIXtscCgllhZKj6WE0uayTuHAAi4pUc6nAs6ma3iJklFi5s2lPHaEppobywi5YyepsK/NvFROP+aa4wilYp8xrvQb9xOWfvJ5CCq+z8nl0dv7/hcnl3/84x8HD/Bd6WTflY//re8MJ5ffk/AfbycSJpxcmiOLwN/5O0OO2/SmE5+4Vm89cSijuVQsKKUpy98ZMWouy99XFtlZdalnlqN6vF5h13PO0nKa8XQWnu4YYdfuaLZPD29zevYu/cC05RHn3Z6k4EW4QUuDa1cL45rX9hHQNRDitf/C615Z5JAIgsijzPpfIihg9E9St+VI/j5tThdhJc+H1ami5TYI1pyebUtthKQ9H6qFBQG7MpGo/4Cj5qx8oA/95il24Me1tLxmhJucngoiawnbiN1+gIjdMo9KDDi1gKPj5+B1ZtmJfImw0gdh03Knp3WZTaNmVjvvNZxBcQflCoYsfmqoGPI/UF9wWMLb4et31TXIXu2gZDZCONWiyQstJotygXj1DlPf4F700tdlhXIc0dXyRN8qxGkpITtOyBWHJp2EnE9jnccI/RheR0G5Y+m6jg/BC9U4PR+5HjvIzaNdxRWFEFPvzeu5t4EbONu21S+U38mG6Y15hMq3OyHiYX9JNQ7bwAbaZAOHygY6xbvvcQNT0EBnvIF2UdzfwBQ00EkNPIUG3igbyBUVeB1Ln+qAQxgX6//kNWpzHKgaYhW9l6pNmo5hEkVT3rxGmhXk/bjjtBx1Ih3PpW+/C3+Sbtu2tccW7rFXp4bstLTegn6CZ2tNir7V1kSz4mmliS93wt3ho19C8dqcpQ2zCC5mOe7d6SylqSaeIegXl+/mGvVdec00VjZvJ77STIqiJweMVi7xoT/sHyk4YmynkUqTI3XkNh4pIda28EjZMVIiPlLpYsypxEjZMVKCRqqXz38PnDFSgMEStNPbOY+gCbRFkVOrcIifvWwiVygd5h9uSrNnjXAXVNiVS4L5RkGFoyabxzGbx3Hn/l6jONzo9NSYYP01VT4v4QT8W/Z5g7FZTt7YZ8RcYgH9hJh2+Q3R3PSB8gfFg71xoiGhWAR3rPHd+9e+/t2bqIqNWJxdLyYUzzKprfqsRazV456ft1eMpwbqs+6ju3P4rpLuMvluId0N5rsFdGfhuzvo7vg+3M2lu06+u5XuPqG76KxCDu8o9b4miMMIueN7KcnWUdyb1NDOm79NZlTj8JTwTrTY7o/Osotd/+g1flHsIHwz/9spidB6KFX8mOhQDG5GiOgtq1/c2yvJg70EPjYq4hmTxmJqgOOXfvIC1O6ziRM67DkGTggihwsDjKnyjXDPYNcjjxGqMMZFjt9rB3+mj4RFHsccNGZndyzCRzUz6ssWMQIa+ZX2ztnjdV82tuEesZ+WaceNnE46BvVP7CgA+uH7TK3C3nFJ4nFSxzksxInXs5LryelwJFI4O3DMphdlwhqRY2lTCS/DpkW5+WUsOcVtbFiObIuXVt5Lz7ErXRuLqlwbZylb290ZWxHq8R47ThIOEjXGKStDiWfKUykf9FklGm1vO5VboBPijuysKco/TBhi5T9pKj1FJa4oYpvqs2YenznaYVXH8KutpxFzVt9qTMquXATxqeqAaZi7kKCeCvF4nUs367MmyYKXxQteLAuu44InuaIPc8ETEwXTq8qkgn+aVDB/vKk/fYoi009BeqtM/+B3N+RRhMxT08BnKEv0tPBdbkv+YX3PDMNfSFjlrkiFU7kg7qcDgrp/A2elhSzyjb+/GZEK98CUm2RKazxlfwPSbIcNL6u/FBZ43Ut/L6fUHZvQP+N1POO5sdHy24SYG9R8Qbnb9eutHFRvnN6jNwnrOkI8mZZP7rG7G+haSNfP6HqWrtfo2k3XF3RtIah9j64PAb3myiPEys5Ci90ERVqx86WJijNcMwlj0b6XnvWiBeGqbkuZOiJcM96iDKmcS3giOmuB2PkesHK2VnyHXpSjFU/Qi3K14inwsFOcqRfN1Ypz9KJbteJcKkAr9utFlVpxoV50n1Y8Uy9apBWXHC/KTNGLxmnFhBTH04NdK75ZL1qYv/P2gpJuYhyKp8YG1/7IadDcabdMLZhVomRGi9hOxHWCXhVP0otKtOKJaCu+TMCXr4/jy3giJrXicdqSuU3Ft15G/W5KX2CBtU0CTYQ7FzJTabcElVQxk0jOARSs0plMvHL0XOUQlFxCd0S9a7Hz7P4ly3ygLbHdibNAqvyPcL7AM+Y3o1lFtwAzBPHdmNPHyvCcsrvbNH2w6+kxW7jZQAhdQsrO+lNAQ7c/y4LQBuks4g/SxuYPpYyGdId+Q3f+PtjebPMcVAQBQ43d9cRWz16lraAaYFFQnel6Ytvpd5d/kjL4XdeGnaWsHEv73lQaHMK+RL46oB2++xtwB1CpE9cSMhVvU63b3Amm5INnwG8SRZnf4FGdrqeBE4EOR1E7PMeWnigody79Kr+hYD7VTohS+Y8Il5n80HU7e2l3KoveMgGh9rq/Jg5tfEDkzUbUNmVMgNP86d1ePLnKpCE52NBTNH5FVFfNfpNXepH2fXHhs7yn0oa14nMam+ueMTcs3ZuTb2hEFXhztaJMuX0xuwgeWqvJ1mpytJrceuzAWtEErWaiVjNVq5mi1UyizmtFhVrNTK3Gr9XcrNWUQHpHm97teY1+pur+1dRrIPLHrUzlyrcpotl8OxfL03xrE381396he8fF39rFGn5L5KVWtGATonOVRWcthIqa2Lenl4ZmVuUOKEz+XT7cxwRIvXxYRA80PvSQv3P6iaJMCKF3QIe7RmkqqloIFn7WUm0LULW2pY7/ruS/gDWtZpxWM15J01Yx5kCwKdqQxEXAiTvEh2tZ6FMJyrP+FQxn1x8yKNW4aBRe3Qw111BzzghbLX6OjZuIAiOrGcZ7Mql4s8/czvmR+Ms/nuAqlqxN2tXhS/2yynGtw/tX1qWVd2QlVlYETkQm93vLaIm5sSYVR0W5ccHNz4HBqkjyvD0gwI8D+oOQ+T3H5WSCLIes38h65bk4wyml1Of+LMmB5QCHjLXVjvvS4c3yaPXgytRCy3LRvYvmQC93RmcYwXBPxpIOfY47ej1t/ecs+ZdenRk2Ri35AHv5Sc+SPQSB4R7Pkh2at5Wak/pEDySpnYBH+HFsvcmv+dgr9hwcT4il72VY5mlp52+brwXstyPKenpl0JK+PKYjZMcOiLyrHpJO8qXIu1SyWq6Njr+hkXd73n1wUPhCCxif2EQaMNdGv3M2/RmMPw78SXNtLEyZ7S+N+nqEC7Pi7QGj1gcadUd/kO4zohigEvjwToylOsyshtsnPqaVKge3zRxcGu5/St1rPmvhUK4IatqH2gTXhu68XDXA4jvZESZRK5HDqjnmy6mCUnjFEKEWGiOIDsGauwPB0KB5UbVV7z22br7eGLeVnF01YDonDoj6JP0x0HbmPRAx2NcC/BEFjaxxBG7TYLdRHSsLRivOKxP3rGB1/dS7NVssV/cdoBbkH/aXBflE6JpTiJFlZN0sRwQFtdGi+YW3ddyylUW5urdb3/9arvDuy7BoRdk00IOKsmmAtEDOoIocv7jpFHvpPyvEtpcQWmMV6Q5tKCyzi+yxVO0cItQAr2KsTHs20h6RAm6ZdpabE2fGBtNWsJO4ZG0WQ7n4vK8/RyfnGGfmYMPvImc8B71x6mkZRXY1g7Z5mh1iU2h2itwZRZlECMODiJvfZeY3FCYcvh5djAFOrDr/mf7uK6Gxnn+YHk6K7b8gdFzsJF4kWnReJcbXL/YSc+0X12xn+RtxZZ7UzoPD3a66S3Ea52sulcq/6wFwE/uHdzif1dX7WQQ+SUKZ0L31PLybtaIcqgZRWVNXVuTGLtdvccNLJbwDl/nFo0TZY8Wf722NpVOxMyk7rTDaFk/vPK955axciOTFht7+SVnPxyUYyO+YlBa/+IVMy0Pcwmm3yrTfPSnNfjE3KUcz53jMzPH/ZVIS7hPuUCXUV06hwa/vBO5+6n9Y2yb/uPZmwykEGt1Of/0IIP72ZpzqvLmd/zbz3938t4X/HuC/rTBzRuxp8e5NfRzC8pGtvQbHKvH7OUp8UwTlQmgs7tvRS1Mc+Q9qEDf+DtwnZfjhjUSTNInf/o9UBOpvWsr/D02rxp/LzaZ1Nnxv0977e1LTLqZc3LTmG7hpfb/rl2nXdsKWvB+a8xsAzlqE649w/RGuP9LKf9v4bzv/PcK9aOE6jsDoKfIV7omWS2mCdriJwTc8mISbsKNBUtgngTmDoxoxaosLJ+vraS9srF+Kv/rW8AK7pcnSSg9cAtPm9qY0vGDRqJFVSEgMiNkMVwS++UAS3/zGtDP4Zn0rUVIaH76W2MHo5u8rKIVwY7pdd8ye7Td+uZ2a1FgPNNwvnIV15XGOrnuW5DqyaYk6+5X9q/7NUTST5AzwagzRp+7wG6UO2j0qyqk4Kie8zI6QbMVUXYBqa4CUaIkzNpZNEHKlCYJl5Ai3WLoSOhmYaQj0qfp/VsxvFH8qSogdp0NgzCETqY5fwmgvfydxV7/bqm+NH1SZ+GrBGfiK2Lit8HF+jNEMPA3DA3x3WdlbfnWUWzy/oc8oGDOObpV2hPLwBwa6gYdLjkNfAOFzPAc4BVY34wTX26CVN0fVzdHqtfAhcGjO5kPlDaH0eeBj3+Co5C1lWvl6rbxeK99OSY+tM2u8Eorw1bufQZ26I7pkfCA6Z+3s6JwWmpBSYhkfwtDDGWkxjNLmE3AxBrjt/iTYorGNFo8PT7HwPBX5xQOg0n5kt3Cgyr0CEbxpwD4N9A/3hUnDPeSRPtaRhrrhbCeGG87JpPesyV54z7LXj/2CFnLLrxPkNg7qmtImjgQAAiz90z1tF+++nS4NwBBRSUxuSIdN489+Y642qfZQUOOuuThiVE3y1LirEc8vaq+nJhP8WRhapHHcbHsxfV96kBDnLEfIIn5LJSO0419mynb8ZCFxIyVox8lQpvjNNab2RhchF7XPs4c26yd+DjdboEZDLODZI16mN7grskvikrYIwp+Q9tJC6veVhECp0VtyxL3UfG2i2ESVxPe9UnQu6u0D8xTemiPGUhLKnKMzM5gFR7dznNpgPk92a1YzdmrStukM39Vj4TU8HluT5u1WLiH46vGjUEQHwLgVY9x8PUk2J+HqbovaOh8fq7ekWyoS6hXjw3e1Wpgkym+IVrcd+5P44Ic0iYscoJyoiwHRc/4pg0XG6vBnCglqm7ytDrAEqsABP5jVPqayxt1zCgwnAqgFt7SMGuEOVG6mv+JXtPIClWtwu5Ju31lNd8FKBc/QGqpcQHeVhXi8h1NOxG0F3QYrM3Fbxm97AF+wAdwiRqLoZjxPoefw9sLKV+ihcjXeQI2/UsHjXDyO4rxTcevktNkEAjT5fgDhTb9KCCkBfnHVcugz0Vw/CrZ7Vg6rK30MqGQhI3Ghm9ItQvwqzo6wcwXlkoB+vztyvGYsobGLPDuqz9dLnXrmzyP7FJs+O9czx6E4Cz07ln5shsHFtB4X466Po6EAQUNl61mZbrEr3MfuV2lhXSD9RsKSFjgqXJVrUYb1v9ObxZbrThnJwgcnmH+CDV68l+mz3HBwH9lJrTpcNc5zqDoXsS/tT1JpNr0wFz7yR8zwHEKr5t9eARgTv5zeZ4R7DeVzSv0VUu/a+nGKMcmh+bqlT7s8tK8nv2HePE+P0lRQnKtso/lnzkSCoFwobhpDT4W7+i8ow9cdHme1QBeYuYe9Iu06eDU245/rHLmPPi69SRLOoqsQWg99lsXELRI/01e5FFq2i00dScQ9YNYgvlVdmnSSPOjqAbJojm298JcZMvixSpSSuOxxXozi0hlmLOuOemy0jgBcSFDjoTg86JE0i+7tKljUrboQuHprl3hwM445Yw2V7aNgkdElsuDDw8cMYSGhDGtR7H25wHHOP23Cs2gotDPcmzpOsWDOD3FnV+T4MkzOLfk7Qym3RYusSYdpIyYTgN08OQVHEDSmomEZoxaCjT4Z3RDOFA5y8EWneG4LTAr7RPZk7jArGjnR5Q8A2fevll12uOruYZkwHwG/Snl4SdIDuun/mG0HL6z0Ex8onrgqjgFZf22Pq+7sFOh8PuewdIyAlvEamVOMjmd7BdnKk7OlIBt7/lj8JGWDvh0vdGT7RAZquLASDufFhcnZbMj2Z2TL+QVlW4dshWa2P8WzgcoRX05KymZHtsXINncpZfsJsk00synxbJVoZH1ytlRkuw7Z7lYpG2tLZ5rZpsWzrUVttcnZ0pANtvti862UDUQjIyVkS4tnW4TabkzOlo5s76G0IT7Kxl5nm81sez8yszVD13tEcjYHsiGGvJh2A2XjKM+rzWxPymxjK+ElQLTlJ2UbRBvXj8SbhKJidzIGRPrKeHrIbsQryekHU/qrxeEvKP2VjCaRfopMf34ljIDF0uT0GbwxXvbvdNZr1LtMidqct3h10CuxZ1UyZex0JFPGRB9q0e4TUrcearTAaa46uLQv08dAeTUQSoUy9H6/GH256SfznqBelCvNkKM9lBf8nQM6X1xSNIJ3fpECpN3DVjH8PrzVETTud4imDekWk+q06fBgu1dkFid8aVI9r10m61F/N5+Qc+Ht3C+W70yvTGgh1lY7ofqrXgLB1Z8ug85sN7amMTWmyq/pcBn2+LF0c9Muh9TTXv+oD75uH+0/D8se4WZ1mxrC56liwcRTLPAiBPg/008ZYlWUdhai9aYr2vQqbfpSrZYlcrUskatliVwtS+RqIW1rDM2tP4kVL7iCQNS3RnTt6TMklcFC4WcrGa1C+2fspbIupDpnb58hrorGtzHs41xisn4DsOs758Bnu2y2YJmc1ylPjCiLa2OzVqRos6oY5ZoiGcp1vGhuNkzOEM59NZ9iEc8CBF61brjb3LEChP+PinEXsIbWIJBO4m0qnrbnFPEG3TTq0xX6kp5qsaQwtFH59Rj1Rt1qrF2KHdBsuLmfseLr/VSJAm1d0TrhlNHfJghviHgUowdzfRzkiQMB7hHXXi+VxML16JXkpH5cSxwGZvwOvdgR7jlbSQ332NRbQl3G1UbWkwR9L9mV6ZWgZIyrRSb7pFeuCKVwH++TTnPAWK2VTnNGhSyhlEr4f0jsYh0Pg8Ch2r2jTyUOVzHet4xJGm/4b6Ch7WfLXjnVv9eNmZjMlkG7TJwN7YdFdlo1OQU1ueoo4bm1zzheuNCKUAHz9T0VxtpWnuP5hWahoBgop3JVQPxrXjzzRch8njhdZmYeJakOKC8kE9iTJGUvyXLxB2QvhGLUIBhxiulV9MyAYs5PdBUgodQvHlnSR13tEfv8p1g/rlH2/JM8jg7wJ/oxNjDQxP0PDSUS1nzzPI1d+AXc0xYua6ww4adZ7KGCzbEC7B0Vn+/uk6elZvSDPSLnEiaZHHK0ifmUkRzFx3MpZclUopin6BwRhAq9TP8Nn7oQFTdIL5gdMIK5sUHG4ip9WMCYPY7W1JAQGpx+CvGVYjPodsvFpyQWmnSiaC7gR8nTiyqpKHt4wSI2GWEAkAB69SUS9KnhQ2iN5vNYxAG2tDQofNQm4naq7Iy+pgXEK8S6bCn62GLxNMHnU9TXUxoMBiSv1aCkAu+MFKPm8qgM/Fw=
*/