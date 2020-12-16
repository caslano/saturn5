/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONS_TIE_07182005_0854)
#define FUSION_CONS_TIE_07182005_0854

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace fusion
{
    struct nil_;

    namespace result_of
    {
        template <typename Car, typename Cdr = nil_>
        struct cons_tie
        {
            typedef cons<Car&, Cdr> type;
        };
    }

    // $$$ do we really want a cons_tie? $$$
    template <typename Car>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<Car&>
    cons_tie(Car& car)
    {
        return cons<Car&>(car);
    }

    // $$$ do we really want a cons_tie? $$$
    template <typename Car, typename Cdr>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline cons<Car&, Cdr>
    cons_tie(Car& car, Cdr const& cdr)
    {
        return cons<Car&, Cdr>(car, cdr);
    }
}}

#endif


/* cons_tie.hpp
GGt15niIo/AorsJP8RQew1BOSJ/hLPwcX8Pj6Mn1xQkciV/go3gSv8QvMSSY4y/OxK9wJ36NdbvyjDim4Glcid/gSTyDESEcp7Ecv8UP8By2D+WaBqfhd1iF32ODMPVZmPH4A27GaryEP+Lgbup5cjlexK/wEkaGq8/ELMBf8B+onD/bRABOQld8GmvgBXTDGE4K7ngn1sR3sBY24yThgeOxNq7DOvgvrIvdI9Xz7Rysh29gfazPyaQBjsJGWICN8X5sglvRCz/Apngem6FLL/V8WxObY8kNar9Nov02l7yYXEl+V2/P1ZOe9KQnPelJT3rSk570pCc9/cnTH3v//8RwJacX0WWv0vh/Hdr+z2nu//eQNoLmsi8+5JPUdfrGqG3H/cLT81lMfl6R2qZquEKbKu1iluVWy3KXK31u4FJ8SXn3iHW5RdnGdHbq6u3h5nbj501ttcos9u8Es76HJ9ZB+7Ky0dNrWttiPSzz8ZoiaYd0w+nqONM0Bs005nZHT8s0vCJE0w4Y6+qs/ctZX63O+hJ21pfq9Ws3dNxnsLO+gZ313eusL15n7ZLO2kmdtT9eezum4/ZKZ33iXnsfwNfah66zvnsLTe2nny14dEPrC3d3/OGdvw4b3HE0DR1qHyfyu5PfY6BdHycN2AzFhlgTG2EjbILSpip9csjvTH5/gXZ9cvgyXUtpz+qGHTAGA3EQdsTRGIYzpL3rLgzHTdLu1Y6Fd8fl2AObso5IrMCeuBR7If0NmvrboF+OK/XJYamTNJLN/Wl8R1b6yvAlZwW60y+G4z4wquzqMAPJ5n4qFpLXk839TxyT+k2vrkxHTiFL3xLShwTrJl8i00cE/UFY+3/IJWvrQw+QT5MvkT1DWR7ZUV8Mu8jSBwN1qNZ+F/zJ0eRUspFcTtb2j0B/CBQ+05Klv4PL+jmoItv3X+BD1vZRUGFXN1tN1vYhEEs29xlQRq4gGynvikC9zlZPetKTnvSkJz3p6b8W//Nmo+t17/8ZLvw7SZxeJXH6Ce6/MvVjittDlRszzHH674vPtfeHN7OJz3Py1Aid8Tbv1sufbpT/sIvd7WNwy/usQMaVmIZ9ZL2swy62nynxv2UZJQY9jtfj+P8gjl9riuPn+y6taDVq6a7IfRueuHP9Gr7kat+x8vuR31WgXd+xPtIHZ2vsjG2wB7bFBIm/R2AnTMcg/BW74CoXloV9WGZX/BRDcC7bGYpt3SgrfBW7YTr7HI5TMQJnY3eswB74AEbiw9gL12IUbsHeOIzvSAxOwj54K8Zi3Vrqfaq+2Bdvwn74OsbjYUzAT7E/zuV7PwCXYCL+FQdiT34ngzAZB+MITMLzOAQ9KL9krIc342YcijtxGO7C4bgHU/ADHKmsF0fhdr3+4U9Z/7BJr3vQk570pCc96UlP/8PpD47/w5ScPymze/h1av8/HWCwPL+eIs+vf+pOHIH78DkCCd+OEv+HpZtWTf2DaYPM/QCWXKUfwAnSD6C8e9wS85vf4btQG+9LHUAFNjbXF0w2TjHI+GW4wVS3UMTLvLOm52ary1htWUZOcfZExkkfg0bGaZ/XTsXzja39EEZa+g8wmoajlXk0/RKGWP6/mLWqy0i0bps8z219p3lxtrVfggLWzXoKDJr7EaI6m9aVYx4XqNlu7XvTZZ0h2joJH/JHplhzQd8fk+f3uXAk+Mjyc08kPzhHjTV9XeSzks9QSe3IXsoI6esvBL2ljdcHB2JrHIZtcTz64nFlXpzCvO1xJvrh3eiPS/AmbMR3JgDvxQ74FAbi89gRd2MnfB8743EMwgk11Bh2Ggbjv7ArVmMo9pHYNQm74TAMxzSMwKnYHedgD1yEkejBfvc=
*/