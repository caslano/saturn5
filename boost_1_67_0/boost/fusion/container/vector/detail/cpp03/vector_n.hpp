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