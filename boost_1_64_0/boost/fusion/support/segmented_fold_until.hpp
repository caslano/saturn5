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
87K2qjhhh6tL3nCVKJfTsaR+TiNyzXU/w04ZXJEfE1nehLt1dw4bWW8bQSzQCxN7mr+IyezQ4XzM9LuCBvxgcPRcDyM2/LrjbfpcxxY9EJbfuHyWAzVkiUKwkhlZPyynU+nueqbouJI0vFp6YoWaPtQCIaU8E2S+Va7XmERnIpawu9xXbYvuJeAgtD74iXxagPdiHeEqfYap7ftyzBpz4KkNEBIZH+yiAp+w9Nj2LM2bIPorMEqTxhTC/8peVnVVuHMar9XakRiA8d5ehHOT3OVDwLYe8zEyeCnJnmDWQbWSyWbFYtH4I2gX17yIrWyMfaSavjLtLPe1D0iPa69fKrsuYGP7SaCSO1PWRtn/u6YW2aTnYXbrkoO2qMJMvivJ5KLpPrlzoa9KlzM0afvFn0pl79OVPX5e90nG5lUZKU0FzZGGmrxSxtwUS8N2jhl36NPpCuM1NciBhAe8gnWTmcDjpp3EKag03z9q7jMX1QNTOZ5sN6wY7tytHZ8Qz/16wk4IipdWipn2++o7Vp/320QtcjsY2qVk/YSJtrqygGOeECjiIBcT13ToGQ==
*/