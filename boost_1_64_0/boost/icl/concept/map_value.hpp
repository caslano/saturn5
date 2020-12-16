/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_MAP_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_MAP_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/predicate.hpp>
#include <boost/icl/type_traits/identity_element.hpp>
#include <boost/icl/type_traits/is_map.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Map>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_map<Type>, const typename Type::key_type>::type&
key_value(Iterator it_)
{
    return (*it_).first;
}

template<class Type, class Iterator>
inline typename enable_if<is_map<Type>, const typename Type::codomain_type>::type&
co_value(Iterator it_)
{
    return (*it_).second;
}

template<class Type>
inline typename enable_if<is_map<Type>, typename Type::value_type>::type
make_value(const typename Type::     key_type& key_val, 
           const typename Type::codomain_type&  co_val)
{
    return typename Type::value_type(key_val, co_val);
}


template <class Type>
class content_is_identity_element: public property<Type>
{
public:
    bool operator() (const Type& value_pair)const 
    { 
        return value_pair.second 
            == identity_element<typename Type::second_type>::value(); 
    }
} ;



}} // namespace boost icl

#endif



/* map_value.hpp
v5A+ihRR1Dd/Pp85CfYhF6lbbtK5Hcep/IcJXZJ151L+UfhbtYD7rLGjPV82c9P4xaiSV8Lhh9toRusUllghBa37bny6jyQ1PtOC2ZqreCS/j4k/a6CCAn/qb5uN4KUByF1SQtxrDU1P6qRpta9gb3OEvJv70fTtE83+UMpTU0rp8cJo3mB5GGct46ixPhHRY5VYWftb+jd0Kl9zKxStT1W5UZ8ZaVVtZMnJD+iWsi5cFUuwIr6UUFaAhswFbF3kFoy8f5HE9HNomkYsk5wfjqlPnyIgyxOt7W+oDQdJXecmNHe2kutgCP/37TTl289jRhv1qEBcg9sOdtOkMcX0XTcbJvmFrDHxpECvFGJJizfY9sc4+FQev1bdYwebwlGQcpzJ3npMKYrbyKQmnvrCNqGQ22OY6nxcsNKhFZfFscbWDK3n7Jj9g+X03rOGdZeaQtakmqVdtKWjewTZ00AdJb0dBs2QO1iXuIB+2m+m7/pX+W3/fgS3NsNHZi7di3KGo0olPJuGcO2Zv2D3pYfu2RbQ1qtrmLLseAys/8A7snXpav9YtKQOpbp5P+D0xZXMd/hz7myKdT97+bEdpyD2/jKlKPxD865etvrUHyrcqM5GjB5JV3fHoLoyiXyfD2EoBrLv2TF/XxsBX//F0vYmoD1cBReE3UgzzphViwi4UaUwex/LsWBYIXcRFaRjjumU/uk85qY48zQ3EwF/u48/G19gSpsLvqKSNOZIw8P6MoWsWsUC6vtw1a2M7E+GUfOMSuZXlyfY7yEYc/EtGc7LwhEDLzIX8kZYcia5B4yiE88f0Oj/8hE8bCE+bstkLaKptDYtDEL56XTKoYFZ3m4Bt5ajZTfzEKr7ERqrL9ITh344C+6wm5c34vQsyPH+XNb6JAnFZsfYqusHaK9wEFeynAFjnUP8j/Qdcq+uY3sHPiD/3ga+dLEovgh3sOaKJLw+WMOUvv2E9OIbTCrVFhGHspj5CX9UyfxgGzvHo6JbisnpxaEow4wrvfcnAckiX6do3AryJfsMWcr/JTgrgc7wbb/Dhnb5UY5CDv/voQE1DhXkPAJPHOh3n7UdksZq3Qo+b7cbXM3lKfVZLil4yePY1hH0TamS/zh+EMP0jFnHezf0jFXkzldEcHjqdtrwXYouN4/nnjZq5BviwuOuK0Ni7T5qUBIBuYlT6JNQurs5nfmmTcQ8mz3s6ozx0A8/xLa/a6Pnt6J4tIC7sA9RfOWEZIofrUE35i2ndVkilDvsLIkHTaOJ/wlRr9cXOj73FD4vkuSys6YjLOMxrS6ciFyfXNSr/EF8gjl7jFukXSTKrhkJMtJl/fyvsT0pj9rJVeZ/gFV3Pvsd6ogEQf8pT+YVNRvKsXkaEzG4rwVhZiLU2x3IK+M7qXPvAX4rtgPhgnkV8q2QpogNsCF6PpQ8ZgW7/Dgf+1yOkNffP5hQHktabt70xyYbEZ/CcDFvBiI0FlCIWSc7KbSDLPSKWaxAB2WFHaVREhI4m2vG1K0s0Yk4upJ1Er52odAfTICJ93MEiqujQVedt2Q005y0l7jy14t0Th/gp9gtxCvF8lf8Cv0ddhqZ3JO2bdFCqsQy4t7CiKqYA99/gXy2miFF+G5BUewPMl/4kLzn3gY/5MDUN1TjQUsdazd/RhK/FFnh5Tc0x0mejgUMgqMe8/8qQz2+jW1eVYIrb37xy8P9MIwD/56chNUIT5KTXUvvZ9WyuZONEaedx4Xqf9IQoyr+8OZ+LDvyAhlHban5z0fydMpB4b3HLOb2Wry2C+Lfz6zHtxZbtl/wtms3SDPWLIS9ocn04kcT8YFyZH53xcq/u1me9Gg8tniLIkFvULtuNqNP0pSq+J4=
*/