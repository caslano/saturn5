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
Et61sDe5R+6wvaPqm+NXzJ5j8CkI58GHcB5mF05gNYTi6AeiNcCmOVtE8CmYn82cBdX4xlFwQwHrXy79lDQyVF3bCqmNXo2ue8Oz6CSKz6M8tvPFOHGhe2W56WwGwTyNccJ+WDw8IXBRkB64D4Ry88Njh2cNXOdfUEsDBAoAAAAIAC1nSlI/u04kYAUAAOcLAAAxAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTElORk9fQ0VSVElORk8uM1VUBQABtkgkYK1Wf2/bNhD9X5/i6mGrnSqy0x/o2qTFXNdtjLiWYSntjHkQaImK2MqkJlJxjLXffXeUHMdNt3RAFcSUSd67x7t7R3uLFhz8sMfxCA7ufCL7H+GD49ZoWqqPPDbfNoiiz1D/oeECx+9w1YWd1eeoA99l9Rna1ipqfJ3QexR9h7sFkaSPLhkvInrFmdqysR+oYlOKi8xAe9CBo2fPfoVDeNh72HPhNZOC5xAYLpe8vHDhJLEzv2Xs6srT/KUL3ADLvT3AMBMatErNmpUc8D0XMZeaJ8A0JFzHpVjiFyHBZBxSkXMY+NP5aPLWhXUm4qzB2agKdKaqPIGMXXIoeczFZQ1TsNKAShEB8ROhDWJWRijpoXsOhpcr3cAQCZZr
*/