/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
    
    
    
    
    
    
    
        template <typename This, typename A0>
        struct result<This(A0)>
            : result<This(typename detail::result_type_deduction_helper<A0>::type)>
        {};
        template <typename This, typename A0> struct result<This(A0 &)> : result_of::actor<proto_base_expr, A0 &> {}; template <typename A0> typename result_of::actor<proto_base_expr, A0 &>::type operator()(A0 & a0) const { typedef vector2< const actor<Expr> *, A0 & > env_type; env_type env = {this, a0}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename A0> typename result_of::actor<proto_base_expr, A0 &>::type operator()(A0 & a0) { typedef vector2< const actor<Expr> *, A0 & > env_type; env_type env = {this, a0}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename This, typename A0> struct result<This(A0 const&)> : result_of::actor<proto_base_expr, A0 const&> {}; template <typename A0> typename result_of::actor<proto_base_expr, A0 const&>::type operator()(A0 const& a0) const { typedef vector2< const actor<Expr> *, A0 const& > env_type; env_type env = {this, a0}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename A0> typename result_of::actor<proto_base_expr, A0 const&>::type operator()(A0 const& a0) { typedef vector2< const actor<Expr> *, A0 const& > env_type; env_type env = {this, a0}; return phoenix::eval(*this, phoenix::context(env, default_actions())); }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1>
        struct result<This(A0 , A1)>
            : result<This(typename detail::result_type_deduction_helper<A0>::type , typename detail::result_type_deduction_helper<A1>::type)>
        {};
        template <typename This, typename A0 , typename A1> struct result<This(A0 & , A1 &)> : result_of::actor<proto_base_expr, A0 & , A1 &> {}; template <typename A0 , typename A1> typename result_of::actor<proto_base_expr, A0 & , A1 &>::type operator()(A0 & a0 , A1 & a1) const { typedef vector3< const actor<Expr> *, A0 & , A1 & > env_type; env_type env = {this, a0 , a1}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename A0 , typename A1> typename result_of::actor<proto_base_expr, A0 & , A1 &>::type operator()(A0 & a0 , A1 & a1) { typedef vector3< const actor<Expr> *, A0 & , A1 & > env_type; env_type env = {this, a0 , a1}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename This, typename A0 , typename A1> struct result<This(A0 & , A1 const&)> : result_of::actor<proto_base_expr, A0 & , A1 const&> {}; template <typename A0 , typename A1> typename result_of::actor<proto_base_expr, A0 & , A1 const&>::type operator()(A0 & a0 , A1 const& a1) const { typedef vector3< const actor<Expr> *, A0 & , A1 const& > env_type; env_type env = {this, a0 , a1}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename A0 , typename A1> typename result_of::actor<proto_base_expr, A0 & , A1 const&>::type operator()(A0 & a0 , A1 const& a1) { typedef vector3< const actor<Expr> *, A0 & , A1 const& > env_type; env_type env = {this, a0 , a1}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename This, typename A0 , typename A1> struct result<This(A0 const& , A1 &)> : result_of::actor<proto_base_expr, A0 const& , A1 &> {}; template <typename A0 , typename A1> typename result_of::actor<proto_base_expr, A0 const& , A1 &>::type operator()(A0 const& a0 , A1 & a1) const { typedef vector3< const actor<Expr> *, A0 const& , A1 & > env_type; env_type env = {this, a0 , a1}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename A0 , typename A1> typename result_of::actor<proto_base_expr, A0 const& , A1 &>::type operator()(A0 const& a0 , A1 & a1) { typedef vector3< const actor<Expr> *, A0 const& , A1 & > env_type; env_type env = {this, a0 , a1}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename This, typename A0 , typename A1> struct result<This(A0 const& , A1 const&)> : result_of::actor<proto_base_expr, A0 const& , A1 const&> {}; template <typename A0 , typename A1> typename result_of::actor<proto_base_expr, A0 const& , A1 const&>::type operator()(A0 const& a0 , A1 const& a1) const { typedef vector3< const actor<Expr> *, A0 const& , A1 const& > env_type; env_type env = {this, a0 , a1}; return phoenix::eval(*this, phoenix::context(env, default_actions())); } template <typename A0 , typename A1> typename result_of::actor<proto_base_expr, A0 const& , A1 const&>::type operator()(A0 const& a0 , A1 const& a1) { typedef vector3< const actor<Expr> *, A0 const& , A1 const& > env_type; env_type env = {this, a0 , a1}; return phoenix::eval(*this, phoenix::context(env, default_actions())); }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2>
        struct result<This(A0 , A1 , A2)>
            : result<This(A0 const& , A1 const& , A2 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2>
        struct result<This(A0 & , A1 & , A2 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 &>
        {};
        template <typename A0 , typename A1 , typename A2>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2)
        {
            typedef
                vector4<
                    const actor<Expr> *, A0 & , A1 & , A2 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2) const
        {
            typedef
                vector4<
                    const actor<Expr> *, A0 & , A1 & , A2 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2)
        {
            typedef
                vector4<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2) const
        {
            typedef
                vector4<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3>
        struct result<This(A0 , A1 , A2 , A3)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3>
        struct result<This(A0 & , A1 & , A2 & , A3 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3)
        {
            typedef
                vector5<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3) const
        {
            typedef
                vector5<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3)
        {
            typedef
                vector5<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3) const
        {
            typedef
                vector5<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct result<This(A0 , A1 , A2 , A3 , A4)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4)
        {
            typedef
                vector6<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4) const
        {
            typedef
                vector6<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4)
        {
            typedef
                vector6<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4) const
        {
            typedef
                vector6<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5)
        {
            typedef
                vector7<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5) const
        {
            typedef
                vector7<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5)
        {
            typedef
                vector7<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5) const
        {
            typedef
                vector7<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6)
        {
            typedef
                vector8<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6) const
        {
            typedef
                vector8<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6)
        {
            typedef
                vector8<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6) const
        {
            typedef
                vector8<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7)
        {
            typedef
                vector9<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7) const
        {
            typedef
                vector9<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7)
        {
            typedef
                vector9<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7) const
        {
            typedef
                vector9<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8)
        {
            typedef
                vector10<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8) const
        {
            typedef
                vector10<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8)
        {
            typedef
                vector10<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8) const
        {
            typedef
                vector10<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9)
        {
            typedef
                vector11<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9) const
        {
            typedef
                vector11<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9)
        {
            typedef
                vector11<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9) const
        {
            typedef
                vector11<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

/* actor_operator_10.hpp
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
*/