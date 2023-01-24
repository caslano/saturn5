/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_PREV_IMPL_13122005_2110)
#define FUSION_PREV_IMPL_13122005_2110

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/prior.hpp>

namespace boost { namespace fusion 
{
    struct transform_view_iterator_tag;
    struct transform_view_iterator2_tag;

    template<typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template<typename Tag>
        struct prior_impl;

        // Unary Version
        template<>
        struct prior_impl<transform_view_iterator_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first_type first_type;
                typedef typename result_of::prior<first_type>::type prior_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator<prior_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first), i.f);
                }
            };
        };

        // Binary Version
        template<>
        struct prior_impl<transform_view_iterator2_tag>
        {
            template<typename Iterator>
            struct apply
            {
                typedef typename Iterator::first1_type first1_type;
                typedef typename Iterator::first2_type first2_type;
                typedef typename result_of::prior<first1_type>::type prior1_type;
                typedef typename result_of::prior<first2_type>::type prior2_type;
                typedef typename Iterator::transform_type transform_type;
                typedef transform_view_iterator2<prior1_type, prior2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Iterator const& i)
                {
                    return type(fusion::prior(i.first1), fusion::prior(i.first2), i.f);
                }
            };
        };
    }
}}

#endif

/* prior_impl.hpp
vetw2vv8OSsEhp5aHrOd4SlCjny9Tf6TEbWwHvH+jEmtZV18TsloVnHPh8LbhaGZLk76NdpDPuOpudN4QcSrdNVf8e2dYr1SEeOZAbKnahYK7jS5C9hgsEd7kv1cj5hzUF6PfrrtTr+AthniduT9YJQA79Be9MEUZOAnRZB0G8zh+JL8Xy/5nF+nu5a4urnov1XRkxlZ0Ei2l9Vh32bF+712vdGtpx6T6yswwaO8IDJyxit3YT5VfBoqZZ7tN0vPVRf56H00vhi02aT9WBTPdOFpN2Q90EechJz/rwvji6cjdvZdaI7IlbrEpvVgdmTWTqlMmdfrg34SKoDopiHzJwdZtTXMtoDOxoeg12C73DdPRwQpcpMNdP9lIy9jC1f660M7UAllWs8pHx11bUzSIMRzrnyPcWLGqEaCZ+wUwdH12l6el8xuoacsMn8StKr5gujfB68MBxfsJTl/Uy/Pmvveyr6dnS9GvVDPuOkst/JtJumE6/PCzzzEOX/GfOZb1GF8xJBlaydFstjyOdMHZMPo8yWDVsc5P2AL819NsgbuL63lq+/B7LN8PaKdUb4U6CHXA+hBGJQvhT2kVr4G+wbuJ18PVglyTjf55o3Os7sMzCcDPh70LrZxjSsfI9qbKJGKhJlqiL2XcD8dnej4RiAWG93XKluP94rGNb9ef+gXnzpQTHTfgqAD00Y39ZCt517ePgb5UqVONn0H
*/