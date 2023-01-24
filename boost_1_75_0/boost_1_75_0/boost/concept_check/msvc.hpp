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
0FkFki4WCcWwk5fJmhAQ/6hP5FKowk7097dDZgjSD3pSY3jWPL9SkTEYQrLhJZh04GFm1MWVthjLyroeOsPuJzOsDmZYFcywB7B8QSmTb8WOI/ohR1jfoK3WOzNTTCGBTmaLv3Ouh++7n0BG/odULM24mSti/eFoJ+S1VCjqQiGJNAOcEUr5wP5LFGhMoEB0KQrYCi7zgV0OYI+QPeZ2yByHFDSb5dczDTyfRpwpmuJGhdxvAttXNlsO/KXPcvMth84xi+uLpUIMRi+LKsOX2qvX4FqhSdSlgJwlKBE1qrU4CnSfM+Jagt2vekLeIo/urnE1BcOuSmdQjzrCcA05itSgUiN64YubXIkgUDIOsrV6CMPpdbiBUuZrN7oAXdFhnWvFvTxm262QaexN0W7mg11JMr8cg/iIkAt7ho6LUINIfQvPNl6jvZxW2QyZA72pddFuOm7Lz854enGh4MeVPJ1gKwRolASsEErrqSNWGcWnKdiXIKPdl5KvmW2C+rVW/KoQgjVAIBWILCYHjU1yJbqm0Y2uARr2GqB7ps+Byvu47O4OyDxyH9kDMjNskkvwpgcv5pquC/T+zZTKjxeY/ijqRSNinbSVhsSsUQJyRAzBcHWLddpWWAdxZ50ecMA9GMgCsQh7UZMY1jTRo2hSrmjoOdcDDmy8BvCfD/CfO9NmvnaFPhW9QOi0BZBZBelhSAGT7IARa8MRfauQ
*/