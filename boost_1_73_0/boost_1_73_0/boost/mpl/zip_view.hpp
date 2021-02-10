
#ifndef BOOST_MPL_ZIP_VIEW_HPP_INCLUDED
#define BOOST_MPL_ZIP_VIEW_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2010
// Copyright David Abrahams 2000-2002
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/transform.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/aux_/na_spec.hpp>

namespace boost { namespace mpl {

template< typename IteratorSeq >
struct zip_iterator
{
    typedef forward_iterator_tag category;
    typedef typename transform1<
          IteratorSeq
        , deref<_1>
        >::type type;

    typedef zip_iterator<
          typename transform1<
                IteratorSeq
              , mpl::next<_1>
            >::type
        > next;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequences)
    >
struct zip_view
{
 private:
    typedef typename transform1< Sequences, mpl::begin<_1> >::type first_ones_;
    typedef typename transform1< Sequences, mpl::end<_1> >::type last_ones_;
    
 public:
    typedef nested_begin_end_tag tag;
    typedef zip_view type;
    typedef zip_iterator<first_ones_> begin;
    typedef zip_iterator<last_ones_> end;
};

BOOST_MPL_AUX_NA_SPEC(1, zip_view)

}}

#endif // BOOST_MPL_ZIP_VIEW_HPP_INCLUDED

/* zip_view.hpp
9X3BmwLviBF2xSfaCT0uLDfAnFO2yfESV9zuV6jVGVLbJ/0AUEsDBAoAAAAIAC1nSlLNG7Vs9wAAAK8BAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MjAwVVQFAAG2SCRgfVHBTsMwDL3nK6xMHEcmjsjrhYGEtAMnOKI0dWlEmkxJGPTvsdtNlThwsGw/P7/kJVipVGcLNQp97BOnT5q+U+5Ko56ej48KzQqgWTgKM53CxEBnq21Un5ICgNZmJcGlICMHmoWB5rKhNvAQPMW6Lb4jhW5umFAonymzlg8Mm2sLGO3It2tt8Q5keG/MnHlklhm6NI42dpBO1ae41zFtfXThqyO9CPJOSM6GIZV6I7beX94ODH0Y8X+3293Wn8qnXoRYUrZA5Pf6D03/71cWxe/VGBt+pez7CeQlwPaVMtSBQCRhsAVaogi6DKlqheeZKwJrtf7RL1BLAwQKAAAACAAtZ0pSxH6F6akBAAD2AgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDIwMDBVVAUAAbZIJGCdUsFu2zAMvRPwPxAucmwV7FgoaYfVxQwMqBe7KbrLoNj0bEQWDUtp67+fpCQLsMMOMyBIoh7fI58pHVlXK0trkL1p2W97
*/