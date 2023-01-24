/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_SET_HPP_JOFA_081004

#include <boost/config.hpp>
#include <boost/icl/type_traits/is_container.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_set
    { 
        typedef is_set<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = is_std_set<Type>::value); 
    };

}} // namespace boost icl

#endif



/* is_set.hpp
jZof70dpPdpE7VFZb6yiBK8A0PGhnhiDAXT/zn77coV5D3tfIZDHHWY0xN6XqZ3M4AdhXVdJPWYcVzCMZn84f/9MkLZpCdQvZO452gKgwp8PFz/NU3blwe13r/ZuMavwLFJLz+EpJH2b5H1cqapfpI0vQKU8DCLrp9VaOGYm8zLPlAAcTtooPAaxBdJ+aiOFq6AQENSIu2HfdMQ7mz9b74f/Vm1MXLN0PEjOKrTx7tHHv2YU46f5FQgGCQm9rd5V7Y+GK3lUdFDWSyT9n8ogrwwUz067qJB/MbK6/Qf61kuQb34/+ta43yZzCxNImyEMMaOD/cLk4ic4zmfoIZwf/dy+tOkpJThT9vMejyTtagni5fNHpYgYIrAt2QMEFh2RSz2wTcyKux7IUtTA/sQ5Auth+mKLcf1WpnWBWE6eWv+i1WrNtFZz8sUEvFKIg0YjMoa65EFvD3Y42kSQCUQX6rb6mgH5sAacVe5ROORR2WWpPrVc1+goXQRbqQvdsLpFYM5Cqn/1EPg9w747E7QxE5R8GKyttVFfEBL0VezQJ2bf52z/uyykuTXS/B8gc9+Hi5wWOelG/qHHFfz+AI/WEwEQP2dmdZDv5JHvoEh3+EmhkpMJBty3BXifgQjs8tohmufk7zAoWAKin7ONU1O1YvfOlvgL0855CXwHCpUIG940JOhSXEV/+ErHXuzLpjCNp6ROSqj3WVbznrmA
*/