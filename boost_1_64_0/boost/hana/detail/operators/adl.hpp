/*!
@file
Defines `boost::hana::detail::operators::adl`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ADL_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ADL_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail { namespace operators {
    //! @ingroup group-details
    //! Enables [ADL](http://en.cppreference.com/w/cpp/language/adl) in the
    //! `hana::detail::operators` namespace.
    //!
    //! This is used by containers in Hana as a quick way to automatically
    //! define the operators associated to some concepts, in conjunction
    //! with the `detail::xxx_operators` family of metafunctions.
    //!
    //! Note that `adl` can be passed template arguments to make it unique
    //! amongst a set of derived classes. This allows a set of derived classes
    //! not to possess a common base class, which would disable the EBO when
    //! many of these derived classes are stored in a Hana container. If EBO
    //! is not a concern, `adl<>` can simply be used.
    template <typename ...>
    struct adl { };
}} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ADL_HPP

/* adl.hpp
ZPIwIgvACUM5cvY1Gkgx4jsCbLO7dJvpnAiY6l4xvciODexzyUQYqeR+oHtpnjtXU/UXz/Z/dPqIUPpplN3Q+DNpBPV202xrQ+cv4kz83ZLk9xXqbfYHVtkz31/xv2tp+gz2IGDyrecbS9Pn778jXvqF+oCQr9+vzvpgLj7uPhU3W8T9ScUVIE7K2fX7EIU2bcmvhf1fEWCoY0oWXAyY9Hc9UmjP9lIGO3/1YX2ut++sx2t22Hs0Zupqef0iHMcxsZBlOe3wdE/W5ADy/XkM6aCu+J3UtYRw135LEJbjudS1H+MAFz5jce9bxC/G77XL0vvTFSJ+EX6/SsWXib4rZt6gE+ddwfAihquWifvipa4/JA7WHPbnQlHHqkB/Vk+jP9cCR6Z5+rLDp1nP/H+1NMn/4YC5+fM7IY/Db4+zUfTPPQJ+vOqfatU/jxTtWy365/xltn03EX8D2/AZy0R6EcYc92GpnzHp9J2NE0izWtJkGdBGvgxfoE5hK/EPlqTzfATgOk/AYr/Spyr/YKcBThzRDxbnWPb96WIsHbc67SN7m4gDfopHnKHaaBvDxwXKhzrEuqOFK5TezNGkXvFrSs/l9HeyTttF3yGdjz/IdmsS8e+hrkbyz52rZbnUPVPm0bI60cfe7sduCBc7beBuAu58obfkuxwsn/qYvhdtYVr38WK+AMY+Suo+TlmmnC+dij/3Kr1OtxrvFaI+zgf5qfyKZb+iPrsR5jrly/ItU4/UO0gF0ROBJ+8wPbgyGSsbVP5PEeVFnG+DPvLDLPEf5/y7K7uFvUL22Sf6IMM+70P6mZ6t/z3+bJIz0jxlu1qk3r8tTsIpGdB8tV+Wd3Vzqx/6frlI+IKrkfdL2Hb7V9MHSemhvprOQpxct852Y8PHKx8lpbxrq/AAD77LMgy8V87IT8Z0++1IfLt1tbXvPIV6L33+TM7E8r1xykgsiHgLEhjQ6a9SwljfRRLWLs/HPTXSXyXCW1y4hPHtHY3CJzpKSZqlgXPg0sA5cBnttGsbmsxIqm3mPYgVHHcHj2Dc3Y9x5/jaG8oSXpIp8T4CEE7ztXGOxXvEPnpC7APOWa31xun3Es5FvOTN5yHMtc77FpPjG/AU33yG4MV860q8xcWPZX5xiS3zBaup+2ca4ov/Er8wutDPDbmuaLyC6CLNh7kGI976ullt8Z6r1oJJVaeL2aYmrb5/cYmav8eS5gsUTeAxnnpL0pwM0HyxoCnLeZmiCTwbT5qXr5b7mfBe5WViPzKp9iNXILz1P8JL5HyS9xOn4wNXv7eQpClWviHnB3xDer+3cQR5iYeRj6h16Bjlz2Zxnrm+hHP9lUcw1y/EXL94huvvIe3u2lzVb66on25rfaf1VUdQl7dBXvuPGY0jdcdVv3nxkPYTbjzIN1L0GKrtbN0CUQT1pcUs0+6G7hbKEMWbHUJeq+78LBSwDjypj1/0SU+9gfQ7ivrIdW8x5bgSVmJhoNej3l5COcT9q1IlI+X6lMl0ACLWJz3vlnu8eILGsBWBd0hWqnvAQnbb4Pqx3IWbM636DabXTnMMcQ3gHV73rkHoDYTC6GrB64AffAPhGr9nlzjhdwHfuJrvRwpf9erM7e/D7quQd16LozeLdYZlD9wxLoiuVeVhOYLleZurn3rzTNbvHW49ID3t+/ldiL90RjwFc0De8eP7fF0ZqS+D9rtT8hUjRxJ3/Ki613zlPQ9xTEyuSPriuhX49J1a5PY+1w/EARw+6zQe/MLPuF2UHwHFr8JvCdXVdma2nuj3y6J9Zbt8aJrtIv1xgVHcUzgj/dh0121ZT6Ejw7BwUUndEt4zz/FhgNS9zswuv3bTp2hjU8pnveZFCxQ=
*/