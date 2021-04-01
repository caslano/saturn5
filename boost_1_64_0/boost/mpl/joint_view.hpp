
#ifndef BOOST_MPL_JOINT_VIEW_HPP_INCLUDED
#define BOOST_MPL_JOINT_VIEW_HPP_INCLUDED

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

#include <boost/mpl/aux_/joint_iter.hpp>
#include <boost/mpl/plus.hpp>
#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

namespace aux {
struct joint_view_tag;
}

template<>
struct size_impl< aux::joint_view_tag >
{
    template < typename JointView > struct apply
      : plus<
            size<typename JointView::sequence1_>
          , size<typename JointView::sequence2_>
          >
    {};
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence1_)
    , typename BOOST_MPL_AUX_NA_PARAM(Sequence2_)
    >
struct joint_view
{
    typedef typename mpl::begin<Sequence1_>::type   first1_;
    typedef typename mpl::end<Sequence1_>::type     last1_;
    typedef typename mpl::begin<Sequence2_>::type   first2_;
    typedef typename mpl::end<Sequence2_>::type     last2_;

    // agurt, 25/may/03: for the 'size_traits' implementation above
    typedef Sequence1_ sequence1_;
    typedef Sequence2_ sequence2_;

    typedef joint_view type;
    typedef aux::joint_view_tag tag;
    typedef joint_iter<first1_,last1_,first2_>  begin;
    typedef joint_iter<last1_,last1_,last2_>    end;
};

BOOST_MPL_AUX_NA_SPEC(2, joint_view)

}}

#endif // BOOST_MPL_JOINT_VIEW_HPP_INCLUDED

/* joint_view.hpp
aE07UXsFLrm7t8byuG1VZxw2tIDFW+qqSEFeDwUtHmfaxodN3I5KdIkMYLdinurIG5IYQPEXeCPGBVztKs7nIHJ59ShHJg3Ve7x0jJYQ+yy3fGeYwUhrqOG60c+89TK8hJhCSRhRW34XkOVRW86sjYvkuEdVikxUei1+ih+6i2zjhC0CZFvvzywucxfo9yHN6hQ8fnW6hkep5Bs8Lt/pAeLlv8oTr8pygAfPY6XkssyEOmAIY0KcUU6HemrvcQoBJ/oLsHdho7MJH1oKp9JBgHJCdYfQooVeqlQ+uKx2ZuO8y8GhK/4/1kLGK4zvxQbjnSoS2BarGDTWFJNFYgIXt3caEwqWscy7ZcAHb7Me71bjCGNTEZMi/+yW5jOdaEY1Z6zB+TCRkbboBiVSR4MC0n42UtUJbaFXOCxjezgvgAXEav9TcVEdBVI9UwOOP7q8cU+SD5kFTL2OAEb/rDbt0GJVpJvvCvuxxsiZQnIIT6q7sfeUN1Mam12eOgb7wnCJ5exf+I9DWr1QM/hx3XylV1v9zzukUBHl7oblSNSNRg9hnNQGm3Ub08dvbw==
*/