
#ifndef BOOST_MPL_FILTER_VIEW_HPP_INCLUDED
#define BOOST_MPL_FILTER_VIEW_HPP_INCLUDED

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

#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/aux_/filter_iter.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct filter_view
{
 private:    
    typedef typename lambda<Predicate>::type pred_;
    typedef typename begin<Sequence>::type first_;
    typedef typename end<Sequence>::type last_;

 public:
    struct tag;
    typedef filter_view type;
    typedef typename aux::next_filter_iter< first_,last_,pred_ >::type begin;
    typedef aux::filter_iter< last_,last_,pred_ > end;
};

BOOST_MPL_AUX_NA_SPEC(2, filter_view)

}}

#endif // BOOST_MPL_FILTER_VIEW_HPP_INCLUDED

/* filter_view.hpp
vIMJWI98Go+BmITBaMa2mCxlv6WF5HyR88dfjtH5kq8pkq+TJP+mYBw+hak4DZdKncEqfBo34Czcgs9J/s3GDJyDn+I8/Azn4yF8Hk/hAlQS8xLWxsXYCpdgL1yKg/BVHInLcCIux6dwFc7ENJyHq/F5XIMLcS0uww24AzfiLnwd9+Jm/BXfwNv4JjYkv7Zia3wLQ/AdHI3bMAm342z8Jy7Af+Fi/ABX4if4Dn6KO/EA7sdM
*/