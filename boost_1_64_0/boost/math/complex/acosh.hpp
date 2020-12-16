//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_ACOSH_INCLUDED
#define BOOST_MATH_COMPLEX_ACOSH_INCLUDED

#ifndef BOOST_MATH_COMPLEX_DETAILS_INCLUDED
#  include <boost/math/complex/details.hpp>
#endif
#ifndef BOOST_MATH_COMPLEX_ATANH_INCLUDED
#  include <boost/math/complex/acos.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
inline std::complex<T> acosh(const std::complex<T>& z)
{
   //
   // We use the relation acosh(z) = +-i acos(z)
   // Choosing the sign of multiplier to give real(acosh(z)) >= 0
   // as well as compatibility with C99.
   //
   std::complex<T> result = boost::math::acos(z);
   if(!(boost::math::isnan)(result.imag()) && signbit(result.imag()))
      return detail::mult_i(result);
   return detail::mult_minus_i(result);
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_ACOSH_INCLUDED

/* acosh.hpp
HrhP7jvypI08krSZ41LizL1gnPN0zrFI7plxCf9ed1p0np6Av13Rebqf5illHp2ny+LkaZclT6sGRefpd3HytMuSpw159nmaNi12nnYlmaekLSpPiXNUnhKXqDw19BZOTLNf8yiYFpanSempdB0QW0/lc5v1jhsCaxDh4f0lPZUMmzn8jNGMl6aZc3gjHOkXMmL3C7hJYu4+LYm5+7Sez90zejB3N/Lm/T7R89opI+hPpxnzWjNvuu0zfdMSn8/6pvV8Ptt39RU7n0123rq89VQukXnrcc0Hjr7shTt3Xnfvdyse+fVWf+/NW5f3/NTRU4mYz24VW08l1/KNjw61t7ra0298mPM2YJ4TuRrMgkNgvvW8SIt/XXH8G6b+DVf/CtW/EerfSPVvLas+y7TYejQ51vmsMd+OmV6dz6q9wd3Y86m9vBj22nSeWoJ0jY4/R61uD85Tz76L+c3d8eer7UeFz1kX3dW789Yld/27564Z7YQZR8emuD2xeWy8Oey89uU3j01W16azPTSf/bi9Z3PaX9vjz2uz7iYtsOP61OU2v012blt5d2Lz2yxehi1CpiI1SAsyH2lfu+dzWsckblbM/N+3b+3Bf33/PzC/n2Ezv98GMb6vedPG3N8yNE+onLb5zta94uHZAbtzzbPem8XuVJuxq/rDf8Y3/X/KDQ46D8hJ/PvlxviUcPndmRv+XWyd/5+t8T8LuZQ5yNKI+Fu/VY4/mKZa+e67puFrsX+0awT/Br5978ezTPzekbxK3cAz0jPKM8Yzku/fZ2XHTYv1W/ZXc/00npdgpyUrkfPv01cZFBw71DY1Wc6S78Uxd7J7SL21J/SsjK2r1yz+9veO2puqjrlol82Gnvtm742tnT0hGUPHGOv33tjacpa8tI0OOBrR7zZqe5f+hGeW7zbqGNcNR0Lu447pKVwbrgrHwEJYBNeG68BJcF24NVzP/F6mtm9t9x0R38tcRcMZCBEZq+bDfFgAV4Uj4GA4Dg6FE+AwuAFcA86FBbAVrgnP0udFMubt/hyJ+Psxzl5M9F5M8vswy2MPJpn9l7TS/8a+S7Lj0kTGpIVjPK7JY5zxp2Mc4xjHOOa/a1bM/L9h/8a9//r8P7B3eA/z+8J+zGtdAT+rfHvpvv/OhYy1dV5dHOO9+qzgvLpi22263asss+5VpkXvVZphtcUIqyAY1i4aWMJhFdiGNUDCmqWT7g+Q/sj7yC3kR+cWEpZkyJ5j62WdoCy4L83BCzG+G7dFaF/uM9mX23P/Rj/x0DWFV+X5i64t+fd2xG6/zuqH37KXmad76C/K83dcW2D7ViRqj9PWj2b/wb5asZtlsZuldo29c598Gy+wsFMViLjYH2ixPzDC7x8ljeSo7j3mW+zmW+z2D8YDE8jHUvFz06mBZ7nGni2mwb+fD/c8z+ZJujy/mXQfLHaGiR323BslLySst8X/Z1xllOgNSMhes8Uv9lrEr5nM17z2/rM+k+KSNRnbdZnMGHoA1AdSIPXB3COl3Lkn2WfuCfuNPWF1m2Xc03JBX0DyhPznXij/sSvpJJ+5Tz4be8pad4vTo/f0D2IjqmtKqO7qMl1C9Rd3dmVrV0+xm5zOhF1eWdNlbZPLVM/9QvXoAuT2wLsZljZZP3bPyDRxXUZYhr21zfjqPTNtBWlm2zTXLA+Q5xvYpjXL0kb84tYXLLgYOgZZ9m1E4pdlPq+ztkOrG20re1JhcKN13S/Px0W1Jbx3nSzPVo1sJ1LXAxlaJM/zyIcUs/21yL3RXGOHv8rkOsXMw43k2hfVpgx9mjx5frZrMGujE9PxjzLbpZD0pxT2yU5dmYXRnH7qFnsUT3OtGd9NxO0I9dtcezU=
*/