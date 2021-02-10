/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_CONTAINER_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_CONTAINER_HPP_JOFA_081004

#include <boost/mpl/and.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_map.hpp> 

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_container
    { 
        typedef is_interval_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

    template<class Type>
    struct is_interval_map
    {
        typedef is_interval_map<Type> type; 
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<is_interval_container<Type>, is_map<Type> >::value)
            ); 
    };

    template<class Type>
    struct is_interval_set
    { 
        typedef is_interval_set<Type> type; 
        BOOST_STATIC_CONSTANT(bool, value =
            (mpl::and_<          is_interval_container<Type>,
                       mpl::not_<is_interval_map<Type> > >::value)
            ); 
    };


}} // namespace boost icl

#endif



/* is_interval_container.hpp
1DEtA3wyNXt/l5Bu0Rn4wASY4gPcR3mSt+DW9KdO4MMt8zxm+wtwxsDsBZHdmLaBqU/QWAbxj6csztF4BsnmaZ3Ey9rm+4322dnHpyz6uolQMpt4g8UYRuvk63YTbwu8lGOdHCC2qYo5w+7xutj/n4H+IF3dmS6m70P3bqOiE4YFYxLYJN7GWURZvv8Jc3Z33u3CDPMVfY1h3rk873Qo/b1zwd1zrdMZQrf3udf73L+86Ix+m3f+lAsO85kA7nmOhxVrcAHM4zDhNveYzw24XoDPbqiOmcs8n+aUMW8EvKIbmxbH2jTADXy/nGFZOzwPPwG3gxkIPxiPwbR9B++ZopzVOuadzCy9AHnhoowmGcFpusdL/8aeM9sTlXI5vtgZF4JNeBtJkI7cwiWobIEgv+nm2OP8lkJBRn3HsRQ6NmGmLap47B0rzeNvbWa5U9a2mD35l65jYGczDMzF6VS826joSj/INX6nc9c3HZv6RpUH56ZVZgYvEKKOS5V35h+lK5nKEhF8zj0T25CFHyiQxy297p3L8UgxZhgwIyS6Mba5qalPKRMMxNTxfKw/zK3jzV5jO0Vn6owcadUFTgsjDwWbcbDxB1oR5ZWjdFWUwLERZ9r4rVuBwdtV0delUwcNAt+0KBqY3YBZWNtY
*/