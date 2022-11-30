// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP
# define BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

# ifdef BOOST_OLD_CONCEPT_SUPPORT
#  include <boost/concept_check/has_constraints.hpp>
#  include <boost/type_traits/conditional.hpp>
# endif


namespace boost
{
  namespace concept_checking
  {
    template <class Model>
    struct concept_check_
    {
        virtual void failed(Model* x)
        {
            x->~Model();
        }
    };
  }
  
# ifdef BOOST_OLD_CONCEPT_SUPPORT
  
  namespace concept_checking
  {
    template <class Model>
    struct constraint_check
    {
        virtual void failed(Model* x)
        {
            x->constraints();
        }
    };
  }

  template <class Model>
  struct concept_check
    : conditional<
          concept_checking::has_constraints<Model>::value
        , concept_checking::constraint_check<Model>
        , concept_checking::concept_check_<Model>
      >::type
  {};
      
# else
  
  template <class Model>
  struct concept_check
    : concept_checking::concept_check_<Model>
  {};
  
# endif

# if BOOST_WORKAROUND(BOOST_MSVC, == 1310)

  //
  // The iterator library sees some really strange errors unless we
  // use partial specialization to extract the model type with
  // msvc-7.1
  // 
  template <class Model>
  struct concept_check<void(*)(Model)>
    : concept_check<Model>
  { };

# define BOOST_CONCEPT_ASSERT( ModelInParens )                          \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =                   \
         sizeof(::boost::concept_check<void(*) ModelInParens>)          \
  }
  
# else
  
  template <class Model>
  concept_check<Model>
  concept_check_(void(*)(Model));
  
# define BOOST_CONCEPT_ASSERT( ModelInParens )                          \
  enum { BOOST_PP_CAT(boost_concept_check,__LINE__) =                   \
         sizeof(::boost::concept_check_((void(*) ModelInParens)0))      \
  }
  
# endif 
}

#endif // BOOST_CONCEPT_CHECK_MSVC_DWA2006429_HPP

/* msvc.hpp
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
*/