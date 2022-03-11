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