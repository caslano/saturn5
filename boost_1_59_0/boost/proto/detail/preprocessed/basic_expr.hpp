    ///////////////////////////////////////////////////////////////////////////////
    /// \file basic_expr.hpp
    /// Contains definition of basic_expr\<\> class template.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag, typename Arg0>
    struct basic_expr<Tag, term<Arg0>, 0>
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 0;
        typedef mpl::long_<0 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef term<Arg0> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0;
        typedef void proto_child1; typedef void proto_child2; typedef void proto_child3; typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 &a0)
        {
            return detail::make_terminal(a0, static_cast<basic_expr *>(0), static_cast<proto_args *>(0));
        }
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0)
        {
            return detail::make_terminal(a0, static_cast<basic_expr *>(0), static_cast<proto_args *>(0));
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0>
    struct basic_expr<Tag, list1<Arg0>, 1 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 1;
        typedef mpl::long_<1 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list1<Arg0> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0;
        typedef void proto_child1; typedef void proto_child2; typedef void proto_child3; typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0)
        {
            basic_expr that = {a0};
            return that;
        }
        
        
        
        typedef typename detail::address_of_hack<Tag, proto_child0>::type address_of_hack_type_;
        
        
        
        
        
        
        
        BOOST_FORCEINLINE
        operator address_of_hack_type_() const
        {
            return boost::addressof(this->child0);
        }
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1>
    struct basic_expr<Tag, list2<Arg0 , Arg1>, 2 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 2;
        typedef mpl::long_<2 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list2<Arg0 , Arg1> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1;
        typedef void proto_child2; typedef void proto_child3; typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1)
        {
            basic_expr that = {a0 , a1};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2>
    struct basic_expr<Tag, list3<Arg0 , Arg1 , Arg2>, 3 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 3;
        typedef mpl::long_<3 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list3<Arg0 , Arg1 , Arg2> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2;
        typedef void proto_child3; typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2)
        {
            basic_expr that = {a0 , a1 , a2};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3>
    struct basic_expr<Tag, list4<Arg0 , Arg1 , Arg2 , Arg3>, 4 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 4;
        typedef mpl::long_<4 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list4<Arg0 , Arg1 , Arg2 , Arg3> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3;
        typedef void proto_child4; typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3)
        {
            basic_expr that = {a0 , a1 , a2 , a3};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4>
    struct basic_expr<Tag, list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4>, 5 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 5;
        typedef mpl::long_<5 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list5<Arg0 , Arg1 , Arg2 , Arg3 , Arg4> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4;
        typedef void proto_child5; typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4)
        {
            basic_expr that = {a0 , a1 , a2 , a3 , a4};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5>
    struct basic_expr<Tag, list6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5>, 6 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 6;
        typedef mpl::long_<6 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list6<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5;
        typedef void proto_child6; typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5)
        {
            basic_expr that = {a0 , a1 , a2 , a3 , a4 , a5};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6>
    struct basic_expr<Tag, list7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6>, 7 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 7;
        typedef mpl::long_<7 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list7<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5; typedef Arg6 proto_child6; proto_child6 child6;
        typedef void proto_child7; typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6)
        {
            basic_expr that = {a0 , a1 , a2 , a3 , a4 , a5 , a6};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7>
    struct basic_expr<Tag, list8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7>, 8 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 8;
        typedef mpl::long_<8 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list8<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5; typedef Arg6 proto_child6; proto_child6 child6; typedef Arg7 proto_child7; proto_child7 child7;
        typedef void proto_child8; typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7)
        {
            basic_expr that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8>
    struct basic_expr<Tag, list9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8>, 9 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 9;
        typedef mpl::long_<9 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list9<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5; typedef Arg6 proto_child6; proto_child6 child6; typedef Arg7 proto_child7; proto_child7 child7; typedef Arg8 proto_child8; proto_child8 child8;
        typedef void proto_child9;
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8)
        {
            basic_expr that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Tag , typename Arg0 , typename Arg1 , typename Arg2 , typename Arg3 , typename Arg4 , typename Arg5 , typename Arg6 , typename Arg7 , typename Arg8 , typename Arg9>
    struct basic_expr<Tag, list10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9>, 10 >
    {
        typedef Tag proto_tag;
        static const long proto_arity_c = 10;
        typedef mpl::long_<10 > proto_arity;
        typedef basic_expr proto_base_expr;
        typedef list10<Arg0 , Arg1 , Arg2 , Arg3 , Arg4 , Arg5 , Arg6 , Arg7 , Arg8 , Arg9> proto_args;
        typedef basic_expr proto_grammar;
        typedef basic_default_domain proto_domain;
        typedef default_generator proto_generator;
        typedef proto::tag::proto_expr<Tag, proto_domain> fusion_tag;
        typedef basic_expr proto_derived_expr;
        typedef void proto_is_expr_; 
        typedef Arg0 proto_child0; proto_child0 child0; typedef Arg1 proto_child1; proto_child1 child1; typedef Arg2 proto_child2; proto_child2 child2; typedef Arg3 proto_child3; proto_child3 child3; typedef Arg4 proto_child4; proto_child4 child4; typedef Arg5 proto_child5; proto_child5 child5; typedef Arg6 proto_child6; proto_child6 child6; typedef Arg7 proto_child7; proto_child7 child7; typedef Arg8 proto_child8; proto_child8 child8; typedef Arg9 proto_child9; proto_child9 child9;
        
        
        
        BOOST_FORCEINLINE
        basic_expr const &proto_base() const
        {
            return *this;
        }
        
        
        BOOST_FORCEINLINE
        basic_expr &proto_base()
        {
            return *this;
        }
        
        
        
        template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        BOOST_FORCEINLINE
        static basic_expr const make(A0 const &a0 , A1 const &a1 , A2 const &a2 , A3 const &a3 , A4 const &a4 , A5 const &a5 , A6 const &a6 , A7 const &a7 , A8 const &a8 , A9 const &a9)
        {
            basic_expr that = {a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9};
            return that;
        }
        
        
        typedef detail::not_a_valid_type address_of_hack_type_;
    };

/* basic_expr.hpp
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
*/