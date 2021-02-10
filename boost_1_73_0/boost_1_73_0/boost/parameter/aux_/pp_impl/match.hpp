// Copyright Daniel Wallin 2006.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PP_IMPL_MATCH_HPP
#define BOOST_PARAMETER_AUX_PP_IMPL_MATCH_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    // Recast the ParameterSpec's nested match metafunction
    // as a free metafunction.
    //
    // No more limits set by BOOST_PARAMETER_MAX_ARITY. -- Cromwell D. Enage
    template <typename Parameters, typename ...Args>
    struct match : Parameters::BOOST_NESTED_TEMPLATE match<Args...>
    {
    };
}}} // namespace boost::parameter::aux

#else

#include <boost/parameter/aux_/void.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_trailing_binary_params.hpp>

namespace boost { namespace parameter { namespace aux {

    // Recast the ParameterSpec's nested match metafunction
    // as a free metafunction.
    template <
        typename Parameters
        BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(
            BOOST_PARAMETER_MAX_ARITY
          , typename A
          , = ::boost::parameter::void_ BOOST_PP_INTERCEPT
        )
    >
    struct match
      : Parameters::BOOST_NESTED_TEMPLATE match<
            BOOST_PP_ENUM_PARAMS(BOOST_PARAMETER_MAX_ARITY, A)
        >
    {
    };
}}} // namespace boost::parameter::aux

#endif  // BOOST_PARAMETER_HAS_PERFECT_FORWARDING
#endif  // include guard


/* match.hpp
cC5wbVVUBQABtkgkYO1c63fbxrH/rr9iIzEB6FKAJbf9QNVxZFn29Ulj+fhx0lzTpkFgKaEGARoPyaqk/u13ZvaBXTwoytZxfZuojSWC+5id529md7G1dWs/G1vs2p8p/TeFH/iNHZ7n2T95WHY3nk4vmfgfdJrA72um8Fnd43I6ZNf2uGQu9ZjKOf6Gf0+n10wzQcLwHx87Tqb4JzzZQA4cZMvzPD4+KZl7MGS7d3f+yrbh1+7dETs8PebpOXuSxylzfw7ypMjS3Q/DEfvbh90PP6VBnkVeXv3o0TivTuKCFdm8PAtyzuDvJA55WvCIBQWLeBHm8Qw+wFDlCWfzOOHs4Oj5b0+fPRmxs5M4PIExzrOKFSdZlUTsJDjlLOchj0/FEMsgL1k2h94wdhQXJYxXlXGWejA1ZyXPFwUMgZMHQCgLToM4CWYwTVCyk7JcFmPfD6s88QruR1lY+KFauXdSLhKxit+AgkVwzrJlycqMVQUfMWw3Yossiuf4m+fH8HBZzZK4OBnVpMBEaeRnOSt4ksBQ0C3mhSCZs5eSMyNsxZZAbVziL2BpgTOdnWQLqyGwEAaZV3kK0wALoE2UAYNHrEojnlNbWrSaQXKTWNsjkprWiGUpUMI291+ypy832Swo4mLEfn366n+O
*/