// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP

# include <boost/preprocessor/cat.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts {

template <class ModelFnPtr>
struct require;

template <class Model>
struct require<void(*)(Model)>
{
    enum { instantiate = sizeof((((Model*)0)->~Model()), 3) };
};

#  define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )         \
  enum                                                  \
  {                                                     \
      BOOST_PP_CAT(boost_concept_check,__LINE__) =      \
      boost::concepts::require<ModelFnPtr>::instantiate  \
  }

}} // namespace boost::concept

#endif // BOOST_CONCEPT_DETAIL_BORLAND_DWA2006429_HPP

/* borland.hpp
F2Z9B8ZgxzmMq66hygEq//McIxcf3GMxOjy82SOTh5+YmrbC4cj99COSib/rft983s1Ftzgm/t8XUd/PmNf2TEg/ZO2yJ2gjv+ZcHp6vnYJ+Rkc69NaQKpDAnqZOu0qcmXTLsTU+/9H5dNOzBvO9cE2wz90hN5ZhU9k34UPO1Rhb4/e9oJs/Y3hfqID3srYXh2jDXjizjeHQmgr5/UF6AFEd358hXuZ5/zu/ops/8Ldfr/h2rbbPcRN6L58ZTtunK/LJdNMD+3TNYTcz4sS1/nfcHOAXuO/0arUM7YUfJPKe+2Mh3ZigYaZx8ao6xadGHBW4hz/NeXm/S5WfU3nr00b3D100aIk/N6ZRQkP3/78+HTT+b3WantTPqeX2tc628PrI+XbW6rCXWDm1yhg/P3xOM2t9fcvTzafXYlzPWBsc18Xavli7DKYqnydk9v9aX8zRl+jGHtHtKqkb5lcTLl6l/Ptk31rmn+6myuG1Ep+0zwXcorOcQyqm5u7x4lF+vJZ5jReo8v5aiUcZ8CWjCfAdbcMqoa+2d+iMs0MvCW902s0hQSNqSdjgB7vJaQkHZACf/f9cvz8S3Ww8F2NxzrnBsXjeOaTXsE/TDHB2+eHcQjf3MJzbK+D8yD5etp3OsFan/HBeoJvfMpyXK+B8STs1Wq/Dqp/ZZ6lpHdsyF1MlR2XVujJ9mfDFVQ6sC7qsLbaIvqywt1slPUzr
*/