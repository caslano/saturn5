//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_COMPLEX_FABS_INCLUDED
#define BOOST_MATH_COMPLEX_FABS_INCLUDED

#ifndef BOOST_MATH_HYPOT_INCLUDED
#  include <boost/math/special_functions/hypot.hpp>
#endif

namespace boost{ namespace math{

template<class T> 
inline T fabs(const std::complex<T>& z)
{
   return ::boost::math::hypot(z.real(), z.imag());
}

} } // namespaces

#endif // BOOST_MATH_COMPLEX_FABS_INCLUDED

/* fabs.hpp
OE0n4jScgbO2+1ab2Vk2h+jxbYzrw+OFJCCcIVv6nRmHcwibxhY+5OT2j5LyJftvKtvJrdvLMLf991vsn1+tszZP5WwxDyTwfIXtK6KbIhAaz4Cysl0kZWzGvKnPssfKin5qrBVqKt/1Y3R++CKN02mIlcceb6fZVJJ04HWg/gLwkhLtzfg9GcKeFFiHBuDszVOdKnxOVVsMLVjc79l/rAXnySm56hC5g+iRsgUtFoP0zzP/YDZf/Y2NRjDf7USFl3z0G9sKO+XwPApmvwFwCVGmfQj+5j++KzvYdENgsyp4YpTbEsgkkjjpkTdfHc7G9lhUf7K9nzY93c/sgqvu8JKYCy1LIcSQ2ImS/st6eeUzeueAQU37jv3vu2zcfWJ1OsekR2gdOx5Zf7TXdLKdep3gcfOTEetrDS3Ejc93L+lxDixH/vDW4/CSfrRWRtcUf5M684/wfCdId8mlOWYpdqupKyWtgjW6iUKWb07Q+xjaga6f2J0pyT265Ck/aTx4+7Kj+WEOdc8aIOw30bx1lBsUfwb4Oll6wcrzb5nyr04Enl3bB3VgV+L4zuTCwdqaJe/nJHgHtPxSly4HfDVynztRlMy6FkFUcjTyNKS/06jHFwf6Npfgzp4Cm8o00SETiRItJWwLZ1wG9a6dfsem6+zVetML6qBzwjiuoze3ELfEGWmospTCKf1Oww7EJihs7XH8LDGgxIhvrWOc
*/