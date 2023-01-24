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
17yVyxQZ13H/hcw/4tm4Pxd3SyxkQ2W96a8EW11EpfJ607V/CIV/iZvrKoV6VUWYydy9PKTI1Hf/jQfqfyO6Qm19aI1drtkvVMSmH80EsgSpLgcNYFORRS90heNqbZnMALNqe8HTI07Mca0aTPUyb2FVwNh4u7t1eHz6zRlS6KC+u81aY/+jxyYABWncyi+f5Oh4DUGVd30uIkJtNX3Yaz/DGGHzuWWjn3bWhp08Wp2T+mU+7ZxD30wH+yT2V34Cu3oH3yc6AaK9AJ84LfP6r9ws1NGDbDbyf7EbCt5ElYr0d9itLg/ga/PeYk9FuXwKVSDwzJC4VtNO/9RQ9PTS/WjXmLeapmPMfxlf230pRSvVRZCo37Z5o/djl1QKSNeU7d2SRP85AlO5P294ULaEICtaRNjESvcYt/Rw2EmQeSS6I5LJW9VnlaOC1lDjnTzlp5R0wZsW7yvclNcA6W1M7X/9nwkn/Y8a0mqV0jvzoPPPoWTbbOPmJOR6jQlueXaqXI2JDV2EtL68/8s17VZPuPHWQ6rFgw2ZltWbYOp+VkOW4jSs6etNMGpNlWmFsS+It3vRUOsMwPU69uFgV5XA96YmqSCb5+9mlwY4fC/caOhNE54Vcf2NmQQ76dvcfUBDweW+KiTrcMaNnmXZJEF9afSJAp6UX5h44shx66ZFAo0VblzaYr5XoflYuu2biAWpotcyNEavCiyNyvQQ
*/