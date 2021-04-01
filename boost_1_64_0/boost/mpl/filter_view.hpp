
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
c0UWyKwc8/QyKvxbfI/qBqfkR7KAXkE0b73VBKpX8WYMrRGcc7ut0O/m6NXgYOpBbgboOqWZkYYaRKMgjs1eB1gvJ0JcqN4BHWuk/7GQofFsuVLzl8dzEJlMm24gbHrHtGcHyOtoYCFrkl00vncreDYaqA7DHRpzuKuadb6cASpcqyYhG26TFaMWD7eFoh23LoZTQcpWjkRtmplLyYohbopm9p+B4S8Evyk0OGJf1m4lbFS0DPqf1yx0MGlgKdKsh0wbe9WCsOvV89Krunh1a2VdKPQTGAUPPQUyV3iBQyBamPeF+MxWA3ZrTw7PrnnQoaKqEkuRDQyGinMsrCW6Fmbwjd8EeWfYpYMAn1SKKQvZn4c+FbcRXf3JF4UM/cznXnb4C9MtjM6WVr03mKkaeP8ZlavF3k3E6r5xWww/jNbwtf7+lsx9OVYtfLpNVqsPLg+8jD7YdP0a+Fdsep1E/YyKv82sEofRVip+T86Hd8hZsBbyONbPeNNm11IAAT0q2O+78LjExalg81bhjKfL4itBROOvf2yxaYmMk6MWcfZJD5x4ephYWUOVjw==
*/