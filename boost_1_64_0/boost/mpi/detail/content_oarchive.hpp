// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_CONTENT_OARCHIVE_HPP
#define BOOST_MPI_DETAIL_CONTENT_OARCHIVE_HPP

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/mpi/detail/ignore_skeleton_oarchive.hpp>
#include <boost/mpi/detail/mpi_datatype_primitive.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost { namespace mpi {

namespace detail {
  // an archive wrapper that stores only the data members but not the
  // special types defined by the serialization library
  // to define the data skeletons (classes, pointers, container sizes, ...)

  class BOOST_MPI_DECL content_oarchive
    : public mpi_datatype_primitive,
      public ignore_skeleton_oarchive<content_oarchive>
  {
  public:
      content_oarchive()
       : committed(false)
          {}

      content get_content()
      {
        if (!committed)
        {
          // create the content holder only once
          c=this->get_mpi_datatype();
          committed=true;
        }
        return c;
      }

  private:
    bool committed;
    content c;
  };
} // end namespace detail

template <class T>
const content get_content(const T& x)
{
  detail::content_oarchive ar;
  ar << x;
  return ar.get_content();
}

} } // end namespace boost::mpi

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::content_oarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::ignore_skeleton_oarchive<boost::mpi::detail::content_oarchive>)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::detail::content_oarchive)
#endif // BOOST_MPI_DETAIL_CONTENT_OARCHIVE_HPP

/* content_oarchive.hpp
x6xsD/OjD+mToPHSs6ySAEbbR2w5X6z++QLCwWkGscwVTb9bK7FsKd5SDadQ/fU5uUbRT5U+pemqoT83apnCvUZLgPZZDwyxP5wXJakrae1xqOxYG9rY0se0CP5nHoTCvhHoCL/toNtJjpTYn1P5bcEIncapAzCV6czAKcYfVepAC4IHzNFU6iBKpcFtPi0uK9hofKZ2soKaqFY45vtUvhYjf6DKHxyVT4nDVKK1/4GXVsqdP2aSk138taewH0kc+63Nq19VVO8KpMHvRFSlKO+K3l1Ty+9CWwhweReH67WI9kdY7ZuPS5zkXH5UTH8uIv/l/qPwDglXQ4CP11ahIdC5M+ikAml6F8Lax4UZC7RRJscUNS6BBTdmTDnMrZVcEim3HOEs/S+Q9PgzCDPAdCxjZpTuRTfOGee/FPV/zxRmthPsmt1jh6kNs9tFfzDLGns/3wjtWYgJKqLHj7MCP/iC47OI+wTutw8FfBiFI2sCnsKKnnCFzApA2HoCDf28DHp6qtnT4f5p1haBw+kJ5r2EWcXGyTMBx9KiNuPUB9QfiRjPQPB/OjZiPANlPIPjGo9+W/T8tDLh7R6fhbUJTh/6i3srz0lTUba89Cz9HgXCUov55fnCiZAw0EvCwEx9AxSUpV0ME5b6U5mwtjQ1GsgI45kH+cRen960Ppn+WbI+S6C5e84QyVEZHnGXRixR2hgaNg3WZw5Ww79oKqxhn0XDnuT3c33RILrnPGEDg+N9bHuOuDxfBow9yDzDHLAsk3YMA8b1eyIaHyaeaq3fQHP9BjexfuWN1u+tc631G0jrNxDX7znb+gVgOHmnN1q/wccwHBv/NxXpl6AvTK/4qsmA364V7pAm6D6MlXk6+8/gjl0O/w0xnpoUl/232d7Bc7A9pECri+qRigdS4A+k6oFeoVNhGnaNy0ahwK7x/VxWv7jpUyKyE6Ozu+pBmTUgEnOgc53j61xT/R0E/RViMsJCTx4CThG5jXIHYLrohMpSD9eXEKX1gvali07kKfw9XosF2307g+7bmTFpjJQnRANXqTQBMHwdJqDTTwRtOitwXhpDs3TQGv8UxZ9vukgOr250Tg1MCLQnfB2csLQNsF0IrNkw5BHws+j8z0f+rhLOF2c3Cuoq3I43VBIrxv9aHkW1yYqocKzrfOPw4AhZbTserYurLXRBg/06Wb6oksj7N2mnzbmAhse+c3sNpMUiOV5VeygiUj4jd54tB/rJi/1ub6oMqYUzVVTZwjReMJzEqsd4a5EKs3YulVWRvspQTv7EABvQB9iqhpt7Y4wtJyhQwCZinLKR6cmKtX6WonLaS8NMKSTTJupECJ3YcIGC2QKVHM27xdF8IlNgsDIOjh9FizzKjSUMWVtS2yDb3koSWd8wlW8FOGfXTrU0pL/NUE86lc0i+j/pY8o/pzd/n+swo2n55oMFTck3r1byzVqC4gG7jO0fW05rOozg9TqBUuVE/HY4p2ZjKh8v6SD/VKn9LAiZk403VWp/SqUOvTC8hdy+nf7DXdLfhWD5Bxvhc6L0VzM5Z5x/BVCTPeNbpL+aTfffPNH3kbiZkVZUKr6Bup2VwZbQyxMJz+E1Bba7aDcewviHPwVEJC2WfnCeYsJIMpsy+CgdMdruGqUoqSoTc/MO5OvPqIux8SBDpJvdAQTwlTLkWp6CL0TLk6oMTmjAAHS1UI4yF1B3NnaiFbWIxzb7Vv2csUaFHDEmZajtoHH276ALEn5kDVllVfK76XnjbMqU6MhnLpW/KY/qE9Nh4Ur6FOPNH1sMrgHeGGnD1gTHZ+hbI4qCwdevbUUrg5MyZW9n8Xk5Ut9m1TDyjau4uP68pJIK1cWcSp2q/7c=
*/