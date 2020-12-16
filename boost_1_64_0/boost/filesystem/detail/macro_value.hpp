//  boost/filesystem/detail/macro_value.hpp  -------------------------------------------//

//  (C) Copyright John Maddock 2001 - 2003
//  (C) Copyright Jens Maurer 2001
//  (C) Copyright Peter Dimov 2001
//  (C) Copyright Darin Adler 2001
//  (C) Copyright Beman Dawes 2002

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//  Library home page: http://www.boost.org/libs/filesystem

//--------------------------------------------------------------------------------------//

#ifndef BOOST_FILESYSTEM_MACRO_VALUE_HPP
#define BOOST_FILESYSTEM_MACRO_VALUE_HPP

#include <boost/config.hpp>
#include <boost/assert.hpp>
#include <cstdlib>

namespace boost
{
  namespace detail
  {
    inline const char* macro_value(const char* name, const char* value)
    {
      static const char* no_value = "[no value]";
      static const char* not_defined = "[not defined]";

      BOOST_ASSERT_MSG(name, "name argument must not be a null pointer");
      BOOST_ASSERT_MSG(value, "value argument must not be a null pointer");

      return strcmp(name, value + 1)
        ? ((*value && *(value+1)) ? (value+1) : no_value)
        : not_defined; // name == value+1 so the macro is not defined
    }
  }  // detail
}  // boost

#define BOOST_MACRO_VALUE(X) boost::detail::macro_value(#X, BOOST_STRINGIZE(=X))

#endif  // BOOST_FILESYSTEM_MACRO_VALUE_HPP

/* macro_value.hpp
5Gf+XnT/zZGgtKfDowYR/dvQTHx7Eh8GwSxdxH0HccpwjNMcgBSKdeO5oR1kYr4pwWh/g8cCJ4TGERYaGsB3TofPQIQK2PA6P4mtbBOIVIdQMlnqrNodPE7uJVT77x+pKuggdXxzjrxSPJ5OYwCL+YEaurUO6oCbEzdqu+mru22V8c1hSCVxuH9u/ROkRSu+MREtCu4aEm/TFgGsxWkEUf1RTM57C5PzwbrJ+VVGk/NTU4QkVfQ8rIGfJKCbEhgnF3CBvoC18YIkWcAqZspCV4Ntd7LdC00HTdd8XKwoEC3d/haqxV6kAl57QyJVj/Z9x5isKI/+Z7AXjWZPmh4lvTBKekGUdE+U9KIo6d4o6WW7ou3Hrfledt9s+oqk3WvUtrzPN5vaam8bgz2wSC+Okl4SJd0dJZ2Yj2j/8J1edtEsRwV5qVvXZ55DqLn166gBP18H+sz1mHLDs6rqnCamDDsCpaxIQAMV3dRb9EqcnmhI42a4LImEDi2/neydYhAF+DS5SVGhnbebcvRICA8OhNLDwlyKV7uom7rotsPcMtejdYKtclLj16zAiuCyVj2GkUg34qkKBzK7SA9NITDs4Be2ow5Oy5x723EQNggXsguiNlNV3Xq92BLo0OEn8vHTmr3urbASledj5VnRj9vxnZro99vn46uPen7k9IIo6Z4o6UVR0r1R0qHnW99//g0rvrH040FCtd4gsd4PmP2NedBQ9gUatZlv8D4Ugz1BshU/1+pnxWP9Hr4o9ZEdJb04SnpJhPrM/9qC/1ufCsZqD5Fshf/pW8G2lt8dhX+iZRr//t1y/Hvje551DPr1Ah3fq4s4XoOIQ2NFo/YxDjXkom4GU7+jePMGjQg1ASbePNMXxJtVACe0FyGX0Nkghr0y0Sz3kDrG16ZtBLX8sDMn7ZHrGq0LTqCLCVQb+BKHinz/C0Ia738R1i0xjU8/fGnG//5VgR/N/olQCathd2vluYlAtVkvGqGM9v8qvfeeDsbkf2B8C/7HvRqM3f/AYVifGu+/cTS16X7Jx78w5//I8zHWXxWhElbV81Ht2QtU+CNPRoV3q/BrnoqtPkMHzeWxH2hLe9rcAv+BvW34HhcTuo79K3vr34PQRhOa9s3uaP0lqQV/ff/ZlvK99C8z/ot/ixGfDWIBwufKAht3Lp8A/2wtPSdcLMACcseWthMzHf4B5HrBR0QQKoEU2NNc2ilOOkMWGhQR5IxnggQCQ+SxnNu00n+udqD+83Ne0Pi1X3aQJzbJt/l6+IMyph7MQnmUypbl8PcF9UbtSqaRIUkTADcCIJIog0hwKYF+PAxpdGcA30hAH9P8gCa4Qkd28g6HddVm6pob+InR+yANLv1ZSa7U2SsJwphBNtP40LaPWQkvCQeAMFviTgnMVKIzfwzTXQzIhhe3veEEFMQxVXi6yCtgCzcgCobh8M1GzAveoZ7o6Ogg2AnFo6OOn81lttle0YXarzc/Fd/yuYPyWx6UN+/zukxnp2/P1vrAmsZ4E8x77UBz1Cjv1P/3YabxKqU7L+QpPXnRwvNOl233SmY7ikihjkAcX2h183Q7yi6NxfgpE3+W3GVD3uiu1zE03zdXi+u+k3FwX0iUyYl6/EpyUo4I4a67r0izBSg53OhbLxKed9oBiKg2eyF7CVNDAeWC0nlSETKPNZR5iEhHtl3apS6mDpmXWlsWjytfY+oKF2/F0h3wFX9nndRL58V6MQ3dt7CgoDskqBrwL7jSZzjgboOu4BK3zo4CdSP2JHxpcQvqZe1Z1ytiqFhz6PGRrhPQoxCicAUeBwInjJXMW9908oS37hpUCv4OlYJ+qRR8/M1guLljvEJBbHyWAa9Iumc=
*/