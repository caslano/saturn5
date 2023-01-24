
#ifndef BOOST_CONTRACT_DETAIL_NOOP_HPP_
#define BOOST_CONTRACT_DETAIL_NOOP_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

// Following must be expressions, not statements (as used with if.., etc.).

#define BOOST_CONTRACT_DETAIL_NOOP ((void)0)

// Following always compiles but never evaluates cond (so check correct syntax).
#define BOOST_CONTRACT_DETAIL_NOEVAL(cond) \
    (true || (cond) ? BOOST_CONTRACT_DETAIL_NOOP : BOOST_CONTRACT_DETAIL_NOOP)

#endif // #include guard


/* noop.hpp
YM6uja9xX+k06y22msxEAirlfUKsiWJoG9Fj1ed755T/oB//RAWKB0NfOsxmYtFuEav8FMeSnqTCSEFHBQxxBctprhdD7FuJfbKLSC7oE4mL1c3QdnV1XVBXr5me5lI6fx5lmPVGh3jHMhUrIDN2qS05piyeZTzXt6fbrUc9fw0270p1f9973V7yvZbr96kMpovQ8ho7C6iLanKqk4lQH/TN0n22IyzM3URQvWW6sU2WYjZsd+fBgwZbgx6WdtScycf9SXDxlNDSM42dlB7lw1HFJtevf2waMLf2t8iwmOoX6badLOW1nqIfHR3lEBLyR9md8bR8LbkP53XViZY77PrDmIksdtJrFsWfHzCQqpcQbyOu8FN28OGkofSgoSBFfvqyt7fmRdr57KIi79zcwxQe1YcwY7xjY56vGTfab6vYQGfzOr4j9b3G2wUh3+IO4iXrkkASYRoTpzB6cmudjWGUDJJSyTRD84Pvj+yhSrav0ie1jBj2Y/50wJJEu7IlxMx0b3jBa26Tx0y5VOhBHrMoIVlrCuwun58eaSi3nh5+Mu8vfmcvppXxtOHUZE/xtjNnzlxQUxPL7DiR2VE9OKh9383qQG9h4EbsLlfJmDEc3c7OqvZ2pcZqDXRmWFqyudiuuiaStmJd1Eyy5+v9TYsaXDVs9kvPY03H1kDfzuxiKvV8XzCJm7QciPV/8lKahmf/Y864oXsxxEkk
*/