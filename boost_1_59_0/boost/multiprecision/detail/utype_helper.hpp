///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_UTYPE_HELPER_HPP
#define BOOST_MP_UTYPE_HELPER_HPP

#include <limits>
#include <cstdint>

namespace boost {
namespace multiprecision {
namespace detail {
template <const unsigned>
struct utype_helper
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<0U>
{
   using exact = boost::uint8_t;
};
template <>
struct utype_helper<1U>
{
   using exact = boost::uint8_t;
};
template <>
struct utype_helper<2U>
{
   using exact = boost::uint8_t;
};
template <>
struct utype_helper<3U>
{
   using exact = boost::uint8_t;
};
template <>
struct utype_helper<4U>
{
   using exact = boost::uint8_t;
};
template <>
struct utype_helper<5U>
{
   using exact = boost::uint8_t;
};
template <>
struct utype_helper<6U>
{
   using exact = boost::uint8_t;
};
template <>
struct utype_helper<7U>
{
   using exact = boost::uint8_t;
};
template <>
struct utype_helper<8U>
{
   using exact = boost::uint8_t;
};

template <>
struct utype_helper<9U>
{
   using exact = std::uint16_t;
};
template <>
struct utype_helper<10U>
{
   using exact = std::uint16_t;
};
template <>
struct utype_helper<11U>
{
   using exact = std::uint16_t;
};
template <>
struct utype_helper<12U>
{
   using exact = std::uint16_t;
};
template <>
struct utype_helper<13U>
{
   using exact = std::uint16_t;
};
template <>
struct utype_helper<14U>
{
   using exact = std::uint16_t;
};
template <>
struct utype_helper<15U>
{
   using exact = std::uint16_t;
};
template <>
struct utype_helper<16U>
{
   using exact = std::uint16_t;
};

template <>
struct utype_helper<17U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<18U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<19U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<20U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<21U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<22U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<23U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<24U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<25U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<26U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<27U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<28U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<29U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<30U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<31U>
{
   using exact = std::uint32_t;
};
template <>
struct utype_helper<32U>
{
   using exact = std::uint32_t;
};

template <>
struct utype_helper<33U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<34U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<35U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<36U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<37U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<38U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<39U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<40U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<41U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<42U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<43U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<44U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<45U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<46U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<47U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<48U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<49U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<50U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<51U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<52U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<53U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<54U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<55U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<56U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<57U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<58U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<59U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<60U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<61U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<62U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<63U>
{
   using exact = std::uint64_t;
};
template <>
struct utype_helper<64U>
{
   using exact = std::uint64_t;
};

template <class unsigned_type>
int utype_prior(unsigned_type ui)
{
   // TBD: Implement a templated binary search for this.
   int priority_bit;

   unsigned_type priority_mask = unsigned_type(unsigned_type(1U) << (std::numeric_limits<unsigned_type>::digits - 1));

   for (priority_bit = std::numeric_limits<unsigned_type>::digits - 1; priority_bit >= 0; --priority_bit)
   {
      if (unsigned_type(priority_mask & ui) != unsigned_type(0U))
      {
         break;
      }

      priority_mask >>= 1;
   }

   return priority_bit;
}

}}} // namespace boost::multiprecision::detail

#endif // BOOST_MP_UTYPE_HELPER_HPP

/* utype_helper.hpp
VJjoMRly0VsU4UyhSM70laP04n3dr0QFEmpjj4/jveRboRb5QrNVqyWKFwQptrXsE27AaOBPo4zcgHm9JqxU3asNYfbyBBuPCXgEo+k2zEZ+oeHM/S/gSWE6t8dAh9GC2Xi7+qQDzfKzl1fSvpJMdsuAL01Z3DbeXd/eWigcndn1T8D4aw1GAhuoljXVY7+F3jfIeychv5fd3kCbf4H8XgoARgCE4iQISIgdL4/ixuoRLpaVzkWufazq+Ygz5SB/jiw/K/5sviBagRKDPyYX589RoT95R/hvR/VIW8tLQvqp+zVHW+Yab0MUutTmcaQVwUNi6M1kO85d8r1dAc9NwJ9Jy3B52qAkBdxJAXbivzmbMPCbxKZjjzsUwaJldNxZj05cEmt2PRbGmixiDYCPXQFNiElMQAPZ+/PsxDlNKByQmTG6IA4zdm6JPuAP8uPZ5Y8ZyP+TbzD/z1hd56z0aGGwEB5Jd9ezpy5WFDK5AODSGwI1bMHjdjz3JWmKGqvskDt8oRn/M7HSJ4T4uOvSKPHx55sjxAdWjj04Paib4pqRM/lxPRJ6hk/mSIPnn2N6ik/LaBkfUw2rfSwhPnmPC3xuHheFz4a5BvH5YKQxfM5yPB8doTchb6QeHTaaXZdwyN4Qc/LLsUfzo8HRTLbEt7hsXC534chtVoTfEYxYNyvfojtaix5xcHvhFgDSk+r9hbOwu9PSB75AKVhFw5SPYtb3Yf1xGzZm82+KM2Zvd8YZsxmbwsfsueI9f7hBvHeN5ni3Cby3x8b7yXC8T4+V8W4Nw/vtzbp4t20EvM1heP9PCG+OtCQr73vIAOZ/+nkczJNHxMH8gT+EMD9XvH/MM4h3beHZ4r1qTGy8f75JF+96AJDW5yG8z8TB+4IHDeBd9rM4eN87LA7eo54Jw9tgvPsnhsZS94r0O20scCGtWm3Qzr7iEB89aTR9rjJMP4ZNtP6ZrZbaMz+G/tkR2SBg9JwfJe3zbbw500vOeMrUxX7O2Qa772qP6xQJ+wG+mSvd8JVtRX1541oy9xrxHarRAVgLLdXgL3OtHIlnYl7ifEaG2u8ekqD9z4/iAYCh/VN0299fa/8pdOC93gQkeI+b4zf/zqFxleo9aP+68xO0319gtP1FUvst8dv/ypBE7efyo2G5kf3pX3Pj6c/tQWkxsoBLi0zh75dikneosNUOSQuKbTTd4mWZ5NniyfAyc2Omut2ZRKcd25+HX6mjeQPWhRW2rWtePYbxk3x/hg+yI7Rtve8d+unet47hfn+u94zJdu8OtatzkGsP/7LTd3tSZ7rrEP/2hu+OFDbiXgdvcj17y6nw00cMGpLN9jxgxxhy2dEHkXQMyW65n4fFd+1gWy6KWrh8MMdOjlXawoUfOUp+tNo2cfj5uttE35XKR59VKJ99hvGMTPwf/HYCvndDST9GEVlMJpPZbD6L84/BsfULoewhN+dz7m0Ssv5Jrl/I4dyDHlnlIZtF7JO30cnu7y7EGM+eocXXZnsGqX7iF6sebidPerNtw060aOqciiHeWSZd9c1I4qzOUlffz1m9GiPweE9bF+batq7LOU4stcOHtufp5LbrjVZSHKHtJtltwl/22jAXtvbBMVzY1MDuzyuUjs8raOKgf/vOxZ9p+3nG1tMDRtLIvgYEvZt8kgGHNg9A8ZLc5VeLLr8au7x6GpEYAkjYvyAkLF9QnP90Huc/mYJvsDnrpUPUA4P0lsJqoAMwPATlveNIt5n/O7v85zkG8587id5rgd46oreK6P0yc5ug90ukt1XQ20r0dnm7rAuH2bautTCitwvofZ2r6l7nqrrXcYJnDeskkj88T49kGC/b4ek3oez7IpzmntH70UBj9BaNOAd6T3J6GXy8nsLpTeX0Uh7xO9ZK9H6dE4PeLfD0i1BeZVH0Gj2fPjEg4fl01XCicynQeSeen4M8mGNFj6USEgo4/XDdII1z3q/7qa1ifLfi+IbHx8qXs8Ive7tMHoev3sNcQDbafEl5zLOqYZajOERibvt4YG/mAz3RPzH9w7hgXMb9ppuMYhBFZFI4CM7I6xYOwsVrHHRGGg+E9wf0Sr5IoD87Mf15vUR/SoJOkCroX430W+PT3z8x/UbW6//ISkj+1UOp+/cH0h3qND8GG1JLNSWz1p6r+uukpYqeX4zZY83JMmav8OIQzph9QmGzW9P1liPIvgUeIxPNV1+TIPrkazHR8PNukknspOrgmuF69sBgsVyiuCo57IG1tF7KibVeKl5Dap69bNnwqNXSc3UxVkvZEaulk1m6q6W146GxJVDKvg5fF50l3l87jOE97XyO936Bd3tP8QbBv+7GbwnvOvjQkveIiQ7lP1t+dxDy/EEa5EkEef6a+JC3+QTkGcOiIJ9YaxDy5f10IVcDv/+mQtkC5cVvojHvId6L7cbw/tvgGHjPWASzLOBtZKI94Ce8d8MHz5KUTisKbaJ1rArivTVHw9tMeG/1xce7/h6B98NDo/D+i9sg3g5HDLwHQoOHQBnp18XbqHx32BIKuP8Y9K+f35O4aK9d6aB5IJ5oD9h6c353ZCam/7xemt9Mxub3qrscNNnFA+GHzF6a3x0ZienP6SX6zQk6QbKgvzXx/P5DRm/lmz7BMtMNnn8MlPKF4no+3KTZ4+aH6GzLYDHcS2m4Y5CmmnTJE4rvTkNDH6q+rtKO2gP0PayDOkqt7hpxesxX+H0zEp1nGFzPDO+bkN1LB0jp42f6VbcHN9fA6snenUQqsrrjfwFexq+fejkAgENLrF0NfFNVln9p0/IoKQmYSGehUpyglXYRt4y2FjWKgSJU0qZtUNoUGWY2U79nE60ulI+0pc9LirosoqB8jF/8xv3JzKIWZKAKEkYQuzI7I4u7685W91Y7bFGEUkrfnnPuy1eTtsHVn0De173nnHvuueeee+//RLbEPmwYMSAZiUdsTQBxTs2RFSZxZUYYNhkkAs1hwubI0ZCTnzYgav0nYI5f0+DdiYivxpCAshIcrr3c+tXRw9Yvh+q/Nrr+upHqx/ZZHXO+Kv5ASdPokeHV/8sclbQY2mWQDk4O2GVQwbwfUeRlnL8eFHAMKzWUsR6ebjKF/dG9GfGw8PL3zE/HP5KTzH8uaH8QaP+Fhmd2XwyemXMQnhlu13dpl2smhS/EVoX5IZ6zxV4EfmMWMT2WmJZdwLHZaIqMpMHRI+/nT2K99AL/j1HJ4c/deEWU3TwHdjOyVrowRPvfIqq2OUU7Kak5Ark6siQf82UTNEtyA1mSPDw1SWCBUxDoTFtCLY9bQv1oDB2cSLgy+p48UrLqy4//pCcZ/xlPzT8XDMvsRPZzumY/H7rSiGsyPWyNSduhBBIYRxIYg9sX0h08z2CKsHR61A+bf3sgLcnzD+NitrfH8TONgqDbLKSV2aSVEwQ02ow6Vej0Bm1/X5iXqxPycpn5r5Okf6MpGfo/NyeiXzcE/UvT///0N+iTzH9uJPptQP+sRPRfq+nTVWatF11JOmTipekmPEHTbnPw36ZFKdIraUOfN7mc+G9qkvFfQf+tQP/NieifSvJfcsUg6ldGqO+Mpv5/9EN2g8vU/5Qk9X9sMvRvGz+I/gMR+q3pUfRfmwT9SeL/pSSF/5dJ5C8svuidP2ifZIFKDFxFDPznODGW4iqGgfUE/l7HDXpw1z7F4RfGK71TG6FSXDE7/lypQ+ZIv9z9n7qk9n8akuPHGM9PfjL8rE35ofh5UUqGn/NjkuPnNlMcP9XJ8POObmR+vl4VtX9inxSNb42YijE7KI5E76DYq/bF9SGRfy2uGxnHaBhVWhRjh1hXM8SdmFRCJyZLjVqXepK6lNezRexzzMHNE9c8VSqxdP8hAx27x8W7nysV1pnMYRYbMHO2aOmQZJG54269dlYZAyJXGd9uadTNw5XUeviHNvCLgF9bOmVh1SOwBeINaNyQJB+UaJ/EkZh9EnADRVRwjKvNYqcEU3OhzHwsF/4kXK/83vK+ayBpeW8dLeT9T5q8XxlK3utC8v73TE3eK0jej8fI++2WkLxTL1/eU0DevSkk7274R2xJD29CHzW0yPuQ36FFvq5JiDwwT9oE5W6FP6+mzEsYCz32g8j/w/6k5T9Zvlz51xiGkf+Na0PyT/l+8q/Xk/wfgH/EWQBDmwgAtslDy//JS8PK39AYln8WlDsZ/lyjT0L+yeG/XOxLDv8lnQzoLBifCwcJWDOgE0i8AxlkQDOK6s3etAMCaIO2HbmiHDsFG3goAJvLtf99fcnY/zSxPA72vyyx/bcK+y/In4D2fzzY/1od79aZpEC9isjDc0OjQGgemeKMGQV+c7FvqFHge5/X+N2FZPibIPhzAn8LE/N3NfFXO5r4syB/Js3/AP5oB8XBEca4E31JcHf55397k+HvJn1y/K2U4/jLl0yUkHdE/r69kBR//i59l3xAVUPXq7twSawrbWBA1a5xm33Xd5fC15gApeuL0DXIpwr4norgXXZZ582oimAGH3YPdf57ZQRfE/HnEsXjFF9PMP0z46tSGGuznQ5C7bpuh8SaMQEUgiA5VMuk+j0a+ia+QHgj/fDe69dFgXDy776zSQkXGQU9T/rC9JQlAvw0MLuctkEnUnvZe8SRLIeA+aRzWvYeMg6Hhw4cRfiHspTVuWBBUTqi/owvNofrjwfja5exuhlCqoo9hMaHuLgOflRD1grxOghKpe3l93dKUTP+tl0HY65Rv7vNYfjYfoRxPgPSm75DCuwnIIpTxRd9GG9OjTkfVMjuzsHIaJlS063U9Cg1Z5WaXtWSg8fU7D2sspeVdtfp8jrKWeXZvH8pdyCwh6UfszqU9te6Cz5azFMbRNZMQwI87L2R/YFlCaPzNTI7qlr0E8MtQP5BMPWNwjckZfZyYCTox8RmFbfulChPnYLLz0+kiwwL4MHtL4GbfGCiQWKZlNqusidAXyj6ZxCRKOjHIyGmvJ0EWBT044j7hz+/Trnig37c9+pZQs/SglLjBzslZ8BPmZqDqftAwOLrTR/gL/zyEP3Cr47BL/6OYwDha9ML2hU/DqVB/y74G4/AK/7d8KvFv08OY9YOCb0d3f98l9f/7vllWN/jZBtWJFm1yBNjcBmH3E9780jthd058BKKIphOAmpGWaPggs1hUaWSmJpDYgJC0NuokzwzvmqTPLl/RsBhJ9/SQAiLRWlesLI+M7/3mz41SBcUKWZn+1C2+gBlIHDwxULWqaJcrdFSgqlaY+pE/VpDgxFBugR1qDu8+1yfGoXlO0ggCfEIatSppok7Bq+37H0/Gr8ystk8JzGUpV12YD80TEQUVNU3akx7FwLfYK+DbwpOQcertuYiwi+OLvBnpuh8ns4Dr2uZIRG6Ex7YPJve2yk5AhXWSeX8ReWCimCdiBYptjC2IqqXhnYKL8essxKEYgR81IPE1+mqMMmLMA7Qq/kLFzOlOtUZWI++oWqpn7IDMa5/HH1d0F580LgO5V+8tj0NUx+jfNn6fXjswoynMaXUD9mzn77cJtmUcf7eH//y44Jz/JkzfYOT4YXwMIuPejM1+Fa2CyEWwniP/aANVc6CUzzViADtg6EfwU0DH7TliVDC3riMK2QPDWAEL3Dd7vOqg399ejamD30AwT57/Idk8LVLAvZ+GAi449vZUqC0F5xp3oQ/K8+Ww8+98JM1P425K0r7wRAqa/+A6PD2s8r6YwgW/9wRgozvgL8TLAg563TsJP/ytSxpMalV13x4MeY5phE5HH6u7ad+Y+uweK7c3hOW5WBArmtRkIWY4y60AtKGgh88lIXgwfgL8BSBHM8mXNBJkp63/nd4emZF05M7LD0ZI9GTYP5gciacQJxkdkPBubzD3uklvicCjFLJ3z9qrKT9fLpmrBTr6C8WAxj/8nSUqop5h+K15hYfj1dTMWeoxPbwLwMdqAq8S4ZKbAEuNQxRRRw/u6LxG4fg54x/hSwZG6/W4fnHv/Sp0aY0QFlb8CDq/CfIoP4KTShfAA2z/XX7u1LxYZ++qd0HDmmgdhSfCkJWfoL38XoCt8D135zip/8Sx3dovgUtORpTVpaoHU99Gua7BopvPGVsQmEUvoSjnLHJRHbN2/R7Y2MaUnryFoJC+aln+be/llgv3/kQXTv5qsS16URtU7C2O9WOxnbflbh+7PlVqiQdbsY6dCJLWZiKP0FzdT0vhR93BQaNM4FWIZwyPr0+drTp/jpmtMmGkjjvTkhXiqDrCqRrAQJJvEvbZv4NRBCmpBS/L/nqkgpzlhUZwTSUMBW8gcpcNbhMDKSwFSZWY4CSDVCyXWbjXU5HFPpnH0rJLsNNHLBseTuGVSjRX28bGNb/hYFoCZSjWpbjcNSGaXIkH/hSS0CodXC7rWFPyA+rWxbtqeIAK9zUDRnCTcVBVmlGp6eKHVEeKQSncFrYUVctb0BJQ3XlKHoX7Xoxovy2xB4HZtQ+5XQ6XTz3HoQcNmHg5BytGe928MbnL6lKTT97zAtvBEp3839ebAMyPtenviopNZ3k0oJjy5GDQOnnZfiK7V6bVPyt1+dfwXW+h9kcKyvthKFhn8is6maP5So1MrxQUVTDG+axyk6WghscHsHVaVrA9Pfql99EUI6f89mP9qphCOzdXP/CJTUwWxfv6pm0MUr7zACf+Y+riq8/aN+9jZGXlELTEUzwymy2oI06hBAlvIaFz62ySTEmMlx2xJ68eSgqviXH5CuU4vIVZkXy1a+QwbnzooswnHI0WnO0tIKgurje/SyqvE4DhdUeR1SgoL2rWafluecnn7uE2Oz4hg7aCxvVhdnZuATtgQgZ1GbVhAudr3lFVu2DlFB6vJl8zSIbITKhtfUvt1p1xiaFjtJYsX9E2vHxIvjc2KoILPAcZiq696x3KTZutdWMBYzHJ++LlsVdK1rTphmberXkRsVHjY3d6G0eeuDX6AJdv4NQVE9qj/n5wkxCmFr9HmXJ6uAbfztWcjq1NAUe7+bXJeG+ARf5mIyuLqVubJ3OM+UqCW/NQsb40vIsytSrSYaw708/1Ku2bKEbGAhA/dCep4UVhP0EJRxSkz9qr2OSPj65wiZFt8UfxRajdaK9YzDmJZG57tZHhCdlwraqdvAH3QOhtkpFOTbYUbhMh6GPJXzhzwcw7vFXmF6Qf3PTICE885uxUrjZKqzV5Xxy7YDa1UkgpyE3DefPz+DkuemT+klg5orf91pYmUFMqP3vGRxszXIgWu3Q/CpGD2L2m8AMBWMnc/SuArU46M2Epu+8XlisBvjfoDTIQbuMzmhgHjrizC0zWSntbzpVPw1DML/PhEmjvZ9V6RX9C5QWC0ydfMuyV9qk5R3hCVokH3py9eHnieu7J3F9WxLWxxTkF6br6SIfZpGhCTnxjraBW738jP+IGmtPhfRVSzsoB0qM3d5ZFVxNEWFslRAi8yQNkdmMiMyeezK14IMbdMJ9sKDdHe9v3X8gyp48EmNPPHH2ZFXEnmTj6MHO1GUhxpp6AqUEg1+BquyztmCqkiC4FUf4W4+ZwDUAXW3RdFUhWAVj4wmg0tNhgpvap2btJZ2ImODHn267qFLIJOrzuTLbuIHCTBuEW8TWNJIeYcd9EG3ROkrQXsafWjygal9SWF3cB8VdghaOF7sHKIY/BRMOamsB
*/