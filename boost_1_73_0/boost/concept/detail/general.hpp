// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP
# define BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP

# include <boost/config.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept/detail/has_constraints.hpp>
#  include <boost/type_traits/conditional.hpp>
# endif

// This implementation works on Comeau and GCC, all the way back to
// 2.95
namespace boost { namespace concepts {

template <class ModelFn>
struct requirement_;

namespace detail
{
  template <void(*)()> struct instantiate {};
}

template <class Model>
struct requirement
{
    static void failed() { ((Model*)0)->~Model(); }
};

struct failed {};

template <class Model>
struct requirement<failed ************ Model::************>
{
    static void failed() { ((Model*)0)->~Model(); }
};

# ifdef BOOST_OLD_CONCEPT_SUPPORT

template <class Model>
struct constraint
{
    static void failed() { ((Model*)0)->constraints(); }
};
  
template <class Model>
struct requirement_<void(*)(Model)>
  : boost::conditional<
        concepts::not_satisfied<Model>::value
      , constraint<Model>
      , requirement<failed ************ Model::************>
    >::type
{};
  
# else

// For GCC-2.x, these can't have exactly the same name
template <class Model>
struct requirement_<void(*)(Model)>
    : requirement<failed ************ Model::************>
{};
  
# endif

#  define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )             \
    typedef ::boost::concepts::detail::instantiate<          \
    &::boost::concepts::requirement_<ModelFnPtr>::failed>    \
      BOOST_PP_CAT(boost_concept_check,__LINE__)             \
      BOOST_ATTRIBUTE_UNUSED

}}

#endif // BOOST_CONCEPT_DETAIL_GENERAL_DWA2006429_HPP

/* general.hpp
GfhXWA3eD+vDcfB2OB52gBNgTzgJDoAPwCFwMhwBp8D74FT4AHwQzoAPwXlwGnwBTofL4MNwHfwb3AJnwJ1wJjwAH4GfwFnwLJwNv4Vz4M/wUVmX5DEYDh+Ht8G5sAKcB2vBJ2Aj+CRsBZ+CXeDT8E74DEyAz8JhcD4cCZ+D98Pn4YPwBTgbLoBPw4VwEXwRroSL4BtwMXwbvgR3wyXwI7gUfgZfhl/BZfAH+Aq0UWeWw1C4
*/