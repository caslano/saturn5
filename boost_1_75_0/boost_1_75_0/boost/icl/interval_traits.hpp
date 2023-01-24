/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926
#define BOOST_ICL_INTERVAL_TRAITS_HPP_JOFA_100926

#include <boost/icl/type_traits/domain_type_of.hpp>
#include <boost/icl/type_traits/difference_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>

namespace boost{ namespace icl
{

template<class Type> struct interval_traits;

template<class Type>
struct domain_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type type;
};

//------------------------------------------------------------------------------
//- Adapter class
//------------------------------------------------------------------------------
template<class Type> struct interval_traits
{
    typedef interval_traits                     type;
    typedef typename domain_type_of<Type>::type domain_type;

    static Type construct(const domain_type& lo, const domain_type& up);

    static domain_type upper(const Type& inter_val);
    static domain_type lower(const Type& inter_val);
};

template<class Type>
struct difference_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename difference_type_of<domain_type>::type type;
};

template<class Type>
struct size_type_of<interval_traits<Type> >
{
    typedef typename interval_traits<Type>::domain_type domain_type;
    typedef typename size_type_of<domain_type>::type type;
};

}} // namespace boost icl

#endif



/* interval_traits.hpp
C6iJl0miN3k8yclRhOFq4K3wTjTB5ZG2MLQXMVYYi4uegnk0uWqiYLsbYxNv5ms0whj3L945or10XJSuhlWlZYAmd1pJqn9cvRrFMYgXOwynOJ/9yRFozZpFZ74YIdE7RqB8lSoJQjWkSvh/shNvbCIItF1KwN+cCKIYoZ1JjNC2XQymIyUBKMr08f5C0LQfq2lfbfkcV1jy2yjwcRvG/J/OG9sf5ozsCzOG9fxb38+pbbNdP6dlny0z/hhkxh2FzAuHIfN8JLyOjYCMcweYfcq/E5/sx5KvVLJbzeymk51ussf85A7zY0r2mP9uO/maPFfZlmP2hzXsy5Gt8ByyFf44GUprJ5/qMM6xPYzt3RbG9GoDo3vawKierWGUQ2tQ8dz93ltms1dtm07+itlrVdmn07SPVlo7+Ue3roSozQFweOMyiNywBA6uWwwH1vogvg2oeD7/YTZ43H8LKtt2oj3odLV9O+JF3svHzJZeae3kky054sebq39CViL2pysnIWKdH4zhNl2J596PRB0ItW287CzWfpV9vK19G2H7xXdEpbWT/+bGeeZv9831M+o6HNq4lMmD8InnTA8D66C2rUc27XLe6LWvV1o7+W9vxmEdLjB5vEE+ZGEdSB7jeN8knq94KuqCqGzzfchVivLXY5+vtHbys5Pj4Q3G395EPlyPhTfXzsAx7BOuOD4In3hOug9UB5VtvwK1fW5d
*/