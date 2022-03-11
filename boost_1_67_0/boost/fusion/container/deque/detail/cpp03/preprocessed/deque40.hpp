/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion {
    struct deque_tag;
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19 , typename T20 , typename T21 , typename T22 , typename T23 , typename T24 , typename T25 , typename T26 , typename T27 , typename T28 , typename T29 , typename T30 , typename T31 , typename T32 , typename T33 , typename T34 , typename T35 , typename T36 , typename T37 , typename T38 , typename T39>
    struct deque
        :
        detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39>::type,
        sequence_base<deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39> >
    {
        typedef deque_tag fusion_tag;
        typedef bidirectional_traversal_tag category;
        typedef typename detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39>::type base;
        typedef typename detail::deque_initial_size<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39>::type size;
        typedef mpl::int_<size::value> next_up;
        typedef mpl::int_<-1> next_down;
        typedef mpl::false_ is_view;
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1)
    : base(detail::deque_keyed_values<T0 , T1>::construct(t0 , t1))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1)
    : base(detail::deque_keyed_values<T0 , T1>::construct(t0 , t1))
{}
template <typename T_0 , typename T_1>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1)
    : base(detail::deque_keyed_values<T0 , T1>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2)
    : base(detail::deque_keyed_values<T0 , T1 , T2>::construct(t0 , t1 , t2))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2)
    : base(detail::deque_keyed_values<T0 , T1 , T2>::construct(t0 , t1 , t2))
{}
template <typename T_0 , typename T_1 , typename T_2>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2)
    : base(detail::deque_keyed_values<T0 , T1 , T2>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3>::construct(t0 , t1 , t2 , t3))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3>::construct(t0 , t1 , t2 , t3))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4>::construct(t0 , t1 , t2 , t3 , t4))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4>::construct(t0 , t1 , t2 , t3 , t4))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5>::construct(t0 , t1 , t2 , t3 , t4 , t5))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5>::construct(t0 , t1 , t2 , t3 , t4 , t5))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35 , T36 const& t36)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35 , T36 const& t36 , T37 const& t37)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35 , T36 const& t36 , T37 const& t37 , T38 const& t38)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38)))
{}
# endif
# if defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(typename detail::call_param<T0 >::type t0 , typename detail::call_param<T1 >::type t1 , typename detail::call_param<T2 >::type t2 , typename detail::call_param<T3 >::type t3 , typename detail::call_param<T4 >::type t4 , typename detail::call_param<T5 >::type t5 , typename detail::call_param<T6 >::type t6 , typename detail::call_param<T7 >::type t7 , typename detail::call_param<T8 >::type t8 , typename detail::call_param<T9 >::type t9 , typename detail::call_param<T10 >::type t10 , typename detail::call_param<T11 >::type t11 , typename detail::call_param<T12 >::type t12 , typename detail::call_param<T13 >::type t13 , typename detail::call_param<T14 >::type t14 , typename detail::call_param<T15 >::type t15 , typename detail::call_param<T16 >::type t16 , typename detail::call_param<T17 >::type t17 , typename detail::call_param<T18 >::type t18 , typename detail::call_param<T19 >::type t19 , typename detail::call_param<T20 >::type t20 , typename detail::call_param<T21 >::type t21 , typename detail::call_param<T22 >::type t22 , typename detail::call_param<T23 >::type t23 , typename detail::call_param<T24 >::type t24 , typename detail::call_param<T25 >::type t25 , typename detail::call_param<T26 >::type t26 , typename detail::call_param<T27 >::type t27 , typename detail::call_param<T28 >::type t28 , typename detail::call_param<T29 >::type t29 , typename detail::call_param<T30 >::type t30 , typename detail::call_param<T31 >::type t31 , typename detail::call_param<T32 >::type t32 , typename detail::call_param<T33 >::type t33 , typename detail::call_param<T34 >::type t34 , typename detail::call_param<T35 >::type t35 , typename detail::call_param<T36 >::type t36 , typename detail::call_param<T37 >::type t37 , typename detail::call_param<T38 >::type t38 , typename detail::call_param<T39 >::type t39)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39))
{}
# endif
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T0 const& t0 , T1 const& t1 , T2 const& t2 , T3 const& t3 , T4 const& t4 , T5 const& t5 , T6 const& t6 , T7 const& t7 , T8 const& t8 , T9 const& t9 , T10 const& t10 , T11 const& t11 , T12 const& t12 , T13 const& t13 , T14 const& t14 , T15 const& t15 , T16 const& t16 , T17 const& t17 , T18 const& t18 , T19 const& t19 , T20 const& t20 , T21 const& t21 , T22 const& t22 , T23 const& t23 , T24 const& t24 , T25 const& t25 , T26 const& t26 , T27 const& t27 , T28 const& t28 , T29 const& t29 , T30 const& t30 , T31 const& t31 , T32 const& t32 , T33 const& t33 , T34 const& t34 , T35 const& t35 , T36 const& t36 , T37 const& t37 , T38 const& t38 , T39 const& t39)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39>::construct(t0 , t1 , t2 , t3 , t4 , t5 , t6 , t7 , t8 , t9 , t10 , t11 , t12 , t13 , t14 , t15 , t16 , t17 , t18 , t19 , t20 , t21 , t22 , t23 , t24 , t25 , t26 , t27 , t28 , t29 , t30 , t31 , t32 , t33 , t34 , t35 , t36 , t37 , t38 , t39))
{}
template <typename T_0 , typename T_1 , typename T_2 , typename T_3 , typename T_4 , typename T_5 , typename T_6 , typename T_7 , typename T_8 , typename T_9 , typename T_10 , typename T_11 , typename T_12 , typename T_13 , typename T_14 , typename T_15 , typename T_16 , typename T_17 , typename T_18 , typename T_19 , typename T_20 , typename T_21 , typename T_22 , typename T_23 , typename T_24 , typename T_25 , typename T_26 , typename T_27 , typename T_28 , typename T_29 , typename T_30 , typename T_31 , typename T_32 , typename T_33 , typename T_34 , typename T_35 , typename T_36 , typename T_37 , typename T_38 , typename T_39>
BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
deque(T_0 && t0 , T_1 && t1 , T_2 && t2 , T_3 && t3 , T_4 && t4 , T_5 && t5 , T_6 && t6 , T_7 && t7 , T_8 && t8 , T_9 && t9 , T_10 && t10 , T_11 && t11 , T_12 && t12 , T_13 && t13 , T_14 && t14 , T_15 && t15 , T_16 && t16 , T_17 && t17 , T_18 && t18 , T_19 && t19 , T_20 && t20 , T_21 && t21 , T_22 && t22 , T_23 && t23 , T_24 && t24 , T_25 && t25 , T_26 && t26 , T_27 && t27 , T_28 && t28 , T_29 && t29 , T_30 && t30 , T_31 && t31 , T_32 && t32 , T_33 && t33 , T_34 && t34 , T_35 && t35 , T_36 && t36 , T_37 && t37 , T_38 && t38 , T_39 && t39)
    : base(detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19 , T20 , T21 , T22 , T23 , T24 , T25 , T26 , T27 , T28 , T29 , T30 , T31 , T32 , T33 , T34 , T35 , T36 , T37 , T38 , T39>::
      forward_(std::forward<T_0>( t0) , std::forward<T_1>( t1) , std::forward<T_2>( t2) , std::forward<T_3>( t3) , std::forward<T_4>( t4) , std::forward<T_5>( t5) , std::forward<T_6>( t6) , std::forward<T_7>( t7) , std::forward<T_8>( t8) , std::forward<T_9>( t9) , std::forward<T_10>( t10) , std::forward<T_11>( t11) , std::forward<T_12>( t12) , std::forward<T_13>( t13) , std::forward<T_14>( t14) , std::forward<T_15>( t15) , std::forward<T_16>( t16) , std::forward<T_17>( t17) , std::forward<T_18>( t18) , std::forward<T_19>( t19) , std::forward<T_20>( t20) , std::forward<T_21>( t21) , std::forward<T_22>( t22) , std::forward<T_23>( t23) , std::forward<T_24>( t24) , std::forward<T_25>( t25) , std::forward<T_26>( t26) , std::forward<T_27>( t27) , std::forward<T_28>( t28) , std::forward<T_29>( t29) , std::forward<T_30>( t30) , std::forward<T_31>( t31) , std::forward<T_32>( t32) , std::forward<T_33>( t33) , std::forward<T_34>( t34) , std::forward<T_35>( t35) , std::forward<T_36>( t36) , std::forward<T_37>( t37) , std::forward<T_38>( t38) , std::forward<T_39>( t39)))
{}
# endif
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque()
            {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(typename detail::call_param<T0>::type t0)
            : base(t0, detail::nil_keyed_element())
            {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(deque const& rhs)
            : base(rhs)
            {}
        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        BOOST_FUSION_GPU_ENABLED
        deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39> const& seq)
            : base(seq)
            {}
        template<typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        deque(Sequence const& seq
            , typename disable_if<is_convertible<Sequence, T0>, detail::enabler_>::type = detail::enabler
            , typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : base(base::from_iterator(fusion::begin(seq)))
            {}
        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque&
        operator=(T const& rhs)
        {
            base::operator=(rhs);
            return *this;
        }
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename T0_>
        BOOST_FUSION_GPU_ENABLED
        explicit deque(T0_&& t0
          , typename enable_if<is_convertible<T0_, T0>, detail::enabler_>::type = detail::enabler
          , typename disable_if_c<
                boost::is_same<deque const, typename boost::remove_reference<T0_>::type const>::value
              , detail::enabler_
            >::type = detail::enabler
         )
            : base(std::forward<T0_>( t0), detail::nil_keyed_element())
            {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit deque(deque&& rhs)
            : base(std::forward<deque>(rhs))
            {}
        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19 , typename U20 , typename U21 , typename U22 , typename U23 , typename U24 , typename U25 , typename U26 , typename U27 , typename U28 , typename U29 , typename U30 , typename U31 , typename U32 , typename U33 , typename U34 , typename U35 , typename U36 , typename U37 , typename U38 , typename U39>
        BOOST_FUSION_GPU_ENABLED
        deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39>&& seq
            , typename disable_if<
                  is_convertible<deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39>, T0>
                , detail::enabler_
              >::type = detail::enabler)
            : base(std::forward<deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19 , U20 , U21 , U22 , U23 , U24 , U25 , U26 , U27 , U28 , U29 , U30 , U31 , U32 , U33 , U34 , U35 , U36 , U37 , U38 , U39>>(seq))
            {}
        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque&
        operator=(T&& rhs)
        {
            base::operator=(std::forward<T>( rhs));
            return *this;
        }
        
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque&
        operator=(deque const& rhs)
        {
            base::operator=(static_cast<base const&>(rhs));
            return *this;
        }
# endif
    };
    template <>
    struct deque<> : detail::nil_keyed_element
    {
        typedef deque_tag fusion_tag;
        typedef bidirectional_traversal_tag category;
        typedef mpl::int_<0> size;
        typedef mpl::int_<0> next_up;
        typedef mpl::int_<-1> next_down;
        typedef mpl::false_ is_view;
        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque(Sequence const&,
            typename enable_if<
                mpl::and_<
                    traits::is_sequence<Sequence>
                  , result_of::empty<Sequence> >, detail::enabler_>::type = detail::enabler) BOOST_NOEXCEPT
        {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        deque() BOOST_NOEXCEPT {}
    };
}}

/* deque40.hpp
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
*/