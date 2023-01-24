#ifndef BOOST_METAPARSE_V1_SWAP_HPP
#define BOOST_METAPARSE_V1_SWAP_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class F>
      struct swap
      {
        typedef swap type;

        template <class A, class B>
        struct apply : F::template apply<B, A> {};
      };
    }
  }
}

#endif



/* swap.hpp
KabOWYcejR+UWD67N6V1eOQfCYWKlbscbYeo0R9iZyg8qMiGG6MPGR0n9fm9lfpEkfL/rs9R1OdUJ22NU+CbA7hCd5UznIFbUPE46MZ++NH2EaEXXIRrtw2V6prodyeKSEoLPXao7VW4FoTmDBdcE78X9UWFBjx/UYDRC03tzz5vtQSid+S8mUeotF17b0yX7im4Y2joLTl6DezvYfDhNIg1BqhQ+Umi/Lueo8PMIFGHn0sks8dL7mSMpD86V8YcPiWO0VUJemcvetsJf1o4677OSmJX8k5QBW3j6cZp9+bpfMq9ejr5cG7Vdp/BF34+hyxFP6Cjhdb6py59ubbBid+34nfU1eIb2jr8hanQ/3qGyROXn06vvsYtvMQfz5wj+KC2i2wsA5r1bEHuFC5mvucwUKvMYaFSso0n1OsJna99Z4JeTzNFGZFrGZWdGX2yMZrlG2JD7zIsGP7t3aQZ9Ol8B4SZd7RT09h8AcJB+B3Wow1JMk14SRNcPQRwUqodgcoc3I4uVDkoP7G2GfW4UoDKRKCy6pEHuZJxXAMsGRpgKUEDLBlvCvcdJ7vvhBx4wL3PrF7I4V2HvG7sTvbtXIWumNwT6gwnGj35lL1CikozpKi0BCmqOk2OVq+ii97Fv1BvA+ALddfbX/eNVH8L6cm+QdIu+dVQti2BjU4yQyGFqr3Cil72P6SEbmYH2kaLMO/N7DbAJx7oDoo0
*/