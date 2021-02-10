/*-----------------------------------------------------------------------------+
Author: Joachim Faulhaber
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------+
States of comparison and inclusion relations as static constants
+-----------------------------------------------------------------------------*/
#ifndef  BOOST_ICL_RELATION_STATE_HPP_JOFA_090214
#define  BOOST_ICL_RELATION_STATE_HPP_JOFA_090214

namespace boost{namespace icl
{
    namespace comparison
    {
        static const int less    = -1;
        static const int equal   =  0;
        static const int greater =  1;
    }

    namespace inclusion
    {
        static const int unrelated =  0;
        static const int subset    =  1;
        static const int superset  =  2;
        static const int equal     =  3;
    }


}} // namespace icl boost

#endif // BOOST_ICL_RELATION_STATE_HPP_JOFA_090214



/* relation_state.hpp
iQOjtRo9U0jTUYNvWXaqsKqhpf3n5hdTbjiqcatmxFKmsK115SXhhU5fFrWuxNSSv8vKgXJ0GUsZvgJLcy6plutcayo7ujYI5mHEzi7XI+K5I5HOF9x6lGX0wI42zEVZEkCVDRTZJdqouP4HJd+QWikwphYiYXjO4liID5AWzy6XEW5idGXgntGyblXD1JhIpRJTvKE9UxbxXkb1pd7SilTLY46qDnilmMOO7p8bciBlVqcFQQdNPjtJ06n3RRrvOWaqs2msFvSjAI/Lr4jfAvx4KMhqY7igaF9neJIE3djAjz2oDPPd56pxfYia7OFz8Tevfwb8PR8CGgeRPjihO3oiNj+jirlIV2fJiuHN3s5GOIK7nJn0ERPuGqFOwa9gTgSaR9mNMYc9z4KQZGN/rgehnb88pYjvncne0vOq4iUbc75lJT7CwzRdD/lXndps/V9v6Vl9bpb1fXpxgRs/1fnhe7n3/vCeOeDyECnZJ76VsSsmbCym5yh7hnrarEPyzCHwwjYJsEw2iFp1aFs827RQG3iaG6v579eJNDfM70wrsGG7pRYZnUCPxDO88oh1owBD1q+KBLJVIQX7e5gAWkoWwglzSR9LE1d1rissX3HCMl60MrhbLPylpw5lxw5zcpAfQVzFZ6NEfnbC
*/