
#ifndef BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED
#define BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED

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

#include <boost/mpl/size_fwd.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/aux_/range_c/tag.hpp>

namespace boost { namespace mpl {

template<>
struct size_impl< aux::half_open_range_tag >
{
    template< typename Range > struct apply
        : minus<
              typename Range::finish
            , typename Range::start
            >
    {
    };
};

}}

#endif // BOOST_MPL_AUX_RANGE_C_SIZE_HPP_INCLUDED

/* size.hpp
P5mP/eXEv8e4h/UK4dnXm94gDF1Mr1t4teyHuwnFxzW4wusQ7/R21hzDvRmelQ7ccrEbOrfYLfFi5vjYdfFMn29neKF/dEK8Kp1H3LvCZAbPwT3+FTsJHq7wKHQKPAQUJZb6/Ro7OR6O8WrmxPq8wQ7X9/70frVubhpG40iBjKsqU4KRBDIYMsRiOIszoOApYcDDv8SZ+qwTChp+nDhHzly+4Mxls6nBZCFQUjAgJWiAq3uzCQHyyFLSBED+g6y51EG8jTOSJLv3dfXF8vtIvgjh5YH/NGJ0+38B/AsK4L/Lpz2H4HQYB29Rr6qX/ZSoiweGSMAIVCeDeaLTaSwWI+NssZh6xoatixAUnATs2t+uESmVwy+HI7IzkrKasaiE1nAaWMdaBiGrlkKgBvx60oMLJlDABYwiXgjEywxFHOis5d7r+MKcg/BCE0nJllWOVtMrBffqDGxYzuALukDvfj76AgNzeLfwJ3js3tBCJFpbbUWJndZTyFrNqP9lOndHd7gPE5BuwVhQdTmCKq/RuoiTjXGSujmfPvStJF5r+9YFbKQ+af0a7IXk2r+DX8imPE2BFHWkOpZ1rmF50865DtH0bu5bHz4is6jcAUyioze6xcEYzFSSQnCPKuxcsH06abQ9mERH/2zrJADX
*/