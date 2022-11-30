    ///////////////////////////////////////////////////////////////////////////////
    /// \file expr_variadic.hpp
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
        }
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a)
        {
            return result_of::funop<
                expr(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
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
        
        
        template<typename ...A>
        BOOST_FORCEINLINE
        typename result_of::funop<
            expr const(A const &...)
          , expr
          , default_domain
        >::type const
        operator ()(A const &... a) const
        {
            return result_of::funop<
                expr const(A const &...)
              , expr
              , default_domain
            >::call(*this, a...);
        }
    };
    

/* expr_variadic.hpp
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
*/