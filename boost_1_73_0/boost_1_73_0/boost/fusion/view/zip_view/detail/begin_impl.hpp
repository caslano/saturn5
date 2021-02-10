/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_BEGIN_IMPL_20060123_2147)
#define FUSION_BEGIN_IMPL_20060123_2147

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/view/zip_view/zip_view_iterator_fwd.hpp>
#include <boost/fusion/algorithm/transformation/transform.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/type_traits/is_reference.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/support/unused.hpp>

namespace boost { namespace fusion {

    struct zip_view_tag;

    namespace detail
    {
        struct poly_begin
        {
            template<typename T>
            struct result;

            template<typename SeqRef>
            struct result<poly_begin(SeqRef)>
                : mpl::eval_if<is_same<SeqRef, unused_type const&>,
                               mpl::identity<unused_type>,
                               result_of::begin<typename remove_reference<SeqRef>::type> >
            {
                BOOST_MPL_ASSERT((is_reference<SeqRef>));
            };

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_begin(Seq&)>::type
            operator()(Seq& seq) const
            {
                return fusion::begin(seq);
            }

            template<typename Seq>
            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            typename result<poly_begin(Seq const&)>::type
            operator()(Seq const& seq) const
            {
                return fusion::begin(seq);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            unused_type operator()(unused_type const&) const
            {
                return unused_type();
            }
        };
    }

    namespace extension
    {
        template<typename Tag>
        struct begin_impl;

        template<>
        struct begin_impl<zip_view_tag>
        {
            template<typename Sequence>
            struct apply
            {
                typedef zip_view_iterator<
                    typename result_of::transform<typename Sequence::sequences, detail::poly_begin>::type,
                    typename Sequence::category> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& sequence)
                {
                    return type(
                        fusion::transform(sequence.sequences_, detail::poly_begin()));
                }
            };


            
        };
    }
}}

#endif

/* begin_impl.hpp
dmHGyarD9lHPITlrPbq4Dqbjf45qPGVXNNtLGy6MdkuBrsyiKDcTlk1lJu4Aw0SiOkNQX1pBB3qxvQStdP5W5LpMHTKJXbti8wIyO2K/preUon9imEHvxwR4DBL4/j8KLA1b8B0rszG+4d6AHzlSOx4Y7M+w7fbGuZ+mOoE6iJvxZPyT7zQrtTmfdyPjQ7jV3k38DifAfZtdzvIW+mudJFsEOvedveNZFJFPo/CwihxXF2GM8a5LC63JLBFNtj2vrlscKlV7acjSwE7nitFkePHtyM243BObSVxZyJYW5Udi+D/Uy8zW6pUqYnf88CyYjKARj3HIdYuuvX1kiT2iG3jLDslswC1FmOvK0dyMw12OkC2PuBRlMveDEl/e6hCxaRBXiOVAh0gmRn4EeARPffy8Uml56+k5vPq/jpge63w2Pj8fTUYXp6Pqivr+4LKGmsiIgeyLHlzD8LFI1Cyk4/5x/8sTrl3pgj3I0SfRziudc9u/AiYknP7C42HJ+Ldz6azCcjT8dji+8HMAWqgb7PShzGr6ePaEOKj7dJVLsNpcdY0F7LepXqUcTR4aXUz7IML9StS4k2uE4tKFVAWRYLPiuQrf5tErmRLXN0Eztai2s4Q64UFLzbU6sEH9Qi2lqQVwmvHsk5NmydXH
*/