/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
// No include guard. This file is meant to be included many times

#if !defined(FUSION_MACRO_05042005)
#define FUSION_MACRO_05042005

#define FUSION_VECTOR_CTOR_DEFAULT_INIT(z, n, _)                                \
    m##n()

#define FUSION_VECTOR_CTOR_INIT(z, n, _)                                        \
    m##n(_##n)

#define FUSION_VECTOR_MEMBER_CTOR_INIT(z, n, _)                                 \
    m##n(other.m##n)

#define FUSION_VECTOR_CTOR_FORWARD(z, n, _)                                     \
   m##n(BOOST_FUSION_FWD_ELEM(T##n, other.m##n))

#define FUSION_VECTOR_CTOR_ARG_FWD(z, n, _)                                     \
   m##n(BOOST_FUSION_FWD_ELEM(U##n, _##n))

#define FUSION_VECTOR_MEMBER_DECL(z, n, _)                                      \
    T##n m##n;

#define FUSION_VECTOR_MEMBER_FORWARD(z, n, _)                                   \
   BOOST_FUSION_FWD_ELEM(U##n, _##n)

#define FUSION_VECTOR_MEMBER_ASSIGN(z, n, _)                                    \
    this->BOOST_PP_CAT(m, n) = vec.BOOST_PP_CAT(m, n);

#define FUSION_VECTOR_MEMBER_DEREF_ASSIGN(z, n, _)                              \
    this->BOOST_PP_CAT(m, n) = *BOOST_PP_CAT(i, n);

#define FUSION_VECTOR_MEMBER_MOVE(z, n, _)                                      \
    this->BOOST_PP_CAT(m, n) = std::forward<                                    \
        BOOST_PP_CAT(T, n)>(vec.BOOST_PP_CAT(m, n));

#define FUSION_VECTOR_MEMBER_AT_IMPL(z, n, _)                                   \
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED                              \
        typename add_reference<T##n>::type                                      \
        at_impl(mpl::int_<n>) { return this->m##n; }                            \
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                    \
        typename add_reference<typename add_const<T##n>::type>::type            \
        at_impl(mpl::int_<n>) const { return this->m##n; }

#define FUSION_VECTOR_MEMBER_ITER_DECL_VAR(z, n, _)                             \
    typedef typename result_of::next<                                           \
        BOOST_PP_CAT(I, BOOST_PP_DEC(n))>::type BOOST_PP_CAT(I, n);             \
    BOOST_PP_CAT(I, n) BOOST_PP_CAT(i, n)                                       \
        = fusion::next(BOOST_PP_CAT(i, BOOST_PP_DEC(n)));

#endif

#define N BOOST_PP_ITERATION()

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    struct BOOST_PP_CAT(vector_data, N)
    {
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector_data, N)()
            : BOOST_PP_ENUM(N, FUSION_VECTOR_CTOR_DEFAULT_INIT, _) {}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        template <BOOST_PP_ENUM_PARAMS(N, typename U)>
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector_data, N)(BOOST_PP_ENUM_BINARY_PARAMS(N, U, && arg)
          , typename boost::enable_if<is_convertible<U0, T0> >::type* /*dummy*/ = 0
        )
            : BOOST_PP_ENUM(N, FUSION_VECTOR_CTOR_ARG_FWD, arg) {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector_data, N)(
            BOOST_PP_CAT(vector_data, N)&& other)
            : BOOST_PP_ENUM(N, FUSION_VECTOR_CTOR_FORWARD, arg) {}
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector_data, N)(
            BOOST_PP_ENUM_BINARY_PARAMS(
                N, typename detail::call_param<T, >::type arg))
            : BOOST_PP_ENUM(N, FUSION_VECTOR_CTOR_INIT, arg) {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector_data, N)(
            BOOST_PP_CAT(vector_data, N) const& other)
            : BOOST_PP_ENUM(N, FUSION_VECTOR_MEMBER_CTOR_INIT, _) {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector_data, N)&
        operator=(BOOST_PP_CAT(vector_data, N) const& vec)
        {
            BOOST_PP_REPEAT(N, FUSION_VECTOR_MEMBER_ASSIGN, _)
            return *this;
        }

        template <typename Sequence>
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
        static BOOST_PP_CAT(vector_data, N)
        init_from_sequence(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            BOOST_PP_REPEAT_FROM_TO(1, N, FUSION_VECTOR_MEMBER_ITER_DECL_VAR, _)
            return BOOST_PP_CAT(vector_data, N)(BOOST_PP_ENUM_PARAMS(N, *i));
        }

        template <typename Sequence>
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
        static BOOST_PP_CAT(vector_data, N)
        init_from_sequence(Sequence& seq)
        {
            typedef typename result_of::begin<Sequence>::type I0;
            I0 i0 = fusion::begin(seq);
            BOOST_PP_REPEAT_FROM_TO(1, N, FUSION_VECTOR_MEMBER_ITER_DECL_VAR, _)
            return BOOST_PP_CAT(vector_data, N)(BOOST_PP_ENUM_PARAMS(N, *i));
        }

        BOOST_PP_REPEAT(N, FUSION_VECTOR_MEMBER_DECL, _)
    };

    template <BOOST_PP_ENUM_PARAMS(N, typename T)>
    struct BOOST_PP_CAT(vector, N)
      : BOOST_PP_CAT(vector_data, N)<BOOST_PP_ENUM_PARAMS(N, T)>
      , sequence_base<BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, T)> >
    {
        typedef BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, T)> this_type;
        typedef BOOST_PP_CAT(vector_data, N)<BOOST_PP_ENUM_PARAMS(N, T)> base_type;
        typedef mpl::BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, T)> types;
        typedef vector_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::false_ is_view;
        typedef random_access_traversal_tag category;
        typedef mpl::int_<N> size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)() {}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
    BOOST_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
#if (N == 1)
        explicit
#endif
        BOOST_PP_CAT(vector, N)(
            BOOST_PP_ENUM_BINARY_PARAMS(
                N, typename detail::call_param<T, >::type arg))
            : base_type(BOOST_PP_ENUM_PARAMS(N, arg)) {}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        template <BOOST_PP_ENUM_PARAMS(N, typename U)>
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
#if (N == 1)
        explicit
        BOOST_PP_CAT(vector, N)(U0&& _0
          , typename boost::enable_if<is_convertible<U0, T0> >::type* /*dummy*/ = 0
          )
         : base_type(BOOST_FUSION_FWD_ELEM(U0, _0)) {}
#else
        BOOST_PP_CAT(vector, N)(BOOST_PP_ENUM_BINARY_PARAMS(N, U, && arg))
            : base_type(BOOST_PP_ENUM(N, FUSION_VECTOR_MEMBER_FORWARD, arg)) {}
#endif

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)(BOOST_PP_CAT(vector, N)&& rhs)
            : base_type(std::forward<base_type>(rhs)) {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)(BOOST_PP_CAT(vector, N) const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)&
        operator=(BOOST_PP_CAT(vector, N) const& vec)
        {
            base_type::operator=(vec);
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)&
        operator=(BOOST_PP_CAT(vector, N)&& vec)
        {
            BOOST_PP_REPEAT(N, FUSION_VECTOR_MEMBER_MOVE, _)
            return *this;
        }
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

        template <BOOST_PP_ENUM_PARAMS(N, typename U)>
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
    BOOST_CXX14_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)(
            BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, U)> const& vec)
            : base_type(BOOST_PP_ENUM_PARAMS(N, vec.m)) {}

        template <typename Sequence>
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)(
            Sequence const& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
#if (N == 1)
          , typename boost::disable_if<is_convertible<Sequence, T0> >::type* /*dummy*/ = 0
#endif
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <typename Sequence>
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
FUSION_HASH endif
#else
#if !defined(BOOST_CLANG)
        BOOST_CXX14_CONSTEXPR
#endif
#endif
        BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)(
            Sequence& seq
          , typename boost::enable_if<traits::is_sequence<Sequence> >::type* = 0
#if (N == 1)
          , typename boost::disable_if<is_convertible<Sequence, T0> >::type* /*dummy*/ = 0
#endif
            )
            : base_type(base_type::init_from_sequence(seq)) {}

        template <BOOST_PP_ENUM_PARAMS(N, typename U)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        BOOST_PP_CAT(vector, N)&
        operator=(BOOST_PP_CAT(vector, N)<BOOST_PP_ENUM_PARAMS(N, U)> const& vec)
        {
            BOOST_PP_REPEAT(N, FUSION_VECTOR_MEMBER_ASSIGN, _)
            return *this;
        }

        template <typename Sequence>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if<is_convertible<Sequence, T0>, this_type&>::type
        operator=(Sequence const& seq)
        {
            typedef typename result_of::begin<Sequence const>::type I0;
            I0 i0 = fusion::begin(seq);
            BOOST_PP_REPEAT_FROM_TO(1, N, FUSION_VECTOR_MEMBER_ITER_DECL_VAR, _)
            BOOST_PP_REPEAT(N, FUSION_VECTOR_MEMBER_DEREF_ASSIGN, _)
            return *this;
        }

        BOOST_PP_REPEAT(N, FUSION_VECTOR_MEMBER_AT_IMPL, _)

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

#undef N

/* vector_n.hpp
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
*/