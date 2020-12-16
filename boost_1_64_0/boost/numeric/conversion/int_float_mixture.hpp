//  (c) Copyright Fernando Luis Cacciola Carballal 2000-2004
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/numeric/conversion
//
// Contact the author at: fernando_cacciola@hotmail.com
// 
#ifndef BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP
#define BOOST_NUMERIC_CONVERSION_INT_FLOAT_MIXTURE_FLC_12NOV2002_HPP

#include "boost/numeric/conversion/detail/int_float_mixture.hpp"

namespace boost { namespace numeric
{

template<class T, class S>
struct int_float_mixture
  : convdetail::get_int_float_mixture<  BOOST_DEDUCED_TYPENAME remove_cv<T>::type
                                       ,BOOST_DEDUCED_TYPENAME remove_cv<S>::type
                                     >::type {} ;

} } // namespace boost::numeric

#endif
//
///////////////////////////////////////////////////////////////////////////////////////////////



/* int_float_mixture.hpp
bPVZ14nInayQxbDsc4cPQn2TgtcHg7aueP0KGFuy38IMe9rLsx5r3TTkThaau1uwRDIbLLQ/k8iiYdo7BclKMps6ppfxvnmybszetqb9ifo+savxzDzbi6dgm57O2qK/N5Cb/t5AsneYpcT+PRB9TVaGWfFrTuM92WQ5mB0cnbIBbfnUvM+sZGb9kkCWl9n9jTs3Y06QRcJC75tJJivO69tVGHF+Mgcs9PpSgMysz9QM8z5zkZnl4CY7x2zioecNMH4z7eqlxbBjz58swrjPZrnr70xMMbcEwTxk8TDtnXuC+QVLI0tkOQwfNPQh5stcNu7adVMfWSxMu+YoWBpZJEz7Hm+eeVwCmVlcohCXJFiKUKZPsFTB0oT6rPOF/OYL+QlxSfONMSqtP4NBsBQyG0x7Dyo3/T2oZNGw0G0ljSwvLHTuuj4zt0SyeFjo/EwWzPeZkV8pfR9HFh1mWI2+Dz/DdrTQruaxuMX9Ds5HO7+wq13MvrtS2Hie6iK7+ojZnMR7S9EWstLMNoxJzYd+ITNrp/oP9TVMW+e56es8WTRMez8smVl9SUJ9KUJ9PrJ3ma2Nqrge/bLYvD4XmVk73WTfWQzLOTObH+O+xK6oEFiHh1kmoL6ldMzHxnbe9F9noZ3LMM/ItHeyCmZdTvMMph3bCJZENp3Z7GYnaiH3FbRNw7T7LsjimNX1P/kU4yfEJZPFwrTfYpBhHPT1WigzVSgzTTDrSnNLIDOrL5HMrJ0eIS5ZqM8rmJ/MAQu9phoQ4tQqupYeZthbKwdWRH1r7GqixbCSd77JgO1onR2/mSxJn8eKPLqJfllP2xhMe7c4WQVmI3KWmIv6yHiZVQdUPYC5tIGuuzGr2X9yRsSRRcC057eSRcO0dz6TpTGr3OnxdPTLJromzuwv6+k+6GsyO7N6f3ruoK/JJjGLvFF3Ofpss7m5t5hbmmBeH23vsNDtPZVsNLPcGY8/xDa9NdQ6DfvsD8z5bXbViZn3nY/2IgcyHrfY+fdJjPt2WkNg2nVTsj95fQv23EYOO4zxK6GPH1l1ZlPP/1oMY/QVzTOYdrxLFg3T1mQep+0fPEKZyWRm7UwR6vOR5YVp67Vg1q+pP2Haei1YEhnaqa09ycyK6zmQTbEYNnPGnPuI24V+IdPeuU4WDQvN3c/j9PfpC2Wq3fQdCrMOXXob352R2ZnZux8x3tVHFgMLfc5CEplZ7slkZjl4yXIx+8qRgPpSyfLCtHOgPXa1j9nGaVd+xzZNZhbn2ktjCwsd20Sy3czqnRxqvMN3n3lcEhmvL+v5Cl8jP7KjzC7kOXkftp/2HTBtn7PfGL9i2vgFyCJgoX2dRhYNC+1r6wGag8yaNhqeC/WRLWWWz/P4NebuQbpWyazI5d8boz6yw8xmvVr+EcxvV/mYee63qIpxOGRXLmaOqC1rMA5kvL7D+6e1wfZOxuubeePvObDDdlWNWZ6TLuw71BG6j4zZ6PHDu6A+sgRm+1Z3r4bcyZoxG16/9UiU+Q2NO0w7DyeLh2nrNRnGT1tDkshiYdr5pmA+svTnexd9sw9/uboy7Fjw/uug9ToVOwRz4jhd72FmP/bLLrSFrEyYYdZfh3ZFfidCy7zat/f3aCdZZWb3ay3eh7lLlpfZ5+sWO9GWk3TsBtO+nyaLhWnfTwuWJFiKUJ9PiEsVLE0w6yk7nntehD5bddnRBm0he8XsVZ05q1DfaZovsND5EiCLhYXWp86Ym4usTtAK0+fyCvOTsV6TtWbWvVKTIcgPZZJp945Yz9KaxWz4lbq5MH6aRbnax2L8yIozc1/2/Y5+IeP19d2duT7GiKwYs/CM9W6inWeFdqbSuMO0eUaGOH2ekR0=
*/