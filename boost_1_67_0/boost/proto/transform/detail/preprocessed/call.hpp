    ///////////////////////////////////////////////////////////////////////////////
    /// \file call.hpp
    /// Contains definition of the call<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    
    template<typename Fun , typename A0>
    struct call<Fun(A0...)> : transform<call<Fun(A0...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A0
                  , detail::expand_pattern_rest_0<
                        Fun
                        
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1>
    struct call<Fun(A0 , A1...)> : transform<call<Fun(A0 , A1...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A1
                  , detail::expand_pattern_rest_1<
                        Fun
                        , A0
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2>
    struct call<Fun(A0 , A1 , A2...)> : transform<call<Fun(A0 , A1 , A2...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A2
                  , detail::expand_pattern_rest_2<
                        Fun
                        , A0 , A1
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3>
    struct call<Fun(A0 , A1 , A2 , A3)> : transform<call<Fun(A0 , A1 , A2 , A3)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)));
            }
        };
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3>
    struct call<Fun(A0 , A1 , A2 , A3...)> : transform<call<Fun(A0 , A1 , A2 , A3...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A3
                  , detail::expand_pattern_rest_3<
                        Fun
                        , A0 , A1 , A2
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct call<Fun(A0 , A1 , A2 , A3 , A4)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3; typedef typename when<_, A4>::template impl<Expr, State, Data> a4; typedef typename a4::result_type b4;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3 , b4)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)) , detail::as_lvalue(a4()(e, s, d)));
            }
        };
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct call<Fun(A0 , A1 , A2 , A3 , A4...)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A4
                  , detail::expand_pattern_rest_4<
                        Fun
                        , A0 , A1 , A2 , A3
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3; typedef typename when<_, A4>::template impl<Expr, State, Data> a4; typedef typename a4::result_type b4; typedef typename when<_, A5>::template impl<Expr, State, Data> a5; typedef typename a5::result_type b5;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3 , b4 , b5)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)) , detail::as_lvalue(a4()(e, s, d)) , detail::as_lvalue(a5()(e, s, d)));
            }
        };
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5...)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A5
                  , detail::expand_pattern_rest_5<
                        Fun
                        , A0 , A1 , A2 , A3 , A4
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3; typedef typename when<_, A4>::template impl<Expr, State, Data> a4; typedef typename a4::result_type b4; typedef typename when<_, A5>::template impl<Expr, State, Data> a5; typedef typename a5::result_type b5; typedef typename when<_, A6>::template impl<Expr, State, Data> a6; typedef typename a6::result_type b6;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3 , b4 , b5 , b6)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)) , detail::as_lvalue(a4()(e, s, d)) , detail::as_lvalue(a5()(e, s, d)) , detail::as_lvalue(a6()(e, s, d)));
            }
        };
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6...)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A6
                  , detail::expand_pattern_rest_6<
                        Fun
                        , A0 , A1 , A2 , A3 , A4 , A5
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3; typedef typename when<_, A4>::template impl<Expr, State, Data> a4; typedef typename a4::result_type b4; typedef typename when<_, A5>::template impl<Expr, State, Data> a5; typedef typename a5::result_type b5; typedef typename when<_, A6>::template impl<Expr, State, Data> a6; typedef typename a6::result_type b6; typedef typename when<_, A7>::template impl<Expr, State, Data> a7; typedef typename a7::result_type b7;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3 , b4 , b5 , b6 , b7)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)) , detail::as_lvalue(a4()(e, s, d)) , detail::as_lvalue(a5()(e, s, d)) , detail::as_lvalue(a6()(e, s, d)) , detail::as_lvalue(a7()(e, s, d)));
            }
        };
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7...)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A7
                  , detail::expand_pattern_rest_7<
                        Fun
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3; typedef typename when<_, A4>::template impl<Expr, State, Data> a4; typedef typename a4::result_type b4; typedef typename when<_, A5>::template impl<Expr, State, Data> a5; typedef typename a5::result_type b5; typedef typename when<_, A6>::template impl<Expr, State, Data> a6; typedef typename a6::result_type b6; typedef typename when<_, A7>::template impl<Expr, State, Data> a7; typedef typename a7::result_type b7; typedef typename when<_, A8>::template impl<Expr, State, Data> a8; typedef typename a8::result_type b8;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3 , b4 , b5 , b6 , b7 , b8)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)) , detail::as_lvalue(a4()(e, s, d)) , detail::as_lvalue(a5()(e, s, d)) , detail::as_lvalue(a6()(e, s, d)) , detail::as_lvalue(a7()(e, s, d)) , detail::as_lvalue(a8()(e, s, d)));
            }
        };
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8...)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A8
                  , detail::expand_pattern_rest_8<
                        Fun
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            typedef typename when<_, A0>::template impl<Expr, State, Data> a0; typedef typename a0::result_type b0; typedef typename when<_, A1>::template impl<Expr, State, Data> a1; typedef typename a1::result_type b1; typedef typename when<_, A2>::template impl<Expr, State, Data> a2; typedef typename a2::result_type b2; typedef typename when<_, A3>::template impl<Expr, State, Data> a3; typedef typename a3::result_type b3; typedef typename when<_, A4>::template impl<Expr, State, Data> a4; typedef typename a4::result_type b4; typedef typename when<_, A5>::template impl<Expr, State, Data> a5; typedef typename a5::result_type b5; typedef typename when<_, A6>::template impl<Expr, State, Data> a6; typedef typename a6::result_type b6; typedef typename when<_, A7>::template impl<Expr, State, Data> a7; typedef typename a7::result_type b7; typedef typename when<_, A8>::template impl<Expr, State, Data> a8; typedef typename a8::result_type b8; typedef typename when<_, A9>::template impl<Expr, State, Data> a9; typedef typename a9::result_type b9;
            typedef detail::poly_function_traits<Fun, Fun(b0 , b1 , b2 , b3 , b4 , b5 , b6 , b7 , b8 , b9)> function_traits;
            typedef typename function_traits::result_type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                typedef typename function_traits::function_type function_type;
                return function_type()(detail::as_lvalue(a0()(e, s, d)) , detail::as_lvalue(a1()(e, s, d)) , detail::as_lvalue(a2()(e, s, d)) , detail::as_lvalue(a3()(e, s, d)) , detail::as_lvalue(a4()(e, s, d)) , detail::as_lvalue(a5()(e, s, d)) , detail::as_lvalue(a6()(e, s, d)) , detail::as_lvalue(a7()(e, s, d)) , detail::as_lvalue(a8()(e, s, d)) , detail::as_lvalue(a9()(e, s, d)));
            }
        };
    };
    
    
    
    template<typename Fun , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9...)> : transform<call<Fun(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : call<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value 
                  , A9
                  , detail::expand_pattern_rest_9<
                        Fun
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };

/* call.hpp
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
*/