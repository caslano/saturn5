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
teAdrWuxGcbO/eT80XrGne3xjDAWN71M1xAl5jW2+PXHI3XtYvb38tKvPFtrXv5TgLHPnq8p1vP9/1zdeViP6RoH8KSVn7RrVylCyJ4RYjJCyM7IHmIsISN7thEaGpLs2bNO9i3r2OYIIYaRPSNk3/fzPcvz7f49569zXZ/zvO/73M+9vG+XOtq6wuDTMxkzmJuw2rW/hXIGwMyFue3b35rxhJUSNu3a+ibMa80a963kwh4Ck3EZmzv/Z2U5MEthL/6JG6LsKsxF2Jz47x04b7V1r8zd0jkfYM7Cej6xbcQZEI5ZLGxweirPyFuzubZprPcgmLzfN59B/1IWDHMSdr/+scHs1zBrYREvqlqwL8HkuQ+YEvJAWQzMRtiqCiO/sC9pduXZA/aQRO1+QQMqRvKMYDIHm2wZYcveA5Mx234+cRl7iGZXlvi35/lpz+KeveFv9hCYzCW/4+6MdQHMTz5n87ecD4bm6K3CWn2K43eHC0zuz7GWuyd7CCxI2NShW77nbNTWXXwS24D1AJM95NYey3DmPEzW0d2ZL16wz8OqCQudt7mcsiyYzJcPwZcDlR2Hyb1XnR43gXHRnnNy1F8X2XtgDsK6tF3MXmfVwvhsvzux0lGZI8xf2KM82wvKQmDyORf4HWOthMG8he0eV/Q7y9EwC2GHdjfme+tgmLuwM3tXLmJ+aver3vPLfGXJsLKyJ0f731SWCbMXNt1uRTDjCZN1W/N3103KcrX7mU5fwXepPJis28yAOObEa21/JjUsjrDPw2yFlc1Yzxw0tDTOl+lZi+J5DjBneQ6e57srC9TW2U0rZH+pBZN5Ft8wLI19oiV/v/+/9tG1BHv5Zu1+p97+uZcxg7nJWbXjBM/oNsxR2JBNY88wLto1h7VNfsi9Rxjvoer3M+tw7zB5TfOkLq84G2Ey5zeU2F+We4e5CPvncMOpyiJg8myf+Xzm/jrA5P6W3pmXoyxWW7f+wcja7K2wstKsqlRQlgaTfelm4LhUzjhYJWFvBqyfyx6prUt99NqdsYbJ83v47j3359fKOJ5pT3NdmC+wGsKOfLRtxn4Gk7nbKMrsFPMFFibuFzniCut2M0w+5/5vO8tzBsAMwiwvHB7FXILZCNuZlRbG+tNs1Y9vxivLh5kLC/0pkv26UNvftqO5VzmnW+M9Ulj+nmXbGDOY7IMnDhUwLkEweb9SI5fyOYNhpYQdfNWG8y8cJs/hff+SlsoiNdtqNoHfQF1gMs/ebpnelmcEk3ldbL/TLOYgTJ7f99PndVKWACsn6zZpIHvIGpiso5i33y6yf2r3W1gibLay0zAZ68pjv+ax12nPcjqwUUdlZm2M+9LA8dHvWbewisJGLmrVj3uHybgcrrulK/MTVkFYXmQU3yeSYbJfNw6qf09ZBkzOxiVf84ZyFmvr7EvcHsP81J4zpu7KZGUmkcZnuz4pNIHzFib7y75Th/9iDsIMwqyj681gDsJchQX5BTDPImAyB7NXv+IsjoLZC/ObP4t1FAuTOf9bO1POo/EwP2FzVx/lGaXDLOW66rN/ZzxhMl8y9vzBWXwEZivfUeJiKrPXwcoIa9777GtlBdr+Rn0tiFL2HuYobIX3ix3KDG2N+9KBTkeylbnAZDynZpxm/dWCyefc3fgUZ2oYzF9Yx5xmvN9gmOxZzyes/Mh4wuQeqpmO8VGWpD3nlQ9erPc0/DdfYWtt9w5kfmr3q1W12xFl2TAPYZU6j+bZFmjP0mu290jGE+Yl692sXVXGrJ1xXDqk/MU8C4AFCsu03d2FMxVmkHW0YKEHaxom6/aXsF8XK0vU1t28citJWQqssjALf4dC5pm27vsmF1IYF1g1ub/eT00=
*/