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
eAD11aT9JrMCl1I3Yhur5VSVlGF/9GuZgLF1O1VhZs9//f1blEnWh1n2Gd0LoT/JHDDtmX9kXXncmb++N35j5FSfsnbG1PQZv9GsG1rf49/UvyiTbEcYy/2jP6si7l2nGs7i8tkOfozxI1vN7NyGYcZ5YwOnWsvsUY4eBzCXGjpVKWY/hkWWRVvIBjJ7HfPrIIxfI6eKg4U+dzKFrA2z6iNm3cU4NKZthVmHSZ3qIAeyCJj2fNMmTlWC2cnV3z7B9kf2MbORpy4/Qg5kDSyGJU9qcgLbWLPQds6u3aca2kL2nPf1J9PvY74k0nEWK/Pe7N9yo77mtP9j4zer0f3dKLMV7VN5md/O6mz85sep1jFrPvnuAIx7GzreZXapZmv0p6ctHWfxMm+tcqCd7ZzqIrOs752/hT5r71SjmH3wacl2yEGzYqkPjD7r4FTHeJ9tzLMd1pGuQTCr9KRCJOZgJ6dqajFse9XTvZHD+061nsU9mDfmPbSzi1P1ZnY92yvjXYtkJ1mZ13b1mok1qxvWHjLtt8dksTBtzSKLgGnPFBXKTBbK9ArmFywg1Ke6m8e5BHML5uku5CfEeQXzCxYgc8BCn8GuejjVeGauw1VwzuUjq8osc8HCjRDXk44ZmC36p2M1jDvZdmYdV+3YhPnygVM9sxhWduTHyVjPejvVAma773qrwvo68e6uTPT5Tr4S27C9k5UPWkb6PDYu21GMQz/aVzHbuT1DTZRJ1oJZ1KHbl5Bff6eqxezC4LP3MHfJVlkM63t/ahvjd2DB8+mgfdhqrvHcEbIYZgn5OtVHDmSXmE1WV/ujLUlOtTKDYbnzlziDHIYGz8ODFtk+5w60ZZhTTWWWLUNyZeO3Qk7VnOXQ7lT1nzCXRjhVD57D2W5Z0J8jncrNbFmLx7nRFjJ7mGH2jy2nMSfG0LEGiws0eboAcWQ7WFv+09RSDW35yKlus7gW4fHYHwXGOdX3zBZmXdgP/fmxU01hZT6buj0acePN2+KeQPscZpcquqKwPZCNYTa4e6FKmBMTneprVt+DQ5u/xjY9mY6lMhq2OTBiH8Z2hlPtVIbZ5hUaiRzIlrEyvb/88B3iZjvVl2Esv52XJqMtc2nbZHHbGw1W6M95TvWYxVmnZziGfeMCp9qqDKs5bOGHKHMhHWcxO33lx+doyxdO9Q0rs+DnuTYg98XB85yg/d7lXT/Wzy/NxyGZ7GeWQ4u1syMwfkuD15eCluPJJ3sxr720nrG2tK9dog3GdoVTTWJx37QpWhB9TTaF2dzIL7DWeVc6VWZm3416/jnmBFl9ZucP3w5HW1Y5VU1mFzK9vo5tk2wis8NH/umCuNW0f4Bp+1SyWJi2TxXiksgiYNpzdIU4r1CfX7AA2b/MjqUdHoZxX+tUGYMWTp9t7hfvhfzWGmVmoM9fMv7TB/lp9uXz8TOQn2YzOk76AOuLZpVjc36J8dOs6O6IEVivNevYeNhczBfNGv2cNBLjty7UhqRGHUB+mnUfa2uF/DSLnNV7K/LTjB7qZFwP0WxH/3te5KfZKv+dRshPs0tlF29BfpodW/LFO8hvfajd61D0BfLT7PmfJaKQn2aTw1s+R36azV/bxtivaOa6d+Me8tOsTKPL2ZCfZnV3rXmA/DRrEbM8A/LbEGp9C/iPIj/Nxsw+Whr5kU20GPbWxm+zY+3ZFFwLgrYivGcb5EeWl7fzaJ/gucWHyk82KmhhqpuaMasznqXQbrNTZfqfuTxdwhT+88beF6yHYH0FSxJsuGBjBZsg2DTBZgk2X7BFgnkFWy3YRsG2CbZLsAOCfSPYCcFSBbso2HXBfhTsvmBPBXsm2CtmXTVTW8wtk2DZBIsSzC4=
*/