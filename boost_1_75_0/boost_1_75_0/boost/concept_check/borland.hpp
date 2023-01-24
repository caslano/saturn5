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
W9r2ZMJiucq9S6bVlZS35WoxKl8aP2Wm7ZmW7TS19zy8gBqfrGvL2OqfhJH8aHFiHhb2iYVSudynnFBrtGXqQfEuScnBjlxlhx5wVrn6nU16SNnk9ipXiXgErSXEiawpXurLzOsE0pzHyKZ+Ja9GV0a96EqYa9PPdevf5vbeiyFTA2ntt+k5NcahUGqyIWP0UI9j8TKmp+KZxZgpd+Ptt9klWVa+C69rmoP8OF1u8oPcnv5vp7W1wd1pbe3hWyB/4zWtS+1CUGwTkmKucA7SG5AO8HwqHZ6WnoXUKuXLeYpLLtUKHWGt2lno8rvzXSFnhxaTY1JMaEaNwMQtxLKXWB1p0C9uzcnOdeTC3hQNIo/Ni6zYhPVJsF1Fb5G5dT1kNrST2DBcVscltMwigvNf0we33SwjuZ2Oc9JktDtgPvbJjZFs7AzYFF6+B/XgAqFTLJJy5VwlVw1qMUcVDjgqVK8SlkPSQ1gvcna6aty93nuxJ2rke5qNck+TN8+T7/YCn1AllYhlOIiWC5oj7HUiDcO3ezUj16u5+Hf/GXx3aMbvNu6B/d9G9n/ITEHKl03C1XoukhZSNn0mO2bzUTcmz5iwt7Cl8l3MOi1h7idu6k2llwLXOHew/tzB+NmH6GvnuRlBRuSdhstlttyKaweTor7FuOBVHwIF6xUqxDaYI37Fr+Y68nXoRr1C89LjrPPs2C/7nX5Xp+ekt8Yo
*/