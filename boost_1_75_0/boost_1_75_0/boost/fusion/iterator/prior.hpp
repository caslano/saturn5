/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PRIOR_05042005_1144)
#define FUSION_PRIOR_05042005_1144

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/tag_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct iterator_facade_tag; // iterator facade tag
    struct boost_array_iterator_tag; // boost::array iterator tag
    struct mpl_iterator_tag; // mpl sequence iterator tag
    struct std_pair_iterator_tag; // std::pair iterator tag

    namespace extension
    {
        template <typename Tag>
        struct prior_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct prior_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template prior<Iterator> {};
        };

        template <>
        struct prior_impl<boost_array_iterator_tag>;

        template <>
        struct prior_impl<mpl_iterator_tag>;

        template <>
        struct prior_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct prior
            : extension::prior_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::prior<Iterator>::type const
    prior(Iterator const& i)
    {
        return result_of::prior<Iterator>::call(i);
    }
}}

#endif

/* prior.hpp
EOYqeeHB1XCOTuotj9ewtK9695p0/g0ToHLJOHkhrP10TzqtiwvpS3LVISAGNOD0MZWFAyXp4ZIkhGgI1abDUOTXRiWCo7DdOsRiEtncEz22Y3nYI8m+t1Bz200OtaTLjsZAL3K1qzOHVPOaZPWzk7TM1P6EfBPDhAh9hcH2oYp2U2AgES5VfRHaHs2AGXJ1NjCJB6woMYV2FNTHxUwbtFFuoKW64NuQw7x6kjIrSd3GiAYFSlESnUgkHRJeHXiONuk/b03Hs2CgL7fPiu1LQ4OJ86TJZGTsjvdJxxz00K9I8k/x0S67l3SSOE1OfUIbidlwbnPvQsSB9C5s8ilnPbC0oenJx/shMSxxb0R3KZEenNXMrZcY9AdDeSJ9fy47Di5BlE7oTvXx1T28a9tpnG3RbvCVhrg79FjNO2syRV+kAYMFOm5iQrx5jHbJt2EDlA9oaqJ7ZWCyvPZ7Msb0JOOQclAddAsMxigyXFQNQNsQ2mKGcGK8Wdw4kPhRTc+WIfW1VpNQguMyNMgI7Xhtwo+145AN2/E9teMYtmM85Vf5+wBO6hkYqZBF6zOCbKmAPbRHZLIZRhUdWO6qgWPBHvRiU3+XQhrNQYKW9XG6eHj9TyawOeV6/PzRHPQwGT1oiFXlhSibwpSE4XVU/LC6j5qJ+ccQSokw9HCOgVTfG7sJo6Gt9ohF55FxrAZPpMDj99UXzpBrQLgCdsYU
*/