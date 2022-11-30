/*=============================================================================
    Copyright (c) 2006 Tobias Schwinger
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_SCANNER_FWD_HPP)
#define BOOST_SPIRIT_SCANNER_FWD_HPP

#include <boost/spirit/home/classic/namespace.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  policy classes
    //
    ///////////////////////////////////////////////////////////////////////////
    struct iteration_policy;
    struct action_policy;
    struct match_policy;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  scanner_policies class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename IterationPolicyT   = iteration_policy,
        typename MatchPolicyT       = match_policy,
        typename ActionPolicyT      = action_policy>
    struct scanner_policies;

    ///////////////////////////////////////////////////////////////////////////
    //
    //  scanner class
    //
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename IteratorT  = char const*,
        typename PoliciesT  = scanner_policies<> >
    class scanner;

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* scanner_fwd.hpp
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
*/