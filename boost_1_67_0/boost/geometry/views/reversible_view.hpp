// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP


#include <boost/version.hpp>
#include <boost/range.hpp>
#include <boost/range/adaptor/reversed.hpp>

#include <boost/geometry/core/ring_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/identity_view.hpp>

namespace boost { namespace geometry
{

/*!
\brief Flag for iterating a reversible_view in forward or reverse direction
\ingroup views
*/
enum iterate_direction { iterate_forward, iterate_reverse };

/*!
\brief View on a range, reversing direction if necessary
\tparam Range original range
\tparam Direction direction of iteration
\ingroup views
*/
template <typename Range, iterate_direction Direction>
struct reversible_view {};



#ifndef DOXYGEN_NO_SPECIALIZATIONS

template <typename Range>
struct reversible_view<Range, iterate_forward>
{
    typedef identity_view<Range> type;
};


template <typename Range>
struct reversible_view<Range, iterate_reverse>
{
#if BOOST_VERSION > 104500
    typedef boost::reversed_range<Range> type;
#else
    // For older versions of Boost
    typedef boost::range_detail::reverse_range<Range> type;
#endif
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_REVERSIBLE_VIEW_HPP

/* reversible_view.hpp
LdaX7O+d2eKPrQlve7VO4Ghb7C/x/a9pZk9qAehNPQs6T1UoajLqgD4UcBqdJET4vVmthvmjSJGcmdD+shoPTFYwNo+b3IAWodo7gKV/dIs/CjfHjgZ7EYiwn0AOfKqXzqBSWpcvoK7F8b357zHm0cSgNEUroWbrljHfs4J8CpvynJNiYCdqOGtpPe2U1hwcKT4mdN3WXCSjcIF2fgjPv0JU3l96j29mlHdkwx6+keRvfFGevr2+v/G/e9CbWmMo+Bq+jTNkmhtQOnrEcvPeS/Wz82DBaBdprtTsJp3uOmkyZzUeTeJOG2bFyId0Te9J60m8Ce/wnhEzMK5NXvDMwTUvv6NJRf0iwFlfWtnnJg3iAl0Um2rAmuHCesvvNzDvkeENiEOiia/U0IxiYh6Rm2JqWBMRazAs08CxGMl+VsRP4XundnH+KUvd3K1o1vt+R23xzZuQLdZrA5JorQwUJNlJokvmseL6I6q0lr/bURfk+uuH6depko3L9ywKFBKNGv+zScgm3asLgcXvRwBijFHlTnz78zzKXIEPNHDCfXml2DApEQSq9qxLSwAcSlPQ5MZcP1b3ZztpgSx5+CSk6dj6o1zluwPmBaYt+gROsizhzv5IttnBa3Bytk3MM1uY5EGrbSsgDNSShdDKSAMzK5MDq3XMsaC3ABQG5hMFQotoNyWj0ZA1oWhRRscWK1eD7gU9IweRaeGPGWrv0pt5WxTVn/t/rs9LE22abGdUD9/FOjp6jHHJ4Ouc1HXaN42dgYNRzyDpoDfUlmOSWrfmHVKo2ASNNcBlzBBDkbcWUm6KiSJVOzDRo2zUoIkl+5jAgq+XT08MV1XNThxBg6sJ/OXCpd6DQr7SLbuiopRrUIcXb1Nru6tWrU1z0d7qYzzjfeNJu7H1KFvRKPn+kiy0J8o6093YfKiBhQ2BhqG3DWo8KIc420VxxDphY654yAlsBzmXAhiFCqNfXuzjqg+IZXhqcBTDK8AQQQNT+K/A3XJqkLxa/XflIu6Co4gzWa+F2mqRJt3IF9LEXw0nPU5TybCNd+Z2tejYKdGCC1M4VgsViWN5ISRromFk1z20eZmTeXhYtYg63tPoobfxoOq2ckP9jastuTsYU7b0L0NKRJTw98tRzIZ8NEb8y3SwOBFlKbJbGe9aCxh7Yf1/U2htRlzPGAIKX8UDiQAmZm//2pRL9xIjiZ7M8Q6qFwLCfLOxzPBUjXyddqTw7cFOZ+zDahwRDxHbYX3k8UpnE26yaSloqtoRJq3maLuhylDNu+soIljZmlSkW9hBTifKTej+Zm9fQYbkg3iuCNtKAiXN1ndY0sAR1JwPKsy6rb8ShY53LmRU1lfFT8oC5XNd2ytAimt3nXWOoSd7Lps660DuEMfUSakjFNcClsVv7re+MehpyZSgJf1Rq/DrgidbEs+w3Z5rBZHuLjoLXVzP4EfUNCXO0SsAPycDPwZmJoU8euWZQCkuqwjqjE5pvBCPzFp5ujazf96Jku7NLXCfzgHhcOt8Q/JNY3MCQOjUtPhYeCtL9Wajo5AONbAVupPebZrjsRKLHeFOyOVq8d1BjK5SoyKMvphq+AVD3kTYGfCY3oXQFy/yR7S1eD2gYCikyFa/EbH9t99i+oihcBumYvqWVv1d5YbiaYPaJ202YXXDRK+ZJ87F5/Gixq8xvP2Q5Go4vqF1DbcVurxNBTgqlRBz5bV8ASuvA88mv+UnYvGl7thzYtB5hNNn9Jsj22cnDPETgKnvq2D/DFRYTWhUMfOhSo3RJWOnC3ZZa0NdlFOrxCrh2dCAguFlTH5FmXoEFCL4Fqeudq4smJ7ka+tw+HhywpJ3vFJ3fQC19egIEUdyTakjO5KhFS34Z77XXHNQ/DtPYAmqtR04sqaoTzRQrGzd05AR2EUQBne6xJ8oyzh9vZpzAaq3r6nAPEuRLQgvWQgTaXSYGOFrNOv1nKfPElj51qK0hH2AtDvyq3FcVf04c2yBD5pSt5cCdoVbg8sUMSWwWvPcsD/uzeAYEgIUqGPx9oNPdYoD6uVTjSweqZ5VZYn/Qi6SMYc9MEYapAz34/5gyiXjnxu36VBccPsMDuPqVzdKZgqWyRAkmaDgQb1lMjGapccLwpqwk1/3X3Ov8rLvpoJpbduNjEImHEZ5VLt9HME9G1kpfZJwK+VSnTXvpx3ZkGRBiA0npHU362uI4IYAYS++cum1Qoy4hQdFmuQfREa3QSgu1R0CFwn2vBvNYN7cv/pLAWeg9/eHMnXN2MewdJnDVbYNbJRwm1I70UUIHO3s7Oobs1IuqC2KqSuQMe3lBJLtC2OpD2yQui+VGukvBTbVpEwgDuZ3kuJ6RAUYdv4LOQM6pg0bjKXRY8waI6A1uda9yg6GvIRGqKTEbGHW+mq6wOIfAVcuXUw3D/9woSXfXd2yLaDcqQ1S6oGiPoMuF2PRG9OpeiSgQSQRUOoH/u22xRSayVGc8TbqbGCiEOvCayPDEXx0Rh5naNw6GygnbZAt1PcIlnEWz3M9AZN+dShdTMOJ6gTN/ZijlqOG69uMykcyvYzl1gYXQzPL1iP0SxQnZOEfm5bN2RUY+5ZPWtYRbVUilqTB80kPLIn1U1qUq/uCTG1byee/VQiHUX+++FNx/d/OxeAFu0c5w4nSbIlNu9D3sQ+ZWuWMSnUboweDCjLfZBe6BeQxW9sqLCZA6vlVHyqz2yRQEFdHN8318+1YatrTWfLtMuSjA3dhdZobYGo6qxW5zdYbMotRHIJJtMfdpIBQ6+nVHAKWc+Onf6QbtGlcN2ImNyjGsfJkaJfao7lzNWoh96nRuMzr7DvlOnvnOHwB8juJda13obZWvMtjPkZ95mQi5g1EV5yeZXB6UQwTJoQf4PBrPDQj7z1eKZGdBR9EV1l5jgBp1GyasY3H3j5T3FKypFd6pem0uLvpMvfwHJgzr4WSQxpe6wqZu0Bs97yzzdmEVsLn1YBjxboJ+eaNTW1c2rEy7fnv9CyDremgp1Lyx2Hs1BqnP0CBB1G3YurLsTdDZpGMI9+wXlqL434SnFUwNbC0po6oOh+pzxv+LNs0uWyfDR7rYLDffA5Hq6Q+Uq/J1dmKloOW9qS81nvnOe8xp2UHoDHzFFqxxdx9qlABPujbWZV1dUOCfuhkTbRo2Jq+On1YUDheKD41/GBiJhQFOn07Sh7N46oUv9pdR9gFOJkGEGusKjDmR6runSV05wouWoH6RjoL+PrMlp043C4ja+zBSOLfyb018iyq7/jm02IaHikfyUhGmEyBO16bhjoxHRA6nUzKTC6oc3L56vATMaRfysSsVOTw3K8enI7JDig6EWbTu49078tLxwcPWOL75yLxsvOZDp5IvHZb2MJdZlASaT+MCVRbWvQuyKQuPK/s20jzILU0SjtvUkRuRundVbaB8FpAJSpUThWdnQd2SmZOyUBVNY97wWdpAlurCEq0YcjuBbueSK+XpgXV5S+Wb6hv3Bi/FeDxThw6ckLWUvSasfS1S5l71k3JNpsASxLyRm71VA5pfBkZINe5lBWWWn03od1fJuAFX/k5sxvdWeiuqVIWGpZdXV7duAXTlNml/9yoEV0CH3HsIEd4q3lIRflf1svrNATE5r2yEWhCv+oVeiFeKVjSpqH8nIGOsYIQmYRwna7kt5wW1GJQxEJSLSFBFkk0UV42RJoE/KgFaJGSUb8uh9W7JeVlnLqYbQdm/Dy81aVNjeNAbCaXeYj37jnozH8UPvt7ipO9XSJNCXrIxh4TaO/izo9xd2BwLwLo14u+h9A0e06SUD0iX9+ZZYkrSlUoCeXcmXm8XNkwBEs5SOZwhf6x6t6IaXHBwscgzdt+exPExW0BgKXBqPtOMQTOGyQ+pYPgoGJjl0eJNKhTOJpMD80BdHEonXDSTj0aeD8GGIuYbIYaO8Ix5mRCafqXfXj30VVnkwivByajBUCm1dAHDLH2AwrrCRzjDhjzZoV+zQXDiY11lA83zM5pklX7qoxz8sdcQAeUbkK9VAkJ3ZL83We7Gda8VZKieSKzkZHR3pHcHvXqXln/1iUKVp3Utqka7hjzJKPoC9b83qocU9YW/wkDRyGn+L0ZpOtq9kHbZa24mk1RL+JWbYZO1sEV4w3nTwYZmrzF0nBvmdG20LXejrI3/+NKWklsCLtjNotpjfJJFAbtw64RfbY8KVRAT52fj9ycVjpVb8ysDUuTEpmkMOE88sNy9ZHltwpY61iR3KLu5SFb4EbYzi6jWWaadoVTAWj5AM1VYuLxtUjlDAUzW5k3c8u0utJBt/A9ct43nPuKi4pbCCeHowz/VM9zj7Y8xqg4cF7WLAIH14ynXDSVXTwPtqDuVtZpg3WXF5u/Sa9ZVII04mTkux1QbweTiXmlISpJSp/h+/KfLkzTLojCwIFC17hDKj9UkFHwKkRlMUAH7UtLYdc3+SNUm8HSysR/L8gdOHOWnHVyyshQ2oHACNg44qdsQN255fV/GlZ+SrmU8+6UYLEzr/oUU4TrXNBKakrSXyjQVEe7QyGbxbhCUPOpbjNtDMQ1xeQJ7ibiYI2Y95tqL8IXSsizUkrtMN1F7MRfiDuKMMZozl67Lw4u0kiTAx7/LgHxolhnrEDC0dbt9DgyM3DjOp3K9DRt93si2FpdOYphzel9Z2SLCFYBiWu2FmbbyOxJthrhqBc32OOdUV7v31+5QpA5/clCjUUGinGRLL7uO/zDuWVGmXACM1joUc5tneubmJV+ab3HoArgmRvvIlFsbnyMecbIwNfJVksLottUqmykEy7kdnKGHWfFlAujC1i7TsP9Rk1nVw9h+r4JBXvWuMR1mFrbLhlwTVW3W8wWRxp5m1NcPbeSoGSSb++G36A8I1kniZKP8Ig/YylOURQXTTgcI91k6AtdXiT8jmLmoPuTGF5ytmMqcwpumhezrZ3eLnLD8oEYq6834HTBN8f2QM0FZ0waKsvXWUu0z6q030t45/hMUq3o3wYCDxVpEqcRr8O2z5dYD2OpOashB2FY7jAwsmGXXdBXIM6Hp150fFQpqcRsf86mVhBiJqnkkUhyvp0bLr3VD6awAAFIHVq8qaMvrozufGidMRbYUNkPCODC3OqUNapr8W8BtTmhVi0ZfUeZmc+2PrpWrdTsNhuir8qe5/hVxXgOBXJlYRq7e/xYpLohdStdF9w80pqDpkjWLPLKoLRlFTJ+CNX1mIO4S9A6/RkwnkR1U2JwUxvT0l97WRzV6/3TKA20LuoMLY5bRgmhU5Ho70U2g/vD02M/ydEjh5Y9qekwjJPv2pe6uqQKbdR6rurpy4mUM+Bb5X5xb2yD6qABojqfyNIPmObTUT3ICnEcWoVY23Dxny/6zqJoKy9aH9Csw936onu9m92JSZcUGPe6ttLdeABNUcI/2MjgE6Xbm9DdONdJLbmv1OQskAZnmEggtSjYxb2V8nBPPdKccKfWnF+qzeiG4UPIO2uhhL6ZFYxl8PhmMxs6Q4/bcJn2qyVxL2KWiDUG8i8nlFWGBNIpzqRFm8MGe39x/xVM+fu7wZ1EUreZaPTWq5uxOcz54oesH5vdZNdi/WUXfZyRnqJ3uyKk0BntIzrdzbGev1NtqUCixR6dELc/aGsfiwBEs2JbePZrGOi2uywHBLSEXcZQwv0iofNbxrt1HvNgbB5+l0HluXsDjL2B/ef35wG/PnhITkE/O3tIEKkPSpg3s1wDXfZC4MjVP0upfQ0cDADUychoREcocl3aYb6XpdDZJdM8WuTU/+h2F08rJbh1T9OhY2S0cfISslDfGupaXUTGw51RvQZZNEp215E3kEendlA623Qytbe18r0RqRiYylO2WirVfHTBM3XnFt30B1I6aUvdfa0nJkJ9jOV5DJ4LmPOsBpHuqnDtN2wYMVRlhqXadrU/M8siKFaTZQ5bX27gFo2LOYJVc0eXieUvpmyJKdpZV8W8ny3RiRsinegRfpSRZMigePN2grzhtpLMWE9PF8K1G3mgklkjFANi1d9yb10c1UK9NYvSV4dYn8boIPjklX5ZKbsuWiSoIWMfMOWVwD79cOoUuhj4cebyW558abOPh3I8bdGXAbJczVawXW01UZzLmCvy8mGUMrNB7X0ZtXQK/3udbMm4lqmVg50aeQD2rvcsPd5ofHcjyxdyAOSAQ12SPAV7gRUARxg3uHFe8vBItlICoGkpkLSSdSQqWDxNeRACREpvBNm2Kfv3sShZR/EK0c3Wi0VTY0K/itm9XZ/EAyqoNSNE0aLbwVVIJY0mKU2BkhqJYWygsWZ7PprKHBfT1Sd16fwkriyaEyqTV9R4iJ9dsOczQtqlTflhGSWwN39skRaHEBc0l+xl/Rl4cwGmRYEsYxmjp6V6T2C8RfmwgXDmcqbpwhJemcOYaTi3zCqbSeTeA8tV6+7ocWP+5enqLNfUJOxJz+N4G4zNIbbrT9D52khP+rjzKvB3C74TcBtH7AY03qwa5QnXsUzHNqHnZS9rIOcLuh5M5i9o7wBv1VSVx9r3EoxXvgUI53deuis58eWlVNbY8o2MfqcuumQZELZ/JN0CxuOlQ7F1nxilOfp7rDEp07/qJsraJOQ4FHymBrL1B9qfOYluBTeJM5TJTtWxj0WJ7oQNs6hDGMX7T5Wav11IGqKRlE3qakwb/xTBBCnEG/FZqO3TjvgPulVjwDs8JwLfPTfarZ4Ydyc7xJMoU9DBol+C73S0McMsoruDhQ+XBmlbkT5P7yazXULgKJZuCPAywe18DQhlo5Dyj4z1t9x6vEHoRTs4zc5qSGgChbKoBfbWyLuiXqLOFtzkZst9RyS3JhSxPBcagIagvk/qujln+ATrnXWdi0fHPdUImeJMTr1n/+HGk17rk27/AzRY12eeQmpycpbgbUi8YoNmJZRhvHlzhSYy3Le+Q7TtEyomsVSA7uKGioJhsipmIl3enelARbm1iMwhEG4r7iQiZ1lhCMVKhmtH0/lI/G6m8phyPSjLK3whYUbhJRJ+g1YiHWG5fku21+Di1dkXpDyI7ktrK2+tiZq0WXxoWEF8I7MuOvr3Hhtn40KrdK+zbzn0yLF1mVN1eFSpGDOV5l9JZ4z3z9sYkWvjbwPFJSVq1Qys1ct6uIZHLWPtjYq391USA0b/wLJjc8c7DTiXbXJ85qn60rqdck16DJzklNu649rry5SXH052DHWaxWIaEJz/dVP0pXI66CGHWV+o1IqfsVK4q50VHJkXYunGjC90eJcUi4x5dnAf0gWydz4LiS2rNOYFWKqT7pLgmGeibIvTl6fJ+MPbbrbTF+deSxINoY9iYc1AZa0YPWbaC0IUs/lzM1zElfoDcwNiR8VNhoZ7Ze/wvmULcxPEFh1B0AvIJ7g3Qqhvhxf2iWHmkCTXh3zWv8A7RMp9kpqo1FeNrn/7buGM+yQyUamnEals+DoGsW7h1E/hXOXvuvanMUOSmyHhlznOzQ7Oz1ZKxW8c9DMcyOyse+3Kk46gV6jPt6rODJ3uOBkSxNk/c1KQOKOBa0f4+lVfjXE78fdDXMv7GG4aWxFeAgXofnbLIbHso91zUvisEVAecZrJ/JeVMAxZIK7rnqlJuJJMqeKckoJjxaKIEr4ydS/b+jSMlqlhwcrFlvJlM7QwJIdQeMlHog0tHfwu8S41/QX/tjm1FcK9qS/vQOsfxQq8YUSUEKc48ZeWOqWCNBZD50cD1cbf+xQDVjuRp/0JlQgyJrS6WcNNvFySG6TEJF2etqMgjhPaTiS7d9ihyVySsMV8TlIEyAV1RnLiLZUfS44HVy986HN2uPqekvG136vwld57/BkrXizpL+IXsW8sxNLac6YrNw7py9n5ViW2dxnwmp5ycSF7Q18cd968e90w0Lil111L5C11a3q8t3fMdTtusOBsc1Nbab1J3VlGj0yhq+OPVkc1S3LBe6OjvRQ5d3AvCJJp1ro0r5R+6gkIScM6iUL1kk0MkTKiL3xfNPfojFOnRbytwEwivC4H8Wa1c/depcnkC3hDtr4COS8AX7O6p6uQu+yKLq5pXN6w5rxG9TtN3sVbz3MDUI5WJhwewuCCd55P0ERp8yexVBNLYixnMzTueZidhYrKVx94b9Pr0UxFVkq4d9RB/z7AS8UixS9fZ2JvrZeUXQQ93XlFPBN4ysER7hkX+DZOrju8eKX3ev6oFc3s2fuMBW6xKxUXmBp8puU8k4QMIN4k6yYe5Vrn1p1KrpfeMKBiTUwBC2P0mJL5VG714E/sNut//tUs3BWt/kRMJE9FyUQwxTO7/TpNYKlHUX66D5j83n6GYhjx3HDYx4hNyRwprMVU4s3j1zi5RZGYzpaMeuwhTxU464F/IkjYrPsHXi2B5dTdmiqwXrrpxS1nUUs60oOJbfPPUyn8SAa9VvXCwtgnv0K7HcPaY6MRgPQv2VjjT9LRjlMHf4/UMAV9Y5HiZu6YkZOpAyxO3fwcU6NMJq7tZyJVhaC39OJIjydO/1ng1bxOC75USLUOeli0rpxQVdNVgfVEonGdF1bxFlU++3aVJq8hCa6QFdzfFyJ6pOL08C8iimAUtwMaN7IiW+if9IiAFVbmytS5DIDpS9HV1KnZ/f223V485v6Wp4Afmld6QjaeoaI2jvUBDVGJP+kY3AXl+Z5qwCzCDiYbKzAiBE1ufiC5WvesNU2BbL6B1dRmh/VoYwE5VhQJzlNklDkyBYdjJeou9fIp6hNYRuxOEYSsMD5NiUN68JAb6DCgQw8Th05DCiu9wqRghLDmUBZ+HFUDne9hzTr9sDoDPd3LfPx4rlhuxPWL5Cv0ZX8Oawx7frKSqjOz+8GoRFaKqjfdpWYuzhQX6h+WHVYRxohEDBzmM3MrpyW4zqysOqhC0fS5W+cfeDf0fN3m95a8RPX8cHwjHcKBlYdQOxXae5rouzAo813nGV3qiTOXmc8WmdGtU7P9AfNWs7yScxEhjFn0vS+7zXz2qs1gdMYE/6QdPaxOJ3n9nK+/1mcTvfDLRw7c3N+ZpfcQq6gh6Qco/uRJEqzc3XfUyt/6wpdjXcyFzG1kRYM4/E1HytJWpjxAmWlLbTe8EjBFEjLTblNt1Bsn6iSOdUJFa7CC4/Af9ExFdlJ6HwqssVmTXcIUjQ4ZlreKmZ1wKrRIfCHfeqlDKw19MTbd3pX0082XN/O6p+9KrodqgfibqE7DF/jSuIL/N04=
*/