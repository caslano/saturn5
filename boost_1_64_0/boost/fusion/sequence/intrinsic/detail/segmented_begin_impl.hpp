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
wS1KEzHKY3r1WFqtd2KJ45uRnawiR1GnkWu3MOUEvMYUJ8zs+11Cz6E11W3cDK21UZO7ZbweJ1VUd7lqe9Zs9rV4+kzK3K/R5jx3Kdw1UQw8xD/pXgUIFTbXVVuYcwx1V9Fry17gUQ4niqpZsaNEItJPOr7YU7GCI1C4UzQ+YAz3FtovJakKnsSHBL0C8LtgEsAmHFVWERIukNC5zy/wWZ5p7oFvbNlNoK7P7YEbnSgfHGCaWZee0pUVC7BCpLI/HR3F7jaYaQ5rZpJTPhHAeN2cUaTwMCXILwbvbDJc7ff0UaLCFsPi8Tq84foPi+AJ9QXghDVdkIWokk8ipJlFKwpaAUTAR/5ixnfLHyCGNK0g/eauLFqyM2xcBw5mbEvwsl4GHXZvKhEgHpZocHgZHvK68Qx2kQXiaoUoC3hZCm76e58w75AuQjHhXAvSI+JAesUOLBxwUC6VdBBXcAbJPOFUQkUBq9vlDlbRDjxgeb7GGPF+RO0LmSd6ImwpUlxAt8LELfdUhLNyzTQMUYsMpf6+vP/kqjR/Y+vqFt/Guewm2+uIW8WO96M16w==
*/