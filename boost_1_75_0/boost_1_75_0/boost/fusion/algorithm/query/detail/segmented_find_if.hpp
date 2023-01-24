/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FIND_IF_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FIND_IF_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/fusion/algorithm/query/find_if_fwd.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/segmented_fold_until.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Pred>
    struct segmented_find_if_fun
    {
        template <typename Sequence, typename State, typename Context>
        struct apply
        {
            typedef
                typename result_of::find_if<Sequence, Pred>::type
            iterator_type;

            typedef
                typename result_of::equal_to<
                    iterator_type
                  , typename result_of::end<Sequence>::type
                >::type
            continue_type;

            typedef
                typename mpl::eval_if<
                    continue_type
                  , mpl::identity<State>
                  , result_of::make_segmented_iterator<
                        iterator_type
                      , Context
                    >
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq, State const&state, Context const& context, segmented_find_if_fun)
            {
                return call_impl(seq, state, context, continue_type());
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call_impl(Sequence&, State const&state, Context const&, mpl::true_)
            {
                return state;
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call_impl(Sequence& seq, State const&, Context const& context, mpl::false_)
            {
                return fusion::make_segmented_iterator(fusion::find_if<Pred>(seq), context);
            }
        };
    };

    template <typename Sequence, typename Pred>
    struct result_of_segmented_find_if
    {
        struct filter
        {
            typedef
                typename result_of::segmented_fold_until<
                    Sequence
                  , typename result_of::end<Sequence>::type
                  , segmented_find_if_fun<Pred>
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type call(Sequence& seq)
            {
                return fusion::segmented_fold_until(
                    seq
                  , fusion::end(seq)
                  , segmented_find_if_fun<Pred>());
            }
        };

        typedef typename filter::type type;
    };
}}}

#endif

/* segmented_find_if.hpp
aKvLwNZfJJx58lnNT2qcybDpzFIFRRxu/S7WvE6ebtypLr04ymkGuoHy3aydQhrMGja3oQUQyKN3yvvjjLCb+iztR0Jr0brKixTcjI0jBMY+oJeP6mTSVmfYEvBAMA34A8cr3fQw1H1f6SbDUEuHx4jAhzQgi2DVRVyNkkU4qKGqxKB90jOkf5EO/d0XS1TXbiTaGsWR998f4Pi3J+9NwdNZ/fWTBHFse8dR7mN7MPf3PZzbSLmXUe4K+rbPvzl3OeU6KPcG+jZa5j6CucqmUgve8IBi0CwU+1mWLe4WQuPV6vNXGzJ/Z8ZCt1/nVCYOFU98nnLQmTmnm7d/rvIVhJoI2n97DilWwS3flxKIBTMl5WIoUvqN/M4FH3SD0OC5yudB+2r8QGZOjxZV5g05WOoRBdJhjQDHqgvnwA7y20c7Opl0Raava9E1felgd3/2ab79WFX9nHRJx7n5GFJjypPoRMfKZsxOMjV9wPmYUjI7yaRj/GhJ5ekGOOdZ9AORaSkjXdKAx3YZo+N4Cx3HDSYCOiJ37X3zO+k9alzMKEEeduJUueQpq9aI8TASWb05q4FRci1nCU40BrI2ETEOy7sSQjlD5yDBf9WRoP20p0A9TpXaWNo5kMHngJPPgQzcS/ueRHx61HhKnxa0f/SkHi1kQIzxg6dEDiPIHiJDC86RwUgo06zR7NAt8pMj6XYBADNF97Q+lZuoTzW8
*/