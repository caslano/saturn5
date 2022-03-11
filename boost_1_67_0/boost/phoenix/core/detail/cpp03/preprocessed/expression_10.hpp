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