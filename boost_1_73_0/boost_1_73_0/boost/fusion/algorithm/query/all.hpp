/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_ALL_05052005_1238)
#define BOOST_FUSION_ALL_05052005_1238

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/fusion/algorithm/query/detail/all.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename F>
        struct all
        {
            typedef bool type;
        };
    }

    template <typename Sequence, typename F>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline bool
    all(Sequence const& seq, F f)
    {
        return detail::all(seq, f, typename traits::category_of<Sequence>::type());
    }
}}

#endif


/* all.hpp
L0l2F+wFaFXpZ9ZaYbA4MKnQJnfoJuSUUln4qRPmAFkwJXa16tnmsma8LM372M17WdD0QiSsntWnwVJG2E3cs7Zu2EnwUmDU/nZsL0LMiGPJJoImJCGhjtgM0G8PGVg4fvQ5E2t4UtHgiJ61/EIm9iv70kAaXMzn6ZQJwbD17IHLClZ+mIxZBJngpkpGIub2ZWQrK7BkpWsmKBBZ6IJAgd9PlkEEQaaR0MEkhS5W3r0PrmG8KHSrCAUWwV08WzkMAycvAqqHD4oBm/sIQ3Yiffto3Ea2hr5Pk2Uz980Qsg1PRm1kF52+2AuC0f6WMNq6B82bbu1e6HLesfYsgxYQleMKrDvjWluxoki2T8BuuoVFNl2/gL2Tq7EBHY1fz6K+0FDD+v9AOA2wH70Kx0rv9eEA+DGFb31OPkGb+crEq9hDarTX2GG1vQXz0D4Aa/TLK9hXO12MKgtCg20xvcDbv58MsS4P/TGJ5hGsGsBO0xK1dU27r8s8CYJJt95OJzzU0B/IcFGuc838cUezm54FzwV952n774IKHl3QYmOWR3Y5pe4tC3sltWFnpZ8rUR7FkI2NIbKrKbmb4IXyqLQR3mHhwMegozgOm38fNbg2qYqqLbHiy5QZQsMplRXQdSF5TpCx3Z4oytEECEJF
*/