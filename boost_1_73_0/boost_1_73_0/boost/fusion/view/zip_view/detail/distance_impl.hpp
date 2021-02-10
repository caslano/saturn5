/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DISTANCE_IMPL_20060124_2033)
#define FUSION_DISTANCE_IMPL_20060124_2033

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/value_at.hpp>
#include <boost/type_traits/is_same.hpp>

namespace boost { namespace fusion {

    struct zip_view_iterator_tag;

    struct random_access_iterator_tag;

    namespace detail
    {
        template<typename FoundIt, typename SearchIt>
        struct best_distance
        {
            typedef typename result_of::find_if<
                typename SearchIt::iterators, is_same<traits::category_of<mpl::_>, random_access_iterator_tag> > finder;

            BOOST_MPL_ASSERT_NOT((is_same<typename finder::type, result_of::end<typename SearchIt::iterators> >));

            typedef typename result_of::distance<FoundIt, typename finder::type>::type type;
        };

        template<typename It1, typename It2>
        struct default_distance
            : result_of::distance<
            typename result_of::value_at_c<typename It1::iterators, 0>::type,
            typename result_of::value_at_c<typename It2::iterators, 0>::type>
        {};

        template<typename It1, typename It2>
        struct zip_view_iterator_distance
        {
            typedef typename result_of::find_if<
                typename It1::iterators, is_same<traits::category_of<mpl::_>, random_access_iterator_tag> > finder;
                
            typedef typename mpl::eval_if<
                is_same<typename finder::type, typename result_of::end<typename It1::iterators>::type>,
                detail::default_distance<It1, It2> ,
                detail::best_distance<typename finder::type, It2> >::type type;               
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct distance_impl;

        template<>
        struct distance_impl<zip_view_iterator_tag>
        {
            template<typename It1, typename It2>
            struct apply
                : detail::zip_view_iterator_distance<It1, It2>::type
            {
                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static typename detail::zip_view_iterator_distance<It1, It2>::type
                call(It1 const& /*it1*/, It2 const& /*it2*/)
                {
                    return typename detail::zip_view_iterator_distance<It1, It2>::type();
                }                
            };
        };
    }
}}

#endif

/* distance_impl.hpp
aERaOht4a5ep+rVkJEHyuTS3gS9F6NuG0FEHGihcMW2vIeE2kdQDIG3Dup6WVcXWFT6AluIXYBbTeWflM4Z6gmQlKPHI4YHDdz9v4kkUgrMoUxgBQq/SQx5NWjUcMV3mkC2MueAZTtElzeDOt8buhhR5rniOSa/K8K3yjUrJCaDLBYqtN7QH9Ko55deMzXuEFUfQAfdTiQRErZtRc/Cv7r/JJs6KrySelgdnO+jmOC10Xr3udCczGaq5CslN+LkuCr7/v7V3FDsMqFq+jRMB4neGbHwnIA5Eklxb7K2pTAp16BjJqC6lyNiqg2/U0t1Y83NRLij2ypBAqEjeNwXdIpdrdHf0I/CLx+4vUf8gUCwThicuXCypew3CZSWl70WO2g0U7lkYbtJimz6HInjupFrJR3w5tHcfPl6FsjKcFS7+mx66k9wHLn6xkytNsW9GvSmlaqeNvdvaffO85bvLvR3efc1jwAHR6XBXXL+8KBcl5Dk+Tp0dHn+FdgP1qaBTxPXh8PANlF4grjlkuQ9AjYq4zlcB6gTp+gGue+fEtn5AU5khJWytA9WJ4uY24qYMFaUo7CYH/JtbSUXM1vYIt4flUvT94qDlL7Tmf7i4OWN9Qiu+50Dg3ht12ltt+idMuKrPfqd1/Likaq39
*/