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
      , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void
      , typename Dummy = void>
    struct expr_ext;
    template <
        typename Tag
      , typename A0 = void , typename A1 = void , typename A2 = void , typename A3 = void , typename A4 = void , typename A5 = void , typename A6 = void , typename A7 = void , typename A8 = void , typename A9 = void
      , typename Dummy = void
    >
    struct expr : expr_ext<actor, Tag, A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9> {};
    
    
    
    
    
    
    
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

/* expression_10.hpp
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
*/