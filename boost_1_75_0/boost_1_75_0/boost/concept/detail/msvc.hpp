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
94k/SDI/pp1hTf3PdDvzmG7HFDuLrScH9MECi61msoXvcXdD5u8hPdJCcLKkXoRejJUKWBBXwx3Ax/8MPzy6xnXYvN19ZJd+IbjFpWTuzlrPc6l6Tk+rxzFO6pk15gf6linmxzwofP1bLOaH51s05seSb6VbdbM9JT0jLt0vkpgf97GYHwvJGsyGNQi/0F8LIwvOLrhCQlfA3LsCxvyKKubJnfRhK8Cjsqzvknoa8C7adzLbK2eIQT32LS7LIrGpHoOCuNmOH8HoM5x6T71sztH1/y2TjG2KvAedug4lqX0BPTfM7XpM54aVVq7zXAiZYCuZd2TTHIsMPyOkpGfyAiy0iW5hDaqlMZrVU9b4oZXwWguBcQdkWikM87mP+P/NQv2ORvx7oRu67xDsTMVAU1YJ3H4nG1AO4DCgn2ey39nZyvfHpyBzBNKZVmpnTmx0Jqmd+fHWDJH3DRj4Y3Zpv3ABaNdKekaZ+2Ki9k+tpthNtrthLJbj1jT9PvPZytDd3O7pRsh8B9L3IDlTfAuxBBqPEEOgs5epM8coTzJ2KybmQPPs5Dpgx8ih/8PdVl3987JxG5aKoZeVMjWuFMu1Wj8Q4CHHhZRGjtDeSyTAG/PRItgiF0XnkdjltO9P3M3Pa5+GzMd3q+l45RmJJ2tU0tmECoAoOSuFRS9wM7moRUr55L82G+B+BeAGACcZiPkR4t/fxvniGyEzBGlL
*/