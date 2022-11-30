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
      , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename A10 = void , typename A11 = void , typename A12 = void , typename A13 = void , typename A14 = void , typename A15 = void , typename A16 = void , typename A17 = void , typename A18 = void , typename A19 = void , typename A20 = void , typename A21 = void , typename A22 = void , typename A23 = void , typename A24 = void , typename A25 = void , typename A26 = void , typename A27 = void , typename A28 = void , typename A29 = void , typename A30 = void , typename A31 = void , typename A32 = void , typename A33 = void , typename A34 = void , typename A35 = void , typename A36 = void , typename A37 = void , typename A38 = void , typename A39 = void , typename A40 = void , typename A41 = void , typename A42 = void , typename A43 = void , typename A44 = void , typename A45 = void , typename A46 = void , typename A47 = void , typename A48 = void , typename A49 = void
      , typename Dummy = void>
    struct expr_ext;
    template <
        typename Tag
      , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void , typename A10 = void , typename A11 = void , typename A12 = void , typename A13 = void , typename A14 = void , typename A15 = void , typename A16 = void , typename A17 = void , typename A18 = void , typename A19 = void , typename A20 = void , typename A21 = void , typename A22 = void , typename A23 = void , typename A24 = void , typename A25 = void , typename A26 = void , typename A27 = void , typename A28 = void , typename A29 = void , typename A30 = void , typename A31 = void , typename A32 = void , typename A33 = void , typename A34 = void , typename A35 = void , typename A36 = void , typename A37 = void , typename A38 = void , typename A39 = void , typename A40 = void , typename A41 = void , typename A42 = void , typename A43 = void , typename A44 = void , typename A45 = void , typename A46 = void , typename A47 = void , typename A48 = void , typename A49 = void
      , typename Dummy = void
    >
    struct expr : expr_ext<actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49> {};
    
    
    
    
    
    
    
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
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type , typename proto::detail::uncvref<A42>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41 , typename boost::add_reference<typename boost::add_const<A42>::type>::type a42)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41 , a42)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41; typedef A42 proto_child42;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type , typename proto::detail::uncvref<A42>::type , typename proto::detail::uncvref<A43>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41 , typename boost::add_reference<typename boost::add_const<A42>::type>::type a42 , typename boost::add_reference<typename boost::add_const<A43>::type>::type a43)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41 , a42 , a43)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41; typedef A42 proto_child42; typedef A43 proto_child43;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type , typename proto::detail::uncvref<A42>::type , typename proto::detail::uncvref<A43>::type , typename proto::detail::uncvref<A44>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41 , typename boost::add_reference<typename boost::add_const<A42>::type>::type a42 , typename boost::add_reference<typename boost::add_const<A43>::type>::type a43 , typename boost::add_reference<typename boost::add_const<A44>::type>::type a44)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41 , a42 , a43 , a44)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41; typedef A42 proto_child42; typedef A43 proto_child43; typedef A44 proto_child44;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type , typename proto::detail::uncvref<A42>::type , typename proto::detail::uncvref<A43>::type , typename proto::detail::uncvref<A44>::type , typename proto::detail::uncvref<A45>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41 , typename boost::add_reference<typename boost::add_const<A42>::type>::type a42 , typename boost::add_reference<typename boost::add_const<A43>::type>::type a43 , typename boost::add_reference<typename boost::add_const<A44>::type>::type a44 , typename boost::add_reference<typename boost::add_const<A45>::type>::type a45)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41 , a42 , a43 , a44 , a45)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41; typedef A42 proto_child42; typedef A43 proto_child43; typedef A44 proto_child44; typedef A45 proto_child45;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type , typename proto::detail::uncvref<A42>::type , typename proto::detail::uncvref<A43>::type , typename proto::detail::uncvref<A44>::type , typename proto::detail::uncvref<A45>::type , typename proto::detail::uncvref<A46>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41 , typename boost::add_reference<typename boost::add_const<A42>::type>::type a42 , typename boost::add_reference<typename boost::add_const<A43>::type>::type a43 , typename boost::add_reference<typename boost::add_const<A44>::type>::type a44 , typename boost::add_reference<typename boost::add_const<A45>::type>::type a45 , typename boost::add_reference<typename boost::add_const<A46>::type>::type a46)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41 , a42 , a43 , a44 , a45 , a46)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41; typedef A42 proto_child42; typedef A43 proto_child43; typedef A44 proto_child44; typedef A45 proto_child45; typedef A46 proto_child46;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type , typename proto::detail::uncvref<A42>::type , typename proto::detail::uncvref<A43>::type , typename proto::detail::uncvref<A44>::type , typename proto::detail::uncvref<A45>::type , typename proto::detail::uncvref<A46>::type , typename proto::detail::uncvref<A47>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41 , typename boost::add_reference<typename boost::add_const<A42>::type>::type a42 , typename boost::add_reference<typename boost::add_const<A43>::type>::type a43 , typename boost::add_reference<typename boost::add_const<A44>::type>::type a44 , typename boost::add_reference<typename boost::add_const<A45>::type>::type a45 , typename boost::add_reference<typename boost::add_const<A46>::type>::type a46 , typename boost::add_reference<typename boost::add_const<A47>::type>::type a47)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41 , a42 , a43 , a44 , a45 , a46 , a47)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41; typedef A42 proto_child42; typedef A43 proto_child43; typedef A44 proto_child44; typedef A45 proto_child45; typedef A46 proto_child46; typedef A47 proto_child47;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47 , typename A48>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type , typename proto::detail::uncvref<A42>::type , typename proto::detail::uncvref<A43>::type , typename proto::detail::uncvref<A44>::type , typename proto::detail::uncvref<A45>::type , typename proto::detail::uncvref<A46>::type , typename proto::detail::uncvref<A47>::type , typename proto::detail::uncvref<A48>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41 , typename boost::add_reference<typename boost::add_const<A42>::type>::type a42 , typename boost::add_reference<typename boost::add_const<A43>::type>::type a43 , typename boost::add_reference<typename boost::add_const<A44>::type>::type a44 , typename boost::add_reference<typename boost::add_const<A45>::type>::type a45 , typename boost::add_reference<typename boost::add_const<A46>::type>::type a46 , typename boost::add_reference<typename boost::add_const<A47>::type>::type a47 , typename boost::add_reference<typename boost::add_const<A48>::type>::type a48)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41 , a42 , a43 , a44 , a45 , a46 , a47 , a48)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41; typedef A42 proto_child42; typedef A43 proto_child43; typedef A44 proto_child44; typedef A45 proto_child45; typedef A46 proto_child46; typedef A47 proto_child47; typedef A48 proto_child48;
    };
    
    
    
    
    
    
    
    template <template <typename> class Actor, typename Tag, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39 , typename A40 , typename A41 , typename A42 , typename A43 , typename A44 , typename A45 , typename A46 , typename A47 , typename A48 , typename A49>
    struct expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49>
        : proto::transform<expr_ext<Actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49>, int>
    {
        typedef
            typename proto::result_of::make_expr<
                Tag
              , phoenix_default_domain 
              , typename proto::detail::uncvref<A0>::type , typename proto::detail::uncvref<A1>::type , typename proto::detail::uncvref<A2>::type , typename proto::detail::uncvref<A3>::type , typename proto::detail::uncvref<A4>::type , typename proto::detail::uncvref<A5>::type , typename proto::detail::uncvref<A6>::type , typename proto::detail::uncvref<A7>::type , typename proto::detail::uncvref<A8>::type , typename proto::detail::uncvref<A9>::type , typename proto::detail::uncvref<A10>::type , typename proto::detail::uncvref<A11>::type , typename proto::detail::uncvref<A12>::type , typename proto::detail::uncvref<A13>::type , typename proto::detail::uncvref<A14>::type , typename proto::detail::uncvref<A15>::type , typename proto::detail::uncvref<A16>::type , typename proto::detail::uncvref<A17>::type , typename proto::detail::uncvref<A18>::type , typename proto::detail::uncvref<A19>::type , typename proto::detail::uncvref<A20>::type , typename proto::detail::uncvref<A21>::type , typename proto::detail::uncvref<A22>::type , typename proto::detail::uncvref<A23>::type , typename proto::detail::uncvref<A24>::type , typename proto::detail::uncvref<A25>::type , typename proto::detail::uncvref<A26>::type , typename proto::detail::uncvref<A27>::type , typename proto::detail::uncvref<A28>::type , typename proto::detail::uncvref<A29>::type , typename proto::detail::uncvref<A30>::type , typename proto::detail::uncvref<A31>::type , typename proto::detail::uncvref<A32>::type , typename proto::detail::uncvref<A33>::type , typename proto::detail::uncvref<A34>::type , typename proto::detail::uncvref<A35>::type , typename proto::detail::uncvref<A36>::type , typename proto::detail::uncvref<A37>::type , typename proto::detail::uncvref<A38>::type , typename proto::detail::uncvref<A39>::type , typename proto::detail::uncvref<A40>::type , typename proto::detail::uncvref<A41>::type , typename proto::detail::uncvref<A42>::type , typename proto::detail::uncvref<A43>::type , typename proto::detail::uncvref<A44>::type , typename proto::detail::uncvref<A45>::type , typename proto::detail::uncvref<A46>::type , typename proto::detail::uncvref<A47>::type , typename proto::detail::uncvref<A48>::type , typename proto::detail::uncvref<A49>::type
            >::type
            base_type;
        typedef Actor<base_type> type;
        typedef
            typename proto::nary_expr<Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39 , A40 , A41 , A42 , A43 , A44 , A45 , A46 , A47 , A48 , A49>::proto_grammar
            proto_grammar;
        static type make(typename boost::add_reference<typename boost::add_const<A0>::type>::type a0 , typename boost::add_reference<typename boost::add_const<A1>::type>::type a1 , typename boost::add_reference<typename boost::add_const<A2>::type>::type a2 , typename boost::add_reference<typename boost::add_const<A3>::type>::type a3 , typename boost::add_reference<typename boost::add_const<A4>::type>::type a4 , typename boost::add_reference<typename boost::add_const<A5>::type>::type a5 , typename boost::add_reference<typename boost::add_const<A6>::type>::type a6 , typename boost::add_reference<typename boost::add_const<A7>::type>::type a7 , typename boost::add_reference<typename boost::add_const<A8>::type>::type a8 , typename boost::add_reference<typename boost::add_const<A9>::type>::type a9 , typename boost::add_reference<typename boost::add_const<A10>::type>::type a10 , typename boost::add_reference<typename boost::add_const<A11>::type>::type a11 , typename boost::add_reference<typename boost::add_const<A12>::type>::type a12 , typename boost::add_reference<typename boost::add_const<A13>::type>::type a13 , typename boost::add_reference<typename boost::add_const<A14>::type>::type a14 , typename boost::add_reference<typename boost::add_const<A15>::type>::type a15 , typename boost::add_reference<typename boost::add_const<A16>::type>::type a16 , typename boost::add_reference<typename boost::add_const<A17>::type>::type a17 , typename boost::add_reference<typename boost::add_const<A18>::type>::type a18 , typename boost::add_reference<typename boost::add_const<A19>::type>::type a19 , typename boost::add_reference<typename boost::add_const<A20>::type>::type a20 , typename boost::add_reference<typename boost::add_const<A21>::type>::type a21 , typename boost::add_reference<typename boost::add_const<A22>::type>::type a22 , typename boost::add_reference<typename boost::add_const<A23>::type>::type a23 , typename boost::add_reference<typename boost::add_const<A24>::type>::type a24 , typename boost::add_reference<typename boost::add_const<A25>::type>::type a25 , typename boost::add_reference<typename boost::add_const<A26>::type>::type a26 , typename boost::add_reference<typename boost::add_const<A27>::type>::type a27 , typename boost::add_reference<typename boost::add_const<A28>::type>::type a28 , typename boost::add_reference<typename boost::add_const<A29>::type>::type a29 , typename boost::add_reference<typename boost::add_const<A30>::type>::type a30 , typename boost::add_reference<typename boost::add_const<A31>::type>::type a31 , typename boost::add_reference<typename boost::add_const<A32>::type>::type a32 , typename boost::add_reference<typename boost::add_const<A33>::type>::type a33 , typename boost::add_reference<typename boost::add_const<A34>::type>::type a34 , typename boost::add_reference<typename boost::add_const<A35>::type>::type a35 , typename boost::add_reference<typename boost::add_const<A36>::type>::type a36 , typename boost::add_reference<typename boost::add_const<A37>::type>::type a37 , typename boost::add_reference<typename boost::add_const<A38>::type>::type a38 , typename boost::add_reference<typename boost::add_const<A39>::type>::type a39 , typename boost::add_reference<typename boost::add_const<A40>::type>::type a40 , typename boost::add_reference<typename boost::add_const<A41>::type>::type a41 , typename boost::add_reference<typename boost::add_const<A42>::type>::type a42 , typename boost::add_reference<typename boost::add_const<A43>::type>::type a43 , typename boost::add_reference<typename boost::add_const<A44>::type>::type a44 , typename boost::add_reference<typename boost::add_const<A45>::type>::type a45 , typename boost::add_reference<typename boost::add_const<A46>::type>::type a46 , typename boost::add_reference<typename boost::add_const<A47>::type>::type a47 , typename boost::add_reference<typename boost::add_const<A48>::type>::type a48 , typename boost::add_reference<typename boost::add_const<A49>::type>::type a49)
      { 
        
                actor<base_type> const e =
                {
                    proto::make_expr<
                        Tag
                      , phoenix_default_domain 
                    >(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39 , a40 , a41 , a42 , a43 , a44 , a45 , a46 , a47 , a48 , a49)
                };
            return e;
        }
        template<typename Expr, typename State, typename Data>
        struct impl
          : proto::pass_through<expr_ext>::template impl<Expr, State, Data>
        {};
        typedef Tag proto_tag;
        typedef A0 proto_child0; typedef A1 proto_child1; typedef A2 proto_child2; typedef A3 proto_child3; typedef A4 proto_child4; typedef A5 proto_child5; typedef A6 proto_child6; typedef A7 proto_child7; typedef A8 proto_child8; typedef A9 proto_child9; typedef A10 proto_child10; typedef A11 proto_child11; typedef A12 proto_child12; typedef A13 proto_child13; typedef A14 proto_child14; typedef A15 proto_child15; typedef A16 proto_child16; typedef A17 proto_child17; typedef A18 proto_child18; typedef A19 proto_child19; typedef A20 proto_child20; typedef A21 proto_child21; typedef A22 proto_child22; typedef A23 proto_child23; typedef A24 proto_child24; typedef A25 proto_child25; typedef A26 proto_child26; typedef A27 proto_child27; typedef A28 proto_child28; typedef A29 proto_child29; typedef A30 proto_child30; typedef A31 proto_child31; typedef A32 proto_child32; typedef A33 proto_child33; typedef A34 proto_child34; typedef A35 proto_child35; typedef A36 proto_child36; typedef A37 proto_child37; typedef A38 proto_child38; typedef A39 proto_child39; typedef A40 proto_child40; typedef A41 proto_child41; typedef A42 proto_child42; typedef A43 proto_child43; typedef A44 proto_child44; typedef A45 proto_child45; typedef A46 proto_child46; typedef A47 proto_child47; typedef A48 proto_child48; typedef A49 proto_child49;
    };

/* expression_50.hpp
V3r7iFLk5nThlHs8blt/tNRjWeJxpUOzo60i61SXe0wXH1Jb+vjzxuBy2tSLoaq6uFoZzXisDu3mznllNPWc/t54x3qpuGZVduG96POfQvDaYQP4Pwns/1pkQO5hQPbxQOLj0UR3yqLdF4PX4+HGcN6+my0ZpqenFXXananQzaP9mH3l5OQ67pywxnn7ZoDE/TfyZXK7b1JjhhnysQD4t2/JkNsPZWQ75iVkefMDCuKeKGcs/QKBpqVKiS6ROn4pj89tr5u13Tssknf6fql8p7jbJaX6hBsKNTWtvukn0UedsoB1KJuTUOfk2BzR5sDYTEmgZ72I8x9+uiUyeZuoOLX1mkeuNWl2oy0IkrqvRfHTDUqRT4mT/d3dWcEcYOJXiA0Y9bmAZYDNQdE+JJXWLuowK7IdzBJ0p7UPU2ijDCdm0yv6eTOuYcFoCZnwjmhXa50qk6nxXqmzM7vgutI/lhuQyRHz3Mfw0G4l/LtS+KYkArPHEyd3+tkON7sFcLOf4Dt+Qk1ripPTj8nyhGF6TmJ6zs0pm2SaDmWa/s+U+66Cc5q6DMmpeZ73n4AdGK/8cDvUEAW+Et8dGwdy56V3NXORzUZzk8Dn7UD0+zpSzvpZqvwGydYI14LsiPa1uLdliRmBS+x8XiJZN4hTXTqCkTGby65Za109CSBSxPDRorJyVI308U05p3LeVIefTbQ533cuNMrt8U36Z9yk7j5ebuyiP1XRXxvRmz4+Iptgxoe06Sggc4l+5VJCPLBhRzM5/t/elGUdc4oURFRw5jTETp8ctn5fvsXRvT43hXg0hPSmMImHFJWlhpd9itxzLT0xyzFs+B9MPjZwoWqx1C0ZZ1iczitXO5QGVflW2qRrBgUe7eOUoaKqSGW7eWQ1aikncXcWVy4dKedplsygP7V3BJqdnjHtn14oGJ9d2UUz5OYgot8uReDsaGfYFff4tR1jCR5RzeMXHkg+xFpjedEbVf6pbgWm1BhSkGoFW2PXm4wmE//fFUo6EQts6RbBM1PKLawimzP5s1jzkAYygdPRWGv1375/s4UBcgu6iSWt6SqZJeDwtogGpDpv3kPKf4aUv8M8wtOc/Q2Gl+Krm90tlo5N56vYyL1gY0sxLzCWKoSSVyq08stXGBU0aixaFGpcuMM9rxoOL8jkss+LvP2f4qv7LWTmA1h7cBgZyju1tLq6XT3gkojRidGJjoiKiIaIxv7t+WvqYoDck0DcgxbiFaIVYv3OLNc+hMskxXIe5rz8t4gCfcLkWUBLqQs7ENkOEH5IdZsZZhx9ocPCXkzLGfljZavElAR49exgVzsScYKnL5lLXYg9YlV2wEnngieSA0upmJKaIsy3AheuU3j/rwwrrFrtmKSIuOpXaCzYZOh/qcGfY5KPNVB5kj6BS/6Z2hQrndUWMxesfIRh1WdwTJw1jIUwL6lqPM2klei1Yfe6JOwJPIJRVxvsBhm1sqtAgToHXriKc3f1pIdiBwWqF2Zv+mQf7C8djc/z8KbxXTWzTNwIva0eJqNbvcGbDYVPTLZmLH8gyUhT+K3eY2o5Yg/5sJPOKxtbiuTeyiFvcZjeglMpzrJMag/brRWvm3vaqudMj6OxM0LA28yV5SCHp+zJOvbhkiHYub1LIH9S63J/oEBaMW6KRJCbkQbz82ZwHbNnddy3G7d/HW02nUgz3Bqz8UTs/19R0AyeZ0609ZufUmhnkt7IZw29tpnnkyUr21lR1i7B+ltiajjzBOauNipQ4UNHPy/ro1Q1Q1lx5hrI+hKtP+t0Qr4F0NnqxzJQzsQxaqmz+s/IxzDye/x1Q+Er6UpG5FGNTI56Xm8Ja7Gkh3tfK+X7/P1K8qxmeqeo+Pv8eyriqSf0TrQMKBalso93IhYZgPP2p+m8Opi3od9BzepKH6+qilO+wOv+TVJDUiLOlFQDtNjinwXOaMQh0UzMfx4YYG+KhWuSyXDajFOOyUyntGaz/P5+Pm895vcvx0U3EzT3tefe2xAnNUS/A4AH4iLs4qMF/NWNlWCBX/jGcSl+aOoa2n0xyElNGimdeSc0ZHaRNaxHUU8N6t3MPoWJNdZAmJ6XTekR8TdPBpFakfDHIYl6EKsxtKwDpC9iO+S/IH8RUJqNmUoxAWv0jv+ZPVqb4f3lJmoSrUdT9XSW1/zodh6a2Xg81cT0bF2CZIiB+Mxe7s6u6R0BWsDwd2UIA7un3viqv7efkU5XcIIhGg9eOqJhXP/NEUczkjfCRuLvTd7gvnsn0gSGPP27heaL8+xrDOsyOC/sZnQ6/y80nRvJdOo2gIsF8u7DuCeVCw5DHD6gBgMwfsOh2cGKt68qF/Q0UdJ7vLpWe7bRVmsxACqpTgiv1a0Ht8FB53elldI3HSVjcHOMXmu0AbOaVIvy/Lsy+GtDTeSvN97lGjokpJsvGORLZYBI2MXubXeU/essBmdyK3I0wSrcCMKIiLQjaCZvK7wc4Tb0CeJNcE7MdeAC1QfR06Ev50/vMmX5wE+myfuKjD72pKVRtPldsOhz+GDSykZ2xTVhjLU5QdJO7li+0DbbnSGqdfhgW2qyQy4jYe1fPLkPt6cDL3nS7Dk+cDY7vFB9x9p+Id7s+I20cd2+zvm4f1rRfz6/Eh8KeP731vMFKv/gG0TxFrO3lgBKSf8JFh4Bk1fYijUuLbP79nDC5hI2qvxtUFQ+s7GobyGo5ZquPDuYv2zlqWVvp6F+cdBSC2uuLFPjv7trCv94S+cf8EXnrL6WjzHCBoOA4LnRTKBWEUS+kl4BbDeShLoPQXh6sVyKVQqoazbfpmBlZU09gXz/eHo5m4/8SJFmWdl0Kw0J6ZAgzN4pksEMQeT2bO8kibymo92WWCN+4tITAkCyHh50d3k2NZtP417hSw+l4ObvIlpMaTyT+b64vXLlu5Tmr3ZV70KqO1Z5u/u+cNQK+fjhnxsg9z5sOCZ//eq2ulrBaVS8F7G52FhbW1vXtK+peK2HyAwJv1Gk+e+owxGDn1/6OwNvRXaMgMDyA+PehiutJid0R2UI8bkUFW8TnewT/Z2vo6P5MJ2VIQWxeoF4NdoK43TkwYuoxwB1F1T5nhj/cpNz+gtVoMgH/+7z8hxRpVaRv1UOf9q1tCf+5m8L8ZAOmF6RN1T7MrEC1Y2y2lwYvKUL6qGIQp9CkTdPxLswZLdqRVWNMH/rwEb495f6t10EIMLoQ2WEXxhY0DmxAd/2jrNnMqWxev/d1FS3e948i9C7olka/uxi0XS/+bdVeKoHgUnYwSL925MhvsANXFRfk2Si3/kA6t9b3L0bkiSG34giT2LdpEQb89Az13C0Os5XZ1QJzxElu3f0fI2Z0aRieu+/brrXT+NRChviUaANFrtkXA4c4SaIOMLF4AmlUQiPQfZ+5bgSebRryFhqjoItCtdYxoz86+Zv5v+OZ+AOHxJO3/KQGtxZaXUYUZJ3T8KDjPTX9pm8q+tBzy6KDohdx9xDtZiRDVPk/VX0ZIOXaEpuuSbTVy1qDVR+W2sLELIDWqAeUsxDRz7J7j4Y3jLJHE4sVxu84H8TrsNQpQIyudKhSuQugxZSAxSuHfZGdSUFHEJnuJjpc/wzTuT7mibK7Fm+8LQneCE11OZ3p59kvLvjXFjwHRl3WlOcwAiMt/7p3ZhVOEaATtL4zgDhYXK+6Mfpwv+0BZWl3qNV/Y2hyVFdkiF16hCPj0ym266gGKt98JUQzo9Twb3pduGMMN0fB2isuzmen2y1yDOMAKuqPNGVSSdeHMgvR1ZeHs+Xq5tBS3S9CAm9rtEtb2ZTWVrcnJtKXHT4LC8XGrs4mm5619we7F0sgtrT/zbJx6zzb6vbGV2LPxGyB3pee3fJLxTbrDdaTDc97l/wLB+gLfHz0Wbh4du02vK9eprJadwsLJbpcVQ7yDPkdeti5unanmwlOl2EXW0pxKCzKiu/PNR55Fj9efZqbfVWh8zVaOj29hGgyKR58+RIUbMgaKpZEUGqPZhZGVgSP4WtYO9yB5Ho/p7ypFOJbig3ijlu8XiISoavTFfDEjGkHsAO3fNPmxLhjgZHVgBnHgWV4QQ95rRz4LWYMQv3tEyIsZlQCH7EfuiEr6rz8eQIEOqu0q+90WI017fCQl4M05OIwb0GzZn7RFvGJ496CLy94zN4H+Rn/OrxMfB0F0hlGoIkcahO59rCNJV9CCjFzundXAsw0F1EUmf0ohSdgfc7/UWqP5avWHsZIW8g5ozl/TbEqY7+hT0to6Q/VX5Wa+sCbh0ZFehiZdrXbHc88NI6vC39sLBcFHs74LhaZ0L12/YLxpVisL8av67WzQwPb7UOAuFaK8bqbOr2oW7L/r2kK9bznChTpqjNElFbWjaYpiR+D6U6aoGhqHcKtuSVi5rngcR4Z/qfV0t1/1elVazXDQZvqxP+GcTn8y1BdYBD9rjXYA3AItvz2cvPIpsZfYG3mH1k0VOlq394Ts7GR32jIavJ0sLK5ur0bG2rK8FFh9tzoP2jo4r//nK7TihDbtlO2OtCt8uT9e6nYTo/IiGAbfWx33Cn3IYmgn1aDoFQvUd4hGCKlyeVi+eAez785CW+TbPZmbRbpULO/fRIM8Wp6GBlJ1AtXUEswfS6elpu+fPfVmmYBIOamVsJeTmbNSouLk8GuT/ieFnoNykzqIBJONA38vC/38Ha3dmvi9OPnVFln0uwW25JrZixs0t1ji9XkXSBAzchTv8Ei+hai1U3na7hmJZ85FuFAZSX+hnstAqrQl6X/P9wvGaCZymsRqLtTWMIt8z2UD3vu0vLvndrPBQAuYiML3sWy3AC39/eskNgfDnC3Wr7Ap0AyI98EMKUxp2ESy+Qj7rl8BwZ6JxZmSDgpRTIRrcLNi7+/ijol2bEi2glmRb11swjXnQtovNqriut7ZGy60/SVP2rPBoeJvr6k6lM3mIIan8S2eX9WoH1QovT2klBR/mzHFYDonIbcPGCFJfdzPS/idb4n/QVrmHhwDTA2yL8qedoW7e5sbK6dXF2ufo9RWt5LnjUGqcdJ5DoRX48iTd4bapn9pMJ+6cz+UOd/2VxufwrIjHR5qcKA/BSZeNztQbhb7fE4UtrjyBcfwZf7XSn6/C7pGZ9MmUHhTzNdlCk1p5lvlyGGwGSk+rq5/8WoiSHsMcCpdg/5Iq3H3YSajXZ5OQyVjNMzLT1W+izDDjm/6qbnjMl1/KnP51qqlkBIAkXQn2uzjWeT3JMLF+LyMhoKXgSVsKskLpeBay1J1s+XgVkNY7f0Og+aaikrH+mG0CORPv/TqiIAEf320Dg9/eQpQDltxOLdZ8FUs4Xse+8foPQGSIacPWyx9t8BCimVN57nuu6QjF0/gX5nHW7jhgOUOgGvBxzqX6s0Of8x84yKA+T+m273wTs754CgvGKAUVOLmcCvuR6fRXeIYOEDCOvAQpvGRkGYP9JXJSCkJL8/yfAyiP11cjoCmhJgoImUqJiYqEymyjoKa0QQmJwFaWU9aFY4KJwcCT+sKDklvY7CpuKikaDtZRComKiv9QEHfQEozw6X1qfr85ZWCbhWAbgIjxefPC6v4PPzqvLF5zknvS2dLZoFfVS3Wfw+9eIqAG4NqQmhzXwOWKBPutLNCeJ8Tk05gErqxCGLzlJ2ZPGMYRLyWiYOkrSvn+FA081VFT5u4HuM6vAsImRDwn+iuQZlE5g+diMJE9l4+dmRA+yl5ZI3OflA4WoN8xDQ2JyD59vHdRMpfpxeaO397fi911BD/Pb6wdpzi3SB86zfJw3YAb5D/u6aSXw8A6s6IhQIL3XN0RmrUTsJTvFSdXi7QTBbm8ZAub9V+PUK0J3hXtV4icQoxGE/DCgp4f2g0HGdzpNZNChPmwQx/2y5k5HEJ8gZUtJmr+553YbINCmRPWWRhU26DCOybyCCuMiyONNxtGk+va6cfAlXyClC6SgB6obds4+0+i6ydqgnMeK2nisDfDAHBnh/ibUrFH4LhKIjoO38h5rjdOc3C7755RmA4NQS25xghDbn5GSeA1sWIiOL/jYHxNmoEGGKJOBi9vdWqUfFDL/GLSpaf0S+zw64o9d72XPf8UM7jtHAiNdwdx7hFZKrI2kdtc+7izGkZWk6qMDD3EqE42Cl9jN/D0tu49XZC/XwI6975Shjnki5uCbWFjxVXDHLqvW5dPHCE2Iz+QKxnfD5k20rga9I/DZw+Rt1yhfZ9UZ1NzVt+JdAPR7L9iS3kSfui7I8/57DPib0fC2QhYJBPi8RrRyPcU/QqrcDbSyyzfkWIvuG3ZKaZ6DhPtMh1oz3AMr9uEbOtow5eJOb7HRXnDtXeX9qky+8JbQ34rxNmhPD8C/ZEyK/nzXZPP+npG+ruM3eSHnT2NWzHmgKRrmD/Q5/e5iyufn5R8OaRJifEorepqZ5hy2Rw3R2Yh9Tco+dBSHaQPQhVTqDZ0nwZpAeeTw1iUZJgKk9MEflRKeK5PLemYZXj2mvIsBY1W8w4R3vcmt/y3r+rNrEA36zX/OAetb2OLHCD/wB7de7HSr+oCmqtTQtwRigTdnWRtqJvcjzzGHPAlHrHsPDR4HKPUWIoxhYc/67TUxT6hNPazAxC6BiE+oYIOjW4Dy+NYAWXgOMsexcRYJP+imrmeLID3w81GJJLMoVIBfoFTgZ2dUbQClwIihHMJfnw+BvqG830EcjqG3X1FQTsZP15ujKqM5TTG7WbdPOMWxAt/do3qhdClfjyJRJ3rpQGsJp8MeQc7gfzOzWoNzjq9GH1AbqDkAsc83vwSrwfD8KGPOtzm+tM+7t0P7uRbmHT1iwE7bDuN2vTXtOlUjohZqcj0TlsV3/4kEBjCQE8C80iRfpa50+nFgF3BA47B4ffDq//qQcytDtIZ1M5MNmNEAK2fKCjeqNjQarXfA/fqyxOVIzE6pYSW/Vcz6JuwrosZCQG9st5fTZSIY8PAgyBgY4Sa02AIOPthUjrieciy1G60qX8gZKPVwnJZY+sysgS2eTJ6uZN2rXxnvXAEkEFQ3ull7m110nPNWDx+n/K0NeYRuGqmfMDxjLk/MV8j8lzsiXI8O6+hWe4404QNXxR4kEJUV7GiXOvRhfSRg7htEv0C7Ue2yBch/tVkY+0yCGvLoMnj1beahHGSzZHmN2G49onoAn+Hfvh7pHQ93uf8qfv9VBqJczYgEkCckguGOTmWyouByhbSuukUYrm7OeT/fHYL/1NGE93s1Lb9Nj3ih30pi7MiqF6Za3fgEQtD+EmQYYqCkWOjwlV5RvlLWAzKvVru5IvH4keTl8GSJJBC/hbWL3SjGPg7GCjZ+5b+/nVGMPUoFB9GQaIc5++ClaLcsp4wBWR7A6zIW03h9FZQL+KM9aB+x3/62878naZ16AR/vwI5nrgrfeWm6tAq6OwqGZDhGdJHVnGaWSoGPDkwalwJxUQN8VG0iFzsJpQBzLdZtwOB1FbLlQaUm4Scpm1Q+f7PepiVD8u0Lak1Oai+FUbAl3h/1BoVG6M6PyG7iCWH87ZPjT7mrLxpVwieAuvboecrmNIVZfEt87i+jnY6vWRrRZZZGsxGYrFkyVxZx34LmtOcpi9TiNaziuWeZgU6iHgcW9sqnhbhGEW3qorLfkRkp1bmqNDqyjAx0J8Lc07IVKHYBFyo6+J7/
*/