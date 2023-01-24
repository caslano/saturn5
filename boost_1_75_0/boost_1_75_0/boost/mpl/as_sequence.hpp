
#ifndef BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/single_view.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct as_sequence
    : if_< is_sequence<T>, T, single_view<T> >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,as_sequence,(T))
};

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, as_sequence)

}}

#endif // BOOST_MPL_AS_SEQUENCE_HPP_INCLUDED

/* as_sequence.hpp
ilMciru7u2uxQYtTCrQUig9uxV0Hd5vBXQdnsMEHhtndbHafNtlsNjkvJ/lybu49Dze/3O8e7Cp0OHMnUQttC3oLSQteC0VL5A71In4FY6ut8xAy2PyZO85Fq0oDwR2au4A7cQ1JC3kL8SLmFRroH8Y0d/FztBoyv78Wi/2aocG4fml361EHTDXPFvGu0JHdofmEZcJ036y6o+cunRefZZhuWr23z5FYMtj8tOm/2R6K7CaQeCYogQpw2sOz6ofxYefb6okkfctAH4sZjAYMyaqEiGRQxmKN75j3UjZW+lV4/TBDXuj3b6efSgfOKi9aJeZ8cpGBbdU4EBKuZDdl12BrNqXD+KoX38zUaOHVo6zfWn6oWPwB/kYRWyv2LgPj9ueU3/j3JWR2bN4sLncYk14gW9IYdkXEJ/shUitkYprVWpToczKYtAiLzomeGpKR/qOzrNycl6paielaeGq3prH1Qw2dQZ6JGceC05LGjAN53QuFFX/cNPJ4bd7bAwHLcFttb54S9zqwMsOb+xYSKkWKz3serA4P23qFX0vKdi5rQ9uIB7ZjH38e1EZZhp0xv7McCGJeSRjC0PXkdfwey/XZNwBWW0rBja1iCrESnRhiA/5VJDZGgmbCafi5LKInPk+/BDupyabEb6TsblddhMsyRuyrXXcN4ZwSlzoQpEKNSCJxqN5ZV89t3M0dOjt2c3WC3zZHCIGQnaHi
*/