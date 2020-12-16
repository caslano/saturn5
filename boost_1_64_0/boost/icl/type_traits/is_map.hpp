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
XuFg+NZbeW/det096QynTJk75Zce625nuGtXk13Ndy97iWHv3mt7T7yyYA7DhIReCfldO0xj+PDDvz38Qd7F+QxXr35qtf/Uc3cxnDnz4ZkXv/VGB4aLFvVbNP2+jn9m+MwzLz5ziVY2guG55/rPfWXgU8sY2u2j7fPyHcsZfvfdj9992+T7Fgz37Dlxzymbr3iX4ahRP436cvucVxk2a9ahWa+2CX0ZlpVdUvbHv75YzfDjj5/4WHO/fgPDnj1X9ezxdG5jhk5nJ2fqlPkawyuuOOWKpFtOvIvhXXfdedeERu4fGM6d++ncl1b8sp7hddcFr3vn1yFZDPfvz9h/1Z8emMTw11/3/HpF8udhhl999aevus3a8gLDOXO+nLPj6p+eZlhauqi040d7ZzF89133u3deddeFDDt2nN5xw/h+DzHMyGiU0XjsVS6Gt9465taF75x+KsPdu9vsPu35Ja8x7Nv30b6VN06bwvDZZ7c/e3VNST+GLVp0aTG080lnM3zggaseaNQt436G06ZVTvus/6PrGC5YMHhB4LHOXzMcMGDvgEW/lz7OsKTk6pKzv9k+nWHjxi0b2xOatmN4773X3DtsaNa1DGfN+vOsh+7+8D2GO3e22HnSS1duZ9ipk7fTzrmpLzPMyhqWFQlfcxbDP/857c+X3vRQEcNvvvn6m+f+8HMKw48+uu+j8Zlv383wnHNmnfNhn8efZLh48amLB17TeiPDm24quGntzt6jGJ5xxsoz+m7KPpFhaurO1Ct/8T7LcN26X9Z9Om7uVIaffrrg087nv/QNwzZtRrSpHnDabIavv669/tc7nxjAcN684fOiT/3hO4abNm3ddOMcT0+GL7zQ/oUz3rvsc4YDB+4b+MzH5UsYZmaOzLygcnkqw99/f/v3+7p/VMjwggu+v+DHZd9dyXD58guWf/fZSC/DoiJP0dZRm25h6HDMc/xh9eiRDMvLnykve31fG4annlp+6r7IwN0MH3xw/oOdkpxPMHz00c8e3XVe5VyGhYU5hTd1uvtFhtdeW3XtF38562KGXbsu7tr63vT+DL3eK70tPt1ZwvDQoY8Ovd3u9z4MNe1l7dnb/7qXYbt2me2WT+s+n+Ho0X8YPfzceRcwbNnS0XJ0L3smw+eeO/O5SZ/cfB3DL7644YsBFz7/PsO33x7/9vXL78theNttm27z/LFoM8Mrrzzpyi4LWlzNcOTI70Z+v+uCnQxvuKH0hr2HBpzD0KY8L73U+aXBry34meGZZ95/puuySUGGVVXPV93wyBcfMJw/P3W+d12nvzJ8442L3/jtnod7MezcOdB5/+zBzzF87LGvHttyzuwow4ceuvShtr3TNjE8//zHzp/9/mt/YJiff27+U61Xf8bQ5TrB1S778skMv/3282/3JP46lGFy8ubkWw7OeIDh11/f/PWZ0ee2MTz77MNn/+W5i95iOHFi1sRruty7g+Htt6+/vcY+9W2Gn3227LMmvl2fMvT5lvjafLH7fIZPPfXKU0+W+5sw7N9/Y3/fteeNY7h5c8/NuX+75SqG771X9N6mS26bwbBLl3CXA4Ghhxn+/e+v/v3pfn8byzAnp3dOgfemPzK85prINR8fGFbFsLJyV+WyjZ/9wrB588Tmyae1Gszw8svbXd595QkPMly//pv1P4+uGc/wr3999q8lU19exPCkk4aeFB7c5SKGf/zjnD/+VDLqbwyLi68rHvLjtokMX3tt9mtfrXlsOMO7777p7t6pOZcwvP764uu3fZdSwPDnn5/7+ebhXxczfP75Ac+X/nDDGoY9eqzoMejhcXaGU6fWTP3Gsf4+hgsX9llY+ODJ+xhGIq9Hnrjr4+c=
*/