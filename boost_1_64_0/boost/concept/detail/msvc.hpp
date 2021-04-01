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
pgTm4SFoE9qjurYO42+1mq4M230pGj08vr22KrOsTGMNxhjN61pvdB7hzjC12UI9nupQ0ohAqpwIyOki5KiWS/eJ9oPY8i43HYbnxePO4gYL3z3N8BzsndCL0Usj/qzSH1R+zrSkSzfTimgPLTJEAH9V0wF+gcZOH9bRj2SxRnLAbq2ejz1kGCdR8DmmwVtyeWNcA8oenbi360ZXaKEGaQstSV4+fj5mH0FoKNJmw1nYdaG+nlbSDEk5ffqycyRd435ii1jMdRcxC0Qsc2OpsaHpFjWKMKDynzp8wJ2WYiMbq+my+1ldcSeQFNAH9MhPJI24N4V4FneX+bHRJw3Rl/VMp/TlTjo8LwWqs169SjS1o0Fhpp518YnLbmCla1fXlq1boDrA3bcGGXbQ4nKCupw1OkK8/rthJCr8n9GZM9djv/gMhKA0mHXS02IiE9qmBiJAEUYgWnKG6QPPYg8xbM3lgtdlUqyyHGg8G/LKTVgWyxnNLCHLLB8ZXVVW2YaUr/wugDqrLltSQv/mCkoCKgS+Pkd9irYnVb/bDjXh1Fp+O8uHaYOsH6dL6w==
*/