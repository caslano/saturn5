// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_QUERYING_H
#define BOOST_MSM_FRONT_EUML_QUERYING_H

#include <algorithm>
#include <boost/msm/front/euml/common.hpp>

namespace boost { namespace msm { namespace front { namespace euml
{

BOOST_MSM_EUML_FUNCTION(Find_ , std::find , find_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(FindIf_ , std::find_if , find_if_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(LowerBound_ , std::lower_bound , lower_bound_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(UpperBound_ , std::upper_bound , upper_bound_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(BinarySearch_ , std::binary_search , binary_search_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(MinElement_ , std::min_element , min_element_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(MaxElement_ , std::max_element , max_element_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(AdjacentFind_ , std::adjacent_find , adjacent_find_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(FindEnd_ , std::find_end , find_end_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(FindFirstOf_ , std::find_first_of , find_first_of_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Equal_ , std::equal , equal_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(Search_ , std::search , search_ , RESULT_TYPE_PARAM1 , RESULT_TYPE2_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Includes_ , std::includes , includes_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(LexicographicalCompare_ , std::lexicographical_compare , lexicographical_compare_ , bool , bool )
BOOST_MSM_EUML_FUNCTION(Count_ , std::count , count_ , RESULT_TYPE_DIFF_TYPE_ITER_TRAITS_PARAM1 , RESULT_TYPE2_DIFF_TYPE_ITER_TRAITS_PARAM1 )
BOOST_MSM_EUML_FUNCTION(CountIf_ , std::count_if , count_if_ , RESULT_TYPE_DIFF_TYPE_ITER_TRAITS_PARAM1 , RESULT_TYPE2_DIFF_TYPE_ITER_TRAITS_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Distance_ , std::distance , distance_ , RESULT_TYPE_DIFF_TYPE_ITER_TRAITS_PARAM1 , RESULT_TYPE2_DIFF_TYPE_ITER_TRAITS_PARAM1 )
BOOST_MSM_EUML_FUNCTION(EqualRange_ , std::equal_range , equal_range_ , RESULT_TYPE_PAIR_REMOVE_REF_PARAM1 , RESULT_TYPE2_PAIR_REMOVE_REF_PARAM1 )
BOOST_MSM_EUML_FUNCTION(Mismatch_ , std::mismatch , mismatch_ , RESULT_TYPE_PAIR_REMOVE_REF_PARAM1 , RESULT_TYPE2_PAIR_REMOVE_REF_PARAM1 )


}}}}

#endif //BOOST_MSM_FRONT_EUML_QUERYING_H

/* querying.hpp
Ht8LEgeDMkd9g99E3VR4RQLg0jBJ87cWmYdb6K7kM+qy2EEurABRWNRA1UJ7l7ARBtaIEnpmo2yP8acOGxBrOKQxjZdJFK4W4exuFSZJnDCOWiudqZxmMhyS0h8+nYCyKlNVwMKHKAbqzGHT20kE90k89fm/lQcOS8bzFNLY5//pm54/LSep0234mJp7xxq5d/q3fgFQSwMECgAAAAgALWdKUvvAjWvfAQAA8AIAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3Q5NjFVVAUAAbZIJGBdUl1u2kAQfl+JO0yIooBUx0qqIEo3VivXUZCcQI1ByhPa2OPaitm1dhco92mvkAtwsYyNKW2fPDv+fuaPWzQ2EQY9xguZKfq84m6rdGo8NnuMp2wR3T8z7p6y3D0A2Tk7hxnqDWrHFCkyrrEqdzWgDRqEXxYobYtImgdBTMPzmFnZigjHJ89Q2LVGsjkrUsnOtoX8eEOAU56oFuXGY6G//BqGdyiX89nVPL53hnXKj5+nwT/JWv3A4JXGJMfk1WMV6hKcx/H18Gk0CoX8Ufd0V7bBB3/yLZgFMTgIl2mB0H1CTA0IaCShVIkosQtFBr0y6R1pvZbW6/f7IIm1tpkz7PY/X1IRJ2/gUqzwMF7Anxa1
*/