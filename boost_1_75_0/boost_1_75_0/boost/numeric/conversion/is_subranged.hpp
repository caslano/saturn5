//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_IS_SUBRANGED_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/is_subranged.hpp"

namespace boost { namespace numeric {

template<class T, class S>
struct is_subranged
  : convdetail::get_is_subranged<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                  ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                >::type {} ;

} } // namespace boost::numeric

#endif



/* is_subranged.hpp
8MMpV5pL3gUQY1ExlHm2LTrz2T+RYmnlF6HNLHsejmGnmkl/uafargdjY2dmAfvRqF5hCMcLSPJuWBTSasN31C/ZVru02sxTdU8H8VDnyRRzvxcQeQ6Q+yLjmMJVVvNT+Zh69zTqnpzRfOjh54kPlcclYu4peSIwQ8WpAlUcDHeTGFXwKMb/9KXn9e8i83m2Lz9jMQr21nrkjdMEZkgcjPNnoZdZMbwxhbIr5vHP686YwSmJnqDDggHBPVyVWzEKT0/GEx4UvYto/9RPEbTH2WFV5zeXok2ALp9fijuqifSfvY261p2Mh7uZTyM1mwXN4Cx0vGtASxlCm+pMKdZ3Nung3wtiFOmPcancSl6OO5inuuW8LPjbjBZ2xBEVOYHI/kSB9B06Dcw/HzXrZtpVRkwMeYAS/v+IusYP0xOpZNPz6RYTI8d2VRv4h7bCxTI32tXgDP3+wJ1/wEgbmNiPqSjQGcCku4LBFvgctp9RYH4j+hhWsTHcHRkD5u5yyycjY3g+vY2S/T5PvbG98BCOwcOi02eyPKHHjGFWMUt9bqbesmoHjSo8gFuFiLxUcYQlCjMfORL+/BIGAofcxtYsTRWj5pumPnOTwMGeyXp24jetSZlAp7arJgZkFt93PbHlZxhbzj4U0D9UtYLMP/AdmGa7E+ZJQaRyFcePDHVBFae4E5AEIrVo19iTiVWIEkS1sOR5QYbcpG6IY8PK
*/