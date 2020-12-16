/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_VALUE_AT_05052005_0229)
#define FUSION_VALUE_AT_05052005_0229

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/less.hpp>
#include <boost/mpl/empty_base.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/tag_of.hpp>
#include <boost/fusion/support/category_of.hpp>

namespace boost { namespace fusion
{
    // Special tags:
    struct sequence_facade_tag;
    struct boost_tuple_tag; // boost::tuples::tuple tag
    struct boost_array_tag; // boost::array tag
    struct mpl_sequence_tag; // mpl sequence tag
    struct std_pair_tag; // std::pair tag

    namespace extension
    {
        template <typename Tag>
        struct value_at_impl
        {
            template <typename Sequence, typename N>
            struct apply;
        };

        template <>
        struct value_at_impl<sequence_facade_tag>
        {
            template <typename Sequence, typename N>
            struct apply : Sequence::template value_at<Sequence, N> {};
        };

        template <>
        struct value_at_impl<boost_tuple_tag>;

        template <>
        struct value_at_impl<boost_array_tag>;

        template <>
        struct value_at_impl<mpl_sequence_tag>;

        template <>
        struct value_at_impl<std_pair_tag>;
    }

    namespace detail
    {
        template <typename Sequence, typename N, typename Tag>
        struct value_at_impl
            : mpl::if_<
                  mpl::or_<
                      mpl::less<N, typename extension::size_impl<Tag>::template apply<Sequence>::type>
                    , traits::is_unbounded<Sequence>
                  >
                , typename extension::value_at_impl<Tag>::template apply<Sequence, N>
                , mpl::empty_base
              >::type
        {};
    }

    namespace result_of
    {
        template <typename Sequence, typename N>
        struct value_at
            : detail::value_at_impl<Sequence, N, typename detail::tag_of<Sequence>::type>
        {};

        template <typename Sequence, int N>
        struct value_at_c
            : fusion::result_of::value_at<Sequence, mpl::int_<N> >
        {};
    }
}}

#endif


/* value_at.hpp
fJ22/QS25Zfh55YjxJkR2I17zWGk24bToj0VbsTGIQb3XgRjitF5psYExvRO0XeCkzuAht8sKcOq+ajod2jRcelAzOTONgaXDJzjD5NvE7I884syzKv6u6NRxsmNtZWmE0gbjzlpu1XHE72jWsvHdR8QaXU3D00uXXdwqFL9YJGUlbEo9YsorJz/th9g7oIv0ViXwo4/zxJjU30YFo9J/KcyjXTVueJLdM4PeJiFeab55wcKwb7IdF+EBsGuWPfFnwLdfZjQtDd24KLMm8Hzv+rnsTMd1/n573tIPTP89IW+gvRXcfYU5Wgd0eSwwNg6ovfXz00PK923rowADfpdXeN6iqr7DdJnRjW9LlIq6zAHqUUX7LpObEzQlXuSfu7vEM8FVnDqvvyx+nmHc9KQ5t0/LjBw+9yw4t7ogngu+rjZ0NQfGvWrNg6GlCHrTCcGhxXKmrhBF476Tp/vxNAceHtviBjsDG0/5Xd0YKQPMtZ77y4b0+Vf/P5OHPUvfuCNbEzbv/qzAvMf/KvzG9sYJUfMFyOAefQz7gSxkB6/uLSxvL62tjx7QnjJG/r3S/Bz85GHxsnRnFeVjq3z5GHyfNZdkql3jHVzYpRiwiVIx2menccoPVldIuvucouuCrgZjPvPiDXok2Lu8LYF9gYwfvfA/7cON3+/q/j7oUmU9Xkx7kfs97yLul9+kZhDZBJMKAncPR4704pn+446Zq3CLPVBxbd1ammhnk8WoD7HEpk9U9bnwfWzZr55ZEMvgpm48oFu7j1uMgKUYzNJLsyy4ALh8Wb+6+EOurTMMu9vhz5J7zdTz89Cv4xZBXM5VBftSYWFpbiZrNOjnpybb3YRuIfYb+whTs4viygOmaIdNmm9NQj1qGmM0IT9o6bFJu3kMnR2TeMmDaafviFzaNygiTXJoO0x+da3aj61F79i0MQiuLC0JuKrrkC0udMn693bSXjfpv9ffezNof/j81non7O3krT1VUGTFHiOddb1ai5PlodmVT/64oimRb3N6c2FuM6rAqTTqn6cYoLV00tg2bcCq8BD5jaWRKd7KPbLrw8TrAf717XlXgFmpkNzCnPFwByFHiJBDpAQ8+NuzENNzHGjXtO0LG2//kmyXidVHoRJXLKH1Oa6teHyETD9Ny9bN9HngvRRRzgnJGmcxcBMzN7VmeNZql4G3wEPjiu8jAuh4ROwSvzi4ld90CrFr2n8VWfjmxW/Hip+JQipdWMHkXpM/JoRv0Lx67D4Jauvcxnufrd5L1NWYeJ4vsuUk8pe9X3Pmu95/6jysiDgIpz5KmQd29ugFfalJvYQ9yovL0MusEurElrHpstg/hiGGQRyBh+tCpG9Vj8fqZ8/JDiahA8zn4/Wz90KvpFTivlPPh8Tz+u9qH62o34G9p/V0Tpm6oUp4Z8nZPTnTkMnV/G+7yK+YxPve/MJs2sbQMHnPj6HxVHinwxvGeNzyOJqPOdaztamfL4pvnf9fKk/OzcLxCa+q5g/d9dz9NbSrNyfArSmLR8A/X3DAxspOSTl/u/mEBsJNv6b8unsZvO8LgceganA2srS/GxjHwLP3wHlwFcop6HR4Jjm+OrvXgW7hypvytRr4I3F3CznWPNc8eWaVk+gs/PNQNI5gkcErTe/uIYknXt+VNBW1yhVy31dTRcNgFTcnz15TNBg0yG/F+7bdtTPYd4FgmmLVD8XawouKFiPH+9s0eDbQYB85PWvj/TNJUiEvWrsMa9K2nxTHPLM3EA8fzyoUHpYYKn0QZ9o5QLJozzLrv3ebGsJftgQjqvDprxDSeCERQmrYbBaq0DpGGQmdopXYZxFQcWEQ4LCYq6C2MTmTChmkjBNRZqFeUg=
*/