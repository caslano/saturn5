/*!
@file
Forward declares `boost::hana::prefix`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PREFIX_HPP
#define BOOST_HANA_FWD_PREFIX_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Inserts a value before each element of a monadic structure.
    //! @ingroup group-MonadPlus
    //!
    //! Given a monadic structure `xs` and a value `z` called the prefix,
    //! `prefix` returns a new monadic structure. `prefix` satisfies
    //! @code
    //!     prefix(xs, z) == flatten(transform(xs, [](auto x) {
    //!         return concat(lift<M>(z), lift<M>(x));
    //!     }))
    //! @endcode
    //!
    //! For sequences, this simply corresponds to inserting the prefix before
    //! each element of the sequence. For example, given a sequence
    //! `[x1, ..., xn]`, `prefix` will return
    //! @code
    //!     [z, x1, z, x2, ..., z, xn]
    //! @endcode
    //! As explained above, this can be generalized to other MonadPlus models,
    //! with various levels of interest.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathrm{prefix} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure.
    //!
    //! @param pref
    //! A value (the prefix) to insert before each element of a monadic
    //! structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/prefix.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto prefix = [](auto&& xs, auto&& pref) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct prefix_impl : prefix_impl<M, when<true>> { };

    struct prefix_t {
        template <typename Xs, typename Pref>
        constexpr auto operator()(Xs&& xs, Pref&& pref) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr prefix_t prefix{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_PREFIX_HPP

/* prefix.hpp
dBpx+K2uHWNEV/ZoEXTbFgqPDqYfkmsR1lHhW4npd0ZFeaJlnDyw0GfOzcK87rXL0lTa8KTIzknb2aEE8IVdIDuCqEDDO9GFPvRsJBb0DlB2sXtx1ys8LKjDdQmlvyBpklsIw16I7fzgE4WMI14KANQTGrfQu0OGjp+7kkDKRLjFrAXO0KU86fRttyrh6FtGi18ICtDyATlqiywYr/o9FeB8B7hD8NmeeQGm0sWMV/4sHjxSqV05wybO47diKrA4AnBtbyuRSMgVkXnM8GtNcPkvTtFtwC685f/BOaPkNHVpadWrbP7YpI5lTRm4S8TeQ+2bO8vjMt4CjWK85kOVn944yFzgsF9sCot9TxJbbFKO2Ek4LgVjMRGOB+rzBj++3g8es2nLIhXzZCy9C9Bf/6CJGKDAdKTQbXPL0DO1YfzgbacFyOLZ7M09RZ4R8YWq7Z79gDYEPiglUfQ8A+nRNy5pRknZF461JWxcRRkN3fPdyQrEbliGr4upEt7SlHdx5Y506uGWSLVcH4xoqkXbu/sGuqH15+xlGxIEuz3OWJq7Sa6Ds5GFu0VSQKGPVRxQ7bBZakJffQI2VP8YtgXWgOk2mZnphTzftCa+q3FHc/9IH+V6xdWiG8fT5BNxXCF0hJ6PRG13DhVj1InTF9sJpJT6Ux1T5vHclsoAdrPCX8lnAzhPIM2lhoMkcR7ONXFUpHq6mqMSTop4wo9URtpfKASMpj/x9twIjjF9LNKfLBYua2ZZNWSTxzIMZOqPnHNy20no0PMkqtPriNKgH5EuKhLsr3kdJJwHF5EuyrW7Y3ciwXZhnHZuDYa74xvHyTIiTHqM4axlGNd+hscLL6sFn+4gu5nmqvFNgGhLHslT96lm+OvJn/DNz0DpZedDX8kVicSNGs1tx0GHYercWxGkbDOn6po7xquDSRwrxmVHKrv28Eeq0ktTf7u+78GywOK6m5l4h3zTeuF1O3AjUOmBK/RkjRDKi2vwSPVfN0KT0h/I8BAoYo+7brHfykLP00CvuMnX2RNuvtW4mwK2Aqly+Gv1tS9bCz5qu5tHt4l5xFStJnLGzDqZkkuWihefti//Y++Nl5ZBop00vux+VdowjGJE81BXTlZZVz7maqjgXk4uoZoGbVOyVS4xH+AAzi591NMsLZuhK/dDnMf2wAzFq0HMmhZgJ04xNxJytE4V9sBoVgTiSeLnIqBSOOsnZI0a4P0vn47usAOfoNIFUGtJYAaKD184I1MqrzfQD61jTMHgWHSKrFPNTt+gtO4WVLwqM2m5N1dxLlWzd5G0Xh0KhpY4bnsxZrQR9Pe/yatc7syL3D4IcSm8kp1HMLCiMUAqhjo9vFkQZKlFFuMvavarmmZo8pxUCj1BWYhTPHS9jFsCu2SFgx3wEWHn8Ia53DUyUhfLJHOZFcK81XhZ41WM7BC0w8VZZ7JNJxZR4paUUMYZy1USUMbH5yYtwRXHrQqshgxGIOs28NgIpsR/zLg5IIYoAk2EENsyAXsAwtUQB4gAiBrrw9vKHshJo4HyP+gwOdrZJCuODTvayA01AucQGtTnAOsdKXq/aWsUzqhgoHGekw0BUdDGgkiJ4JXO6ftxN56A/4inYsLyw7dalx7A+Qq4/A8O5sRWcSjKMi3tAJ4lOcs0D5OPVvlgf4D9uL/ATf39xMs/Q46RyCpaaZp/z1lLu2slvOQuaz2hF3eelT4aqdGqFyToglnUnZx0BVMBK6W/c4PUn+iMqgaumsFPnWzQDPfPPoAdLmFOYb7zVqztAbGXMNeBR+FdXJ2dtWEr5QJUztpTpDy9/hu+0FUsfWV81ayUOemGKDg2HiwRlQAZfoYp6ycOVBPX0tu8OL/D8oFeqGD+D4bcQyqpNVpkaQjp+XLiO3J9j5TNPYPHXqPq0er5NoEap/OSAqLr4j+5V4T6c+rqNXRGQM3P+BGSSJp5NSucCgqkcyvAjzi2MjWrNtnzRyv/LvBp3E20hn7APEUfGlmzgpmxbeu6Tuao/ZWdYb4QGg7gThXGjk4bRePJC0ul+LGUXjvpcyrjLwCeLF1K5PnOTF0+tdgzhxAB4DtBWCaPr1qVn0NeHbo5TR0LKmTI7rm28vweuwnPw6g9m1wObrGQlU2IoBzNPSIxLbst+3G+2kPNqezDRXThnyxYpqvG7TEQtrdxryS13OtOznqg3A1HuH0+3hKADHgMZQ0RLVnjuU4lzKTin5Dy56CQhYvU+n6iFFXDs8T6MLVdXjFLLox4b6B2ZoJ7WSgkpeNSnSR82mqNFPy4bLtCGBlyvmJreXjMjltRmA4KrNF1YLFFJvxbyCCIYwXEiswnxleBawrBpoeU7nMcwe8OBBkVxrnyuQwkWWdq+wH0IlwULNA9nF9hSH3ceRGWBW+yrk+XkZj7GBvTXyI2d5q83EGwT5InpEC4MDzFW0XXCPMGJBk32I8IPJhf2pvGuTTqVo21PQKO+cddaTN3GnwqPntDKguvB3tOCF6D6fS1J9o9wt9vpO+/Bb/vtprlHLL0TR5QB8g53qH8ALG5Tc5ARbGA+bJr/wNE8dKXB0FSyJUFUHh+SwOHvAOwEWKFh09w0H89EsonIZO8zixioA6PrulVDH5fYrgxe/h+xMPyD9lMAX7ASReCJUrLkxCqjTXIt3dJlqDZdNTcAl1LrYllIJFuqMM2WQxFa9m9YwQ4spkXp+umhy8qL0vC2kIuTxC2nkeJ9FrNs4xfVnO227rwjavroHyG1xh6PtpvT+6TXo0T4eJuxcmZeYbRaNtvL35SWAPjJhMbBzmvLFttPvF/RBy3UAqKUlNn9z4m2ohQhVNit3udST5KMEh6wvRcA+b5rNEFd8YKOKWiSBanQlFi5yg2SKwIXYvwnvjomcFoBq1EHECkMkpdA/7+hDlUMwKgglT85ZWWCPmPMloij4CvHuXDhnMXt6imbL70WasNLNdSaeBn9cOBMVvb19xeC++J4oiTxQQkB2yMXZzzPQ125VI6yMbj6Fe8G6/2rDM76oGt+ryRjSW2iJ4p9CkhsUhFTjaTrpX2YdXJ7Vk3HABh0CRvovS/lSfUl1OqO3eMvMJrNcqPZCiO/ULpl3Wn+Efh5StqZPZAivsUTJWz6/f++VNvj7UQZbY1gicp2eJI2JbyMYVFfmqhGDEM9xvW6MHH8bARlODWuHxyebdusFtekyArFeu4RzUqXFbATZuAjjQGwB5mbBp+fus5oKbWHTCQUf4998gcWNXKEJr5eJwk8B46Tu8oO9zDSzHC6FFjlLR9o9wcfoWAVcX7Z/awSSyVHsMxJlHR2WyMhqgcrphwIbRvjq8WlJ4AZ/W2Ps1kYn01IktPl14dn+1iXjVq7k/YDx4pUtL/GNWGfajg/FTPU8P1OCdq7YR9eXRSZujjXU2qE2FtQeEotI37nFHcnSMeKkedMXP8wL+wglt9lbnqCGVV+ly3DcDpVte+lyXD9cgZeiqGSNjMO2daRd8/GHdK8CUZQCDQNcgeRXMHMosnvEGX91wke2xhqAOBGFoEVKMFIqaqGXeYRDFdVeJj0ZWxaIwAQyvI9uRX2PkflsRwL8o851SoudnTp+pXc0Ad+nddz1Oz9XSIeq9ezfbQo+y+rVR8RWgxbNjWgBcANOLCZRHarAhErOsUhzfJRMBgAqIrMqUZ9JGiVKngyZTc5Qv438MCvXHABWez357W2ndmrT3fEkrTVDnxsvk1oU00XwWUDm9zi/VEPyTx0yRz6ZB9NviwfKwMPTTOOqF7pIV2U6won67/K+nfpV6IXSgldR050t96vFsSTV7hCeX0YHf95yqXjR8d+xqZc2TKtEP+KJ21KYoTNT7TRkussoEY+dJ4d3pa6113MgwuWtGGCE3eS4dZToVTjzJRG0ysMkycYviuIlqZVqBCc7sKbk/nGG3/BaQ4HsUC4B6zRHtcuY+paYHZd1iZGs0CsGcIBMbDsiA/xZWa0KHoq0O5qzrCNal25adRbr6KH1jTgTvVfW7eueJVFX0/snGK75kBZkR3WCkltHzsnCtulQ60Wia1Dnw58eZyAiGWVZyzs5VjZfnij9yXDr9fnqy5oH9SuXq3nAzywycArvumd8qeA2E5yYUaLJdT1vDNbVGpPHrXe1I6JoFR5h66pka/gEqzEupWKmEuk1ZgDXDr/4i3Wf66ill0CA3WWTtDkPVNJjf/ZRZzZAQP/cVGKbf9gJVr0353Gze6Nq1Wu30UzcqHpQ+3OIjB6IlhBP1U79krQqXPzO6NFlQXCdRcChSt1oVDpUvHIs6Pz+zqZRRtA51LeLmCcGo0++VnoweMp+JCy+kHGcpuD2fiL1BQ8qxeOOJ6VWSzEO4imJBOAJn+JSbzH9VxMeUrdc8/pQJpQXuktEFTBK/5Bd3NB9tz2u5nVE8LxEh0piEmaf5+801MJvJiOS05rJpoNT5YSWa76u7Z9FyStVyv3dRb6RmOT7vr7lVdP69qH1WbtvcpsPITB2DuQX6O7Ji6XxfHjsMkmdSaATiVtWRUeREsVa4+S7WT/k6Yz4JH+lszZ/0wl2uVl/uriGjFYbLygsyb2xA4pUrtoTaHDHQi1Ow2LorqlwTKZVE3pGfLZdWwHqIA2mzOW25NRFv7CY7+UBBA9rItEscjXA69JKqviGBRwfRriXP2j/abo0AQuSkQIoQvMZjb9XMWEODNeaMVKtxRBvzzt9mzW8aKITMQsx6HjouKnXve3V/wK1ERco3ucd6DsDu57ARLej65zsWquJFoxUYNTYpqRgm6IpFMdGDcCycMEAvYf4z0BwdRS2mjHDOvD/kZIhJASAhn0INx0t9Cnv+s1mDZVzeXMzjKMXPjTcFppPBPADP0wLrQvbc+e4P9FOnRzxScdwbofFzHMXdRaoISEiaZHJSGTPLpxDH17E0Red0E4T695sxw1w9uNclxPQhZCa6SMMSZYGA80UMh8Kg0d4EK5ooaiiwzcjpnrpqMPTctTCXhYBYWlrQ7gaebaR1HSae1vcK/iMkmX1PjDt2RofZQKHc1WbNBkmD36uMU+fN7U89vO5/cIn50i3vVi1EY8mWZWVZHNvG+0WGAdNsvRK7hgYY7R1Qd/wGhbYyyhVfUHMyMqCB1CY8PwkKQ6Fs/qGRgH3npz3JMNbyz4EVXoLmjVzsmIbAAyMn1QNkVXXuxnAY7Y2Z0ojlNbtYpwTqOGj+otFsmnCT2dsaqpidjX9R0U73uj4c/Mzve5mZ3vuv46/pm5WSxE7/2r7cDJpwiS5dbA+QRL++sWN4WLu9cHmfxqsuFm8KFe84YvZJwgri+vvdBXrXcYHhiiW86vHg9EG3e42oSApPXLXbkcGncri5gIjg7StOi5ZM6YxZLY643MO0XXLx/a6ZA9y5UmkrOZ5Yn43fnEi7Lij6Jy16dJSh8cMe41XI90XL/S1oD33n0zWirMHO/bres2U8MM+7DxWDiMGf9STx6R0//Fcz+5jH0tSW4OA7Lgah7ENUOsOjnE2Djyg8HOjjglpzPbYI1OaFfjrANUD8cYnrh/CZS23b39Y1T6ZXngKykSpb1/QB63HNMYG0jtEe22AcTxdMR1y6x/JmjNFrr7GPOr509izNJ+YdSGb5OYEabSmiq1+1aiuGNcSnaqfqbcpE+xEg+CPOb00uU0xNEPKpnDK4jAcg6xS523u8+NgHjmAgVjX/06fefekuxlhiv1DuQTt7OLCOeYxQHnnJ6Yq8oXwD5fMoWFAkmwSXjZdcZH8LZzdLBrc/jHln3PemztG1kXXax3qHsc6KZ+vkkg2Ejs7JMwiAERzZmo09R07sjj30QmPw8yrGG8zVgNqI54R5esUHxKOWHDykKu1AqYc6MyE1BrsubVTwCsX4Fe+KmQOVDbph8Q1mn6FWTsNP0dSj/tVAQg8hs1XhawcwSSvcZpErE9kY6uGKnOhAVn7RM4tVJ3OgM8e1QoWPnGGCuClzAFVXn6jhHNoEF2cB9meNrZ58elchm354qHdCvQx3yjewx2ksPxg590Otwkge9/gAAtyGio3Hc/mu0seb78cS58QQw0vYJcVKifFlM2SU/ifxE/GWmnOWQ4ShW4qsVCwxzrSEnJmRX3slNgymTU6062jn65xLLmC8209OIzAvF3qrSPtgCCdpq4jK2RKf6St6ZrRwZJDbghwyiKlLrOYkmn0Fv5Pi/lX3GuCj8hOUfT3iOTByDKoQMmvQgTKAzUkd8o7DrAqVtziLMI8l6adtB9uTZMdvr7E3JLNN1HYJOaJNWGdfUIb2E6vtGR2zwxnmyMRvV9mp+W+r/bswHRouhguoARz7osm9YYJLoBs1g7K8Ov+ax5lsaJbqoCzKX7gXrNv6z40V+OgKpdBon4ZENbJHpmC6aAQMx4NX4D47k4yiYTnbD+pN+STVLJbOpXV3mMU1AtKtVxscxo/jC9dk3Mb2NTSG0N2oY0U/q4nkC3lWqO3PJYOIcJDpKOfP4c6V+P5a6vOL4k0vJMZxMY2QhwaRj3oh9UgNpvOvhnIRA49V6t+ioTzLIX63WExTvWtiu2qaJyUCrLfdgCNNQXBdDcnLS5Pyx++KUKIaveNhrOvuznWbfikkEtvtRi2dC5l9j7XYcqyllW6yQyFhW85UZF3tTUwK1cShbSWc9gnSISgXboKW6sCw1te14lGHMVZri+/0GuIUMRm8UF+mRTYIUd45qn9Pb7oqkrqnbdXnnc3lnydJ2x5KO2cVMZsdliVvfSynTrE2aCT10FyPokrYrVMMiFRe0sVn+VdP4DJLLXPaJVTUsRtQBxwwzoGfbNRPULxVo0sfwIKdrzECOAIDQDVfQA6Hz51okhXkPrrimp5NswReMM/G6l9UXbV76Chfdf9KDjsXjVP+yG0cOpE2Z9oXaD7t+XThEc0rutu3gtE8EWQ0B5ec8i6VBsBqlvANi7oBfnCIA5abE5bAvTqv0lt2HSDy+WJPcJzebYRoXjFi6bVw5SQYG3L+QXs56XFal+UQXeTDP8+ZNcOGiMJRXMdsMt7pq6kkpQ7htgas46DVQHnTgYD60uI2LOTwA4R3Za2n8N8hSKssTLSsAyhGLAUcfIDeeiPNq0BPV2VTc69R5UN2rH1S1sRN57Dr+kj2HrasPifclpfet4lsHpTdHm3cDwVDZeDiq5YcxVXb/G7IOWlSLBsOGIsNOZogDOEvYKvyy1cmPxp7HREDXo1+Aue8oqGPEtRRryMv5x5wZ25fBSjzC6m3V9+PMiUVyU0t64DKHgBwd6vpVEPzUhl4ZPI7RMz2f6OWsT86PlpHhdLM9Mk5VCytZHH4v0rBrL5OgHybM5gDEYIvS2+QepB7iAD4ESoX+dW7Q9KIfvTWlFwlNlW/WN8qBZg6VBmBXQ4+17Kcymi8Ypa+qHrLf65yzGdlPD2PztWM8pZMPesZaIBhnyyEAXRpW/VmbLipzL9iHjAX2KLx13j9T3zzgaEguuAuNjzhdmd/gP5SupqONlh+vzU92VudyC0+Dlp78Un7SUn4gBjP91bSfXgQMEOjfBfw5/H2CMgXNgL5DYAjIUAJEbkAHgf/pm3AZOIyN8alRQkFSBdLOpZdzmwh4HoXboVTbE3uKbg5/ZbMa+tqrOYQjImJ5CaIZcFowAF/7HGh8AOE1VJo2L4ApqghR
*/