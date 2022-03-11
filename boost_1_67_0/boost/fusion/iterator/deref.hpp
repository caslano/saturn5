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