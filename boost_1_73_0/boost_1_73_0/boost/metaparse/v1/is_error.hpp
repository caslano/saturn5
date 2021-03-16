#ifndef BOOST_METAPARSE_V1_IS_ERROR_HPP
#define BOOST_METAPARSE_V1_IS_ERROR_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fail_tag.hpp>

#include <boost/mpl/tag.hpp>
#include <boost/mpl/vector.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class T = boost::mpl::na>
      struct is_error :
        boost::is_same<
          fail_tag,
          typename boost::mpl::tag<typename T::type>::type
        >
      {};

      template <>
      struct is_error<boost::mpl::na>
      {
        typedef is_error type;

        template <class T = boost::mpl::na>
        struct apply : is_error<T> {};
      };
    }
  }
}

#endif


/* is_error.hpp
ke1oNtLqXjoT1u0kVv2OzCwso7I6mkmn9LBbFC6kwuJMhsoWrEtmSu9oj7nGpy7l3/Tp9ps+XT2oV0AmrrwRez51IV93SRozIZpNd2kSfvVE0pTZl2qSqbTn5iMlYCwjbDLRqjUnRHCzFgnr0YTdV70jlukIm5E2XJXsWAwpqcuVeBwXOqLq9yVGuF2LRDLSWMSIdco0GuF0vEvDPMRaYhHJrKGxWEuX3hKWzkbVHT3SrFuHxanfurVndTAidmQ=
*/