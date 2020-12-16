//  boost/filesystem/convenience.hpp  ----------------------------------------//

//  Copyright Beman Dawes, 2002-2005
//  Copyright Vladimir Prus, 2002
//  Use, modification, and distribution is subject to the Boost Software
//  License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/filesystem

//----------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM3_CONVENIENCE_HPP
#define BOOST_FILESYSTEM3_CONVENIENCE_HPP

#include <boost/config.hpp>

# if defined( BOOST_NO_STD_WSTRING )
#   error Configuration not supported: Boost.Filesystem V3 and later requires std::wstring support
# endif

#include <boost/filesystem/operations.hpp>
#include <boost/system/error_code.hpp>

#include <boost/config/abi_prefix.hpp> // must be the last #include

namespace boost
{
  namespace filesystem
  {

# ifndef BOOST_FILESYSTEM_NO_DEPRECATED

    inline std::string extension(const path & p)
    {
      return p.extension().string();
    }

    inline std::string basename(const path & p)
    {
      return p.stem().string();
    }

    inline path change_extension( const path & p, const path & new_extension )
    {
      path new_p( p );
      new_p.replace_extension( new_extension );
      return new_p;
    }

# endif


  } // namespace filesystem
} // namespace boost

#include <boost/config/abi_suffix.hpp> // pops abi_prefix.hpp pragmas
#endif // BOOST_FILESYSTEM3_CONVENIENCE_HPP

/* convenience.hpp
UGA8OkwSP8f2nKDAJOswLvGYx2AFJkWHcTKjM/F7XgMtUZmxfsAWChIzh3n4uOF7Rn5wKCYhrwQzvSoztwMWgFIQV4IVTLu/n1mBVAtjETyLwAX/livgaRYeI3gugQtWling6RZ2I3gegQuu9lLAM6ycp92bwInBX/Q1wTOtnYC2VQIXvN6igLez9gea2E1wP4CvV8B9lq6x53mWyvMT+xLPbZg4SqGcbeG5DRPTFfD2Fp7bMPGNfBO8g4XnNky8TwHvaOG5DROXKeA5Fp7bMHGqAt7JwnOdiQDcWwHubOG4degKnueqPH+7D/Hcholb+5i0u1h4bsPE6xTwrhae2zCxUgHvZuG5DRNHKuDdLTy3YWKaAn6YledWJv6ztwncw8Jxu/mvgPe08Nw6dAXP81SeL+hNPLdh4nSFdi8Lz22Y2EcB723huQ0Tv+plgvex8NyGic8o4PlWnluZuEEB7mvhuA0T5yng/Sw8t5v/CvjhFp5bh67geYHK82/yiOc2THwzz6Td38JzGyY+oIAfYeG5DRNXKOADrDy3MvEEBXigheM2TMxXwI+08NyGibt7muCDLDy3m/8K+GALz61DV/C8UOX5qp7EcxsmnqvQHmLhuQ0TRyvgR1l5bmViOwV4qIXjNkx8q4cJXmThuQ0TH1TAh1l4bsPESxXw4Rae281/BXyEhefWoSt47ld5nt2DeG7DxD2HmbRHWnluZeJ2BXiUheM2TLxBAR9t4bkNE89TwMdYeG7DxDEK+FgLz22YmKmAj7Pw3G7+dzfBx1t4bh26Ui9EhoEy6pbSPW23WhItZFoSDREtyc1aoCWR0KEl0XKuJdFEoSRTH1jpRv2Bj4ak7jQamnXvR91km1E5WMuUDm0KWnu4TsFwNcNItunkyxWMpGYYHpt+nqFguJthuG26ureC4WmGkWTT2591NTGSm2G4bNaqJxSMlGYYTutMk+qEpS9+0TWuRjFbKSHVtjesvD1CwUgTGC3qFXu7mBjpAqNF1WKrgpEhMFrULtYrGJkCo0UF40wFo53AaFHHKFQwfAIjATVD64toblxNY0euST/bti+snL1FwWgvMFrUN+YrGB0ERosqxygFo6PAaFHr8CoYOQKjRcXj1c4mRieJEV/3+J0C31nAJ6R+aH1xeue4GkiJUkIX276wcra9gtFVYLSoh0Q6mRjdBEaLqsj9CkZ3gdGiNrJEwThMYsRXSEoV+B4CvkWdpKuC0VNgJKSWaH3xSk5czaQuR9NMrH1hw9nLFYzeAqNF/WSGgtFHYLSoovRWMPIlRnwt5YuOmpZC8C0qKg0KRj+B0aKu8isF43CBkZC6ovXFpI5xNZaBSgn9bfvCytl9HTSlhTBa1FsaFYwBdn1h1f8U+IECvkXtZa6CcaTAaFGBKVIwBgmMFnUYl4IxWGAkpMZoffFY+7iazG3tNU3G2hc2nD1fwThKYsTXZ8Yp8EMFfIsqTYaCUSQwWtRqdmVrWg1htKjYbFQwhguMFnWbxQrGCIGRkHqj9cXg7LgaTkelhJE2fWHl7HtZmpJD8C3qOX9UMEYLjBZVnRUKxhiB0aK2c7yCMVZgtKjwdFcwxgmMFnWej3yazkMYCas9a1l/6JqPNZVWRmsqjSSZqqtAMlXXgihVV4SsqTTPRGrTtg9iMXnYV978MG+TV97DgvzJ4Y7gcU88CA59Vp7eaId8mIiuUc1P8QQxZ6LEnBox/fhOEHMlSsylEdPP7QSxpESJJWnE9AM7QcydKDG3Rkw/qRPEPIkS82jE9CM6QSw5UWLJGjH9bE4QS0mUWIokRiOutiEgT57R14s9FMC/1j7O/jp8qy58G0foWjywpvev72Yn5l7ngZ0=
*/