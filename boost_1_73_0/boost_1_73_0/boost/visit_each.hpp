// Boost.Signals library

// Copyright Douglas Gregor 2001-2003. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org/libs/signals

#ifndef BOOST_VISIT_EACH_HPP
#define BOOST_VISIT_EACH_HPP

namespace boost {
  template<typename Visitor, typename T>
  inline void visit_each(Visitor& visitor, const T& t, long)
  {
    visitor(t);
  }

  template<typename Visitor, typename T>
  inline void visit_each(Visitor& visitor, const T& t)
  {
    visit_each(visitor, t, 0);
  }
}

#endif // BOOST_VISIT_EACH_HPP

/* visit_each.hpp
3lBpMtQtM7mkWswlOZSuI7JMOvedr8Pg6vT+7uPN7fjh0/3N+Ky9P6KsFFbN1iiG8M/Nlxvp9J6nTbYrfNpz5FAeUBoEP7nJ3Cav95cfz0g+ChaO2BhtE8eV9ALtuGBg86LnpHcUzGdIdURpU4eaNFoF/rAOnFdbzk9gX49ILI3KKb38+wx8pCbhFqwyV1DQ+OvtGR0HrzRJ9l+stFyipGh5gngi/h1PbXx4EHXNzWQa7xQCb2YC7A6C6Ry+PUpjrJWZD30SXmF2dI7Jqa3xxq9rDrbphMI4r+pNQUJXIAdfkFvrDO3mTMk0JslGzpv0oNsdUVNzQ4UMtqocf0kf0svzzwfABqhttJfOu3aNGRR5Tr+Nz9Lx9f3VydkdLaEctxx3AfcZCNdrLkowocpYfqWXUisI8FN3guLbp0XAXlwtM24GoaGol1ajs5Ds45qNnXCwck+apad3x1dxenEc98Leejkn/QEtleBmmrMNTTZVhboswo9FggZ0MR7fBi9Xn8Zj5J58b7AZ2KDDnvWuRjEdGO/Bk4SXSa//izthoc1K82Z42gpOytDJnQ/XN1+uH7AkUnrDA+xGnQ5PQtvJTgAESzZsF74q3/4QbmUa8NDGUyFAtDRmIXkdL5g0cNs8C1nWrTCrLdhyHR2n
*/