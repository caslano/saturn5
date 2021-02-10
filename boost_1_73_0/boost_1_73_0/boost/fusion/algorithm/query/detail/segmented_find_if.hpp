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
vo8HzatR9jI2ZgZClomhozxQi4jagvq2dElBxD/P/AT7cJ9s+5EQeDojJDiHwb19mZmV1vwtHhDK85IDRx5oOZMYThJs3SQSJNbzWVhywejmk2RNvG7hmrFfr7eetj0PggC8Jh4t5aAh1ahpQUOsjiffo6BwbMgvVSNDdh1/G/gsFdtKZPOi3Rn6rXF/+K3wZvTtErrN4hf+507Ln5x3+63Sl62PzWHhHSTd9qAz8ItdsSa+CKzfH7LKlraFmPskwoXENIQWYLSh/8UkEApLyIqD3PdXvU+9/pceICi9huh+4yltJ7PVfH9iHVnf8yJzci6Y9ek2P0wYSqpYoB+lW3iqOUahm9erm487Alk3b1Q3H/jDS7v5cXXzq07bs5ufVDf/kGt+Wt2cbwOr+Vl1849Aq1b/qjf2jCRMW9RJOTy59nB3Eambh0pLxRIin95ZDBJ4MR7gbM+mwWpGx5buODylbbWVaPgUTCEfCaFkRtJWgqLefy9FBE95zvA/70VYfAgeE+/fwlX8m8iYmwWoNLOm7MF3j8/w+yaa6V9v5VeLSwOVe6+1Y2hCQ5pB3Za8f5Hq//6dicche7wJ78KufYlS+iUiB6293lW3W4P7Bt89lrL0egK6oaw1euI8GetvPWj9N8iN/fctMSdL
*/