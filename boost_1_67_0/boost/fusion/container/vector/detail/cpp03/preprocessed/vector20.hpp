/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/
namespace boost { namespace fusion
{
    struct vector_tag;
    struct fusion_sequence_tag;
    struct random_access_traversal_tag;
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    struct vector_data11
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data11()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data11(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data11(
            vector_data11&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data11(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data11(
            vector_data11 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data11&
        operator=(vector_data11 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data11
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9);
            return vector_data11(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data11
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9);
            return vector_data11(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10>
    struct vector11
      : vector_data11<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10>
      , sequence_base<vector11<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10> >
    {
        typedef vector11<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10> this_type;
        typedef vector_data11<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10> base_type;
        typedef mpl::vector11<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<11> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector11() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector11(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector11(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector11(vector11&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector11(vector11 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector11&
        operator=(vector11 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector11&
        operator=(vector11&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector11(
            vector11<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector11(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector11(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector11&
        operator=(vector11<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    struct vector_data12
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data12()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data12(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data12(
            vector_data12&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data12(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data12(
            vector_data12 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data12&
        operator=(vector_data12 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data12
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10);
            return vector_data12(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data12
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10);
            return vector_data12(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11>
    struct vector12
      : vector_data12<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11>
      , sequence_base<vector12<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11> >
    {
        typedef vector12<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11> this_type;
        typedef vector_data12<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11> base_type;
        typedef mpl::vector12<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<12> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector12() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector12(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector12(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector12(vector12&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector12(vector12 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector12&
        operator=(vector12 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector12&
        operator=(vector12&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector12(
            vector12<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector12(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector12(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector12&
        operator=(vector12<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    struct vector_data13
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data13()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data13(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) , m12(std::forward<U12>( arg12)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data13(
            vector_data13&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) , m12(std::forward<T12>( other.m12)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data13(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) , m12(arg12) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data13(
            vector_data13 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data13&
        operator=(vector_data13 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data13
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11);
            return vector_data13(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data13
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11);
            return vector_data13(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11; T12 m12;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12>
    struct vector13
      : vector_data13<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12>
      , sequence_base<vector13<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12> >
    {
        typedef vector13<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12> this_type;
        typedef vector_data13<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12> base_type;
        typedef mpl::vector13<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<13> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector13() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector13(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector13(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector13(vector13&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector13(vector13 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector13&
        operator=(vector13 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector13&
        operator=(vector13&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11); this->m12 = std::forward< T12>(vec.m12);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector13(
            vector13<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector13(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector13(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector13&
        operator=(vector13<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11; this->m12 = *i12;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T12>::type at_impl(mpl::int_<12>) { return this->m12; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T12>::type>::type at_impl(mpl::int_<12>) const { return this->m12; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    struct vector_data14
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data14()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data14(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) , m12(std::forward<U12>( arg12)) , m13(std::forward<U13>( arg13)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data14(
            vector_data14&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) , m12(std::forward<T12>( other.m12)) , m13(std::forward<T13>( other.m13)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data14(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) , m12(arg12) , m13(arg13) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data14(
            vector_data14 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data14&
        operator=(vector_data14 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data14
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12);
            return vector_data14(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data14
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12);
            return vector_data14(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11; T12 m12; T13 m13;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13>
    struct vector14
      : vector_data14<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13>
      , sequence_base<vector14<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13> >
    {
        typedef vector14<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13> this_type;
        typedef vector_data14<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13> base_type;
        typedef mpl::vector14<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<14> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector14() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector14(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector14(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector14(vector14&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector14(vector14 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector14&
        operator=(vector14 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector14&
        operator=(vector14&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11); this->m12 = std::forward< T12>(vec.m12); this->m13 = std::forward< T13>(vec.m13);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector14(
            vector14<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector14(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector14(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector14&
        operator=(vector14<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11; this->m12 = *i12; this->m13 = *i13;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T12>::type at_impl(mpl::int_<12>) { return this->m12; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T12>::type>::type at_impl(mpl::int_<12>) const { return this->m12; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T13>::type at_impl(mpl::int_<13>) { return this->m13; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T13>::type>::type at_impl(mpl::int_<13>) const { return this->m13; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    struct vector_data15
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data15()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data15(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) , m12(std::forward<U12>( arg12)) , m13(std::forward<U13>( arg13)) , m14(std::forward<U14>( arg14)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data15(
            vector_data15&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) , m12(std::forward<T12>( other.m12)) , m13(std::forward<T13>( other.m13)) , m14(std::forward<T14>( other.m14)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data15(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) , m12(arg12) , m13(arg13) , m14(arg14) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data15(
            vector_data15 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data15&
        operator=(vector_data15 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data15
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13);
            return vector_data15(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data15
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13);
            return vector_data15(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11; T12 m12; T13 m13; T14 m14;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14>
    struct vector15
      : vector_data15<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14>
      , sequence_base<vector15<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14> >
    {
        typedef vector15<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14> this_type;
        typedef vector_data15<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14> base_type;
        typedef mpl::vector15<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<15> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector15() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector15(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector15(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector15(vector15&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector15(vector15 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector15&
        operator=(vector15 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector15&
        operator=(vector15&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11); this->m12 = std::forward< T12>(vec.m12); this->m13 = std::forward< T13>(vec.m13); this->m14 = std::forward< T14>(vec.m14);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector15(
            vector15<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector15(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector15(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector15&
        operator=(vector15<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11; this->m12 = *i12; this->m13 = *i13; this->m14 = *i14;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T12>::type at_impl(mpl::int_<12>) { return this->m12; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T12>::type>::type at_impl(mpl::int_<12>) const { return this->m12; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T13>::type at_impl(mpl::int_<13>) { return this->m13; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T13>::type>::type at_impl(mpl::int_<13>) const { return this->m13; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T14>::type at_impl(mpl::int_<14>) { return this->m14; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T14>::type>::type at_impl(mpl::int_<14>) const { return this->m14; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    struct vector_data16
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data16()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data16(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) , m12(std::forward<U12>( arg12)) , m13(std::forward<U13>( arg13)) , m14(std::forward<U14>( arg14)) , m15(std::forward<U15>( arg15)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data16(
            vector_data16&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) , m12(std::forward<T12>( other.m12)) , m13(std::forward<T13>( other.m13)) , m14(std::forward<T14>( other.m14)) , m15(std::forward<T15>( other.m15)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data16(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) , m12(arg12) , m13(arg13) , m14(arg14) , m15(arg15) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data16(
            vector_data16 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data16&
        operator=(vector_data16 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data16
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14);
            return vector_data16(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data16
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14);
            return vector_data16(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11; T12 m12; T13 m13; T14 m14; T15 m15;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15>
    struct vector16
      : vector_data16<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15>
      , sequence_base<vector16<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15> >
    {
        typedef vector16<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15> this_type;
        typedef vector_data16<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15> base_type;
        typedef mpl::vector16<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<16> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector16() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector16(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector16(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector16(vector16&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector16(vector16 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector16&
        operator=(vector16 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector16&
        operator=(vector16&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11); this->m12 = std::forward< T12>(vec.m12); this->m13 = std::forward< T13>(vec.m13); this->m14 = std::forward< T14>(vec.m14); this->m15 = std::forward< T15>(vec.m15);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector16(
            vector16<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector16(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector16(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector16&
        operator=(vector16<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11; this->m12 = *i12; this->m13 = *i13; this->m14 = *i14; this->m15 = *i15;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T12>::type at_impl(mpl::int_<12>) { return this->m12; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T12>::type>::type at_impl(mpl::int_<12>) const { return this->m12; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T13>::type at_impl(mpl::int_<13>) { return this->m13; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T13>::type>::type at_impl(mpl::int_<13>) const { return this->m13; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T14>::type at_impl(mpl::int_<14>) { return this->m14; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T14>::type>::type at_impl(mpl::int_<14>) const { return this->m14; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T15>::type at_impl(mpl::int_<15>) { return this->m15; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T15>::type>::type at_impl(mpl::int_<15>) const { return this->m15; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    struct vector_data17
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data17()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data17(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) , m12(std::forward<U12>( arg12)) , m13(std::forward<U13>( arg13)) , m14(std::forward<U14>( arg14)) , m15(std::forward<U15>( arg15)) , m16(std::forward<U16>( arg16)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data17(
            vector_data17&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) , m12(std::forward<T12>( other.m12)) , m13(std::forward<T13>( other.m13)) , m14(std::forward<T14>( other.m14)) , m15(std::forward<T15>( other.m15)) , m16(std::forward<T16>( other.m16)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data17(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) , m12(arg12) , m13(arg13) , m14(arg14) , m15(arg15) , m16(arg16) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data17(
            vector_data17 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data17&
        operator=(vector_data17 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data17
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15);
            return vector_data17(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data17
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15);
            return vector_data17(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11; T12 m12; T13 m13; T14 m14; T15 m15; T16 m16;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16>
    struct vector17
      : vector_data17<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16>
      , sequence_base<vector17<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16> >
    {
        typedef vector17<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16> this_type;
        typedef vector_data17<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16> base_type;
        typedef mpl::vector17<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<17> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector17() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector17(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector17(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15) , std::forward<U16>( arg16)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector17(vector17&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector17(vector17 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector17&
        operator=(vector17 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector17&
        operator=(vector17&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11); this->m12 = std::forward< T12>(vec.m12); this->m13 = std::forward< T13>(vec.m13); this->m14 = std::forward< T14>(vec.m14); this->m15 = std::forward< T15>(vec.m15); this->m16 = std::forward< T16>(vec.m16);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector17(
            vector17<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector17(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector17(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector17&
        operator=(vector17<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11; this->m12 = *i12; this->m13 = *i13; this->m14 = *i14; this->m15 = *i15; this->m16 = *i16;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T12>::type at_impl(mpl::int_<12>) { return this->m12; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T12>::type>::type at_impl(mpl::int_<12>) const { return this->m12; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T13>::type at_impl(mpl::int_<13>) { return this->m13; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T13>::type>::type at_impl(mpl::int_<13>) const { return this->m13; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T14>::type at_impl(mpl::int_<14>) { return this->m14; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T14>::type>::type at_impl(mpl::int_<14>) const { return this->m14; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T15>::type at_impl(mpl::int_<15>) { return this->m15; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T15>::type>::type at_impl(mpl::int_<15>) const { return this->m15; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T16>::type at_impl(mpl::int_<16>) { return this->m16; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T16>::type>::type at_impl(mpl::int_<16>) const { return this->m16; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    struct vector_data18
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data18()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data18(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) , m12(std::forward<U12>( arg12)) , m13(std::forward<U13>( arg13)) , m14(std::forward<U14>( arg14)) , m15(std::forward<U15>( arg15)) , m16(std::forward<U16>( arg16)) , m17(std::forward<U17>( arg17)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data18(
            vector_data18&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) , m12(std::forward<T12>( other.m12)) , m13(std::forward<T13>( other.m13)) , m14(std::forward<T14>( other.m14)) , m15(std::forward<T15>( other.m15)) , m16(std::forward<T16>( other.m16)) , m17(std::forward<T17>( other.m17)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data18(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) , m12(arg12) , m13(arg13) , m14(arg14) , m15(arg15) , m16(arg16) , m17(arg17) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data18(
            vector_data18 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data18&
        operator=(vector_data18 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data18
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16);
            return vector_data18(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data18
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16);
            return vector_data18(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11; T12 m12; T13 m13; T14 m14; T15 m15; T16 m16; T17 m17;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17>
    struct vector18
      : vector_data18<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17>
      , sequence_base<vector18<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17> >
    {
        typedef vector18<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17> this_type;
        typedef vector_data18<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17> base_type;
        typedef mpl::vector18<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<18> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector18() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector18(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector18(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15) , std::forward<U16>( arg16) , std::forward<U17>( arg17)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector18(vector18&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector18(vector18 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector18&
        operator=(vector18 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector18&
        operator=(vector18&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11); this->m12 = std::forward< T12>(vec.m12); this->m13 = std::forward< T13>(vec.m13); this->m14 = std::forward< T14>(vec.m14); this->m15 = std::forward< T15>(vec.m15); this->m16 = std::forward< T16>(vec.m16); this->m17 = std::forward< T17>(vec.m17);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector18(
            vector18<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector18(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector18(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector18&
        operator=(vector18<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11; this->m12 = *i12; this->m13 = *i13; this->m14 = *i14; this->m15 = *i15; this->m16 = *i16; this->m17 = *i17;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T12>::type at_impl(mpl::int_<12>) { return this->m12; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T12>::type>::type at_impl(mpl::int_<12>) const { return this->m12; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T13>::type at_impl(mpl::int_<13>) { return this->m13; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T13>::type>::type at_impl(mpl::int_<13>) const { return this->m13; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T14>::type at_impl(mpl::int_<14>) { return this->m14; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T14>::type>::type at_impl(mpl::int_<14>) const { return this->m14; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T15>::type at_impl(mpl::int_<15>) { return this->m15; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T15>::type>::type at_impl(mpl::int_<15>) const { return this->m15; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T16>::type at_impl(mpl::int_<16>) { return this->m16; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T16>::type>::type at_impl(mpl::int_<16>) const { return this->m16; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T17>::type at_impl(mpl::int_<17>) { return this->m17; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T17>::type>::type at_impl(mpl::int_<17>) const { return this->m17; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    struct vector_data19
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data19()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data19(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17 , U18 && arg18
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) , m12(std::forward<U12>( arg12)) , m13(std::forward<U13>( arg13)) , m14(std::forward<U14>( arg14)) , m15(std::forward<U15>( arg15)) , m16(std::forward<U16>( arg16)) , m17(std::forward<U17>( arg17)) , m18(std::forward<U18>( arg18)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data19(
            vector_data19&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) , m12(std::forward<T12>( other.m12)) , m13(std::forward<T13>( other.m13)) , m14(std::forward<T14>( other.m14)) , m15(std::forward<T15>( other.m15)) , m16(std::forward<T16>( other.m16)) , m17(std::forward<T17>( other.m17)) , m18(std::forward<T18>( other.m18)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data19(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) , m12(arg12) , m13(arg13) , m14(arg14) , m15(arg15) , m16(arg16) , m17(arg17) , m18(arg18) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data19(
            vector_data19 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data19&
        operator=(vector_data19 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data19
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17);
            return vector_data19(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data19
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17);
            return vector_data19(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11; T12 m12; T13 m13; T14 m14; T15 m15; T16 m16; T17 m17; T18 m18;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18>
    struct vector19
      : vector_data19<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18>
      , sequence_base<vector19<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18> >
    {
        typedef vector19<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18> this_type;
        typedef vector_data19<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18> base_type;
        typedef mpl::vector19<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<19> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector19() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector19(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector19(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17 , U18 && arg18)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15) , std::forward<U16>( arg16) , std::forward<U17>( arg17) , std::forward<U18>( arg18)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector19(vector19&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector19(vector19 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector19&
        operator=(vector19 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector19&
        operator=(vector19&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11); this->m12 = std::forward< T12>(vec.m12); this->m13 = std::forward< T13>(vec.m13); this->m14 = std::forward< T14>(vec.m14); this->m15 = std::forward< T15>(vec.m15); this->m16 = std::forward< T16>(vec.m16); this->m17 = std::forward< T17>(vec.m17); this->m18 = std::forward< T18>(vec.m18);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector19(
            vector19<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector19(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector19(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector19&
        operator=(vector19<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11; this->m12 = *i12; this->m13 = *i13; this->m14 = *i14; this->m15 = *i15; this->m16 = *i16; this->m17 = *i17; this->m18 = *i18;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T12>::type at_impl(mpl::int_<12>) { return this->m12; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T12>::type>::type at_impl(mpl::int_<12>) const { return this->m12; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T13>::type at_impl(mpl::int_<13>) { return this->m13; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T13>::type>::type at_impl(mpl::int_<13>) const { return this->m13; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T14>::type at_impl(mpl::int_<14>) { return this->m14; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T14>::type>::type at_impl(mpl::int_<14>) const { return this->m14; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T15>::type at_impl(mpl::int_<15>) { return this->m15; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T15>::type>::type at_impl(mpl::int_<15>) const { return this->m15; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T16>::type at_impl(mpl::int_<16>) { return this->m16; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T16>::type>::type at_impl(mpl::int_<16>) const { return this->m16; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T17>::type at_impl(mpl::int_<17>) { return this->m17; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T17>::type>::type at_impl(mpl::int_<17>) const { return this->m17; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T18>::type at_impl(mpl::int_<18>) { return this->m18; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T18>::type>::type at_impl(mpl::int_<18>) const { return this->m18; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    struct vector_data20
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data20()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() , m10() , m11() , m12() , m13() , m14() , m15() , m16() , m17() , m18() , m19() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data20(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17 , U18 && arg18 , U19 && arg19
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) , m10(std::forward<U10>( arg10)) , m11(std::forward<U11>( arg11)) , m12(std::forward<U12>( arg12)) , m13(std::forward<U13>( arg13)) , m14(std::forward<U14>( arg14)) , m15(std::forward<U15>( arg15)) , m16(std::forward<U16>( arg16)) , m17(std::forward<U17>( arg17)) , m18(std::forward<U18>( arg18)) , m19(std::forward<U19>( arg19)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data20(
            vector_data20&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) , m10(std::forward<T10>( other.m10)) , m11(std::forward<T11>( other.m11)) , m12(std::forward<T12>( other.m12)) , m13(std::forward<T13>( other.m13)) , m14(std::forward<T14>( other.m14)) , m15(std::forward<T15>( other.m15)) , m16(std::forward<T16>( other.m16)) , m17(std::forward<T17>( other.m17)) , m18(std::forward<T18>( other.m18)) , m19(std::forward<T19>( other.m19)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data20(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) , m10(arg10) , m11(arg11) , m12(arg12) , m13(arg13) , m14(arg14) , m15(arg15) , m16(arg16) , m17(arg17) , m18(arg18) , m19(arg19) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data20(
            vector_data20 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) , m10(other.m10) , m11(other.m11) , m12(other.m12) , m13(other.m13) , m14(other.m14) , m15(other.m15) , m16(other.m16) , m17(other.m17) , m18(other.m18) , m19(other.m19) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data20&
        operator=(vector_data20 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data20
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18);
            return vector_data20(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data20
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18);
            return vector_data20(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9 , *i10 , *i11 , *i12 , *i13 , *i14 , *i15 , *i16 , *i17 , *i18 , *i19);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9; T10 m10; T11 m11; T12 m12; T13 m13; T14 m14; T15 m15; T16 m16; T17 m17; T18 m18; T19 m19;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9 , typename T10 , typename T11 , typename T12 , typename T13 , typename T14 , typename T15 , typename T16 , typename T17 , typename T18 , typename T19>
    struct vector20
      : vector_data20<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19>
      , sequence_base<vector20<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> >
    {
        typedef vector20<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> this_type;
        typedef vector_data20<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> base_type;
        typedef mpl::vector20<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9 , T10 , T11 , T12 , T13 , T14 , T15 , T16 , T17 , T18 , T19> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<20> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector20() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector20(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9 , typename detail::call_param<T10 >::type arg10 , typename detail::call_param<T11 >::type arg11 , typename detail::call_param<T12 >::type arg12 , typename detail::call_param<T13 >::type arg13 , typename detail::call_param<T14 >::type arg14 , typename detail::call_param<T15 >::type arg15 , typename detail::call_param<T16 >::type arg16 , typename detail::call_param<T17 >::type arg17 , typename detail::call_param<T18 >::type arg18 , typename detail::call_param<T19 >::type arg19)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9 , arg10 , arg11 , arg12 , arg13 , arg14 , arg15 , arg16 , arg17 , arg18 , arg19) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector20(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9 , U10 && arg10 , U11 && arg11 , U12 && arg12 , U13 && arg13 , U14 && arg14 , U15 && arg15 , U16 && arg16 , U17 && arg17 , U18 && arg18 , U19 && arg19)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9) , std::forward<U10>( arg10) , std::forward<U11>( arg11) , std::forward<U12>( arg12) , std::forward<U13>( arg13) , std::forward<U14>( arg14) , std::forward<U15>( arg15) , std::forward<U16>( arg16) , std::forward<U17>( arg17) , std::forward<U18>( arg18) , std::forward<U19>( arg19)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector20(vector20&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector20(vector20 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector20&
        operator=(vector20 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector20&
        operator=(vector20&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9); this->m10 = std::forward< T10>(vec.m10); this->m11 = std::forward< T11>(vec.m11); this->m12 = std::forward< T12>(vec.m12); this->m13 = std::forward< T13>(vec.m13); this->m14 = std::forward< T14>(vec.m14); this->m15 = std::forward< T15>(vec.m15); this->m16 = std::forward< T16>(vec.m16); this->m17 = std::forward< T17>(vec.m17); this->m18 = std::forward< T18>(vec.m18); this->m19 = std::forward< T19>(vec.m19);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector20(
            vector20<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9 , vec.m10 , vec.m11 , vec.m12 , vec.m13 , vec.m14 , vec.m15 , vec.m16 , vec.m17 , vec.m18 , vec.m19) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector20(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector20(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9 , typename U10 , typename U11 , typename U12 , typename U13 , typename U14 , typename U15 , typename U16 , typename U17 , typename U18 , typename U19>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector20&
        operator=(vector20<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9 , U10 , U11 , U12 , U13 , U14 , U15 , U16 , U17 , U18 , U19> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9; this->m10 = vec.m10; this->m11 = vec.m11; this->m12 = vec.m12; this->m13 = vec.m13; this->m14 = vec.m14; this->m15 = vec.m15; this->m16 = vec.m16; this->m17 = vec.m17; this->m18 = vec.m18; this->m19 = vec.m19;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8); typedef typename result_of::next< I9>::type I10; I10 i10 = fusion::next(i9); typedef typename result_of::next< I10>::type I11; I11 i11 = fusion::next(i10); typedef typename result_of::next< I11>::type I12; I12 i12 = fusion::next(i11); typedef typename result_of::next< I12>::type I13; I13 i13 = fusion::next(i12); typedef typename result_of::next< I13>::type I14; I14 i14 = fusion::next(i13); typedef typename result_of::next< I14>::type I15; I15 i15 = fusion::next(i14); typedef typename result_of::next< I15>::type I16; I16 i16 = fusion::next(i15); typedef typename result_of::next< I16>::type I17; I17 i17 = fusion::next(i16); typedef typename result_of::next< I17>::type I18; I18 i18 = fusion::next(i17); typedef typename result_of::next< I18>::type I19; I19 i19 = fusion::next(i18);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9; this->m10 = *i10; this->m11 = *i11; this->m12 = *i12; this->m13 = *i13; this->m14 = *i14; this->m15 = *i15; this->m16 = *i16; this->m17 = *i17; this->m18 = *i18; this->m19 = *i19;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T10>::type at_impl(mpl::int_<10>) { return this->m10; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T10>::type>::type at_impl(mpl::int_<10>) const { return this->m10; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T11>::type at_impl(mpl::int_<11>) { return this->m11; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T11>::type>::type at_impl(mpl::int_<11>) const { return this->m11; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T12>::type at_impl(mpl::int_<12>) { return this->m12; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T12>::type>::type at_impl(mpl::int_<12>) const { return this->m12; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T13>::type at_impl(mpl::int_<13>) { return this->m13; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T13>::type>::type at_impl(mpl::int_<13>) const { return this->m13; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T14>::type at_impl(mpl::int_<14>) { return this->m14; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T14>::type>::type at_impl(mpl::int_<14>) const { return this->m14; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T15>::type at_impl(mpl::int_<15>) { return this->m15; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T15>::type>::type at_impl(mpl::int_<15>) const { return this->m15; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T16>::type at_impl(mpl::int_<16>) { return this->m16; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T16>::type>::type at_impl(mpl::int_<16>) const { return this->m16; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T17>::type at_impl(mpl::int_<17>) { return this->m17; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T17>::type>::type at_impl(mpl::int_<17>) const { return this->m17; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T18>::type at_impl(mpl::int_<18>) { return this->m18; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T18>::type>::type at_impl(mpl::int_<18>) const { return this->m18; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T19>::type at_impl(mpl::int_<19>) { return this->m19; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T19>::type>::type at_impl(mpl::int_<19>) const { return this->m19; }
        template<typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename mpl::at<types, I>::type>::type
        at_impl(I)
        {
            return this->at_impl(mpl::int_<I::value>());
        }
        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<typename add_const<typename mpl::at<types, I>::type>::type>::type
        at_impl(I) const
        {
            return this->at_impl(mpl::int_<I::value>());
        }
    };
}}

/* vector20.hpp
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
*/