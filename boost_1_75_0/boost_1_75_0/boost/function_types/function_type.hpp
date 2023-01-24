
// (C) Copyright Tobias Schwinger
//
// Use modification and distribution are subject to the boost Software License,
// Version 1.0. (See http://www.boost.org/LICENSE_1_0.txt).

//------------------------------------------------------------------------------

#ifndef BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED
#define BOOST_FT_FUNCTION_TYPE_HPP_INCLUDED

#include <boost/function_types/detail/synthesize.hpp>
#include <boost/function_types/detail/to_sequence.hpp>

namespace boost 
{ 
  namespace function_types 
  {
    template<typename Types, typename Tag = null_tag> struct function_type
      : detail::synthesize_func<typename detail::to_sequence<Types>::type, Tag>
    {
      BOOST_MPL_AUX_LAMBDA_SUPPORT(2,function_type,(Types,Tag))
    };
  }
}

#endif
 

/* function_type.hpp
1aQR7xBVuQCLhyrkn7jMisr+YT2ASy58kGzu6JqGF23oGm3yYm1Bfw73PYBBhzgzEi1I7XTtYF0US3t0ErcapGDBkf8x2gmbSwog/6vtqMtqahjP/pQEb2+w79Vk0Hgugxakogya5FcGXTSfBLlbX+LyH//9NH/O5M/J81HCK6DHg/S4nx4j6DGUHk56DOQf/rkAf15Pb5P428T5ZPu3eQH9juO/Vy5AsXOz/CUveH8hfreYHkfLuF1xGf78hR676TGLetrC6zzGW/iW/ZZzF9KPkfBSHs6LbuNvBy5Q4x/wHG+am/SdR7qprpjovHEMjXKTJ+m8om6eSNesabjC7VA8/f50LIinD/8LcqntnXq6Zk2Tv3iErlnTFNvBx/iFXJq8fhh5RaUAUqUAQehaqLcBSZFO24VPFBgw5Nnd3eFUvYEMXCGUJEZ13irMPFyql2V4cbXCqoepJh9pmskH9rTkcaHPSKNrar+umVf013yg4zOlx1NUH2hCpOHzeEz1eX50ABTqLDTssKoDSEMzYrosygRT1ZOwcUlFyuhAEG2iIsX2fYH+7u7Hh710AQTsUacQ2H1PI7Cv36/TBdwyUa8LKCzQ6wIGD/V/d/fGpEB3d+kpq2kRJrYnJ5QCuiZPfOqUkoXXcKhFugB/cr0SUZV6QVXwMO/fXi2QeUHZQn4MJ7QnZScl1ME69Cf7uACZT/OcCPxe9YvLkWNn
*/