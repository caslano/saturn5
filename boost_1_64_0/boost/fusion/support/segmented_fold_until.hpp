/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_FOLD_UNTIL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/fusion/support/detail/segmented_fold_until_impl.hpp>

namespace boost { namespace fusion
{
    //auto segmented_fold_until(seq, state, fun)
    //{
    //  return first(segmented_fold_until_impl(seq, state, nil_, fun));
    //}

    namespace result_of
    {
        template <typename Sequence, typename State, typename Fun>
        struct segmented_fold_until
        {
            typedef
                detail::segmented_fold_until_impl<
                    Sequence
                  , State
                  , fusion::nil_
                  , Fun
                >
            filter;

            typedef
                typename filter::type
            type;
        };
    }

    template <typename Sequence, typename State, typename Fun>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_disable_if<
            is_const<Sequence>
          , result_of::segmented_fold_until<Sequence, State, Fun>
        >::type
    segmented_fold_until(Sequence& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence, State, Fun>::filter
        filter;

        return filter::call(seq, state, fusion::nil_(), fun);
    }

    template <typename Sequence, typename State, typename Fun>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::segmented_fold_until<Sequence const, State, Fun>::type
    segmented_fold_until(Sequence const& seq, State const& state, Fun const& fun)
    {
        typedef
            typename result_of::segmented_fold_until<Sequence const, State, Fun>::filter
        filter;

        return filter::call(seq, state, fusion::nil_(), fun);
    }
}}

#endif

/* segmented_fold_until.hpp
Bm0lbfrrI6fRzYcC6C888BT6+XDAuvOHU+nnQ4JyCT3oLJ75PDj3YKDdKDfEB8ewZR2hfOC/b+gON3dq1L7ls+8kpul7zgPd+G7RP+HCefUhQLN4l+uLofwOD4XyGiC/Lx7Lf9aUH+4Z0TcB2vqeh0F5f3ndtKK1Z3040N0s32lHb94sb8h9ZRCL/xGVpu6auI5n9uV/q+Wnv++eGmf/lY88k76/5R+/pf4KtMX3ryqG5FdPe4/Ij5rTwfNc8533p1PoelC4s/7tk7DfohTJaCoJtiTAd6R/eRK+A+kSVaxGgTj9+Qp8pSDOw5Oxf7qMmmurBJk8aw3fT+Bbg/g4YS4oUZOvzp6e8ZvHKuJjRAmVOlX4pp9QPSD4FCI+RSzzTMWkyGnP1JOYaActbyY8eKNcJwh+vcbt/MhEvgJljKeazJ60Jz4ziE+SoFyKNCTSTLlFktvd48F3gcB97JSXJue5ouSUJ+6BF3QHyyi7bHLoMmm/DGex2adjmFxnrFMETV8YfZDx3FMmd0HKpqiFRHxo9MecuOcRryXZqli6KBN8HVM3hqUWLSsAfV1F/IxEmxljnSHTY/uSbxf8p1s+T4TIJgSfyZCNtbyZzXxmXoOwHInaaCm6PPiB7VantbKs31xeva28bnd7rx+Y0X9rUkcnknRWq7aO43IJeFodoFOoDk5UkbhGMhrqKKIvfZpghM/tgR/WBJ8rEzramdERqipXHeNlDTU3Q1/HeM+K6ogkGKmyjoa0wr92uzxZbiNhsA1bXYjxXSZzLofSlqXT02K04WK9595ig94UXqQ3Kntr8sLvaXN8lTta9mhxfty9MfPTXkV1MNIxLmXqSh0jbJuUe+DLiI8Sx1IXWPA945v331gvyo/L9TLm22n5EknRcNspuWBb2qAgt8ExV+yknyIXNFuXSD+1+uzhSyOA/h5FDXf7LS9XRCbKVegkGQWsmchL95Su6tsPN9tkfGP4BWqDJCorRmvygcP9ir250TeiZEE/Oh7fgo8hBzXi74gOIVNfxrpajBXBocNxIuZjNdzJI/5AsvTKWKvn/HMHwsoPY/407AOauOuC8mS5HRauk4P2LXt7aH8ufMj3uatRiaLsGXvp37pd/iyW8+n+eIBxu86IwJjq2XuXt32Y6lsD7kcQriaaWy2V8GP+6OvbR3WSQiJpPP4/RPwLl2nGOz7JHX04PC8W6xh4wgK/sHs9s5xXysHk9otbMOwYVsv//KRSvgvljWMY9gv75ugXVgnBMSwOb5hPwneTWgoak/ivc8z19ynobu4b87M32NSA7fRtQIc35IbmybcrNLNz7LIiOJfPaFpropHu+PYzuno/1psmNTm67jCnK3N8PLvfsSk/Ohg+8qD8Fi6vxm4o59HWnebl/blwrOPOmKb2HsqbdJd5+ULgo8bH4jSaJtbm6l1PKT/oXxxLsiF033oabe2V0urD7cYm/W4j3fwQgfISzOj6LhjrujvQHC3exRaoQDbaP92j0uG3m/5MD98Hf6k0/8XbzWvuiehmbzfwJtXTnWXXpO8F5bO3nZ+gstpQHKMdynrQ+/VlP1uU1f1t/Fa5z+PxedNJFZLMZHk+rXYP1ZgE2+Q8ueVJxGWmhNOs5ykWKCML8Ky2PIEkbqXIRpDmRWYWl0Y/HseliYonYevuWR+V8ffTtZaWGZKzFZ1NmSxHvreEmNlBQPtOcPtMl7VL1JFGJQaWo4HnI7gfohaMq0QJrMq1+5ZcwPNljBOj7YQRduCpRiKAA363SDZOeKbVZ0D3TDOpwI6r5YtECCaTtZS0tstLjtFP+7ctjyfJdJzmqMnxa4/6PsRnoz9N2tY54YzvEtk/WIY/Xh/mOG4=
*/