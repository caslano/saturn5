/*=============================================================================
    Copyright (C) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_NUMERICS_FWD_HPP)
#   define BOOST_SPIRIT_NUMERICS_FWD_HPP

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  uint_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T = unsigned,
        int Radix = 10,
        unsigned MinDigits = 1,
        int MaxDigits = -1
    >
    struct uint_parser;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  int_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T = unsigned,
        int Radix = 10,
        unsigned MinDigits = 1,
        int MaxDigits = -1
    >
    struct int_parser;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  sign_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    struct sign_parser;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  default real number policies
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct ureal_parser_policies;

    template <typename T>
    struct real_parser_policies;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  real_parser class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T = double,
        typename RealPoliciesT = ureal_parser_policies<T>
    >
    struct real_parser;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  strict reals (do not allow plain integers (no decimal point))
    //
    ///////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct strict_ureal_parser_policies;

    template <typename T>
    struct strict_real_parser_policies;

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* numerics_fwd.hpp
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
*/