/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_NEXT_05042005_1101)
#define FUSION_NEXT_05042005_1101

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
        struct next_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct next_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template next<Iterator> {};
        };

        template <>
        struct next_impl<boost_array_iterator_tag>;

        template <>
        struct next_impl<mpl_iterator_tag>;

        template <>
        struct next_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct next
            : extension::next_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::next<Iterator>::type const
    next(Iterator const& i)
    {
        return result_of::next<Iterator>::call(i);
    }
}}

#endif

/* next.hpp
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
*/