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