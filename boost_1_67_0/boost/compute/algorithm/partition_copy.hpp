//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies all of the elements in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p first_true
/// and all of the elements for which \p predicate returns \c false to
/// the range beginning at \p first_false.
///
/// Space complexity: \Omega(2n)
///
/// \see partition()
template<class InputIterator,
         class OutputIterator1,
         class OutputIterator2,
         class UnaryPredicate>
inline std::pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator first,
               InputIterator last,
               OutputIterator1 first_true,
               OutputIterator2 first_false,
               UnaryPredicate predicate,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator2>::value);

    // copy true values
    OutputIterator1 last_true =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_true,
                                  predicate,
                                  queue);

    // copy false values
    OutputIterator2 last_false =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_false,
                                  not1(predicate),
                                  queue);

    // return iterators to the end of the true and the false ranges
    return std::make_pair(last_true, last_false);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
lL+b28P5a1b5HMf5dXKIfunaqFOM3J435C4paKPtdWTjlXKo4CCk5va8LwVQgJMPQ4P8SXv0IzkMrWHJKlyqBjFe+ITbQ1MBMgbAPtuPKmPQgZf5z9qj/5C7MDIXJgGzv4aJid+B2vvERdA2ijEhBkj7qRhAmzaCeiqUtYSFQtbfhHSQDVKYsKK9iKf8cRpWtrtaYtNwIZuGUYFsFNiD0yi/6/ZvWcMgfY4zfIW/CsF5VzvlJUhqR4yfnujzGfHcTUwwa6cT/vdxi3P1yMHjIU+ewVHjL1wV+dbF+XLTsGdSfMOl5MeJzyNmHRN3tPXxHKTdZJgMRtyAfQYJrLlF3Y19O0jFTo+b1N1LNdIYh0BnrPQD9JuHXQCm776CSj/xDn/DEJWXI9cOjeZrt5APvsRiO87AkDGMGExo04ZxMConLdEnhxNvk4NRytlAhIlcoac+HFGMBJEIL/XEZfSREpGQEpeGFMt/36bvT2WNxaglUpEf+st30OZAXOoN5CN51C38FlHdwG9kSwEucI7td7vJt1OZ7hU1NwDinzDHX0S7xgPvUfkDRXc5iKI799uQPtSjl2iURKOUe/DOhrrbQlkjxhPfngN9dgeAAIBDSwEAgP9/DBzkFORJCnJjIssHE1nWpSanrVHYDaEeg2ckenL1FyhWJ3oDm8i4PWGRFO7QUrgxNI9EP7QwivFzRxFp95SRHT/SFxvdvB6i9lHvH/snM+pN1I6u90C3eEQzcHxkwSL9mhEUfl/DKPwtpLAzUd1dieqqljiFfxmn8PgEhYOUwsgjgK7KQhaEpZhij6/Yvk8RLElh9Pp26BkEMHjI+D5KF5ZgFHWSQ+gw862NAN9Al6cmj6LLDerFdPn08xF04U0DTyEyUS0F4foZOr8nxbNvaYcXIQvZkIgvW2gB4h2Tz2RklfRyAKkoLTUotob9l9NvBkmv6H3wiS50YnSxDqORLdSUhcidU3DRTC/IjqrH33KZcOKTMzABnYhYMspGUSk6vrPBRLDJPnHhjLhZKWry1idu0cEaJkAnEFjg+VAV8Z9QeUVIzlH0foKib9NryL7LE9fzlQqmAHegLkE6N/nTZ8gA34xPSMo1pOVynAgpW2CpeIrMpOTgrZP40jAuOwmfUamCbnZoVwlWlU5+ZKMG757T7RAtRqI8RNZg5KiKXSlTyqMBtSJKPwEPlBv2d9DBsVAOHkJWhcr414p0D0Ur2IgyM7mFcmOdmoROlQMUmvobpe0Zv8VybDBGt45RHnttnZpjE+d/1fQwGleYHDR81YBan0VUDUUtFNtzknoo1lIxlr/1GPXLEhbzKSDaJPhCVj3yZFQn8R7AuEp5YUDlM8VtBi2fXqkeqySb1JgqztRUi22WxtivH8mxbT1JIddSG3UpCCno3eqx4e+f4OZrfLNRnfs6AqvZJb/FjWI0TohqhSVQa3SbUt9rP1E8GU0pCDlkzNPAjKeQVTsTlsy1C6kdC8ESnEsLXDyFN8jtynf9OWQxdS0SdZwXOPLsjGF7DYrbn0qqNEyTv3iKUEBpUZmggzC+kjwTi6kABiz509VkYzKRVNOrpEkLFXMlacFPF+s1Hp+Beo2p5ApU809WzBtkNRMXUhOR09W47RP/GNK+CMLqdWr2MshzhHPNp3dpJtie/gs+9uLjVXiMcL2Zbrh6nM1b7DbwnPzF3f1WvWARW62OtrrTd3da9S7LGkdooxE/63BrUp2HOJhUHfbn1T6KZI3kI1mBqlJ9N2q+nE/bfhOfLYf9uuqCEH8Zc2HPQ1hYSv62g5mj7Q6oQhbduUOlDCziTnwoFerm1fIxUoMVC26wyCalXAbOz/HXisTETyvjx5Kr85N9N/h9GK77DmCZduJDGXcAK7oTH0rqAazqTny0O3vZoRMtuOTswctrPVp2V6jY2SOY/XrybWj3YmcvXnoIxqgJB7Rgcd7Cp0KNeKN43iBMkm9eJ7nekZavg3hhoXzzesnV1b58PfXTeB7d5qZHrxpnk1wn5fQhCOjpa7HrZP0E2XUSCCpXrpaWjbGozpPKKVLxE2BZppEudhDHVHXzeo9a0VOtTECnoPXd1NWhBQ08IdsP02+jizVGdibKZJKdXdLy9fZW8tPpCW177ASHhlvdB+8+MVrI3d+spbdPb9howSutpLAmvM9GOUuIE3Evdt86E3u7H9+C5amwYtloBtiCEID2JT4uTn6s+8c+X0o8tmA49q3gtzbRuPHDcfsScfrhuGcScWgiJB73WCLuRDKOux+9IOzzWeM5hUZ8WYsTWTzFcyPil4+If2xE/NWIyZ1BMdX9MBE7IQldd2cizog7EyE3xnnEg24a9wW03L4SG0u9IAF5AmN7xrPYyxOxr1MLVYUYlykeLFSML0+ktIZPv4/F7VMw/yeVXo/ssqV18i7qzMy6Z/Gfb3spL3ijpmVmam+Lmb88tRWk8Dat2K694dM60w3/2KzTfXJDO4TCEGq7oUdIEyNa4Yi984YePgWda6h1uoHjcmjVmrWd4b3ILcM787Im2Lz+rDXAPczUvbpicrTVm+W2p/GL3+AmO35F7/rYDBOQhU3xG7zSPPxGGkZ9MPonVq0J24/uQ7yKcSdGS1adGMoTDxoaB/MeB978T39sDUDsegRZ/cFQ1CgbmHLlOfHTqaFPTbLBjDqSFljho5kknXQNJF/SOGh7FBK/vdbeuiZMTlbAPLWgB/XxeCNp3IK2zDAvchPMTXEOiSrftH6OvrrLGmMayHvzRPntgo7QoFEM2crJX2Dl2rjSqmnQoGlXsS3Pewm/FKNZ9ePEVpubPHiOaoY3ljF4PJixiq15bpZkOAWtOTTr1AU0w5zGdVZ1u6oWhKCiFNEdaFi7JszSloxI67IgysGs+sx4GlrI6y4F99tqdyGr3TYVL5JRZuvXkk8QEGYce78k9Dho43BB3ManjRA07CrO4Vfhcbz1WVEoew5rgRZBL4hR2+axwVIo2UfRuJT6RCKVOneXl/RRlQD6Lht29ZdYRd7q9hIcRNXVpcpjyMF7ldv9ReTqp3BGTKeNbngRFosr6dSXSMrqwGZBGidkQgbkpwPQZKyn5O5SJiUBka4s6fxdOJ+sRfMy4xrvpA0grTVIay3SVGltrnizLenrEy9SyO3kuSnI7ihZ+gfUkR2i0kt6FqMoBT3MvZMqMse0Qkp/A55zaGGsxHRCbn/JMi0/zq8juwHUr5Wj5A+L6fKvHY0r/RrD6FCHWtQRUtmlUXZg7yVDaHqlbbhXi59MDX1iqm5bVmjQgFhjrSS/mczMCFFjyWtoc3Zhc74wmaqoiOdjwiTihxcxT0NunozzG8oBOD9iIQMntlgcVKG5biJZGgeblQQjD9TCNHhUDkMRgvPZwDrDCiGbuQNQDLFHy7d5yBJKBtSRMvdDrJa3esjfYlRDsFfhyLu5yYxdvepoK1a9pGwyc1PtIT9bPIq+cil0L37KsxZ+orrJQl79KqY2+qwD1NtUNRoKtkilhqRjEHYpI5vclZucxdvvhIUILk0pJq4Juf+zJVwAb/Y+q+PTxI48qdQa6aYU0ULwOSvMGXiT9pd2HMdGGbIwqZtyIHsvOboU24rcaaJXkqndNa4JN1CpFy9Uzesvtd4vlHvJs0vjvaLQS37BwjE+H7rLI/ACtPTGiUm2w7vYM7U61GPSm6vXKsa9JSCDtZQY8u+ff79gRoaSp9E0bstBPipkYzUsfMZzqEeC+nw56BFHzlBXGriXtIulDCWLKnz32IA5pJRaRZ9BM8qOUK5cgaaVLP5YleQ8LVX0Ovqge9w0ibV74aSR3aPeqNF47CccZ7ZaHFS1u24qmTaJmk8xJwHJHT52TLoSt5Swp1ZC90h0FTP0k5YVhQbU+s0ivRNp4jcmJhIrtY3oYmT75pVSzVnHMa7JBEj6QzoucMGA9xat/LyWZYX5utauaLMzxh1oLfMbqvkJZUKGfHCg61kYVeJHManCJtdYpZo+5T4WK0wg97Gc1k1MdoQDd0A/vk4+eIRILmSoesmJxmfJGz+lRr0geeCEMIVcNTEhRJPraNASJ8b38MxKi366Ua9pbCFUlpOWZcxC01K3ZsyWOf3b/YsNZXKYv6/lRmPDYCpfR3Xh7lFdtob6mKY5TeaCS7XtTjT3qWlblmFM5d0y17IiYwYCOynwomaLzJWwFAiqY6AzUoUZFHQmgk6koFkJUADTM7CZqX5N0EXK0dCZbFbnmtRsa9xM1xbcMHKRQCfX/F28heWycQ+uxziz1nU2uMxk6Ec3wijIQs46rgl9wgU6+dQGR6pgbLAYFH1D3nm5pk+GzMJSDYi5Zx3dnHhEQy0ktGjnT+SaXoCX+em8tVm/dDHQmOrgA3yZo2NjTnCxtqEoFfhhSAef2vSpigD0V76rOm1+DVOYCzrV0aVOsEIIOdFNK78IWYvJUMZnNdSrqfy+Nn26bG5xqc0rTEZlhqOmTzDRD7+GdlL9aJWR+K+i23U02gDwS6FAxU4bd38pdDslWzazupdgJXWKsUULhZfDBc4+bACoJBdAvXakIOrv3dSS1tS5xbQ08gBdmZVwL3UqnBg1bM+EzOsybuJeSitp2IdSiYYnLZncS29wByR8DXQK6eTY+IRGnnLfYkeHYNB3KyUy17/sGqjSjKXNt15jFKO6rSktmTLXfGvGjKV4CSPxNnNpQbcydqB7h197ixtr9ugcWjPgngU1fUcIqnJ4VKHPr6lFVyns1j9UAM2AMzK6yZbxyIdcp9FkCFp/gcXI3TAbV6NaZDTGBWR61+ZsRGS/8nh7pyPMPRnSt6K9mRXjCpU26BNpPvHfdwqqzgQ03mMRB6FbHMcBNJjOj/FJaWIYPZhAy0d2055zVgzFYA04JVim84nFqUI6vd1j86dSzTfsRDhFiU6bLt5LdKhH/E29ZBXtJRWJXjLLJ9ZHU/k/+dOrcBcIekoUewoGBiEwQza3LTPNTFWuxJ5jZsAB2nViSOCrZ1MCs/gUhgTKn+hAqNoGqyguyGcY+k3YgTJ0SopP1jAwaBRgaZHHcZqj5fMb1zjahPHkrewk5/xbNl5djvhRQo9+lwvchoE7Tmsiq6nBK6qkCrN5H87mH2aPmM1/kc3YdWP2SHb90sWzuRAHu204y73r/pvZnJrWczhtk1pLYDa9Ko4mMztp0W6Ph9xSfNF8H1fq85DH2bkszvvjyQdZybw/yaJ4vnb+z07O/8XJ+X9v70RI9eznMXWUsXIqdoGUGpj7MZ5eFNFn4cdoCYuZ//ijCfV1hKlEyKLWXFZlJSeBfWvZXCWb4nOVHPMEcxkd9Gy50LKiKF/X2TUoPZUPOJuDi+DZMKhD00la4XJgdgNHcDKbTMaz6pChzCT62wB9ZDLg7l9WZMjjOb/OT0+Oeq+gXclLflRAL59wTTvQHJa+f5nZAGz3ITTl+piEOhT32DuLy7KCgTzIlXsi5Jb16lyz/IWaXYh3qjrxGtw6gHZ8wVuLaNG4Jjf61MqejRrzT1GS0MT2VikwG4kCffWB6UbUmSj5GE01YiJ0NH0njNKWNHl3PgWGeQWv3gRy4U026dvFLUUaPrvFPbe54myz6ytxXREagnSedSs3cQdCbtId33C/QQ5ingWH9S4bMERHB/cA+gRHo5HLPqYHJpfRYWSlAtLjMIcuVWlBlEl+rYcBuUmsYBgG51m8DuU3Bl1ny2FaCCJMuVvdjdWKp2ZaqeyWxwKcmDVBWlu3F8soB7BSsgZIxxwQIsVT6WENJpaD2Fv0ISmAfad4NybkHuqn55hYfw3X9JZmBE6cmoaRtjnPpo9C/CJNiJBa7qFd9AAH8asUewSve8zX8ob5OmEat8du7xRjQOkQMkJaGJ20G+snBTHnOOAtKo0jT/qpWhwlEhe4EfOhSHXxcvJXAFdyS/Q7qR0FnEvLUUTLgaUBflxM8+PuH8SteQvO/RktmQym+VZurpwhLeOKIp/rUGEcu2YRdk0029awH/uMRgoy1Girm/W0YpAiHriAPfmwvb+AdoRgoAyeIF5snNmSCWLAU9hoDedg5mflaNOkl5Q220pKG2NqpkZT9ze5jyUp6EN6z2JtSGO+vhmXUgvsCKelRXe0cQ+hETiYtClDcCBvRrvSkRnJooM4+dboQpehsvszSA8oOys5dlnMdg0Wfim3J1P/gf5tVn4Ryj9RuxvL709f5ZNyZBqtb9PuRhTs6ZNs+rbG/RiMYc32/v/W7C7tpTX7tvaimuEqOXIThWRjfXaiSgLVT8HXeMVGVGswXi2H/CTt7HvGammv17+NVctglfrG6jwLDK2u1d7v9dZWpKMx7T4FBmQwiGgLQjsKDh6BKTnk9sYFDzoyux0fcE0/iY8iWneoRps72DQPE38dAXirfjcCOj7YflixsjmTdW2IWS3TihbEK12UIEcaTsKLoCyYspza4EUIdW5REm02o6n4zDLaiWna0fhFOodohHvE/RSGnwNzdTEdgrBmmZyRnMBmZOB8rSyKD88rMtDU0jWJuiAzL+E51jANRRPp3bp8ciod0+di+o/T2QQIa3WrTAtSQAdF0p5XZw+ehMCUbxuEKf+z9BFT/nMsLXk4feSU/8TFU/79cbA7k2Dk9ar/bgHfeM03TehxZSY2oacPY85O/8YJfXN6YkLvvCY5oY+6/0GtSsFquaSSC6BrXS+1EFX9Cq5+cd18lZesnxtfN1/mJVVzRy+by+aOXDYrOjncUpKfv32+jh07e8nlc+MLcEA0aQQi7iJEqv3rEWm5pl9RRB/YhxEdtQ8jarOPRvTSJYj6SwwNfA3ehXCe9RtRadxNrq1OWLQx05M2pcYOgkvftkJYwW8ZK4P4seAsrOwy4qv5DGihBWe9bsJVJiwUdyx31Pdt7cKddiVPLDXEtqTLGbjtLmlFk05JRy1sSPCz9dQLWcLi6Pc+iCXuZ5RTdy+U9JTaXKCO0v+ra4crGrl2uKKnrh1d0beuvbSi+dv5m7EGqcmSm73kzs8YQiGVVjWCegMA1Oy0jIZbFIfju5udKVgvumGDBeQC79E2uG1E0VaOKNqSi4p27dcUDacxXIra1eWXlPD1fzG8XBOaqGt2DnEvtbrJeS0TbuZeAv9kHF7I5A44h4DKr/iAyqwhy/AG1oW1lXgbhZodnjU9KdUEZuLgOJqSWABGFBT1se2sgH6PFpfFNIOq9Uyjv3N4R8tLts2J52ojj6SMGP6KqxLiqJNet5pteDp+vR8vsSB3U9ilVqubbE+JbxFOunQrMQhjvSHvAvOGC6ynEFnPxpQRrOeqlLj8n/JvWY85DnbakmQQ37r1v2M9pjnfxHr6YyNYz+PDmH9m+UbWM2RJsJ6ViBbr5MY6/cqSrFMmWW4ZWZedo+sylswazukBD9Th/W+sg4nW4W0PWTJ7RB1MUIdrPOT1Ara1q2Er1bT4rAOVMYh39Gro4dsE8raZXhuVLORF87/bJJ2erJgwe+QmaVagf1s6NTPc1RvD02VYkOfGrznlkFdpHNqih74wDqO8Iy47bYGSKePwFEMw+nVVShp0mU5uR2twmUaL/QEW133oK95qmADyfXj09Z03KU+3iL19p3Lzz3DbDPkEd8s6wz5u7LJ8g497vVXvm6Fu980pLPQteN3GPbgEDwW5senu68fZvuSqOyCcXUXDc458yVW9Ae+TN9D31RCelb2OwR33cVmdjQc1m3I1X3K2HvGjRfBxTgl8DBptV4+zhT4y6g/6uGrAsToM8OlbGI5/AL4tFkjcCslOQsRHAER83GoAnjUvjyEfgviTLL4a4Fa/D98w8WFIXJUDpToGL+cA8B0A6INfBO5CYB9XNaeQIcmD8DwbhBERZAalqKqywIe/wgvkUAVFqfoKMNZC5GoFs4TIMgT/EgKQpOrv8P8W/B+G/7d9XHY//sKUCT8f+rjM9fmGU0BUmDvC22+EaF+IGHwLLliFcZCL8VGadeayYSAkZQMrXDdkB//Vk5svgYqQUlV9NNGeDfdlGIUxPvkp9DfV8Fddw6exPy9SDL5XFmX6pKfWQOTx5/H5ypuA6PjH0pMoaP/81H50QNVGXSVoft4S/Db8dn3YNdgVagnlc+9xB1obP0R32vL7+m70vzn9/yCb450sn+Mfx+Mh4nma8cddF7peb3kdMm7pGVGKrt6u3tRDl5aF4AHv8c5T3WGCxj+V/lPdp7qPfxamPyR8Yj/qTJ54Hp/9gbvgWcJbWBnMYfarPWk8BOUMH+/8OuCUOLBijkN/EPpapHn/fXIs2ok5uyDPhv2UGNsTH1M7w6mdvO54T3ygHm89PnTyw+Odx3uO9x0nH4SOXzh1PCzfmm9o/EiDq8k3tvukW/NNx+/JN4Wf02gsGt601wxUCJ809gB6escwLC8xzECb2QvwwetP6TBGPJ0KSwF1u7Qs3wSvcir324600Idp8G6QrPknZueLh1LxjFwDX8N4A3EEDi2NCPsa5+dv1/H647Pzbwv7ZEO+bwG8TvGJPXl89s//3kMD1r3IUghuIt4WppDAcU5l5cu0AzOsStalcfwCltfaJOIrEZ8wLYE4hyIWz03mzeSHFDupGc7klNFaBH2vEykGVPzw5OQhIAik/eVe6D2aje0n03MBQHntlNFwEeDZBCDuym/65cn0LAT8cYJfHuqRnD3oYc+JbBovFacko0/VRCVXL5orcGVJTiK5ToMgEXT1uMtvIS+vodLEKWfU11hvoXT7riV543YWKpREQawuNnZpJtj4DHWexZBQplGMe4fSTIj05f9BccrxBvfIb7SocC+hJufgBO6RHPpqols3txW8wTWdBsAbuaaTSKOIkWs6xN5/kXjHfY0b+ZViJIULoMmzdmc31rfdebIXqiu7LKe0sssqC7ZTNT2ntEFX96kaUn7KdKqmT+2ihvmOotufVk3C40XkoJam7vl3qSETpD5DEnlUOzJbTKg8CIFuhgETIxKKAZKfMlG7wFJFdxwmAhI1zLEn38GEb7N4DEcWsXisR+QHqJgRmchX3siX3cgX38jniZHJ/FgxoucC2azEb2L6hyFwCAOBURSAMkyJCCPw3U7D3XiuE+mC2f04gdY+lRPp1Iysy6sIuhc+N4ZyUGVu0Mo9+Dv4pOYHD5vH2hKF/nm8JsrjifpLEPgLBhog8AfEwrPMf4vhWhb+BYZXs/BPERgRPoEBMwQeHVH4k67oqXGjqEg=
*/