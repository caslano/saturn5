/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_REPETITIVE_VIEW_ITERATOR_HPP_INCLUDED
#define BOOST_FUSION_REPETITIVE_VIEW_ITERATOR_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/iterator_base.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/view/repetitive_view/detail/deref_impl.hpp>
#include <boost/fusion/view/repetitive_view/detail/next_impl.hpp>
#include <boost/fusion/view/repetitive_view/detail/value_of_impl.hpp>

namespace boost { namespace fusion
{
    struct repetitive_view_iterator_tag;

    template<typename Sequence, typename Pos =
        typename result_of::begin<Sequence>::type>
    struct repetitive_view_iterator
        : iterator_base< repetitive_view_iterator<Sequence,Pos> >
    {
        typedef repetitive_view_iterator_tag fusion_tag;

        typedef Sequence sequence_type;
        typedef typename convert_iterator<Pos>::type pos_type;
        typedef typename convert_iterator<typename result_of::begin<Sequence>::type>::type first_type;
        typedef typename convert_iterator<typename result_of::end<Sequence>::type>::type end_type;
        typedef single_pass_traversal_tag category;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        explicit repetitive_view_iterator(Sequence& in_seq)
            : seq(in_seq), pos(begin(in_seq)) {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        repetitive_view_iterator(Sequence& in_seq, pos_type const& in_pos)
            : seq(in_seq), pos(in_pos) {}

        Sequence& seq;
        pos_type pos;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(repetitive_view_iterator& operator= (repetitive_view_iterator const&))
    };
}}

#ifdef BOOST_FUSION_WORKAROUND_FOR_LWG_2408
namespace std
{
    template <typename Sequence, typename Pos>
    struct iterator_traits< ::boost::fusion::repetitive_view_iterator<Sequence, Pos> >
    { };
}
#endif

#endif


/* repetitive_view_iterator.hpp
Z7tr7SS/GnZwRbsmgVY7Tn0jkrX0j2c1mmsuWipzxeRe5dz9Xbe4ECOTzKsBvChzb8wpVwPT4Iihy34quJ0r+oISGrh9keUMV0ji5JHCgquaoBZDwy5tbiJeIOe8CLGvmYi8vnpTFdVuU/RI+TWmzNhKxoOIjFCOK1IdFluH7ItSUw4Kn7J3sZryfHsIOVn58LIKfsJLxlJY/eSp1kf0El/5P96INlP5gnamWn/ePnqrZ7gTsL3I/RyzTMI6aNQhbFS2Kcr1rxA0xC7SdPBVHezXeczx9pBP1CxALeRHj5zx2s/G5/2zBEhCpRupoU8I97HyyeP/YkSUu7HRJOlFqh+0cPqvgFP6pCiv4xJ+qPx1iRuDh7mR+8WudeNifW2M2ryNss+BYWFlZuVRKQl5tBKLlF3v5otJEg2AmyrcD+jSF+RTygWmw2lPHxgPjxZZPk1jJYF7D1isiQLVzOe2MnsW/aUrPtU2iu+0eSirrEbovQ2+ZB6IDWhXLUBNm+7G6gvLJ26gZSI4WCTAMRTSp8LXiVB1CQ5uaht682e7ec5DZi+W4sshH9pjkw==
*/