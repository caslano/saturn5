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
SCRgrVHRattAEHzXVwzJS1IUK81TU9JSNXZbEWIHSyE1BMRZt46uSHfi7mQnkI/PnuwQCi1+yQppT8vOzN7s4Yf3i+gQe6Mc3pKDcwDcWPOHKv/v5rJ8xvZh0D3nPRIJ3hDP5TH2Ip5xNCDKncZFOJflHpn7MFj4JAF4X4YjV6JDxl2a7smqh9rj6PIYH8/PP+EEZ6dnpzHGQitqkHvSS7IPMS7kUPlWi8fHkaOvMchDNKOBqKiVgzMrvxGWwOdGVaQdSQgHSa6yask/SsPXhJVqCJezm0U2/RljU6uqZo4n08PVpm8karEmWKpIrbcUnbAeZsVo5pbKeebrvTJ6xNIET7Z1TBHEReMMxFqoRixZRnjU3nfuc5JUvW148kSayiXV69VHtW93t1jwBK14guk8vEHvKEboi9EaqVYhsxVc7Pplo1wdv43CQlomxsJR0zAVwxS57ciEfOdMHLrQ8bTKh+SMdkFpU5v2r0a2kElWvdUswxZwjzRscIxeS7JD73DpV4Wdm4O1/1nJ26wSRvMkOEhzZPkBlsIpF+MuK37NbgvcpfN5Oi0WmP1AOl0w11U2HfO+FStZ0GNnybGyhWq7RpEcBN8vovz2+zib5/iCsLIomvwu5mk5zvKCS/NJOr6ejFoZReltMbtO
*/