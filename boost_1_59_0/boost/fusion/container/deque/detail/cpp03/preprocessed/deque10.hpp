/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion {
    struct deque_tag;
    template<typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct deque
        :
        detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>::type,
        sequence_base<deque<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> >
    {
        typedef deque_tag fusion_tag;
        typedef bidirectional_traversal_tag category;
        typedef typename detail::deque_keyed_values<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>::type base;
        typedef typename detail::deque_initial_size<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>::type size;
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
        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        BOOST_FUSION_GPU_ENABLED
        deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& seq)
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
        template<typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        BOOST_FUSION_GPU_ENABLED
        deque(deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9>&& seq
            , typename disable_if<
                  is_convertible<deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9>, T0>
                , detail::enabler_
              >::type = detail::enabler)
            : base(std::forward<deque<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9>>(seq))
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

/* deque10.hpp
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
*/