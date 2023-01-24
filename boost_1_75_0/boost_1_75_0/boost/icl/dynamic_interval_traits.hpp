/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DYNAMIC_INTERVAL_TRAITS_HPP_JOFA_100926
#define BOOST_ICL_DYNAMIC_INTERVAL_TRAITS_HPP_JOFA_100926

namespace boost{ namespace icl
{

class interval_bounds;
template<class DomainT> class bounded_value;


//------------------------------------------------------------------------------
//- Adapter class
//------------------------------------------------------------------------------
template<class Type>
struct dynamic_interval_traits
{
    typedef typename Type::domain_type    domain_type;
    typedef typename Type::domain_compare domain_compare;

    static Type construct(const domain_type& lo, const domain_type& up, interval_bounds bounds);
    static Type construct_bounded(const bounded_value<domain_type>& lo, 
                                  const bounded_value<domain_type>& up);
};


}} // namespace boost icl

#endif



/* dynamic_interval_traits.hpp
PiDdQ9d8jHwrzRf1X30OVQsiv8NbGV7Nz+P38obCMZDu1cYGqO61VtvF3mZ2sRs2lUZ+h7cylDz1EH/3GgrR6j+ki82LXoy4fnpnXfzkg1A4435Y8OxUPlZbD8fkO3zle/jC960fVN0tfaTmO9j8+uyI6w8UPQ/TqutgyIYfoWzWNDjacFBQv9wK+a5zkO+vPcbvda5V3DX+I2wpnxNx/R++Nhue+qIOHq2uhfIXZ7S4zzqq+3zrpbt8t0ZxhzjNEy9+3QBPf1HP7yklfyLiELprnN9/3zRGtkZxh/jq8mIo3NMAL31dD28XPsP7NqpAdzs3hu52lu7h37Yk8jvE1y1ZCAu+b4B53zbA0ldn8vEeqf6V4WTvMK5YWg5v/HgIFuw9BMuKn+f6jDb8nDuM6Zuyd2sOw1s/HYLA/Be5fUcbfs4dxvRN2QcHjsDSfUfgg4Wzpf6MMvycO4y3r1sOqw4ehY/2H4GPylr3Z04Ufs4dxp9vXAvr64/A6tqjQPcJq8Ix+Yc873HboPvDQ2sSzT84Xn/OHcb0jV+w/ihsqDsCkdxnfKrvMKZvPzc2HOWwAduxBtux4iDawv7D8O4+tEscG2U/HIKS7w6Bf1st/ybrZOoRBTovHqo/1Ia12IaVtWgPaJfv4dhYjGNjEbZh/veHoLCV8zc/J/zw1W74fvfn8O3Oz8LfoH6x5RPYtWkD/96QvrfbtvZj6Ttd
*/