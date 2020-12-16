// (C) Copyright David Abrahams 2002.
// (C) Copyright Jeremy Siek    2002.
// (C) Copyright Thomas Witt    2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_ENABLE_IF_23022003THW_HPP
#define BOOST_ENABLE_IF_23022003THW_HPP

#include <boost/detail/workaround.hpp>
#include <boost/mpl/identity.hpp>

#include <boost/iterator/detail/config_def.hpp>

//
// Boost iterators uses its own enable_if cause we need
// special semantics for deficient compilers.
// 23/02/03 thw
//

namespace boost
{

  namespace iterators
  {
    //
    // Base machinery for all kinds of enable if
    //
    template<bool>
    struct enabled
    {
      template<typename T>
      struct base
      {
        typedef T type;
      };
    };

    //
    // For compilers that don't support "Substitution Failure Is Not An Error"
    // enable_if falls back to always enabled. See comments
    // on operator implementation for consequences.
    //
    template<>
    struct enabled<false>
    {
      template<typename T>
      struct base
      {
#ifdef BOOST_NO_SFINAE

        typedef T type;

        // This way to do it would give a nice error message containing
        // invalid overload, but has the big disadvantage that
        // there is no reference to user code in the error message.
        //
        // struct invalid_overload;
        // typedef invalid_overload type;
        //
#endif
      };
    };


    template <class Cond,
              class Return>
    struct enable_if
# if !defined(BOOST_NO_SFINAE) && !defined(BOOST_NO_IS_CONVERTIBLE)
      : enabled<(Cond::value)>::template base<Return>
# else
      : mpl::identity<Return>
# endif
    {
    };

  } // namespace iterators

} // namespace boost

#include <boost/iterator/detail/config_undef.hpp>

#endif // BOOST_ENABLE_IF_23022003THW_HPP

/* enable_if.hpp
SHOrkaVkIW4ZyX1DTZtAfPpzYp5jJkh8hkPddxY6Se1jfSn0BaoNT5a0WmvbENLSn+2w7c6WuJaZ9Y0G2j0+e/gQqzBs+4OxwKYSPkGVxe2SFzd6kFO1y4vET4h6E6KD0AdMnZzFQHGbjvOWCCOFbXKr/JaKfa8K3E+6Aqd6ydX6RDr33tLF7ydmEfK0HPv33c0svKOeqPTKtxH3L0xbn1BnF/3E7WpztvGVOrMZId+Txfvb1fICn83VO1qXi9vzZpza/59Ykj+pMsNgeZnAH0dSXzjfVEiVMAuwlo6WeHYjnpby2yFbHrNVeWexLcSxbPOEbmg4Ed5Kd7/sXVYWVOS7C4psOutTcMa9zoE2EWrpbMfvUSFz9+OI2xkZ5jjZs2q/fV/6B/u+Zo8wxueMIpE66PdLfCrvwhd6jPDmEy/70M1HetNDfOh1PvS7ivZ5r4t3mZ+BYxPgeuCnyM+6K/zzGYs8r6t/XrNXwl6reM02oW803eA1/zJa6XgN0tPyGnUe/Ky4dzZnob8eMPqrc4p3Rvl9z4tx+uc328X9ViUj9bTQDRR/eUzibqXjL4xbrzc/HthBwm5He4qGju5YLY9hHNJ+35dyrHRXFOZPkX1mvi+xS/wsMT81mqm+sFN+i9SdGzBO/3zrHXFPVnxr7ygP3wpXfOvoFd5864DQlVq+VUfCDzR6GhGKd1wmv3UwPLIGC4V+Hr01x5iLkNXGdcb1pqTTRPHojyVcCfqgk348eauv+Np+oX+j5WuGhI80i40VKm9r5bccyhN48nYXwozAnd/G6oziiPzuVDyuvtBDauRxmaOFx6l3Y96QvI1R/G2f0LO1/C1E4o9W/C0OtJ2/feaHv3l0TryXYpzUe1Wnk5fFA9+X+NiObTzuMw2P++YKbx5VKN8scQi9ErTd/VMfuvFo/dypiB8OYSQjDXiAc6ddozU8rbD0hHOnwxLu744U8oVDQr/hmI4e9wi+8GNzoo6nIT0tT1OyaaPGVLVdJbtzpUWvMrPMXkpWxDW26lw0Vv+GJ9Pwz+OOivvbkvdEq26FnuiYAz73mHU+5qhqg4kqrVwdv0M6Wn6n3pQdI3k/aMbwbbvvjC91PI/x+OdPhsSToHhRC6FDlNxxpNDPO2y8SM3tO4nbSrSDCGM6rPyOX4ZLOV8CPu8w080Ev/znB8lbGmkrbfIavgcdLvRLtrSLVdgJkkYj9RZXe/F7mWO98Ve8meZU86hd8vsLZhOcQtyC/KwyGysec7643e6oicc8Ndabx3wvec6XOF5CHE6J4xWHjsecK26xisf0Bm3nMQf88BhL98hezBPKo6vmUCHzOoXWC6kTcUlEP8yjnPa6UOURKuURpWRue/4P+ZL1DQc0/Kfhld785Asf+nsfevYYb3qxD33zWD/6vfiG3kYHagO4GmjNsVaM0/KjWs2xXpGw0xRPelzoeY6F6Neb8aVrzCu1PAlp6nkSx/rXxH2qw9OvHxU61rEcbeQl2C1mf7XW25MrbU/Hl5iO//sDT4r7YrXWe0joODX2R0ncj2P0JH9S6Tl1/Inp6flTErDDeMt9kRkBnn0JWsWNxrda/sR49HMy8tRnWdbLzCLVt54Z53dOxjj987yXxD1dffsByWt/s5Xx8s9zMvETonjR34Uu1PLBHyw3fGEmeOAc2CjGe4PEe76SC31Z6CjI+n3hlyduk7hakvbko44aw94WuljLE/dI/OmKJ9YR+qC5Bm3mNTOcv3vy0dOsh+KOs/HD+vJ7lxr5YZs8vt9OebPnJD+Z2BVwKp64W36bouWJxni2O8+8C7SdJ35ey3nX/5K/1TTv+lzD9z4b58231o73nnf9C7Td/Tsf2pHnI8M=
*/