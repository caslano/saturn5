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
w72rTP9eUrEzIK9jLgIFqoM80NFfoX01fYZPKxdAZsBEtQcZrXMK/6gi4Jf6LQW7chDqZwIIW7qcJCAoijiD2i8sMMwrT6VlRr1B7tupDYDRhGmu4Yq21C8rkzuwte1FsobEn9jUzD4q1meYda2pKzOZy1O2xOmZif3qKK+jWfOn+FxKYm7vD2IdZdSY4unkJi9kDc5m1JFIQfpbJb26DeOnf+jSLfqWb1gTnWSBzw1aY8VL/CBHPDBvFV4GbOHJaiZGO6ZHZbtvBFqfgUVEbls/Na8X33UtMD+sIkf6B28miYnuBkG8sqiZ7SQr1XzbN2e5WZa9SdcijqRzt87Doo4UiBmDP8lg1lS3zh8ps4MRHHIpD5XfmR8LceUhtUY1jvSW8VAIzL0l/hY0yvgbZXRq3brRIod/nB5BthvSyEROJ2rZ7rZRQ7E3ssw4+JH1BVNsjXYXe8EleAZwJM91RBdagvdlNRkDXvQgkMPnGVxw7T6t9emtXAgCi6FDcgv4EyGqvPlVSGyScTN3NcbX2VmekXfh3HSiT6EB+57K1X66Qv7uLDX7gyCLHg==
*/