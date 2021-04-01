/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102
#define BOOST_ICL_PREDICATES_STD_EQUAL_HPP_JOFA_101102

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>

namespace boost{namespace icl
{
    template <class Type> struct std_equal : public relation<Type,Type>
    {
        bool operator()(const Type& lhs, const Type& rhs)const
        {
            return lhs == rhs;
        }
    };

    //-----------------------------------------------------------------------------

    template<>         
    inline std::string unary_template_to_string<icl::std_equal>::apply()
    { return "=="; }

}} // namespace icl boost

#endif


/* std_equal.hpp
APkOxwin7waG8Rpzz6wKLjTmsWwrcyedJwyF59rZXg1XmxqkRmPem9ArlZyOZ2bvYFavaQ1zqaiMbX5Rg+sVwamwKr1pUJKTAM2TkKz1uc3Fvs8i1MNAyyl0Z2BEAGlnI8g68hM/Cjy87WiFScidOS4vzdw/7OJCc0kUXX4rxlu/MT9W78cp4TELQmLbNMs/gzR1BMg9puyFxt/8N+ReIRuf8EDBY/MvsNJYNSjt7TmH9gIY119mMc8TiLhs4BwNWMySPIk8twKQoqpDzwBUJw0pcdROviZKojO+0J5Z4rz7SDvrn7Li7h2N4s9KdC5GEh9BDz2JkhYUQ1u2qo7GNWnP9n5oIEnTehbfLsOUND2qJ/t/Y4+PcQQ3CZwWJHdzTInxVqX1Dv8TTqyDZa7R0H9OM40hIHC4uTFMFQrI+eNNrfR9RKRlOfyQ4/VMSluKDFr1Ewsj2Uacvf//GzVKz7uiSzS946yrMz6uPSZ1IBxABla+Hj+Pc9LP9taLODP6c1nyry2+wotln0JeoXHIMqXtBkyVLbkhkjqGyUi5TRTuDMHLyMw9NCYOIA==
*/