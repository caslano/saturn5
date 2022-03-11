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
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10)
        {
            typedef
                vector12<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10) const
        {
            typedef
                vector12<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10)
        {
            typedef
                vector12<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10) const
        {
            typedef
                vector12<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11)
        {
            typedef
                vector13<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11) const
        {
            typedef
                vector13<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11)
        {
            typedef
                vector13<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11) const
        {
            typedef
                vector13<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12)
        {
            typedef
                vector14<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12) const
        {
            typedef
                vector14<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12)
        {
            typedef
                vector14<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12) const
        {
            typedef
                vector14<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13)
        {
            typedef
                vector15<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13) const
        {
            typedef
                vector15<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13)
        {
            typedef
                vector15<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13) const
        {
            typedef
                vector15<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14)
        {
            typedef
                vector16<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14) const
        {
            typedef
                vector16<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14)
        {
            typedef
                vector16<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14) const
        {
            typedef
                vector16<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15)
        {
            typedef
                vector17<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15) const
        {
            typedef
                vector17<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15)
        {
            typedef
                vector17<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15) const
        {
            typedef
                vector17<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16)
        {
            typedef
                vector18<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16) const
        {
            typedef
                vector18<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16)
        {
            typedef
                vector18<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16) const
        {
            typedef
                vector18<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17)
        {
            typedef
                vector19<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17) const
        {
            typedef
                vector19<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17)
        {
            typedef
                vector19<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17) const
        {
            typedef
                vector19<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18)
        {
            typedef
                vector20<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18) const
        {
            typedef
                vector20<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18)
        {
            typedef
                vector20<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18) const
        {
            typedef
                vector20<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19)
        {
            typedef
                vector21<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19) const
        {
            typedef
                vector21<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19)
        {
            typedef
                vector21<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19) const
        {
            typedef
                vector21<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20)
        {
            typedef
                vector22<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20) const
        {
            typedef
                vector22<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20)
        {
            typedef
                vector22<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20) const
        {
            typedef
                vector22<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21)
        {
            typedef
                vector23<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21) const
        {
            typedef
                vector23<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21)
        {
            typedef
                vector23<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21) const
        {
            typedef
                vector23<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22)
        {
            typedef
                vector24<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22) const
        {
            typedef
                vector24<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22)
        {
            typedef
                vector24<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22) const
        {
            typedef
                vector24<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23)
        {
            typedef
                vector25<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23) const
        {
            typedef
                vector25<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23)
        {
            typedef
                vector25<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23) const
        {
            typedef
                vector25<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24)
        {
            typedef
                vector26<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24) const
        {
            typedef
                vector26<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24)
        {
            typedef
                vector26<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24) const
        {
            typedef
                vector26<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25)
        {
            typedef
                vector27<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25) const
        {
            typedef
                vector27<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25)
        {
            typedef
                vector27<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25) const
        {
            typedef
                vector27<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26)
        {
            typedef
                vector28<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26) const
        {
            typedef
                vector28<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26)
        {
            typedef
                vector28<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26) const
        {
            typedef
                vector28<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27)
        {
            typedef
                vector29<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27) const
        {
            typedef
                vector29<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27)
        {
            typedef
                vector29<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27) const
        {
            typedef
                vector29<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28)
        {
            typedef
                vector30<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28) const
        {
            typedef
                vector30<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28)
        {
            typedef
                vector30<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28) const
        {
            typedef
                vector30<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29)
        {
            typedef
                vector31<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29) const
        {
            typedef
                vector31<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29)
        {
            typedef
                vector31<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29) const
        {
            typedef
                vector31<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30)
        {
            typedef
                vector32<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30) const
        {
            typedef
                vector32<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30)
        {
            typedef
                vector32<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30) const
        {
            typedef
                vector32<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31)
        {
            typedef
                vector33<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31) const
        {
            typedef
                vector33<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31)
        {
            typedef
                vector33<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31) const
        {
            typedef
                vector33<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32)
        {
            typedef
                vector34<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32) const
        {
            typedef
                vector34<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32)
        {
            typedef
                vector34<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32) const
        {
            typedef
                vector34<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33)
        {
            typedef
                vector35<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33) const
        {
            typedef
                vector35<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33)
        {
            typedef
                vector35<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33) const
        {
            typedef
                vector35<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34)
        {
            typedef
                vector36<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34) const
        {
            typedef
                vector36<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34)
        {
            typedef
                vector36<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34) const
        {
            typedef
                vector36<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35)
        {
            typedef
                vector37<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35) const
        {
            typedef
                vector37<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35)
        {
            typedef
                vector37<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35) const
        {
            typedef
                vector37<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36)
        {
            typedef
                vector38<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36) const
        {
            typedef
                vector38<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36)
        {
            typedef
                vector38<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36) const
        {
            typedef
                vector38<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37)
        {
            typedef
                vector39<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37) const
        {
            typedef
                vector39<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37)
        {
            typedef
                vector39<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37) const
        {
            typedef
                vector39<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37 , A38 & a38)
        {
            typedef
                vector40<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37 , A38 & a38) const
        {
            typedef
                vector40<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38)
        {
            typedef
                vector40<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38) const
        {
            typedef
                vector40<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
    
    
    
    
    
    
    
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        struct result<This(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9 , A10 , A11 , A12 , A13 , A14 , A15 , A16 , A17 , A18 , A19 , A20 , A21 , A22 , A23 , A24 , A25 , A26 , A27 , A28 , A29 , A30 , A31 , A32 , A33 , A34 , A35 , A36 , A37 , A38 , A39)>
            : result<This(A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const& , A39 const&)>
        {};
        template <typename This, typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        struct result<This(A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 & , A39 &)>
            : result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 & , A39 &>
        {};
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 & , A39 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37 , A38 & a38 , A39 & a39)
        {
            typedef
                vector41<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 & , A39 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        typename result_of::actor<proto_base_expr, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 & , A39 &>::type
        operator()(A0 & a0 , A1 & a1 , A2 & a2 , A3 & a3 , A4 & a4 , A5 & a5 , A6 & a6 , A7 & a7 , A8 & a8 , A9 & a9 , A10 & a10 , A11 & a11 , A12 & a12 , A13 & a13 , A14 & a14 , A15 & a15 , A16 & a16 , A17 & a17 , A18 & a18 , A19 & a19 , A20 & a20 , A21 & a21 , A22 & a22 , A23 & a23 , A24 & a24 , A25 & a25 , A26 & a26 , A27 & a27 , A28 & a28 , A29 & a29 , A30 & a30 , A31 & a31 , A32 & a32 , A33 & a33 , A34 & a34 , A35 & a35 , A36 & a36 , A37 & a37 , A38 & a38 , A39 & a39) const
        {
            typedef
                vector41<
                    const actor<Expr> *, A0 & , A1 & , A2 & , A3 & , A4 & , A5 & , A6 & , A7 & , A8 & , A9 & , A10 & , A11 & , A12 & , A13 & , A14 & , A15 & , A16 & , A17 & , A18 & , A19 & , A20 & , A21 & , A22 & , A23 & , A24 & , A25 & , A26 & , A27 & , A28 & , A29 & , A30 & , A31 & , A32 & , A33 & , A34 & , A35 & , A36 & , A37 & , A38 & , A39 &
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const& , A39 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39)
        {
            typedef
                vector41<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const& , A39 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }
        template <typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9 , typename A10 , typename A11 , typename A12 , typename A13 , typename A14 , typename A15 , typename A16 , typename A17 , typename A18 , typename A19 , typename A20 , typename A21 , typename A22 , typename A23 , typename A24 , typename A25 , typename A26 , typename A27 , typename A28 , typename A29 , typename A30 , typename A31 , typename A32 , typename A33 , typename A34 , typename A35 , typename A36 , typename A37 , typename A38 , typename A39>
        typename result_of::actor<proto_base_expr, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const& , A39 const&>::type
        operator()(A0 const& a0 , A1 const& a1 , A2 const& a2 , A3 const& a3 , A4 const& a4 , A5 const& a5 , A6 const& a6 , A7 const& a7 , A8 const& a8 , A9 const& a9 , A10 const& a10 , A11 const& a11 , A12 const& a12 , A13 const& a13 , A14 const& a14 , A15 const& a15 , A16 const& a16 , A17 const& a17 , A18 const& a18 , A19 const& a19 , A20 const& a20 , A21 const& a21 , A22 const& a22 , A23 const& a23 , A24 const& a24 , A25 const& a25 , A26 const& a26 , A27 const& a27 , A28 const& a28 , A29 const& a29 , A30 const& a30 , A31 const& a31 , A32 const& a32 , A33 const& a33 , A34 const& a34 , A35 const& a35 , A36 const& a36 , A37 const& a37 , A38 const& a38 , A39 const& a39) const
        {
            typedef
                vector41<
                    const actor<Expr> *, A0 const& , A1 const& , A2 const& , A3 const& , A4 const& , A5 const& , A6 const& , A7 const& , A8 const& , A9 const& , A10 const& , A11 const& , A12 const& , A13 const& , A14 const& , A15 const& , A16 const& , A17 const& , A18 const& , A19 const& , A20 const& , A21 const& , A22 const& , A23 const& , A24 const& , A25 const& , A26 const& , A27 const& , A28 const& , A29 const& , A30 const& , A31 const& , A32 const& , A33 const& , A34 const& , A35 const& , A36 const& , A37 const& , A38 const& , A39 const&
                >
                env_type;
            env_type env = {this, a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9 , a10 , a11 , a12 , a13 , a14 , a15 , a16 , a17 , a18 , a19 , a20 , a21 , a22 , a23 , a24 , a25 , a26 , a27 , a28 , a29 , a30 , a31 , a32 , a33 , a34 , a35 , a36 , a37 , a38 , a39};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

/* actor_operator_40.hpp
kJzrXwAbNfIOcvOBalbvhKLGUpxQsn9HHxbF70Xa1VaJN52IWmrrNANkupwIrAcwsg3waE6m9U+1J6JFqxExL+NMJWJHyn0HrtZBJbpkg8+k314Sy8gd12jJUdu/aLdKt3kXkrx+WDG2t27HgryG0AoxtmmuWhbSy5mXF6UhWKRA4F8xW2TS0qBaIaWGhY1RthSwc6EXpvVPDBoYt4JH2+AZaZnDWLRX1fjwSMAlFM7bnCkUIHm8Qt5e8nXAQApxBYa70TZkJNOwdIKqnXtHwhxmFZrMDTWdnS+CrWv3dnHzt4KHD3OdfFMolX+4WVwa3/KsfVjbm60EKKDJg/Yng1EOruIdp3hwQ7x4G06fXeO2JIe95sYfPDLXlpddkCecR1A9vxrkLazY0q8Tx9TvnkZ1vZvLstB9J1ZuyprHThj0+NJhhKGYDUpomJ+OStzRZ2gbtbWPy5oDaq8SUmPH7z4esVW39QfJwlZPc2B26DP02bO9+67QamUd0/jQ0Aj1kWebT7+DJ7iTku10qQtFXsCwyIYGN+zB9PQjaLaHDLuQIKfCSmPhFDOUn0pyr6lZxENUrcKmGElEG8K1nfzalwmRPT3TY0h5Z4HXcoFQBXqVg5D18Kjq7AbC5pnhp5VfFgsM1m3Q43BbwzLkE2m4FHrmrbMfRtVtxIzcyXN9RkHWxBt05NNBq7Sk9qw/kkfIAUoXjy+EgOcvnIEgFKRIsVjVoNwX1v2LLlfHWKxYPmhsbhptpPT3tObgQRJtgBjZjZtQv++dPdq8BycIv+8hPN42bnzDApaP5ylrakHEEzYrpjdqtDRsSfXg0EUGkJH19NQcf7C2V1vrRm5N1FMF81/i30rshYH7KEibAZeSRxgmaouxZmRQPKGG9tsI0WgkHeFxK73wZT7O5uL+HEMszf0MAouUrMWM3+DOj7rCbMm1fqynZth1FOVEMZLeFGDZY/lttSeoDjhGHsODpzmWNDUBQODqtw+0g8glCCTRiBSAvB0zW+5WN5mLTijddNi3UtTC3ig+weTu8uH7AdGOssxa0SMr33TCWPsBG+9rhXH1LhIiudbfd6e28vjlwd1lHeENC5vlavxBbarpGbyotYEdkMPPcRksmApwY9tR8lvDPuPtw3XEELzbiK0HJFCtD51niZBsGGJvioX4MjWCwcfWLDCq1YM0U5KBwMKqKKjukOjh8bfNANrKDCGuh9mt8mQibFGR3kzLfpv9AtecGbk9a5WJtkbFPvzeYdvvH2NLr9JJeDyENVNKTB50csOZ56nAs2burE/6+zH8wAKvrMdGaIkhJpc9mX/btETXoT/vprU4H8S237mq0rAdaKWEPW6ooGGlgCo1bojFB2NsptI2m0oYDTzeHy69rXTP/VgLtNZEKkfzc/oR+3e3moAmlGlwW/4Gfd/sy0dkW4Qf50rXt9sZKxsiOoWMaIZ6QfwpmvkEaiqBaKotd3mgUj9iXpb/TLrJyM+UuYdBYBmEWWDR6YyEfciWNtdh4Z+HwMn0qYA8/HN5Df9cruajFL9h+R5RFYFaVjBfCp1I0w9TBn/nue1ZdrGRT9q1Rbg0scT17Gy0p4nbKkjvax8dQuTCEpraxSkMNULsB7GOR5IM6FtxX2kwb7Fw5RiM+Ia/cJi1e3q2r1S0gIs1GCJRIRmiZwFl6fXA7EbXtuwhoOVcSdOskgHYlRJFC3Pl8cV3D2zJgG8dT1zA7Y4dWWWO65zsjl2YTUFKVqHmAiclWSD1TQ1S4xnXEve/ypZvnC0uSPEJvLIRRvAHZ9JnUIwxZzNjWCjh/A0EZOLHtTur0PrSHJW8hlJF3t040vxoL2BCTTJ+cAKkUsfSl29BZPgJQFGk4IJ0IB4xq4reL95YH7+lYi+HsaeiPtAxdlMKrSQzov5/zYNV05O2BTT1GXldyYQN+DWCD15thbzfBpxbzogyCy97YPEft6VOb36RYEuOGLnnB8YcAGHQcEji649Xt5JQcH9UqrzFG65t4swfNvoPYgQmWv2bUb7u06cJOWixapfCHTZhHMWjI1obghC+W1ibR22srpjX1C2qFbdjQIWfKevnDLWtrdop5qkhl0+3DmXOwjnQnHwy5+ZP/Sx0gwX1waMQPRMdOvGg3P+kT2mMmvhQtUEEiTvyIB8FbWoGhCb2VQd9xJFK4zGyypr+xR9/F7FV/VqYrfn3PwAkgNt/Do9fBHj5HN2CkLjQ+6bitzSfgTsvqGtsKva+3DOTvBUbE5BH81soaCrHDju3zIlomVsLCzLJiCosabbDZpvQMJ1E2B/RQpX4Ch9jmOwAYjsFWKe2+o9Ruo3+HAhcrQRrFZf7ZZHzBH1r8v4rTHh188+HCb8n8FKlWjdQhNb/N8EWdENb20wXCbZGJU/2a7pbytPpgiQQAFsVCGcu3H0OO9EKi7ELgyH1Px24TcXjzbHyXNCZQAPb8jj67p0dUsf+lTaxttxOgg8nd5soZyGM20YeqiJmwMUvf8hKOdfc+nP0Ve8iJnDtKn0LjsQD+YWCjujBZisXT9HwUOztaoTuTMfzbfk4zXkhbh2GRV8Uu/X3tAEaW0O231Ht5e62W1GqIp5QSJOmS0E9WSrOWzbNBYhJhvyTStBFKZHhVJJPpCBfiopMs73hbF16ofk0iiAXrv9U20Emz503INHlHVJvWM2PExzHgBSgEye9/uGHYfKnQ3m0p7uVu4kAP4r2AtrKZ3DrNIyTYuUOGtB3QNv0zpL+7jYypDjxoHIrUXB7ajs1jW8V34pyhzMYq7EFY80SSuKKD+jWXwTavkdSUeopaCgB1CdakwWV2uWLWbEY2WDJkM9FupOtTX+c9iKr9L1IkGPUPXijKTRabPF7C6D1+l1LiSj0vuxIbl3jNCB4cf/xDXkMibm5fxZA6Gi8PkbI4SmUrSmBsBBezItt+e33viggefJ8PiORop0CIBpoBEYO3AOgmfkgyPnIOxN0fNDthQ4kTidZKSj0CCMMYpoC01kxAFM1gGbAYIgq23o7PRwBdgOACvcr4b5u32gArrq7FsXJgZQ4eef1QL67AZtLxRSRx1gKQEjwYpYtRfjM4WttPZteHNFhbI1iO+haFT635aXHCP+yIhtWmYAmzAeVvFERn4h/lubNUlyLvCdXnXR9SvhUgT9buSMLCp/9IHz2Q0tfC0ZLUA/0uM4UqFItUcOTpdXwVLFue5D7uMfEx9GLJXG90dhb1/PGnlg5vLFqknT7sLE+aKwPGhM1Hj+Utwc4UqXe34pN9UFTs08ZTjEzks30sXIVXp3xqvHqfICvicpbEO6+Ab8337r5FSDs7b7RbVu30XLoT9MHyvu+zzXGOLZ6GM9EDmSsy6OgzhQ72XMHYl34TM8diGThsWwTqcG2sFgnLu6qy4CPeXHX/6qcOZGB5Qo6Cjfh5Fl/3RHpsCFh16l6z2VI1W+/jlN1IMY1p9KEsg3XpQtlKJFFblktohwmS7G5i9X/eBNtRHJRyy3NQvgnLbs5fkwr6MBsgYC2btVL9rFiSyAQgIZjYvS764CZg74xas0Q3nEUX4W4RoS7ZcOFJq57tvnIHvA6dN4EnccdiqD6ns1QP39Mp+S4HoghuFXfK4ZOQpEKoWHet+NvUN+sfMl41haGxe7in5hixBdQ1zsD0YEWsaGgHhDSK3jmeysQOGkYUYGup+IbTiFImRzxvrGR/Ol1RRWpwMZ3OFKCbp9UVEMpsfC9ZP5LUQIk9gMrOoJnfsdjOSm99kmpgvvoKLyklYm4p3of+fSSelptyER2tNEUdADN8TxA5pTqIzBFBb2eB7Zzf0rrrzvNnayPldq9XQ3juFOP5yzZ5I90imXhb7zHwtkFx+PPZRh+KKThlPwM1+NK9bxrdQ1nbJ0TluOd000oxCfMSnV/rPyI+tkq0mFRpDwSztlN9OhGvCN3yGTdQj7V6J0OVZLLmPrFtbzWvSuStaKr5AyqtQ9r7YuVD6p3UK19JKjqtcbKBxJVVBNU8/C13DmsFaphfd5jUNHEYJ1ZvavCJCwJ1I0DSP3+RyaBW0ChpPrdcU3zHlPCA/KTsJar1Ht+bKKC8K4pR90JBC3+HIZwqB5QH4UfHHTyfHYboQGJvBK81K1bEhZtskDheA25Rw5696JL20DYDGRDnZCq3Lpthl7tgzcNaZ7ldhhgwwoYGp8FwACP0yJfk2oB8CC9kcb7Rla+Y3pa5YcFXnkpVK5BpQCyUnv97zkeyHPZbb/9we5Dz1DvH1H74vTaN+u1x9dC1wGNWluEFIoo1RJMxLkr+HyeqtHnc0xdBsznLy+Hagbw5o0Y6BJdtQD8U0qTlJxKKXExNjoIOu6nBbzFxjhqVaYQ4Ku6v8DohdSUrdZB84lJ0J66Yi1SeRsW7Vf/ahQEpDmCSDML3iJKXgnfZLlOKl02zpHLpYKDWD+gLkyDOgUqgBkJF6ZhfflyPp6pxnjEuqsTAcShQXXweo5Dg9YoOvEkNnIsCRdxcIMISYKWxxG+JK1GhAzWeKBar/HJugKA0NzLCD3/lJZzn57z79VJWE6GnOddlkLkQXW90QljsV2DwTZ9fRRk5Fmkh95j8uUgfBQuFtPEjv9sRa/kwUCVbtfYvwArjbxiR0TAY4+RjXZTeA4rtaWhooGJDkL3TFyBZwLCELqoP7o8fQV1AxeIP6fjy3NrEF/6RuILrf9qvnD3LjPWf7DOBYPsviR9tc4/pq/WcDYNMmGFZqvUTy7jTTblYCbzSU1LzCYkSmK3msDbg0Bg6lM/GcA6GnPRVdbIRHav0QJHm7FkXLYhPpgAI1DpXTvNJMRgFQz8EjFpUO37ZRom9ZjQuB5fiAG2PWZgacSLazfdDOKI9a6OLtxftKQbN0zVXKL5cKku0eSgceMqFbpNx3pZo9uhZBtDvFA3a+zhJg1uz0CP+aqgijFL0N+1ycqsae6eF/ENGv0SDu5wgHiejSdYUIQuOMje4GZ7LVCGxFRqbEQD6VZiDBW5Hofswv01gdmUcgngRuaTPeQw4OT554F8hderqRbc+xgwycCXBtsW2xM/8tQ4Gy7G7TpQpEcF2bg6UzAYDPA1ENQanFq+1uCiqjDOq6daAn0dqU3Su68ml3v39Q4bACxR3NtxKuW03XAprHvc3i+XzJ3Q3TPpBpLn8GYCrNlBHKJxWsQnSSCTO+vfZhW5w5soHyi8B+U52cDmYsOkIKXcNELAQLXCajQQQQVyHhlBBilY/c+QSg54TzWuSkvcNqQnBhNXFS6xyx7a88BeV9sb8jzVdtBx/S7o7xkEHTYuyPvrpEKTDFse9rd88LT+JY3P17iB6W/n2wS4N1tw3HNFw2TQclG8l8fBewcTH2ejjRNufu8V9f9abmAEGZvS7jRo2Y3tCCF2S648WneDAmBILRvtQjgLHYoT00BqmOsMezzznXRHxOt07kEMj9fWO1hWUD9lg6YPs1bqTJm2sLAy35n4Ast0+zThB8vt1R3IIP31oHHOIcDf/T2y0WEKX4U+X+EQl0BN4R9HNjoFPFxqw83dEjeI/KRa9tOIAaz9uLQtKkh4GlqCqPRZ2nyHVbmRLgeSsHORGxxCHC8L0kodrNThLXE2BlF7KVNKHUkpz9qKB+ZxNQARgC5ajKVA3bNuk4hhglpgbcVAOOo3p2hJWKNZaJBNIE4EXTGpOCa1RzyCUt4vu9mtKBG3z76QLbIxcTOztfaCNFaJvdbrThSyIK4huu8Nb30TFrDf3EWxi7R1TjzYCxLBdDQNYqFROG+dgNS6+zX0qgGvV7zBKcRb4MFQQGEVsZNA0zOUahXYI7C7dWekrNqfYbSFvvhLJLtIIdWZZ0rKaUC4yhZzRjQllBTSioFybb8EhbRBFNIGY+WqeqQGwTuIS1CFFaAXHr2YU/h4VYrC/wJKf+JOUfg+9ZdfcArfZ7CxqVyOqlK1qZzIW7c5TCmWBgP4Hq72WtNwrjY4N42rHaAdrRThf5OIKL55Cbk0imL9fOOFcAgZ1wuvotFzOB108DJP870lzvsuT/YR402xrY9zxoeKT3iKp7o/fBZUvx79KTPxnBACOaB+AeCDbgOb2XUhspkB9Y4bUGrrR/G51M43XrgnUKrTPxVT3OoIcSsVudURrOblKVhNn/ot3s0Ncs+sG5BrqeqVN6RxLWznYkhI/BeR2KoDX4YOAWs/apid/GjbiHQ61Z5lmva+bwAtG5Ch/tNItxOk6CcwtXqAwsT+ysKj3iZy4MV2fHE9rP/ern9T8fbvrXjzD1X881TFUDpeAz/52y7dz5y82i0Hccf2aPKeQwCHAAquKaumWr90iSxf2Qezgc8Oy3bgZ5jtYKnISsVoR/qbl/ANXtukV3HIx89E0PWJwNLVW2CCDvmclZWxUhGSAuimeQeluTFN4mmS2kRp9vfn25e/77cfqrEf+PJQjROqdfNqyffCEjniOrQMCPhRqDJW6oZnW6zCDeXgyQJtY21qmFdv5H0d8mLGYblCKt4Au5zqp6tHHGrpYvTOlGriVy0mmlDJpTA0CSbFk5+hs0STFGA9ZFnyBI2jCjZji5mi+l4vCVFNgSl1BdE057OxKlvnvzJAoXQoznERl6ABc2+S6j9aivtdqWN6IimyJUAgDqi0ScuHEKtwHlAVv4Sj6PZbTAdUHAj8dbq1sEN9fwi1aGesYiVif+9PTbQzOzh8ZxYtf7R9ZRN6svLdxYKcq5tRz+Rol8pOhrrPcU9hwwK0n+LhEnkMq5DSPV3xPuDRAbVqgUhx1JZA6zXxJ9Ghla5kK+jAqs/DfeB7u6F76Dtuo7+g6OORlSxq5UPjZHYl+Vp7/HY8j35TsOBgSYjvZS+D0qBHsQGgD9W2MF5bg2YP2o6d8xRZmItbmuyCPApyhcX2rkTG5R1sYoB7Jb9B5MiG3s74ejRWgXe1abNF3NgG0arCXv+b5UtrUHQ4OHNVF5u5uottwl2erpabLXgDC99bVcosyBKN3bmFODsHvgweqn4Mx1s3vqBjSazp6WOP6g7oyGrpKe+gfxV7HXgO5FT/hoaI1w9VP61+B0+Hql9k/tUwt4rvFfXRxZiwh1VLB75suWWFcKj6TVgA1e/KE9mWNrJ0Hi6AJfwJsA3FdwT3bbJQYA3qZ67dhDgFrEFqaSYLsx+pfYVF/WA9Uns75o2VP1ZJYYsQdFvLTHh5kY4oaM9SJTeawqKB1Nmr1BYF3seCuyKRWkSfFe6008sq8MGUj4w/kG4xw+2L5MZFipU+oB+dbpye1mEn7/Cjj6Hzp3z2iOS7ILmnWKTLnHtw2ToMZ2jcvqC12R3g28sPzjf2RbUGYEhqoZZUHua5bYrJ2NYeBRXAWxMaovkhhtOvF3igIXnaRdRPuyx/gnuvc/fqCOjyPUKbG0+OWTB1XEFHoM4U4P8Aenn0WWBBy6cJ8/FNZEkHo74Kbc1nJnemUqvQ1vg5bkl9XYGrsCcLS9cAhlqIqoNAY4mscOCJNSAi0Dq6F5dJyO/KcIn0CI9Tr+zVxkaZAzdcMDF17syBFaJ3le4eFbD0CDupGDpJwXhgYkUTlOat4wyvrBh2JZK+laDUgJxpR/8GIpp0pklpGoRpuXQ+XbVlI4JpqUg5NSQvMLwaiYWtGe/CUYo2FXv9tsZ+pFPNU/B81tKX0cNNAhFDeq5S31q1cIt0FsHovTSPVXR1lLr00+5XRI+zTtmhrZVQCh5XRc6mC6azrDoTrBlUBbtLRdNy7ivHnU9RXWmS8KQz4k6FmLaBgYqdRZmMd5QkpkQPyufQziNHMj3XdGaGqvcmq47cYBFSh7GSnr/kuIg3wLAD4aXsCm2dhL7R+lky/fadEnwfnsEq7NDGBcgiJDpxkOa5i/qd+nAfidPh5yn/GLwjoUTMpLNRwjCdrWrYSqRluOM7HtzD78QbClyK3634cxV/Xk/WEb7AcZVVBhex1W6c1ircSsdbr5qdCjAimNqF5TC1MXFjTIyi+31AvXieLr9OWHXHjbOEUGyxWCcFlUL1OgEo9UGlxiWfDzXR3sXEcsILJ+FF31yDkbrDOT3XuG2EGFNZhdO4vOryn5J/F55r7gWN1hSrcixYxDfcIHuTSGco4Qlow9IlgPHBdmCRx7syADdld2jVA9CdWPOgdkWdVKUW3DOkHe8CehVSfzOXk7vEGcBr/vV/NJ5epTbP5ViePP/hwsWDcJFH15nV36FiX4sXzLk5H6yYi3zQDWVer4nfOsjPdWwZTNtLyJs7ci8h3e4xah4Sr3z1sznGLW/y+ThjWXjFEO2jN+ANQ/oFJ3mkSqOpMKoZtzzSlmM2ytq5yPbcGDMQJQo8JLUIr4y0NV9CNGb7sItddEK346Yhjc13K+I9Jd4aW+M7BvpzpMynWqyoGa+wCEohXt2SuIgvgPGoazbwZRDSl0HSjQMv4dMPY+URs3g8/ajLWXPS70WITBHQB0GeChgmsq2oySh+kd1mN9EWsE4WQ+rHs0XKuCT8z+WRWguRRDExnrXhyWkv0GTZylqwNKDZ55d3QOWPmxInuUBnB7g70J+9YL/3a/SGUCZ2C0PKokFlglzjmRj2sy1Ui08C7bncrt+gv8UGX22m2Bbsiscm21HdNdw8RL4ax7Ed2CbWG97hWTTYZGWj08xOFyRXoz111woelLRYWxVUrWpEeaNnElpvVpObgmjuabdoa8WWk0PaWktb+QC5wl8A37t7mUTe72wcXhMKIJqXLXr36h4N/xe6HSq++EcAgENLjX0PfFPluX/SnCYHGnqCBAgQoUoFFFCkqC2p2gJJy7SQEk1krK3btKsd25jkAM6mlKXRnh6ibmO7eu/m9W66Od1+1/25yNSxQrWlwoCi07JSxY1tbwxikVpSKM3veZ73nCRt0Xv5fErOec/7/8/zPs/7Ps/3QdZM+ZIFVSzUVRbUAc31spfKCcZwPXwQNd3OTqfL/OCTNWjQ8/1ygn0UlNktqPdLwgn2UWQwEFwJTHdrmRdF7Ba3SIgu6BPiaRBU13efRAMMP/ue9uIPsNe+O8KddwSv4P0RGZTblrbVkH4nDMOghuBkJ+UGKANV4VwwBKiYVgjzpTZcWIL7hgndDJ1HpFfCCihySZEouTi8rUQWo54s9GhkUmSkS60l3kCgxZ0gMRPWCDOmKocMB/vk7lRdkerN0Kso34gjbLrMCBcGp+GyI+tJYlgFtJYdbpjC2+Q6L0UQu6ooNBw=
*/