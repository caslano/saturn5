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