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
T64ax3nRyuLcIMfZKVXP9mZO+y+fYNjf2S7T3XfvuEjwZdNURq+pQ1SXAkz5UTZ69fRk1XKriWL0SrjOquOD66gOyxQYvT69AqNX82m8WsoPVV8KUOtHqTYkY/2X8vpIF1ofaVBY0iIsf0/HNueIl9vLw8lKewkhxgY2UdpLAtrLD78zBi2cwZdf4+1lRTxnbGoEGEvQ2SHG7ub4zKpu3KuW6zdu3CJ8jc4pMHencvfcfdjd6JxI59eLOR+KMXu65/dpxYzZ3DWWi42ixS5h/7L3ivjYk2+R3eyEpvcV9aTKy2EhWg7Pu5wj70K+VvGey13Tcex66e1e9/hd0wnCNpFgelesXc/YZO488K54s+OGpssaHYga6j7ap+2UMdoJUtJ0tJp5gomms3WqiaajrGu0f021RFV7IC1qRAl1f5BlCu5/iWmqyBS/bNZlQ7OxRLVjIpaohl+ETLkax5eo0sNpz6fKgDK/p1LNQ+z8koNP42TJsf9VRXKso8UoRxNX/fS9Xxgbx36B5Gg4kUuO4XFccrQPV9Yk34qwp/TLFhpPvVekGXZaXGLDzuglT2hNa8UFeVxwc/1boD1lSLawtxYbG+bU4mODdYme6T7MbNX9+ZrhxJV1qwqL78mT1b3J97QGUvnGQNKIVtD+fMlm8qx8eDchxVk8Bqju3xiXfE++K3IYubMkw15fcjMJcfUN9cfR2GmJUqdy5KMF
*/