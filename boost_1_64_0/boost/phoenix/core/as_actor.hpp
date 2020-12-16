/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_AS_ACTOR_HPP
#define BOOST_PHOENIX_CORE_AS_ACTOR_HPP

#include <boost/phoenix/core/actor.hpp>
#include <boost/fusion/support/void.hpp>

namespace boost { namespace phoenix
{
    template <typename T, typename U = typename is_actor<T>::type >
    struct as_actor
    {
        typedef T type;

        static type const &
        convert(T const & t)
        {
            return t;
        }
    };
}}

#endif

/* as_actor.hpp
QUDTRmsYMKc85mWhfZ1P2r6U16cwL2AFaZk96DgO86Kz82tD22C5gNF8xoTM/gDbC1hRYhM/+rE0thcwD2LP2+6qh+0FrAixOvGm4thXdOneqdypO/ZpnYmpjZKxnYF5EnuvcX9XrD9dfGuavMSxIFtnPu4HvsTyXKSN7+sjX1TH8tTZe/1r4bXDAuYuTXN/ZAWj50ucvL0klieYD7GuzxZtwvLUpetWxvculidYaWLL4/Y/x/IECzVKu/X62EQsz2Xa8txY/OhFLE8wX2KNrpTF9RfxKYxLxP7e6DICywWMtpdfi33dD8sFLJbYdPd36+H5wGgfK1S5yjGsI7ByxDpX6BqO51uuTVe/xNeyT4PR8lx9ftB4LGuwnsQsiQXkPaXO2kWXkevzK7TxJRxMbYLHBKPnC/Vf+gTrD8yLtvl2F4Zg/enMVvKzBXitAmtArPezJkYsF53tHecnY1+pHeu2X4grjPlcmXdfsYHVJZbSu7J8f2Kltt+WsmzfjGW2UlsPLiGpkzGfOkurufYWjmertGPWid8+/QjHJTDazqau8Je/DwCjeRk6dHYhjEFnwRdaJWBZg+XVPpN16aJ+31Yf49PlpVHWmEiMT2d/hT+Tc4bVBtGB2B/3LlfCfIL1JXZ0Y9IqPCYYLZe5Y97fLd8ZyjsGM1gZWn+/7MDx2sqks4HRek/f5xuH5QK2m9ihbcPeYPtMgnkksRJ/jP4Tx10wOoZM+n1TaYxhrTa+r2LvncQYwGoSa1+uUgzmE4yOu+/WH3kH6xZsDrFXxoe4PmhZZ4A956R1erp1JeZlvbZcGvUYvRbzsl477vYfcrQcHnN93vHZwNYTW/f7mQ6Y7nNt32zf/+pY7Jtg35J5iJgTIu/tN2nrduB3M0dhewErT+KbMH18YzzmFm18094+mIXjElheY0Ei2FZifv6jsN5tX8AxjeSaemu+3Ct9hwF++Szto5c73PGaA+ZPx+vlLw9jDGDVSex7Bp3tgG1wl30dRdqRftvxPQjxpfY6Nm9fn6+wbsEGEzvQ9pU7xgc2m9jBDbFDsI5S4H6TWN/zHw7H2MHo+bzMH5bH8gRrR2zGntM4984Eo/XeoHOTvzCG3dp2fbJpiHwHGYy2wU3h1XA90gxG66h1/zohGPtX2nSbN16qgscEK03nIe49S2HsYLRvZi2b3w/bEpMuAYyOdd5ha77F2MGqEet46ruOmM89sN5D7Nv+PddjXsAa0et06uqKWH9gdF5w/PsuntjOwMrSemh17Q/Mi86ubwrE9QmRqi2zdm/Cf8V86iy82D45HwSj1/Au2QtWYB2BBZO++bhDX/ncd6/2HmFtwU1lsb+DWYi9dSq0Jp5vn/baX6jXbLxHsIHRfD5c8tVXWEc6exQxexeWJxi9H/spy3UI5hMsgNjID+ZsxTL7WpuXLlFj8H1oKxgde+Z8XQXnITYwer5n1w8Ux+uKzgqff5aI5QJG+5/17m+xWLfUdM9essFo7K3812VjDPvzLmsrWFFa1uPDR2AMOjt19sSnWJ5gjeh8t6ZhCeYTjF5vP2zU5xrW7TewrkjMtMQ3Cfsf2Bk69kS3HIZ5OaCNPXJT70NY79R0z3oSwWi5nGt/ejrWA1heY1YaWF73lOk6G5K1wQdjB6PzrMXjT7TGevhWO754uw/9AssFrAsx81n5jm4i2D5i1R+Ev4uxp2nnE333TlmFMYAVp+2lUdZBzGeatsy+6GPDY2aD9XWRZmvlJX8rdMwgUmg9BE3OvW7C+7Ta8ix3YR2mSwD7mljGsrjBeMzj2hiKmErK9SWdrd455TvMJxg935K7N3FN3Pt7g/iZzlFcwuSzuhPa2D1+vynvLcDK0DE=
*/