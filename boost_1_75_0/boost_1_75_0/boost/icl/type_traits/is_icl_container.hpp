/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_ICL_CONTAINER_HPP_JOFA_100831
#define BOOST_ICL_TYPE_TRAITS_IS_ICL_CONTAINER_HPP_JOFA_100831

#include <boost/mpl/and.hpp> 
#include <boost/mpl/or.hpp> 
#include <boost/mpl/not.hpp> 
#include <boost/icl/type_traits/is_element_container.hpp> 
#include <boost/icl/type_traits/is_interval_container.hpp> 
#include <boost/icl/type_traits/is_set.hpp> 

namespace boost{ namespace icl
{
    template <class Type> 
    struct is_icl_container
    { 
        typedef is_icl_container<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = 
            (mpl::or_<  is_element_container<Type>
                     , is_interval_container<Type> >::value));
    };

}} // namespace boost icl

#endif



/* is_icl_container.hpp
b+XUtu4KcSNLIYM7otQ6rzexBFShNMKU5NHlffC5LWMZ2CwGDb0pYRr77YH1PfYXPMpjaZcqTOSpLV4vCX/Nx9cEX7eSytvEfbp6WWtH2R7zffDrZnHh3wRu3pdDfVjPw8+W2+5CnWzcpWah1PSZ6VesL2rOom7n0RsUF8GeQiwCLDajVS98plmKOzxxwQPu36pvxUwIPR+C7JJvK/5UEB/EuC2XsjGElG8KhAaLMDygMVZvRXI0mmkkLDrSQqWiRKu5LtXJ7qb633j+gyRGDb/8jE2RnFG0d9wlRoVUbLcyEvpczdnbQNRngaOhbO+O7jt33S4MCikdefNjcl9i0/8gs+PSR6j+E5b8tuSUQEqlhL4dlKu9xfp7nsP+jBCdE9nxiRdp3me1H/Ju2+cWvXG6Ua+9JHrKMqw3NGZeQHxniAS3chj2Nq+1feSg6/eyR2qYa//m8mWF295wvV9TqXliO/FB97gkGgCrgTnIxRcLHJ6Nde6i3ngu7/uQidA5Dnoh4YzcESey4Eicguaj90TYxHhMQXo94n432TwZVX4DRpyF8frPmg7tMTG/9Y1UP4Onzr61JLUBEAbQNOxp0k7EdvzOizTA7Djf632K2W9c1ivoHR4aJxIirWHjb5Wdje86ri9CPf0qvu0My6Gpx/045h+fRtRMqd1vHSjGxn7X4xbwgCU0Wg45whI6T+4erzdwc1I0tEQhzy0o
*/