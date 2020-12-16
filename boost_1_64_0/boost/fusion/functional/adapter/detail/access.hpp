/*=============================================================================
    Copyright (c) 2006-2007 Tobias Schwinger
  
    Use modification and distribution are subject to the Boost Software 
    License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
==============================================================================*/

#if !defined(BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED)
#define BOOST_FUSION_FUNCTIONAL_ADAPTER_DETAIL_ACCESS_HPP_INCLUDED

namespace boost { namespace fusion { namespace detail
{
    // const reference deduction for function templates that accept T const &
    template <typename T> struct cref               { typedef T const& type; };
    template <typename T> struct cref<T&>           { typedef T const& type; };
    template <typename T> struct cref<T const>      { typedef T const& type; };

    // mutable reference deduction for function templates that accept T &
    template <typename T> struct mref               { typedef T      & type; };
    template <typename T> struct mref<T&>           { typedef T      & type; };

    // generic reference deduction for function templates that are overloaded
    // to accept both T const & and T &
    template <typename T> struct gref               { typedef T const& type; };
    template <typename T> struct gref<T&>           { typedef T      & type; };
    template <typename T> struct gref<T const>      { typedef T const& type; };

    // appropriately qualified target function in const context
    template <typename T> struct qf_c          { typedef T const  type; };
    template <typename T> struct qf_c<T const> { typedef T const  type; };
    template <typename T> struct qf_c<T &>     { typedef T        type; };

    // appropriately qualified target function in non-const context
    template <typename T> struct qf            { typedef T        type; };
    template <typename T> struct qf<T const>   { typedef T const  type; };
    template <typename T> struct qf<T &>       { typedef T        type; };
}}}

#endif


/* access.hpp
io9iXayLDdEDn8R6mDeGe5asp5xsD+sx3IfIesKwBRrRH8MxECMxGKNwIkbjQhyOW3EEvosx+AmORKUNYhQ6YSyWxjjMrafSlwIH6tTT1yjPingQ3TALW+Eb2AXfxL54SLajiZAh69sn6/sHRsr6jhJvVfwA3TAHPfAENscPMQA/wgH4MT6Fn+AGPIXb8FPcjZ9JPsYapF8EbpF4y2CsxLtXxojfjzXwANbGV7Ahvopd8TV8Cl/HSMzCVHwDZ+Cb+Awewkx8y/xNU+kbIX0m/G2+aTpD6tVcfBznYRN8BlvjfOyIC7A3LpT8L8cRuAKTcCVOwdU4G/+JS3AtrsF1mInr8Tl8FnfgBtyHmzAbn8Pj+Dyexc14EbdgCdK8FWviC+iN27ANbscOuAN74U4Mxl04AHdjCO5BGXtd+lfk9rfwtxl7vR3HqTrYBbthV5yEgbgQe+BO7IlvYy/8HAei0jY8CL3wKczCoRhFHKHozI5txJ0YgcHF2W/wFg7HtU7sJ9ixBPsHXsA4fIYLxAT0Jb2JmPuuvvQvkH4H/jbv6o+Sby8kYl1MwsaYjJ0wBbvjWAzBcRiF4/F5nIiv4yT8GCfjZZyCyv6bhjVwKvrgNAzApzEU0zESZ+AcnIU7cA6ewHn4Cy7GEqR9CVbFZVgTl5v3X+k3gLN19t8QOR4Mxho4BGthKPbBMByERhyK4TgaI3ACRuIUHI7pOAKvKRqk7wDMkHidcYjE+47sv9lYA4+gKx7FJngMW+J7GIDvoxGPYwp+iFORspXzgPQjwOo654HP2e6l8TRWwy8wr3xyZLnutuUj7+AXx474D+yEVbCzpLcLPoZdsTEG4BPYDZ/EQEl/DwzEnuZ39qU/APorwead/cOUoxO+gy6YjTXxCD6G72JbPIbt8D3zNzzk+T9OI/jbfMPjCzlef41u+A3WwbPog+ewE36LffA77I/ncRJeMJ935Vk+Ntcp7+1yvbgDvXEn5i2XJsv101lusyy3BXvhVqvlrspy3XWWWyvLrcMuuN68nDw3xxCd5TZKfcjEfrjJshzPvQvO30qJb5Xkb7UsV72IPMeW59vKcu7y3EuZGivHYfRBD2yKntgM/bE5BmAL7I1+GImtcBW2xrXYBp/Dtrgdn8QD2A4PYXs8hR3wCnZEJVGd0Bk7YwXsim4YgA2wG/piIHbH7hiCPXA09sQ52Au3YG/cg0H4MvbFgzgQj2AIvo+DrK6X5Bk4z8bzXy9dkvr5I7rhVSmna9gcr0v53MAB+DM+hb+gEX/FBLyFk/A3PIx3MAd/x4/xLubuh/LsGxN09sMz0jXqLKr7B/bHb3EQnscovIgjkdtluQ6TZ90wTOc6bIMc/zaiOz6HXvg8+uJmWf8WWV82IU3Wt0zqVVX1OodJxkpxwslYF6dgW0zjv4E4FVNwGqbi07gU03E5TsfdOAM/wJl4HGfhjzgHb+ACVK43M7AWLsTWuBgH4BIMwRU4AlfidFyDS3GduXzkmTi20SmfK1LuP2A1/BFr41Upn5/wCbwm69tFyJH1HZT1VcJMWV9qMY7bOA5r43isjxPQFydia5yEnXEy9sIpGIJpaMSpOAqnYTKm41icjlNwBqbjTFyIs3AFzsY1OAdfxrko+4M8A+cYoXP/sFf2h/3ohgfQA1/B5vgqBuBrOABfxzg8iMmYhSvwDdyJb+Jr+DYWJb53sCRmm4/r8qwb3XWOeyflPPqJlOMpyYe/EmS5QJ37qSL8rioWxUZYDFuik5R3Ccyr5+tlPRV16vljUg8ex8ewPjbGBtgcG2I7bISDsDGGoRcOxyaYgN44Dn1wKTbFNdgMN2JzfAFb4F58QvaHlngKW+FX2BrPYxs=
*/