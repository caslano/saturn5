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