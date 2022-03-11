// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2015 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_DETAIL_OPTIONAL_RELOPS_AJK_03OCT2015_HPP
#define BOOST_OPTIONAL_DETAIL_OPTIONAL_RELOPS_AJK_03OCT2015_HPP

namespace boost {

// optional's relational operators ( ==, !=, <, >, <=, >= ) have deep-semantics (compare values).
// WARNING: This is UNLIKE pointers. Use equal_pointees()/less_pointess() in generic code instead.


//
// optional<T> vs optional<T> cases
//

template<class T>
inline
bool operator == ( optional<T> const& x, optional<T> const& y )
{ return bool(x) && bool(y) ? *x == *y : bool(x) == bool(y); }

template<class T>
inline
bool operator < ( optional<T> const& x, optional<T> const& y )
{ return less_pointees(x,y); }

template<class T>
inline
bool operator != ( optional<T> const& x, optional<T> const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( optional<T> const& x, optional<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional<T> const& x, optional<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional<T> const& x, optional<T> const& y )
{ return !( x < y ) ; }


//
// optional<T> vs T cases
//
template<class T>
inline
bool operator == ( optional<T> const& x, T const& y )
{ return equal_pointees(x, optional<T>(y)); }

template<class T>
inline
bool operator < ( optional<T> const& x, T const& y )
{ return less_pointees(x, optional<T>(y)); }

template<class T>
inline
bool operator != ( optional<T> const& x, T const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( optional<T> const& x, T const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional<T> const& x, T const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional<T> const& x, T const& y )
{ return !( x < y ) ; }

//
// T vs optional<T> cases
//

template<class T>
inline
bool operator == ( T const& x, optional<T> const& y )
{ return equal_pointees( optional<T>(x), y ); }

template<class T>
inline
bool operator < ( T const& x, optional<T> const& y )
{ return less_pointees( optional<T>(x), y ); }

template<class T>
inline
bool operator != ( T const& x, optional<T> const& y )
{ return !( x == y ) ; }

template<class T>
inline
bool operator > ( T const& x, optional<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( T const& x, optional<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( T const& x, optional<T> const& y )
{ return !( x < y ) ; }


//
// optional<T> vs none cases
//

template<class T>
inline
bool operator == ( optional<T> const& x, none_t ) BOOST_NOEXCEPT
{ return !x; }

template<class T>
inline
bool operator < ( optional<T> const& x, none_t )
{ return less_pointees(x,optional<T>() ); }

template<class T>
inline
bool operator != ( optional<T> const& x, none_t ) BOOST_NOEXCEPT
{ return bool(x); }

template<class T>
inline
bool operator > ( optional<T> const& x, none_t y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( optional<T> const& x, none_t y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( optional<T> const& x, none_t y )
{ return !( x < y ) ; }

//
// none vs optional<T> cases
//

template<class T>
inline
bool operator == ( none_t , optional<T> const& y ) BOOST_NOEXCEPT
{ return !y; }

template<class T>
inline
bool operator < ( none_t , optional<T> const& y )
{ return less_pointees(optional<T>() ,y); }

template<class T>
inline
bool operator != ( none_t, optional<T> const& y ) BOOST_NOEXCEPT
{ return bool(y); }

template<class T>
inline
bool operator > ( none_t x, optional<T> const& y )
{ return y < x ; }

template<class T>
inline
bool operator <= ( none_t x, optional<T> const& y )
{ return !( y < x ) ; }

template<class T>
inline
bool operator >= ( none_t x, optional<T> const& y )
{ return !( x < y ) ; }

} // namespace boost

#endif // header guard


/* optional_relops.hpp
GA/drJcKH4f3enhCNXjpeH8c+ufdDT6DnkUFXnNli+GyvutsAYSvp+5XJQuvJQ47ZttBbpjYb2ldWInfd20RDgmLSRMvuAQfKGiH7zKEDUsvZ2Yk3BHGd04WdmGOk8zJtqLAwaLO8Kf5llrUYIFCFhyZzisPphjBRRhZpyaWUlLAC+Rjku70Wpj1DkDAGdGhKMox8RrAXR8TZP5wSFbDP4hEdqOw4viUgTwooOXEiY3ORctt6M3w5EMM9Z2gsFVHqJYLfrSp+EAnHGXtkv5qyuVXeyUs5zsIG7lOabOOVGUWtsRPlucjkrMbu0A+zyawzVtw61TmDLOG+9mnT4vntpH7NWEEisV8JZL7dHhoob1AsH1WuQ7M1XYKPEItd0GxeHrbEbwNYPNdV8/VRqhkd6Ble4t7sFl1go4ZRjQSQ5ezJNJ8MT1cI1x7phx1QH2yPvFMpfGV5sq/zK4XrdM2Fo/HM8cJjp4BuNCd25vLoyePSzect+nfc4AHhTil2DqQ5LXP15mQOJPgCVHdZ7Rfc3zu8S7FNbS+5H8hSTlPLoWxGIdLkFsvkT5A3RMxeV9HqSgQRNk7q+zEcX1bdh/K2066+DOtklL13DTdUThht9wzylWJIuyv5lb2vup7wT6VBW9ECRVp6oH67uQ++g3sXocvuc5dnA4j3vLHATfoaNg6jQx+HI4l8gfFXmq/DkKjLtU8fYspAsw9oIjuH+Ucz96CPBbkfnAYZP3B+vkGWhnfbcP+Xn9jrJqbSkwuABGshzaUZjrFT2apgQGIWMtQowKk4YeQm/svw9DQOgq5x63mjpOs32dMx79DMzD+5HyeSefnmapcVG/7bgduWQkQWdPY/OIX8FHz6J7g4A0lmWKbtmpVpmJDM+tvtFfLfhUW6oTAzTOSFlVV5g7lGeAk7icWzCV9ymuy53gNUjp4+MgE+ui7A/r5rTvv6fzf3fPEm0iQUnbUd8exy9KroPqr15u7u6IfFuY0cczPcJ3ZfQf+cdo+MG4XItcT+AALPoWWZ+Ku+s1tKqhIyrJYi3PZL0CNc0BSF1e7FNBwHbK6bbhpOe5Z9jPD0Z4HR37j45DDVpyb0xOEVOMu+mqV6mzz22YPBWhI+Bi2Bv+kUWiW8DPYIlHN9byprskr0O2SV6rHH8GQ+hVHoUYUYtjG/pPXY18GVc3poHSHWv5SkyK+TKhsw5APEmvGwaN6E7rj52EcPBVHrc4xXV87hbCyb3v8pr0FULyeehWOjY1dKal1WIDcfcqrQaKh62lLAT5rg9kSGcxWeWxba44fT5cW218nng3TX1N9haagCIljV0OG1P57Uvn+0biRb7fJAx6klFDLy7YceLxJ4H01/3GKT5u7A7biennbRuui2NNWrKs4FnAp5i9GjcMCLTDw7oO0n7Kn108R2GzCNdBQZGOxSch+6/yoYI61x3zX7wx8YN/2IHJ+ZDeCNHi//kxDaqRpKJestAje2dT47JZtSPjys01zydvQG0RkJbbDvPDTfzN15/qWaiTWqW+jtS5pW+nX40s5btx8v1GofsOgyHxuGEXGpqIz9gmyLN3ws/1+Hla93jnl1aHk4rUWtO6gkSy8lmhVnHLkstv+6O03b8whc++LjQvFMnX/hQIdDAN0n67GPHMN6ZNj3/q/eO19YKsd1KM4fN56vpBXeiMOAUPFXQCu/8PSd8cl2f3vo2bUY0plZebAsrLpyMwNlpWVpY2ntBw4MjNzb2VoZloOKsuttNVy5l7gStxoDty4cYKIsuH++Xy+P178fb/O+1zX+7quc27O4Wx4HbAm9ohP+Ij/9+tR6vbHgW7NTrgqWIZE97E4umyL5F+Oa8Hhd2MfyieMF+W7zP3oEQwmJA4KqsE89Se99ofQr3877VxcSH3em3QuyQTtpfKP8kyCPlXCjTacOK8+e/DcRaiDNVzU3v6TIrdJdRWnfRsn+rKqJos3WGq56cKj8dv5+/twj58KE1FKPEyPap6ruNtKTSCCZKzDgj9sxPhMQ+tGU2/OQz3H6KJb3RDXfk3WINJkh2tU9RfnHR7sMvTOEn7yosTEkm1al0Sz6Pp04moL4PlBEsrvN+2cs3vCb/KPyPoeO2J3fzytOXt9O9Ps7qjjUV8HZISz2wU0MshrvtEWyhIDsWd3N70impG/9zbv7S2WDTH0PqG6KJt7gSHOi2wVNrhfCvQcGr+01qdFlqqrqSS4eZUEDkKpBxfGjvLCwjHe22JQ3uIWFus4R5y2mA5rXB60Yr7OAHJeAtONcD0FU1PTzflDQo34oIrtJmPLdaH7BkH6haRxucl51gZKF+9dTF/a1jUTsBmRDn66WKX6+nXSpM/kDs5cWPQA7x8u4FgHtEpcMPM9p8myTwuVpoVh46R1WTUexgtTLhr5LYcTphhZooDciiF4GdoUs375UVjgY73yPd6AvkR9V408posGqEAfkgQqtM1df5mK+GiAnIhpfTrYJGJosbA4OrxviPAcGk67cu3oXudjAjmoiAGPvfrVOG10Zl44zrWyn1htHR3OT3hnhbXJPN2Pjzydwfi1LIhiCW33gytDwk/O8PvYPwobqVFd0oFs3uLDdCMLtIYHlCcw3DUflgiNk9HTYtSn+stAr6FGf2yY6T5+9qzJVxBj5h0aEdYPVu1FRXLvyRoqtpmc0jBW5f9d9JMIdxxUbFyLHoO7ht1dQ6IQdO3v6kUckvBkLB/zCNbSTUOHo5Zu1w7mY2zLNIY4b+8tHD45RahcI9lR0jDUaajenO3y1lNj+dXMQISu1le2xJ6ZTtlKfllVYjTaNAVXGPAiS0zxgsTb4nN8l4DxNL5BDKbOsvY2qTAWA0v2M+GKFiTjDir14EI18iND3KDt6XzXcykGSRND+NKUYPzPENNnNiV//9apCl+byit2mBN7XpdKZ944j3ri35B1Hm9Xo8mPZNw8KJoCZsLubADxgBlPLxjKEyMeb3G9FWjliEOeMXa/g2EXCet5lQ2A/39NCwTRJ4wts/vSaz0bl0QGVg+eRrOnerkJob7MNXQoyXYIGcJLr2Sdbxl/FN7Br+qEO9gpUbsPERI0FpKfCmpQhAKLSUWfcambSiBBuOy/4x8+NnembhyPU47Jum5zXqNL2AI92KYATNb5E0nfnPW8EnA3/Ci5/qkE50TXC6+8mZKz/JdCzwn7qe8k3/20vNtZNTSbMQr8HxGuusKKzY6uy24JPSiKB+Cx3HdbLJETjdtRCmQcJrLIfW2LYbHsrkydVOsE+x6xHumYnY2sbhpdoqSFpkyVIIgRczQO1tQI4PFNHeuYArhJd1yB1lPRuY0XrOuN0xg5sKOx2AgkJQASLO3Tdfz99g42SX4Uc+SrNt0leLruT8hRlv0RVbrLCeFFp3vQ56tFo0OC9kedIMqOIhLXeaOicQUeDEyKojKdh4IcZRrWIZpsTMeMwjubPFfcvjQt2iB0bCb332eftzqxiUBY5tNpBYgJNVGIsQ+m+ZGn/antBebUIe3hYRI3tKFPur7K1RzicetkJ2Jt40/qazWZFyEjnur1c8J905LVIWLkguVMmzHXRmUTnvKG/D+bEtVVGqvgtxBSrUIwulXqE6zHASl6MAPoBj43Xx3N4IaZt7trB9rXD3H0aVXZt6kP/1kVe7FqJsDIIy6SFvpRdzPYJHsXmsaOWNQ/wzxN5bcNwBGntr2iWDAQSq6wYX7VqOciHDmF5zmFcfaJ1e9qzlUZHDT6cWVZslXUG8FQekCaeWVaCI3xeaXQ18eG9ElZTeGQpvMlVRK3+Rv7BsGVNfRzsPBY3aXdrAuLdlOtwsPgGC6oRyqUDuEaz27XLFwYeZAcXVRUtHt2SSoz+wALsmY4kzKxOvnmF+afVRCZVz+JqfqfhnEO9T4tVY2jkjL2rsKdnWkL9h1nr81NBuQqV6nrqJK/HarxP57VQWtguRo4eITZTzPz/yaFPrb3u/VFOyDC3kTpIgIbtYbaL2pyAtUBlvRtrKAHrZ2dcXUD/LNDuE+r3p+HTEYfDZroM6NrdqQEOSu91dIN8tMyw1IEvx8CI+oSQKhowqX6OrNYn5xS4Uhp2jys3ifGC0Qije5tucQUFCi0PnOhJYVSJgwF765ijfUZlg+p3t/OLGO438Vx0vvjRbeeOc2jBVk386+4PNM5JeybuwutURtoIhtrkcCi5AtqA8rVQilDHY0mIUBk+RWe5UaXpg+ljg8NnSgrK1vfWLynRc42wohsR0ZGVpSNpz8KJi/pi5GfPMt4hoajIDvc3yLjbF9eKqmztgmCgymmOCvrzr3zJUUwP3lqcY/y2iX+Na7uGhb2/n/oDrEdp4G4eeHTGlK1PD9Uk9rXnbw1inBA4QAg3bb8N6X2sPRrhauQMc3Q+gVJ1QDG8l2vjRdq5M5i9wv2ekawDefIEin9Z5k4srXGS0yFck4xSSl0NzPs0ZhpdXX1t6qqh8+ePZvt/Wq2vjZlyhXx6XM1dHwiFCO4ExoWJkHJ3GR3BF901JG2U2POH6VGGmQWRNu6WDWthySNllYGf5bZ2+K8w3Cex6ZlWbL5CxzKODDDA7YDCimHrRoxjEkoH1a0PLop3KRBVkkj+gRR1gRjzo9PcSiifKj2mM06Hz/Oopt6yle5zb76aPBVtvovKfKgeK22MdZshnB71yRLujI0okQ3pEtGWvo6BkPYtWvXJzO76pqasyJHAGcU4qQFWcEIN8nrA1aINghc4LD5cp5i96BmV8nHKFbgX7h38erggK3dp1WNdbRjFXBJ8SpPK+pl2R228QZ1iaRGseKrVeIssivMORrqAj+yrrtT6b0V7GfMDQpUqNqMGZmEipBKa14raOf1pGhhcc1fo0DiDs/PENq1r72S0vOMtHfL5zycJFp2jzHb7NKilnhR3oVVRrSbmrbJTU1Ndx8+PBkZGTnoeoEyMAIkJR2IxYwAXnjuVRqFoLEl4WUGk4wZ4gHXSrwOlXsuq6hGrmNuflIxFdHDf9X4/Ocy2z0zwo6QA9gd4PeBv0AvI5eRakF6byltdh1pzNl5yVLEzDTF1nx0TW1r/DIC5wd+RsqFWkAN0O8D5wav3Cse0iWra5KEtWpc2cWsYEfnUA2RLh6z/qOBezZ286o7n35wJYzjpQkzGT/hCyI/Bp4SbROhq2i4fV9npru9p/VYYTGNBbwza06BwuDeu+DQKl0jcrOBnADAYUTDI3wvgvBCPZBvU/HcSFNHZ/9Kw4zielHlQz/51/qDBxiPJvY6d9btf/NVJ3tivKQLD0XjikbgTOQsYxH16dHY+KdOs/d9t09ADh5QnQx0cnKq2BKQBngQalkfGhp9ofCXrDsULV1EQBUd7vpKub66ZuemEHYy/nXhzefYIeBHtsT7CqSxNzF59AIsHNfznqO+BtWcsZl5FWg+M77K3DK9njCxNXwrVYxSr4WLPvippOReWlrat+rqEZhMXpOIUhOkUQ/fEGOCZrVrmOGbsPPz63pylFX2zg5+30S1cPsGxB9X15Kezif7vOhexpGhveCUxK6V8ufDD0WGv6uTPm7eolsfL/H5bPk2rEfPK+f2OCXe8biaGmQLDGVB5C+X6ak762hrqiq0m1ckqrWmzWY+1BZtTErnQkNUPHJ19163uuZaPbYQzqcaqPh0LIlx+NJtow+g/Wq1yMn6m1GZppIRQmqZ6aj10wOfWjCfjVRCntc+wXDn5GJ9WIBJDGYWYAxZwoX7mkX1QKZh0BmRzy59UO0D5trJvD1vT9ejTeL9YiFEi2eZJp7iy/t4wvFD4S24rXKMjtZCVlEHqO+1C4cNNSvCfpcWHdaWNT+Xavs2tc0lNdP63WZcCC2BocSScXH262CJL+i3CIw39fctSZxnAbtt17eUSQJA0zBXqLwh5k579ecw9to8BXcD+Pf7vzIHa5TDnhchjq86z+2VL9Q0+PR3KfxHM/kB2Pq6yScpT5tMEAXKMastqqo4yNlLRHelh7m0EgPCQAVp4C+uYjPC20RTeyzMSCghS98KmcUcM3sTqigGs0OI6a7rK37bAagVGHue5dxxXT/NMUErhhurBdKi873QRcUfaANziueCKEXdNe6CJiDIb/es/m5+igQoC3OhRm1xqNbfKv7GtzPHM+fm+cnEb7+OOB67eyD5c8LOh2mjbyObZA1noCXbvO05ZwYfS81pl3lqE7ha89c+riEUOUQ8dnh4WHUaQaK/9BB1EQKDsL//JgUfuR8Z9F1fdPOR7Nx2YO4AoLQdUJr5+OAT+NFduLyAUoqHPcPkSD7SYrsjBZEQb9/AvQsg2t5vwkEfEfCdRe8GipmEOHpCGqy4iRdVbLkl6dLSB4BWoXHwmko9nIkhZRlLOXmvO+uI7CaAiQn8a7fazFcrIaVVmxRjOO8rwa+1A4ws9V0gCbcCwLCJY/lHg+22x3TZpCyKSjdloixgoOzP2cWC1+aY1WbXc7d1T0ps3nuwXeFHvsXB5/LJM1/vjUIrk4Yri8J2ExDWQlOyeufmB40pQvAadgxYX19X4wEbQgbhT5kgfZzArdlFunA9BLiVGw97+2PoXkh6sGp+2zk37b+emyZRH2WWpVIIRMR1v/XPDQIPd+bJVqEEcN+U/Nih+kjMybdSkwGXC3w+h0yqq5nwd4TKgVbg3t3B6WGwNWS/hBsQgWnm1RutYW2G0LM7qxSGMvcsOEF17rAMnAtTy/hoO2nYPk2I4BN876bMUoU2RplcToDYUjXKushhzXcIPVUYFHqQpgAoVQ18HM4rJSgn0do/bAx8c6kMuep01u/c33PuxwYNXB9PTBBngu1dh3P8P0i32dN6lukjndvHHhuHZeDDu4Uzg5NA3pYG1W9pkGvJMNDDRHnbyWqEQuh30Ign2lqRIRyxiu9ozufSOPx5DB9v0k4Wi6jXDffUrD6y2XnDfL34HeLbMUZ/LfHWw/GsndNSSNiMxUj6LySIDPV2xTxdWQgWq9POAcS2EFZlgy8qhmdcPHNA6tlYvSpGdp2nV9LHWnpoL4RG1KkBcuhEstfbCl7DjFK6XpgrubuPolURdrzFQAtrCl45oVT/EGMAvpbRwDYjZQ1eyQiJSc1M4SZ3rJjPbsb4W337ln3ErXgcoasu22T++xwu8fkTy9/L/HO6We+mBk8ya7+F2LdPBOLlP0a0fMjIctBYuqOpEF43lkbK0++r9EK2QdZOmnOAdcbWGmkew4PnWS6nWlbaO9aMoWrfOn+Vei+l9HcfYP/zK/ublsh6McLPzkGSLZzxwJemUS+0YN6NTIVdKDRRqq81Zr515Gg0S8+iBsmVsTFcvf7OvsXSOTEVAAwQamvHpqGVZkqgWpUhq6VdxsxrM/FVm6YdbDCL5I7uTFftBrMavNZ5n9ln5+vsDrV2zeU5EFjvQizs/9A4IppgL20iAhFZfZy52SkfXPtCQt+gU8EGfvi6M6WmXZoVHwc5ggh+zE1KqnGbi9yUdaBazZf8tUn8TVo9ZX5j9pbtXuOSLMjbLrsec0/lezOUIRHlxn8myq/BR1uPDqJgnWIZTCEpz1hqtDdzODXxhnMH5Xj7c3vQkOdmgJj/JfPpqPNYmHb1dHE/1mjXt24OZEsLHjv8/EvCCj21TAvwhpCFc+pFeJKBYuG9DfanQfCYKg5r0yy5ubl5984dRxSKA8RI1IMvIZUeMJ0TEtCErvgIIn1UCEfWeAkjIdQh+K4iguu07+T2QPTo9DNnVXfh5mqmnY1zFA50Zo97HPtzza7y24iSkPh/T7kEyCPFvD9Mks6cLRwaG7f2t/ibyTw3XHdi3GWn/NODFULyrI04f9Zn0ovlUKuA0C6HH7bDlxIUkzbLPGxO92u3cmvWUwog4sBkYtIaMDeDq8HrN8kdVIPcJFHJXM8hZyO5C5bL4U9mwOfjjH4b1PdJZJ3/gzuUQUluG4Cdlj099WJIPGT75CvGjxqFhd8h9bPSRcm4qm1M4YtDKsjQeKC62sAdcOTvYaoC0UYq6+J548XKuUxhXAlWaEwdoQIL1Hbmiu6uYr5NEX87M2WgBo93c6f3SKTM4Ngh5hnAjN+zVf2KigobnKT+reazHIs1q0+QNc5QSi/Y/Ndfq/QPr2nHIgGXxULl5O+pXaAZIjEkNUa9/Sk1L47d1eFJWxMUJ2q7sw0RanFxN2ZdbKfH+8oDY/yOQt7wk8ZDJvWerAFmW+vqCAyGzC4oB2aBRP6vIO/qjAqkqLMEdXX+gtNdWeGjiQQ843vn/PZTYK82EeNBDsXBeedHRPjbimz2TrlGgiHTkol+reDNR9QGO64e07wiCPL3txYQQpjHW4Vf56MF0GmxfmFK7GOjy+M5HnDqoXNeXsV06l0Py5K52dWQIcqPcfa839eWpIeUt2Wd1V1lqgfqt6xahms8FJgB3nhHu/NSpp6bSIihxxCXFdK+CT0KL7e/OjrgiAwvuPK6orO1ZclT09XF0Xe8hb3GOBwjpVeys+IdWQsCFF79zpzL2fhX7bEHynxQ93eEZfM4Jg9hUPUa03Imd6+IgBQ4U8CBKLk0JgkWrlK46ifhT8+xWubds5iA3rgCBLi9JvzmED02J40fjtzgixgDL0IPruZRnQVol1VLqBrhAPmIk7OD+BhiaxABb6oRhwWRbClBCStaACpwVZLwhiXlq4W7tiJxULo2/AkKbUhyoLSwRkdr8OMUmRVYEWTUq5hQrv7ran1vk/vayPDww4574qxfP3/W/4I8AavAxUSQZ+F6crPia5ntp3/O9mJJ3+av/9qlE99m/dj+7/HtKcpaxaa+95/EN49mk1b5y5VnSB4jacBUb25m0+6Q/RVD2NqNNYoIaX0gmdylT1Xv3B4YBgRTBC3HBHI7RcXLo7b3gB/OmAoAwS7YnRjX8TBItEHFPdj+49c3zwXXSOG5GSmjt/1OZkWx2zky6YtyLaqfVwk/WdR50YZg14bgUyG4ovNeAxhkEX6a8zdmMwKzLooARiu8bBCgFGfFLwwsaUrdHulaGEQLgvJdI8bZSxB1ll+DhcwQitOvzNIiajjTVXXDbeufHnH0O2BsbMxifmrqqYhRvjqvpcJB97iPQa1ZtVfbcf3Xzbifmm2yXWrdL95dpT83gkbcwnx8+y/F8OFDTYOnSptgv4JA5ZncTqzrit8kWwKo9MBoHTHfDiTprqwc2ZF+73dp6UbQ0MctzJ8LVNleBbjtfnWiiizm1Ag=
*/