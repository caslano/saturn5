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
t+apBKsJbnkCuYnrNYb+hHiJ1wDjY91HPUrO+QYVVq5X6yuOLs5wY+Naud46vDIVjZW1KvUaYADOHPi66xwoiV5QqEfAqzAwR4fBDa1Hxkbb3s7iSIO98/OcaLkVG5G5s9EXHWeX2IfRSKC4JLrYQZ9Lt35VVOlxds8qnBJwTXPyCynC/9Rd3ZQZNtHWkxc950OKHRnN8IX2msPThi/8NHEOhE34oZaGr3kza6uvwSXCUy1H9pcetj8dr1PpS5E=
*/