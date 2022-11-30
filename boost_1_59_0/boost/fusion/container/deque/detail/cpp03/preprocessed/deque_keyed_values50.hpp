/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion { namespace detail
{
    template<typename Key, typename Value, typename Rest>
    struct keyed_element;
    struct nil_keyed_element;
    template<typename N, typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_ , typename T10 = void_ , typename T11 = void_ , typename T12 = void_ , typename T13 = void_ , typename T14 = void_ , typename T15 = void_ , typename T16 = void_ , typename T17 = void_ , typename T18 = void_ , typename T19 = void_ , typename T20 = void_ , typename T21 = void_ , typename T22 = void_ , typename T23 = void_ , typename T24 = void_ , typename T25 = void_ , typename T26 = void_ , typename T27 = void_ , typename T28 = void_ , typename T29 = void_ , typename T30 = void_ , typename T31 = void_ , typename T32 = void_ , typename T33 = void_ , typename T34 = void_ , typename T35 = void_ , typename T36 = void_ , typename T37 = void_ , typename T38 = void_ , typename T39 = void_ , typename T40 = void_ , typename T41 = void_ , typename T42 = void_ , typename T43 = void_ , typename T44 = void_ , typename T45 = void_ , typename T46 = void_ , typename T47 = void_ , typename T48 = void_ , typename T49 = void_>
    struct deque_keyed_values_impl;
    template<typename N>
    struct deque_keyed_values_impl<N, void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_ , void_>
    {
        typedef nil_keyed_element type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct()
        {
            return type();
        }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_()
        {
            return type();
        }
    };
    template<typename N, typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38 , typename T39 , typename T40 , typename T41 , typename T42 , typename T43 , typename T44 , typename T45 , typename T46 , typename T47 , typename T48 , typename T49>
    struct deque_keyed_values_impl
    {
        typedef mpl::int_<mpl::plus<N, mpl::int_<1> >::value> next_index;
        typedef typename deque_keyed_values_impl<
            next_index,
            T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44 , T45 , T46 , T47 , T48 , T49>::type tail;
        typedef keyed_element<N, T0, tail> type;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        >::construct());
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        >::forward_());
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1
                        >::construct(t1));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1
                        >::forward_(std::forward<T_1>( t1)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2
                        >::construct(t1 , t2));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3
                        >::construct(t1 , t2 , t3));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4
                        >::construct(t1 , t2 , t3 , t4));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5
                        >::construct(t1 , t2 , t3 , t4 , t5));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41 , typename detail::call_param<T42 >::type t42)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41 , t42));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41 , typename T_42>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41 , T_42 && t42)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41 , T_42
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41) , std::forward<T_42>( t42)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41 , typename detail::call_param<T42 >::type t42 , typename detail::call_param<T43 >::type t43)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41 , t42 , t43));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41 , typename T_42 , typename T_43>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41 , T_42 && t42 , T_43 && t43)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41 , T_42 , T_43
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41) , std::forward<T_42>( t42) , std::forward<T_43>( t43)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41 , typename detail::call_param<T42 >::type t42 , typename detail::call_param<T43 >::type t43 , typename detail::call_param<T44 >::type t44)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41 , t42 , t43 , t44));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41 , typename T_42 , typename T_43 , typename T_44>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41 , T_42 && t42 , T_43 && t43 , T_44 && t44)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41 , T_42 , T_43 , T_44
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41) , std::forward<T_42>( t42) , std::forward<T_43>( t43) , std::forward<T_44>( t44)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41 , typename detail::call_param<T42 >::type t42 , typename detail::call_param<T43 >::type t43 , typename detail::call_param<T44 >::type t44 , typename detail::call_param<T45 >::type t45)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44 , T45
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41 , t42 , t43 , t44 , t45));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41 , typename T_42 , typename T_43 , typename T_44 , typename T_45>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41 , T_42 && t42 , T_43 && t43 , T_44 && t44 , T_45 && t45)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41 , T_42 , T_43 , T_44 , T_45
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41) , std::forward<T_42>( t42) , std::forward<T_43>( t43) , std::forward<T_44>( t44) , std::forward<T_45>( t45)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41 , typename detail::call_param<T42 >::type t42 , typename detail::call_param<T43 >::type t43 , typename detail::call_param<T44 >::type t44 , typename detail::call_param<T45 >::type t45 , typename detail::call_param<T46 >::type t46)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44 , T45 , T46
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41 , t42 , t43 , t44 , t45 , t46));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41 , typename T_42 , typename T_43 , typename T_44 , typename T_45 , typename T_46>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41 , T_42 && t42 , T_43 && t43 , T_44 && t44 , T_45 && t45 , T_46 && t46)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41 , T_42 , T_43 , T_44 , T_45 , T_46
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41) , std::forward<T_42>( t42) , std::forward<T_43>( t43) , std::forward<T_44>( t44) , std::forward<T_45>( t45) , std::forward<T_46>( t46)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41 , typename detail::call_param<T42 >::type t42 , typename detail::call_param<T43 >::type t43 , typename detail::call_param<T44 >::type t44 , typename detail::call_param<T45 >::type t45 , typename detail::call_param<T46 >::type t46 , typename detail::call_param<T47 >::type t47)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44 , T45 , T46 , T47
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41 , t42 , t43 , t44 , t45 , t46 , t47));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41 , typename T_42 , typename T_43 , typename T_44 , typename T_45 , typename T_46 , typename T_47>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41 , T_42 && t42 , T_43 && t43 , T_44 && t44 , T_45 && t45 , T_46 && t46 , T_47 && t47)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41 , T_42 , T_43 , T_44 , T_45 , T_46 , T_47
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41) , std::forward<T_42>( t42) , std::forward<T_43>( t43) , std::forward<T_44>( t44) , std::forward<T_45>( t45) , std::forward<T_46>( t46) , std::forward<T_47>( t47)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41 , typename detail::call_param<T42 >::type t42 , typename detail::call_param<T43 >::type t43 , typename detail::call_param<T44 >::type t44 , typename detail::call_param<T45 >::type t45 , typename detail::call_param<T46 >::type t46 , typename detail::call_param<T47 >::type t47 , typename detail::call_param<T48 >::type t48)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44 , T45 , T46 , T47 , T48
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41 , t42 , t43 , t44 , t45 , t46 , t47 , t48));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41 , typename T_42 , typename T_43 , typename T_44 , typename T_45 , typename T_46 , typename T_47 , typename T_48>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41 , T_42 && t42 , T_43 && t43 , T_44 && t44 , T_45 && t45 , T_46 && t46 , T_47 && t47 , T_48 && t48)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41 , T_42 , T_43 , T_44 , T_45 , T_46 , T_47 , T_48
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41) , std::forward<T_42>( t42) , std::forward<T_43>( t43) , std::forward<T_44>( t44) , std::forward<T_45>( t45) , std::forward<T_46>( t46) , std::forward<T_47>( t47) , std::forward<T_48>( t48)));
        }
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type construct(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39 , typename detail::call_param<T40 >::type t40 , typename detail::call_param<T41 >::type t41 , typename detail::call_param<T42 >::type t42 , typename detail::call_param<T43 >::type t43 , typename detail::call_param<T44 >::type t44 , typename detail::call_param<T45 >::type t45 , typename detail::call_param<T46 >::type t46 , typename detail::call_param<T47 >::type t47 , typename detail::call_param<T48 >::type t48 , typename detail::call_param<T49 >::type t49)
        {
            return type(t0,
                        deque_keyed_values_impl<
                        next_index
                        , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44 , T45 , T46 , T47 , T48 , T49
                        >::construct(t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39 , t40 , t41 , t42 , t43 , t44 , t45 , t46 , t47 , t48 , t49));
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39 , typename T_40 , typename T_41 , typename T_42 , typename T_43 , typename T_44 , typename T_45 , typename T_46 , typename T_47 , typename T_48 , typename T_49>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type forward_(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39 , T_40 && t40 , T_41 && t41 , T_42 && t42 , T_43 && t43 , T_44 && t44 , T_45 && t45 , T_46 && t46 , T_47 && t47 , T_48 && t48 , T_49 && t49)
        {
            return type(std::forward<T_0>( t0),
                        deque_keyed_values_impl<
                        next_index
                        , T_1 , T_2 , T_3 , T_4 , T_5 , T_6 , T_7 , T_8 , T_9 , T_10 , T_11 , T_12 , T_13 , T_14 , T_15 , T_16 , T_17 , T_18 , T_19 , T_20 , T_21 , T_22 , T_23 , T_24 , T_25 , T_26 , T_27 , T_28 , T_29 , T_30 , T_31 , T_32 , T_33 , T_34 , T_35 , T_36 , T_37 , T_38 , T_39 , T_40 , T_41 , T_42 , T_43 , T_44 , T_45 , T_46 , T_47 , T_48 , T_49
                        >::forward_(std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39) , std::forward<T_40>( t40) , std::forward<T_41>( t41) , std::forward<T_42>( t42) , std::forward<T_43>( t43) , std::forward<T_44>( t44) , std::forward<T_45>( t45) , std::forward<T_46>( t46) , std::forward<T_47>( t47) , std::forward<T_48>( t48) , std::forward<T_49>( t49)));
        }
# endif
    };
    template<typename T0 = void_ , typename T1 = void_ , typename T2 = void_ , typename T3 = void_ , typename T4 = void_ , typename T5 = void_ , typename T6 = void_ , typename T7 = void_ , typename T8 = void_ , typename T9 = void_ , typename T10 = void_ , typename T11 = void_ , typename T12 = void_ , typename T13 = void_ , typename T14 = void_ , typename T15 = void_ , typename T16 = void_ , typename T17 = void_ , typename T18 = void_ , typename T19 = void_ , typename T20 = void_ , typename T21 = void_ , typename T22 = void_ , typename T23 = void_ , typename T24 = void_ , typename T25 = void_ , typename T26 = void_ , typename T27 = void_ , typename T28 = void_ , typename T29 = void_ , typename T30 = void_ , typename T31 = void_ , typename T32 = void_ , typename T33 = void_ , typename T34 = void_ , typename T35 = void_ , typename T36 = void_ , typename T37 = void_ , typename T38 = void_ , typename T39 = void_ , typename T40 = void_ , typename T41 = void_ , typename T42 = void_ , typename T43 = void_ , typename T44 = void_ , typename T45 = void_ , typename T46 = void_ , typename T47 = void_ , typename T48 = void_ , typename T49 = void_>
    struct deque_keyed_values
        : deque_keyed_values_impl<mpl::int_<0>, T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39 , T40 , T41 , T42 , T43 , T44 , T45 , T46 , T47 , T48 , T49>
    {};
}}}

/* deque_keyed_values50.hpp
Ve7dA1WiZgShVtxpqBWbF8+z/b/k8repWGARm17p1NxwaCM3KLTZ+itsQsMy+TzyxEPD24DZvaAxHZuG5CwfvGCElod5ZHq9yNnE2DGj/pcmuISTK9SXxsPAEqZaZhXuIYCn0Rl7DDfpp68Jop3onoDxE4FfSQ8ISp7jbRQegJyufgut3JY11GuX8raXcvC9SWQLVP60DQi9gLexXGnx+ep/ZpQWEeMtIN3LrH4M0zfhugxTQDYPvki+Lr6I9qaBYMnRKFklfAvexH9a2noP6USAE16E+wQvINzGTz8i9eXNbCzrQ72HIciLVcMhF8A3ZTFR2EVf6JWnQnDW2YyDg1n34rXqWHdyupmFtZ/CXAED0QatG2ulHrJgl5Kj1A8+1cYmHerFn5qQOJ9KW27PvgTiJtDADE0BtukCdjrjXw60FgjULz9Oc0RHoRDQo3SJfCiRx04Pza+cJb8Zz5o0LHCctNn0KqEuToZ8Ya4fUYqavouwnu80C2rcGTaW/pwrSOTpiJQ6DmZBU2z1y8ybviYZ8gI7A6TI1eUkhqbg59Y1TP0ybjAZE8lqVwP2uVYMolMoLNeAUWEOpRvv68/lc93mRZEr+d+w36G/UFbSxma3x+lN0BkNhIybf54F5pjt4Mrvh0zWPRowXvlvMtF0Wlc5BA0vdbbxoXJ1B11Xh13ybcCVb/oVxuvbcNqGzoFfrh7xAn2Z50TsyF1Ui3I1e/X1IyzxNR7SZGpZDfmDxl6e/5zCT5THyJAybt0SWSiRMGmlKD8Oby8M5UNGiJd/OatKhT96Earcn3XXGrbuwl7BrSs0USVvs8+MB39m4+Hb+I3YMooCYQsHjGd/RhdZuS/ggCQnk/VpOUn0bpBGosaznGNix3i9BxEp1oj8zDQGPuN+At0baUnJ15I5fKk5RueZ/PxZR6qCRvW/f8bNZ80hYTX0olvoKT2zsK+G4AdG0VU1IMas+OV3pKQdtw06jsM3Af8vdQyofaL6EXDaM5X3h+NjbPgYw3BlIkt5kY3LfUSIsEfJ2C3KPtPwZUZg1Idc4PtMtVDnw8j2yXnmOmJbqGTJK8bkH9lsG17CSuOI7IaDDHQggtkrbMpB1knVXp6LwTo7FyNtNIDHfdRGX7C+94fW9/L2TH1RZ7OFOlr2MJ5ibuVbJtYxugPdyJ9JXZcJFKLKZfwFt5UBawoetEDdB4bWvSqr7kpnhJiBgPH3h0hTqZhLNJP92rN35emHeFdey+rKWw+ZXXnIZnYlTF1RT49r+WH9zleHVvyPbZmKv0TbXrbfmMrZf+V8XEtsYrNAcSaInXFCpRpXNtZn1fLwtiHdKzO7dy51pUzqKkqRE7fVxRn8ufxzqAHjJ9bXlbxCq8yIZSp6BYMROx4R+Pw7mAOdgmj+fwqD5DBRfxsoNBLNaUTq3GzO5XX4n7OOJrSBjxhs5f/5KR+tFvaace3prOmBnAd4TpgKNeGOBZLF2Job9sBms9BcKDTqtDWQUOJVq24qETIafkpzdxEPNUN1NZfB1qr6KX9ZZzphNB5VMKqjaIkGjD/AUVWnOUxngyH+dDAD+cDUlYIMqoyu5+Yu6AUFD/KBQa1w+6TZduUfrMbd8YHUccKuXJxWuN48CThy4CIvfBA3MTpmKdPo3MbyapsoKCP1CtSiO5O5rMaFXlhQq1O+DyQ60tXYwzEMoyJ1IRZ5qSKyOhe6f7aESHUaZycpEM+YzPmIIulyCjzgcyQCUk8FCNq5xpWDGcsxJUhAWHFUdZAe07N6H4l4baJx+bOpFA1BaYVIGGxuZuoAOuFNAlrEmaggxipRwaGdFz4AMtXKjI7xzkl47l31AJJHLiS441oFhhRxaxWu5HXwCi2IeuU2+yv11GCMXLQI90WReSk2vnsybXWqYE+zVa6e1a+yOgzVB7LdYjjZgVUMGd5fW0oipZxVuEr6gYhO7q/IcIr3Y9+NnwGBVL/j/hQmB7XAmuJiTkR202qslxI4ynSD2W+6fzKPk/8zCU9yrskygvebZ4kDyClytw5IUJaqA/Y1l7NFfBUI8hTs0GipJ+rUJqK1A97vjtJygeFyarUiPdE9QCFdoUDMeAmrbEG0m2uknoVrBtVPBM3Vo3xO2RCObgKL8hUhyLhkgRZjCou6gNnAgQyGYsb6+7ldRbZ/3sdFYd2lRfSiblYjAnfiX7hR1PM2YoBqeXQ6JFQR6itLW31lynRYz/x2D/b8gF2ZUNrmkt0sbDaujChd51JcDXU7D50yS0aBRX+DVJfporhkUd+H1wzKJbiWpsDE8JH8CMOkis0C3U7k/gRHkqKoFGNrF6TvMD6hbEHj7/chU48KHx9skd3G97ClATI4Skmdexxcp/NztBReh7ed3RTThQsL8zJLIEVL4KdQmXqTGzGDFibm0Qputmm3461ReQDeIzHPTXbZiXl20WY8/C9TV6LM5pXkTMazf+l9XG2XeRY0KuBZfUOdWacV56oIedIyYAnybVZIU6XG1JlOTrMnhv0+vKxANwzlCp7qoYaO/dhmy/ji4LOQ8acfU0NcCQf1V+Cyb8mxXMqgXwvZJMfbDm7iGYBql/u8sl3zDr2AWSiYrDGIjoWvsUThbiA9iMhZTL0FggqiI7BHIfkS474fI4PEKRBqdWCgjiMSnOE+TjaFGF812UhBWeRiRx9zFWAsCONGs9iWocXyjXf6M8Wu4LnLjBmUW7kRc6LZMgppsyjgWdSY9SWFF/chFzagptAGF+iElnepo87W+Ta9YI6D/uINDd7hIMnYLfqvo1ua25fTpQ/a0V8I8/LiqVT2HUrBZFwY6JeQmdNLaU5v+xEPIEHGMPT8Msq79EfIkSca6vgMoKL4IyTlLeug6YXMbh2R38bydWLUWPvfWbh812eUtH6a0VG8GbPp2dRE//bhTc+h53/ZTooMq+nlBNhSQF2owHvra0wbkMlAy3HEjLqnaOjS2ZJ5SJQmwmbMVF1FVau8yYXMyZ8G4GmGMjYmKmBHxDSvsWx79qIM0itUndHdENV5xXZarJYOvMjUNvdPwtV9zvYhKzlz1XR8Eso9n28bkmzRs/5KN/CmV8gTmm2xIMaD/CQdZW0qsMyVCHeJaweIKhCLTzIgblPYIiAP2iqnqSgwFQSJSgrWmuarTWUKSc8DevnvYFVscuviJvNkz+GWwcbfT6CgTFt2PC64hvqEHRUtZj2660V9xlZYCF375ANh5vXvXzOGRUXH6/7Dq8XCd1CDQmcQFiV1BAE1oAoElckF+jpB/edgjPZAkB0wZn4Fs7jSV66+5EXiWmGjm0rT+OInNAUv/dCWZXSKXMClrQRq50F0yHytXjT6eJgA2EYmif0lLnOozbhrSOGz+Fd5o+Qlh+aImAck8jfS+LpXjwP+/XVSpZp3ekkTpvQN7h9UDunvDUlXX0tRlonsDUhHwI9dQ9NfzU4X7FLnb4am709hsKgZiL1zBQ4YKjCs0cujILbBENvDXmNvGCdJlekl7e2LWMtJODae5OJuHtIXXbyfRl6Xu2zGg9wuh1sKkneS1PkNmFegrG/QfQL0ZyJI6Jn7yyO15JtzpBD/HDuC6LfkICh1LsWv0E0duil1Io4MnljzuL9NQdCMVuXBPvvoBi4ai4SCxp3UhXy8sZiYslB2sDtntWEE/pTsAUjEd6kvpwrPxbNxZ+nWv806/iHaGC9A+G3/yy3oy2We9u54hK+A9yfzQ7bjB1y7hRHuFSdHf3PHWQ4U1j2btXPhaEWT4TzLHrVlFRGV3YVxYj/5rf1YzeVl52LgJ5T4bvqBqal3sIAYJG/XENpg410E8DsrHNx5MR+hPqIWDq1jtxoXTRja1b81/Qzz2DsY3gPjyI3FSpeJMXbamPogzRR/jxOTUX9+zHjhvxBQD+Vy6n+aTH1Ge+Th/8pg21lmieQzNZ6c/ByCPCbjF1fSS9fOA/xK2ikon8AaeBX9AAQs+9O77GfLdxBRXNEJ0IFOgLvUtaJ9javkkLrW6abL7DgrQ5L7m5J9jeosdybsL/BnmXgmuI6LacPNjsbYV9D/avYO+xJONoKLhdnx0S1qFa6LmemQcFgyS8GLlybDbyPfwGetvuo0HyJtfRxl791OvWYAcabQ/BfmdKGuDJCRWp4x5S2Tq3ZIXXtt3CZE4kpBvOWVV6Bi8HKU3rs22dJ3YxRHNRQNsITx7bTNstTVANUnbyTdSoWICwIpUyx7URTBiVlLqtJ8KnE5lihGXn05irFs0Aj+PgMyLVE8cy4On7ibVlq+JsBqhxaMWe9StJwikJgTFSK3qnUisT+C0jiwc/lSTw6HHEKbWg451Gkqb8Mgd65EnXaLOjBCOdcK3xtDe/JPydXenYwiJHMUD9pgY2nFV8oCVnGqo7UgZZPn4sIYELWKU2ty95TDk+QVzWKER6H+4G4aJXcYiP2M2B7YB3DAkmHNTCN9TJXigif2xYOhRXHTSVuWDBL999G9j9mhQCyCg7gkZCzld/3I4CB1KHnF2N6F41gUN/GoCSl7npMbCu3fSiuhCPezR8klZBpXnBTG5IBawHEnPNFYGneC76EtqFDzRI2/bDU14RmXZlecX+nEIkbrEe7UTOGqzJI/8KLSego2nBJYQur6nXlX+IgAjBtezaP7q0/3tKCRwmLiQ71qbw5d+s0OROFF9xuHT2VVfAm80mxCFf7TW5Zx+V/Pw1ae1zOuwi4OxDGPE6RDOmqz4sbkTuv+zcTiNKigqvP7+nSIWo6B1yxQM18+aoKRWlEL2qfDbnQzsq5BuwUEd/lQJ6+vlEvxkNwKqwmFV5L7Pa1vmBVyNORf8AohswUJOkjdOLVlWDcg/+fGdpUOglkcsmwkrnK1z65RiEEKiHU73sw+fMgMmAglVqhUP91WnzV4ZHzLmVTi8S1pw4087MwtW2zDY+4G1WzdU5DowJoA4LFt27Zt2+YZ27btmTO2bdtnbNu2Z+7ch92X3f77q04lqeqqTtJ/5yVJIjpL1r4WGYakLW/WpokHVnTQQiALrmNGG2oXQ6sHZrX/hONqHcOMBY0xa40fWbIwTH4cBfXAOQ8L1hhzt4cGP/ixdwftxCtm9O8+aqqRCecPwPTMhMv2v6M8wB1n7AQkLy7uEFLhRcfGJlLhLOIOVm0RgCkwwkeshE8CF/y2BxZoWjSzG13lQg//KMSmKV/BFIdXIwpVLH9QUjLmKppOLn93XGI30XFa5ZnjsVU/3HPAZhhhtIJeWmLXiG90HymZUffbs8j7qMYQTfs3qaCCbFawID2LkbHPLSiiaE7oMU+iIMgUh59ZmzCplnwMdjhsi4VUEOeUPSGzncDK0v0igOVMAMw/iayuuH+VDKEd0TvIxAgVdm280QC31cLjezo9mkWRcpvVdlQHDtklBl3ulTWCtOBBo4talc8KEZmFHpugrVaA7fEV/QFf/6dhBpvlcWFNlPmTon0dJyoj/lVpRl+bbLbbqKLeucFbeh37i5nZNjqzqz1mPeg4gWwCkGNFgR+2KukaKkNurmorNnauSvewZ+7Q2J0X6Ig65NMIbpsisszfj98GzJzxTcTD63lJtTPKWlrn4Wn4Epqn15+fP2VY48/DyuZXyI6uZDb8HyJQjvaiafcigEk8iXNM6qfHKcHG4if06bvB3BYrOvygCzuD9b/l87Gx+jpBxx+68H34sf88CQmbJ9TtTZYDR2DJrXEr6YU6UKHFAyXJs233IHKE4U0FChAr+iWdyahZ/J1cwspd9CJ7ANiFsPutQF4wVysHMn6sWwjdN2vM/zl3JHH5xcXyN6ItB6NJ6LqfDFWIHkrcuiC2HeE+FemulxELjDVTmhY3FUoBYLUZwV03b1w8Tg2P/cnFaCd7AXV0uk3FOdczvonlXNR1faZ3UdDRPf/pGp7my30ArNAnKw8q1OKZIv67/K1of6Fah5nJlqR99hbi5wAjpNy6kya4JzdKF17p9f5Uoah44Hg9H+OLqymnI/ypHToISUtTCJmhK9YTNP6wxx8IUtFAEPBfr9Pnk+JHCn0cDREownCmIFwsBy32RP8inXhXyDkUc+3hsGegSe8TRn18kVcQdj9x2tTs8QNnuG/fbrX2qtw5z0dFdKQ8x/+u2hEwATEl0zHpIGrREVITmcTh4wcGJPQwlSJAl6HJ/7TM4uC8R19N8BuyRtHi71rgi51YstM0toKHCVnuDxsbU366jwVAe9vKEUPx8+fhg7s4YDfYF6cUNDl0B6UvBmKA8bjvQWosX8IawLp+x8uBDU2npNkzwP1xOyNS/gOMb2vVHpkAzLOOtmQqipMKzaSVV3uvqF/fE1WAG/++EmTY202xQJ4AShtI9qDnPm/ZEMieESa7bclqMUqGrpwUVUVmhoGfPW3ZAIMZFP3XZFF0taoxqjHnc83c81mU/DyfEaR9LaULhcZ9G7UIQ0leFO4o7KBk3AkxpNAczTkudtNnjOKK6MPMgAUxA2Y4UqYQuTzAi7t9nfJhU3pmxUWLp68o6hbnFc9lqKvxdqh+q0ZP1wGJCJZQwFYIOgzGp6Jppj8j4XpbvtOLun7zPpEz7mCwphJkIon4iUYIBav2GvJMNNDvqLvAecXE9vR4+aEGGIxXBoLg5NQt8pxutzZ6ZyczYDKhQ0xom9jvJMoMDBvy7clcTqJXeDFo+g94vhUGrrBUVwiQQBxleZl+AMW3tnYJ/drXK+DMYYIn3eywLiAavyM2TRAnx9sErvs/AYs3NZphaXyHy9D973uvYdYdy8t18AXlzcS4e4FKpsBggErEUVtx/dEqteF6cOzYgUZoCMRRsQi74MfmAjx7tsKpSWn+sUfdDKnG2LZMMARjcsqc++LO634fkE0GPUQ0ZKLJ1ePNvPobgHHJzdeoWbwo5pKsSXOlVjscvrdJi/sN9nvM3ZlzuoHixa4EDksn5dvkwrcyAliBiYaqGLvhoH5h1HFJQAmQsj2Cy6PRmwH+Ey5rkG6mq955pBm3PKe0hE57tWtyd9s0WNiQmIOXIqcZlpV702CfMCNjtXJyD8rOqVWfGc19UY8xP6Jck2wjNcoRiUVKSVYvoHcis/E5AgYd0dsMwFwj8zaAWvpZ2gBpIRqqkpB8cXohb/okNtDoBlgGMa+vcPdDMRz+Hu37A4yP4dB6/VO/OVurYCmsZgM5i06MkeUi2UqEYKcZCp8zihp9I4hEdjsE2Vys5rpsEtUw2IMILhup+nVb9ORJLMTvvF7HKoI4s5TCfxgGClI89ziCB8ezL6OQIiuAXvZkPoPhI2kL7GmyFsIpmIvAwNU+8s5VDW53jeA3IX/1AlqVRwA5EecwQbZvQuE0JI1d0L9gwKIpsTmQAuhufRHyxiHQht3Cj+tEXXER/1mbQADuj2GH1F7s9/vfqZcdh4d1GIBrMagRMCCzOx9InoNVBts2ZYnbsQXSDqyjHTk3cSmzkYIHvaiu5xeqsfOacwVj+MveGLmJs0IjGp94np6Ym7gSCxZWB+3MS2b/1GVsBRsTKzM2jWxDoeA5K5CwHXTAyYW8hLdXU4AXeqcVtYXM8mt0r3PNzeXgkaV3lmytXmuIhHapQWA1ltv43DUDrdu6ICx1LuFkfRoGMSOtVrfaKwABHhw9sUAVVbLe0P/Z48R2I9pxyT4zv+8tVfShmBk8SNjwouuR
*/