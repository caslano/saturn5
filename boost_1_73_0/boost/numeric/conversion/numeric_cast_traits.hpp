//
//! Copyright (c) 2011
//! Brandon Kohn
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_NUMERIC_CAST_TRAITS_HPP
#define BOOST_NUMERIC_CAST_TRAITS_HPP

#include <boost/numeric/conversion/converter_policies.hpp>

namespace boost { namespace numeric {

    template <typename Target, typename Source, typename EnableIf = void>
    struct numeric_cast_traits
    {
        typedef def_overflow_handler    overflow_policy;
        typedef UseInternalRangeChecker range_checking_policy;
        typedef Trunc<Source>           rounding_policy;
    };

}}//namespace boost::numeric;

#if !defined( BOOST_NUMERIC_CONVERSION_RELAX_BUILT_IN_CAST_TRAITS )
#include <boost/cstdint.hpp>
#include <boost/numeric/conversion/detail/numeric_cast_traits.hpp>
#endif//!defined BOOST_NUMERIC_CONVERSION_RELAX_BUILT_IN_CAST_TRAITS

#endif//BOOST_NUMERIC_CAST_TRAITS_HPP

/* numeric_cast_traits.hpp
LAa7lzZ0rVhd397ZJNZfKjWovlbR3632bm0SiVvXWRVl3tm1drCdtrr26Gg+c7ACqtaG/aVeRk9Dm30UwY5ZHXT9uIrXJ2TbaubMGshQjlVs20zX2928lTO+GuHzv7aSld75bRCTxH9pEbH8/9cc2OOup6Nv7dCbsvrD4CRU76rWxG+tZQebj+pSmtc0Nvf1z8GKUYsz8L2pra1e/tfe0Nox+FL9F0HS4XqXbZ00W2kP/NxG
*/