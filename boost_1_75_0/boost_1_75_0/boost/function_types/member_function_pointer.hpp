
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED
#define BOOST_FT_MEMBER_FUNCTION_POINTER_HPP_INCLUDED

#include <boost/mpl/aux_/lambda_support.hpp>

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> 
    struct member_function_pointer
      : detail::synthesize_mfp< typename detail::to_sequence<Types>::type, Tag >
    { 
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,member_function_pointer,(Types,Tag))
    };
  } 
} 

#endif


/* member_function_pointer.hpp
uENcJZwWmnt8seivDcnQZXcZ9myKvqWfM5n1f+M0rP9QwPB5YVj/z5H1HypY/7ssTnZhWvdQ6+EOBSNDq4e8k1a3veBDQfk1eCiwhLc47aHgSByh5TwSvOQpnBQYtzUfEW9Dvn4esOj1d61sFO+OX92QjhzAvNY3A8TAFbGY//rqpmCYJy6MSh8xbNJw7awZmm8XZG09TWDdmWZ84GoBbTWA4L06yJsj04eRmrPSjyCWLUVy8EmljjFiEBBjiia6JbYc9nY7zPOZoWPLyyRQcDO2oGhtNmNLRnHvzIpVJBRX2JBhwQbr5wIbhtL8n6N8RMpdTfERaRYbkidPD/sN57+RFKdiZMP05sfljc57pKshejM3hN7MDUdvlmY0BRvSmzVEb+4b2gi9SV5+OnpzdUYovZn739CbuSH0Zu7/QG9e+Q/pzdwQejO3MXrzyn9Ib9pe9V/Qm5nRDdOb2+6gPBV3NCh/uHtpo3ZED/cNxbvDRVPcZauhOVuxw+0fQBYAOaiVvs+thdaXGElPKlpbrKNS+jYFIRdGNYSQe27Gru24ueHY3/4lja6pd68Mt6bykQ1ZKN5hBq18OJHQFn6kpsPGsh8jKwbEqU6MuLIpnfg1siEam3hzMI2VpPWrxboa41uCvcYmFWwH+jBllbAH8svSo4ofKJsUZys+0+1rBi5KW0jlRYQRtBL1t0j1PNi4LUu2IVhJXjD4uJY4
*/