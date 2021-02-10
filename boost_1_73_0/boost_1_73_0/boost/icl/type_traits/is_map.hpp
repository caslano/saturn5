/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_MAP_HPP_JOFA_081107
#define BOOST_ICL_TYPE_TRAITS_IS_MAP_HPP_JOFA_081107

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_map
    {
        typedef is_map<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_map.hpp
UaXNUYSYPKTrPFHGsIhnWU7BokBAwPt3LNrzkkeoRzl+rSPFW1EQvEUXgzh0okSgsUlg30B58gvlaV4+0UVKGiitreqJdbGB5UdppjqcPiXPU7kL71M53qPcGz2Qd1BxRIzkIYsgbhxYgW0OBjqxuyiRRDkcnxszy7aCW/V89O7jp/eDydIzz63Pv9JJOByfGT7Y3w3HvkmogdRfzWZI9aF7ORhMM+BLUa6jCJK3dUIhLhJBmXI6POIyPc/1hivHXy2XrhcgCZaeG7gz1x5M60zWRUEpg7It8yqP8uR0qHPFcqwAirbo7GqUxNXpkEy7Muxz17sy6CG+A++Eko3jsXvmu7YZmB/wKF/LHOaIo35yOpy5K3vuBKFngvDaJFM+3w6mkZpCgBlDCFz3lBj54+E5/cL1g++R73NZ9dQz13HMGdnXU0Z5lmGVOB3emJY3D33TQ3wgd2lD/4OIyw1qsEQRQmaRQPV5sAwNFfBwbjqWOR9MccS4ijdmLIbzpvf43c8vuUxyGp1LA7K0RhLVaKXTVmcn7eT/knb9XWnXxx40tCcnH0ON2REtTlmLHNHOMITCCzPQUSZCFJ+K3g67RxPjzsRf/sjEFgkf0oLbpamldWhIyKsOBaiXhhdYhh2eW1QtU5orMfKayuSp
*/