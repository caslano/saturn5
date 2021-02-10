/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_REVERSE_VIEW_07202005_0836)
#define FUSION_REVERSE_VIEW_07202005_0836

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/view/reverse_view/reverse_view_iterator.hpp>
#include <boost/fusion/view/reverse_view/detail/begin_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/end_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/at_impl.hpp>
#include <boost/fusion/view/reverse_view/detail/value_at_impl.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/static_assert.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace fusion
{
    struct reverse_view_tag;
    struct fusion_sequence_tag;

    template <typename Sequence>
    struct reverse_view : sequence_base<reverse_view<Sequence> >
    {
        typedef reverse_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef Sequence seq_type;
        typedef typename traits::category_of<Sequence>::type category;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef typename result_of::size<Sequence>::type size;

        BOOST_STATIC_ASSERT((
            is_base_of<
                bidirectional_traversal_tag
              , typename traits::category_of<first_type>::type>::value));

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        reverse_view(Sequence& in_seq)
            : seq(in_seq)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(reverse_view& operator= (reverse_view const&))
    };
}}

#endif



/* reverse_view.hpp
rFXQgLXkaBfmODbjtbQ43vC3L1muCUtmR0q0m7GseWQpJ0ZbY7uUZqidIHQmSRb2zZxdINJs3jIAh+CAHQr37EjdpsgMyjjbHL1P8bqg4MguB8OhGvQ8XTI7Y+ZHjtln9TXAnNa8NmpbC0fr1VaRB0aR6HFOi63t8vY36fy2DvzNAddbXLRG+iECv7YwgAEUsLamGmwwUd5pJuTGTXBZ1rDAbEOIb5fLk6oEA2Ig5pgTQHH6KnGXZiIyNdvaLGDsG3DdcP7kAQxXPXvjZbdTW7y29Ygz5LItHtA2wnyJ8xhWAnAfNRM0Swty7F3zymCUBdsB5GNrTWu9WDIuPYwkG/v3V2fHb6ZvT07P+tfBMvg2gEfXzpGuvSDqoxjfAri2LjH4aqENgVjzHiKhhStxOPXACadlLkkKKaIlXAkCwIXQYezPDAjMdIyViuFRoqh5IsI6o7aQ7snB0+/AQ6MFDxJFFHUi4jZPbPngRg8iF1rNSSYAax9LuifgC7SYZ4l4ze49gwiMMgmaBfU5BmQHZgTNnsprXaevO7NfYhzFeI1BohoXG+fzPG1FIrdSC4cKDMFL2U8CZB/UHhhbtwXY27N46gZm6BcX5uG2Rm6OwxWw8NfG4nM9mlpoSD45JX2wKOTNKqHNBPCIdsQQ
*/