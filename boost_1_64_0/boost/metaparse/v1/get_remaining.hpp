#ifndef BOOST_METAPARSE_V1_GET_REMAINING_HPP
#define BOOST_METAPARSE_V1_GET_REMAINING_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_remaining_impl;

      template <class T>
      struct get_remaining : get_remaining_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_remaining.hpp
B9W6jkJR4VBonYuThGk6y90QAToWMzrpsnFB+fqR21+ydl2lZE6xlJgvR3E2BnCRC6jQaQmoZrw8fZHNvgDjbESH/S2/jVlB/T9erFeFJ39xGnHP9xHRloFVbhA8kjqABIuKkDc+pwtw8TBS5OhhNbF6I9HXsZ4io7hfa8ucQaYEMNes+JR1bhik8Sn+/TpLOyaI2A5i1tr6XdPx56CLXpkS3/FR3fB2GIatpxjpyr9yPaL6ouAykiK6lJLWKAuMdqTNn3aYXhy9MolbkMzrE29pRs4gFklaNc3P1N3AYoE6ZOymQFlP0AbJoaTpxfGPAE1TESe2M3md7DgJo8bpxyS/sf+kf2CwdPd11e4epKjQ25odZf1dY9PHbUKYVlhOYhRSXVyRAdlmond5YebBIMunYOduRszueOd6Ki3Zm4RBsTEJ9zaf4JU0Q666LXgSEjhBZt0JGgID2Pjn9YnQQFPyDq61aCuY5bBMkEIv0xTPqSAq3CmF8HJ1DLP56WoIquLpGp21nSYjsvd7gKiUjebIOiDke+vyehJs1T/nXPRjoaeNC1OqtZ6ixw==
*/