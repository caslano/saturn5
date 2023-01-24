#ifndef BOOST_METAPARSE_V1_REPEATED_HPP
#define BOOST_METAPARSE_V1_REPEATED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl.hpp>
#include <boost/metaparse/v1/impl/back_inserter.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P>
      struct repeated : foldl<P, boost::mpl::vector<>, impl::back_inserter> {};
    }
  }
}

#endif


/* repeated.hpp
6ETPy/AMXsEy6Lzk30L1dZQE8SU1AORNUQazCVHCYXpUD0Gh7WY0i0g4WqCZW8zLmZ2w8mOuXc4T9N64fi1vYFv4hLbhhCKb7dPJBASRLys0BzGMoP4IWyNpC/9t1FO1oLMnt7HLTXaAr15kwJwv6teb57Xlmxm2O4rmeHxaMNUGVXvn8u+M13r+AiYTdi1VGOeMq6naBz/hVQGwL4YNPE7gzNmF/e9kzN8OPn++KNP8qfKTVBgJbhgchVAIjuI7bXSniJ9DGGBTAJ1ldtrBCOZJtNJDKhRfttBo4HzqjrBUpz+O2Dosl7zniI175HXnpMO8dLNAiXcYkyobJ4HHPacBHvdYgcfhWpz5WpzpWji2uSg0gNRpFBqQuOGAf/cA5kgkmxOo7rpzs2ygaZWIySCushbFlwn9Ut1FPxNyhWudjVd9ZP9nI1o1SERMRtlilNomVVN7pYltMEFQr0SJ6CxTOhKvEd2gGDWiD0y31IjOCqsRfZsY8wbe6U6684Y/bWJZ1P5hs9aA/i8JJtQGz6i4AqvAcLppfJPXhEnF7XQ/304lhQvBYa79P1D4VDuBfaTTEhXNPR3zcViZj2kfbhzENvJCqmuNPNQ/Ri7UocSbHUXDcekLEPTd6WwTPHYNSNmOonxMz45gj9TxXsgMW/DlNB5V5KzAeiG1LVLOyWY26F61RRACipAEIsWLGUPUc422CL+Wd0NII/pf
*/