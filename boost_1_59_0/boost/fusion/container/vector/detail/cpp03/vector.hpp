/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2017 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VECTOR_07072005_1244)
#define FUSION_VECTOR_07072005_1244

#include <boost/preprocessor/iterate.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_binary_params.hpp>
#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/void.hpp>
#include <boost/fusion/support/detail/enabler.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/fusion/container/vector/vector_fwd.hpp>
#include <boost/fusion/container/vector/detail/cpp03/vector_n_chooser.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/add_reference.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/remove_cv_ref.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/core/enable_if.hpp>

#define FUSION_HASH #

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1600)

#define BOOST_FUSION_VECTOR_COPY_INIT()                                       \
    ctor_helper(rhs, is_base_of<vector, Sequence>())                          \

#define BOOST_FUSION_VECTOR_CTOR_HELPER()                                     \
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                  \
    static vector_n const&                                                    \
    ctor_helper(vector const& rhs, mpl::true_)                                \
    {                                                                         \
        return rhs.vec;                                                       \
    }                                                                         \
                                                                              \
    template <typename T>                                                     \
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED                                  \
    static T const&                                                           \
    ctor_helper(T const& rhs, mpl::false_)                                    \
    {                                                                         \
        return rhs;                                                           \
    }

#else

#define BOOST_FUSION_VECTOR_COPY_INIT()                                       \
    rhs                                                                       \

#define BOOST_FUSION_VECTOR_CTOR_HELPER()

#endif

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/container/vector/detail/cpp03/preprocessed/vector.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/vvector" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
#endif

/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    This is an auto-generated file. Do not edit!
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

namespace boost { namespace fusion
{
    struct void_;
    struct fusion_sequence_tag;

    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, typename T)>
    struct vector
        : sequence_base<vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, T)> >
    {
    private:

        typedef typename detail::vector_n_chooser<
            BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, T)>::type
        vector_n;

        template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, typename U)>
        friend struct vector;

    public:

        typedef typename vector_n::types types;
        typedef typename vector_n::fusion_tag fusion_tag;
        typedef typename vector_n::tag tag;
        typedef typename vector_n::size size;
        typedef typename vector_n::category category;
        typedef typename vector_n::is_view is_view;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector()
            : vec() {}

        template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, typename U)>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector(vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, U)> const& rhs)
            : vec(rhs.vec) {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector(vector const& rhs)
            : vec(rhs.vec) {}

        template <typename Sequence>
        BOOST_FUSION_GPU_ENABLED
        vector(Sequence const& rhs,
            typename enable_if<traits::is_sequence<Sequence>, detail::enabler_>::type = detail::enabler)
            : vec(BOOST_FUSION_VECTOR_COPY_INIT()) {}

        //  Expand a couple of forwarding constructors for arguments
        //  of type (T0), (T0, T1), (T0, T1, T2) etc. Example:
        //
        //  vector(
        //      typename detail::call_param<T0>::type arg0
        //    , typename detail::call_param<T1>::type arg1)
        //    : vec(arg0, arg1) {}
        #include <boost/fusion/container/vector/detail/cpp03/vector_forward_ctor.hpp>

        template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, typename U)>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, U)> const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(T const& rhs)
        {
            vec = rhs;
            return *this;
        }

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(vector const& rhs)
        {
            vec = rhs.vec;
            return *this;
        }

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)
#endif
#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) || \
    (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector(vector&& rhs)
            : vec(std::forward<vector_n>(rhs.vec)) {}

        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        vector&
        operator=(vector&& rhs)
        {
            vec = std::forward<vector_n>(rhs.vec);
            return *this;
        }

        template <typename T>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename boost::disable_if_c<
            boost::is_same<vector, typename boost::remove_cv_ref<T>::type>::value
          , vector&
        >::type
        operator=(T&& rhs)
        {
            vec = BOOST_FUSION_FWD_ELEM(T, rhs);
            return *this;
        }
#endif
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
FUSION_HASH endif
#endif

        template <int N>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<
            typename mpl::at_c<types, N>::type
        >::type
        at_impl(mpl::int_<N> index)
        {
            return vec.at_impl(index);
        }

        template <int N>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<
            typename add_const<
                typename mpl::at_c<types, N>::type
            >::type
        >::type
        at_impl(mpl::int_<N> index) const
        {
            return vec.at_impl(index);
        }

        template <typename I>
        BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<
            typename mpl::at<types, I>::type
        >::type
        at_impl(I /*index*/)
        {
            return vec.at_impl(mpl::int_<I::value>());
        }

        template<typename I>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        typename add_reference<
            typename add_const<
                typename mpl::at<types, I>::type
            >::type
        >::type
        at_impl(I /*index*/) const
        {
            return vec.at_impl(mpl::int_<I::value>());
        }

    private:

        BOOST_FUSION_VECTOR_CTOR_HELPER()
        vector_n vec;
    };
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#undef FUSION_HASH
#endif

/* vector.hpp
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
*/