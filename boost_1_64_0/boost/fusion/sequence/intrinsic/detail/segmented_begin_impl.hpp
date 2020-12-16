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
SVOMTi1DcsBbOADIOQz75g3aGPE9YEu4tTEHE47WWXfiQJ6Z1+eGNoamrdHYyxbWSl+D3295l42109gYbX2jFp6ms0Hc8ywcSWmj45/deADOyEv6jk7MSv8UTpRa3t6bdGCbJQDrdr4TA05OvUaJiWNyogMnlwtIx4W4Z3Ti7Ph1f+rEiUMJYmAt6MT058z9k4UhKbsRl9+sjeuT/oe5GW3cwPa9cHMLa7VvfAsL09m+X7ZxtH3RhsLCdbbvvltZOKt9P2tjrPZ99K1tjG5fvU/6ucD9B99j5dM1Yfp0nVoRlTo0aayfj/6guX6WLM+jKuJV/N+un6HSlRB5sfDrLVO3SllQH7ymFrY2pJUftKKOuTxVq4sN367LH6R3A64XBH4MAmfgDcCwri9jRs/hIXVSnZt66tz145YMPw/LMixSdsyMw4vOnUoCxo8Z/xD1n668UIRYqZg7B3wb8tpg6mRzFzAlXq85AtfHTIZtcpjI8ZhfhqEXZ1G7TdSRRbZGfelh6uof/SGqb81Tp+JRuzqyv+j2mFP1OEPqkbOEV0GWFiEr4Bwzd6onfAJPgQwzNrFuaf0+l4iciBWx51RZnrLprfXeBljyrImT5QoVKuNMm+/z4w+17iDcoop57IsXsvnxfdZlPaAiNMa1VxapX6UOM6IONKPaeA315Y0+u5/IcVkYhwnISdrfB4aluBrBz1O3siHneKs+QRKmee6XbTl45DQkMSMO2NlL1Caj5CkP0yJvotFMLjTxRv7t/1RbaT34JXJXVgWluBqBUV4zHFqWHEfEOfvJk3juFnea9Rn9LvUz3KKfUOf5xzfPxbwintbYJzbPcGABQfuwievQETh0ij0QPTfrfLPDAmPUQGDpvk7bTo0QLLmtxryJnZgVEpt2c7QLg0c03AfvG2vj6N7rvEUXa6QcnEZ5EztsnN7n6vLOtnHS6AzvPiw6XWtx/dlp4fD2/5Bqy+t1YpbX6hC7vfml+mPCcFxqzpoYw9nik4Zs2H7Gtx3vwNKuovNGX78Li10QZV7pwsnjs+xaiN28wb/BNjMNYsdv+G+wj+3R97Kw9vnmvmgD/B+ws+KUNkTy6Nt4HHKIG7uxgZOKaPMe7KDaP5g4mfR5dUaIezzM+fpTm34gD5wAHq0rxvP5x+rn8K3pN9R+GzdVdPxuSBu6maLhu+j8vjUNlgC8nIJ+LzVDqAO+ucSQm0YEYt0v3kLg6s0P0SHvuyU8t2IU2bmPn2fh7BzBUBjBDMoRfM7C2TmCd9+aYrTvrd4Dvg4xeBc4UF89vtvCduqhXypx9N7Qbo8/deCkLOwXZ24jMFTjat79XCV0UoyOaXxbioEm1/dChIbFI92/HaGr5sPyL0s6vbekPuD89hJjxwHSd7zdGCwPx8EdEGfdSX6K0Ow7yfiOBl1Kvpmkfb6mNT0b7UvvJJ7JO2eimdVlvp9iUOuKd8h7DLq8RJSrGL775p0Rg/ONXsK0rKG7mjh9ljXj1f6YYKQBmZ5T+ma/+PZeEwvzsWlPfHdJwzMUzKUgZFP0MGM/9MX3mr5ObuQXrlvFLGq0qLjZHA6Vf5CJdwvme4nIeFggx5SYO2HXuraACss+itHljr/P1MNWYRklhV8wDH4nOaYUfreJP5wGwOBknD200cNiAVNoCwp4kmsnyt0sKBJmRsN5PGhjNTfWjZGyysQJeVhihCB8lw3VJtzE+y7LnDQtykrYmcESsgZbuycCX30usjKfMMP//Nz7WmdGxw+qKGOb0LT9xs1Fbt7heLGytLmppIJMU86niJyEZWXEwyLhbHMRttrCGkCwnFASFufgTFCT6uQoOufN1VZ9uJcEThRnjZyZaefIYcFZH0Q=
*/