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
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
*/