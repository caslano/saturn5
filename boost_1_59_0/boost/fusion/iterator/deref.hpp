/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_DEREF_05042005_1019)
#define FUSION_DEREF_05042005_1019

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
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
        struct deref_impl
        {
            template <typename Iterator>
            struct apply {};
        };

        template <>
        struct deref_impl<iterator_facade_tag>
        {
            template <typename Iterator>
            struct apply : Iterator::template deref<Iterator> {};
       };

        template <>
        struct deref_impl<boost_array_iterator_tag>;

        template <>
        struct deref_impl<mpl_iterator_tag>;

        template <>
        struct deref_impl<std_pair_iterator_tag>;
    }

    namespace result_of
    {
        template <typename Iterator>
        struct deref
            : extension::deref_impl<typename detail::tag_of<Iterator>::type>::
                template apply<Iterator>
        {};
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref<Iterator>::type
    deref(Iterator const& i)
    {
        typedef result_of::deref<Iterator> deref_meta;
        return deref_meta::call(i);
    }

    template <typename Iterator>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::deref<Iterator>::type
    operator*(iterator_base<Iterator> const& i)
    {
        return fusion::deref(i.cast());
    }
}}

#endif

/* deref.hpp
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
*/