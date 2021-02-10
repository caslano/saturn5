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
CQiSE3rbwTSZUMBLRED8gkqFmK2ivHYxPAFFxFr2MDqJjEkO2W1GWbbCcJmCSqlGvh+N8lYwPMmo4Lkc5Tsq3Eqt/3OqBWazzrbAGwWKQyuJA9regTUvaKlXpAg3m3bFqKych7QwYF2MuABJGOvh0JUS2R2BQNyz5WhLaDB7qvQieS11tE3F13uGSGsPVLaixnBIC9oVHIl3oK0LIoy9IWIXpWfZUP6Dkj3kXgCvMSuwvRiC2IZVJql04DpIzqOrBK69+dwLkwVEE/DCRY93EYRnqA2KUQWQu0YQiVkIoOuGUVLsBf+pnW65yTmMr+bTIJxE6TgKQ3+cpElw6acJvAH79TvwGmFUboPN6ErXH35z3x67R7ihn1KSyW16QxStS67LjaqSCByfQ+hd+tb30JevAJ061umaYBEUZVjnusYJYtzjRRjN4iC2fqF1ztqCwIkO2Gmw+mgZ6Jzj/pM8BvoVHFYoD4Yq+U4OTufIyzJVcKizaIYfTOgzPx7Pg1kSRKE1y7AYGTSc1krLBDvjsR8+953WnYWrjHUnwo5d01xwSfBUhbRK0atSKt2O3YH1c39oJE6j6R1B1hz7oOISxwwKoRH8bjuEDbZyzlEURGlVWNcVQbGhdUGFnruoxJIzxjekcB6YNXFJlldo
*/