/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_ELEMENT_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_ELEMENT_SET_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/is_element_container.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_element_set<Type>, const typename Type::key_type>::type&
co_value(Iterator it_)
{
    return *it_;
}


}} // namespace boost icl

#endif



/* element_set_value.hpp
/sKz8MDpRVP8ppPFt9HPuWpbRxynocR+Cf2J5LIlheSXxjQjd4F9AeEkx/JVnAKLwwvqatuZ37Z6ws2n/DctvsdGh/5lI2y6WLQMJv4SWzJAxm+c7Wix+n41t8f0ZJ9Q+OqBP93GleiERw6coyXa75r3CSmZjcv8BJUSWM/aMtJ79erz3dOYOsL3fQioTRDB9eHJy8xz6u95MqFnty+W/57HHnEchK/dWS1d5WphxsAoE6/X6FtbAym0yIcc1qtrzi1e9maWP1X6q6Aj9ahzwh0rY8iYfexwt6DzJDAx74ZEgJ6t+5Qm/cfJdFQjkU51O8Zfg2JH/gIvlCbIoZQmtQV2nMJf0DVJadZwAWpVCsQ++fpkZXJBjoFTxPXbuaGx6p9630tMh1+y/UyfGFYfEfmfP8b8ybd+gBGQk4U5FewUnvPCrS/oHGAiM3aRNMZ8YK8x5ziMiRAHUmL00VvJNYV/5UEh9E1+8Uaam8+48po4bCDEA2a5+IQRUodSPxAC1FfVoVPjm+NWmJPrf0doa5c22sZXrTUfjHKDyWbuDamdn2G0ZUuS44jG9dxTvtzHqj06vVlw8H261j7tOE61q0F0XXCm0RaZ995QTn0PLrpVkHn4TMnv5F1uu2j2kKmxKtEVnxhWznRlKLwdFkk9fSCX/0mifij7lZN45D9Z0XbyBQt//blKJ9Tr327YTBS/FFDwybS7xD2qrW36
*/