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
UOPHXyUzHfeXu2T0qLPiQ+H3YgXsg3JCCaptik/OF3twm1istTja9FpHq1bnGnMWuBu9mzztRtJT4/RqxBcj7wImNBPdDmCOvZpoknPPbEfQWq+i/yTffS9kfg7pk/q03We9Vc5NMTe7xfgAsweFFAljnmsMx7eYRG7seG+ljdrAvl2f/vbDj8C33za/cAWTaIfkk8qgWqtVOALAhxa6A56wsdEb8nhdxAtASAvJZZIuxHCaFZUVqm+nNorXIHd0MXIDnzfdRrGmgfN4KyDzJqT/bUjL9Dfj1AY18/elNN0mT3D9s9tRmMX/5gW2lC2pCcxk+u82ZHrg19AD113ZfKtdWIZLxVFpEMjfSnVcC/A+CHsrfCX+Vt8orIPvYRz1lQRW+6oD632dmW5RY0pIjOECem1GPgwrgxkNqrAW/CzlB7xkXaRlHQ6k7snIOnq/yXnr70FmFNKub6qZ2H+DowKqpPTV2DetRjsLBfVToVTciL1AvTWLkQwtaI3X98Y3zfwPFD75JqMFiTmWtATjRqZsZHY289nZP5O9kqfRfAYRCn/RyO3fG6205BSW7iTQyjkvRuEtBHi6xQ9wayPnp++FzCCkTY1pepId4Wb+RIengZ+XJX2CgbNegxu4bJ+feTplle2faEzJ/yDzMSRhhcnOkcDvN/nI/SxTC3U+eZ2kXBKkETEO9STRcsmkg50WnyC6gvPIxGfLUij8
*/