        ///////////////////////////////////////////////////////////////////////////////
        /// \file expr.hpp
        /// Contains definition of expr\<\> class template.
        //
        //  Copyright 2008 Eric Niebler. Distributed under the Boost
        //  Software License, Version 1.0. (See accompanying file
        //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag, typename Arg0>
    struct expr<Tag, term<Arg0>, 0>
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 0;
        typedef mpl::long_<0 > proto_arity;
        typedef expr proto_base_expr;
        typedef term<Arg0> proto_args;
        typedef basic_expr<Tag, proto_args, 0 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0;
        typedef void proto_child1; typedef void proto_child2; typedef void proto_child3; typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        static expr const make(A0 &a0)
        {
            return detail::make_terminal(a0, static_cast<expr *>(0), static_cast<proto_args *>(0));
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0)
        {
            return detail::make_terminal(a0, static_cast<expr *>(0), static_cast<proto_args *>(0));
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a)
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a)
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr &>, 1> const
        operator ()()
        {
            proto::expr<proto::tag::function, list1<expr &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0)
        {
            return result_of::funop1<
                expr
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1)
        {
            return result_of::funop2<
                expr
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2)
        {
            return result_of::funop3<
                expr
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3)
        {
            return result_of::funop4<
                expr
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4)
        {
            return result_of::funop5<
                expr
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5)
        {
            return result_of::funop6<
                expr
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6)
        {
            return result_of::funop7<
                expr
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7)
        {
            return result_of::funop8<
                expr
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8)
        {
            return result_of::funop9<
                expr
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0>
    struct expr<Tag, list1<Arg0>, 1 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 1;
        typedef mpl::long_<1 > proto_arity;
        typedef expr proto_base_expr;
        typedef list1<Arg0> proto_args;
        typedef basic_expr<Tag, proto_args, 1 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0;
        typedef void proto_child1; typedef void proto_child2; typedef void proto_child3; typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0)
        {
            expr that = {a0};
            return that;
        }
        
        
        
        typedef typename detail::address_of_hack<Tag, proto_child0>::type address_of_hack_type_;
        
        
        
        
        
        
        
        BOOST_FORCEINLINE
        operator address_of_hack_type_() const
        {
            return boost::addressof(this->child0);
        }
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1>
    struct expr<Tag, list2<Arg0 , Arg1>, 2 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 2;
        typedef mpl::long_<2 > proto_arity;
        typedef expr proto_base_expr;
        typedef list2<Arg0 , Arg1> proto_args;
        typedef basic_expr<Tag, proto_args, 2 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1;
        typedef void proto_child2; typedef void proto_child3; typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1)
        {
            expr that = {a0 , a1};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2>
    struct expr<Tag, list3<Arg0 , Arg1 , Arg2>, 3 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 3;
        typedef mpl::long_<3 > proto_arity;
        typedef expr proto_base_expr;
        typedef list3<Arg0 , Arg1 , Arg2> proto_args;
        typedef basic_expr<Tag, proto_args, 3 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2;
        typedef void proto_child3; typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2)
        {
            expr that = {a0 , a1 , a2};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    struct expr<Tag, list4<Arg0 , Arg1 , Arg2 , Arg3>, 4 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 4;
        typedef mpl::long_<4 > proto_arity;
        typedef expr proto_base_expr;
        typedef list4<Arg0 , Arg1 , Arg2 , Arg3> proto_args;
        typedef basic_expr<Tag, proto_args, 4 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3;
        typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3)
        {
            expr that = {a0 , a1 , a2 , a3};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    struct expr<Tag, list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>, 5 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 5;
        typedef mpl::long_<5 > proto_arity;
        typedef expr proto_base_expr;
        typedef list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4> proto_args;
        typedef basic_expr<Tag, proto_args, 5 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4;
        typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4)
        {
            expr that = {a0 , a1 , a2 , a3 , a4};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    struct expr<Tag, list6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>, 6 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 6;
        typedef mpl::long_<6 > proto_arity;
        typedef expr proto_base_expr;
        typedef list6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5> proto_args;
        typedef basic_expr<Tag, proto_args, 6 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5;
        typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5)
        {
            expr that = {a0 , a1 , a2 , a3 , a4 , a5};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    struct expr<Tag, list7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>, 7 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 7;
        typedef mpl::long_<7 > proto_arity;
        typedef expr proto_base_expr;
        typedef list7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6> proto_args;
        typedef basic_expr<Tag, proto_args, 7 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5; typedef Arg6 proto_child6; proto_child6 child6;
        typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6)
        {
            expr that = {a0 , a1 , a2 , a3 , a4 , a5 , a6};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    struct expr<Tag, list8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>, 8 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 8;
        typedef mpl::long_<8 > proto_arity;
        typedef expr proto_base_expr;
        typedef list8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7> proto_args;
        typedef basic_expr<Tag, proto_args, 8 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5; typedef Arg6 proto_child6; proto_child6 child6; typedef Arg7 proto_child7; proto_child7 child7;
        typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7)
        {
            expr that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    struct expr<Tag, list9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8>, 9 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 9;
        typedef mpl::long_<9 > proto_arity;
        typedef expr proto_base_expr;
        typedef list9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8> proto_args;
        typedef basic_expr<Tag, proto_args, 9 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5; typedef Arg6 proto_child6; proto_child6 child6; typedef Arg7 proto_child7; proto_child7 child7; typedef Arg8 proto_child8; proto_child8 child8;
        typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8)
        {
            expr that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    struct expr<Tag, list10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9>, 10 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 10;
        typedef mpl::long_<10 > proto_arity;
        typedef expr proto_base_expr;
        typedef list10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9> proto_args;
        typedef basic_expr<Tag, proto_args, 10 > proto_grammar;
        typedef default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5; typedef Arg6 proto_child6; proto_child6 child6; typedef Arg7 proto_child7; proto_child7 child7; typedef Arg8 proto_child8; proto_child8 child8; typedef Arg9 proto_child9; proto_child9 child9;
        
        
        
        BOOST_FORCEINLINE
        expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        BOOST_FORCEINLINE
        static expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8 , A9 const &a9)
        {
            expr that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
        
        
        
        
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr &, expr const &>
          , 2
        > const
        operator =(expr const &a)
        {
            proto::expr<
                proto::tag::assign
              , list2<expr &, expr const &>
              , 2
            > that = {*this, a};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator =(A &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::assign
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator =(A const &a) const
        {
            proto::expr<
                proto::tag::assign
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A>::type>
          , 2
        > const
        operator [](A &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename A>
        BOOST_FORCEINLINE
        proto::expr<
            proto::tag::subscript
          , list2<expr const &, typename result_of::as_child<A const>::type>
          , 2
        > const
        operator [](A const &a) const
        {
            proto::expr<
                proto::tag::subscript
              , list2<expr const &, typename result_of::as_child<A const>::type>
              , 2
            > that = {*this, proto::as_child(a)};
            return that;
        }
        
        
        template<typename Sig>
        struct result
        {
            typedef typename result_of::funop<Sig, expr, default_domain>::type const type;
        };
        
        
        
        BOOST_FORCEINLINE
        proto::expr<proto::tag::function, list1<expr const &>, 1> const
        operator ()() const
        {
            proto::expr<proto::tag::function, list1<expr const &>, 1> that = {*this};
            return that;
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        typename result_of::funop1<
            expr const
          , default_domain , const A0
        >::type const
        operator ()(A0 const &a0) const
        {
            return result_of::funop1<
                expr const
              , default_domain , const A0
            >::call(*this , a0);
        }
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        typename result_of::funop2<
            expr const
          , default_domain , const A0 , const A1
        >::type const
        operator ()(A0 const &a0 , A1 const &a1) const
        {
            return result_of::funop2<
                expr const
              , default_domain , const A0 , const A1
            >::call(*this , a0 , a1);
        }
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        typename result_of::funop3<
            expr const
          , default_domain , const A0 , const A1 , const A2
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2) const
        {
            return result_of::funop3<
                expr const
              , default_domain , const A0 , const A1 , const A2
            >::call(*this , a0 , a1 , a2);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        typename result_of::funop4<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3) const
        {
            return result_of::funop4<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3
            >::call(*this , a0 , a1 , a2 , a3);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        typename result_of::funop5<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4) const
        {
            return result_of::funop5<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4
            >::call(*this , a0 , a1 , a2 , a3 , a4);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        typename result_of::funop6<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5) const
        {
            return result_of::funop6<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        typename result_of::funop7<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6) const
        {
            return result_of::funop7<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        typename result_of::funop8<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7) const
        {
            return result_of::funop8<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        typename result_of::funop9<
            expr const
          , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
        >::type const
        operator ()(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8) const
        {
            return result_of::funop9<
                expr const
              , default_domain , const A0 , const A1 , const A2 , const A3 , const A4 , const A5 , const A6 , const A7 , const A8
            >::call(*this , a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    };

/* expr.hpp
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
*/