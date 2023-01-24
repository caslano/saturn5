
#ifndef BOOST_MPL_DEREF_HPP_INCLUDED
#define BOOST_MPL_DEREF_HPP_INCLUDED

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

#include <boost/mpl/aux_/msvc_type.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Iterator)
    >
struct deref
{
#if !defined(BOOST_MPL_CFG_MSVC_70_ETI_BUG)
    typedef typename Iterator::type type;
#else
    typedef typename aux::msvc_type<Iterator>::type type;
#endif
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,deref,(Iterator))
};

BOOST_MPL_AUX_NA_SPEC(1, deref)

}}

#endif // BOOST_MPL_DEREF_HPP_INCLUDED

/* deref.hpp
tzNgtrxrnCOT0bpFedqIVHHf/PtZu1nzHq2+UoNZqKqGazXySw0apfmtpWTT+eEe9ibURtbgpGT+2dZqqA0afFFlcHSzme2GocjsWQahoLycYWL1xIYKUF7uQYH7OW+2jJe7Gs6exJfbN0T6wXmTTZ4VIu63iCJnqpaKeDT82PkWjEx7Uc/o+n/0RdfB2e1y9v4EH7w+w72JbA55exTkZ8DLWcO7XXnZK0aQ0W4PAZENU7cvj8Z3uGB0PhLuvnpQPTowXR6epjPFTvJLFyUa6q0HSBcNSHeOcjZMnqeda5wvy5kAGrfqtxrbVi5XQOePNGynAhP1vG5caT+MZnryQ/K1Z7RnfCAV7BN7SMK3T7S9eM2R821/5oxfkig6PBPuR+nGQjXa33KdEsYBtFvbN11jfQ7P4IK73ea5y/dTtdwxJmZbozimmeC9uCFu2UqX34pWd3rFA9ixHu+pnAxze0jaBKcBQtxSjydYnn/WN7s+VrzrZ+T1tuHMunzdOkCpwnI8yB6huJ3lyqI0cKfG+UI0R/9gaPmNmskjxsXaH4oGiMucizU5/GTNoZevPv+PrEw/nyjN1/dqfdqJb/pNyocOzHIOersYRM6dgkXSvBGiLPK0HhjOTKk6yZp29U3qld1Cp3idVljxf9GMzUUymfzMQ1WKP80qKBndl40rG4Iyc77yzTwsCXBg34vSVBxcNpXko4TJlve4QyP2
*/