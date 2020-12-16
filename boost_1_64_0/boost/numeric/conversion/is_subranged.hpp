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
SxLiUoQ4H1lE0PLo962RVWI2bG/ZcshhqEPVtBjW5eDcMKwhw7BNk4Vu036yaJh2vzdZXph2Hjecxh2mfcdOFgnT9o1ksTBt30g2IJjDm31P9uEZT6OvRzrU+8qwC4uMd6+lkkXCtHMZslgYry/Kah1lHCfn4sfJZAlksbDQuEQhLkmISyGrwmzdXp8z3QJktZi1nVPXj7aMNo9LJhvHrNmFGtfTzTXGPC6JjNe3pc2YT9PNT3aTWZliL8qjnWPNy0z4SGgnmYdZ8pdvlU03Nc6h9jKLy7ptULqlkY1kdnJpuaXoz48daiCzoT3VcuSe7FCDmOXseq99uvnIyjI7+Guzn1EfmZ1Z+5EHvsB8Ge9QZXh9027cxJwgM4tLIuP1WTr9px3aQtafWfHsM2enm3sCjZHFsMeNR59Jt9SJDjUzzLB/h8w/gf6c6lCULGxVbtt2tIUsEsa2FbIUMrO56xMsVbA0sjHMun35zxPUN82hvmHWeVvaM9gndG7Bcr+T/yLM86kDz1uLf9NnRTtvQ5/NoLUug2ErIjxXMSdSsLaSsbWVLEEwt2CJgnkESxIsmcwGY+s1mZcsGsbWazK/EBcQ4tQc8zgXmVmcW4jzCHHJQpxXiPOTnWe2LOFmWczBubSvgrF9FZmaZ24JgnkESxHMTxYPY/tGsjTBXPPNLVGwZMF8ZB9nMOzF0wdDsZ59ETxnDtqjfQcSYYsc6hSLO74rbhr6eolDjbUYtubLTF+iPi+tL8zK3mr/I8pcTqZgIWtPAlksTNvfCpYklJkixPkESyWLgLHzcLKAUJ9aYV6mSzC3YB4ys7YkrRByF8r0CZZKVjU4fs43cyJu3TG0ZZVDFQgzrMoPL9dibNc61D8srmy+8igzZb1DPVCGnc7+3jfYVjZQfrDQdTBVsABZU2br+w37DP250TwuUTAPmQ0Wui4lk0XDQtclrxDnF+ICQpzaZB7nemMWNg4lXi9BOzebl+klMyvTTxbHyqzd5mwA9fmw1pGFrnWJgiUL5hMsQLaZ2ZaxkaPRzq201sG0tVUw1zZzSxQsmWwts5gXd0tgvmx3qCnM8sZU24/tYQd9Z8Ps18ufDURbvgp+fxS0jvf/nYD8dgavMwTtdflGpbFG7sb2Tha6vSeSxcK0NVKwFLIIWOj64hXq8wtlBgRTe8zNRWZWn1uI8wiWLJhXqM8vxAUEU3sd+G2Sgz77VX8yCX1NZg+OrZ3+drByQWPu7gt+dx006yfvVEc799MYwULXLB+ZDRa6vaeSRcNCt/c0sryw0O3PdYC2B5i2rZChLdp88ZBFwkL7M5ksFqaNg2B+wQJCfeqgeZzroJGDTT8PEMwtWCKZDRY6Dklk0bDQcUgR4nxCfX6hzACZy2LY8h3FqqCdh4JjG7SucV0rY4zIzNriJavBbOSasj0wl8hSmFU7UWsccjhs3s5UssbMfN2rlsc4HKHvZZillsm0H/WR9WLW2tagG/r6G/McUsjM2uIjywvT9keCWY+am1uwJDKMg7aNeQVLFUwdM7cEsmlBi6PPSv2fpiA/spnMRg4+NfX/VnJ4ynHaFwfnUiz9Lf7ak9Pp5vuOrqWHGda0h6VXuiWewtwlY3OXzCNYEpkNxseP2kIWDePjR20R4lKFuDSyvDA2RmSu0+aWSJaLWab1ExelWzJZPIyPA7VTsAAZ+iW4tqKdZJEwttaRWc/QWgdjax1ZgmCJgiWRmbUlmcysLV6hTL9gAWYx9LnsyivcB6jO0noWtGj6nFpnYBZcnycbwSxfyeqFcF2YbAuz0Uf6PcN19lSHKsdswM53n+CaMVl+WOhzdF3fO9RcZlX6952J6+VktZiVW3NrNdp5jvY=
*/