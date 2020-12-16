
#ifndef BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED
#define BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

// Copyright David Abrahams 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/max_element.hpp>
#include <boost/mpl/not.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(min_element)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename Predicate = less<_,_>
    >
struct min_element
    : max_element<
          Sequence
        , mpl::not_<Predicate>
        >
{
};

BOOST_MPL_AUX_NA_SPEC(1, min_element)

}}

#endif // BOOST_MPL_MIN_ELEMENT_HPP_INCLUDED

/* min_element.hpp
rvz/UKCtDuif7LeNzXSAtsIhaRi5NBmjS2u6oMAue62Z0dwfb2IU9QRG6uCsu9W5Vd/qp5GDQZRw3FE8vd+mPzH2z+td/cHZtpnTnx+aOv1JFo3JvvvzfdM4/blMMNKF8l0x/aHMjoeuP5Nx/lkXqem/yb6b9PPOWfo5TQXxILi9HXhRaG+rBBAErLr+izWTCPWiscDxvpNOSwtlWH9yGAGQ/P0FQbINJ+5AUQ4uqr+RKRRvT4XZUKSF2oL04Kh95iqQHuf6a71BOwZoQwrtVMjPK0Yw7YHnhjWrlfizgottMsWGodggVexkVEQyX399+Zi1VhGeZewtmfVQdrrOO3uNKy8V1bwxW9/PlQ0misS4oGPo9w803IShQ5eT6eghqrDzKAkeQT5rojZpyqyhXnPMJIWQ8fpkd3nTaFNwowO92B7RyIk6iXtoxwzMxSulh5dzCRL0fAOzFucdXmQQl0C2bHxeQ1leoU7WboPhKmBoIxhojVTTB2Ho5IRg37xA2//cIV/Qzp2udoZhS0RS/gj2xQUV39jtisUvYmF3eier0tTXFPU99nxUfcvB6ReNKAKClWR+tNXBj9hJ1cZkhV2dVT6KbBpoKIbnw775041qmPi0DM9hQB4+qyh7AR/4cOcznxajDHWjdUozNJcdlkxvbzVJ1G28Fm1MimpjuCF98XqUCinwitIBPSNic966yP+AJ5D6fQy/HLQG9mNe14Go6SJtJFaEB57EPFve1Jz+bzsNt7xCKRuqUvV7oevEf16N+lyBSq+zp/trBio9TARhx4PHridreHr6ysiWkEXm+rW6twVY+CSs70QC5EenZS+7n02aB6nKACfZrwh9ZUox3ghDXEXW9X4thsHqpuhu7bdgoSIuyXkXQjJoKPVFtfpY02ojXwx0icMgqQ01xwiggrWwhIQPNYprcQ5vre9IE3xgfKS+HxPf55iX3fwm2BeSyU0PauLYV8UG6PeWTulgXeu6RZkrqtxbn9YHFTY41j5ZwVL9YqkGP6F/cBTjuuS5umR4hPa7igpbrnKKhWpWmGGKtcHp/Zr5+jFarEfI29Ycil1u1vOelyLueObF6F1UPPMqDJ4rnvnnGyN1Bhh3/H8Qfkgd65XZjeNt4OWtUca+iGfVznF+gNF+ar5arX+bUXel8d6XZ7yE/RptycW0NIjtaVdui/Ieh+ebbM+FpXzD7agdaps+nAiPasFEqPGD1diloWmOWej9nijryNkyt0Owh1Lha17YMvVevvD1mNhtYAeum+HYoMI578MaISLG3POy69CKa0WPWUi6su0rpLJZtVYGW2M0faSprpMyaLCeNhgbaIw3C8ZwP4LxcvYLGoZmCGoj+IHo+4BSHiKmmY/zcsuVW70fb+Q8MYBuZa3W5bGanl0WOZjAiYfoY/Qdu1+MtUc2yybicTGZn16pYYncFwILzEQefNO9qpDbinIxGLfJkdNY+aoTbILl4fLVWAjtbjImt8FxrhXFs8rn38dlknm96acKsAeWGs6chWyY8+YH8xxL4Atewlg7MQ4nq9WjEd8liMOnKm810eulosDB27lI5ehzSt4twO2MlldHxP5pCjps3aLnHaY2Ly0F/G+kttDv2z5bHanT31cetll8f+8P1aN8v32U/309yn//59rLt1hQa3m7w6uRGv7Nvnu57vreXr1v/2UpD8bPd7/0WiOkCTA1/J/F7w88WTQhKHESUxgAQA3/J8+b/Rj0KFLzBBaUjvV9klcpoC9TNozaPeiZf3ODtdY2FYnIfHmF83bjtFsUkzlvqla4AId6fcF7BSi26/DrVX8GnOZcLdn8bwr1hl/G8P3x5EvIBtRi4zprFe9dRDq9WbY=
*/