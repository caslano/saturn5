
#ifndef BOOST_MPL_BEGIN_END_HPP_INCLUDED
#define BOOST_MPL_BEGIN_END_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/begin_end_fwd.hpp>
#include <boost/mpl/aux_/begin_end_impl.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

// agurt, 13/sep/02: switched from inheritance to typedef; MSVC is more
// happy this way (less ETI-related errors), and it doesn't affect 
// anything else
template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct begin
{
    typedef typename sequence_tag<Sequence>::type tag_;
    typedef typename begin_impl< tag_ >
        ::template apply< Sequence >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,begin,(Sequence))
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    >
struct end
{
    typedef typename sequence_tag<Sequence>::type tag_;
    typedef typename end_impl< tag_ >
        ::template apply< Sequence >::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,end,(Sequence))
};

BOOST_MPL_AUX_NA_SPEC(1, begin)
BOOST_MPL_AUX_NA_SPEC(1, end)

}}

#endif // BOOST_MPL_BEGIN_END_HPP_INCLUDED

/* begin_end.hpp
mRNcctxfi8Ksnqe/ZW7618J7opXULcScFpjPEtjuEAZ8fAFfHARP8626N8sfc6oS6mjkBIoEej/9zL6d7tWyWWjAdn5KJnKrGeb1zj4/Q+6OBzTs0kOVe3oI5C7FTUWuz37dlGuOR3IXmOdXEyV/yBgE4cUMnGRmWWusD6eJj0e5vQvppoQG4c0qvZi5Kt/ehy1Cy2+xbGtdc2Xqc/HGjm826YlQeJs+VSq5xd00Qb4VGK9bn8mXySFhtjvgdiWKuVJUUQDNmFdOYnkze7tGdyCGCvRfJ3hrKSHv+XPUVJouPwO2MdDnEh8BBqPmduzBx8sbRcBSwhMll4eDpD6Tj6KLO7VfIx3BdhsQuXZ9jzK+B2iahD05r79F0hx1vW+IKCm4XqgOksCD/MAUS0tV9qrtSIAkbNxwUduX1jUJ2yHzpi9TRyxaNELM5Xa27cDU9JJbkwiFSJD87Ex7SQ+B306snxFoWehByo/Z0PHbDl22n0fU/kBZzDl7mJjB3ry+QBliCoD5wBE9UcdXyaRbfeutttWntr2nCUeuNdIzYmlHJFX/Ghq2tRYa/Q==
*/