/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ZIP_VIEW_23012006_0813)
#define FUSION_ZIP_VIEW_23012006_0813

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/sequence_base.hpp>
#include <boost/fusion/support/unused.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/view/detail/strictest_traversal.hpp>
#include <boost/fusion/view/zip_view/detail/begin_impl.hpp>
#include <boost/fusion/view/zip_view/detail/end_impl.hpp>
#include <boost/fusion/view/zip_view/detail/size_impl.hpp>
#include <boost/fusion/view/zip_view/detail/at_impl.hpp>
#include <boost/fusion/view/zip_view/detail/value_at_impl.hpp>
#include <boost/fusion/container/vector/convert.hpp>
#include <boost/fusion/algorithm/query/find_if.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/size.hpp>
#include <boost/fusion/mpl.hpp>
#include <boost/fusion/algorithm/transformation/remove.hpp>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/transform_view.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/find_if.hpp>
#include <boost/mpl/equal_to.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/eval_if.hpp>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>

#include <boost/config.hpp>

namespace boost { namespace fusion {

    namespace detail
    {
        template<typename Sequences>
        struct all_references
            : fusion::result_of::equal_to<typename fusion::result_of::find_if<Sequences, mpl::not_<is_reference<mpl::_> > >::type, typename fusion::result_of::end<Sequences>::type>
        {};

        struct seq_ref_size
        {
            template<typename Params>
            struct result;

            template<typename Seq>
            struct result<seq_ref_size(Seq)>
            {
                static int const high_int = static_cast<int>(
                    (static_cast<unsigned>(~0) >> 1) - 1);

                typedef typename remove_reference<Seq>::type SeqClass;

                typedef typename mpl::eval_if<
                    traits::is_forward<SeqClass>,
                    result_of::size<SeqClass>,
                    mpl::int_<high_int> >::type type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename Seq>
            BOOST_FUSION_GPU_ENABLED
            typename result<seq_ref_size(Seq)>::type
            operator()(Seq&&) const;
#endif
        };

        struct poly_min
        {
            template<typename T>
            struct result;

            template<typename Lhs, typename Rhs>
            struct result<poly_min(Lhs, Rhs)>
            {
                typedef typename remove_reference<Lhs>::type lhs;
                typedef typename remove_reference<Rhs>::type rhs;
                typedef typename mpl::min<lhs, rhs>::type type;
            };

            // never called, but needed for decltype-based result_of (C++0x)
#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES
            template<typename Lhs, typename Rhs>
            BOOST_FUSION_GPU_ENABLED
            typename result<poly_min(Lhs, Rhs)>::type
            operator()(Lhs&&, Rhs&&) const;
#endif
        };

        template<typename Sequences>
        struct min_size
        {
            typedef typename result_of::transform<Sequences, detail::seq_ref_size>::type sizes;
            typedef typename result_of::fold<sizes, typename result_of::front<sizes>::type, detail::poly_min>::type type;
        };
    }

    struct zip_view_tag;
    struct fusion_sequence_tag;

    template<typename Sequences>
    struct zip_view : sequence_base< zip_view<Sequences> >
    {
        typedef typename result_of::remove<Sequences, unused_type const&>::type real_sequences;
        BOOST_MPL_ASSERT((detail::all_references<Sequences>));
        typedef typename detail::strictest_traversal<real_sequences>::type category;
        typedef zip_view_tag fusion_tag;
        typedef fusion_sequence_tag tag; // this gets picked up by MPL
        typedef mpl::true_ is_view;
        typedef typename fusion::result_of::as_vector<Sequences>::type sequences;
        typedef typename detail::min_size<real_sequences>::type size;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        zip_view(
            const Sequences& seqs)
            : sequences_(seqs)
        {}

        sequences sequences_;
    };
}}

#endif

/* zip_view.hpp
mddQU/q9VPm2+cJLEzKfYVhPjEupeus1WRjMXtj7mn61yWJglsJmBy1qRBYPsxD2fUNsUbIkGP0O2u8a/m0rbXwPMt0onjPfLCY/a07mPoprz7co77uTuT7FUg1v/yIrq9ibxk9TuXaYg1hv6YksXi8QZi5s8qP1Q8mClX2OGtt/B2em2LKdIevIDIqFHfL0IouFmYp9PnPumEkWB3MV4863u1yT81T2WcGhxXqyVJiVMPNnae3I0pW9DPi46itZJsxW2Oo5B7PIsmHWwvY/dl5ElqvsZXdeq45kX2HFRH093izks1Qk2lQrKizpW6cqZNYwOe5M7L2VZHqYhVhvcPEN3txbmI2wTU92cY8CYLLvIzpGWXNvYfbCblV4V58sHOYoLHxPqTLcI5idsMaLat4gS4TJPrRpXWs6WbJi1R2mPyBLg8k+XM/NKkmWAfMVFjF3sgW9ZtdGF17TP/Ca3erBTv59OoGwuKCC608z0bRBH0dls50zpfcd+faxysjlZDGw8sI21f34nCxZsTljy3Yjy1Ks702PdWTm543Xa3Q+8QrvBSbHVa3Q+T6ZQbHWbUY9JUtS5pzvNSmT96KMm5qyagPv5YLxuEPavxm8F8W+PGl0lXOBVRO2YN9jriENVkFYq4qjJpDlKLbcrlR7Mn2mqeYnrPOVt1/JgmFy3F+fHySSxSnjZpapUYP3ooy7Mmtped4LTNZg5XhRI/O5aDyubo+NY8lCYXK9nnX/HU+WoIwr6RdQlCwdJtf72Pi3YDLtkvG4Hc7lQ8j8YXK9G/86u5KFq1bvsR1ZkmLtzW7EkGXBfISNvvWQMzO/bGyzhluEkwUotiHlQj3ei2LDelcZSJao2PeFAzzJMhSbfX/iZ7I8xRafbcC1+1wxtt1zVnDWoYpVaHz9d7J4xQ7N+nSPz8sV5ZyVsTCQ5cDkdfTS4ss+Mv1VYyv31P4DWZBiVhNiDpDFwSLzLTjf1kSHVCHTXTM2yyJ1dZwnrKKYc+T1sNJkmYo1qlhpEPf2urH1CLQYRhao2B9JD7zJYhRz3yJ+b6hiEWHjR3Fmij24PciLzD2Ln+PyrYj3rSdkZRUzabv+XzI/xbLX5P4gq6mYbfNBnGd9xR4fbNOdrKliZ0deSSdrrdg/pTZdIQtRzCf3RxZZD8VOuoRbkPVXrMrLX2PJhimW82Eyn5dRivWxD+BcYhUbOKDx32RTFbv0r2MzsjmKrbyT6MjnDCb796TJnhEFttYsE0aviUxN1prVaJRkQpYNsxf25cnx7WR5MEdhbU/ntiDT3TAeN3Wf4QqZD0wn7PbR135kgcq4evWr1iALhbkKW3rmbXuyGGXc3tAdaWQJML0w++r775GlKuMu2t46Tpah7LP8icMhnAvMVphXgz7fyXKVOXta7D1IZn7TeNy9yKAVZHqYjbAmD/S1OTOYnLNHQvkZnBlM9qGz+5w1nBnMQdjW5HU8p0GxGx2dPpPFK+vZzxiSQpak2MDYm33I0hSr98zqD7JMZZ/t/7u3KlkOzEXY9O5nrnNmt/DeUNije4c+cC4w2dvt55fwPoMU+/rxzhuycJiHsB1/jttHlqCMm3TzBI9LhbkJy27iWofrU2z9/d1HyXJhVsI+PT9cjEy7bXzOztSq3IxMD7MTdn1Uo4Zk/jAnYSGdH/6Xa4fJPI+dfzqBa4eVEdZmdyxnlgDzERae+B97snRYKWEzrXP9uH8wV2H6fe8bc//uGNvOHbZFuH8wP2Flr1+cSham2JfcH9PIEmEVhWn9epXiPijr3ax81I/7oFjKtchsMt1/jTPzrBTygbOGyfOiXervQhaqjNu+4uZishiYu7CrHUPHkiXBvIT9ea/mGbI=
*/