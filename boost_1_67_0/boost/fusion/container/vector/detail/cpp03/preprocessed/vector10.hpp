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
    template <typename T0>
    struct vector_data1
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data1()
            : m0() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data1(U0 && arg0
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data1(
            vector_data1&& other)
            : m0(std::forward<T0>( other.m0)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data1(
            typename detail::call_param<T0 >::type arg0)
            : m0(arg0) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data1(
            vector_data1 const& other)
            : m0(other.m0) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data1&
        operator=(vector_data1 const& vec)
        {
            this->m0 = vec.m0;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data1
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            
            return vector_data1(*i0);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data1
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            
            return vector_data1(*i0);
        }
        T0 m0;
    };
    template <typename T0>
    struct vector1
      : vector_data1<T0>
      , sequence_base<vector1<T0> >
    {
        typedef vector1<T0> this_type;
        typedef vector_data1<T0> base_type;
        typedef mpl::vector1<T0> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<1> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector1() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        explicit
        vector1(
            typename detail::call_param<T0 >::type arg0)
            : base_type(arg0) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        explicit
        vector1(U0&& _0
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
          )
         : base_type(std::forward<U0>( _0)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector1(vector1&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector1(vector1 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector1&
        operator=(vector1 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector1&
        operator=(vector1&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0);
            return *this;
        }
# endif
        template <typename U0>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector1(
            vector1<U0> const& vec)
            : base_type(vec.m0) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector1(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
          , typename boost::disable_if<is_convertible<Sequence, T0> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector1(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
          , typename boost::disable_if<is_convertible<Sequence, T0> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector1&
        operator=(vector1<U0> const& vec)
        {
            this->m0 = vec.m0;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            
            this->m0 = *i0;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; }
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
    template <typename T0 , typename T1>
    struct vector_data2
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data2()
            : m0() , m1() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data2(U0 && arg0 , U1 && arg1
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data2(
            vector_data2&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data2(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
            : m0(arg0) , m1(arg1) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data2(
            vector_data2 const& other)
            : m0(other.m0) , m1(other.m1) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data2&
        operator=(vector_data2 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data2
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0);
            return vector_data2(*i0 , *i1);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data2
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0);
            return vector_data2(*i0 , *i1);
        }
        T0 m0; T1 m1;
    };
    template <typename T0 , typename T1>
    struct vector2
      : vector_data2<T0 , T1>
      , sequence_base<vector2<T0 , T1> >
    {
        typedef vector2<T0 , T1> this_type;
        typedef vector_data2<T0 , T1> base_type;
        typedef mpl::vector2<T0 , T1> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<2> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector2() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector2(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1)
            : base_type(arg0 , arg1) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector2(U0 && arg0 , U1 && arg1)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector2(vector2&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector2(vector2 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector2&
        operator=(vector2 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector2&
        operator=(vector2&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1);
            return *this;
        }
# endif
        template <typename U0 , typename U1>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector2(
            vector2<U0 , U1> const& vec)
            : base_type(vec.m0 , vec.m1) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector2(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector2(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector2&
        operator=(vector2<U0 , U1> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0);
            this->m0 = *i0; this->m1 = *i1;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; }
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
    template <typename T0 , typename T1 , typename T2>
    struct vector_data3
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data3()
            : m0() , m1() , m2() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data3(U0 && arg0 , U1 && arg1 , U2 && arg2
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data3(
            vector_data3&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data3(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
            : m0(arg0) , m1(arg1) , m2(arg2) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data3(
            vector_data3 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data3&
        operator=(vector_data3 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data3
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1);
            return vector_data3(*i0 , *i1 , *i2);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data3
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1);
            return vector_data3(*i0 , *i1 , *i2);
        }
        T0 m0; T1 m1; T2 m2;
    };
    template <typename T0 , typename T1 , typename T2>
    struct vector3
      : vector_data3<T0 , T1 , T2>
      , sequence_base<vector3<T0 , T1 , T2> >
    {
        typedef vector3<T0 , T1 , T2> this_type;
        typedef vector_data3<T0 , T1 , T2> base_type;
        typedef mpl::vector3<T0 , T1 , T2> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<3> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector3() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector3(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2)
            : base_type(arg0 , arg1 , arg2) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector3(U0 && arg0 , U1 && arg1 , U2 && arg2)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector3(vector3&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector3(vector3 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector3&
        operator=(vector3 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector3&
        operator=(vector3&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector3(
            vector3<U0 , U1 , U2> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector3(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector3(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector3&
        operator=(vector3<U0 , U1 , U2> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; }
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
    template <typename T0 , typename T1 , typename T2 , typename T3>
    struct vector_data4
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data4()
            : m0() , m1() , m2() , m3() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data4(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data4(
            vector_data4&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data4(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data4(
            vector_data4 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data4&
        operator=(vector_data4 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data4
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2);
            return vector_data4(*i0 , *i1 , *i2 , *i3);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data4
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2);
            return vector_data4(*i0 , *i1 , *i2 , *i3);
        }
        T0 m0; T1 m1; T2 m2; T3 m3;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3>
    struct vector4
      : vector_data4<T0 , T1 , T2 , T3>
      , sequence_base<vector4<T0 , T1 , T2 , T3> >
    {
        typedef vector4<T0 , T1 , T2 , T3> this_type;
        typedef vector_data4<T0 , T1 , T2 , T3> base_type;
        typedef mpl::vector4<T0 , T1 , T2 , T3> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<4> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector4() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector4(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3)
            : base_type(arg0 , arg1 , arg2 , arg3) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector4(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector4(vector4&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector4(vector4 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector4&
        operator=(vector4 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector4&
        operator=(vector4&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector4(
            vector4<U0 , U1 , U2 , U3> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector4(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector4(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector4&
        operator=(vector4<U0 , U1 , U2 , U3> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; }
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
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    struct vector_data5
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data5()
            : m0() , m1() , m2() , m3() , m4() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data5(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data5(
            vector_data5&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data5(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data5(
            vector_data5 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data5&
        operator=(vector_data5 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data5
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3);
            return vector_data5(*i0 , *i1 , *i2 , *i3 , *i4);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data5
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3);
            return vector_data5(*i0 , *i1 , *i2 , *i3 , *i4);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4>
    struct vector5
      : vector_data5<T0 , T1 , T2 , T3 , T4>
      , sequence_base<vector5<T0 , T1 , T2 , T3 , T4> >
    {
        typedef vector5<T0 , T1 , T2 , T3 , T4> this_type;
        typedef vector_data5<T0 , T1 , T2 , T3 , T4> base_type;
        typedef mpl::vector5<T0 , T1 , T2 , T3 , T4> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<5> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector5() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector5(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector5(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector5(vector5&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector5(vector5 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector5&
        operator=(vector5 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector5&
        operator=(vector5&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector5(
            vector5<U0 , U1 , U2 , U3 , U4> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector5(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector5(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector5&
        operator=(vector5<U0 , U1 , U2 , U3 , U4> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; }
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
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    struct vector_data6
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data6()
            : m0() , m1() , m2() , m3() , m4() , m5() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data6(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data6(
            vector_data6&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data6(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data6(
            vector_data6 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data6&
        operator=(vector_data6 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data6
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4);
            return vector_data6(*i0 , *i1 , *i2 , *i3 , *i4 , *i5);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data6
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4);
            return vector_data6(*i0 , *i1 , *i2 , *i3 , *i4 , *i5);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5>
    struct vector6
      : vector_data6<T0 , T1 , T2 , T3 , T4 , T5>
      , sequence_base<vector6<T0 , T1 , T2 , T3 , T4 , T5> >
    {
        typedef vector6<T0 , T1 , T2 , T3 , T4 , T5> this_type;
        typedef vector_data6<T0 , T1 , T2 , T3 , T4 , T5> base_type;
        typedef mpl::vector6<T0 , T1 , T2 , T3 , T4 , T5> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<6> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector6() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector6(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector6(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector6(vector6&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector6(vector6 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector6&
        operator=(vector6 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector6&
        operator=(vector6&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector6(
            vector6<U0 , U1 , U2 , U3 , U4 , U5> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector6(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector6(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector6&
        operator=(vector6<U0 , U1 , U2 , U3 , U4 , U5> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; }
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
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    struct vector_data7
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data7()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data7(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data7(
            vector_data7&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data7(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data7(
            vector_data7 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data7&
        operator=(vector_data7 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data7
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5);
            return vector_data7(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data7
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5);
            return vector_data7(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6>
    struct vector7
      : vector_data7<T0 , T1 , T2 , T3 , T4 , T5 , T6>
      , sequence_base<vector7<T0 , T1 , T2 , T3 , T4 , T5 , T6> >
    {
        typedef vector7<T0 , T1 , T2 , T3 , T4 , T5 , T6> this_type;
        typedef vector_data7<T0 , T1 , T2 , T3 , T4 , T5 , T6> base_type;
        typedef mpl::vector7<T0 , T1 , T2 , T3 , T4 , T5 , T6> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<7> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector7() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector7(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector7(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector7(vector7&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector7(vector7 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector7&
        operator=(vector7 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector7&
        operator=(vector7&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector7(
            vector7<U0 , U1 , U2 , U3 , U4 , U5 , U6> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector7(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector7(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector7&
        operator=(vector7<U0 , U1 , U2 , U3 , U4 , U5 , U6> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; }
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
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    struct vector_data8
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data8()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data8(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data8(
            vector_data8&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data8(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data8(
            vector_data8 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data8&
        operator=(vector_data8 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data8
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6);
            return vector_data8(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data8
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6);
            return vector_data8(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7>
    struct vector8
      : vector_data8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7>
      , sequence_base<vector8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> >
    {
        typedef vector8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> this_type;
        typedef vector_data8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> base_type;
        typedef mpl::vector8<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<8> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector8() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector8(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector8(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector8(vector8&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector8(vector8 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector8&
        operator=(vector8 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector8&
        operator=(vector8&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector8(
            vector8<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector8(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector8(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector8&
        operator=(vector8<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; }
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
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    struct vector_data9
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data9()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data9(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data9(
            vector_data9&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data9(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data9(
            vector_data9 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data9&
        operator=(vector_data9 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data9
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7);
            return vector_data9(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data9
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7);
            return vector_data9(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8>
    struct vector9
      : vector_data9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8>
      , sequence_base<vector9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> >
    {
        typedef vector9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> this_type;
        typedef vector_data9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> base_type;
        typedef mpl::vector9<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<9> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector9() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector9(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector9(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector9(vector9&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector9(vector9 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector9&
        operator=(vector9 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector9&
        operator=(vector9&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector9(
            vector9<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector9(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector9(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector9&
        operator=(vector9<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; }
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
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct vector_data10
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data10()
            : m0() , m1() , m2() , m3() , m4() , m5() , m6() , m7() , m8() , m9() {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data10(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9
          , typename boost::enable_if<is_convertible<U0, T0> >::type* = 0
        )
            : m0(std::forward<U0>( arg0)) , m1(std::forward<U1>( arg1)) , m2(std::forward<U2>( arg2)) , m3(std::forward<U3>( arg3)) , m4(std::forward<U4>( arg4)) , m5(std::forward<U5>( arg5)) , m6(std::forward<U6>( arg6)) , m7(std::forward<U7>( arg7)) , m8(std::forward<U8>( arg8)) , m9(std::forward<U9>( arg9)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data10(
            vector_data10&& other)
            : m0(std::forward<T0>( other.m0)) , m1(std::forward<T1>( other.m1)) , m2(std::forward<T2>( other.m2)) , m3(std::forward<T3>( other.m3)) , m4(std::forward<T4>( other.m4)) , m5(std::forward<T5>( other.m5)) , m6(std::forward<T6>( other.m6)) , m7(std::forward<T7>( other.m7)) , m8(std::forward<T8>( other.m8)) , m9(std::forward<T9>( other.m9)) {}
# endif
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector_data10(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
            : m0(arg0) , m1(arg1) , m2(arg2) , m3(arg3) , m4(arg4) , m5(arg5) , m6(arg6) , m7(arg7) , m8(arg8) , m9(arg9) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data10(
            vector_data10 const& other)
            : m0(other.m0) , m1(other.m1) , m2(other.m2) , m3(other.m3) , m4(other.m4) , m5(other.m5) , m6(other.m6) , m7(other.m7) , m8(other.m8) , m9(other.m9) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector_data10&
        operator=(vector_data10 const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9;
            return *this;
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data10
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8);
            return vector_data10(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9);
        }
        template <typename Sequence>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        static vector_data10
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8);
            return vector_data10(*i0 , *i1 , *i2 , *i3 , *i4 , *i5 , *i6 , *i7 , *i8 , *i9);
        }
        T0 m0; T1 m1; T2 m2; T3 m3; T4 m4; T5 m5; T6 m6; T7 m7; T8 m8; T9 m9;
    };
    template <typename T0 , typename T1 , typename T2 , typename T3 , typename T4 , typename T5 , typename T6 , typename T7 , typename T8 , typename T9>
    struct vector10
      : vector_data10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9>
      , sequence_base<vector10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> >
    {
        typedef vector10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> this_type;
        typedef vector_data10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> base_type;
        typedef mpl::vector10<T0 , T1 , T2 , T3 , T4 , T5 , T6 , T7 , T8 , T9> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; 
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<10> size;
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector10() {}
# if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector10(
            typename detail::call_param<T0 >::type arg0 , typename detail::call_param<T1 >::type arg1 , typename detail::call_param<T2 >::type arg2 , typename detail::call_param<T3 >::type arg3 , typename detail::call_param<T4 >::type arg4 , typename detail::call_param<T5 >::type arg5 , typename detail::call_param<T6 >::type arg6 , typename detail::call_param<T7 >::type arg7 , typename detail::call_param<T8 >::type arg8 , typename detail::call_param<T9 >::type arg9)
            : base_type(arg0 , arg1 , arg2 , arg3 , arg4 , arg5 , arg6 , arg7 , arg8 , arg9) {}
# if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector10(U0 && arg0 , U1 && arg1 , U2 && arg2 , U3 && arg3 , U4 && arg4 , U5 && arg5 , U6 && arg6 , U7 && arg7 , U8 && arg8 , U9 && arg9)
            : base_type(std::forward<U0>( arg0) , std::forward<U1>( arg1) , std::forward<U2>( arg2) , std::forward<U3>( arg3) , std::forward<U4>( arg4) , std::forward<U5>( arg5) , std::forward<U6>( arg6) , std::forward<U7>( arg7) , std::forward<U8>( arg8) , std::forward<U9>( arg9)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector10(vector10&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector10(vector10 const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector10&
        operator=(vector10 const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector10&
        operator=(vector10&& vec)
        {
            this->m0 = std::forward< T0>(vec.m0); this->m1 = std::forward< T1>(vec.m1); this->m2 = std::forward< T2>(vec.m2); this->m3 = std::forward< T3>(vec.m3); this->m4 = std::forward< T4>(vec.m4); this->m5 = std::forward< T5>(vec.m5); this->m6 = std::forward< T6>(vec.m6); this->m7 = std::forward< T7>(vec.m7); this->m8 = std::forward< T8>(vec.m8); this->m9 = std::forward< T9>(vec.m9);
            return *this;
        }
# endif
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
# if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector10(
            vector10<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& vec)
            : base_type(vec.m0 , vec.m1 , vec.m2 , vec.m3 , vec.m4 , vec.m5 , vec.m6 , vec.m7 , vec.m8 , vec.m9) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector10(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename Sequence>
# if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
# endif
        BOOST_FUSION_GPU_ENABLED
        vector10(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
            )
            : base_type(base_type::init_from_sequence(seq)) {}
        template <typename U0 , typename U1 , typename U2 , typename U3 , typename U4 , typename U5 , typename U6 , typename U7 , typename U8 , typename U9>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector10&
        operator=(vector10<U0 , U1 , U2 , U3 , U4 , U5 , U6 , U7 , U8 , U9> const& vec)
        {
            this->m0 = vec.m0; this->m1 = vec.m1; this->m2 = vec.m2; this->m3 = vec.m3; this->m4 = vec.m4; this->m5 = vec.m5; this->m6 = vec.m6; this->m7 = vec.m7; this->m8 = vec.m8; this->m9 = vec.m9;
            return *this;
        }
        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            typedef typename result_of::next< I0>::type I1; I1 i1 = fusion::next(i0); typedef typename result_of::next< I1>::type I2; I2 i2 = fusion::next(i1); typedef typename result_of::next< I2>::type I3; I3 i3 = fusion::next(i2); typedef typename result_of::next< I3>::type I4; I4 i4 = fusion::next(i3); typedef typename result_of::next< I4>::type I5; I5 i5 = fusion::next(i4); typedef typename result_of::next< I5>::type I6; I6 i6 = fusion::next(i5); typedef typename result_of::next< I6>::type I7; I7 i7 = fusion::next(i6); typedef typename result_of::next< I7>::type I8; I8 i8 = fusion::next(i7); typedef typename result_of::next< I8>::type I9; I9 i9 = fusion::next(i8);
            this->m0 = *i0; this->m1 = *i1; this->m2 = *i2; this->m3 = *i3; this->m4 = *i4; this->m5 = *i5; this->m6 = *i6; this->m7 = *i7; this->m8 = *i8; this->m9 = *i9;
            return *this;
        }
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T0>::type at_impl(mpl::int_<0>) { return this->m0; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T0>::type>::type at_impl(mpl::int_<0>) const { return this->m0; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T1>::type at_impl(mpl::int_<1>) { return this->m1; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T1>::type>::type at_impl(mpl::int_<1>) const { return this->m1; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T2>::type at_impl(mpl::int_<2>) { return this->m2; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T2>::type>::type at_impl(mpl::int_<2>) const { return this->m2; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T3>::type at_impl(mpl::int_<3>) { return this->m3; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T3>::type>::type at_impl(mpl::int_<3>) const { return this->m3; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T4>::type at_impl(mpl::int_<4>) { return this->m4; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T4>::type>::type at_impl(mpl::int_<4>) const { return this->m4; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T5>::type at_impl(mpl::int_<5>) { return this->m5; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T5>::type>::type at_impl(mpl::int_<5>) const { return this->m5; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T6>::type at_impl(mpl::int_<6>) { return this->m6; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T6>::type>::type at_impl(mpl::int_<6>) const { return this->m6; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T7>::type at_impl(mpl::int_<7>) { return this->m7; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T7>::type>::type at_impl(mpl::int_<7>) const { return this->m7; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T8>::type at_impl(mpl::int_<8>) { return this->m8; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T8>::type>::type at_impl(mpl::int_<8>) const { return this->m8; } BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<T9>::type at_impl(mpl::int_<9>) { return this->m9; } BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED typename add_reference<typename add_const<T9>::type>::type at_impl(mpl::int_<9>) const { return this->m9; }
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

/* vector10.hpp
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
*/