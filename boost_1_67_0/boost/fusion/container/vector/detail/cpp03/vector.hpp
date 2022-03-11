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