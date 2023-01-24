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
XgXJVc4osKmNzpUZwQQw1vi+Ceoz0RLV6Umlt8n7dEk1s0tUc3nUpdK3GJV8TispRvC8/T0nnSDBw34Ya85/dBcxJvWM4sUBOWx7BXN98UJ0QNnlheR6AiCrxcMytjgpMykD2rZUQdCoKOmL7yFSBm5IYartsyysIycXExQHQZ5M+r0XJj3iDJq9pvm9FOheEEqVDy53wxzMd5aXcmHNNdxnko/TcX0ssH6YDvMcwEtM970sd9ob7KdcTzCGTk9YltofEVR+XXisoTUwUI0kqYwp71tblXzpAC93ejf9hUStiddgNQJA7ST0QD9YX7qHrcfpPho+eBoLw7sXIS6G8ElSvKgwOuyfBFwk9GRUqlW8zztJYUUdMZPEdzxCJe73cZl041VM4dTry1zKiqLT5Esmdj/ZrEzNuUlIP3frmI8nGjmt06En76iH74LiqA+7zPljE/xHnrZuAhk6nABELtfxBug22CA2li5G+OCUrbVBaGC/E5pK84uscJ+PPxBAoODKIp/oUWKdY2pojxm0J8/jc0siPnju8wzI/lDIKGZftRzqAPwYFIfPRk0LZSPq32IcRI5u+r/gTRgpEk8zihaxmCIVDccvrnmfrXLrcMHdc6VIWLUoyuA1pNMTUmXyzubf2KmemHDd9V3OYT5238jEkqVt/fBe7o8Kip9uuLZb4er0wzRwzG1WQyOzHXyeS9VhojN0w/GZhj1A
*/