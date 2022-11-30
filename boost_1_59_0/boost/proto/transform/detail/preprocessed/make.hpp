    ///////////////////////////////////////////////////////////////////////////////
    /// \file make.hpp
    /// Contains definition of the make<> transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    namespace detail
    {
        template<typename R >
        struct is_applyable<R()>
          : mpl::true_
        {};
        template<typename R >
        struct is_applyable<R(*)()>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 0>, true>
        {
            typedef proto::expr<T, A, 0> result_type;
            template<typename A0>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0) const
            {
                return result_type::make(a0);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 0>, true>
        {
            typedef proto::basic_expr<T, A, 0> result_type;
            template<typename A0>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0) const
            {
                return result_type::make(a0);
            }
        };
        template<typename Type >
        BOOST_FORCEINLINE
        Type construct()
        {
            return construct_<Type>()();
        }
    } 
    
    
    
    
    template<typename Object >
    struct make<Object()>
      : transform<make<Object()> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>();
            }
        };
    };
    namespace detail
    {
        template<
            template<typename> class R
            , typename A0
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename> class R
            , typename A0
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0>
        struct is_applyable<R(A0)>
          : mpl::true_
        {};
        template<typename R , typename A0>
        struct is_applyable<R(*)(A0)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 1>, true>
        {
            typedef proto::expr<T, A, 1> result_type;
            template<typename A0>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0) const
            {
                return result_type::make(a0);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 1>, true>
        {
            typedef proto::basic_expr<T, A, 1> result_type;
            template<typename A0>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0) const
            {
                return result_type::make(a0);
            }
        };
        template<typename Type , typename A0>
        BOOST_FORCEINLINE
        Type construct(A0 &a0)
        {
            return construct_<Type>()(a0);
        }
    } 
    
    
    
    
    template<typename Object , typename A0>
    struct make<Object(A0)>
      : transform<make<Object(A0)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0>
    struct make<Object(A0...)>
      : transform<make<Object(A0...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A0
                  , detail::expand_pattern_rest_0<
                        Object
                        
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename> class R
            , typename A0 , typename A1
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(2)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename> class R
            , typename A0 , typename A1
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1>
        struct is_applyable<R(A0 , A1)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1>
        struct is_applyable<R(*)(A0 , A1)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 2>, true>
        {
            typedef proto::expr<T, A, 2> result_type;
            template<typename A0 , typename A1>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1) const
            {
                return result_type::make(a0 , a1);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 2>, true>
        {
            typedef proto::basic_expr<T, A, 2> result_type;
            template<typename A0 , typename A1>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1) const
            {
                return result_type::make(a0 , a1);
            }
        };
        template<typename Type , typename A0 , typename A1>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1)
        {
            return construct_<Type>()(a0 , a1);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1>
    struct make<Object(A0 , A1)>
      : transform<make<Object(A0 , A1)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1>
    struct make<Object(A0 , A1...)>
      : transform<make<Object(A0 , A1...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A1
                  , detail::expand_pattern_rest_1<
                        Object
                        , A0
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1 , A2>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(3)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || make_if_<A2, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1 , A2> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1 , typename A2>
        struct is_applyable<R(A0 , A1 , A2)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1 , typename A2>
        struct is_applyable<R(*)(A0 , A1 , A2)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 3>, true>
        {
            typedef proto::expr<T, A, 3> result_type;
            template<typename A0 , typename A1 , typename A2>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2) const
            {
                return result_type::make(a0 , a1 , a2);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 3>, true>
        {
            typedef proto::basic_expr<T, A, 3> result_type;
            template<typename A0 , typename A1 , typename A2>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2) const
            {
                return result_type::make(a0 , a1 , a2);
            }
        };
        template<typename Type , typename A0 , typename A1 , typename A2>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1 , A2 &a2)
        {
            return construct_<Type>()(a0 , a1 , a2);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2>
    struct make<Object(A0 , A1 , A2)>
      : transform<make<Object(A0 , A1 , A2)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2>
    struct make<Object(A0 , A1 , A2...)>
      : transform<make<Object(A0 , A1 , A2...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A2
                  , detail::expand_pattern_rest_2<
                        Object
                        , A0 , A1
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1 , A2 , A3>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(4)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || make_if_<A2, Expr, State, Data> ::applied || make_if_<A3, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1 , A2 , A3> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3>
        struct is_applyable<R(A0 , A1 , A2 , A3)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3>
        struct is_applyable<R(*)(A0 , A1 , A2 , A3)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 4>, true>
        {
            typedef proto::expr<T, A, 4> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3) const
            {
                return result_type::make(a0 , a1 , a2 , a3);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 4>, true>
        {
            typedef proto::basic_expr<T, A, 4> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3) const
            {
                return result_type::make(a0 , a1 , a2 , a3);
            }
        };
        template<typename Type , typename A0 , typename A1 , typename A2 , typename A3>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3)
        {
            return construct_<Type>()(a0 , a1 , a2 , a3);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3>
    struct make<Object(A0 , A1 , A2 , A3)>
      : transform<make<Object(A0 , A1 , A2 , A3)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3>
    struct make<Object(A0 , A1 , A2 , A3...)>
      : transform<make<Object(A0 , A1 , A2 , A3...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A3
                  , detail::expand_pattern_rest_3<
                        Object
                        , A0 , A1 , A2
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1 , A2 , A3 , A4>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(5)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || make_if_<A2, Expr, State, Data> ::applied || make_if_<A3, Expr, State, Data> ::applied || make_if_<A4, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1 , A2 , A3 , A4> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct is_applyable<R(A0 , A1 , A2 , A3 , A4)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        struct is_applyable<R(*)(A0 , A1 , A2 , A3 , A4)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 5>, true>
        {
            typedef proto::expr<T, A, 5> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 5>, true>
        {
            typedef proto::basic_expr<T, A, 5> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4);
            }
        };
        template<typename Type , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4)
        {
            return construct_<Type>()(a0 , a1 , a2 , a3 , a4);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct make<Object(A0 , A1 , A2 , A3 , A4)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct make<Object(A0 , A1 , A2 , A3 , A4...)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A4
                  , detail::expand_pattern_rest_4<
                        Object
                        , A0 , A1 , A2 , A3
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1 , A2 , A3 , A4 , A5>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(6)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || make_if_<A2, Expr, State, Data> ::applied || make_if_<A3, Expr, State, Data> ::applied || make_if_<A4, Expr, State, Data> ::applied || make_if_<A5, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1 , A2 , A3 , A4 , A5> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct is_applyable<R(A0 , A1 , A2 , A3 , A4 , A5)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        struct is_applyable<R(*)(A0 , A1 , A2 , A3 , A4 , A5)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 6>, true>
        {
            typedef proto::expr<T, A, 6> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 6>, true>
        {
            typedef proto::basic_expr<T, A, 6> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5);
            }
        };
        template<typename Type , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5)
        {
            return construct_<Type>()(a0 , a1 , a2 , a3 , a4 , a5);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5...)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A5
                  , detail::expand_pattern_rest_5<
                        Object
                        , A0 , A1 , A2 , A3 , A4
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1 , A2 , A3 , A4 , A5 , A6>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(7)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type , typename make_if_<A6, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || make_if_<A2, Expr, State, Data> ::applied || make_if_<A3, Expr, State, Data> ::applied || make_if_<A4, Expr, State, Data> ::applied || make_if_<A5, Expr, State, Data> ::applied || make_if_<A6, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1 , A2 , A3 , A4 , A5 , A6> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type , typename make_if_<A6, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct is_applyable<R(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        struct is_applyable<R(*)(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 7>, true>
        {
            typedef proto::expr<T, A, 7> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 7>, true>
        {
            typedef proto::basic_expr<T, A, 7> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5 , a6);
            }
        };
        template<typename Type , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6)
        {
            return construct_<Type>()(a0 , a1 , a2 , a3 , a4 , a5 , a6);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6...)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A6
                  , detail::expand_pattern_rest_6<
                        Object
                        , A0 , A1 , A2 , A3 , A4 , A5
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename , typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(8)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type , typename make_if_<A6, Expr, State, Data> ::type , typename make_if_<A7, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || make_if_<A2, Expr, State, Data> ::applied || make_if_<A3, Expr, State, Data> ::applied || make_if_<A4, Expr, State, Data> ::applied || make_if_<A5, Expr, State, Data> ::applied || make_if_<A6, Expr, State, Data> ::applied || make_if_<A7, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename , typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type , typename make_if_<A6, Expr, State, Data> ::type , typename make_if_<A7, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct is_applyable<R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        struct is_applyable<R(*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 8>, true>
        {
            typedef proto::expr<T, A, 8> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 8>, true>
        {
            typedef proto::basic_expr<T, A, 8> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
            }
        };
        template<typename Type , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7)
        {
            return construct_<Type>()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7...)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A7
                  , detail::expand_pattern_rest_7<
                        Object
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename , typename , typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(9)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type , typename make_if_<A6, Expr, State, Data> ::type , typename make_if_<A7, Expr, State, Data> ::type , typename make_if_<A8, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || make_if_<A2, Expr, State, Data> ::applied || make_if_<A3, Expr, State, Data> ::applied || make_if_<A4, Expr, State, Data> ::applied || make_if_<A5, Expr, State, Data> ::applied || make_if_<A6, Expr, State, Data> ::applied || make_if_<A7, Expr, State, Data> ::applied || make_if_<A8, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename , typename , typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type , typename make_if_<A6, Expr, State, Data> ::type , typename make_if_<A7, Expr, State, Data> ::type , typename make_if_<A8, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct is_applyable<R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        struct is_applyable<R(*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 9>, true>
        {
            typedef proto::expr<T, A, 9> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 9>, true>
        {
            typedef proto::basic_expr<T, A, 9> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
            }
        };
        template<typename Type , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8)
        {
            return construct_<Type>()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A8>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8...)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A8
                  , detail::expand_pattern_rest_8<
                        Object
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };
    namespace detail
    {
        template<
            template<typename , typename , typename , typename , typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
          , typename Expr, typename State, typename Data
        >
        struct make_<
            R<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9>
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(10)
        >
          : nested_type_if<
                R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type , typename make_if_<A6, Expr, State, Data> ::type , typename make_if_<A7, Expr, State, Data> ::type , typename make_if_<A8, Expr, State, Data> ::type , typename make_if_<A9, Expr, State, Data> ::type>
              , (make_if_<A0, Expr, State, Data> ::applied || make_if_<A1, Expr, State, Data> ::applied || make_if_<A2, Expr, State, Data> ::applied || make_if_<A3, Expr, State, Data> ::applied || make_if_<A4, Expr, State, Data> ::applied || make_if_<A5, Expr, State, Data> ::applied || make_if_<A6, Expr, State, Data> ::applied || make_if_<A7, Expr, State, Data> ::applied || make_if_<A8, Expr, State, Data> ::applied || make_if_<A9, Expr, State, Data> ::applied || false)
            >
        {};
        template<
            template<typename , typename , typename , typename , typename , typename , typename , typename , typename , typename> class R
            , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9
          , typename Expr, typename State, typename Data
        >
        struct make_<
            noinvoke<R<A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9> >
          , Expr, State, Data
            BOOST_PROTO_TEMPLATE_ARITY_PARAM(1)
        >
        {
            typedef R<typename make_if_<A0, Expr, State, Data> ::type , typename make_if_<A1, Expr, State, Data> ::type , typename make_if_<A2, Expr, State, Data> ::type , typename make_if_<A3, Expr, State, Data> ::type , typename make_if_<A4, Expr, State, Data> ::type , typename make_if_<A5, Expr, State, Data> ::type , typename make_if_<A6, Expr, State, Data> ::type , typename make_if_<A7, Expr, State, Data> ::type , typename make_if_<A8, Expr, State, Data> ::type , typename make_if_<A9, Expr, State, Data> ::type> type;
            static bool const applied = true;
        };
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct is_applyable<R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
          : mpl::true_
        {};
        template<typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        struct is_applyable<R(*)(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
          : mpl::true_
        {};
        template<typename T, typename A>
        struct construct_<proto::expr<T, A, 10>, true>
        {
            typedef proto::expr<T, A, 10> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8 , A9 &a9) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
        };
        template<typename T, typename A>
        struct construct_<proto::basic_expr<T, A, 10>, true>
        {
            typedef proto::basic_expr<T, A, 10> result_type;
            template<typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
            BOOST_FORCEINLINE
            result_type operator ()(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8 , A9 &a9) const
            {
                return result_type::make(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
            }
        };
        template<typename Type , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
        BOOST_FORCEINLINE
        Type construct(A0 &a0 , A1 &a1 , A2 &a2 , A3 &a3 , A4 &a4 , A5 &a5 , A6 &a6 , A7 &a7 , A8 &a8 , A9 &a9)
        {
            return construct_<Type>()(a0 , a1 , a2 , a3 , a4 , a5 , a6 , a7 , a8 , a9);
        }
    } 
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl : transform_impl<Expr, State, Data>
        {
            
            typedef typename detail::make_if_<Object, Expr, State, Data>::type result_type;
            
            
            
            
            
            
            
            BOOST_FORCEINLINE
            result_type operator ()(
                typename impl::expr_param e
              , typename impl::state_param s
              , typename impl::data_param d
            ) const
            {
                proto::detail::ignore_unused(e);
                proto::detail::ignore_unused(s);
                proto::detail::ignore_unused(d);
                return detail::construct<result_type>(detail::as_lvalue( typename when<_, A0>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A1>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A2>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A3>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A4>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A5>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A6>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A7>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A8>::template impl<Expr, State, Data>()(e, s, d) ) , detail::as_lvalue( typename when<_, A9>::template impl<Expr, State, Data>()(e, s, d) ));
            }
        };
    };
    
    
    
    
    template<typename Object , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9...)>
      : transform<make<Object(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9...)> >
    {
        template<typename Expr, typename State, typename Data>
        struct impl
          : make<
                typename detail::expand_pattern<
                    proto::arity_of<Expr>::value
                  , A9
                  , detail::expand_pattern_rest_9<
                        Object
                        , A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8
                    >
                >::type
            >::template impl<Expr, State, Data>
        {};
    };

/* make.hpp
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
*/