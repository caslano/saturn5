//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_CONVERTER_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_CONVERTER_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/conversion_traits.hpp"
#include "boost/numeric/conversion/converter_policies.hpp"

#include "boost/numeric/conversion/detail/converter.hpp"

namespace boost { namespace numeric 
{

template<class T,
         class S,
         class Traits           = conversion_traits<T,S>,
         class OverflowHandler  = def_overflow_handler,
         class Float2IntRounder = Trunc< BOOST_DEDUCED_TYPENAME Traits::source_type>  ,
         class RawConverter     = raw_converter<Traits>,
         class UserRangeChecker = UseInternalRangeChecker
        >
struct converter : convdetail::get_converter_impl<Traits,
                                                  OverflowHandler,
                                                  Float2IntRounder,
                                                  RawConverter,
                                                  UserRangeChecker
                                                 >::type
{
  typedef Traits traits ;

  typedef typename Traits::argument_type argument_type ;
  typedef typename Traits::result_type   result_type   ;

  result_type operator() ( argument_type s ) const { return this->convert(s) ; }
} ;



template<class S,
         class OverflowHandler  = def_overflow_handler,
         class Float2IntRounder = Trunc<S>  ,
         class UserRangeChecker = UseInternalRangeChecker
        >
struct make_converter_from
{
  template<class T,
           class Traits       = conversion_traits<T,S>,
           class RawConverter = raw_converter<Traits>
          > 
  struct to
  {
    typedef converter<T,S,Traits,OverflowHandler,Float2IntRounder,RawConverter,UserRangeChecker> type ;
  } ;

} ;

} } // namespace boost::numeric

#endif



/* converter.hpp
YTpXY9Z2fqF45H7EWM+q0+fy8iOqI3fNZjdZOAS5k1Vm1mdVX2O/QlbDYli2Xv6dmC9Hbeo5s9iYTVb0y/Fg7kHrGTnqMsbvW5uqyGzQ7LSxKJMsK0x77wCZh1nlHhcmYT0je5vZkLJpceiX71iZ2rmMiywCpt2fRVaLmWP4Azu2aTLen41f3sE+zkc2kVmDLZd+RQ4naH8E0/b9ZLEwbd8vmF8oMyCYOmlepkswt2Aeze6NHnwf+ZG1YFat3uHlmPNk6c9yrkb/rp+69RAs1YbnR1Z9k1PrhWNR5vc29T2zaqv3ZsS2cs6m8jHbXnJzSfQZWSyzJo8LG/c6kMXAQr/HUz/QnGCW7Wyexpi7ZA2ZVVw4YRHmBFlHWOj3eAnnbSrcYlh8iyo1kd8FfOdGFvqdW4CsMiz0e7WEi3QMBgv9Xi2FbCIs9Hs19yWb+pRZ98eXJ2IcyOKZLXg8FuPgusz6U58vZJEw7ViYzAHTnvVIFgHTnvUolOkT2pJKtiM4z6rQvyu8yPYX6rthU1uVYbu+zJcH7bxpU6WZXRs2pQ62TbKssND1xcdN+921X7Pdj9aWQjs161l3WVGMOzf9N02axQamGvcs3Aq1OV1Sw7FGctPvYSXLx6zThRWJmPM8Trvm4eGmXbdJ4qbt35O5acc2Kdz0a0ia3X79px3joJllz14XxkGzG1HbCmMcNCua40gExoHMzsz54lKjoBGGxv2x+kR29DU37XjJxU07tkngpl3PcmtWo9W/eTFGmrXf9FMcxoibdj0riZv+Wz2yiHDDVp7d3A1j9JNNtWRxjQv3Mb7ju2dT9S2GFaSDTIzfz8FrF0ELy9rDuBeOLJLZd44jqzEOZLmZ/ZZr+1L09X06DmE2c9Yh43m/ZLy+mysGTES/aHETnpQphfy0uD0dRkzHPNNs0Ryv8YxdshrMJhe+Vxzj/iB0LvXJ3/4K2knGy6xfZd1RtFOzbYUuG/tbslzMdk4o2AjtFOpLJXMw21f0d+O5OFqZrg3PuiCHh6FxCVteHEMOZGindv3Mw027dphMFg0Lfcefl6xfuGEbz8033suWZlMVLIbZyiX8jbn0q03ZFCzkWasBsnhmy6I3HMFc+o2+E2b26K0rxvtCyCaw+vIufLwZZT6jc4QshpXf6e2G/GgUpijD+j7uUBI5WOyqFLPs1zxx2DbJHjNr2++vvuiXMLvKGmbYroiUWygzo11ZMhiWpd2enkGjf9hVCxZXfP/5rcgvq131V4aN31d9AXLIZlcHmFWJHrwd7cxuV/0shjka/F4AcyKnXXn5vrFNrVXoa6tdNWNxi3o++w3jF2lXx/l+039rLSzKro4yu3qDPVMt2q6uMyte6NdYjFGMXeVhNnli1wdoS6xdPWU2r3yBa8ghzq4mMDtjWWAct5I1Z7b11vVOmPM2u7rC+trasV9dxDnt6jXLPWZHp9noz9x2dVkZ9soytQ/GIU/oOJzZ2ykCcXnt6hyzc3FveRHnsis3a0vkmcX9se8oQPWxttz8fWoZzLNC1GfMirdc+Qh9VtiucjDzjSk5HW0pYg/Zjqo/9lRBfUXtIcdg2+dH1cLcLWZXxTMYZv/PXwFYKbuqzuJeVP52D/Ij683aUrF6aQ/qS7CrGSyuZOtNxm+ky9hVBIvb/2UGI66sXQ1idjnNinXXVd6uVjBL+2lGfbSzol2l8v2Ys8lYzKVKdtWImXfvXRv6mqwOs6FxJYxjjco0r1l9A6tkPIV5VtWusrOxffzh4Y2YZ9Xtiv6PsDWb4s/BatjVMWY7Jm6cCKtpV2/xtiQeW4q21LKrSJh2vZUsFqadIwhxHiEuWYjzCnF+IS4gxCm3ubnc5mW6hTg=
*/