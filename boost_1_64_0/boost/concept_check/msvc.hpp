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
T428nJ9uFWpVxoE5CnkPvEN2cC3w5H+8ShaBtzMRMGxJmIjOsSBzpa/W8E3zkij4iW4iUqT5OCh41Ujqo4Fa7yGpEQzeuI3JgcNjqBx67h/dMXdk063eFtaKNM1SEaJw16E6xxw9C96+X50t0kmZTgg/AQj3GbMOi9ZoJ1gcaIC820ZXTAYY9PmVcQw7srrFzILvptfdgTXaD307omtLd32KZVhbyQE7rLM028el8Y/Is9hpX/qEO5D8ZNGawZoc5aqMOSy2Ma/z2fME2tLBmp2f1q3DsVkR1hsjBHQ3lHKacYZH9tmRtGbIQNzskRlSB/AidPP3zbkTe69vU2bvclb4eo90szS3/LAtvTw4dL+nggOqDSrMcWofqSDC/3T+VnewJ01HmyRXL2Fl7/30uuPL/5GIgalJvI3m+IZ+EuuQZlJTeQnBeq5Gk9gdwweRQ+3V9hHNK3aN9NJhg9r90tbXZfs3EhfX9dhRf0qYDuDpFwG3Eoqo9THeH75s62QUg3T6cErh+et7I8Q0D6VXqVpwO6psxx1IFx/7YOu1s+SDBb1qrg82ARYwYw==
*/