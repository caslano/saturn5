
#ifndef BOOST_MPL_FOLD_HPP_INCLUDED
#define BOOST_MPL_FOLD_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2001-2004
// Copyright David Abrahams 2001-2002
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
#include <boost/mpl/O1_size.hpp>
#include <boost/mpl/aux_/fold_impl.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(State)
    , typename BOOST_MPL_AUX_NA_PARAM(ForwardOp)
    >
struct fold
{
    typedef typename aux::fold_impl<
          ::boost::mpl::O1_size<Sequence>::value
        , typename begin<Sequence>::type
        , typename end<Sequence>::type
        , State
        , ForwardOp
        >::state type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(3,fold,(Sequence,State,ForwardOp))
};

BOOST_MPL_AUX_NA_SPEC(3, fold)

}}

#endif // BOOST_MPL_FOLD_HPP_INCLUDED

/* fold.hpp
phLMplMmAc3lJTaeBG5nkKW3Wv0ddJJUAVMwE5MSxDSHMpWjOiGrDlvRzY+OpWuvdX5yGXYsx6qqtYUVjqxFZy5CKyXHWiacZfroJuSF7Nqdxaoq8TaN1bL3NP5K3X+81WKX910MYQ/7Un8jwr3rD5QwtTG+WAkCuuAr/i5v138BUEsDBAoAAAAIAC1nSlK9+ANX5wEAAHMEAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTU2MlVUBQABtkgkYLVUUW/aMBB+t8R/ODHxUs04zrpVJAGpYqi0awtqsr17yQERYEexKfTf7+LA0KpJ60MnWY7Pd/f5u8/nJA6ty5XFEUtKvTD0WePL3tSFHbFpls1TP/sJbiYZy41Zl2jbjRqrjcqxgBWqAmvLEnHOTkQLyD5AivUz1tyWBbKkSXohd6Gcku0hQvYlhEEAs2/sq3IYQbbDjxAM4NE8k0MGIC+jy0FEITcPGWvxImjIc+sNsVBrJIfjY88wgoUxQxl+iqFSbjUUMVjMdzXGbGy0Q+34PeqlW0VwxZg2WxpE+UjKkwv/M7kYJoeqrNEOs9WOACW/U5rLwVUAQRD50QDG8KAO/HqJwyCGua/lnyWEjfxHoUn/8aZsolv9c29QwAKVI0HoqtL0
*/