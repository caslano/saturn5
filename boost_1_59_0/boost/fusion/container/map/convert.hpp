/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_MAIN_09232005_1340)
#define FUSION_CONVERT_MAIN_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename It, bool is_assoc>
    struct pair_from
    {
        typedef typename result_of::value_of<It>::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type call(It const& it)
        {
            return *it;
        }
    };

    template <typename It>
    struct pair_from<It, true>
    {
        typedef typename result_of::key_of<It>::type key_type;
        typedef typename result_of::value_of_data<It>::type data_type;
        typedef typename fusion::pair<key_type, data_type> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type call(It const& it)
        {
            return type(deref_data(it));
        }
    };
}}}

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/convert.hpp>

#else
///////////////////////////////////////////////////////////////////////////////
// C++11 variadic implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/map/detail/build_map.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_map :
            detail::build_map<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
              , is_base_of<
                    associative_tag
                  , typename traits::category_of<Sequence>::type>::value
            >
        {
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence>::type
    as_map(Sequence& seq)
    {
        typedef result_of::as_map<Sequence> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence const>::type
    as_map(Sequence const& seq)
    {
        typedef result_of::as_map<Sequence const> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<map_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    result_of::as_map<Sequence>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    typedef result_of::as_map<Sequence> gen;
                    return gen::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif
#endif


/* convert.hpp
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
*/