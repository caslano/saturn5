/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_TRANSFORM_VIEW_07162005_1037)
#define FUSION_TRANSFORM_VIEW_07162005_1037

#include <boost/fusion/support/config.hpp>
#include <boost/static_assert.hpp>
#include <boost/fusion/support/detail/access.hpp>
#include <boost/fusion/support/is_view.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/view/transform_view/transform_view_iterator.hpp>
#include <boost/fusion/view/transform_view/transform_view_fwd.hpp>
#include <boost/fusion/view/transform_view/detail/begin_impl.hpp>
#include <boost/fusion/view/transform_view/detail/end_impl.hpp>
#include <boost/fusion/view/transform_view/detail/at_impl.hpp>
#include <boost/fusion/view/transform_view/detail/value_at_impl.hpp>
#include <boost/fusion/view/detail/strictest_traversal.hpp>
#include <boost/fusion/container/vector/vector10.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    struct void_;
    struct transform_view_tag;
    struct transform_view2_tag;
    struct fusion_sequence_tag;

    // Binary Version
    template <typename Sequence1, typename Sequence2, typename F>
    struct transform_view : sequence_base<transform_view<Sequence1, Sequence2, F> >
    {
        BOOST_STATIC_ASSERT(result_of::size<Sequence1>::value == result_of::size<Sequence2>::value);
        typedef transform_view2_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef typename traits::category_of<Sequence1>::type category1;
        typedef typename traits::category_of<Sequence2>::type category2;
        typedef typename detail::strictest_traversal<
            fusion::vector2<Sequence1, Sequence2> >::type category;
        typedef typename result_of::begin<Sequence1>::type first1_type;
        typedef typename result_of::begin<Sequence2>::type first2_type;
        typedef typename result_of::end<Sequence1>::type last1_type;
        typedef typename result_of::end<Sequence2>::type last2_type;
        typedef typename result_of::size<Sequence1>::type size;
        typedef Sequence1 sequence1_type;
        typedef Sequence2 sequence2_type;
        typedef F transform_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        transform_view(Sequence1& in_seq1, Sequence2& in_seq2, F const& binop)
            : f(binop)
            , seq1(in_seq1)
            , seq2(in_seq2)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first1_type first1() const { return fusion::begin(seq1); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first2_type first2() const { return fusion::begin(seq2); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last1_type last1() const { return fusion::end(seq1); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last2_type last2() const { return fusion::end(seq2); }

        transform_type f;
        typename mpl::if_<traits::is_view<Sequence1>, Sequence1, Sequence1&>::type seq1;
        typename mpl::if_<traits::is_view<Sequence2>, Sequence2, Sequence2&>::type seq2;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(transform_view& operator= (transform_view const&))
    };

    // Unary Version
    template <typename Sequence, typename F>
#if defined(BOOST_NO_PARTIAL_SPECIALIZATION_IMPLICIT_DEFAULT_ARGS)
    struct transform_view<Sequence, F, void_> : sequence_base<transform_view<Sequence, F, void_> >
#else
    struct transform_view<Sequence, F> : sequence_base<transform_view<Sequence, F> >
#endif
    {
        typedef transform_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;

        typedef typename traits::category_of<Sequence>::type category;
        typedef typename result_of::begin<Sequence>::type first_type;
        typedef typename result_of::end<Sequence>::type last_type;
        typedef typename result_of::size<Sequence>::type size;
        typedef Sequence sequence_type;
        typedef F transform_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        transform_view(Sequence& in_seq, F const& in_f)
            : seq(in_seq)
            , f(in_f)
        {}

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        first_type first() const { return fusion::begin(seq); }
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        last_type last() const { return fusion::end(seq); }
        typename mpl::if_<traits::is_view<Sequence>, Sequence, Sequence&>::type seq;
        transform_type f;

        // silence MSVC warning C4512: assignment operator could not be generated
        BOOST_DELETED_FUNCTION(transform_view& operator= (transform_view const&))
    };
}}

#endif



/* transform_view.hpp
PPV2kkGMYlY6dUdjNGEziBHMxGl7eeo72GhmjkHHu1OtJxvEHWYjdbdsVJcpBlGS2V/fiuVoVrDazOyPJgrKAawZM9vIW3o0/VR4LnDVLNy25Hu0jBnaewsw9t4C6gnWmVmfu10MVJeZBuGrGft5/jC3ZPT3AIClgQ1j9nFC7mOqyyz43IbZn/cH0XwOsBrMvr8d/jWabrZB+DCjv18bTA9WjBn9vdxgJrCezJ6OKU3rdIA1c9HssyGBYyn3uQXj3j87MgEtG8yHxaUMOrKE8ptvENtY3GrPoEuUwwKDiGW2qvufa2k+MDOzhNPfdkbLBKvF7H6CtQ7l/lXBuPMBRV6g2cE6Mluvq14ITdgL9v3+L1vT0axgemY+CyrQOUoDC2bWzs/QguoJ1p1Z4PSQbdSHrw3iDLOhRxqbyBYaRHtmt8q074aWAVaa2ZJ+5YdTH8DqM6P3lGBRiwziGrPNP1S203yLDWImswtukwej5YIlu2hW8/BQC+W3BK9nYNL1LBcsnBm/RkYthWsdM36ts4I5GzNNEZetiNMtcx5nBnO2TjuYszEdCssFc5r7t87NCuZsnRlgZk/Ndl8PO4Rm+aHAWtjnDJAD2Dxm5famh1Hf18NnJa551hFsVuupH9H0Gw2imtCsbGHrXJoPbC0zx5eTtHvqJu25p5P03GNSmBksyEWzp32e5FLumw1iIYtr3u7KSarZFqgZM/5MlAFWnhl/JsoGK+6q2aiLZ3LQbD/CZ+IsLjL6MdVan2EQi5ntnL7mEY2Z4Xwt+v8UHPNW+q+90BySratYex/VenvB+TwvtCTT73CenxmsrWbsvRrMBxbHjD/v6nY6NwtYNDP+LJymsGywEDLpbO5iNZPPJpizOBtYODN+jhyKMcVuA32fTmewUlFVv6B6/gT3AFfNEscOJNPtw70LJu1dPVhlZrzvFrDyzHiP7GCBzPjzdQZYCDOeezZYODOeu36/c7OA8XXyuqSBOZsvUxGnO2AQu13yLBHsG5ca7dBMhwxiObPbYUXHUW8dcC8WmsU86NCY+gfWmFnfNf1rUX6H4awwO1vYfQLFgdXQjH0PMqzziEHMYna/1uhqFAd2iq3zv1NbtEQTxw1iKYvbFBszj+LAOrppVrLkiAtouf81iKksziOwofZe7Rd438Fzn3griGp92iAeMot99aYDmjhrED2YbQj58gGaDWw5s9OFq3+kWp8ziDBm9HM1wexgvZk9Gr3/ONXsvEFkMrP36voHmj4TzgMzfh6iwNoy49eeNLAuzK55FVtH8/0K13lm/S/3HUp1AVvtotnW5fNfoGVfMIghLG5Ij2oRaNaL8LzE4nZMMuyjuEsGsZdZr7R3M2gtWQYxmPW2acfTjdAs1w1igtBsZt+nN9HEDYOoysb8YU2kP/XoJpx3ZudenuhBa7llEG+EZittfnOp1rcN4jGze5vWaPfNPwzie2YxLk97UdydgjZ/zIKf0XLB3jOb/D6a4qLuGURTtk7f0V5/Uh/uG8RPzGa5h75CEw8M4orQbKPjXDrV86FBTGbWwDVcu/+B1XDVrH6VWQ40+xO6LoFJz2Bglcmk6/xfUGtm/NqqB3M2phksnEx6HlRYJpizteieOp/P9NT5mLanzsd0KOJErvP5onKdx1kVlqGwXLBqmrG/FxHm+9sgDjKrnlC+NZr+H4NIZBZt2v8L1RqsKrOFq8adolqD3WDmfvetkdbyDN5XuWr2cHr7vym/VwZRl1n/SQtq5tk9N9Nb7X1jF9d7bm4tXp9BywBrl29dwTafP1kSTf8OrmfM1vt8HIdmB+vOLCHMURZN994gEpgtqrdyH5oVbKuLZsdDvGrRmP/C9ZrFTWw=
*/