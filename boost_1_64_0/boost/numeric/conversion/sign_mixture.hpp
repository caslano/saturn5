//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_SIGN_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_SIGN_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/sign_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct sign_mixture
  : convdetail::get_sign_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                  ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                >::type {} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* sign_mixture.hpp
N+nwLpuosi87BNpd/AFKRJQhnUTBE6F5p/66e/w9Iyev+C9tAVb83Yg4hJ053rQNsDsZRs2oB07owyeVKDCH5sI0DdDtcagv3r8tokpocn+ALTTjObfMV4En0KvTYwvIR3d3sP2JxahfpCmofqgOEe/0O+LqApqG3xr12v9k6qmKxdNLW6Lu4G9djH8yaf/wxhfjOT/D2c2RZ/e8EZ2Nk1yM5qVsLJLnhebXNa9bXRjNcqer2WYYZR8XJtx36nT0sHFofR2bUm6YknLmwg5063BiA9ZDSW3k4McAcnIzqSAEGi+JHYZS7vK8/8xCcgsdS+UzaBOhLCBjvpdKg1cKpQR/ij0csmJt/ZGR7NdtCZN2WN0gpMq10YHxLChREfu8oks2lHZVTVpB79Y+y/cyZBja+8HxVIXOmE7Wg4O9a/s56h8wwrJ4XR1rxxoy0Gccgk5kqo8llwu0cQYHqUx5SD/OFstPbsQmgwE1YqlF0ikLqw+IH27en6YZ5OdPe5hoqgd04hvuOHPxU2h2v1oUMfgRZ+8iw23n10WPnQvvpdDS9JauVPmgfqFyag==
*/