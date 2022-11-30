// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2020 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_POLICY_HPP
#define BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_POLICY_HPP


#include <string>
#include <tuple>

#include <boost/geometry/policies/relate/direction.hpp>
#include <boost/geometry/policies/relate/intersection_points.hpp>

#include <boost/geometry/strategies/side_info.hpp>

namespace boost { namespace geometry
{

namespace policies { namespace relate
{


template <typename IntersectionPointsReturnType>
struct segments_intersection_policy
{
private:
    typedef policies::relate::segments_intersection_points
        <
            IntersectionPointsReturnType
        > pts_policy;
    typedef policies::relate::segments_direction dir_policy;

public:
    struct return_type
    {
        typedef typename pts_policy::return_type intersection_points_type;
        typedef typename dir_policy::return_type direction_type;

        return_type(intersection_points_type const& pts_result,
                    direction_type const& dir_result)
            : intersection_points(pts_result)
            , direction(dir_result)
        {}

        intersection_points_type intersection_points;
        direction_type direction;
    };

    template <typename Segment1, typename Segment2, typename SegmentIntersectionInfo>
    static inline return_type segments_crosses(side_info const& sides,
                                        SegmentIntersectionInfo const& sinfo,
                                        Segment1 const& s1, Segment2 const& s2)
    {
        return return_type
            (
                pts_policy::segments_crosses(sides, sinfo, s1, s2),
                dir_policy::segments_crosses(sides, sinfo, s1, s2)
            );
    }

    template <typename Segment1, typename Segment2, typename Ratio>
    static inline return_type segments_collinear(
                                        Segment1 const& segment1,
                                        Segment2 const& segment2,
                                        bool opposite,
                                        int pa1, int pa2, int pb1, int pb2,
                                        Ratio const& ra1, Ratio const& ra2,
                                        Ratio const& rb1, Ratio const& rb2)
    {
        return return_type
            (
                pts_policy::segments_collinear(segment1, segment2,
                                               opposite,
                                               pa1, pa2, pb1, pb2,
                                               ra1, ra2, rb1, rb2),
                dir_policy::segments_collinear(segment1, segment2,
                                               opposite,
                                               pa1, pa2, pb1, pb2,
                                               ra1, ra2, rb1, rb2)
            );
    }

    template <typename Segment>
    static inline return_type degenerate(Segment const& segment,
                                         bool a_degenerate)
    {
        return return_type
            (
                pts_policy::degenerate(segment, a_degenerate),
                dir_policy::degenerate(segment, a_degenerate)
            );
    }

    template <typename Segment, typename Ratio>
    static inline return_type one_degenerate(Segment const& segment,
                                             Ratio const& ratio,
                                             bool a_degenerate)
    {
        return return_type
            (
                pts_policy::one_degenerate(segment, ratio, a_degenerate),
                dir_policy::one_degenerate(segment, ratio, a_degenerate)
            );
    }

    static inline return_type disjoint()
    {
        return return_type
            (
                pts_policy::disjoint(),
                dir_policy::disjoint()
            );
    }

    static inline return_type error(std::string const& msg)
    {
        return return_type
            (
                pts_policy::error(msg),
                dir_policy::error(msg)
            );
    }
};


}} // namespace policies::relate

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRY_POLICIES_RELATE_INTERSECTION_POLICY_HPP

/* intersection_policy.hpp
1+hbII1uynSDOfxwnn5jBAHF6td3wHXeOoLahuZ0bF5hWrJEPzWQckwEctssN2HICdr4eiK7GslnI4uZOotqRRAL0rxechubm8f//dg4/CsDj0+yogK19BiKY6rnGOuC2R5xc2l3LJ3NylU93UOCgueuG4fxvc5+V/AkhfdCAa7tWEvwMYZAweyQSvWrq2olRsvcPMTnC57B6N/gMa21yiRcR7aQ3qw7gf6BiELqdny5Fz9E7HHjHwcw9rgbsYiDg+4DSpY/ynC/lGnL84ASv4npO/uIYyfWF1lxtQ3VOk7N7/eLiGSoXV1eCA1g6fgWPKZHIZ+cCcO8MM+1i6ypdgFo6icVD0r/PNgIO8cy3Gn8xGJYs3Py1naGCAOVNp5anMdjv/pMGxq+KZDzgWKlk5uzMg5IVM35WVD+U0ao32OJ3RXZQ1NFnC6QiOhXQAz/A2vGUiPc7uNjoNgFUa+dUPCHQFWXCe8pKxyIJtpCcIxh8jiGxkdyuFaLgUWzujwDwREuz6AyNboqOwFvfCvm4LmJzbGa5piZTWQ/HGMqHYD3TJ5B9VF8FTdgMlxyJZsaeU9je+f5tBdDpAhdMpRRjDee79r9GTDuywgJ775LKFptm3HpKqwmCGtnlzaF+Lm1mYYahMXlDf9Fq6APxxEDvX38e38XUU38nW/GBbTT6Trnq5fwMywBLV58BpaAoVF9GAc36O5SRnDkMPk3Eu8bMlI553krLoFschqjDdOnwT0+D8SmaDPCPsFxbaHTCj6tPvXRPKl4HMpa8+sNV9MI6KHtA4k6Wr56DurASvnHzstaNUoBf18hQ+H1fvWsgZ3+uRibJ06LsYFjmzYIDI76ub4pUAwiX9jJlbr2iuK/eGRtQrZOLCKnxnpkjL8rbA/OEgwBMIBoIf8pnkQhLUoxhXAe+t0NlvA8OAWj5jZtSg2OPn/7cQrl9dj5tb1wyGEo0ehnLuFJqi7Pc4UHFZte/K4zaEA2QdkiOg9rmIo+NBb++O/g1PIMsJCFWVRYh2FrkxZ8oIZotvKfQgIaRcE1zzvPidi2uXmqN6+zEI9Pgy9KvAs/+cdLWi+BQ7ecGSUBjqVicxlryc4QbjQ+P//ud0lCfQx19jMyMKUGAu4F4VR3029b9Kt4wjdjtnlmbSOdGv+6eOn6OeKZ+sOkwJlsElI+1kMKcz+Z6jDkcP9S1GUJLGcRcliUBwRDXugmHTa2u7KzmLrBc6D9iKJOse9QOKNFcamfGBPEO7c1fYRJc4ryMIRyVp54vYyf/sMlHPcPh8M4lyH9n3PTCRO6xLyK89vwYNOJ0ENu+h5+QIgVbNqmSIMXpHjK3whb9p1qkcFRWwGinoU/9qXzWpF4pb5DZ3re/NSagupIYr83lO2mX2E7e46KNn+TFebmz8re1/vMp1f1yBWOi2iRhTOZr3+G+lUfx0DDs2kX7kZkQlG8Q9wpr209mgDd9IQt+ut4mq2oea2+SsdCXyIEgGBMaOG36qk4Yf1GsqDUhifhZGD7eMN3MGpPmR3ZZUHRPngjP3fpMwmRUpGG+mKfdEHDQ59/FL8pTIoNN0VqHdlpWokjN5YZMATSkx7WZhPYmp0cUY3RlZgNM1sk5Vovklo5xIn/4BP6ic+LfmtNDU1P8FGLgnQm8cOvUIudkXepjw138lkpLY4MpIdHBNKrYjael3LDmI6vR+F15HEipy5H2k1GwX4N5d/QVBjHAtsiBv6VpIFvjQ98pT9p6F9cDGyhZ2AEngYLFgCB6ENwpz+dxiA5fBGOx4YCIC4VbpqfcIkQ4dm0tmhxAkxfGQmcYSX/+3/qr83xAvPdhWxjG52j1UsabJTpayTIQ4P8A3gQoakyPkkZO8KN0Z7O43+H0yRx/OS03YoMu7IKdYUYMN7Yel6oGj3dGEc+ToJWdPu0FcBN8N3wdjTY3enpnvESLIA3j5sM/Nb6TMO+KyApMmDQBDX45aLhqcGcKewIuVtM8GkbuykpKzwk6IMkDHKgKnU69y/30L74/XB4HmXSPuvUvCBfwtjeURn9Gb5VDmP8EBLwmexRM8vZyeZ62XyL+xGvYkU55ncLl1QTIPcrd0PhJiC2hzCotXSQU/wO/F2Obevhvzhx5WoE8vLGRya0ub2NRL7hgab+0Az32wbYU+FpbN0gXIvM2GZQrnPT/XAuW4fh5Nq0bUhZ/uY6rxWLO/UHJDDvY/FaApa2T3fACXh8JZ6AQu3h7Pfi7sekiZ2eM+NwTfbb1mNKNPfbYjG+HleXRM3bWDZJUtHSPn7z7RaC0olcHhkeFS02+mratlSHYqMjl8eFJwDXWJMDR3LU0+fjP887p0X2W2O3R4v/Ehm4PjwxcP2Cly58Htn7+LxI+xQfPFPjgGfh7KUH7TBmBgzLh2HLIe4UmBcQfrdth+1GjS7WSs943X22DT5EYz8P3dnHaz7Wu1mD2J583cmEui8zWd135ppUTuXFe85pzvbOdOuox0Nq82FS+bxPn8fos5s+T9LnKfo8TZ+UKL2Z/Kaa++iTXLya0cUL48UH6ReaC9RmM33iwcY/GV6LiLXz66b8Q1rE03f/f21xfqqeMq6etOjqSWxH7+J7zmkJLcFM4ujOBpZVAbfXvC2uR4tSc30q5RVRKXlCJynbrqHfmEVMOx6ltvvwyxn9y6D4EmlBbZAWaaGkYim6B3ECCoVmUu4QWxOmREAbdhdZW39DCcsVZUxkF5ZhCuqgtK7ltYo1squdLpqc/cXce+EzjcwEhhEvCOOzXcRKFfr85LyHuaEDRqHO2X5YpAJD986tGvqfr1KUsaKSNAyHQPKjYPJdq2tVLVaPNaVB9f3FiAHFP+6n2uyJ2rL02kiSLREnbKVf1ncypb7o9jNCP5stwxIxbtBBAolXpYySGM/s4Er/Z0lBZHmyAFI7bSJfKhyb0a7t2OyUoRnHIu0C/nREZMAoBuh20eQsaPIrqQNE0XoYEuWX2q7tgynNHcbnIS4d/nnKP6qr7aLvXXFdbbVYZEO2jFS09HCp+fSzXaTY/VJnsXkcBQvH9S/t3R+g4mZW8Jbu30mFzcGeg7/d23Pw5Ogu+PXbDr5rBelm/i/yDnBGeEQAgENLpb0LeFTV1Td+khmSAQZmEgJEjTbqqGhQ0UAlDmoUJsZKcEJgAtYAKuI4RYs6g+EzCaSTAMeTAaxY7Vfq5S2obf0sVZRYFcOlJAgFRKqxgKWWtjtO1BAiBImc//qtfc7cgvr2+fM8TM5ln31Ze++1131J2Wz4rTbpbsyU/M1qBvN6ValpTGQaHT7F3nfvWZyufaTxaNx76clmftKKDchCwns4AZBdCQ6KuxOkRsVnuWhzolzUPCk55Z04NZZAOA57MBLeJYM0RcIHzYs+42JirtYVeatTTkxiWsYPsUfCGFrQbyyst3aZSZOfaOd0gZxNgt9ZntjFJYwFuU59guN+PHGYywkuwQjoiYP8nN9yb9QnGBmFgYZisxQYNPNMM3J+/xlpkTNyaYiOszZDWC4TyQWUE+10xEvsIcWzO4X9jIc802KS1HIzTeBYARo4GYW0xiPTctnIW32x4Uug9PBgcV+wWZ3ed4CYfw9+JcFBzzx9n5yk+092JAgCfxocRgM2Rh4YpHXNPtPIR7X/o/29TzbHxltEXwX6NBqkOZU8wmgGAEAgaGUQFHSl8Z7TuIylVQ0DpUeH1G/tY78z5rkTI3DGfazsUBvahK3gmB4PGXtuzKHByUfDtqT4aWcKgcByDBSrdLPaJHQbZDioq0TbhOe33RZIC/7gtuDQcim4QVy5mdGzZXKdAhmPzi5D1Vn4GQjIl4gxpz9f8q74Nlc+kH3c0kz0+pkWw8xst5jGGIMRWXviBgvXBZXg6DB3SwldKAtz4G9uOJiFEGy7RYFs/KG0mNVWvzGPG83Wi2AqYASxrM+MkRaEVfzNnIGxU/ZHPmZLjiv5+a6k5wHLjOhIel7felA+r9Q/lKyFpbT/0Bna6yW0sVDrpiQS/aFiolC1FZ3sB9HDYWRRqOB9dbrtgMeG9WmTn+Oule7o7ycnPzkpdj44jFZPNEPjWhOlc/Xb2KwzPTgw3Gvh0VloKMlWlXXVCt7M2ipXApUODU2c0WgW7ELPSZxygrTY+jXDeRDTbcWzEkPtlEAIOBYuwFdyyDe6uzghYOpGr4zWQhTkwlJ/VmIAZDPIjaFBmvRTQhubtTKb6mlTy3ZJJZK3WqvKL6jKjSl+1OnbtOk5lunOcrW0GhqkvessBy6taveq0/eaGqRdMQ3S3mQNEtcCNU/B1nWqZ4PmabZ4Wowz2dOMI9nTIj79InYi66G2SGiDHtoFlGIeyWY9h2U9WpmwSCQXFvT9YfOmJT2gq5Auw47MVKgupbp9Pp954IcMtVgbbfJd4FvXGJqmkmpDwTT5pW5dvP1AXMFEPINjN/EMv7kf8nEsazqyHp5UKS4oBr9stbSkZSJbQplNfBjtZk4Ppt7VPVfXXRy4CuQ/Xv19wjHE2uQodmIAtWGQ9IdexCWKK8FzOOWYLRLqFL5eeqwxoUlMx/I05C9F8VdQvFVYHkgRLEsT1Ya+hLAHoGLjYQ96+4U9ABKLB145qtVNQiACiDHEofcsSnitCy7hSqTEKuPeeqlp/RErh5z5/LNuvfDAxOVruAwc2ni842i8iF8gg9S4j3GElZztDeyUmC6GUg3xT3Iwnk9e6NaNz5VgXmAgt1T+G/mQlhHuvcL9fDfjYXUN5w03oqPKWA6FLUXLmpgCqZ/sKoZxEhy354e353orvAgpMBbhGsSiPRbZT2r0Pmo03MT90Dn4wg1/sSDtMkMkyXW/V7ru695vc91P1io/OKmycB/kgOiQY/UW9RdNifHmid1ndAsvCO1caAhMjcHCfP0D2u1XP5il+NMG8CPasx+wkth0Jqf/uXAaZyMVr+lXLm4cm6hCnu5NUSH7/Cw5f3R3r651wRIui9pZc/43emvGhqw7WeQM5CQZwx67yRg2O4fEeURaN8TCHxU/ebqPPhs79M7qQj3yDJzxVbf6qFV91KY+alc3uZwc14t/R/PvGKehd4ysKOUHY/l3PP9O4N9imK20j7TRpZcf3MG/M/h3Gv2+OWf4XdXqisl4sGIOP57Lvwv4dz7/+vm3mn8b+HcJ/9agAtaNrghyBcv5cRP/Ps2/q/l3Fb9dw9fP8e/L/PsS/66FidjS9fSLKJrqprf5aQv/NvPvBv5lU7KlbU7JzIVXOKE9qtDOBaGhbrLj7oPIUsDJiwtAw6tumsTPmW7+r8T/AWvzDTnLqsWg+yDMUGu7WjMxN62ePmSpFuMzaPNuXM/WbRz8c8qfLUpkGcYobj73Gz2yDMAQE/gS0BFX4XIlYMyK4Q+rbEpk5WSnER6ulW61ZZhHaGUuoj3Kkok9IveXfbp48L6YIqQ9YemAUq+HMM+nddX/W9EVpf608jOilkKDL1rcpesqv6zqSHuuT0/MOAZTZJaviYFM49tjwrVyB51cj/mhDYc6Szup7a7/h65LZWQmh8CGHVrhATZ1qDqsVh1Rq4Ra1WnoWMoOqs8iv7r428Zs5beKYlWCGfW7gSz9h4dAXNPuffOliVq1uGPhCZ14tZxI2WE9dJCKUNlyn1rVpykVXgybzlmt/cSBsw9ICU07UMvQ/+nWT28NTdBCB/3tf2XR97ul1FdI5QYF0irFlTec0KO5/m2DaULWlbJQ3EHPqdz2N3uRQY3VUhNofKZFXMDf7HuKzp9f3CstAE5WRsqa1NDLYsKCbBqm1kpdEm90n8Dx0iT2zYlHJ/e8xMHJvW12Opg3ePXQan34jGxYT29QPeuLnsWir5veeKD6oJuva/dry7A1EFt8DLLbNpWb6W61DI4r7A3Kx5Gy5zjx7QzNs7a4yLN+sYUqnChrqXlFC70M5QA2X10VshYsgjKE7x2R+6EMWVb9/6sZ1FTzAjWjh17CoA/NzlaSTRECubefyRrhB3Gro4ND9t5KTIg0PBKA7V7T2mi9e29durZFBrhuas3gpM4lVnHrTxH4Sjw7L0X5JaWzRxt1AvY/t9sl7/qVETh5jWHUxodUZWQp77TFCBkFjQ92l/6gTaRhc+0WFw6XBKZd6ScUbTxOtTfGa5eyX6N2n3/9MEjC0IZ4sCQe78Bv+On7jN2eYTTMuxwNL7+DGt4jfpeT0rCvkjVmhISK22hd6jPdrcFBlVqbmJWLUOIJgzPH9Ptd0HdiQKycRuUFVDmrIG/NUfrBK1M7mlpHKwOJ1VdV/Ws79GObUlm/HRhNTNx7Bj05EfjQQrYQMvT0FS3j9XdVZCVj/jIbcbHLVfAzN9ocEUQe0R60anlLiypKgyXFUOryBzXtWLq8My6JbATMOPXBLFutF8ZB9qeLyksdDa9wzgy53P8u0zgg8+YyHAPRIZFSWMPnF50VzNCgxfoStmISFbtLrERA2tQp1qhdbNxmR4Q0zalmuUtstLVLreoUW9Sm2TSvVS23alOcqk2fYldLnDT3K9+1KO5nXRaO3v0i/tLtKOMWf5W4pL22jxaNOG8k52TsqML2W5n85crkL2V6Re1U9L2EbBSFxyuLXpNQhEic9TOvyV3M+pkwdrFmX5+QoLFEFqjZE3kNYC/URdnObziRBYP00sbj1TPcfE3wDDed6XsG6keR15bL74fQ9wG9MqJhLQjXDJvCd1i/YgTdER+488cdn2XR7b1b4wrEmnjCiPpVyckj6NRobKke5uYytYM1lYdhrQfmTV5RsZKrjJJN31rycVTmY5uJSiOb8XT3ltpy7U2ufcKyokdKg2M5m7H2OKpDzkUudgUVu0x7syle7HwuZuYwpNcJfYyKetqk9OyE7E30s+8xb6W/NiP1LNKxh9H24rPZ0cswGz2/xKRukbCdelTj5lK1QU3jXo2tN308U8NoBLN1mR/eLj+peSe6rrAFAlHwEao0cM2XIY8ejic/gijXpfXCQBYGgJtPrVPZ0d0PZcbzm5N1QolG3HW/NC11QEPH/W3McEezvj9Ik/axSF+fLRMnRF4DEZtk+RtaKC1813Gn4Vb1i7uy2b0CUZliyaC1nRi8eP/VPuZUWCjRkhUtjrwG6i6xinVi+pkqQB5mbadYRRUEHDOicHidUpyVoLPVJvU3BmULcTtbiI+hub2oi+ip65Qu2sjn+8TV80+wumeEhJU/Oyn1USadLp/fkKXMOlOcznOeaozzjU8nhctb1Y9vfCkWLi8iXyN3Irvgvu1ivuxt1xr55zn5Zy27bfHUb+BXBRtcq6UfJscWLXZvrx0cu4kO1RpkqQYuVaGGMWJR8ZMTfAgN4zHNOUtGoVXfwkuINl8BNQdLMuMZQsBWi9x76cjeSp1g849VHSeYJa0Wv69kMonj6Ek+kkPpXfQuYeQGHkYBNytFyKp8xE58YUm+f6jxe9idvCq9WqntgibusqWJB+DeXJOubSYuEt9GNjCsIm9hxdHasGwOvwXCX1mnasxJhfOcCI0SOF/CAba1SiScw41Je0CzBpesIXD+OiPhjAY+q6BN1UYxygycrozIDscMc7E3S2VoCUcT0jxGHWbdH0b3aMaLb07TOcFlHZGjsA3RJDVYz2TaZFcQ4Q6DrtEmrcaPOMubJNIQ/422vFsuC0fT7yFEl7ywTMfOO7dLmkhf
*/