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
IBTrXGsolpHkJoH+8Tu56cpgJS89Y58s3fdDJ+y+LmtFJa4uRxeXczG+nV+LfDa7Fr9GeT4XV0mfV3VNbxdkg/eLBAMcDNHdgoNzh7hx9jcV4f/VQjzh+WLUPedDIhleIU/iGIchTzjqIGKvch7HQhwSuo/e4iOLyHsRhzzDsIgc22bn9EMVcDQ+xsezs0/4gNOT05MUF7LWZLAIVK/IPaQ4V93Mt0put0NPX1NQgDTDPVVeaQ9vy7CRjsBjowuqPSlID0W+cHrFL7pGqAilNoTx7GY5mf5Isal0UUWSnW3hK9sahUo+EhwVpB+fORrpAmzJcCZX2gcmbIO29ZC1CYHc2keOKC+Nt5CPUhu5YiEZUIXQ+M9ZVrTOsPtM2cJnxcv2h1VY/93Jkk2s5Q62CQgWracUsTLF2ipdxswN4cmmXRntq/TVDUvVKrMOnoyJXIzT5J9tExb79qSxDA071iEmb2sfpTaVXf9TyH2MLGXrahbiPnCRstzmFC1/Uq4r7nb+IrHvadfgN4/m1a+CrdkMeqMFJoseVtJrn+Jukl/NbnPcjebz0TRfYvYdo+kykv2cTC/46DWLOdC2ceRZ3EGvG6NJ7TXfL7Kkr+vCtIrQC9Ya4Sm0zbDqJYmuA8qN04HEVobgjuKPA4N4
*/