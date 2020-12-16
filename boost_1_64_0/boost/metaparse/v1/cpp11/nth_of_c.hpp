#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <int N, class... Ps>
      struct nth_of_c
      {
        typedef nth_of_c type;

        template <class S, class Pos>
        struct apply :
          std::conditional<
            (0 <= N && N < sizeof...(Ps)),
            impl::nth_of_c<N, S, Pos, Ps...>,
            typename fail<error::index_out_of_range<0, sizeof...(Ps) - 1, N>>
              ::template apply<S, Pos>
          >::type
        {};
      };

      template <int N>
      struct nth_of_c<N> : fail<error::index_out_of_range<0, -1, N>> {};
    }
  }
}

#endif


/* nth_of_c.hpp
uBtyeLVcXzAHlrq3DGMENFrWiSE9GzrPHkM+w8tZ1Xz+FmWy3OPysb1WKtbjJsF2m035y7yACq8VzBF1KEdZdhwdj9EflEXE5KvDGPKZOhyBOpjvedWuLTa/2rXPKd3K3ZGq3bU9vsDK2jjCzfPxhRY351tEYZ0vUs3ypfUUxVlaug9UVUtfpAyj+1+16E/R6Vwvpkcy5sKgbi69o7nudq1Cv9nyzmp3f2LGUebn6tZjq913SSjdluVtgJU+897F9IDP1fNLq/2+vHYOv1Nqwo/MtmEjeM/KcfOwo9zyvv0oP//rZT78EjP/4zOGTfWtG1vac2vtyxuC8Fxvou1v9g0gKkN3MkMbgf5auv/tr53PyOGqX1afw9NQv0zhWOXjsH76LBIECAutC8t3f9ctb2jDvh/sOcR1DvXQvRjssawxfWvUPZYl3jBwf4z0my2BsNMbCUepjeM9z9UUN8nG2aI+G+Qts3HkfbtLvMFm43getpbyVtiyUjlxb6JJ9PUFBl7oHBuCvlkY1scLwFv7zenPfO7hhGpXplvD5dHCanls53GMYHl9QMvvfhjH1ov+OVRiYfBz7YgNIXBYz3DgNlWL81mQV/3GY1r5sDuF8sh7kgdQnvNyctlGz6O1Na9rrW+gVwJXNzWf2OQ9DzmVae1r2hING9obmsxbgXjbTaZvqI4cvb6KQSDr+0mY5vq2lkRb+9KWNQ3LE/QYYUtzUxud2TVvQ5agH5xGZc100YW4gaHBrmRw+lbG+P2qJij/2a8bAnjDkHatiFhDO5UPdeOk9VE7fxF9rhO0sMrBxESU6X89TIvwrWk+PmF3mRPtG1saAoqEGzQ1iM8a5unIdHqXsb6htd07TuzXdVPZqBy9A5sTNPcb3GmnekEJQxJMOZ9EOVHvpWsa6cIlVd2wvH1dW66oaNtQGIiAKSL2E8PhbAy3cShMY5ONs3hK8tKj9mlc0diwHG/+jVIutKYn3wPsCdqxozdFipHazb4aPZRxWlQn+jyLYY7fVa3ui0G3lhjMYp5casLQaYAhfWhaI9Ut581liLOgiJ9ldWKW1gGoBDSdZ9/qyR2SxmwKOzTsGYktHZktiY7ezV4ubr55I8pGybk9xTnzegoLXEmqZ9xjyQnK1kHxdZ7tY7m4zRR3jDeCcd6ReGNqi9DdSyxfsMBFn4XfXu3KGu5kaOEkGeRxo7AHVPBddxIUm1NG5PaAtla761wvm7V6iusLeUO+D/baVmGvDVSLt8xE/DYbz+NFOsAJ/TtYDX2N8SKDeUevGouGlG3ZC9tyWNg7FEft4torO6qx5oB0OZc8Q6Slg3xIO5PxUhrzYM8iH+9ZIt3EabpnU1joQdqlbKJ+2drgKsFAB6pko90S7Y1rG6gzr22B/lEw7a0NDYmVS9tW0tvaQg++H33b7CCT8A0mHUUYkoLxITg7tdG/A4g1SfRpGzb9yeN+nYvTfTtlAblfpwAkz9R10ZkpuiHq+ElGHPo/v0VJZ8ooWuqKShMHUOgJc5YgPdC1JWG0RSJFS6UZ0lU4O3Wu6HcRyx1615v7HoKF3h0unMfI/AeFzH9IzV0+TOFXF6l7ZEre/ruIZf2U6WF5yG5Udskk+FQl2s662/lKzi9AmOKxDwZagO2abH4urYt4XmLSsKfjwnw66APAk5ys9gZV+p6pam+QaVAa3phUNC5TOGapdavPQl+cDh5gX96W2bMyRXKHcImXymSGWJausPZ6To3mZKksRJZW4D7ClUKWphuLIz1At8N3JpKk9qWI6BRIi6OrJkbculxVnec93L2gY/eawROpx65ReuqL0OVXC/m9FvmkfrtO5bue2450uLsm9eIiv+1uQB6rUwg=
*/