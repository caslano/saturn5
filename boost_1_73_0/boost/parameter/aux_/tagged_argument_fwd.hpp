// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP
#define BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    class tagged_argument;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    struct tagged_argument_rref;
}}} // namespace boost::parameter::aux

#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg>
    struct tagged_argument_list_of_1;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* tagged_argument_fwd.hpp
R5ca4ujWMdveEaKGOHrUEEdFDXH0qiGOPjXEsU3N3hGiZu8IUbN3hKjZO0L0OGPvCFGzd4SoIY4HqCGOB6ohjp1qiOMyNcTRr4Y4dqkhjt1qiGOPWJqBprbXGd5z6gzvOXWG95w6w3tOneE9p87wnlNneM+ps3Dt7oCzcO1uUA3zHR50FuIYchbieIizEMewsxDHiLMQx6izEMchZyGOK52FOA47C3FcpVaD95w6w3tOneE9
*/