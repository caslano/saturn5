#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/sequence_impl.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        #ifdef BOOST_METAPARSE_SEQUENCE_CASE
        #  error BOOST_METAPARSE_SEQUENCE_CASE already defined
        #endif
        #define BOOST_METAPARSE_SEQUENCE_CASE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, class P)> \
          struct BOOST_PP_CAT(sequence, n) \
          { \
            typedef BOOST_PP_CAT(sequence, n) type; \
            \
            template <class S, class Pos> \
            struct apply : \
              sequence_impl< \
                boost::mpl::vector<BOOST_PP_ENUM_PARAMS(n, P)>, \
                S, \
                Pos \
              > \
            {}; \
          };
        
        BOOST_PP_REPEAT_FROM_TO(
          1,
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          BOOST_METAPARSE_SEQUENCE_CASE,
          ~
        )
        
        #undef BOOST_METAPARSE_SEQUENCE_CASE
      } 
    }
  }
}

#endif


/* sequence.hpp
gLK0PJlI5YCnUyRP4dkCQe5jMsYHWMbSh3u16bgPbv/oeD1of9b8tHHSTG+yXJrSdOLs+f5a/BTkNu+T9l7puan51r6NmSfb4Lfh4jOWOX2ZuuR1kPvMghVB3srJMtR7Hvvd8XwQIJ3spZ+TPggP9gXiI84I5uT5jmH1kMclPP7Ypy00UsjwkDQby8Fy077ZaZv5msoWR8I4jGUzo4dNyvwb6qoVTE++sbaKc00ZUWQtrZZ1nBPYG9MRPh177/yf4o+/fT+xVvTifrHWYIce7uuiPbGaQ3ilWIs3gifTB5zn9XpYH7JmXO8HVC+O3Tbr4xcoe/RnEdnUCm8crZk/2jLsuShrcm1CXVzUsXnT1uSPYLw2qjrwFrQVV7HdrdNcBpaEFcdLMtfh3wE7tH1g/6HNmQS/dTXjY7Ac/J8AH7gD+7e3NNcfBEOcZX9jMmu6Zltq/RXTxDei41CjWsyHOgfvslp+m9ptLWTDj5dffziLq9/hYk3eOZ6EuoBRXmIuPxnl/fvw4b6Xv+ZuFp80Q+SU57fYABPfuJaqo7atGH464PzNby32EiTz7x4JfNjJZTsn4QV5eoetTzJeX0+Pc4Khipm44fsysG/9b5adL4CF/mX+cZLi5B81gbMQOIhp5iMiR8QnOIsDHH5bNeZ7iZQFJRdJ2DJSFePbBlxgkUQxOfI5fJMRwOnjLoILvbJMactOMYPIeCuAF83BSMRwlZXqE3A/El3u30rgBWdYe/pMaK1V8v/wfsV4S1W8TWakHX/FGjvvKGHluJnJLbPitggGKbeEb0oAW4zfOuDSO+0kz/iddsZpE/NgvDpWFLJKxm99gkNSN582cJKYupR/u5R/ByFRvWa/K2bdAF7U897587UzVMdq+w3qMRxKi+YjVBuYUJ+AsSbj/LclawwAG/KUrOvtMYyoGKBzfgY8iZNCE0S9KTub+6XZUg9Wbakdq0PfiJ+T494aDmaWHJduXR8FuVvqs0JafuzHTrvmfbTgLcXdq9k35lhwNI3KJfZlnjNLWWdezsVebS16eu1+Kg6EwToGa9/Px+Dq7n2h3pscF/X3+3DvW5FzA7iRDOuBfgsP2TRoYp5eQPKDgHcDxdl/HuT2s9t/a+rBHtzP7/YQB47E9uf17IVt5+SJyMY4Ljhp46ECbmw5/13uXALv7t3V0x+B0+uAQqU0oemAicA+CH1kxjPs+n3g8ySezAMvtvMS/pQ2v771/cTw4dVuHgijwKXuHrX7E2tHY6sGtsm4cxYqN1hPmHWJj7Sq49DMY1oPAx7nYqzkJzgVUWgjsd2SwO7N++I4nhktyTlVT2DkXQBc5r6ajOdrRDV5c4/3v8XOfDbXSPC5J3ds7Atz573ZJ+FRofBZ0deHh3jGpAcy20yPDHEwZA49fnNP2mSF8Pvx0ZWOv50MB9ZPj0N9nBetiJxUaiz7JxA/PLNE7kva29E6WZsMexLBwHwQb3RhwrfZkNg64jkW6JJQniFO6WiMcmujMbRjh0E0g+nsk09O5oqNqKapEr6D5eWKeyrqYebK9ZPAngaYkD8WkYjvT2ymKccffjixg41AoxjTCUzOZN95Funq8Ek87vNzVBxYYN7+9DwVj/aeMIdVFYNgh5nHyddPlB/Yza/1fJKDvQFw8/NUzmjwJp+w514o979NJOoko5DxarE+fPFq9w7Mtz0QD8xwUgt+XPBtIY4zRr8TcA6209vAdDp+GxZnBvYmRKGeb1/r7DX6/Zm5vLN+hJdDZm+6J3JSwT/58tTn4UZ5Id6g8nDlanGX6uUb2jNPwsqwvrIwXXmtFeJ5QEZss3Eelleja8BvYMe+VeXzZnGm6evu2ZlmbDoy+Kcjo/o=
*/