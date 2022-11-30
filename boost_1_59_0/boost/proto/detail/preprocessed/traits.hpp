    ///////////////////////////////////////////////////////////////////////////////
    /// \file traits.hpp
    /// Definitions of proto::function, proto::nary_expr and proto::result_of::child_c
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 0>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child0 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child0>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 0>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child0 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child0>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child0;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 0>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child0 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child0>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child0;
                }
            };
        }
        
        
        
        
        template<typename A0>
        struct function
        <
            A0
            , void , void , void , void , void , void , void , void , void
        >
          : proto::transform<
                function<
                    A0
                    , void , void , void , void , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list1<A0>, 1> type;
            typedef proto::basic_expr<proto::tag::function, list1<A0>, 1> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0;
            typedef detail::if_vararg<A0> proto_child1; typedef detail::if_vararg<A0> proto_child2; typedef detail::if_vararg<A0> proto_child3; typedef detail::if_vararg<A0> proto_child4; typedef detail::if_vararg<A0> proto_child5; typedef detail::if_vararg<A0> proto_child6; typedef detail::if_vararg<A0> proto_child7; typedef detail::if_vararg<A0> proto_child8; typedef detail::if_vararg<A0> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0>
        struct nary_expr
        <
            Tag
            , A0
            , void , void , void , void , void , void , void , void , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0
                    , void , void , void , void , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list1<A0>, 1> type;
            typedef proto::basic_expr<Tag, list1<A0>, 1> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0;
            typedef detail::if_vararg<A0> proto_child1; typedef detail::if_vararg<A0> proto_child2; typedef detail::if_vararg<A0> proto_child3; typedef detail::if_vararg<A0> proto_child4; typedef detail::if_vararg<A0> proto_child5; typedef detail::if_vararg<A0> proto_child6; typedef detail::if_vararg<A0> proto_child7; typedef detail::if_vararg<A0> proto_child8; typedef detail::if_vararg<A0> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename> class T
              , typename A0
            >
            struct is_callable_<T<A0> BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)>
              : is_same<A0, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 1>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child1 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child1>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 1>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child1 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child1>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child1;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 1>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child1 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child1>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child1;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1>
        struct function
        <
            A0 , A1
            , void , void , void , void , void , void , void , void
        >
          : proto::transform<
                function<
                    A0 , A1
                    , void , void , void , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list2<A0 , A1>, 2> type;
            typedef proto::basic_expr<proto::tag::function, list2<A0 , A1>, 2> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1;
            typedef detail::if_vararg<A1> proto_child2; typedef detail::if_vararg<A1> proto_child3; typedef detail::if_vararg<A1> proto_child4; typedef detail::if_vararg<A1> proto_child5; typedef detail::if_vararg<A1> proto_child6; typedef detail::if_vararg<A1> proto_child7; typedef detail::if_vararg<A1> proto_child8; typedef detail::if_vararg<A1> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1>
        struct nary_expr
        <
            Tag
            , A0 , A1
            , void , void , void , void , void , void , void , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1
                    , void , void , void , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list2<A0 , A1>, 2> type;
            typedef proto::basic_expr<Tag, list2<A0 , A1>, 2> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1;
            typedef detail::if_vararg<A1> proto_child2; typedef detail::if_vararg<A1> proto_child3; typedef detail::if_vararg<A1> proto_child4; typedef detail::if_vararg<A1> proto_child5; typedef detail::if_vararg<A1> proto_child6; typedef detail::if_vararg<A1> proto_child7; typedef detail::if_vararg<A1> proto_child8; typedef detail::if_vararg<A1> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename , typename> class T
              , typename A0 , typename A1
            >
            struct is_callable_<T<A0 , A1> BOOST_PROTO_TEMPLATE_ARITY_PARAM(2)>
              : is_same<A1, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 2>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child2 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child2>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 2>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child2 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child2>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child2;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 2>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child2 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child2>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child2;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1 , typename A2>
        struct function
        <
            A0 , A1 , A2
            , void , void , void , void , void , void , void
        >
          : proto::transform<
                function<
                    A0 , A1 , A2
                    , void , void , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list3<A0 , A1 , A2>, 3> type;
            typedef proto::basic_expr<proto::tag::function, list3<A0 , A1 , A2>, 3> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2;
            typedef detail::if_vararg<A2> proto_child3; typedef detail::if_vararg<A2> proto_child4; typedef detail::if_vararg<A2> proto_child5; typedef detail::if_vararg<A2> proto_child6; typedef detail::if_vararg<A2> proto_child7; typedef detail::if_vararg<A2> proto_child8; typedef detail::if_vararg<A2> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1 , typename A2>
        struct nary_expr
        <
            Tag
            , A0 , A1 , A2
            , void , void , void , void , void , void , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1 , A2
                    , void , void , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list3<A0 , A1 , A2>, 3> type;
            typedef proto::basic_expr<Tag, list3<A0 , A1 , A2>, 3> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2;
            typedef detail::if_vararg<A2> proto_child3; typedef detail::if_vararg<A2> proto_child4; typedef detail::if_vararg<A2> proto_child5; typedef detail::if_vararg<A2> proto_child6; typedef detail::if_vararg<A2> proto_child7; typedef detail::if_vararg<A2> proto_child8; typedef detail::if_vararg<A2> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename , typename , typename> class T
              , typename A0 , typename A1 , typename A2
            >
            struct is_callable_<T<A0 , A1 , A2> BOOST_PROTO_TEMPLATE_ARITY_PARAM(3)>
              : is_same<A2, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 3>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child3 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child3>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 3>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child3 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child3>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child3;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 3>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child3 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child3>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child3;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        struct function
        <
            A0 , A1 , A2 , A3
            , void , void , void , void , void , void
        >
          : proto::transform<
                function<
                    A0 , A1 , A2 , A3
                    , void , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list4<A0 , A1 , A2 , A3>, 4> type;
            typedef proto::basic_expr<proto::tag::function, list4<A0 , A1 , A2 , A3>, 4> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3;
            typedef detail::if_vararg<A3> proto_child4; typedef detail::if_vararg<A3> proto_child5; typedef detail::if_vararg<A3> proto_child6; typedef detail::if_vararg<A3> proto_child7; typedef detail::if_vararg<A3> proto_child8; typedef detail::if_vararg<A3> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3>
        struct nary_expr
        <
            Tag
            , A0 , A1 , A2 , A3
            , void , void , void , void , void , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1 , A2 , A3
                    , void , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list4<A0 , A1 , A2 , A3>, 4> type;
            typedef proto::basic_expr<Tag, list4<A0 , A1 , A2 , A3>, 4> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3;
            typedef detail::if_vararg<A3> proto_child4; typedef detail::if_vararg<A3> proto_child5; typedef detail::if_vararg<A3> proto_child6; typedef detail::if_vararg<A3> proto_child7; typedef detail::if_vararg<A3> proto_child8; typedef detail::if_vararg<A3> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename , typename , typename , typename> class T
              , typename A0 , typename A1 , typename A2 , typename A3
            >
            struct is_callable_<T<A0 , A1 , A2 , A3> BOOST_PROTO_TEMPLATE_ARITY_PARAM(4)>
              : is_same<A3, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 4>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child4 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child4>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 4>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child4 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child4>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child4;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 4>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child4 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child4>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child4;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct function
        <
            A0 , A1 , A2 , A3 , A4
            , void , void , void , void , void
        >
          : proto::transform<
                function<
                    A0 , A1 , A2 , A3 , A4
                    , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list5<A0 , A1 , A2 , A3 , A4>, 5> type;
            typedef proto::basic_expr<proto::tag::function, list5<A0 , A1 , A2 , A3 , A4>, 5> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4;
            typedef detail::if_vararg<A4> proto_child5; typedef detail::if_vararg<A4> proto_child6; typedef detail::if_vararg<A4> proto_child7; typedef detail::if_vararg<A4> proto_child8; typedef detail::if_vararg<A4> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct nary_expr
        <
            Tag
            , A0 , A1 , A2 , A3 , A4
            , void , void , void , void , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1 , A2 , A3 , A4
                    , void , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list5<A0 , A1 , A2 , A3 , A4>, 5> type;
            typedef proto::basic_expr<Tag, list5<A0 , A1 , A2 , A3 , A4>, 5> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4;
            typedef detail::if_vararg<A4> proto_child5; typedef detail::if_vararg<A4> proto_child6; typedef detail::if_vararg<A4> proto_child7; typedef detail::if_vararg<A4> proto_child8; typedef detail::if_vararg<A4> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename , typename , typename , typename , typename> class T
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
            >
            struct is_callable_<T<A0 , A1 , A2 , A3 , A4> BOOST_PROTO_TEMPLATE_ARITY_PARAM(5)>
              : is_same<A4, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 5>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child5 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child5>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 5>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child5 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child5>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child5;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 5>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child5 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child5>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child5;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct function
        <
            A0 , A1 , A2 , A3 , A4 , A5
            , void , void , void , void
        >
          : proto::transform<
                function<
                    A0 , A1 , A2 , A3 , A4 , A5
                    , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list6<A0 , A1 , A2 , A3 , A4 , A5>, 6> type;
            typedef proto::basic_expr<proto::tag::function, list6<A0 , A1 , A2 , A3 , A4 , A5>, 6> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5;
            typedef detail::if_vararg<A5> proto_child6; typedef detail::if_vararg<A5> proto_child7; typedef detail::if_vararg<A5> proto_child8; typedef detail::if_vararg<A5> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct nary_expr
        <
            Tag
            , A0 , A1 , A2 , A3 , A4 , A5
            , void , void , void , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1 , A2 , A3 , A4 , A5
                    , void , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list6<A0 , A1 , A2 , A3 , A4 , A5>, 6> type;
            typedef proto::basic_expr<Tag, list6<A0 , A1 , A2 , A3 , A4 , A5>, 6> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5;
            typedef detail::if_vararg<A5> proto_child6; typedef detail::if_vararg<A5> proto_child7; typedef detail::if_vararg<A5> proto_child8; typedef detail::if_vararg<A5> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename , typename , typename , typename , typename , typename> class T
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
            >
            struct is_callable_<T<A0 , A1 , A2 , A3 , A4 , A5> BOOST_PROTO_TEMPLATE_ARITY_PARAM(6)>
              : is_same<A5, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 6>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child6 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child6>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 6>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child6 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child6>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child6;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 6>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child6 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child6>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child6;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct function
        <
            A0 , A1 , A2 , A3 , A4 , A5 , A6
            , void , void , void
        >
          : proto::transform<
                function<
                    A0 , A1 , A2 , A3 , A4 , A5 , A6
                    , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list7<A0 , A1 , A2 , A3 , A4 , A5 , A6>, 7> type;
            typedef proto::basic_expr<proto::tag::function, list7<A0 , A1 , A2 , A3 , A4 , A5 , A6>, 7> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6;
            typedef detail::if_vararg<A6> proto_child7; typedef detail::if_vararg<A6> proto_child8; typedef detail::if_vararg<A6> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct nary_expr
        <
            Tag
            , A0 , A1 , A2 , A3 , A4 , A5 , A6
            , void , void , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6
                    , void , void , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list7<A0 , A1 , A2 , A3 , A4 , A5 , A6>, 7> type;
            typedef proto::basic_expr<Tag, list7<A0 , A1 , A2 , A3 , A4 , A5 , A6>, 7> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6;
            typedef detail::if_vararg<A6> proto_child7; typedef detail::if_vararg<A6> proto_child8; typedef detail::if_vararg<A6> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename , typename , typename , typename , typename , typename , typename> class T
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
            >
            struct is_callable_<T<A0 , A1 , A2 , A3 , A4 , A5 , A6> BOOST_PROTO_TEMPLATE_ARITY_PARAM(7)>
              : is_same<A6, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 7>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child7 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child7>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 7>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child7 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child7>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child7;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 7>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child7 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child7>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child7;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct function
        <
            A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            , void , void
        >
          : proto::transform<
                function<
                    A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
                    , void , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list8<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>, 8> type;
            typedef proto::basic_expr<proto::tag::function, list8<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>, 8> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7;
            typedef detail::if_vararg<A7> proto_child8; typedef detail::if_vararg<A7> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct nary_expr
        <
            Tag
            , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
            , void , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
                    , void , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list8<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>, 8> type;
            typedef proto::basic_expr<Tag, list8<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>, 8> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7;
            typedef detail::if_vararg<A7> proto_child8; typedef detail::if_vararg<A7> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename , typename , typename , typename , typename , typename , typename , typename> class T
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
            >
            struct is_callable_<T<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7> BOOST_PROTO_TEMPLATE_ARITY_PARAM(8)>
              : is_same<A7, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 8>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child8 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child8>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 8>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child8 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child8>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child8;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 8>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child8 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child8>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child8;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct function
        <
            A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            , void
        >
          : proto::transform<
                function<
                    A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
                    , void
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list9<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>, 9> type;
            typedef proto::basic_expr<proto::tag::function, list9<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>, 9> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8;
            typedef detail::if_vararg<A8> proto_child9;
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct nary_expr
        <
            Tag
            , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
            , void
        >
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
                    , void
                >
              , int
            >
        {
            typedef proto::expr<Tag, list9<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>, 9> type;
            typedef proto::basic_expr<Tag, list9<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>, 9> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8;
            typedef detail::if_vararg<A8> proto_child9;
        };
        namespace detail
        {
            template<
                template<typename , typename , typename , typename , typename , typename , typename , typename , typename> class T
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
            >
            struct is_callable_<T<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8> BOOST_PROTO_TEMPLATE_ARITY_PARAM(9)>
              : is_same<A8, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 9>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child9 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child9>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 9>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child9 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child9>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child9;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 9>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child9 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child9>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child9;
                }
            };
        }
        
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct function
          : proto::transform<
                function<
                    A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
                    
                >
              , int
            >
        {
            typedef proto::expr<proto::tag::function, list10<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>, 10> type;
            typedef proto::basic_expr<proto::tag::function, list10<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>, 10> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<function, deduce_domain, Expr, State, Data>
            {};
            
            typedef proto::tag::function proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9;
            
        };
        
        
        
        
        
        
        
        
        template<typename Tag , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct nary_expr
          : proto::transform<
                nary_expr<
                    Tag
                    , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9
                    
                >
              , int
            >
        {
            typedef proto::expr<Tag, list10<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>, 10> type;
            typedef proto::basic_expr<Tag, list10<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>, 10> proto_grammar;
            template<typename Expr, typename State, typename Data>
            struct impl
              : detail::pass_through_impl<nary_expr, deduce_domain, Expr, State, Data>
            {};
            
            typedef Tag proto_tag;
            typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9;
            
        };
        namespace detail
        {
            template<
                template<typename , typename , typename , typename , typename , typename , typename , typename , typename , typename> class T
              , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
            >
            struct is_callable_<T<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9> BOOST_PROTO_TEMPLATE_ARITY_PARAM(10)>
              : is_same<A9, callable>
            {};
        }
        namespace result_of
        {
            
            
            
            
            
            
            template<typename Expr>
            struct child_c<Expr, 10>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child10 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child10>::value_type type;
            };
            template<typename Expr>
            struct child_c<Expr &, 10>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child10 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child10>::reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr &e)
                {
                    return e.proto_base().child10;
                }
            };
            template<typename Expr>
            struct child_c<Expr const &, 10>
            {
                
                BOOST_STATIC_ASSERT(0 != Expr::proto_arity_c);
                
                
                typedef typename Expr::proto_child10 value_type;
                
                
                
                
                
                typedef typename detail::expr_traits<typename Expr::proto_child10>::const_reference type;
                
                
                BOOST_FORCEINLINE
                static type call(Expr const &e)
                {
                    return e.proto_base().child10;
                }
            };
        }

/* traits.hpp
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
*/