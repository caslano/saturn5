/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_DISTINCT_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_DISTINCT_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> 
    struct distinct_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return is_distinct_equal(lhs, rhs);
        }
    };

    template<>
    inline std::string unary_template_to_string<icl::distinct_equal>::apply()  
    { return "==/0"; }

}} // namespace icl boost

#endif


/* distinct_equal.hpp
yXU286gPMcuzJbqdnj3R9uyVs8mZkrQv+bPSyHz7Bb+xVe40sFXSrcfVqp4z4m9oR3KOPS+xJXnlkT9TpPv1trsWlRjPj+3D/0an0023rf6db1s9GrrhgvPtOO9gTV16V7sUT7L9dQzD/plr3Yf9748mWZ6UTyzxzbarbI/ceAfrivvvuEMWB7v5fphhQB4dkTTYARt+BDO70bvb2omcF9oifkGlEn7lfBWXVF6W+WBzCX+Xm1IxJM0hXIZvXq4xHZttLLqON+TCwf3ieGDwHob3jjsd2utuJ64UyLWm31yordUlktlw9nuXSG4SI/s8X7f0MsRK91iYqRLLzbgA27nMXPNERjRLgOsTU705V+l2oAAYvtnxjUxGhnQvIq0aic5nL8lt68Ks/5l9XcWJkKzmlBWB1YA3B/BpkxwI2bOsHmYTtMzuBd2VWQDhupLFQj4U8QjVWVLuh1I5IWupkiy9Z0rOqy6mm9ycXYhGxrF8YLGgxQwBeS9j1opl5QyrfrgWxzqXlxuzC3BItQuVS8O3H96X3+cbTVFIWryUW6xgmc0vwKrmtWpU8Op2ZV4hEgZeYpbe1ru62rJuO6ACmmHRnSEfP5IPpdblWcBQrsM8XnIB99ZiFKaaW50jCfTWGEIxrsMPVvA3USa+
*/