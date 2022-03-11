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