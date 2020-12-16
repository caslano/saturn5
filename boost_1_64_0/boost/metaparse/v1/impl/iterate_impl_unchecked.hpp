#ifndef BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_UNCHECKED_HPP
#define BOOST_METAPARSE_V1_IMPL_ITERATE_IMPL_UNCHECKED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/fwd/iterate_impl.hpp>
#include <boost/metaparse/v1/get_result.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int N, class P, class Accum, class S, class Pos>
        struct iterate_impl_unchecked :
          iterate_impl<
            N - 1,
            P,
            typename boost::mpl::push_back<
              Accum,
              typename get_result<typename P::template apply<S, Pos> >::type
            >::type
          >::template apply<
            typename get_remaining<typename P::template apply<S, Pos> >::type,
            typename get_position<typename P::template apply<S, Pos> >::type
          >
        {};
      }
    }
  }
}

#endif


/* iterate_impl_unchecked.hpp
a9BPfRbkCr1PVt7c0Kv88sWFZGBYQWVVlFefnpFWNnhd3pAMbi3nfXH9Gq0viqmz/j5eQX/2UdfCIZnOSL086hfUN8zVtine5y+t3BwhnUnKo13llROjvKDujVb/YFsb67tofRy0U6Xk046FKcrorLxrQ98ZszlWea8aswAZqxLqzzTMLR2SCX9LC9mQtCyh/o/XpgR1SYr1vry6KD+2UmiMlsgzpbTP6+gP1xzMrM+C8l80oNH6rYCyEZs9VLeD8jyjb27Kpz4djI3yL0ibLW1ulDyR6hzU92yhMa/nswUo7PqTWehAplA/btTXVXO7r8+eCPaVz6eE7UiOoB0OyqV6r64hv/snSWtTLnAlJjJGGcvy6E+fp0SpZjavTbRFWVNqeZU2rLp7a+PGnCG7M1e5YwYatwnKidWOTvLKcy7YL+pSzLVZuuibAuqa272zKKese9cK2c4lBV0nzwX3OilPnqzKCtrmTOohr7CM70pBpHZH0etw2vuVXJ8nVM9GebU1t/zytfGaX/q3yvhEXy672mfFlF9FX9dQ59rKCt5D+jPSZw+9ch9znjFsT0akB3UkuQ2iXJMnZHc25FCngqG+n+K6vcn6LK/rlQXn8JW3Tf/Qiehc2lKCbEXLJ2/VIuoVnGNKK+ca9/F6QdqGliHZ6pDNq7K+zadfpe8Kzh9B21dUfZrKW0iZNcmo8haqS1qwfVF0xN/H84fGoYP+OKge7B30Y3b1zR3SzWLB9uaTv3RIv5Pyy4Mdyo/vH5pTF9RX96LuGeyHGvq1s+uzhuTlQk55C6CwOl+tDHUtq/xaeeTJrF5Bu52bTKlzFq9tvK8nz3Gfz66g/cqJdu2CfD5P00ZljNEPMxtqZ3AurC+v/DPdq0NQF/OE5vb8sfS6Hp0oGJqn2FHzhL9LK7dVSDcC+qZpNv0cnIfkm5k/JCP5o8hbZGh+TArKsvSq4fStAXV3zdyA/FchEJxfQ69jgv5ANPnCyQhlZgnp1dao0Jy7EE8E5SLsFyyJVE5k6HUK2mTXFp/5qViNDqXXivJZhHGLkB68LhD0eUL2/KDP6pUN2cOF2qhO+tnfAdfKu9mrsLI6ew2EXpdF6MOgyxp+VW/55M8ael9M27xnI0Lvs0R4H85Xz/oyEDC+r4fOoga7dJT/jUR+FEBBFEJhFEFRXI1iKI4SKIlYlEJplEFZlEN5VEBFVEJlVEFVVEMcrkE8qqMGaqIWaqMO6qIe6qMBGqIRGuNaNEFTNENztEACWqIVWqMN2qId2qMDOiIRnZCEzuiCrkhGN3RHD/REL/RGH6SgL65DKvohaNcP4Ut8hcM4gqM4huP4A07ga5zEKZzGN/gW3+F7/IAz+BE/4SzO4Wecxy+4gIu4hMsIzkcRiEQUopEJmXEVsiArsiE7ciAnciE38iAvYpAP+VEABVEIhVEERXE1iqE4SqAkYlEKpVEGZVEO5VEBFVEJlVEFVVENcbgG8aiOGqiJWqiNOqiLeqiPBmiIRmiMa9EETdEMzdECCWiJVmiNNmiLdmiPDuiIRHRCEjqjC7oiGd3QHT3QE73QG32Qgr64Dqnoh/4YgIEYhMEYgqEYhuG4HiOQhpEYhdEYg7EYh/GYgImYhMmYgqm4ATfiJtyMW7AiizLCvuVYjMN4TMBETMJkTMFU3IAbcRNuxi2Yhum4FbfhdszAHbgTd2Em7sY9mIXZmIN7cR/mYh7m434swAN4EA9hIRZhMR7GEjyCR7EUezKx39iH/TiAgziEL/EVDuMIjuIYjuMPOIGvcRKncBrf4Ft8h6JBvQr6EvgRP+EszuFnnMcvuICLuITLCLguApGIQjQyITOuQhZkRTZkRw7kRC7kRh4=
*/