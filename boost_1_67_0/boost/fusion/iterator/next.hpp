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
+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
*/