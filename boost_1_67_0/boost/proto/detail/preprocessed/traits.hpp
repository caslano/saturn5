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