// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# include <boost/preprocessor/cat.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>
# include <boost/config.hpp>

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept/detail/has_constraints.hpp>
#  include <boost/type_traits/conditional.hpp>
# endif

# ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable:4100)
# endif

namespace boost { namespace concepts {


template <class Model>
struct check
{
    virtual void failed(Model* x)
    {
        x->~Model();
    }
};

# ifndef BOOST_NO_PARTIAL_SPECIALIZATION
struct failed {};
template <class Model>
struct check<failed ************ Model::************>
{
    virtual void failed(Model* x)
    {
        x->~Model();
    }
};
# endif

# ifdef BOOST_OLD_CONCEPT_SUPPORT
  
namespace detail
{
  // No need for a virtual function here, since evaluating
  // not_satisfied below will have already instantiated the
  // constraints() member.
  struct constraint {};
}

template <class Model>
struct require
  : boost::conditional<
        not_satisfied<Model>::value
      , detail::constraint
# ifndef BOOST_NO_PARTIAL_SPECIALIZATION
      , check<Model>
# else
      , check<failed ************ Model::************>
# endif 
        >::type
{};
      
# else
  
template <class Model>
struct require
# ifndef BOOST_NO_PARTIAL_SPECIALIZATION
    : check<Model>
# else
    : check<failed ************ Model::************>
# endif 
{};
  
# endif
    
# if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

//
// The iterator library sees some really strange errors unless we
// do things this way.
//
template <class Model>
struct require<void(*)(Model)>
{
    virtual void failed(Model*)
    {
        require<Model>();
    }
};

# define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )      \
enum                                                \
{                                                   \
    BOOST_PP_CAT(boost_concept_check,__LINE__) =    \
    sizeof(::boost::concepts::require<ModelFnPtr>)    \
}
  
# else // Not vc-7.1
  
template <class Model>
require<Model>
require_(void(*)(Model));
  
# define BOOST_CONCEPT_ASSERT_FN( ModelFnPtr )          \
enum                                                    \
{                                                       \
    BOOST_PP_CAT(boost_concept_check,__LINE__) =        \
      sizeof(::boost::concepts::require_((ModelFnPtr)0)) \
}
  
# endif
}}

# ifdef BOOST_MSVC
#  pragma warning(pop)
# endif

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

/* msvc.hpp
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
*/