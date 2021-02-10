#ifndef BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP
#define BOOST_METAPARSE_V1_CPP11_LAST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      struct last_of
      {
        typedef last_of type;

        template <class S, class Pos>
        struct apply : impl::nth_of_c<sizeof...(Ps) - 1, S, Pos, Ps...> {};
      };

      template <>
      struct last_of<> : fail<error::index_out_of_range<0, -1, 0>> {};
    }
  }
}

#endif


/* last_of.hpp
YE2PsQ6DMAxE93xFKpZ2iDJVLBYLv9C9ioJTrAaDElPUv28AtXSyzvesO4NgFu8yNgpOxuhbT1knnKLzmPVq6mtda2OKTxzGMp74XsbU5UbNTLIiaqHYeZe6wYnvFdgDAbtfqUpVuo2ELCZThwr8JgqRMb0wNYpHLmv7lRDQyZzwPyfIVIjD0MBuKNWJBRO7qNs5xXvgrcf5svUnfhTO7iDYX6w9Pv8AUEsDBAoAAAAIAC1nSlKJiyLAvQAAAD4BAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMwOFVUBQABtkgkYE2QMQ7CMAxFd5/CojMKiIUhdOEC3ABFjUMjQlzFLojbk4CgTM73f/K3Y5VEByfUg405cC1Xej64eOlhzlGbD8Nc0jlwuTnvF3EhBWsW3JrPBOigw2OKlHUt0RPY4S0qIVTuVHrInGvbfKUN5HQu9J85qk4VWRy02d3qni16YlFsKDZWqmc+pg0xEbb3YZX4Ypq93u42+1UPp0gDIQfUkfDN6egUo6AyzlNi58mjE3T4zWgLVLDd9rvBLF/2AlBLAwQKAAAACAAtZ0pSL95abuYOAACidwAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzMDlVVAUA
*/