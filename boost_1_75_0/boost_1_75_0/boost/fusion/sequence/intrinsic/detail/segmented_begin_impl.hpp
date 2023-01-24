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
nWuwziTg+pGXGFyf1dpnpW1egcCPUz3sGzyocN1vgOvIeODo+OwjqpPNsElAE3ZzssdyjN2c6rFsc7JHukqWbVJgcoPJY/kB/iomYUJlYHKjid3WEzMHsE7Bopxq1zqJZJy/whOcXClc5IKVg/9KfkbflaMcOEM5/mRvDkxsD1fCesas2k1dcBsmbKUkezd62W/e7BZ3SLW4mDqaxbeA3nxToNEcdNX7ug7HezmlZAC6/IXwxE3ENlxYH99CyQmsV1+Jx+5wBPbG0zk4+zK7sY9X7uOnHGy4bVWuCuV/Mpm0c2lQWB4LoEy061tE/ofwnLyWu/GRJONxkWqfD2xAKRisW7VdOa0Ci2rvGa0g28D68GkD67kG1okp5DOihFMIqmr3kk4gHPz8jMwbyfjSejfWHyxrwDYuxjbIjU61f9xVQ+qgUP5HeJJ3d1ffwLy7e/r6S5NGDV0wNJdcIS9j3pw8T64NBGj+nNwcf+IYdtdpDFfrf0BiRfupoYHJhqgDzN5M1jH7sX8sZmPiVfvwrkbJKGado5jNMzDLgVqUwxSpbKLiDvbMhPpWavX1QI4hTKzEJ4BbcKKi2r+9BL755DdyHUbnqKnnCNgbHntQPeeegpfd0oGPkMguk0KH492Wf5K30I0HW3sL9djT9E9Lffm4tp5C7zdowQHOeua1Q3/qwI8wv3fNxLThNi8mUBsP0jO73isM/2Kyh/Xs
*/