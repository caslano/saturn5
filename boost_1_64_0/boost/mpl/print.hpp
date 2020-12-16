
#ifndef BOOST_MPL_PRINT_HPP_INCLUDED
#define BOOST_MPL_PRINT_HPP_INCLUDED

// Copyright David Abrahams 2003
// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/identity.hpp>

namespace boost { namespace mpl {
  
namespace aux {
#if defined(BOOST_MSVC)
# pragma warning(push, 3)
// we only want one warning from MSVC, so turn off the other one
# pragma warning(disable: 4307)
#elif defined(__MWERKS__)
# pragma warn_hidevirtual on
   struct print_base { virtual void f() {} };
#endif

#if defined(__EDG_VERSION__)
  template <class T>
  struct dependent_unsigned
  {
      static const unsigned value = 1;
  };
#endif
} // namespace aux

template <class T>
struct print
    : mpl::identity<T>
#if defined(__MWERKS__)
    , aux::print_base
#endif 
{
#if defined(__clang__)
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wc++11-extensions"
    const int m_x = 1 / (sizeof(T) - sizeof(T));
# pragma clang diagnostic pop
#elif defined(BOOST_MSVC)
    enum { n = sizeof(T) + -1 };
#elif defined(__MWERKS__)
    void f(int);
#else 
    enum {
        n =
# if defined(__EDG_VERSION__)
           aux::dependent_unsigned<T>::value > -1
# else 
           sizeof(T) > -1
# endif 
        };
#endif 
};

#if defined(BOOST_MSVC)
# pragma warning(pop)
#elif defined(__MWERKS__)
# pragma warn_hidevirtual reset
#endif

}}

#endif // BOOST_MPL_PRINT_HPP_INCLUDED

/* print.hpp
Xzh5giirAlrM0u24T5mmAJVTjUeoFqrkq7RuptuYkaaeNGKaFQ+lUHtcUPFBl/lgG4xDmNnQt4czfIQVZfilBB/eCgJyMsvwR2PbeCQ+gIQ6wRtKz2yGPFybeKsIo2fY4Gc7LSOGHgrcYNDnPKEPKBl2iDMK2GR9gMj3p5id9KK6N0v5tew0vP61p1geYaIM4o4B9vD6cfIrc4l1+jSHS1yrSwRE83vVKoGrD0rtVDPc+Ed3q5EisepETVFZDIqWbcPiFI2vgX2VsPhwGY4iPhThWWj8K3HAFj5/l9zzQg2ZAxwlf2wAcDEufhDSz4XXc/37upu0KgStCjmDeVXajqt4/hK+mjeUvk0V9K6GMUlVL0L1IpY3U6Rua1LdIq67wFb3HJz5gcJq9KnEQ4MsVIcSozl0OHywyUXvHtAMtaAdzzjLvNl8Ltt/QgRHF/1p+6J559j2JxOpy35j87+0vLLNNeP8iy15Nf6fSfLqQvUaV/cElNc847Ke1rRFOKSLspWQMYqzk+QBOFmEBRV+QPk7AkSvOc/lP5NBjYuHQCCIu//kwnFdWEmPHFvhC5VDACqQ8h+2mupwcjICpdXOps1z3ytx9BiE6f4BnulzqE1NnEcbDfTYf1q/j5JefPU11kmhm08KG5v8KpwfUjw5jfvoxjm2HXa9ST3mM6zGN925W8zTaZeZlruFBEgSsPE52R2hTaakjuCm98pOgceJDNDoANCdCtCdBqA7HUBKoXnXAaAnFaAnDUBPOoAeBtjakA2Ap+MyX7wkO4fm+g+zUXAQ7v60lni8ojuWwKKrISsbGORtqmiTiIicgr2bWW2NMQL9zrK3sCRauSpBSk/Jyuf4zwtUiBCiidRoePM2bUZ8xZKV96g82hTihWTjATrw/SXBRe6DlIvGyxKusjbGDCV3UeNlCUDgBHR+ViKp7dUAXLL6ef4DBDm2X6Kxmdp+edk+gF9di0zpD1+jazT8wAyZy9B2RQLac4KQMLGktoNtAgEpjW+mdHw5AJcs/y7/AYa79qFvXqtvy1fpTAxJW2OzH6hJ7n2cC89OCVdFGzbNW0rMYw2jhBdrhrh63pKPq0YtJT7WeM3RHIjRNHg0sf4s6QIdsM2bRMd5kziCeZM41LxJpJ03Ce1lyTZv2jrMm7YjmDdth5w3benmTRsWAW242hYH58RJzSnhWdxq8tcA8Fcc/JUwR/M0jGYrRrONQJecdPRtsybRcdYkjmDWJA45axLpZg2+tq6TL21IiQTntJBiWsKT2DD5yw/+akmSlv0xmkZGWnYNaRkvMf1JtUJatpr81Rf8FU+Slv0wmq0Zadk1pGULOKeFvl+QlobJXz7wV0uStOyD0TQy0rJrSMs4OCdO3y9IS6Vb9k6jW34so1t2JWmZRrfk1rPT8FyvDM99BHju1DQ8l5fhuS7Pc3O2eNKs53pm1nNdSUPpZD2Xk2Y9l5tZz3UlaZlmPceNu9LwXI8Mz30EeK57Gp47JcNzHwGec6bhuW4ZnuvyPEcUTVUtXRnV8iOgWmalsBwNRWY515WEZcflHDEaqLWdEcZVi9ocpHmT0q5yINGdnOik4YsDEzqqrh3rIqhAYIuVlo00b1JaN6S5k9K6Ez1agTeu65bTN7YFlNxlS3Qj0Zuc2AOJ7uTEHBrcFhumuST1VT91oocSUzrakxJTOnoqddSwkM379HUn+lQ688v8Mr/ML/PL/DK/I7Lfes2Rsd86bvZbWSmLMoKYOdfuSqvpNOfaoGiqKYkrY0rSlVbTaUxJuHVnmq3Hbpmtx660mu7EfKt7Gp47JcNzHwGec6XhuR4ZnvsI8FxOGp7LzfBcl+c5GCSkmEz2zKiWXV61nLM=
*/