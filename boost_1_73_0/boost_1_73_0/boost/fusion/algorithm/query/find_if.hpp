/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_IF_05052005_1108)
#define FUSION_FIND_IF_05052005_1108

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/algorithm/query/detail/find_if.hpp>
#include <boost/fusion/algorithm/query/detail/segmented_find_if.hpp>
#include <boost/fusion/iterator/value_of.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/mpl/bind.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/quote.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename Pred>
        struct find_if
          : mpl::if_<
                traits::is_segmented<Sequence>
              , detail::result_of_segmented_find_if<Sequence, Pred>
              , detail::result_of_find_if<
                    Sequence,
                    mpl::bind1<
                        typename mpl::lambda<Pred>::type
                      , mpl::bind1<mpl::quote1<value_of>, mpl::_1>
                    >
                >
            >::type
        {};
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::find_if<Sequence, Pred>
        >::type
    find_if(Sequence& seq)
    {
        typedef typename result_of::find_if<Sequence, Pred>::filter filter;
        return filter::call(seq);
    }

    template <typename Pred, typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::find_if<Sequence const, Pred>::type const
    find_if(Sequence const& seq)
    {
        typedef typename result_of::find_if<Sequence const, Pred>::filter filter;
        return filter::call(seq);
    }
}}

#endif

/* find_if.hpp
LmdpdGlnbm9yZVVUBQABtkgkYEsuLcopSy3Sy9BLySwu4SouScwt0M0wgjGMuQBQSwMECgAAAAgALWdKUrwyNKHGAgAAsQUAACQACQBjdXJsLW1hc3Rlci9pbmNsdWRlL2N1cmwvTWFrZWZpbGUuYW1VVAUAAbZIJGCtU21v2jAQ/rz8ihPtB5jCS/tp7doJFliLWtGKl1VISJGxD+LhxJHtQJH643cOIFZtE19qRO7iu+eeJ+fz2eePW8EZnFxx+Y9pkfWAZ6N/IXf/To7jN9j9CDQje4KiCUfEW1yDk4g3qJaIeM9x4/04PkEz88L8o+mBs9i7tBOcES7S+dbIZeKgGtXg4urqC9ThsnXZCqHLMokKRg6zOZplCDei3Gkn7PW1YfFbCOiAqUZZaJxIC1Yv3IYZBPKV5JhZFMAsCLTcyDm9yAxcgrCQCiF6ep72B3chbBLJE6qx1QXYRBdKQMLWCAY5yvWuRM6MA70gNNUW0jqqVzipswZRIzg0qaUSnpwpq4GtmVRsTjTMQeJcbq+bTV4YRcqbQnPb5IdPbyQu3X/FlBSkbAs6d+A0FBZD8HkhpFrIhbfUCtrMi7mSNgmPUogoE01twKJSVIpgEu1OMsJo35nQZ0FOaqXzxurMeqZNotN3idRCKrIo
*/