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
mKPljxGfRuQ6UbBcKpy7/wUjH/PqLZ8dxMGu4KKcmjT2H8VOY4dj/dCliDYRoJVurQIBBOQhZ5dJzYj9BX4GdJF/CO5wthQQjmy4r13m9UFRXbmA6V21Wa7FQthWIa/7IJvzjKa5eLXPRfkrjc0M/MEpQZfJoL869Ll4P+tArrB1k4lsI2TKdQno2Pggj+DPdyTi0Yq8yrtKVkO/3B0wW3wcKJpxZ9zfXQ2x+qjdKmq3zdMi6YpKwPUD6Pt20xg1UZ2ZqK3MU9WaMIdXRn3QpeMUX5zbzV/rObFvqYRrXgN6DqjJH3j+nL0Uy0+5TfKqbithuVKln/6uYuRxnMfyo3qfdNfo7t02TWI6SNeHlnEONcjOa5+L/aTSpimNSesgf2D0bUwSvOesk9b28WLSz6tw339FNK55pVNQXOGwnlvbpTPVkH4+qhPj7mRwqpalX2toQmX0A/EHHpD9xDgHx6SzHt3CuOTMf53za1E9mkCfGyeCw9G1v+ltgaSPmTiYk4VOtexa43UOLAbV9haTvkAvS32+8nsiH9kK9mOlMavRmg+n9ciM1mhUHyaYlXXVFE24d9P7BvQ1CH00Kf1eCFWGezeIEavndn1MhJ+xN4uxTUo+ftTvX/mWMY46hHRZ9fEVLnN38C6tlvcu7M1iQJQR3cneFeLBqLGLLL7LlWC/A7IV3UmXBm8gZ1bgmQSYEI+zBOexZzCcBPCge+THnngADnZuZuY81fXpAR4GZYDZ5ev64nQ4NCfEpvjFhQmc3pwh4GxenMRZ3YPwM/iGRzFZJusaDzTcZSguxDLhfnsK7iMHuD4GzwC3P1/RasrrG/5wYRrOzIbv4wFtQyMUatOvp7fJ1wcaIF/f7sXwNoRLAk1FeJsvMDiskYDD4tM8heHIhYbjnKZ6nuFw1mY3Ai+85BP8eUEXw+F+Lj9gP2pHrE96TIBh6h/66NS+Vw77EAKu+DH72P4kTi+9LvdxYjLi9+khrn9TC/PitXGdaMVzbHllb293+QzkDCkV8iPcN/07XFi5vO53xLi99cr6Ba4jO/TYwXiAtc0uWqPsb+3xeX7D3RgPK3a4fSNZG9938SDcvpGsjdbxNRjUZTzxevkTwzURztLeAGdrLHsvrwMOfddXjxCnzwpGUWZgblI/Pxna9IDjYLW3RKO3vIVGcX7ufAfOS8Bzz7zuY2qq4/P3dDD4eON9gBRzBD/69rHebW07XgIe/tO3eTif/j4+2NEPIhxlW6cY8HF0gt4On/dgrjsO+L5MY/7VSX0dawYcoMCGxuIfT5zE5dGVCO/KU+q1PtpbuNdc+fPxeQaKMpDo6lTIFZ563W0pXtiPVWDed/NEpL/PrS5qBfKvP7jWYjn5yFwsJytVYfqPanwrD6GeR8M4h4q32QoMNJxiaJfxM9UyiY5xXUtAw+uqk7KC66DGR1tONayrOBa/ZdusSHWZiD7qEs9pkmRUF6eRINqaGh1gErjL9LfLR25un1kBdwDHxaVG6X0MRfBLW4v72aSZrVXd4kVxYnSo7j1OI1uMs9+mqarpjbkByz0v9w3vj6zuyzkfmBayNbK2qf+WTE5+TEX3/ahuKXTT1bqzVnDNbXBg3Bj13jmjc3iZPyqQhyG9UcSrFirNqlqC1L2x58wPRuHGubKHTCFCZBRKABjyHNoPHfhmZFKZMmuED4HYK3gP8ADwflZfiHUseZFjSgAlcmdi6y3atDwols9RQ3d7zktmIk2rrFPaxrx6zybXq37lMdbMB6P4wuAuOPaSbbx9AWdbhxbJk+R/H9EnojN1kuim9R8dukF3SK673on6oVCxIJu0LIPeG07xeDT62yJkFwPNoqFvFPHB3K41jIY=
*/