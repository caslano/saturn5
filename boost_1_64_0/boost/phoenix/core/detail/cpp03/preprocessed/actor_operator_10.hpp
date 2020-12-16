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
nPvbL98vxc/0Pbi/d0ulbxk+03F7f1cRvDjXKd9tfPo6/HRTvq9rGXx/PoAXG2/XKag/rscnGr/kYCf+YUzM2+RlP/4K/I+ejf914uPxB4z3HuHEx+P3Gp+H+8f/SYzx8al6a4b4wxX4Oan04/75R9LHx8923I6f2YrnO27Hz5QXxOT8NDXHxrwxjRvmz+CUv4v3wesc/+2QIL7nS7yD8Xfwpqlff8fbGR+xX1D+RI+Lec2Mr8L9++cUnqRU/TrupK9luv6CfxMJ3MZHr8M/d9yur/oA/qnjdn6xB/FPHLfxE/mnxbxnMoxfiafjj/A76stcx7slgviCU/FbjJ+WCO6vQnyV8TsTwfU9H/+Z8TaDnP65CTHvcNW+hXdw4ldt+b4R/yt/nuv4+ey/SSr9W/A3jT+Gp69mh4kx7yTjewx22ocK+f5z70+7/gD+Gzw3cJ5PZ/0B/NfGfzE4OP5NeAfjNc7xb8bbGR8yxKmfTgq+L7tkeL8Mw0c7bttvK/BOrtv8xw/yssf/34cPFfPv3I8nRP+INznmnaraP/CySPB9b+vfl+OFeIuU2/jgZfgpjtv321X4OMft+205fqLrNv69OOblifw5Ce8j8mcc3lP1P+Jx1T6GvyOu/2P4dsft/OrP41uMd88Ljv8lvtr4LNx/WqfGvJONb8b9+u3UoH2jU4bn5zN8peO2ffcrfLnjtv79Nb7MdRvfdDrtByq+CR+txs+fwfdlhu2bpvvv8KOMk36//OmJH2qc8t2vn/fHR3jZ558bjA9y3Jbv5fgeqv3P7N/eH6vw4aJ/82Z8kJo/Cz9KxD/vwI8Q8c8f46NF/+Yn+I/U/A7TYrL/uxxX84tV4ap//C5c9Y/fi6v+8TpcxgdOp34hPBeX/ee47D/HZf85LvvPcdl/jsv+c1z2n+Oy/3xGTPef47L/HJf957jsP8dl/zku+89x1b/9PK76t+MlMdm/3QNX/ds9cdW/3QtX/duVuOq/rql3FT82U9+/CVz1Xw/CVf91Eu+v6o+4nL8eH6XeD7jqX86dFZQvuZmeT3yB+36047vxea7b/ju8WGy/HT9VbF84m/eDuH7l+NtqfS/8TbF+zWFJro9Yv6YSf9dx2/68Fq//vu3k+KK2wf5fwq8zXt022H/NHN2/WIcPz9D+0j/le5TGdsa/xh1/u0tw/JH4NuN9ugZHuwpfZHw+7pcfZbp/rQKX/Xe47L8L8eoQrwk5fm3I9nUh7s3V+8+dq7ePh2yfCNk+H5+d+p2bYXz10Xhhczv+M/h+OAafYHwCnh4/MAYfb5z2ab998Fj8RMdt+3QFk9M+1zh7+lbgj+L9HJ/ZzZnfEn/Y+Go8nb5V+Frj3+Dp75sb8DuNF3YPUhO/JOYdJ+p3PfCxon7XEz9KvH974UeI928FvirD9e+Qzh98Wf3fHS9oF7Rf3ISf67idX7NwCfkjyv8i/H5R/hdcGvNeyrB969S/mIg/LtYvXoTf6GWfP+Fm/Bzj0T5O/OtlfN+I9adn4MNxkz9+/SuJ50Wy5g8XgPMX67c3wn/nuJ3/pxm+WszvPhw/W9Q/6vBa8fw3XUr7p+j/PBxfIMaPnIifIcaP5F7B95MYX9UBH6rGV+EXi/E9M/Cfe9n7D3Ov5P0itu+MzxXbV+O7q/Idbyy8Dn+fynaJc33yBtLGzK+d219H+2Vje38E8+W+j7+Dd3H8sQFB/9AH+HbjjfYJ+oc+xF81fiLeOvXra3yz43Z+3sqbY/742vYZns9b8Fcct9/vv8W3Om6/32/Fnzdeh6fHx67Bn3Hcfr9X07l7fMP2Tf95XI8fa5z0+f03G/CjHbftxw/jRzpu248fwQ933KYveavf/uE=
*/