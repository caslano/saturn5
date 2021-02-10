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
f/4RdCtDpgC+vEbYh8ST17fWUGsIrYFP5V1hryewC8dGm6HtoTle3BXRBLNP8uTtawY0RnZeHYPQ5XbyiJmgAlW6T3DwJcjWlSwCwbjcg+S/Su/2S+AQmOUrkaseWjKpDmlFkJWJCi5cJ7lrZNM2wNa8XNBAQPxbh3zTCgm2UcC1ZFbQoFwAqk6dFVzJJX2vpPleQaKDw+rraRn45tY4UKbpAoiOaWNrf8oOX5HlQdj9fSyQfyv7AHlM1QdUKQERvXW21kBIItHrlezTe3eALX/+sEm5xbtqlBsUD8j9Sh6rVtH0Y/jwOIYRZmyaZzYQJ46g5F6dBkJjdHvLtyIkNkUEELmGvtfKRf7XaPieIqKEAYuFj9JnddHtBOqLvn2jHx/+BdRXo9xcFaK3AFUWo/Jep82xTvn3jy203bbQpAEYM0rCFYS2JXvHdW2SwhY7ZDJbxHzddrsU0nl3hFunDg7ecZit7ooi7HtJipImPIX+RCxVbBqpbRNocNdwuUt7+2zxomJK22ZLH/hj+bRXwYNN23Qol41y6emXlMRH/1QLDcPohNoeRD8CFz+tPbXR7Yks6cETvZX8XrR98kZfwwY+5knST2Nv3c8CXC9kcipK5A0KVbVswi9oXKixJgzore7ywbFcQBiUBUnr
*/