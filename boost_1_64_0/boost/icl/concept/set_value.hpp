/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_SET_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/type_traits/codomain_type_of.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_set<Type>, const typename Type::key_type>::type&
key_value(Iterator it_)
{
    return *it_;
}

template<class Type>
inline typename enable_if<is_set<Type>, typename Type::value_type>::type
make_value(const typename Type::key_type& key_val, 
           const typename codomain_type_of<Type>::type& )
{
    return typename Type::value_type(key_val);
}


}} // namespace boost icl

#endif



/* set_value.hpp
ugpMKLZ0Ny31qoPC4QJanq6LxWmS3D5NwOWfttJhcxmI1o3Aoq8c5GAEp3FVlCQ1lz/PkaEfkwIpIceJ9rSp8dPlDjB+bsdGlEzBo+px9DW4Ff4dJ3Bp5CsaY/CIB6UVktjBNFIqb8T6O2+Q/O0KJjuoICdnJI3z60fIFy+8xUcm2V2EHyXHSLzHAZObZ2L25iySW/iOd5o00jShRSTfoI+MX7GY7j2OhFU8cN5PEsO6PiKx2Yd6K5XxdXQxPTthxB7euUu/l0iy1Kj3JDS+kFktdaKA08Z8hookfgXvokFVEcjGr+RK0jvpwZRZFO3/GMuyQ7FTBtgQrwvdPa9I8sMr5vpysoDdveGdnw3JfOooMsrppLc5p8l83HbUzL0OlZxSoDsFe5/8wY2DRyHnJ8hBkoNRq8tou2YrpHbPpsbjkawqM45uXFfAkoRItHbuYcfFR0Jl5CRSk/pB1dKt3CP+Csa27sWVkbMRbRnAmk7PQ/24X8RFJ2CY5ndmK+CpGt7ZMHUQ8KeSCihufUCZrl/5lA8HKbLOjq/7mUsDMksp2M+YnkgcYUJ3rpOowwCklmbS7d1RWDT+F8YE/OUr29JpnuhtJA/bTbcSVbnk/ceUn7ONubuepVDlw1Qr8B/FP4UZ5Oxo8Q9zvibMHBW1G5nLhNW0LeopvWkzhJzSbIHOcMfZTUo87o8iLKL+YX+8HwabfKEdswGG6yZScdkotNmGkPlME+I3l/JaH2ucD3rIJSWeYN5Sacq21IdO5idqSJxNM7Us2NdLndhoe4Jrh+3CNKsIfP6rRm3vhenSm3qKul/Hhb9K4sHxIoGP9SWPNaHcsumfoCslwRVNSimkYQvb6iuNrpcK+M+xjRT2uPK57gPkt7Cbj+yPI/8Dp+ninQQoJ72infUXqMDiBi48v0PDj/nhkLu4gNPr8FVyOvTlHkfPbzl0KpfQ7RUD0Cz9ieOyYhCZ0cKH3HSE7cST1FS0G2fL7vGH5ZfI2Cqczdx5HrGRDkzHPg9ds+Ohu+Q0jXptxH0GMynFYSF/+Rd4ORBKP1orKaS0CFM7naCnb8Q6rHdBfuA02y0q6GzXy8Kx8g0dd04nXbFZeKvdj0Dj8/DV8mP7vu1B1lZBv7bfEyWCbnOx10Y6ktyOhCFnKflyBlv824/Ctz9iNst66eArTdry1peqlFqYf/Nzqs/5S4ZnxtGD4EiSmDONhlts4M8M69FlaEJ2Sq+p5/111PsHk87HJTy714RSNa4zxY+qsJpZhakTMik5XhKmBrepo+AFC7rYhubG4SwvTgTtKmps0OUe8obFUeGxBNyZ9A6Ht5nQuHmj6IWYNXQWf+CRgUeh/K6ctAOn0Y0bp5lNtBclSniSh5rgvueIsslKo+nRvdfM77UI2YgF46OVAeStL/LdUKS8fiO+L9iA2u3P8C2nFpDOvFl85/tRyHTNhJXvKyRkPeBlo3+QrpsXV21bDkVHCT5suws5p/7GDs/X6A4oReHhbbgifhv/5SpCSimBzq30Qtq64/yKpBfeN4djesQNbN2/HCkvRlKM8XambpSJ/rnH6KBQFakFLmArFj3Aiw9CXGTrGZxJGUtrf2XQsQke9H7ZezIz+ASTnb/pfOkhWlO/CKN6DSi/OhVfGkezTScekNb8E/jviiw8R0Tz351XsFzlAgxLfDHu7BF679xBN3/30RDfM9RyfhkTjGTB2gWQUkwaXVqzlW1LGw4FNTNBhn+bFgv8ysL0LAROXcDjTZTgktrFRNxO0vCuVyxbV5nyL+7h2b/8KEBSkm+w3AGnv+Hsu7qA4wcW0+mXvXRG25GFti5FZ80RQXd4Cml7rmP/4qfQXO9RzOR1Dv1z7WQ=
*/