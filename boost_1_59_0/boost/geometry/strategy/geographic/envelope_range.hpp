// Boost.Geometry

// Copyright (c) 2021-2022, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_ENVELOPE_RANGE_HPP
#define BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_ENVELOPE_RANGE_HPP

#include <boost/geometry/strategy/geographic/envelope_segment.hpp>
#include <boost/geometry/strategy/geographic/expand_segment.hpp>
#include <boost/geometry/strategy/spherical/envelope_range.hpp>

// Get rid of this dependency?
#include <boost/geometry/strategies/spherical/point_in_poly_winding.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace envelope
{

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = geometry::srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_linestring
{
public:
    using model_type = Spheroid;

    geographic_linestring()
        : m_spheroid()
    {}

    explicit geographic_linestring(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename Range, typename Box>
    void apply(Range const& range, Box& mbr) const
    {
        auto const envelope_s = envelope::geographic_segment
            <
                FormulaPolicy, Spheroid, CalculationType
            >(m_spheroid);
        auto const expand_s = expand::geographic_segment
            <
                FormulaPolicy, Spheroid, CalculationType
            >(m_spheroid);
        detail::spheroidal_linestring(range, mbr, envelope_s, expand_s);
    }

    Spheroid model() const
    {
        return m_spheroid;
    }

private:
    Spheroid m_spheroid;
};

template
<
    typename FormulaPolicy = strategy::andoyer,
    typename Spheroid = geometry::srs::spheroid<double>,
    typename CalculationType = void
>
class geographic_ring
{
public:
    using model_type = Spheroid;

    geographic_ring()
        : m_spheroid()
    {}

    explicit geographic_ring(Spheroid const& spheroid)
        : m_spheroid(spheroid)
    {}

    template <typename Range, typename Box>
    void apply(Range const& range, Box& mbr) const
    {
        auto const envelope_s = envelope::geographic_segment
            <
                FormulaPolicy, Spheroid, CalculationType
            >(m_spheroid);
        auto const expand_s = expand::geographic_segment
            <
                FormulaPolicy, Spheroid, CalculationType
            >(m_spheroid);
        auto const within_s = within::detail::spherical_winding_base
            <
                envelope::detail::side_of_pole<CalculationType>, CalculationType
            >();
        detail::spheroidal_ring(range, mbr, envelope_s, expand_s, within_s);
    }

    Spheroid model() const
    {
        return m_spheroid;
    }

private:
    Spheroid m_spheroid;
};

}} // namespace strategy::envelope

}} //namepsace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGY_GEOGRAPHIC_ENVELOPE_RANGE_HPP

/* envelope_range.hpp
9YgQKYzDWBLkIZ5tIv7xYYJ/4M3H9FixLrXYs5hEl6/T3de3WRWn389uywnNHLstGHTCtPWg5ZQ6k4FuKARwWXMUHCQvgA/4tXQTnzAlaQmE7Sbi702FwuVULRjeFHYeXA8vEaHixe4+/NzPRD//eU9cbpbwXw+BWFOGUFmuo0QlBvpHJkq0IGigRCenDXbmtQs/qmR6pgyIWWlPcKnecQi0h6zros08OY/ES3P1TFnaVtPHkDBBfhW5eAeuyPYi2olL+dIQ+h0Hz4/5AW/41ZgfsGn9rMTmjNafc4EVj4rXmYIWpBN3He5xqU53HR72VG3uOifeYDSJ3eX01DfgvUll7mXzlTXR3dvweHPqEkpeBTItEF3mHHfhkzKHv/rXYUF3FjjFfvzKQPQBp3GfAEdVFB0RtJ+YoPPiv2ekRMfih0Bq5puCbBiaug+aCsqmXsamtEOJpmypTaW428v6KpvNicff/NZ8cVahHcRj3ibjPl9LaTC6D0dsHL4zzuKQcxHFUNxcs0U7uBBrKPilgHvYPnQAhbJFNgZ7WFo8A9W3MbYKY3S9A9p34mmsNf+Q7gNU9eNBwoOb0sgD1ig0BXvZNKJrVXT3zyb6fRzPZHyBLZAB1YDLk1ENc+AhNgWbS7zK03/4Nb2zbHU8f/VAJXlD8zvQeRFlPVgIDIKP38aQBePywQ//mpE8DihPO/xpQuKzXzjx5ch6wJqNQ6WUiyLs21sbZMxxiTyRMHYr9QErYWIC3S+B/usUSWu4R4iyHCDHbkIdqnkpEpZFD48G8JxDPcbMc0fdOUFveybiaXN4M6plu5uJILPczUiQKn0DIa2gJTTDH8o2Kj9Ve06sM9q99n+rl+UPZcVm/W+lpvtDLgOYJbX/KzBBYJfR+l2gpvBsKJ086kc4QTU2BZUu1B4Su3oNL1JmQi6Pd04wFa8LZ6fEzVENse/X8YumxoWMNq1D9F2NdsthNyPgLnczuwSSEXBZeC3G5h+ZTX3EVrQnUQB5Wh07UVv1aPhFIEd0FwlH2hebvx0sBLHJGt3sFPPGXfBnHEHZJNuItNSsNe7MWM2Z2s8mRhfN8xwPL80/5vhtC1jld1gdvx3M9w381PHbw/mvW469Gfd0hK+VlWOXRVqqrpK9hy81erZv17bMN6nB4i1/M0ot59XPggWkciCfg/jFo5pbIqLqQ89BqgelqJ61Sauab1KmAZa0Fqe4eey6ysuXeaha9WFAU/K6/H+9J30JrD0WuyCkaR/gCQTMxZkgsHaMuNfrNspt4oT3L1n73f9b7VyxH8eU2oZcb3njWpP3s8yWR3y2pa6jpJdq1VNmo2oPuQCVzPZl6PVIvUyedoZc14Jl9evG0aREuGzP53aGbGMX29+Xp28nELcjach7lowQp/9AyTpqS3yK6pe/w2se2jNmQQd6M/GrZoV+iYM1V9PvNvqtpd8d9LuTfhvodxf9Pk6/T9Dvk/S7h36fo98X6Hcv/b5Iv030+yr9ttAv3ZfW3EG/R5GR1iNW6EtYnZR4gn676LebrjPox2MuWGrPbdOcknmQuT6onRMHq9Fy3I1pcuHTN5K6IUffja/R+rNTKNHC2ykRX6P1Sy+hRCv/b0rEV8kJIDGd/0Ijj0E9n43RC8QgvvE08NvLkXVr9Yh0Ea2Ti7uZvuzVbCV4bfRrp18n/ebQby79orgSb0frniQ5AA+bZAtEYc0b6Xc9/W6g30r6JYn0Nhgret0sIkVUMPW6OfQ8SiSKvCpat1e2lke15tIvuVOaF9LvIvpdSr+F9FtMv/fQL5IwgtSSgK1TPujNfspfjvR/iG/LREVsO44ZNLtCiuWgL43GhZr+1Kq38f4kCumQCWveTlyoxB5+URqUTKdPlTgT35UwvmhBH68CHmVjdf2oJtG+NSPJBH/s8o9V/kHojVa3Y6AwHewJiaEu9L3JKzDlJytmJQuWSsEsj9KLk8jHT2qvYTyEOfoyTiSsVcUCChVK+PFxA2Da/67BkP0pJ2s0mk6TOhuBJ1WjOUXVyNKapaphS9y0w+oGaFwwijQ5JvnHJv845R8kgrYoLWg8i61VWU3qNKbvlZZCZgn/+QPDAj8KBYv8b7jIZ6Qn1Wdc3ZJmQWZnoAlqvue6aU6++LPzIoW4F/zwnEhZANfSa3KRzKDX5EKy0WtyxQ1vx1dciuTXOXU2njhf8h+gpfGvpycu7YrSHjqAPImM0HRe+0ZcSOD4b0YBHnLe+HnaVnzupufBmvN0QunbtRdV+ErxO6Yv90MLsRVis43dzJ8b+h/2rO43TqSxZXmhNIzZl0kNdOcEamcw/2NSZ31kUP0vPFZtx2PVDbgq6EOo81lRHnom7SXy4CdWd7zshf999tYe56RWJLdKCy7PxLeI5Q1giZOXbY+YxxTk2V0pCvKF35k5U3AaCc29G5etujBBUhjrYWxbjDtYR4MTC2phdVE2Bhnyd+SNn0BrBX8qXMdffjdj7Ls2uO4KrdjRAVxDqE88uJx2YvFk4OKnUKn44dP4+DQ+1pXi4zP0uBMfG+kR95MXP0uPm/HxOXq8npzP2FhkAy0DYo+OWrxXIjTlwqueRw0uUGjT+JWO2noT3Qz8AabWPUnWFPKWaJXZ0uEZDodY+0+HiMOiAGV/DshvKqPRwuow2UKV8Irrd2KL6WBDex3evYwrUTQ4k0IbFxvox10duP/ypCl5LhKStWfpsmaMeT98IRjVZuGJg+X3P0ERvctDw936l9hri7GZ721YnAZ/NucsRrrYvHJxOv6ZmD78GVi0cfMDtzEidrYYqeVgplV+e4AuOJ1EGwF0NOddRsvj4lk+2/YtVgupjNE6XNXGx+HdZkftLfLmGf6dR8ym1JtvcW+TLbHC/HuIDYUxrmwlfWMmqab5PPS5ybCX1Y1X0+4nNa1gbMHMXOZplmpayn7aZWeHhNEltP1v/r0nkuf78eMjeGpafuYHkR1kizFsQllhyMCkLbr4Sm/8Su8oHbZ+l36hh7fRxKCC485WT7kgCCb2VUMGJlv7yv/c2t4LW5uukQw0P4VtKulP4Y6lP/Y0IPPnnwyJ1A9Da/3zxy1eujIWpaSjtgWJBk/Tqt3JLX7D4JsWpbsy/fLGG/EIXiusUzUZfOBWbeo9iVt81X7g6Lp6VlcTG74aAgcUpE5iGilP3rOxyVo8TZ3AtKP0HsdvctCVN0fJTDXmRQPoo76jJQGxoPMTwFbCAVNhmKoSKnFyextK/AB+hE+q3Zvfzkj9MNacC+4WQhVfDvptHDRdUUvmR9Rrb8RBAASLxkHulXv0Mnalk3ntb57DEBnsNjofg1RgwJ7XwxP11f2WN/XVZ2PrmYZqoGegZiXeotOKN+gU45iXGDv/iZacsqUTiZYAdXHZ0gC2FI9NZVq3bMmGlwq10r2bUbp0P2ic6WrACTHcl32ONDx+mEfD+ycNbxOxEtyE0VYRL8lnqBTke+1a6wgYSmmslS2mUyPZulYpJwQWaweYXJbDno6ajFC2eNfSIvNknNMJatLj7ar5EvN1SdNNa+1v1H0gzs7KMqiuFfoT8RKo2eBZEkPE4eENGAbBFg13Jz4ShHWoSndKle6xKvRAR7qoC8R/geij/ZEFq1BEnvRz38AQhtlH6INDVEzaLo5a5P/ug8UkPH5G5H7WnwhNyKMLq5fTph0GwOE5a188tBRFsy8uHS2AQuyg/2PsQJ0jm8KrAc7ytlsyTWsBH+GpeE/KS8abYyd6dFN2F38HVUEGgxxebW/9q3PSH/GL72LBiVTqxkPV7oPIa9Sb+cCxYeOOG+Nb4xPal1SjhIhd6j6I+pcylR9NlkFvjL6kGgX5EUOQD/0kRZCXdyYEOfkhRTbiDPgfQJV/aKjrMnLLLJMIw/u1lVmeERjfGKc889GQCMBy7EoFGPjMLT8zmyiK/ccjQlS4dyP5KS59Nyng9Fa+TlyDvKJ8ndSyuBssToOlKiVaMyreQi0OygiqiFCytK1W/ObHcW49mPAXzZUs8p5OGcjw8Cvx/+E4EEVeknYeNAQofuHnWkPxVS4nIxQVoxfxO095+LkmkxMDG7a+hgyzrRLDDJpsZRj/dS7DJJ1KVlpTRagbWCRBsI6n7vnhDKe8xrMjGhnFww+h9Xo9CiqxwHYCWfyaN6GL9VHvrqCfr3kzw/SjCH6CYYf314zK043/uyp33Q72oXev/5D3v9JF9nNvg8iJRnvxKMF9L8cF2JhssQLDju7G0Dp2hH98AHejd4FwwAucHjyAgVuyfCVgJRE7EInjIYdWJH78gn00skbQUZJ+PNiQrQBk4iUsYlS9AaqmjIhKS6lbk6OFd5nC6cK7K2YRvl345ogokB+l0NJ27x60lPmaMbBkBu9vMs53yS6G9sdFzM0djw0J6dpSZrM6XKqe9q30jZ5osTzJrrVYgfcAb9IJgFg6vywMevqx4YyLhoitphCxU/pqHnnLsQPjmjyPPkEOpw7ypaIxC7P3O1rg6AqQTDBy2FH/CyosvVM/xnzp65nfoB1yJi/Fd+8jZ98XmLffo2H9cLZkbFJeO2qDWHM1L10J0+HeYjb1IaG495GDZpV7Hzlolrv3kaNsKSP3Glvd7+kMZ+V3mh9FO7rvI+yWvLHMe9ZzyFGPZ3tYPP+cZ9jx0BBk5h8ya1SSPvfu6/fQGKodIJ08NCiH/AY5e4IGiH6PK9Xe/KxNMKUgzm+PvFVVwAbwE3GOnS+QNtubcMv9QqqIVTn5VU7tkDV/2BzmwtvrXt1bc1x7Bjs1ac+giWeKvFVTzAgF+TQKt5fX3MIOYh6oYmsMj5k/gcUmVpSTX+TMb5WgX+fly3Qq7DlX3ST589GkXEGGPuYlStzAjQpSJu9+BCN+krzskSMpMr5EfqPh9cPDGOpEF/cmWNatH4KlNdNfibsSnLXjLji04Sc//5grv1E8itYF6UrJD8+C1ca/i00+kMe6Eu191AftFRjteag9PzHcoOFhpaifipTNErqKjtWh+YcBA/IeBLxPAOc7gLf+xdkaG7OBnMF7B94jlzW6XZQsN7k75Aft0wpa3OEcR2Qn1U5o0CkfafN0KfcbPul0d3hUvRv3wJsND2Gz4SEk347igHxlIquTeoCzOORKxvTgvaPZNtTqLl6Vmr6E+ZwWX67ZZ4tNDrmC+I9RK2TGJ2TGAcmKYSrc4bgjMh14xTq88jfHxKc8TAq2tB7x8HIJrpXyPEctSlT37hzitIvombhuBIPYg+7dBNFi926CaIF7N62mGwAxu5G2pLXv+GWLn+ceBP6yG3GhbmHkB/XUoX8q9k1ZyL0bqVSdEOCfvAIiLbYG20CqpNrvvYJHHrFEMWgSO/cjxuvkOsFr1Y2G84wLkuzb2e05nnpcETU2N7lbq2lOcJc+2owOCby+75UERMqXjIFkGwPJMgaSsmPA6tCWl4ciXFpLFoq7ufecE2w/eRFmshobuxmEM94Ut1wqDZMCgdDMoBTJnk/Vv1TgV7D+86GEKUOfEMfz78P4VVO9DvGK34Wxwht+vCYdP4FL/mS9qFr/MQKmDWcoE7ThTCUxGrwXDyHl9R8kjkjioXvIGf/B4VkfDIkxtzHu8EwEWmwvJNcx+XldTd5yEK6uT1G4JoK7H/2ATpL18KzfxSlIwrBr1MmsDg2HfHLxxeys7ii9oT/2pyFT/ush05vxQj8sQzvU9lMYm7fKCC+G5qZCc3w7dAVLW9yXVGYQSvzsbKX93DS87dDfFif/VMpHVs9oQoDZQoYyPCorwU4HjeIF5MtdkdPKbdKGxss0KbTXSZqmQseefpDs6OA/hkTIFKy8Ki31bpwjPP3AhaG0Ka6VQa8NjV55n0ggZC2NUmBIgGd857xgloLDnlZHLd7m7y7OkxfmBbFQM9roQdTDfQO4A+iL83fugQq4F+7StoBFPlmq4XgZwGPTz4ukIf1/ePse8Ciqs9/dbBIWWNgFggQBDZoquLaiAXW7oEFZiH/WblizC2LAqti4/SOtM4iaDcRJAtPDxlhQsY1RK7T2k1ZaULFBDMIlUVIISCVCPqWWr066+dqgNFkEM/d933Nmdjbg1+c+9z7X5zHszJw5c/6+5/37e28k6s0F6ZCy87iNNApCnpZylPd0oDIl2fqyKfh6KRse0crgfUOg3sUnHO0ISxaR7a+oZbHW87+487J2UcISjj/pZK6tInsKQvSwcx1o+xHV4tDJXEs4/nvJtK15F+sfnPA5Q8BDYjwDJWM0lnxkWjIRuwROlFalwNCxiHiSSSf69e67iUnA1YYCPs4Pl4hR56ZwgdtFlbhrfpPJ0n/8137CkgKuuF1wxUdAUKBkRFvxPItwbyrKz7QsYgr4S6kxoUGNacDaSK5lqcRW/DA66oBspBW+igEP5+gLDQkdfgt52JDQu1cPEoCkixAFxEUSI/LBfrJ8yU5kIJ1f6bpVbHh4NXDnJN/Y5JvSr5kKxm9ZFIwPf62C0Z7FFYxHTINY126LKlFoDzmNRxgKT/dE4qI8/g9EwsZbCxJkPrEgNvvb3LWf2yzaui9wE0w6/jkCwn1m6se42oyrxNSgB+n4mxY6/ir+fTPuAknMueszz/Av2TN8qT/hW3A9m4QroDXnuICGk6asijuzpVz4myNPjNm0F4+gk6wLaA9IyZ7SijwP39kfwBXudIokpeugR/kGVoOgkDF4K2YPxbL0N2yU6mjzhyQ9lX6h6xYha+1fiFzoM9rEevogOUb7WO3X55u4KwuTQmMlwleK3vPV46Epj1TrySRTT4bD3T7SBcpOtZ4Ov09ZHZpn2DNYJgyyFp3/85yOIf5d8SyEysJivno6nS7x1dPpdKGvnk6n0f6D8eyiY8ksdtTfWZnN2pK5/oOVWex9/kn/QeliPvJInM+LmQN0Yf/i7uyUwGVUehYMVkb5P3bXLM2BJjwMNO3uHFy/3LyiBraltQpqQDCOL5I1ejZw1yiIZ/t3Vbl8W9F4IQ3175Vz1OCWpEOVt0QxZynppnaocosq71HlNqFlJw1PiXRVieTm+1zsqOT1ieYtpFXZQU5hP2zLZYG2YlVB22ByAtzmz/nDPbksuGe2yugNztqn6M2YbVNswEiiXIQABSz60/s3vlmNp3zNnMNBI4424h0U3wkZFUR4igjrTQReCWlzJp/V2UhmKzqUqLRnw5u+dbRRxiXmZbH4NqX1rD8Vz4H7yRzgeAObGTsFnfGtI9bR6VuHrKNkv8W3bg7/wQJbEo843K+dJADsjtZACnHoL90LLMchXrW75r9wD8jbfeuwafJkZcBeNRxG2LvfFNtDdCA6FIDh2raNqW3btm3btm27ndq2NbVt2359i+8kq+ySc/9FZBlD4qkDN5SRaBOT6vpmh3A7cmowv1x2jajVrE+MBPxckOS9odDtXId69366LJ0N/zF3TkCDPru/pJKEZapR0lXMgqP+7a6a1loOLP2hqxQdkFeUUKjy4CF3KOoKmCbp4oWaXEswDJjuyDbsx+3oInX4WHLNl8wq2pIj7N/lwWFpE7sW8LmtHqxIxMuW3LmrRua+4+xHriXOdcfBN1rj4aPEIW9TYrLrDtKMu8on9C/Nv65Nax7gmwsCBldq7O6egygFeENGCBR+iDruiDKxQYoE80QmG9koTcyTs9Fbcg7+2sYGapiJ
*/