#ifndef BOOST_METAPARSE_V1_ITERATE_C_HPP
#define BOOST_METAPARSE_V1_ITERATE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/impl/iterate_impl.hpp>

#include <boost/mpl/deque.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, int N>
      struct iterate_c : impl::iterate_impl<N, P, boost::mpl::deque<> > {};
    }
  }
}

#endif


/* iterate_c.hpp
ZXN0MTI2MFVUBQABtkgkYI1SwW7CMAy95yssJo4sbJOmCYUKNLGBBBRBt8s0obR112ptUiUpHX8/txTYcRfH9nt27JcIh9ZF0qLHRKYSTcc3HmttYuuxeRBsWgOvs4AJfkUEP5HZDezQHNAMbBYjEwbL/NjAnUP4c56hch0etQERbFvlMaUVpfk5FAlKVxmkK1LnSkKuCRBKFniaCt62S6gzl4KpwjCzKcjEoYFSGweqKkI0xOenAhCRLgqpYo8NvqDXNB5x/tGf+7tgsfkc9df+crELZuuNvw1GT0NeI6+lcvzu/nHYuxR0/P/SK9ppgj+yKHO8pQGIOcl1JPNUW9ejzS5DkdvJQnK9o8mSI8TSyW4nlyI0rwSptBAiKujZVDctDi3Xa0QmPWZ7MvvVdPnib1fTAMZjeGACjdEm0jHpQBH/Ewp+rhf8+gt+AVBLAwQKAAAACAAtZ0pSe25njA8CAAAxBAAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyNjFVVAUAAbZIJGDNVGGL2kAQ/b6Q/zBYRDjIbbTlSmXPIlaqYE/R3EGhINvNaMIlu7K7XpTS/95JoqdwUPqxEJJMdua9N2+GCI/OK+lwwESmN4Yez3gsjU3cgE3ieFHf4Os4
*/