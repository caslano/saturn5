/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_05052005_1107)
#define FUSION_FIND_05052005_1107

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/fusion/algorithm/query/detail/segmented_find.hpp>
#include <boost/fusion/iterator/key_of.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename T>
        struct find
          : mpl::if_<
                traits::is_segmented<Sequence>
              , detail::result_of_segmented_find<Sequence, T>
              , detail::result_of_find_if<
                    Sequence,
                    is_same<
                        typename mpl::if_<
                            traits::is_associative<Sequence>
                          , key_of<mpl::_1>
                          , value_of<mpl::_1>
                        >::type
                      , T
                    >
                >
            >::type
        {};
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find<Sequence, T>
        >::type const
    find(Sequence& seq)
    {
        typedef typename result_of::find<Sequence, T>::filter filter;
        return filter::call(seq);
    }

    template <typename T, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find<Sequence const, T>::type const
    find(Sequence const& seq)
    {
        typedef typename result_of::find<Sequence const, T>::filter filter;
        return filter::call(seq);
    }
}}

#endif

/* find.hpp
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
*/