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