/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_MAP_FORWARD_MAIN_07212005_1105)
#define FUSION_MAP_FORWARD_MAIN_07212005_1105

#include <boost/fusion/support/config.hpp>
#include <boost/config.hpp>

#if (defined(BOOST_NO_CXX11_DECLTYPE)             \
  || defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)   \
  || defined(BOOST_NO_CXX11_RVALUE_REFERENCES))   \
  || (defined(__WAVE__) && defined(BOOST_FUSION_CREATE_PREPROCESSED_FILES))
# if defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   undef BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#else
# if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   define BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#endif

#if BOOST_WORKAROUND(BOOST_MSVC, < 1910)
# if defined(BOOST_FUSION_HAS_VARIADIC_MAP)
#   undef BOOST_FUSION_HAS_VARIADIC_MAP
# endif
#endif

///////////////////////////////////////////////////////////////////////////////
// With no decltype and variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/map_fwd.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace fusion
{
    template <typename ...T>
    struct map;
}}

#endif
#endif

/* map_fwd.hpp
jnfJscxVxjmNz4dn59fJ6Ob6UzKeX0EcB8c4kIr3nsXhzxsBhXRwJM03wcDcIK6M/sqp26+dJPfUfoC6xXyIJKYd5D7p02HIPfUaSNKxnHo5SQ4R3Xrf/E/skbeJF7EDmEeOdLU18kvhqDfq05v379/Ra3r769s3EZ0JJbmkqWO1YPMlotOs2fm9EJvNwPKHiNiRKAedqVkhLVmdu7UwTJBLmbKynJGwlLFNjVxgIRW5gimXJdPo8mo+ufgzonUh08Ib2eqabKHrMqNCrJgMpyxXrY1KGEc6BxzGM2kdDNZOajUAN5Njs7TehqcXpdUkVkKWYgEi4ahwrrK/xXFam3LQXSHOdGrj9CEGg8ItH68zhydLsSVdOXKaassRec2IljqTuZ8RFWxW9aKUtoh2LoFPZbE2ZLksvS3gJNvWd6ZpF6PIq1EFt6Xzk9XKeqp1oZf/UkQwvZW8NgpECAaUMo1YR1Sjmkyj3Fz/gaILbBPlZ/Oz8zcjreAMHQ2nNJke0UJYaSP6PJmNL29m9Hl4fT28mM3p8g8aXsy9sb8mF2fIvwSZId5Uhi3IDcllVUrOOs6fN+LgWKq0rDOmI5/BxLKrq0FxFOAgp1/a1pH1mqZxNpkOP346T8az2VWfXr2ih9Ob6XnbUfrBzt5p
*/