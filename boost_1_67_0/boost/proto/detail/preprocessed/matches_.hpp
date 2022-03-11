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
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
*/