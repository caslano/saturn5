/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_BEGIN_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/support/is_segmented.hpp>
#include <boost/fusion/sequence/intrinsic/detail/segmented_end_impl.hpp>
#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;
}}

namespace boost { namespace fusion { namespace detail
{
    struct segmented_begin_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                iterator_range<
                    typename fusion::result_of::begin<Sequence>::type
                  , typename fusion::result_of::end<Sequence>::type
                >
            range_type;

            typedef cons<range_type, Context> type;
            typedef mpl::false_ continue_type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&, Context const& context, segmented_begin_fun)
            {
                return type(range_type(fusion::begin(seq), fusion::end(seq)), context);
            }
        };
    };

    template <typename Sequence, typename Stack, bool IsSegmented = traits::is_segmented<Sequence>::type::value>
    struct segmented_begin_impl_aux
    {
        typedef
            segmented_end_impl<Sequence, Stack>
        end_impl;

        typedef
            segmented_fold_until_impl<
                Sequence
              , typename end_impl::type
              , Stack
              , segmented_begin_fun
            >
        fold_impl;

        typedef typename fold_impl::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, Stack const& stack)
        {
            return fold_impl::call(seq, end_impl::call(seq, stack), stack, segmented_begin_fun());
        }
    };

    template <typename Sequence, typename Stack>
    struct segmented_begin_impl_aux<Sequence, Stack, false>
    {
        typedef typename result_of::begin<Sequence>::type  begin_type;
        typedef typename result_of::end<Sequence>::type    end_type;
        typedef iterator_range<begin_type, end_type>    pair_type;
        typedef cons<pair_type, Stack>                  type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence& seq, Stack stack)
        {
            return type(pair_type(fusion::begin(seq), fusion::end(seq)), stack);
        }
    };

    template <typename Sequence, typename Stack>
    struct segmented_begin_impl
      : segmented_begin_impl_aux<Sequence, Stack>
    {};

}}}

#endif

/* segmented_begin_impl.hpp
7IRinkUFqi2yy964d7FFBtvKi3eRnfaHG5KCebIpxTgHYioTIggy9E0+DC7zvcwrDb5GR6q9iKzs3GUqbjCgyhwkiArKQ5BPvCUvj1HIlwmXnPvzBZ/flsdv0POBKA9mqZfIgKdb2pcHwF6Q1LwMRbEO7E2hduGa81vmQ9rArR2LJFuwxIth70ME59SwA5Noa4EU1iD+hvTv7FNCizyZse+ZnYXLkyY7zrjKpCHuPUwEJSnEb5mGSRZUCIp5LNL78gMY8/lsdWO2FWTsAKLWb7w/G37/Cs6nz3bkYnIympRGXHdw8XfXdWrfqREGE2gbQtRNBxfscDO2RpeDIUT+4GQCu+bn72vfMc0Lci5P3JR7vkii+8ayGTg01GgsnWYjgH8HDojhkeRfT+RY8R1Kh6ciBTf4QD2PIPjxCJGYtiDTyAy+zimfzIW2ueuLBoT2Cs7+PpqPe/Ke7WNIN9lMiAg+i4Q73V3ECd9FXtt9bFsmyHQltSRItjF8TXdKm4skAZDye/QN5SNMHtBa/Wg6zQZp2D5+eZyS1PPBkWYh4JpditIpUJj3zeo+rDSIN2EDAc0kZJOYAzhJ/AhShYoamAdbtShfPy99cQnzHLN/gUZ1ZFZvPqITJAItD6Sw6mVv8UCijTkFcl88IhTI
*/