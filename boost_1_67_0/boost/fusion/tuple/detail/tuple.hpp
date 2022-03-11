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