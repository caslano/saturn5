#ifndef BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP
#define BOOST_METAPARSE_V1_ERROR_LITERAL_EXPECTED_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <string>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace error
      {
        template <char C>
        struct literal_expected
        {
          typedef literal_expected type;

          static std::string get_value()
          {
            return std::string("Expected: ") + C;
          }
        };
      }
    }
  }
}

#endif



/* literal_expected.hpp
4JPv/wqfVDC/Cgt4nAQfa3uEQSbVBj2DWr0aaOSvfFzfYKKC2jvdV3lzdFhfJHH8r9iJs0HLDvSHxqdi42/wxuMwH7ZifuYRHDnTHgqFfOpDOrWaLOUtoxK83QqCv5qoIPIhQmev+0788KhKcQ26vMdFFfsMlWIl1oMdF1eptNBBsuibnKCYSx/CYXsBdcDX9NH1swHKQQDl60cByj9OMyiTkAQU3PGNYv7lYU2chMuS7vOSk5/YntUO6scVl+txBInSSVGwHwMawc8pMfck62qh4iLRPy9KqLgKbcGlURnfuAcVAzqDhIrNMitJuFWoaJan02G19HVGk8eIJfrqynZapTrhtWpvo1K2UxBrzlWupYufQ02bnnVE9I+UhhKETqndqUF43JnbThAusX5Faz0AqIsAvQ7EDBxkbHdPQkAn+cd9Vezt6Dc/phjGXaBXsRWGXjxC74yioo/+PO1+Pbuv4P3t8jC63yFU1MPTGQ0MrefLGqWNiNUmBbpfXB+ZI52nR9fGUyYG8hgb0xGDnQ4wFzDROOAi2Gu8oP4qFFaGsdMganTRyG/rHiCF1WP0NigBk7cjSlhVSwMl8xa2fiBU7Kg5ZPIe0gulFwPV6aBTxw/2qgeP00F/90jvqSih7Bp4sOrSQYhQTXHG+qpTYIsUl60XygbCjcrLBmE53gahDN3MrXHUlTv8jy5owdKTscJjWCvS/+gs9TSO
*/