///////////////////////////////////////////////////////////////////////////////
// accumulator_base.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_BASE_HPP_EAN_28_10_2005
#define BOOST_ACCUMULATORS_FRAMEWORK_ACCUMULATORS_BASE_HPP_EAN_28_10_2005

#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/joint_view.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/fold.hpp>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/empty_sequence.hpp>
#include <boost/accumulators/framework/accumulator_concept.hpp>

namespace boost { namespace accumulators
{

namespace detail
{
    typedef void void_;
}

///////////////////////////////////////////////////////////////////////////////
// dont_care
//
struct dont_care
{
    template<typename Args>
    dont_care(Args const &)
    {
    }
};

///////////////////////////////////////////////////////////////////////////////
// accumulator_base
//
struct accumulator_base
{
    // hidden if defined in derived classes
    detail::void_ operator ()(dont_care)
    {
    }

    typedef mpl::false_ is_droppable;

    detail::void_ add_ref(dont_care)
    {
    }

    detail::void_ drop(dont_care)
    {
    }

    detail::void_ on_drop(dont_care)
    {
    }
};

}} // namespace boost::accumulators

#endif

/* accumulator_base.hpp
0wF+RZf1/RJctZh9Zzym2rhYE7DL7IVvNpd2hs2ew1MSdNifWrj0nfsre5PoZkY7XCxsplCqR9jM1DZCgWmbUUYok80V8eQcPdezAz5j9PqoxoxPtW8e6tGPvpEBRCFMBvd64fXOyY8EPIvvM/u0KnYnWUwO+oajQRSTPOsepbwisVrqhdPQgc/s/L7rV3C1Jo2PypEVpbt4fwzBbqTEavci3xi6hIQ37pgpZEbEfYAas79UNr1NqJyguvKQ3t0/GmTxrZsl83ZVvsE3QMVFMZ9FB94G8MJ+ZwCIfLnH53ebLipFYN2yygR438ORSHMmnzCDZtlLVj1B/vyDxCUTPjf3C8T2yMSlBgtKMfl0T3rF/d82S+pumAxmWK8KFc4YPwslsuCKIAPjzrCEsUhVEeqwkggZENEuqUeFlpxqaZeu4UHQDztx7Tt/M5X69j1IBhYF5hhYyktf27twgAD6XsjA5GEl+7+XCBTnJGgb7xBfRtRhy7QrzinKSK2oj3rfA/gOGq4dpg/LACUiTfl0ZJ2hXSHpWrhdVSgGtNwUNNHfSivFpKEjzshCEQ==
*/