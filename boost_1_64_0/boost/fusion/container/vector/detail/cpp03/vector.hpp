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
GyLboZ4vctWx7eyG8pn3o9NItkPODe4+WyjrScpv53jt+ZQrb1/7W44V7/6jSNo4qddL/6UynmgFLlWO+71VdRHYcV/rOY/j3uPcWWJy7iw1qYs4/bnTu88zOfZlO7X35zrkP5S6Ok09na/n/s2+bJ9WV8necVHq8uHUR3MWfEm3fKL38obPyGWpw8ZShw2wlOXPPFdVh4F/RuRY0uXr/7Hk1T+ce7Z8frTjqbnn58RWlJWfnlvAl6shxiW1vvRvQGoo33PLlQvKg/oYG84mxPTk5VUf06OP3zlS3zxWaOvBmo8Vig7xzusuXpw46NGHUAB52X3ktS/Eu7+iVUrGhwx5FTtyri4vY9+8dmeR57beYB4XlXDo2sZFVTemovlYgoGPYRjo2Iw1dS8t0HipQOOHampMRfN7coHHP/kaO/Ej1729LTkvhSX/deOLN97z1eL9reI/dt/bK7HIb208RDrDHw0wj6RMi2pxLw8XY3tcgt1wGfbHUkzB5ZiKd2I2rsR78S7cjqvwaSzD/XgPuu+RyW9kdJLOeNwjWyv9C5SjFR/AfrgOB+N6yX8DzsWHsBA3yvrjasnvW/ndy/pdn68oVKY35J7WW9gJf4mx+DZOx3cwDX+Lc/AUluHv8CE8jVvwD7gbP8Dn8Ay+ih/iSfwI38OzeBnPYV0Zoy4S/4xd8Tz2w08wES9gJv4N78C/4xr8B77KcVOJjdmuT7ElfoZ98Z84AT/HLPwCZ+OXmIuXcDn+G1fh17gFv8Ed+C2yLp65yu9q+b2t1F9HV/8K8gUo+2cotsLhGIkjMQYTcSjehtNwFC7F0ViGY/AgjsX3cRyexfH4CU7EyzgZryPPKdgVU7EvTsWhOA3H43RcgDNwCc7E1/B2/Bna8M+Yhp/gLKzLdmVgCGZhGGbjrZiDrTEXu+EcLMW5uArzcDMW4Hach09iEf4MHfgOFuNJnI/UK/tNfpfjzVKvLVzHhXt6RI7LzdgJt2AsPo7TcSum4Q6cgzvxPnwCH8Rn8Anci/txH76M+/ENfA7/iM/jGTyA9SjDQWyEh7AnvoCxeBiH4cuYjj/FpfgKnsBX8QK+jp/hEVTq8+fYCI/iZ/IMSH6785vevd29lPJj1T3hCEzE9jga4zAJZ+AYTMdkdOB4LMGJeBdOwvU4GbfjLHwKM/BtzMR3MRs/tEh8IubgzcpFErbCOdgO52IPzMNBWIAHquITcR5+g0XYpg77GztiMXbH+ZiCCzANSzALF6EDF2MZLsHHcCkexGX4MpYq+weX45/wTvwXrsQm1N9dGIarsC+W4XC8B0fiapyEazAf78NivB9XYDnejw/iQ7gBt+JDuB03Vj3LqKVeZ1h+LsdrJH8noTLVke+Jutger8eBWB9nYQjmYgN8HhviUWyEf8Wb8FNsgqzDcjM2wjBsirdgS2yKrbA5RmELHIoROA5b4XRsgxnYFldhO1yLHfA97IjnsBNews4YwXZ1wdbYFftgd0zBaJyMPTAXe6IDe2Ex9sZFGIv3Yhw+gn1xG8bjARyAr+BArECOKRmTVK5B5NrkjMeYpLfK56IFdsAfYTS2whS04u3YCbOxsy7Ocz12w20Yja9gD/w99sSPsZeMLRqDzTAWJ2EclmBfXIn9cA/2x704EI/hIHwHE/AcDsbLOBS5xtLFw8q1CDaTZzs++7eR5VpXs9wJP5ezyLPGLtUslyDLdfKx3DFXXGzNPDMKjocafGYUfGZUM8+MZjxHnDppPelp0jHSeZLlefrAIcWTZpBKSOtJ+54PPjsKTsEpOAWn4PTfPX0Pz/8Jbq2Z5/9DdO3/I+T6cZTc5x9OSlKeST8gsbFqhG5g48+543G9Y3EbyDM=
*/