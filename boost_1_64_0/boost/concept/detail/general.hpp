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
ay4+RkzSgVpRSLuMwr9qVdQrRLatAkhPbTbuDIBSgZpI9TVFAu6LgqyueadAMLhzsivBTNHKmxSuaPxeZWYrz2xI2/bnMrKjkFFz4G4/b0v/pH08XJF63w+Y09+WSkkycVIxWqEFJlaeNis5v6A2kH7hG+2ktgK1LZ3rcQNAr0nmfphPQk1FZl1a12hW0iw/GCVH0veH6SX03t7qxD7nNtLPWyMKlMnt4ALq6z2gkzWlKRd02i4eP0A3WYtNFt8xPiUW1OdjtYCvUhAbmdcBsxsGaeqvZdvIsNQk/5A+JsLrtlURL8PllH5a2Djkh9khzC+R2bfx4XG6D5DINc7KO+mqXezqVOAsGysXG4z/w69NWRki9DWCgHxyYGE+DAo4OUes6ePn8oHFpVTC6UygNbCYeEanGFGiB2HsUSfPSnVHlizMaNFlXEjOFKbjfKt2IlP1xRVhOPumFOCokj7QTFRPdeaBZOKpTMFWsUx49CtM49HPg1Wri59WYxABqQg60bo/g+MC6KH+9MLXqnAJs5WbozNSQ1mgNlwWTfX8bgKf0zIQYUEqG2ZcyQ==
*/