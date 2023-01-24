/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ABSORBS_IDENTITIES_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_ABSORBS_IDENTITIES_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct absorbs_identities
    {
        typedef absorbs_identities<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* absorbs_identities.hpp
tduBa3C31AC3CX3A8ecs4Oo8DfXIg7BlCmyPB65obfFUtyxsanY3Nrs956vqAULbR7/5o0f5N4fCAYTTVlHaMfi2jpcne5qW1Lnn11HcDtgXjr+dS3CLGpsbqutVJucAqdtkxyWfEXx9I8GhzcpLMQYmPox28muN5qbhbta/yjCXBOebG4rq+4noyzvaa3gjALd9GvrZPVcH53aFtHUA4MePAe+1tzTxwgO3bRTG5Jle7GaC8wPcesS7lLL7OsPubpz3yaxA/7zrLw3+SIQMTVrmOdMQvzu8kvRZscRa2JXKWTMFY/CCtJC4qVRl/Xf3RPTv15KJLjR3TzZG6TrV1qfMRDyL87UZyo8ziZ2Bd9OaorYCjQPdcS+QYn2so3V0s3cZrw46vqbjuzdd4IsE9O/eNBn15vDTGZ7uoubzlQNy3+wIwgDkTgPK4ZuGcnwyvIXVAS0H8Eup3z/pc7bvEqQIxc85FfJfjmf4arrnRLP5MpScdqEumX2Tj3b/zml0LtVHs6oiN8fB6Rj/a/PZ/h92KAH4I9SH+YWbrbYa+3vXFiN+/9Y72C0KvooKtM31c8mz4pEISts0FeV/6u80zMgHPvD96AvKdSuwT1QTD/zJcZjzP909L9DNnRPNomV2Hd6v0Dp5uJ69bF7QSzwW+o20zl1bGlp0957iKwvo+afn6k34DQ7Mk1tf4E4QLTTwZdS2yYzMw5SsBVz4
*/