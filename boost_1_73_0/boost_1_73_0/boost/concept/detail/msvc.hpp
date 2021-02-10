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
zprmBC0MbFtR2dfoi/r2fmw3sRRocCIu+oa2ylJkrYlBjgYh8C8V6D/Fhd7/XWZYKxUlBVxh90L2feu5HJ1lmtNQmqbUECepuESKrUI0oVdoJsTYakcqopBXrQcPSq5tRtBd2GtKfXaSIjCWTZy8x5IacMNy71SzvrfrQoWVUGFlt1jGaTyN54lj8uoGJHlDzdzsr+B0MZ85fls6VmLGL79+pkDWMjVCLbFypAd34D8HPpuWVKGFzJTVpT5nvHngblrwULif88bFRBg+3oU/SdsTcQ0Tz3yLdE+aPH7y5OnBwaP9fdgdfxtEi+ltMD+beZ9FzrcAmg7duLEd7SVoOKtssuZa49q0SHDTPRhpK1s7vB3LwuPT+CgJo+lsC72gAg+sGQRrfWFw8LRvcdvZhZZYE40s/4CrLMsmWV7R/L3t9bdajc0IVrzG8C/M+12MTQe52dKXO8fPm6ahk9wpA9Dn6Idy5Kb369CC/0kO9qLFatW6ni3oNzeKU/e56w5ZPzn698nxS2bUF7wNwnnwOpyH6bkTFLatYLOePPMPzYLlLD1bRmBO2VkOjUFvYZbFbzYWtB1cC0j2XccFftLsZ9YuPIveRPG7KItNC9RBLVfWGW4ym0EwT2Ls/q+X9zkDF3sUCvmePjYTzv9Q
*/