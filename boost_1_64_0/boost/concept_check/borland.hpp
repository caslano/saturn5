// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

namespace boost {

template <class ModelFn>
struct concept_check;

template <class Model>
struct concept_check<void(*)(Model)>
{
    enum { instantiate = sizeof((((Model*)0)->~Model()), 3) };
};

#  define BOOST_CONCEPT_ASSERT( ModelInParens )                     \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =               \
         boost::concept_check<void(*)ModelInParens>::instantiate    \
  }

} // namespace boost::concept_checking

#endif // BOOST_CONCEPT_CHECK_BORLAND_DWA2006429_HPP

/* borland.hpp
SwiUhmnZ1wJuTH7jXRGkc7MrVwSyQPS+CQJK56BSA7Tu+YEg3Y4hxd6LGCAlAhsGN5UICGlEqLgCW1uzF0eiGVZkGMt95zeQKgTISIWoklk1zqhPenfckQ3umg+QkKnKjy6vamyWRrPZ6NHeItB6tzB9cJL1dGCvldZEa7hUtSttZferHypIKUI+TP47C0Lso5WWWLrlTo+NI57wcMSfa8c/2IiXcRIl6McUvdW0hSOxo7kH6f9n60spSluf1JWNQENXsFUN2ap6oSOxRlnm3rgyQs3ZuTOxquqlt8bXLf7F1gwkgqiKpHexfWMYQ9uhKJprv6g56f2XE7XTfUhyWQmVka4fVfv7r2CC3Rmzw4IQrcDwBSXwB/4H+TfTlByiF+2gjRDLZtRrWIb66FNBCof+B02Hrex196cryIS3N1+EbmktoPwzbGTs7pdDLj3oFJw7uj32JPks0GhOLq9sGfKH4YowaSq6+PkcNaibvdH8xNU2uZdpkGLOANRDHBvzBMSReY5mGFd5qHHXxERV2zTwLCMi25zpKFwCAApsMcuV6nLlZAjb1o+HFA==
*/