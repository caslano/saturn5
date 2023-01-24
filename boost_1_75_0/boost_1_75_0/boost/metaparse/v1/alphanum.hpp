#ifndef BOOST_METAPARSE_V1_ALPHANUM_HPP
#define BOOST_METAPARSE_V1_ALPHANUM_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/letter.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef one_of<letter, digit> alphanum;
    }
  }
}

#endif


/* alphanum.hpp
d/8kfG84/zTwfTsh7r8D3/D5Z4avZ+mfgO+45wmuBa/QMf+V08BXGfmfwrfEyuFbvfpPwvfEeaeB75D4/xJ8L+16ZvjWL/kT8P11OcE1iVPnhJd1PQEYy7e9MUIf07MHO3+ToR3AyrgzZdlClE7CSR7Lk46+jl0IqsJLmsbj0IS10h/9l4iQHKD/L1G9Pv7+Xi1/f9qJv/j+dYt172/1kuAzamzQeA3FnnFpWV+MpMvjMPWd0IzBtd5u5g3SmAZfVMbIfKAD9ZTaew7Hj8hYvrrx3Opk/sFKFl5Vnq4T8rRAAswuqsNR4SSXpxNIng5YMhpBoh5p5hJ1Nby2I732FvZaJ733Wo4u8Tyl6cvv+XuzY3dqEy8OyDgmnBTWr9bc+hWwgn4EL4cKMCAQlszDP/TaOu2B3AasvvKmhJpHSS32cm6Kkn33crgZC7wZ2SGs36Plbh7hfvxxLRcqTc/w9AXjopOBmrx4jTkSAtX+u2dIbtn7TFN/yPLhOn8IQ7k0OQAoJ/rnJpHvKfH7UzykLUPhIYnYHFREoWEM2+XTQrPUhveZ1Kp60LQB7Jx9idaxAx9NER8csfQtUx0Y1scNDgyIU3xeV2tMnXNkmHHOKZTzDjW02KyywyPNfOJpcm13fZSdeLfIwU8DIPbm07byUv9bMc2w8DKceZZ9SYXqTMt6tMIw37GLouf77Ao+X9zrbM/ahmpzTfNJlaJd
*/