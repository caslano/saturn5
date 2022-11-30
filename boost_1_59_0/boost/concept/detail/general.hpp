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
#   if defined(BOOST_GCC) && (BOOST_GCC >= 110000)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wnonnull"
#   endif
    static void failed() { ((Model*)0)->~Model(); }
#   if defined(BOOST_GCC) && (BOOST_GCC >= 110000)
#   pragma GCC diagnostic pop
#   endif
};

struct failed {};

template <class Model>
struct requirement<failed ************ Model::************>
{
#   if defined(BOOST_GCC) && (BOOST_GCC >= 110000)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wnonnull"
#   endif
    static void failed() { ((Model*)0)->~Model(); }
#   if defined(BOOST_GCC) && (BOOST_GCC >= 110000)
#   pragma GCC diagnostic pop
#   endif
};

# ifdef BOOST_OLD_CONCEPT_SUPPORT

template <class Model>
struct constraint
{
#   if defined(BOOST_GCC) && (BOOST_GCC >= 110000)
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wnonnull"
#   endif
    static void failed() { ((Model*)0)->constraints(); }
#   if defined(BOOST_GCC) && (BOOST_GCC >= 110000)
#   pragma GCC diagnostic pop
#   endif
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
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
*/