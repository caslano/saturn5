/*-----------------------------------------------------------------------------+    
Copyright (c) 2011-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416
#define BOOST_ICL_TYPE_TRAITS_IS_INCREASING_HPP_JOFA_110416

#include <functional>

namespace boost{ namespace icl
{

template <class DomainT, class Compare>
struct is_increasing
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = true);
};

template <class DomainT>
struct is_increasing<DomainT, std::greater<DomainT> >
{
    typedef is_increasing type;
    BOOST_STATIC_CONSTANT(bool, value = false);
};

}} // namespace boost icl

#endif



/* is_increasing.hpp
9ppF/QVhFb2lTJf6YrtzLbGVKmoCgTw18Fo7Vf1q4a6Iu8/+9kP2lW33J/6FjC/CFvX0Kyq6S5rCg1x47X+MUpa38Q9ovJR5IohXpixTVFP9JgWW1JmX3Y3hQV+tbXGpU3eTrYe87XHyk7IXlUbgJO89Nz53OxeEPru9GskToU+of9sFSULn7qxMrWlyt5zUBTPmEOLyB+87tVU9T7ersu0ALqqKBRkupd6/craDM+45Gx/ApETpBe3z6KEaH0v9h8VjFqY8xX+0qG5hBvFzy64Knxce9us8Ot6vkenZ35ysJJfMwGwIpnUOStp3vc5flIn6mfzYuvgutvehiaLdOZ6YqgbxbfmFx4/jaH96zR1HcQL/7GybgdPO26ION5NWWtOvMhTUOOJEMP7EI9xCwjf9Ja7g8VceGjhKRE3k1iBWqnu1snE/Q/gcusZqEkuFNwHDvA2FnJUbW6Tg4pD5eYiJLadHlre2+Evy8NibyRBmqtqP1i1HbXHrKYFN3F1iqy5EBNXNcH35YY+TapwzW8Ubk+kenYR5ukVP702hnjETAXYBLvLK5tPtO+jsGQ/nBgSenJuDJxSRcj0bkX9II/haYM6I019xat28a6EdjfKuT5A1JBEvympArBnPSbL8R9J3ar0zJSEu75+q+ECwb6hoPbVy6HvrmXCPWt+IIV/ten+5fmeujCQH2QbxJVfrkqRpplwfmXU/Box4
*/