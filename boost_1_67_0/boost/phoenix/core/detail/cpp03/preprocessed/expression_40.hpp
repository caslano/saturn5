/*=============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    template <
        template <typename> class Actor
      , typename Tag
      , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename A10 = void , typename A11 = void , typename A12 = void , typename A13 = void , typename A14 = void , typename A15 = void , typename A16 = void , typename A17 = void , typename A18 = void , typename A19 = void , typename A20 = void , typename A21 = void , typename A22 = void , typename A23 = void , typename A24 = void , typename A25 = void , typename A26 = void , typename A27 = void , typename A28 = void , typename A29 = void , typename A30 = void , typename A31 = void , typename A32 = void , typename A33 = void , typename A34 = void , typename A35 = void , typename A36 = void , typename A37 = void , typename A38 = void , typename A39 = void
      , typename Dummy = void>
    struct expr_ext;
    template <
        typename Tag
      , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename A10 = void , typename A11 = void , typename A12 = void , typename A13 = void , typename A14 = void , typename A15 = void , typename A16 = void , typename A17 = void , typename A18 = void , typename A19 = void , typename A20 = void , typename A21 = void , typename A22 = void , typename A23 = void , typename A24 = void , typename A25 = void , typename A26 = void , typename A27 = void , typename A28 = void , typename A29 = void , typename A30 = void , typename A31 = void , typename A32 = void , typename A33 = void , typename A34 = void , typename A35 = void , typename A36 = void , typename A37 = void , typename A38 = void , typename A39 = void
      , typename Dummy = void
    >
    struct expr : expr_ext<actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39> {};
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0>
    struct expr_ext<Actor, Tag, A0>
        : proto::transform<expr_ext<Actor, Tag, A0>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1>
    struct expr_ext<Actor, Tag, A0 , A1>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2>
    struct expr_ext<Actor, Tag, A0 , A1 , A2>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39;
    };

/* expression_40.hpp
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
*/