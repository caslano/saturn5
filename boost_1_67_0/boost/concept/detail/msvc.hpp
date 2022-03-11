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