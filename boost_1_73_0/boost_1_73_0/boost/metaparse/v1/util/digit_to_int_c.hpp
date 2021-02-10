#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_C_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/error/digit_expected.hpp>

#include <boost/mpl/int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct digit_to_int_c : error::digit_expected {};

        template <> struct digit_to_int_c<'0'> : boost::mpl::int_<0> {};
        template <> struct digit_to_int_c<'1'> : boost::mpl::int_<1> {};
        template <> struct digit_to_int_c<'2'> : boost::mpl::int_<2> {};
        template <> struct digit_to_int_c<'3'> : boost::mpl::int_<3> {};
        template <> struct digit_to_int_c<'4'> : boost::mpl::int_<4> {};
        template <> struct digit_to_int_c<'5'> : boost::mpl::int_<5> {};
        template <> struct digit_to_int_c<'6'> : boost::mpl::int_<6> {};
        template <> struct digit_to_int_c<'7'> : boost::mpl::int_<7> {};
        template <> struct digit_to_int_c<'8'> : boost::mpl::int_<8> {};
        template <> struct digit_to_int_c<'9'> : boost::mpl::int_<9> {};
      }
    }
  }
}

#endif


/* digit_to_int_c.hpp
AAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTM3M1VUBQABtkgkYM2UwW7iMBCG75byDqNUXCpSE8ruqlGIVEFV0O4WBNne02RCLIIdxYaWt9+xAxTtvkAvSTwez//NP1Zig9rkmcaExUKWil5bPL6rttAJm6Xp0j3g+SllMf/ciXmXzG5Y3GJTHylUZCYDqfIK8+3YP6L2uwo8vAthOBjA4qfHppnBCNI99mHwAC/qQDvhAMJRNHqIKOf5d+qxNbYHbCOwbIF2C15mW/TYREmD0gS/UG5MFcF3F5KYG6FkBHmt9FVWemzQVvkwvDK72mMeC4f3o2+Eb2FtGyd46uMGJrWwp7QokMW5W1BKp5+wypiGDpyXscx2mFzcgUBBaUMQCHgXplJ7A2eOqdCN0sIy9iGYgjYFbVOxrkacq90ukwWoxqaMfakC2m/2pk9fQub1vkC/I4g4780W63S+jHpWe7lYpTy8/3FvdYmhVhtOZ0tRYxedQkBCJwXSIhDjRpSwBtsaeuvVZDpf8Vq8Wbu5VOSX0EbfNbWrZstQhatzVO5kjrPtFVtRHsGNPysNtmAqdLODKtPwhijB15UyPosPLtditMqoXNUJs+Z1HZwvi8dmJBbBf4167A/ZHzxuSJyGvW9r
*/