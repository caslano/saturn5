// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

#ifdef GEOMETRY_TEST_DEBUG
#include <iostream>
#endif

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry
{

namespace detail { namespace is_valid
{

template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct debug_validity_phase
{
    static inline void apply(int)
    {
    }
};

#ifdef BOOST_GEOMETRY_TEST_DEBUG
template <typename Polygon>
struct debug_validity_phase<Polygon, polygon_tag>
{
    static inline void apply(int phase)
    {
        switch (phase)
        {
        case 1:
            std::cout << "checking exterior ring..." << std::endl;
            break;
        case 2:
            std::cout << "checking interior rings..." << std::endl;
            break;
        case 3:
            std::cout << "computing and analyzing turns..." << std::endl;
            break;
        case 4:
            std::cout << "checking if interior rings are inside "
                      << "the exterior ring..." << std::endl;
            break;
        case 5:
            std::cout << "checking connectivity of interior..." << std::endl;
            break;
        }
    }
};
#endif

}} // namespace detail::is_valid

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_IS_VALID_DEBUG_VALIDITY_PHASE_HPP

/* debug_validity_phase.hpp
F+3vz78XqnhJ/QA7/WYUUVG8QEUT/qRge3KlWvESkf5gmbdaXP99ut5SQUeTFlgH+9ZzDIyBFFQcUI8VdBQEDvqTrIHDBe9ZPQerqf5S6sABkYnKrDHhnrIcq/mi6TUaq72v0FjFTJcnGmm6PHRJBwvhWY0nwcKRGsobTxqm3IMvUbNd8KagiQQFeBuVFoeshkxgSEfquHoS7yP91HK7CvHaqf7KWVrhUIbihsMhOCDsgIye+ycpMNot4lVqQ275cgocDqaBufZRt4ir0ZfUGnxbItd15AMJzbBtig3R0v2ptCmFOdb++Qmacl8uoymHZM4vb+Gz33s4a5K2CFk24D7ahUQ2HeI/SALYdSzrietY+v3u4fJgV6eSG+z6PqupxEy0BG+Hdjjal57OWjCUXzNuryXJPTA9+gpcsf2URRY9xoydms1a3BKqsNOOYys9HcmUjXKmDxx7QRqtqlKHguT+DHDPj6kxpPPhNERAjBiT3v4Cxr8j+OpO9vLwCNkYwJJQT5Iv3svEJlpFR8SqeTrUhg6qDEuX3mRdFF2YrpAV1oQbHY7aJ5jAmfRRGjAmEX6AwVUVuzz8iaTKYx/Vcxhsopu2H1G1LMOSmD24aS7GIZAS3KJFzi1XcsuVvuXlSlpQ2AKH/cci6f7vIqn+zkiy/3sxC4EsYqTqMT/SePZfivHkjRhXI24dJsPCq6l+DZ6lHWbHWH7t0i8u3P859ixCt3Xedp0u2iIEEhRvLs1IyAUBGvH0ULuy1njs/mRcnxl0e/2cBocla01zYEiTVn92sMup9JlOVHgI/qNMwsWchN7Ur8Jzuyym+TDByjs11iTJ+ZS+FePmpFlq1DYx+C/YKpSicMXSSv9krc5Ge2g/JHVBc+JR+hr2LI1eb+W32v+hOmZuN/jM6SrsCGjSp0hph5lwII/gw/oI8o8i7M6wSaobYZXMbIy5w2NQfNnLoLixZogF7C09PauOhrJ0YyBlLQbCi5HYmRfRQrV8RWVSp1KIrO8dlUyY+cY0c78M4mPGwIgZGaItYiNmf/19RszSkeMW4g/izTaaTKl/SJxMN9tLn4EQ0JDdtKveoV5dr6Rdr1oCp6HmU9/PAq8pt4uPOmCjKItXfCtlmudu4pj2uS2QHyrFLRcepp2we2vCCYZDZcUbcm91yNOlXBpexVl9Kzo1o5Gwp9ML47W6Wbww4Vs0UuqxK2fBFz6wh2b6FLSpejojxxNU+90Wi6VHgu3Q3LYer6GkixGzaWt9ZFbkIl59N9ppI1Myg++2sfbHg0/9pA6F5rKs1HaUZ8UuaTSVi3nRbF7M6WB9W8TbVMKXIpe+zE8Pu2miSQWTh9aFVKyVvkRWce3HJAW8ClnEEslqZW2Zr+WdpvfRBh/WG6RJ6GtIs0TXBk2t7U+QijzupQyZBklsOyqzH7SmTrPdWR98FRu2JfgqezSHF8KmK2YdoSKv2vjDVg1RXO2cCAlliPBfvxSTR2I5Whcv6q3LRjnZere6EC1Av1b7erUJNtm4zFLBBpsZSG0I3rFDXN5BO9xCs921HabW689deyUEmq4X5e6CSMg4LXVPIYHmVQ68bOMUe7heChkmVHsgVHsQichrD0tdxK+IfT/Sztt1S6hhHy0cUmP6kvj66SNpltY+ri6i2oc0kbcClSp/UjUa8WVeY/G+ixVX4+uaRuoM0iGEuENiOHFpGbDW76zyXZGtG5vZaM4lcGesqqZKXN1pFMQ6EVtejOd/NM9IPvtRqXM/4lTuU59EwdLNyh3uQHZD/+pqny225ZAnG66/FvVpFKuq9mvV1V5k4LaKEoDh19VYh23V9J/fVl0lOuhD6X7imn2qMS2x8agbb4tYaZnEGJBogEYgz7syVA3pA9afDwQY/kM6/I1UaWPCoqaS53DNQWbNLFxc5IOUy78ngTlTrbDzBiLycvWUH7GsgSoM5AayzQZSHNxDcCDMEgDg2NjYycbJxrZt27Zt27Zt27Zt23by573DV9U1Nbfuqem+tMUGT3F6GMaOaPl2fuZF97qZrljMV9kPHM3XSYtfS2jhdCNIBk58PKtbQrU8j8J5xVIcW6Ha4uuH9TMr5XrJjXpoiZSNuZLlo+XLywL3UQgbSrSlj/NjXzEYWsP2Hwx9UXWvMEJpF50biFWN9QaRuFEmT+wwzZ/8beOqt6QAJMrdUcc5CbF3MSo6hO6dkXqlw9s0yBzJ97YDUgiZzbyzVvlwAwKjwrZ+qE/lHhTG1Ecchiz88w1OBHyXt3eTkUKwQcnM+FFwvqLz02EHT1yQEKIiGhix6FJO1DFz8+oZWXD3vBSa5BHdMJPPWiAuCIpYe5tbreO/44pNMd15S+tfhfhjadq3WkthX9wdmQcC0TEM9Gj/UuR+qJMjG7V5vMK5k5qnxNv5rhSMJk22FjcPGLH34SXFfC7q45jlT3KZeziy0ytZFwvNrRBEonFTSDm4ie2mV/kMFKtLxvuMQ+w1KybkwM1n9p1j3m8rRXXa8P9svbwlDHY7H38hmFu5ys0MtxZJzMp7ZXPN6jwdo3o4RPekVK5GIcGHCfs3rY4SW2oaVoPdVEC6OS8Iw17qDJMAa7929UGrme1ByrVTVSCYQQx9BaYb8iqp67bc7KkG87/vEM7+rOvC+cVwec2t/azgFap5bnGI2rp5uDgqvJJclRY/tBh2N2CvSmEzK24glF/BLDlD/sQx7vd8iOaZQS9dM7TVpnEqPIUCzQA25U/JII0uqPFK0RYgw8VZQ3Z1ZSFdWM0VnAVMrsVPEvWbKIWFlMmeufgNoN9y6//YYcEJRBJuH4vgS65NJ5Jmo/LcxTAbhbsHJLwKR3GEapOxKK0MGn8K5vxzUgTOOkfXbKT5K/ambxXTtJajOZt3RX46qt6wVgF2tH4PG1FUkkbVjT5qGWlgz9VKBNumPFiRIBgiWI3SJTurm/PRSgUZkrRjzGSUajef9/MJQCD2BVp6eF7qeYnSBl9yN2Q8uEE3fsGS8l5qZBvkbAosDmYA5okkujBkzPrEZmgams3x7cR2GemNo8MKuSBTY5nywT2++XwaARyic4s1g7LjPWA62YMME9S9Wo+5F1E087diRaXUoS0mALyyoEpNqkxsPjWsQTo42hUxzw2O21B7+jUaUteEzCJkLJksIZLsS4rD9wGMg8IsrQ9Wk7vCjmqk7IeBEwL9SzPMGxd84QzFC0589zAQlxDSxTFtNQtcFVnUc5gV/A/qOq4T2fEwlXfmH2MLvABHWIG9c9XeVfkwjU/cJomP1saKvtbUjYByqY56zAhGKYMNnfK8pUb4Ihai9IidqeB5b40bME2ZlZnjyWHIq45as7FVd49qfRxO1ikmzIPD/mXy69d72l4ONurZlAWEctF1NhHSMJWaeYPSI3cvrflmNcHfEov4eZUxv6R2djrhmLhJGDMeUHGZHZET2++7CmkcFVKyXPPGZwBCerb7zt/gHAmD+tdH2IHYGRRgs3g75B9fkZ/3Ck3lkv6niuAv/jHCIKvuGMCzRFrhYT6ILvbet84GnNkBsub5NDHxS9ANo3NyAxb4AuL1O0WBLelIb1MY3vVSwNGKizqQ2mIuSIV8RZyOaG0FTpfvE8MqIEyzAqtT7e3LhFgy7YSBLnW4XxoBf9cAJwfYsVJXH+c3H/Kxy36TAR2tFeLxNZ1c6oWBbnE44Is963Dn7oFvmGs0zAOKOb08pZ71RCztVMyD/i4OUoHB3poRSIKk6i6d5X5VDWOUyZ5Psd1JJu/qA+A0hfsYkXV9v3mTAA/RB7e9+oXd8YTO83wKQw58NU6Ge0me8OpKtm1ssf3RgrwCW6RjrQiN4YeR6577gWgDk5MlnvnzTAFbuMzdtsVJQnYXIaNMtifzw47UJ8uzqkOJWyV5DOuQd6Y3iryE7ErIwqLgNhsk2Njn4JaGHuQ1BHVglBx0vRlfAGq3Hh5L//B7igGcro72hE/dSASM4jZlMXdWbtEA0eX72MP8cyNiRBlqNTAbtZZpdmb+weLe/kEhftuKLVSbn7nxQZG51xncqJRS+goqZpjJS7rU+0oS2pDPUIPHFOpXxUP9a42rc81atU+Wg9KnCmfHyuVizzHx4tRBe8dTDfTmnc7dpfZCsU9W6ix99hOScxxVcwsuvbSmC76A8nU/a5Mk2trqujyOdpC67ZBaD4JxVWuBybSipyHgsYItDO0sAxbaO46+sEhIdrOqSuJ7aMixo1mskg6fnOnog2v5JzN2gaRDAs25FJDV2YtbGbzdzOAaFxaVa5UGc3j/Jlno3+FnU8fMbbJhXmb10xyibZ71giGngu4kqnyiltA95BFUoubVsnFUumPhiIXByWyqbFVn1ebQ+E2C4hjV36s851T60RhU64O32VTt7DHjqHLxGpbHpY9c6o/nVNN0Ym5FPZKerkR5Q3yeCLQqA1VcAwi2/RrsRifoiUbAa/hMdEQT6JJSpTLieMpV2Kg9EpMAEJv3yi2hnxNEQgXB+yqyRuHtRc1fLo9SMoRjhALt/U885uv0nJaLPLeL+fB5eKfAuJHwnHynA8KevQF3fiGB3Ir55JzoeKn1j3vkv0eftZbRamlkKSAG370l9JQQuPM4UI6iPzjxwhUUFoOE8I7mfVJw7/PnZ7uDKoAh+0BzYJYz+N4BHFb0MadljIILPqDHKHZEUQ/+3c+K/Nqy5DOcfzza6PcIdLO8oaICgtQ5JKOcx0SHgqZCGM2yht0oq+boX5mlnZck7KBUss/IY77ZvsQ8Q9vV3BOJw5xcHM3WRzfFBtHaCwVbBYgUrNY3zhOUItybU5AnIf+g48MtYc1HqApq9nKtJVUcVnj1T3ZSNMW5mR4LTHFg3LQfcpTcwe1nrbZfIk+4XRRrFyxDT0iE+BlHfxhd/hM3Nz2dfi85f1N2OUNTi4LnZdSCjYr8IN7O2i6jQgpa3E7NgpW5G5pcRuYkPavj/5OnaDVU8/G3SLq+QgWFheUqyUQkisnUulhB89pErYd+NCNC6KzEGglHhlA0qcCROhe0OlZELXwR/V6JYpHhbIY0q/Tohb3CEZVu66OxV5Ofu7XvNmadBO4orrxVypPzkyzC/e8XRa9q5FtAlJF4TtApYchcBXy40qYrtf24/zZzVajRPPmEJSqnRhRZ8toNwo0xOJGUHRjLbXNZ5hTBI7PdFk20OeXGPhzIF1z9SrzQWPJiYkM/BbBDq6uqENueQuUZx1KIOGbM8j5F99JjlZRPkGWItBfNpyyG+rvQ3yhVseBSBOYITM0xPlqxVQSnHbmQo2FjRueDcuupqWgFcXcLKLD0FZibc7+GR5qWdjF9eZJxwGjN6D7F79Jkvb9FC4hgWa+L/PJqg13cuKIhkWPChAZHdK+5ZjXxVeWbC0Q+8Y2tsjutKwVqbdeLON38kq3zNIlpiG7KgX+motKz/umg4LnUgLZAae7L3Kutt0Xe0kg2uHq9Ed6Uo8FvGmzb2raacCRxVx20Gty3d9dA+nGYv74iKZv9MxIhtzB15oKIyeh3E8znjixbMX7l0Fy2fK1d/Brk0n8y7khnfOHahEwD6G6AoH7rQrUj/rKMI+5Cw7e785eMjxG9uo566ryL7nPndL6NnmrsFrOMf44tL7cd0mv9EwrZpJWePlXn0GyKpBlLTAFXgVO0kc/1ssr2fdNBOR+UgSjY/oPjYegXl+WA6+vhyDle8pPdS/WRFX6UbES3Wf8vW406dTNBzduePk7t+FE32cVqNu1ItimGh2ucdGKRW0kOTm144rAczYDt8BgNzmJQ3lZhtrpGJe6ToAEu5RCcc6Yr39xNxptAPoT4Pg6UhvQ2juqHtfBM84AnZSE9Cdqm/jD/Tx8Sqg6cJyTzWBHBIKO2bwp6ZiNNo17dZxmjBHlNFm90p5RRrYyVnBg9zVzR+sZlfa1U5SRXeRr8TLYAPB1Mj4U5aeuJzwn2Un7m+dEOQsXYJE7VsgDQvUbgUY/MRWSE9mln8aqu5jAFLXWKoeajuejCNi+evoZET+MZdFP42nJxAdgGfUb6k3vLNPvw/uSwaoNvVq0x1vKPzDJlMkC0IBpbgjv2wFnWrkFTh10gPnfno8ZZpScwNWg0g51EDWqajfOA2K1+U7+00nsonRAClf1yvdcpI2WVgIBZ4ZHyxzvJ0Orx36SSBV0YVU703x5UPcswsnfN1uViwsScCGp5DqYfJx+y7dguDD660QIthwTj7LoNo9asgnRA7xUyXCMLlZwh7IM7P0jHOOGGQgzM8w1bPdanoqSksvhh799Di9qnB63zJTerL5xKp+APnCJBkfsiMCmya9lSgyJufspFcQ/PPd+K/fqxOtfEHsA/Ye7e5ubht8vqFkZs1j/Wpss4RfzZK/3ZWduYPnHMu1V8tAPX3HPHSlwcZzarC5U7wH+9f6Q5e0jj9ubeSHpyvERuPrX38bnbckh8YBJouLml3eNskAZuYreP9Jw8ET1SGlbemONIdkyClz4NvSbupZch33rZWE0iDc9jWnKABXpSeUgJl0+IAGZ2wPFCMpAIXMBuuCelsVjd4FUg7sxgW5NhNYuB11n8HAn8yO6M9tU8g+nwVawG7IjM9oW1N1lWcPi1N/0q/yqHpr5JOxSANbAqYZmJFHAw1qTc9qTKiDbGwX1tGQqyC0jyuqfgPETb9Pef1IkMDL7klGinwmm6z2TnTMFpqpfyBWLCrSzK5vDDbvFXXM9V6TiROFKUiLSsLw87URhfXBVpEHc5VlSmWCc9XSpfZnerWabiXCVPg+aqjwH3DXBxXlKUeUX+TdonmO1fDYEYCb6bMhxpNjQ6SWLoU0vLhCB9vohaznn/5/6GCa7e9IV8Gp+oTRTuM0kwVJ5GDNUKaU2UndSFV4JxrQ7eIxttb+ziMZoAe8b/GjM0iipr6Li3/xHGiGR6yG6Inq35qteLQtQh7+4dx404mkwgIuNX8GSFynqPuU+SDY5EY4MawTm4uAULl27firs6K7cuHrr9ICPciJ+Bg51U8JpF6OMT5uGI4ixnH+687FvgarOaIJBUUwQpZhqBsjMufWtY3W9ozLFqtBmSucptOL4mqhClLWn4SVclX0Qn8lRrqgf+jtuRKtmKyXIHAyTjXQnut7OJJqP7OZ3c0xMYCEKv0XOVNQld4R7rRiS7LFe49xwt4n3CINf+bNPJIxycVdZrSv03263SRCXbrVFEBe466ibc73s1envux5Yf/pEm5UJVOv4+p99rTYMn4AOb+i+3G6Mx5lmrz30GbutJDuDLm4hHUrbDvpyI4YCEgRwNRwMnlbKBew7GDVUFxk1e1y5XI+m2U87P5+OaY+EKtyuFTzt8wfQm+MrMYx/Jh+2EjfvzXvI7rpfrVUPOTUDRCzfl7fPpwBEkRe7p5Fbp14WMi8GkThvWzPJL5vcM93wBlk7TE3cQ585j+LsIyxfjG/RM5Eu4Ek+Uy8K/4Y8HEcRnVlTJJMl/mdPmR0ATGIwzpd/nn25fS28P7xaaCPrHW2gIkDbu6M9f6F9JN9lhhDVp7xbg1smFuMtj4CXkx7j+Zy+TUcXnK33l1yH6NoFFUYfo+OUCpGM1KrjzjsE4EtTO0FXaY1jTOrjRS7YVS0q1YryjNFDVCcuZ0IrPx59VPF/JSKQacLHHm/c2GreG7gFJ3zXW1myxVl4z6/Sg1nTvcbPrb19UwaA+1B/QuLbDPMYjPOsHeFZ3MWN3MWLFWo4Am7Peio4yLIifFZ4nmsBnHs1JxDO3/UOeexUMV9PudxnjjKzOjdMDHBtsChdHYs6u2nAeNrxVKCWkccEs8GrjQuBfllkpVq48lqgyIPTfeJAqJ+k3Iv/bF1DVBeupcNTF6j1feGWGZeqrGO6rXBaOikJF1gZIxc+f1VgMgiS7TqCPRrjBKyM+xzwbBDUy8sq8tRiRkdGOtrVl1EHgRNCcKPcnCAqmnJYv5L2xTL0xQJfi5OXLOyeBUUyv4+OHJgd+im3GbVun22bmhVhNXlz4Qqf56Tvhgnp8ZTWcSvl1eFuQpbtzz+7g78DSZAMi9aA1TQCOPTHcKaOPAYctZRFJ9/vN7OdiqzagALM5A7v+Ilz9dPFAn8cqezu0ToCXU1k0LtWN3e4/AuaWm7XATu+xKw00HxWcrnW+/WKfbXeHUwODUibg0ERtKhuOW4OW1yKlDZC1QlD32tJSRDFx747npGGLJMUyu5lGvqvo2UgRXM9WafuGu1Kzm7t6jMIwFwJb3DOVDtdjK7VCorOZPAhQRmpGrTntkm5cfujJ9VqDEmjVHFL5+YpY+E3y4GLSimiXuY7xS1s1kaCKrTm6MEZY5+yY9PUsMz9sn2RUVxWYqDkvHuW76ht9RvEdUZKHkE+w5hCfoA3hRy7ZShenuc/KVGtWZyUZJ/5/YYuhVFq4Ck+RZj2WDyQUmbEeFnTQQyFb1s78lfqdH3IeGrYomc65G/AdTb2+qmRfDgoStrjEJHBpTu1PXu/rOz3Czx/mLD8FWGkCDPQhLu1BMZbEOWqr0ldjR/xWFBqdT7EC54Dzi1HLPECEOxYEDx97+ye4W1wiGvEktRuEznkpwbbsZoT9+QN/zJFc8jdgFYpvmrhXy6P95MeVeCxsA93N0PeOAggXkfI6QZ0dFDlKQfP7jQeuTwWCvv2UbNrM+PRLdGlmhqJviLcBvb1NRC95Lqsmbquv3wClVDYCtJzIi2v7kMUKK8NLaKm4tTUPEu/m+zIqbPS4qOQPpXGW0DkdxUJoB5hcB9nlwe645jxQ0m66Zn+qY4jJx/JfV2CFw3wcAYcFeHE4u/Fw16S9zSSaBftM0tWTLGnKsx4wRf1zyKBwWvbNQTS1d1ozTJ1auoO+gV67NuqJa2p4C7sI5jsTnf1EP8pEM4TMDoTWY4TWlzZK3wvAxD/hE2k4eIpPOHYIToDdIhnNpb1onVVODxyRW2Aa8wncncKi8dvnwUdQH77iPfkR9/juqD00rmnU9Vhi7Td81ZfBXy2DNrIcoy2j/YLHG3By4vFHwHMLJQC8q7EHHgrQl8a5AZzf88qLB3mLvfPAQoaU19BcJaEf67i6HxCGFq3y0lQBB4BaIcsMaJ3CRLuA5a14RtxU7Plh5xrfUwG7KZohmOPu1h1MFlWGCeiNszgKujVzesQwYpoGGcabx03/aA23G0yskNxbmvU1+ZoDnB5xgyodGuz4UHF/5xN/7HB/AvTY41k=
*/