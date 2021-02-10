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
5mVMj+jBNMo81MW1kZPMQXjYhM7e3i+wDbvt3XYER0xJkcPQCTUWZhLBC+49rzM2n+9Y8WsEwgHLd2qoUSYtWJ26GTMC8DmXiVBWcGAWuLCJkWN8kQpcJiCVuYDD/tnFyenbCGaZTDICudYl2EyXOYeMXQkwIhHyqsIomHGgU0xHcC6tQ8DSSa12sLYAJ8zUEgaVZ7nVwK6YzNkYCzEHmXOF3W+1ktLkyL7FdWJbyaL9ncxNl51cIIkpuwZdOHAaSisioMgIpprLlO4oCDqLcpxLm0UrNlhK8ZY2YEWeExbmSWEr2gKGtTwRhUGBjKWjm9XKUqlZpqdrgagjoaSlUVgIdcAgrlHmCErFhfHBvvNFiVpTL/BXl2bFl4NWSAaC7hBOhgGMmZU2gvcno9/75yN43x0MuqejC+j/Bt3TCwJ7d3J6hEsvsZgBMS+MsFjcgJwWuRS8rvntrlbjO6mSvOQCAicsLlXQuOeaiikX43Li3VLhimFMmGTMwNb5oNds3DQAV0FZh4pZOVHYsv/KPnyEl3DTnu+mEbTnz5i3Y28Tb7m3wts0ajy4zdrzvQ4Fsl2y42dkkx/J8p/Iip/Jps/vDhDnEIklmtN4W+RAr8dx/x19qogXzqD/9LzXIx91hcvyl1i86NLlQmFE
*/