//  win/chrono.cpp  --------------------------------------------------------------//

//  Copyright Beman Dawes 2008
//  Copyright 2009-2010 Vicente J. Botet Escriba

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

//----------------------------------------------------------------------------//
//                                Windows                                     //
//----------------------------------------------------------------------------//
#ifndef BOOST_CHRONO_DETAIL_INLINED_WIN_CHRONO_HPP
#define BOOST_CHRONO_DETAIL_INLINED_WIN_CHRONO_HPP

#include <boost/winapi/time.hpp>
#include <boost/winapi/timers.hpp>
#include <boost/winapi/get_last_error.hpp>
#include <boost/winapi/error_codes.hpp>
#include <boost/assert.hpp>

namespace boost
{
namespace chrono
{
namespace chrono_detail
{

  BOOST_CHRONO_INLINE double get_nanosecs_per_tic() BOOST_NOEXCEPT
  {
      boost::winapi::LARGE_INTEGER_ freq;
      if ( !boost::winapi::QueryPerformanceFrequency( &freq ) )
          return 0.0L;
      return double(1000000000.0L / freq.QuadPart);
  }

}

  steady_clock::time_point steady_clock::now() BOOST_NOEXCEPT
  {
    double nanosecs_per_tic = chrono_detail::get_nanosecs_per_tic();

    boost::winapi::LARGE_INTEGER_ pcount;
    if ( nanosecs_per_tic <= 0.0L )
    {
      BOOST_ASSERT(0 && "Boost::Chrono - get_nanosecs_per_tic Internal Error");
      return steady_clock::time_point();
    }
    unsigned times=0;
    while ( ! boost::winapi::QueryPerformanceCounter( &pcount ) )
    {
      if ( ++times > 3 )
      {
        BOOST_ASSERT(0 && "Boost::Chrono - QueryPerformanceCounter Internal Error");
        return steady_clock::time_point();
      }
    }

    return steady_clock::time_point(steady_clock::duration(
      static_cast<steady_clock::rep>((nanosecs_per_tic) * pcount.QuadPart)));
  }


#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
  steady_clock::time_point steady_clock::now( system::error_code & ec )
  {
    double nanosecs_per_tic = chrono_detail::get_nanosecs_per_tic();

    boost::winapi::LARGE_INTEGER_ pcount;
    if ( (nanosecs_per_tic <= 0.0L)
            || (!boost::winapi::QueryPerformanceCounter( &pcount )) )
    {
        boost::winapi::DWORD_ cause =
            ((nanosecs_per_tic <= 0.0L)
                    ? boost::winapi::ERROR_NOT_SUPPORTED_
                    : boost::winapi::GetLastError());
        if (::boost::chrono::is_throws(ec)) {
            boost::throw_exception(
                    system::system_error(
                            cause,
                            ::boost::system::system_category(),
                            "chrono::steady_clock" ));
        }
        else
        {
            ec.assign( cause, ::boost::system::system_category() );
            return steady_clock::time_point(duration(0));
        }
    }

    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return time_point(duration(
      static_cast<steady_clock::rep>(nanosecs_per_tic * pcount.QuadPart)));
  }
#endif

  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::now() BOOST_NOEXCEPT
  {
    boost::winapi::FILETIME_ ft;
    boost::winapi::GetSystemTimeAsFileTime( &ft );  // never fails
    return system_clock::time_point(
      system_clock::duration(
        ((static_cast<__int64>( ft.dwHighDateTime ) << 32) | ft.dwLowDateTime)
       - 116444736000000000LL
       //- (134775LL*864000000000LL)
      )
    );
  }

#if !defined BOOST_CHRONO_DONT_PROVIDE_HYBRID_ERROR_HANDLING
  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::now( system::error_code & ec )
  {
    boost::winapi::FILETIME_ ft;
    boost::winapi::GetSystemTimeAsFileTime( &ft );  // never fails
    if (!::boost::chrono::is_throws(ec))
    {
        ec.clear();
    }
    return system_clock::time_point(
      system_clock::duration(
       ((static_cast<__int64>( ft.dwHighDateTime ) << 32) | ft.dwLowDateTime)
       - 116444736000000000LL
       //- (134775LL*864000000000LL)
       ));
  }
#endif

  BOOST_CHRONO_INLINE
  std::time_t system_clock::to_time_t(const system_clock::time_point& t) BOOST_NOEXCEPT
  {
      __int64 temp = t.time_since_epoch().count();
      temp /= 10000000;
      return static_cast<std::time_t>( temp );
  }

  BOOST_CHRONO_INLINE
  system_clock::time_point system_clock::from_time_t(std::time_t t) BOOST_NOEXCEPT
  {
      __int64 temp = t;
      temp *= 10000000;
      return time_point(duration(temp));
  }

}  // namespace chrono
}  // namespace boost

#endif

/* chrono.hpp
KB+qF/C4eDngn97aR+x8dgQydKlnBIMvopxvAq/2pjv3t68XeD+pLpGH48c/USeSoFisNE4fE52W4DRN8Kr+43XbDnRWF1nO9FfXtd8KFPfmUOfmbucPGpOHTrqFGEsqxpMygAe5UbIV9yHAAFN0XjpI9FYBksVFu8qKJ10QIpPhZiX5CxDaOfa6uCqkHNZe2Ve18pdVU+ToDQXtShXmKtPDuaS0eI6UUG6e79rXC1uovBEWWycrQjYwWm/nAr4rYnaCMIosqVdkAp7G2c9QAPjt43+A7VlhJDDeXIn6kiJ0La64rtf+RLWhV6G8d6drTiKzpzvCcn3D6DYYpqmm50aPkZs9bYJjW0u7DEBpnBF7XXawCrRSM+iimZHL8Y5mmnmUo3yMsYu7q3E1gLHWq+eucnQBAYAY4IOxK9+AyDztpj2KKW77kUPnYF/3PTeOEBSnrjXaPB9PsboGefR7x7UsikDLuoE6FsMs+OpCWNDtryBXVlb2bLOaEy5+U5eCDvz0zfuWkoNACoQTGsGHK6LQkoEP9+rX60GgRAuEjREiKFwi2dGjUFPW+PlRjAoZ7+XrQUDFhBCi6mEwtAZgCwo8k4HK2gPgc2ABFJKDAFAk+4LIivwiAeD3yAu0BgUwcntf6VMkticp/el8/LHlKjnXsjPhoP7CS3Uu4uyHu90KubOUAfy7MEBUlzh5U/gotn0AEv0nj2FxdYTKJzMzRqdg6YDxo2Pls5FCujw7P3mI+9oudKeyzNVQDjyMLMnbm3BeGTCG4ChCByW0+XC2i4Td4JTjb81ehYAqGtss+wC4pBfPlJaf+RcLc+xlHVTw1zD4mV6z/ZYqHny1FzFRNz1pQtVR8mVFlJloESuSG0SGZQ3+0B9MK0wNFk7jf7GFXEKcGtYI0Q+yWgnOl7oSuC1IMlZL8Tw5NaXJMrjMB5QOO6WsBMFJQ4eTn2LVoH90O+ofnuckhcp4cJ+blSGFchywpNdk3AU5tdbTqT4HOiTGuVuwmdd74UCZw+U8sQi6oFgPDNq3VNcYeLhLB+VckqdmHY0yFlS3rG9kdio1DaZq6VDBm1eMqJ6W8cVst8mC3xV4LheDpJ4HO3URYjcJLqOQNl27fcC0U7/PXyc3ikrXeFrlTNWJ3EITjesYn4p0PFSYqm9tgv1FyYcdDOs0IVeneqf6nFTK/lWKPrBqf3Vl8KOJV1gGj6njX8n5SMZYnpxTdHh+yKri5F1fw9q1TsZP/sx9q+nEZx0CoXNYgpAcdC0+eEEWwHASDMUuXK+dDmVDEJxcZcQUPZq4wmrhVaKSOrNG21yuGmSoHuq4Fn3rfNkqOWta6L56t+A9OcKSNft1Gj/keGRg1L8ZyliZgkFFFeAQ0dHIbexqr67DVB0qQVRXgUW5tzVvbehxKtbqF3x188v0eWXkTGyQOngsZR7pGqMUEOoKO2lErQyTq5fSDJ6M8WWocmYj52khcl0BahzsMm+YnezMcSmc0eI6V8bCpno0a7otd/b7Pc8LeT+gbjvEKH485aw8Zc/cOvowZC19JFlwyVIGRe57YXxmWbfWdVbj2l4+GcHQ8bLgOgW11OvzGDZxniX8u9umCaWeII2NpI5FGte59+1FEmzaYfQxV3NP33UqlhsJNWw+JN8bVEsb0rQMGye6njSvnCQqlIrjejDsswOeHd4CZFHgMvSt6f36I+/1BznhaD7yTUE+bFT/Yr6Wgm+8NJjxvwfl/52dX7bn7VDERARfw7VAoTDQxKAJeF8rTxVwC7UITxDYwGIoxfYYYV8P7Jd+MxK512HfhkoVnd4Dxdrb+XIv6WNKrWVsVn4IhsgRV6BLdCaXV3ebt/UPDx1m7LwG79dNhjud2r5k3QK6Igonq3S8Mft3S+10b9YOmeWLUPXMQ6XNlUHLT0EGSquA/Kip9PrTtbsrnytExfNLqsgoQbqSSeDiAsn3cV1QPN5c+3WCyxbI6+LNZUwunmOUDHLdyv60ae3Ql5aqw5LHo1PCaSl+GBNL65xi2qYBAGEkhatuWWuD7cjCqPOMTj7pxRAZZ/Oo4ABmnckKVOfwjJMWujsxcvZrCR7FBB43OMjcbCfSld8ijgsmpEtLHWBtYy7V8gzcHT/3aLgqwWuWmDZV1sU+qISbHzCa4doafb7HCvZtDMdph8rg1RftC0Q+twfe8CPVq2AG+B7syvBpXlgNsyLb7Qv50M9cMrrzqxoR5WbJPXiFGhjekYP77ns7/fUdWT05fvz4g1GXMyUrAzfvI+3VEQTyBhj0SMEgA/rk7o3UWMEpwf57YuppGBJo0byTo+N9cmJhneQScP79owOHQ3p25BiQImPjA0Z75Icz+apkAHFZwACFEGAAFDNf/1TX8R49bjf/fUABzB8A8odk+krXyBmsLP2k6RCU9tS89fCC8RIUPB8GCN338aHqTqDoUPk3qCJjHo9dmrFCTk6LTUcBOmCRCuUpr/JeLUdnUz5lcHnS3Dxzyi4GW3rdoj+0PkTwNJWf1xe/XU1AQbsmJgcw67Q8qi27OGdxPXktjsxWi2yv+Ilnds68gMlEfqYmkWVrMbJfNZlck2b4d3SjNW1mPB/o1xSn/E0u4BikDZqTlTaaouzexYS59ZXUzF/GtVXu9E9ZzJcZWwit0MzCifZzM9iWe0GxUDGbMngCy5XsJsBcgFYsz5NrumAD43EakAilzpCbjDWSqc+2eEldJWpQ4yJ7TLMp7Heg+fbm7fFDdB7T00wqdTV/WqP9mgEk+HcIA7xSjhV9NMz1L0lnvjvd5ijA02zTUfVwLHQC8DsjSkBSkki1Zfxjnjl4WtcQUhVFfngEs6tD0d+2PFGFtaOsklvB/97pj+0OgRXXddLbpa28UvZTBWOT3ZUPRylT2gXtLOPY9H3VYQ/NM0n1R7xlWyKlqjlVn2R0QSLgWMv+RLauLI34NnJqH85XbeoO/VckiuU0J3LGXdtmpaCzSbRMNZZhXraXsUkrbHLIy9LQY97xxaeQwP1QtFT1nYajE6f/UPBn+iQnzmeLjLwONvIeTLdudUIuYze4+WfcyLW/RN0q9GvVoe/CKdjsywVBFxYr7/NJJAJMzXn4nvkz+7ClyL2GN8tYjgmejtwYU58+phueSvPs527zxepn4hhc2y0H80+RT8S7IbUA4J9LpkRGLVuNKvKgJz5FVaRzio1h7J5GVsxawoS/DhqjOM/tpCcdaeMddKHaC/TUfZy0DNuqBIemtLrK0pMfo8oCsgnEXtv6yg6sq2v45mr7iTMhppyVcQXLy0uyYv74wQ6F8lIxsZnUmH+KLyRdNyJgrI8Q5nuFtDa3WdwlOLW8a6dn4GXU6QdS4KxGrbMmPBB33B07/apK/T3ym01vAxvXB7q98jORtpJOi4XZSNop5qTDbSScFP/T+voqACB4/jmVv7XdfNyNu2yhBSLmx1+7WagI9VY8E8Bm55SHUFLRXsC+0DJ4Bmfd0vj+tAl4+LiwYJSTSLQ6PtXAzo3SWLy4ywupecd8IuHtMKbUOebSRPNta8ihcilChD9VxWnlHDn0YORiaCnD4x4pggsW5HjBtfr7yupJxcNkuVtQZCJZSPknvzvEN8RiuMVk/wGSmIhKRFuGiqRhyD2hheoChG+EFgKlMtuVoIcx8UWf30hs47ZgDmZpQWfrWGthf7O8OQMXgbPpNE/levOTaTyW22Qy9QZnCRfjkWetOCqUWHH+6Aj12iFYdKcBia/PFJfzjtqTjeNUcHalkaXFUTJgQ/8qpeh9N5BiCEfqLOGxLykGwKGEoxJwFbKJhYysXNBxuEJ0tfUFsIfP11v+nwEs130/sU/vbJDywpZMBznjY3RvavVmfHLboMYR0A1xC9KWlGp2X6hGemQsoqgmJqhl4hLKXYbNFrVRYiy/bUf9PO/tynrQq6EuCI33/KW2OOstZ1ZixVYLB6yRMvqUuKPvJ3tfePPslJTE1xcu4Evjxe57ZF4GZfBPzZ8TWzpewuFv5qjg/G+OKJGxAXozGBRCeCE9vXoDu8M+7O+SLs/YkPKdHwDeQHH5BM3xKhSogU06DAOMVEiCl8G4+I5ZpUIlFHFcQcqETVtMZtIxGofwzQSucAQTrXGSMuychZuXrJPKnfMV9QsO02y+Z7ydm3XL452ule2Ppu2Pr77Extl1eu6EMGGLiht5Ifw4epxWNMQQ4QFmtoDiP1qRI4ZzdjRIaKLE3yIY0Nq6Qvi3pN4IaZ6XovoCD7H9ATYIanG+3s4BvYJ5fCNqzEi9q7o0etp8LD5lfk/nO9BqltVnZ7YotbT+nVKezUm9Z5NXjCs3oprn7qpP7CHNxSzEok0rdKjFHw6VEVVNakgn+95H0nyO7nj7o+p3prbE+lOYCpWrIzdCEntp35g9yHvcuaS54thBExZiakeXFjpXCsxMP3bnDuIY5JItY61pFdQTp56H+EohSHkxRuUeF9vBRrDv2Z5670/23gdKXl/RE+LpwKYZl1lnX6IFSESL1BFloUSBnXH9zNm02yF9k/aKwyBD09TjEaoz4XHlYbz0Cair+c/U+dvJJGdSuXdKqVmutc0a/co3fGRItp3Gy8e943tT02xu7YYWW7KNYQPOEGxv2a6p54ralZtU2zmSf9pRaLM2cXmf81jWTSZYTBeOcEJBoV7uLFwgYFPAddKdpohNcf+c9oMkJrl7wfNlVFFuIqh/RhbWP8YLbITSypefhIRQ8tClTFqgvHql8zVENKvxNs2zGTeQu38t4sCXAJZL8IJ4cCk5lHiCDtnp2i/MlyO9TqJVTQlt7LwkN41ht5tXJcfKYT1GheGNdxoiB7/MBg3jwAuUbKR5P1S1Seaf27hL2fzZc5qxIq01rqB5HuHfNmbBZCDmOizouCY00Xq5hl2lwG95LcQknc+7fp36UURhH6dsbDcH3doa78Ho9dzs8MDyeEZkYneHLV9pJ0X6iwabfxK5wRUaAf5klGuiFQXtVAztFXm+n9BmgTGI4PiN0Qvcoe4XSyM1IHYQAvJ4hT1IT0rakGItvf7RninFArpFsHxfdgaRudMCXJAXdnBfcHahaeExl74WCsgF/FLlvyBssOYXA8QJdUr+r+C/g++8PMZzz8eBD9zoe/a3b4mEvxt73w+3soScGx22/t9wBnvuorfEMgUPh3+HdtX6fW884djoh8IpGBW6Gv+sXo6GhDe6r9fM6/hs5Qy/vtnU1WV7mD/wIzjRE8atq0VRDpccKT8P8IZEmAtCaluhVXu+ZyT+6aNtBml7WaXTp5yEyryl6BejF5X08Exwl61b4ue82XFMe/VeisGesK8189waT0/2UY8XyTK+4Y2PTM5AOPeXq1wzaT1AMuL2a7DZIGWiO8Jqk6FiOwTJvEq0H260/rnYEIwpvP64Qv7b3ExG7eW5sYFRljT+hTUIHTrE7mCeB7lL1TQWkFnuAKZYih/q3rZu0c79UOhcW5rx/SkTtkc56f9oxLwX3ul6gwrn1PUaadEAPZXPhbs3LAuPv2jLAN9Z2dZMl87ydSgcl5UqvsnCqx29bZMbQvcXuAzKa5+NDi2zHfM8ODj4z1/KJ9DPA9zlhb7pyYjPg9sEASCdUsUIYMKb2+3L0bcpwTXVfFiWE6Ph4b/fs9L4Fu/o56SXfGojEUJVPfQFTXXkSWhQsoJ7cW7WxPKKf2JIDMTdqHW8Y7FSwv6emhnIQRBjB873x90SM6sggxP1I6xrZNgRvtOVG1YB+LctxxJ449OzXYXarH/NTiXi1wKAgqAlqetq89UYDu0DbH0e1XzK9yCwoP502DyXnpoF27K9eXcq1ZaY5+itD7tR+A+zW9TluCbPdFiYrJ/AHdi+3uybc50l586A9LUlNBRE/sU/Fzb1WdloeRpL0vPGQXspd+Ki8N5QLrdAiDbqFmrboFBMcy3qoIWGzrwqPt3gWDyrEHOEeBLcYYWuxdV6JR+6t+CW0OB/T5ZG767mUog1dejJqlelRzKCw4c1C6qDEploHT4Y3pHBqkbZpkLfnjI4mBQDhVWqPUkNhuEqJwbjwTNxDf/Ypn2M4uXoDHB/0u4uhOahX95z/nFvQrRwCQxAFGx+eht5DsbMHFavtonMx+q4ddi6+9Nh04XxNDZD5g7bqC6bAt8MZ/QHfsVl2gfClLgZ6yhU4VF0MTaYwHzx3CmH4WeNIHToD+iXubrONbe6nY4ZUPMfab7AjoUMc4ceJQbvf9g39UlL7Dx87x4+7w+irMJj3/mLmvsLpYh1cMMwgCwSVB4s0hNxDdeTTpMxHtUJ3KliRYyiZONCETAh1uWkUqdV4JmguFFrY667b5cSh8qkn0z0MqHWb2PTaa6vnw4NTeFxkCj1uVnJE8YK4roeB4kC9H7BueTlEhD1vO8kvDkWCx70vNOEXF8NsybeLCRncTw5ezVQ1Fds4WhQyi81bnz3zdeVLdmZ6Bw/MPU+PZUaOsjmml2jG0I5idNjf5NQcCz6qdrTSdZykFtI0Kl1vKjd7tXCO5E0G+j5DcG70Aa6aDQ06LIw9ykDFJEOws2U04wsiTo+dB/ioEYGBCQsjyBSZh9FojMSYTsmsB/cgHJLCSZS8m6aXjF52ATnxjRHZjI8GlcIMdglbMsq+mgXOom6qeg1HLOWFxGk77XeEz5YcYY4IXVlawoOufOQRPjM77iacVeuapJMyhhbxxbW5fW1AyZuOUl8E5oEn2Z53pfLHGLZcuL8RDtyasrTZ4rCWBQg48u2pYtj9uLH4xNnOUX7n9ClElmpCK/sCOtqxKh9OpodPbAa5JeDQURavejFvUnONPt1c0wChdbphMjWEmeFFX3TL6BKqmeoXvhMxwCxoM2o/9X5DQP9V/gWN5T/EYk1/FFVQQXS6fn+GS0XZHX8dlRRXqcGi+G3ieqg3LR0ODtRV46+nPjW2mFqboT0EW+82ln7whqhlqcdZT+60rf1fT35sxFAd4Rl7OqmmwMSf8OhEadf5KBMOCidIsGj/2NUKuTeu+F8AvNsb/H0l9c5ZMVVKiHWb81vbQP8WEZ63lGZDj4JrUN4jSZVl9Ny0lH+ecm7Pz2PZJSrKVD3Rn+athv2cg2TMfVN/k2+OnZPLIJGl6p639yH5dmjNLR8fTSVgnQlrpM++4mi+6HyVnVrOmGxPADxySmE+HA/RiRqrwqZZcLAO2lJjPVSc0uBGs4A8ijYHkn1UAcXE433Wa3OYuP5ZQw8vO+423oIP+nv5JvUyYIMqos2Dx6c+51m23Q55aGEVxZF2cr+Y5uWoVf1yrTF8/MZEqpPHUL8ln/NtDHftCx2QyncpoD38prp3H7mhRyuitfmlGIfqK0Mn47llYXXWDdrmJVdzslHN8WfBv0JdwpF3R1Frme042Ey6yDFPMp11QvctdfQp05zxgi0De3z9bqbF12ezeHDR0Ki2CLpa/LJaOkEMIWyH5sWkU/wLbSQ2bl+AgYxjAQxQQIWRDdisJjB895bTuJGOCBgxZ2CkH6kcE4NcoyQ0uAhS2R5cpxCUsTgYGSWcGLsiKCfSIUyHXx6YSiQbScckG3qjwJCvY3YCL8ndFiBpacmMCDoOd8ciSFDgJavJQaNn56NYWSDmD028D8zU41TtpR7+7NZHPLI7ryrYpu+rN8qz1s+xv7gE2IdKVItqamXgeyihd3UdKDtH5TUFL50C6toJ9mxW5rWHQaIkweq4nETsUytyBsfW328jNlrI9KdyYX5G85hO57pVeAuP0q9Z9voexptVQwHan8VNKIP+lpL09TVLZd1+g+fE77WbMl3MmKnlMRaTRyiSJdCh72un8epSSWRYMywqFAPMZHX+JfqFpkorjH+shWbJqcgEmJ+He8JupRrWxUngWagEeC1n+UcnsUwg5mT13ZLB4VfUiDd2nW4LqhIx5YMSNqge7y9rZzKREoegEyxupYrezwKC1FvKv6TCjgA9g0Or47kKAD4s1S2e8AuCGFHLPVRNMT3MxVY5KBEnd1lp75dYi4RfsXuW/CP98ovoQN/NIiNi8Ac62zhMpCc/lkHU9WC+8pieUihrWkyp/am5lK3WgpXE6vKiCwSTmZGpJlJzYXhofWvhfp8YcX+LUbXOXOXyJv6sFHNAqUQFZUdE/oBtYAP5c3bchKoyrtk4Bu8BFTE0F9am9N2tdKRguOvGUbcR5rFW7RWsNnmgNTXqhz51baCb38CuA8DDeEcNjZMdduXed92txV7O/oTsWpjqKFwTP2jV64tg9/BmmInYuQjQZO2tbQG+/WJYjCD/fzn8PU9+Q3/tOOKYGxiU09KS1/rTFAnWt4nJlcwSTLCS9lBJdypQzTZYwf1rOE8GC4+Z+RFF3X/yodwQRxW5uqLpvOztTtpcwvq6YB41RjSpH3AVExueMWRIoIxZsA7JqRLth4404wAeAgTHChLpH2dONQkaFvL8k9+7dILGwbn3+dV78v5PzOo3hrqAj6t+OVuzA6XxbCbDhjNC+I9BxgGCSLp+UYFY5Rjm0O7nEoBNmUbyWLUmTM1i/h/4VUyRyz2LoZw9pTDUhmmMkdXq+gxZCcvePXRWllMm6x6rl+w6u0KzTLUqxzTaxoUPblMFrPPmSmezzURL9jS78rM3AraRv79m/geqxXEadPsogGly5l2hjGmIzEZsSb6aMJgIPTCJmlh20S1xlBWNlDJQcFucHFRjS6vYLcDNGW54Jf09jbdOF+tZdS64G2lyK+Xd0mVqL6qUjUVwTNYyWV3P87U0a6tvIoNS3EbHz9Iguzqy5rtrpirphbRVkEXT1PWeQ9pvlQ/GJhgAWaFWaXXG/CD/f/DTznsD6yPxMTh2/9+955tKqdovhOKXI40VERFLmYLdGZcJi522gUBAQVECVJYoIBaGOiEooQggHAGEYZPjiMg54GMiFokAV7WDbJ2ou2a4/wSeDM9zcXB9DKmPZ3e9rB3aFT9NvX04zsdgrjrOyPbl2crrt2Ll9DeYeb20bfjc/JjK4fOX90/1P9nYHIczP88O+TsEz26b37y0I5roQU4slAdHdEjxUB6YYRRWUWFMBlbVzf3qCmNjCLv+QzXwxP7pbpiXIhOytVZ66Gj7IBY8VqVSFofELjrccjMtBvxJeHcfHigz7j9RalhJWaSdxXqHskzgxPGAE6KF4RR+y4z47hScgpm8Gm8uyqOFC1iNUo4ubOTfG05Z0ow0E/e0XWLubExlgI=
*/