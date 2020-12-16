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
wurkvOf5eWi2NLdFjLIgzTauj37L3NXMZPWVM8xBzSon/s1cGqzZ5KQYV+YEzEze7/sWX5VNg8mznd4v9ZiyJM1avnK/oCxFs6bll9orW6rZD99Z8vthjfYsi57+GsR8gRnl59YWpZVlauvKNv+rP3MJJmt62KXX8cr2as9i8q4wlHkGk/W+03dQgLLTmr1dFd1HWQ7MWs7bTn+lK8vT1nmVv+rEHIQZhOV8XHaOOQgrJez6t82/KzNZbnzNqYf/VZI5CDPIedR3bg57MqyUPIf+h4r+5rR2zfomHo3Zk7VrvsnrulhZsHbNr9di+A4dDpNxGb7dYpOyDppd370zlf1Ts8LKjuy7gzXrkHLsG/ugZjsez7VhXmvm+qxBTfY6zaqOWGbL3NUs9WzLH5mfWswav7xqxfzU7PHbQbWZg5rl/fQvZ+agZtG5HlHMQZjskTVn1TysLFczw7UGO5Tdhsk6+uB/gu+RBZq19xn9iDmoWXTWX38qe69ZXvFiRd8PK/D+Is+hxUm+Exk0c20dx1nsolnVS7mOzE/NUgeb9mD/hMkz6my44aMsRLNLG5pbMD9hbrJn1ck5yjkNsxX2NKl20c/rYN7CKu6PcWEfhNkLy14xKoP5AvOVPflC3D3OMe1+zialg9hDYC7CzLu3K/qZjna/8JleyewF6cb7O2eonM94wpzl/U52Xs+YwbyEPUgYwueMgsl4zt2dVEpZjHa/SROT27D+YKXk2c4rHMaYwfyEzav3pB5rBVZG2Ialz8zZd9O1WRw2dCVjBnMSNn9V7xTGDFZcWK1/vdnLvNaes7DSoNWM50rj/Z06PMyS8YTJ/Ox1bNb3zE+YvF9w4fADympp10yObs9zj4TJZxnXZ+Zm9kiY3HvbHgmV2SO1Z3Het4x7j4fJPrF/7IHiPCOYg7CBdq6cK2kr+f+58L9cOt10ImMNqy+/4y5Pj2ZNrzJ+93448Sx7pDdMxiVqSPw7xhNmJuxYpy48owCYubCkyxbcXxDMVNiecL86jLV2zV2vpl/kHINVE5ZzZ1sa8xom47nUawV7SBzMVuZE6hwXxhMma2WFrctIzhyYlayjSa+/MtYwmbu5v5dk/WVqz/LcPMRPWRZM9uTuz4aYKTsOsxO27JvrTWVXYc7C2lT8PpIzAGYQZnc3oIOyz9o5/DPLaaAys9XGNnNNAwdlBpjMidIWo5opc9Rs2pIN75V5aNYi+FNP5gtMxbMsrGBPQVdlgTBLYfkHFtxhTsCshb1zCk9UFgozE2YYHzVTWRjMXFiD7VerK4vQ1tlbtDjImlbP6f0/i/7r6xxlXbRr9gjqHcR618z3y+IGzE9YRWGRByd7srfCygtbYuKxn/mixcVnRHQN5ou2h9ht66cpO63Z0eGzeUbZmh3Min3Dfq3Z0DPbMpXlahaXm1uc+alZi3H/sCfnaXtwbxEfriwfVsZof5klmLua+ZaJX8UcXIOftwqbmPNgDPsLTJ7D1+Jr2F+CYb7y/JYHnuDchAUKsx54rp+yRJh8lpfhj04pS4e5CKt/zt2JsxFWQVhelE2YstswD2H/lN2Vy73DiguLmnvYVpnJWuN82Vl2BOsoAOYlrElfN87pcJirsGZJ6/htGA0rJyyw9G+3uXeYn7Dy05fwbDdrz/Jz5y+mzBeYj7BXL9vv4wzXzHVP8y3sIevw811hv7zpN0lZCEzm2eex1ufYCzSbO7vlU/YCmMzBm8/PFP0bLJiVsDkLalZV1gEmcynss/8H5ot2v7Z3a7VhL9DWte8/ojN7AcxC5vzHZQZlsbDSwmy2r3ihLEF7zlem3crzjLT9HW+ax5xI1swvqgF7eZp2zZw/fuXZpmt7mHA=
*/