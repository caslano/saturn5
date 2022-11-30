/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TUPLE_10032005_0810)
#define FUSION_TUPLE_10032005_0810

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/detail/tuple_fwd.hpp>
#include <boost/fusion/container/vector/vector.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/fusion/sequence/intrinsic/at.hpp>
#include <boost/fusion/sequence/comparison.hpp>
#include <boost/fusion/sequence/io.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/config/no_tr1/utility.hpp>

#if !defined(BOOST_FUSION_DONT_USE_PREPROCESSED_FILES)
#include <boost/fusion/tuple/detail/preprocessed/tuple.hpp>
#else
#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/tuple" FUSION_MAX_VECTOR_SIZE_STR ".hpp")
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
    template <BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, typename T)>
    struct tuple : vector<BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, T)>
    {
        typedef vector<
            BOOST_PP_ENUM_PARAMS(FUSION_MAX_VECTOR_SIZE, T)>
        base_type;

        BOOST_FUSION_GPU_ENABLED tuple()
            : base_type() {}

        BOOST_FUSION_GPU_ENABLED tuple(tuple const& rhs)
            : base_type(static_cast<base_type const&>(rhs)) {}

        template <typename U1, typename U2>
        BOOST_FUSION_GPU_ENABLED
        tuple(std::pair<U1, U2> const& rhs)
            : base_type(rhs) {}

        #include <boost/fusion/tuple/detail/tuple_expand.hpp>

        template <typename T>
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(T const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }

        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(tuple const& rhs)
        {
            base_type::operator=(static_cast<base_type const&>(rhs));
            return *this;
        }

        template <typename U1, typename U2>
        BOOST_FUSION_GPU_ENABLED
        tuple& operator=(std::pair<U1, U2> const& rhs)
        {
            base_type::operator=(rhs);
            return *this;
        }
    };

    template <typename Tuple>
    struct tuple_size : result_of::size<Tuple> {};

    template <int N, typename Tuple>
    struct tuple_element : result_of::value_at_c<Tuple, N> {};

    template <int N, typename Tuple>
    BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Tuple>
          , result_of::at_c<Tuple, N>
        >::type
    get(Tuple& tup)
    {
        return at_c<N>(tup);
    }

    template <int N, typename Tuple>
    BOOST_FUSION_GPU_ENABLED
    inline typename result_of::at_c<Tuple const, N>::type
    get(Tuple const& tup)
    {
        return at_c<N>(tup);
    }
}}

#if defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif // BOOST_FUSION_DONT_USE_PREPROCESSED_FILES

#endif


/* tuple.hpp
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
*/