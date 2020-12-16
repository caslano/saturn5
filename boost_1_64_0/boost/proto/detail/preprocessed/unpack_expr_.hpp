    ///////////////////////////////////////////////////////////////////////////////
    /// \file make_expr_.hpp
    /// Contains definition of make_expr_\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    template<typename Tag, typename Domain, typename Sequence, std::size_t Size>
    struct unpack_expr_
    {};
    template<typename Domain, typename Sequence>
    struct unpack_expr_<tag::terminal, Domain, Sequence, 1u>
    {
        typedef
            typename add_const<
                typename fusion::result_of::value_of<
                    typename fusion::result_of::begin<Sequence>::type
                >::type
            >::type
        terminal_type;
        typedef
            typename proto::detail::protoify<
                terminal_type
              , Domain
            >::result_type
        type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return proto::detail::protoify<terminal_type, Domain>()(fusion::at_c<0>(sequence));
        }
    };
    template<typename Sequence>
    struct unpack_expr_<tag::terminal, deduce_domain, Sequence, 1u>
      : unpack_expr_<tag::terminal, default_domain, Sequence, 1u>
    {};
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 1>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0;
        typedef
            list1<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 1>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain1<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type
                >::type
              , Sequence
              , 1
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 2>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1;
        typedef
            list2<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 2>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain2<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type
                >::type
              , Sequence
              , 2
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 3>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2;
        typedef
            list3<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 3>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain3<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type
                >::type
              , Sequence
              , 3
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 4>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3;
        typedef
            list4<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 4>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain4<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type
                >::type
              , Sequence
              , 4
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 5>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4;
        typedef
            list5<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2); fusion_iterator4 it4 = fusion::next(it3);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >()(*it4)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 5>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain5<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type
                >::type
              , Sequence
              , 5
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 6>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5;
        typedef
            list6<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2); fusion_iterator4 it4 = fusion::next(it3); fusion_iterator5 it5 = fusion::next(it4);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >()(*it4) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >()(*it5)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 6>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain6<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type
                >::type
              , Sequence
              , 6
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 7>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5; typedef typename fusion::result_of::next< fusion_iterator5>::type fusion_iterator6;
        typedef
            list7<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2); fusion_iterator4 it4 = fusion::next(it3); fusion_iterator5 it5 = fusion::next(it4); fusion_iterator6 it6 = fusion::next(it5);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >()(*it4) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >()(*it5) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , Domain >()(*it6)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 7>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5; typedef typename fusion::result_of::next< fusion_iterator5>::type fusion_iterator6;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain7<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type
                >::type
              , Sequence
              , 7
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 8>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5; typedef typename fusion::result_of::next< fusion_iterator5>::type fusion_iterator6; typedef typename fusion::result_of::next< fusion_iterator6>::type fusion_iterator7;
        typedef
            list8<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2); fusion_iterator4 it4 = fusion::next(it3); fusion_iterator5 it5 = fusion::next(it4); fusion_iterator6 it6 = fusion::next(it5); fusion_iterator7 it7 = fusion::next(it6);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >()(*it4) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >()(*it5) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , Domain >()(*it6) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type , Domain >()(*it7)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 8>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5; typedef typename fusion::result_of::next< fusion_iterator5>::type fusion_iterator6; typedef typename fusion::result_of::next< fusion_iterator6>::type fusion_iterator7;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain8<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type
                >::type
              , Sequence
              , 8
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 9>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5; typedef typename fusion::result_of::next< fusion_iterator5>::type fusion_iterator6; typedef typename fusion::result_of::next< fusion_iterator6>::type fusion_iterator7; typedef typename fusion::result_of::next< fusion_iterator7>::type fusion_iterator8;
        typedef
            list9<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator8 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2); fusion_iterator4 it4 = fusion::next(it3); fusion_iterator5 it5 = fusion::next(it4); fusion_iterator6 it6 = fusion::next(it5); fusion_iterator7 it7 = fusion::next(it6); fusion_iterator8 it8 = fusion::next(it7);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >()(*it4) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >()(*it5) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , Domain >()(*it6) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type , Domain >()(*it7) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator8 >::type >::type , Domain >()(*it8)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 9>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5; typedef typename fusion::result_of::next< fusion_iterator5>::type fusion_iterator6; typedef typename fusion::result_of::next< fusion_iterator6>::type fusion_iterator7; typedef typename fusion::result_of::next< fusion_iterator7>::type fusion_iterator8;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain9<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator8 >::type >::type
                >::type
              , Sequence
              , 9
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };
    template<typename Tag, typename Domain, typename Sequence>
    struct unpack_expr_<Tag, Domain, Sequence, 10>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5; typedef typename fusion::result_of::next< fusion_iterator5>::type fusion_iterator6; typedef typename fusion::result_of::next< fusion_iterator6>::type fusion_iterator7; typedef typename fusion::result_of::next< fusion_iterator7>::type fusion_iterator8; typedef typename fusion::result_of::next< fusion_iterator8>::type fusion_iterator9;
        typedef
            list10<
                typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator8 >::type >::type , Domain >::result_type , typename detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator9 >::type >::type , Domain >::result_type
            >
        proto_args;
        typedef typename base_expr<Domain, Tag, proto_args>::type expr_type;
        typedef typename Domain::proto_generator proto_generator;
        typedef typename proto_generator::template result<proto_generator(expr_type)>::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            fusion_iterator0 it0 = fusion::begin(sequence); fusion_iterator1 it1 = fusion::next(it0); fusion_iterator2 it2 = fusion::next(it1); fusion_iterator3 it3 = fusion::next(it2); fusion_iterator4 it4 = fusion::next(it3); fusion_iterator5 it5 = fusion::next(it4); fusion_iterator6 it6 = fusion::next(it5); fusion_iterator7 it7 = fusion::next(it6); fusion_iterator8 it8 = fusion::next(it7); fusion_iterator9 it9 = fusion::next(it8);
            expr_type const that = {
                detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , Domain >()(*it0) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , Domain >()(*it1) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , Domain >()(*it2) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , Domain >()(*it3) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , Domain >()(*it4) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , Domain >()(*it5) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , Domain >()(*it6) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type , Domain >()(*it7) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator8 >::type >::type , Domain >()(*it8) , detail::protoify< typename add_const< typename fusion::result_of::value_of< fusion_iterator9 >::type >::type , Domain >()(*it9)
            };
            return proto_generator()(that);
        }
    };
    template<typename Tag, typename Sequence>
    struct unpack_expr_<Tag, deduce_domain, Sequence, 10>
    {
        typedef typename fusion::result_of::begin<Sequence const>::type fusion_iterator0; typedef typename fusion::result_of::next< fusion_iterator0>::type fusion_iterator1; typedef typename fusion::result_of::next< fusion_iterator1>::type fusion_iterator2; typedef typename fusion::result_of::next< fusion_iterator2>::type fusion_iterator3; typedef typename fusion::result_of::next< fusion_iterator3>::type fusion_iterator4; typedef typename fusion::result_of::next< fusion_iterator4>::type fusion_iterator5; typedef typename fusion::result_of::next< fusion_iterator5>::type fusion_iterator6; typedef typename fusion::result_of::next< fusion_iterator6>::type fusion_iterator7; typedef typename fusion::result_of::next< fusion_iterator7>::type fusion_iterator8; typedef typename fusion::result_of::next< fusion_iterator8>::type fusion_iterator9;
        typedef
            unpack_expr_<
                Tag
              , typename deduce_domain10<
                    typename add_const< typename fusion::result_of::value_of< fusion_iterator0 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator1 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator2 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator3 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator4 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator5 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator6 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator7 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator8 >::type >::type , typename add_const< typename fusion::result_of::value_of< fusion_iterator9 >::type >::type
                >::type
              , Sequence
              , 10
            >
        other;
        typedef typename other::type type;
        BOOST_FORCEINLINE
        static type const call(Sequence const &sequence)
        {
            return other::call(sequence);
        }
    };

/* unpack_expr_.hpp
begXZRmwABnr4pl8L8+BOQkr033faWUF2v3qPTn/G+cYLPQ/5h0a6gUbfG1xEmt6PXP3v1Y2rP9Hnh+surDcjRM7MGYwC2E/ZVXZzpjBDMJanXw/jz1ZW2c2deZnZUthZYTdmnGHM24nzErY9mNda7GXw5yEdXY5m8pagdkXGXpBfknGDOYmzCqk+XDO8AyckbAnTZvym8sAqyKsvl0y+3wIzFQ+p2X3k6wjmKewZRsNvzOvYTIuz948MGNewyoLm/7oUiHjCfMVVvp6T15zL6yksJCyFd9yxsHKCVt7Ii2CcdH2sO5OAWulUDMT/Id5BpPnfuhdQmP2XVg1YWerJY5VFrgBdSRs46CFrL9awjxhmduLr2CsYW7CKrtt9lDWBWYhbIZ9YBJjDXMVFmph9bey8dr93lgU/b3Kadr9btbJtGBNa9Z8x5E05ifMStjWXzy68Rxg3sJs/F884AzX1g19cOY7ngPMQ9jEjY7myqw24myFDXr0jn0pEGYu7G3H/KL3QW3d4s1z+jGeMBnPtAFHXBhPmLOwk2VHL1IWD5N7uBy6OIc9RLtfvwnz5ipbA7MWtuhD7GhlmTA7YeuWVinBeGr3M+y9zDmWDaskLPDoHM6j99q6ZzY7WdMmm1B/wiJPRbCOAmEyX/Y+br2X8YQ5CDuw+7KdsnBt3aT9jYspi4SVFZb88QBzMBZmJfP6sP8ZxhpmL+zUhol8Z0+ClRBW/cSFGZxVMBdhEQ6VmGeZMHnu7sFOzM+92v4c1tX8kbGGmQm7OqxU0d8FgNUQdi6qLc/IbLPx/TzOXvmLfRfmLuvozugnygJgMp7mqzPLcsbBAoWVPbGvi7IobV2832ZPZdGwisLqHK3E/SXDZL1H9C8TqWwzzElYD7cfjzM/tXV2PV8W/U0umJms9+9ud2cvgMlY+48bsZC5q+0hyvHxNObuFvRd2Sc2VTBlXGClhQ0Yt4Q5HwqT9dew7IxjyiJgvrLX5f3Ieo+FeQqz6v9H0Xc/TObZlKQZ1ZRlwByFnTjXL5H9E+Yk+1Li8kqc7zBbab/VrsCYwQzC1q4sw3x5DvMT1sl7WZ4yx63Gedb/w/ifGDOYq7AH1q67GBdYGWGbfNYPZy5pNmLj0XjOHJjsyaGtD+Vy5sDk/i7ef8o+nwKT/bPW3vZTWZswf2Fbzmw7yTyD+Qg7vnvcH6w/vD0ECMtotXgMex3MIGy5zZ/s5cEwub/XD+L6s5/BZC797jt3COsPJnOwa1pN9vnBmjXbaOjEmMHsZe/ZeSGKeQazEzb371X+nCswWUeL1hneMWawsrIvZZ8NUnYVJs+93utinB2vtf1l7ivjwPrLNM75hcEVOR9cYPJsByeMPcR+BpM5H+w8lL0gVLtm5wKLZM5pWHFh+WHxWYw1zFnYF6+y0criYKWEDV/TriFzECZ78tRmzfn+kgST/ax+Qr8VrGlhHrDhR4esYR+ElRM2pWcbPksBLFCYY9dvnDmO25CDwly9DvGdwRtWXVj+KBfO1A4wT2FvVo3Yzb3D1HO6w56Nn96MuQRzF3ZtevWW7PMwC2FPFr7aoWwnzF5Yu8jvBik7DXMV1nqB1TL2LJiVsEHjis6vEFZe2L0JAy8wLttx7sLmhxoOMs9gcg/3ff04x2pp6yIdfFJZ09q6uZ9+Zv11gMm977s82pp5BqsqbODgGw+ZLzBzYeFBg8qxn8E8hI302XNRWSbMIGyUm7MF5wOsnLB5m/76jr0OZimsa6MB15hnMCdhxSqdLc26xUlaC2vsas6ebICVEebVdU/R397X1h3q9XY9Z4e2bolviruycG1diOmRBYy1ts4s63f2rMEwL2GP+pn+zlhr1i98yW8=
*/