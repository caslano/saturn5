    ///////////////////////////////////////////////////////////////////////////////
    /// \file matches_.hpp
    /// Definitions of matches_ specializations
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1> >
          : or_2<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1> >
          : detail::and_2<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 2>, proto::basic_expr<Tag, Args2, 2> >
          : and_2<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 2>, proto::basic_expr<proto::_, Args2, 2> >
          : and_2<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2> >
          : or_3<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2> >
          : detail::and_3<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 3>, proto::basic_expr<Tag, Args2, 3> >
          : and_3<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 3>, proto::basic_expr<proto::_, Args2, 3> >
          : and_3<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3> >
          : or_4<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3> >
          : detail::and_4<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 4>, proto::basic_expr<Tag, Args2, 4> >
          : and_4<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 4>, proto::basic_expr<proto::_, Args2, 4> >
          : and_4<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4> >
          : or_5<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4> >
          : detail::and_5<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 5>, proto::basic_expr<Tag, Args2, 5> >
          : and_5<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 5>, proto::basic_expr<proto::_, Args2, 5> >
          : and_5<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4 , G5> >
          : or_6<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4 , G5
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4 , G5> >
          : detail::and_6<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar > , matches_< Expr , BasicExpr , typename G5::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 6>, proto::basic_expr<Tag, Args2, 6> >
          : and_6<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 6>, proto::basic_expr<proto::_, Args2, 6> >
          : and_6<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4 , G5 , G6> >
          : or_7<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4 , G5 , G6
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4 , G5 , G6> >
          : detail::and_7<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar > , matches_< Expr , BasicExpr , typename G5::proto_grammar > , matches_< Expr , BasicExpr , typename G6::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 7>, proto::basic_expr<Tag, Args2, 7> >
          : and_7<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child6>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child6>::value_type::proto_grammar , typename Args2::child6::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 7>, proto::basic_expr<proto::_, Args2, 7> >
          : and_7<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child6>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child6>::value_type::proto_grammar , typename Args2::child6::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7> >
          : or_8<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7> >
          : detail::and_8<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar > , matches_< Expr , BasicExpr , typename G5::proto_grammar > , matches_< Expr , BasicExpr , typename G6::proto_grammar > , matches_< Expr , BasicExpr , typename G7::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 8>, proto::basic_expr<Tag, Args2, 8> >
          : and_8<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child6>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child6>::value_type::proto_grammar , typename Args2::child6::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child7>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child7>::value_type::proto_grammar , typename Args2::child7::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 8>, proto::basic_expr<proto::_, Args2, 8> >
          : and_8<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child6>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child6>::value_type::proto_grammar , typename Args2::child6::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child7>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child7>::value_type::proto_grammar , typename Args2::child7::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8> >
          : or_9<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8> >
          : detail::and_9<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar > , matches_< Expr , BasicExpr , typename G5::proto_grammar > , matches_< Expr , BasicExpr , typename G6::proto_grammar > , matches_< Expr , BasicExpr , typename G7::proto_grammar > , matches_< Expr , BasicExpr , typename G8::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 9>, proto::basic_expr<Tag, Args2, 9> >
          : and_9<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child6>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child6>::value_type::proto_grammar , typename Args2::child6::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child7>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child7>::value_type::proto_grammar , typename Args2::child7::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child8>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child8>::value_type::proto_grammar , typename Args2::child8::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 9>, proto::basic_expr<proto::_, Args2, 9> >
          : and_9<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child6>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child6>::value_type::proto_grammar , typename Args2::child6::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child7>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child7>::value_type::proto_grammar , typename Args2::child7::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child8>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child8>::value_type::proto_grammar , typename Args2::child8::proto_grammar >
            >
        {};
        
        template<typename Expr, typename BasicExpr , typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8 , typename G9>
        struct matches_<Expr, BasicExpr, proto::or_<G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8 , G9> >
          : or_10<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr , G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8 , G9
            >
        {};
        
        template<typename Expr, typename BasicExpr, typename G0 , typename G1 , typename G2 , typename G3 , typename G4 , typename G5 , typename G6 , typename G7 , typename G8 , typename G9>
        struct matches_<Expr, BasicExpr, proto::and_<G0 , G1 , G2 , G3 , G4 , G5 , G6 , G7 , G8 , G9> >
          : detail::and_10<
                matches_< Expr , BasicExpr , typename G0::proto_grammar >::value,
                matches_< Expr , BasicExpr , typename G1::proto_grammar > , matches_< Expr , BasicExpr , typename G2::proto_grammar > , matches_< Expr , BasicExpr , typename G3::proto_grammar > , matches_< Expr , BasicExpr , typename G4::proto_grammar > , matches_< Expr , BasicExpr , typename G5::proto_grammar > , matches_< Expr , BasicExpr , typename G6::proto_grammar > , matches_< Expr , BasicExpr , typename G7::proto_grammar > , matches_< Expr , BasicExpr , typename G8::proto_grammar > , matches_< Expr , BasicExpr , typename G9::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 10>, proto::basic_expr<Tag, Args2, 10> >
          : and_10<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child6>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child6>::value_type::proto_grammar , typename Args2::child6::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child7>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child7>::value_type::proto_grammar , typename Args2::child7::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child8>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child8>::value_type::proto_grammar , typename Args2::child8::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child9>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child9>::value_type::proto_grammar , typename Args2::child9::proto_grammar >
            >
        {};
        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, 10>, proto::basic_expr<proto::_, Args2, 10> >
          : and_10<
                matches_< typename detail::expr_traits<typename Args1::child0>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child0>::value_type::proto_grammar , typename Args2::child0::proto_grammar >::value,
                matches_< typename detail::expr_traits<typename Args1::child1>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child1>::value_type::proto_grammar , typename Args2::child1::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child2>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child2>::value_type::proto_grammar , typename Args2::child2::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child3>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child3>::value_type::proto_grammar , typename Args2::child3::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child4>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child4>::value_type::proto_grammar , typename Args2::child4::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child5>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child5>::value_type::proto_grammar , typename Args2::child5::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child6>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child6>::value_type::proto_grammar , typename Args2::child6::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child7>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child7>::value_type::proto_grammar , typename Args2::child7::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child8>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child8>::value_type::proto_grammar , typename Args2::child8::proto_grammar > , matches_< typename detail::expr_traits<typename Args1::child9>::value_type::proto_derived_expr , typename detail::expr_traits<typename Args1::child9>::value_type::proto_grammar , typename Args2::child9::proto_grammar >
            >
        {};

/* matches_.hpp
7DC9nvQPW2HF1QuBTx0LdOqedtXG7iCQE6Ab29HN9vpxQLVKKJNGE8qkGyvHPGF1BGt2KQ2QWYHMPa6Ogs9WpiOJO45qn+7yNFBBUzw97GYbG+/PRSMHY3E/O+BFABMtgnKIX6Gs4ajYHWBitUkCQkCXkBHNzRK65G3SUbV4+TVfR2+p7S6lhRpATIKEGYG5O8jaXJ42tyf2uJWilva7PH0FnhbH2mfgfZcSK1DaHGufFJHsNae6sMIrOKMfbEH7f2gnbUa4TJZBCg1KROKQoKvcUUPrpyBifbTobA9juqx/HkYaHNiMLcK2fR9LVDrdi6fiwYRiQF3r0LWjXoFGUlbCj0xK4kPKR0g+JC88D8ma5VcjWeMk/6B2hBk/Ur0fiH0CAOqsPgIz8OebThqQGoFU9hmim6t9oYdMdsRdPF2dI/w1DvAfbUZxD1P6rEoPO0CshxdhDVDld/uvsZrDn3A+8Skh97kG3ux9RSBZFIc8HTCAaXopMBkwU+cvRtl0F5udDRxP64rL3IGOlZcwT6c/RViWA2cQ9H5usNlpcjZWNliFrehInDOVCGFtVTqgj2FWwTa/Mpd0ZF1iDehKuzvQpX4njCvEvXKmlh5e1x6f8ZMRF2n2rK+uhOgC98ppmsO4oSFBjka/5w5kqtlsdpHI35iUv2I7ioCuuGhZFfRBMTfhe/4U6JCX1qIvSBfGxzDbBeumcrGVZOyVD+J6W4papvHM6kfA3GJjKUz5MsNbEb0t+E9nGf/Wjn8awDwugJYSyzAK+YOmW04b/jF4tR2uqFf72XiB+oOSNRS8z60g4uD2GC/Y+k8DJ9u4tULTaS6fdlPY1jRJwLakhac8CXNpb47E/kYbkOveHTDy97dmdC2d5AwTYrlnSK+xUwwmG8V3yqRrJ11n03UWXefSdQ5d59E1BTuruZ6uKRxYzXS6nkbXs+h6Jl3fRtd0ZlM4En01ykz+SujqNejarT83nx4uout7yf5npj/tTp0iQCRDpes16O6u367uqoTB2qcM2fXVFfQWwaY/R7DpzwnYdLS0sg8DTNefQ8B0ffaD+uzF+uzl+nOExL46Qr8PitiFdL0YzdCe+PwUwgrd/TYBqpfkUMgD6NZPsFsfvCoOqY6dKSzXCCgdyKLRAlL9w82m+TFUdBQkHN5smiYT+DqkjoTU3ZtN22VIsEHCHzebds2QMAISXths2jwj6CEkrNlsWjMTtJ6bL9tsGkgTrJ6b37/ZNJ6WcO6llJAlEhDJfRYlOFPiSO75lGBLILl/fXPMRHJ3vj1gcC+0eW8FGkCEs9dAHxz+GuIW5ABnjEekoXuqdGWtrlUWnFEnuZvI+ujysuHKMT7l+QGjtxZ5glU04QiBqqBVTXcvTwMmO0WoV6CEyyqWLyBB60svnzRalVrBb2lWPVBLT9GQBp5W0tM1iadrEmIZlBXVaje7A2thAyCNkP8LEXW1CFZhKqFzcB9sAGSI4Rv2CCMb+b9IxMaIZqHa1D8kb1Huspa2rLVMqxL+g3IB6oQJgV8e4w6sgTatPprkpCC2lzwBciUA0qAkVCg6v4JC1J2kegjUOqpupEinsPYnrEFwzG6yha0ylVDaWn7tOzBY8U1yDb956UkUhdTySxv+CadNJcpegMfkf08/RXKYpusZsF5UiTIvH3n6JPwLKZUCgGDmrTD6LVn4PiFfHDlMZQSbY/zVzXAZwtfgjtC06iDFlIKFlHV1UHNbnTFhOQZlCTjz98OJ61kL7LOS5Wp1KeuKSDV3+Gx0nFCDQtJMGQA7GFhrYePVESmeo35LdCJGbt+nKx2hNMcD+63WQ6hi8nRVkM2sUsuK+oEdKSumJgNdsSa+HVZBN/1zNaqxanEKY61ToI4GYZ2ZXSaQw8QBzldnkyjGPzO8CCc3mygWeB/zOLn3hn7USMwlZ5Eevm+WEPkgfzIZEmAieI2dLRSTxi5IZPIVROltAijv8V8kYjm9CCX0vkBnawv31KD9IqwgyYMXnEnoNowJDwoIxhae8zzFhyY7MlZuZ4V2NsfmKkxzjWalmUSdRqxvWvcgEk0grKOxo10PdLcqXVmw13jhLJLQtw2iwC6++QVR4Gfk19UNJBh/99dJiDicEHFSXzhJuHmj2dK0ihxLu8VbXEaaphiCorcBIfQQ8u8tBExWX0hwgoHJIW079Aok4fZDaFoNFG3xX3XOj/8DZXhOVpTGnGy5HY7WJvxWWTH2ueusa06az7XHNd5bPBe74lk4/LBOE8sQmQZrQRXyopUWCUGwTkyJa5ixaUMvIBDGUZrL2YUo4+giCBfRP/yGl0xQjBb+/ediBv/xFQK8f174ZZwPj10O8+GYAMJOijhmjXuJSCzs6lPxuMZbzKhk8ZQ1MuWt1AuBsHeT/ASBC0KeGPx1FptUF9IAKHcMeXhxPhJmhG7VZ9TaCaeEhzxhf4qPL35JwPZ7InCHi/weSugOedoggVa05yVcDzb006NemP1C0mB30WBPeP6kDLqOYU6KEHR4prjHMKJ4v8Lm3o3HozqZRP+2YMTqJY/ZBi8//ytCpqXULzGVH4IlSCjohOBC+NoieBNMBGSPTc/kUGCjDPkGU6IIAZeteGhsFEpQG5JAtYPEBUSQZVu7PiYUlw0ijBOv+pVQXJIL8p2r4zd27lmNIDht+FbZeqyeEzhijN8ECd+BZ72vYW22dZGfZAP25Dd/g6/nkvLlK9WbaSgbdaU+7oCVVEMCdk6u5SfPUz1CylZZy/drkhylt1fHK/ba80npG6rjN3b+q+qkpjyBb3gacOxalQaCcnn8Rdw6cvMJ7MVj40ugJDfpONUR5PkVFaJV1GtnsCByVV7Cvh2fBDgHK8z0BkS/BAHc62kjsgAWzsQX4wgyuhbh9hfNhRLWtTD/EnaM6JVl8a5iB5LKrONPvAeEw2WXJWERIJhAtrSAmuxDSF3PIClSfclBDQsoXsENSamwv/Tz6zZgfwwOk3xAeqvST7hwi7Ey9w+L2lcwLKbhdcNiGl6FMQ2/zwgL5qsSFWpVLvMM+oQmOQkjuOlPAyZEgd8e3oP7w10TYH8IAFNko9ig6E0uxAwC4IfzQ1A3PDQIkekg3/8s8usxUvhiZvJqxQdfwAPWWW2oY0VglcwLMZgyMddiOLpKEEzgWeFneJAvx/du6BPfzkhGGeQmKFPxCwjKxNdAVffkWfzXhz/Gmo+CWzhTEcrSJJ1wXtbxXZcgj8pdRNt1M09X/pH8AYnZ8vAlErPl4ZESs2WJzW+9k0Q2aOc0F8kX/9gSPdCpB7r4qvFnjDJYXAg5tA83YmCLcScb4s3rLox18NTTJ8UyTUX4vyJS0MBpvonR5oKrl5Ih6aEnBKcaWBcHNGpVOqip98Na59syzeicl+jQ0PD4kRZTLm4zPM5hqhjUTPV4fQJ0MFuAnpwNRkZ4y4RbBm+C3kDTh19I6ZqnDzeLs+uxMeh4gI3pf4YkCRn+dESDyPXDQCZbM8WHkFArX3lYDOGodQJH4NVnvhK9YSMsZ35svDiIpoVnYCvuGo/D1RgmV8K2+3VPR/5++D1C10fp+m+sLT8ySWlvwpMN7jtblfdgk7Pcryvvw4qeBKttRsVDQuqOk8xv89vQUcfTxn/1FM6ndnblIhR7vI0aslXNSKlz7Smcvy2W8B/ND3fD34fw1wN/n8Afh79P4a8PvvNP2CpoCsjicTOhT0R4Hn2ixSwc6V6e9dSwPWbrc2ZXtOEO9AKex59cYiJKBfuyh5s0ZieMSTh/0i+sR4xt5Cn8GAa/lCCRq+MgkQIYMtluCsEgPzoWuyhI5AFI/3cgkfwrIJHGth46UHr4Y8/HwSyTQDfjSJZNzyZZKZeetpH01z817MehXjwO5UCZtDKz4kyNDw5rEbYPxttEN5iqpbsD16tTyXTalyzXh1eT7OX855Mj/uWjPMNQryWcsk5+6DlCDRvGeYRw9nRSXS95Fg/zyRg/J0+9LPzGG2+QHjALl6K66pTR+w7al2MyrfR23vVsjNBlxUp/t/bClf77mpOEv45RTbLQ/ui1J8XRewDxNZ5ZiTcYJwn3gE78ym+exD0A6Mdcsf5Xigp9bVghy58U70EhOfx2ypKnfp0p8A6dxi34agmVREk5KOtaKXaS/Fpz4rW3Ku20BrPXYQmyf69mylH8b2OVMWFaGVeHUjf8vPKUwac7YcFej6KC9TiKNzlGWipUcr776YVoaRleXgJcCT/tSIZLAyIsDpf2x58mwaXdZNuLeiQ+rjHDsjcpyJ2j4CZbYBS7JS0kw9t5QieNdlEeup4/ZCvjb76WYTHL+Tdvjo+/yUptMFhPrUdgtnURfLjp+o8Rmw2t3eXXPTZh+160DKexXUeD+jjQCiEk8KeXfWagfYfTHwcNL8E6tdUZc4tIcm+37E0AQ2ShGzhw7k2WMUgrYjBkJBZCq5fbhWy2toZc7tnqRZDgWn23HbFFiHe30k1o1jQDuLH5eKkMevnPqtEf7N9nvteO4ehXYEZMtbZ62er54gIhneCrVydKSXoID/77sWFv3Us5cMJyfNpXNew18yk82QHv3Rw0Uh1rv0tRCGyYFooZdyGUDA5RiY+dzT/ufnkQ3tHK+H99PWagwaBTvZWNKEM71BZkPWIFn5uor7cJTfZIH7/07VMwZ/DRABMs7NOVyY+AxlmoshEl9PZMIIEW3pMfuSuOaQF12OX8CAZz8yVmDFiYjMbOytHQOYWvIgcMa/bzX8Lp7E2rPqKms6JpwKQWXV+9/5GRcH49mXvaiF5efUSzBvcbxf4U2Cf5m1YgIdr47RlniK1YaGxEviK54E93yoJ/DQXj5MbXnhGvXTb8NVhQu3FBxUZL2Rv/2uzTRrCmG3oI/vXgv3wj/3hha0bao5OcelOHHeMwHqXfTvrtwt+XOP320W+M0vvpF7s6VJMzhjwd9KYsvGjKHoPxIMIZKK2tmU5J19PvNHzg/cF5A5rLmvXVlP2laaPxd4jKI1llUxtdW+hpGr3ZTik2unbSbyb92seQ2BV+gUr7EFq5Nz+CQRz7sNXnRsUljtg6URcpMWhNWVc8yclPzjhviPqTUOb4qxkWKb+bOee0wWuxRL8advwSisvETjyWbxR84Kj6EY5JYQ4GlCvDMNjGhJlCk151M0ae2V0xGpdiAV1jO9TxMFnfvu40Bkd589rTRi+GugwFsYvd07QxIYbdXOzl7D+/jIewNd1bkXWls7UEBVOfAAdGona4wTPiFpbEkm4llvSJNSelNhyxiRx/CuJ4MvT36XbFZmNoBE+ne/dkrNYV0rnlEnG/ci8L5mJnWqLpTOGuZoLS7PDqgTa+8/V+Y9NtbwGJrHSkBpWjqW7lKKqRjrJg+2gUxDmqThJ0MlPa8UZDSdFyG7NJDyCM/RHYgl10Fz65I/dMM2TPUW8q0BrV6dIVVstnShsr7WJa48zQ3BRdadNLOx1rpqDIM4g1dISuxLefwVqG0p5gFvR61RoGmlPgpKH+tCqdyG4qXa5gF912B/fZdGU7sF7R77ARwCCQiKAW/tYUozdRNrPhF2emWUu7dU8l83Ra95Ed23ZdCTPPFpYSbJ0nnVPRXEcLo5i03VE9nrahrTgqe/UYDu3AjNMGBbwMRPRAizEhBx1w4Z6cuRrJor0FUQ0jODi1Vtxilmfou4dok+V/nnxaHqW1vAR2T/6NkQkCbtgur9qCbUZvu9jpnSXxUCLupqMwFMAKF6YFIxl6oT0/0kvOT+i0ha6peIa2BqwwcdhqHDU94CxoVX/C2mCvy2O32Jiler96deiheaEAJz69tM9dOrTi+8zT7/YMrRxrKGgz0BH9Dr9yNfIcQy4PkEucfQF5XXvqCppX2tH7rtA+Wy9Mg7Nec+olacHzKDwoxCdBDrVKg+r5v4TDLZJRAnWUMX720T4e9zvFMLmn8o/7Cj43RXs58VUGc/ylanQKtBnaDxEqTy/v18sHzf7ul+b81N/AWxhaP2uqGo2+XqLXgZQarTetgJTel3EhN2FXRKewVuAh64zFNnajgEBdsgYtk6Hn0HtSBP1eDF/PAHbxbahR+aAIWG+zrPg6HkcH+R1/7if5YDmiUYsyvi3LGBIEtLt8yFGF0gZJKP/2YAxyolsfT49/7bij6ik0xNv0FtBWcmHMQUe5VcvTUI6r/gB2TdzLgltkENtNuUBT+C1FXn8qtX0the0M7p0n5kbbI4Iyn2CHDopOk5nWoIvO77AgKYmfHwwMWtTLN9n/cQ328ggEr/uExAdeXt86iGQ3Ou8FH8kx1JHBXbUEFGhjwLCUGd4c4Pvh6SK+sQH91NW7oH9gUj8Nd8J/OiKO1EK2Bj9ZwFB/o90gns1MwwFAeKMhIDxrMAPMN+0y/SlsIdVXfw5TZa3pKKBpvRoHVs2T3VnyVrw7d642zcqNnTT49KEhCi2EVJmMnprc2NyPSZBwXBvBb8cQRZ2y1C/b46Xea5ZqZ2sINH6/msqOVR9XMa2UlQ7l7yc9Dpz217BbaY9Ls6jW4L5UvEzBy4M2dmuOiKHisQUPOo2Greil+Oo+x6v7m7udo5u9FVeZbtQNy6RdPdEWPjYDW89OAamANRPj+K6Yv8Hf4SFrkQMKM3lhCU3oe5Mm9G+rsVVQ/+NqgRhyROCdyl5EJR4kfpM+KhaZae7XKUBuLX4nPbx3GXo+aVvuugeojN6rt/Ub/JInTAL4Aj7TF1J68g0vnMECp0Guz57E+oTFkyKAn0WTaHRZzTrYEAsOqaPdj+SoGT5ecAXShDRrWtUs4A2DkXmGBsVMCC8T9mtzU0zx8HSYSeyl6+NUB57WqHJlq1eIU2rtN1FttBo3SkfoCjJfOMife6XfKNjrqB6VYnp91bYhTso5sv6wpTqqq815KOroJmLGUXXM9DkVrrpvvxmfKd+rwpmCptWdou5QY6h3UqV/g1OY5jpLgcUn6COsb5U5L2Gjwnm59sOYUeLlU1oGjegDm4p+mON0KzbtR954baQLU3IgB8mOIx/dl9xXyLpy3BN7zN2Q1azHnmmD3fmsAfscBQJ6en5qUiyGf36MbHZa3EM0SF1rUUcnjxouRkyGb3y3gFqsCZDPWlzdcnpGL6OtyvEnxe63eP0p/xOej/UcEkkAgENLrX0LeFTV9e/kQRggYQYEwYoaFBEbbKmBlumIRmAgPkYnDGRAnvWZTrGNekZREgRPJnLcDKSKLbaIWKVixYrlFQpCYpAkgkAt1SCxTdvY/45JYYAYQoGcu35rn3kEsffe7/v7yeScffbZj7X3WXu9VxxbzYkzQaB0ExBdUh+HaPMz1rc3lChdsYGxzKVAvPxlr+XjVHnc9FbouCT/K3NOUsSsJOMw7E27OJF0UjyejfjDyQBUA7AlBnAfDwCLQufqb/j0bRB1rROVlxsnxW3o7uw9yRKBqKJ5fCJl8orY4ysSmir+Jg7KH7/VqWJqvktY823rRruJ23si1h6LVKikkIsu3h5h5Fo6emvgaDSTjYs/miNHNtsTwfg6PJnsnhuawM2oeQ6ui89z4RLkZyNQdxCoD8hsDGarCsqiOakw070RPC4fzJdAUn9QeVHBYOL3f25n2zBnnD31q5jTFqU53TUuG27VPkXJhPKT1vrF2vgQOhcrUGsjaK1L1VpfoWgWi4JX
*/