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