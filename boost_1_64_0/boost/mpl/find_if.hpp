
#ifndef BOOST_MPL_FIND_IF_HPP_INCLUDED
#define BOOST_MPL_FIND_IF_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/find_if_pred.hpp>
#include <boost/mpl/arg.hpp>
#include <boost/mpl/iter_fold_if.hpp>
#include <boost/mpl/aux_/common_name_wknd.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>

namespace boost { namespace mpl {

BOOST_MPL_AUX_COMMON_NAME_WKND(find_if)

template<
      typename BOOST_MPL_AUX_NA_PARAM(Sequence)
    , typename BOOST_MPL_AUX_NA_PARAM(Predicate)
    >
struct find_if
{
    typedef typename iter_fold_if<
          Sequence
        , void
        , mpl::arg<1> // ignore
        , protect< aux::find_if_pred<Predicate> >
        >::type result_;

    typedef typename second<result_>::type type;

    BOOST_MPL_AUX_LAMBDA_SUPPORT(2,find_if,(Sequence,Predicate))
};

BOOST_MPL_AUX_NA_SPEC(2,find_if)

}}

#endif // BOOST_MPL_FIND_IF_HPP_INCLUDED

/* find_if.hpp
7cyAXWBVfSXrbFuMdVQR56de4cO0otZtZn2QSjYIsE9u0fVxcWPmNHQBAUTstQYYfzY0LuEmKjS1YKh7/Eei2VWM5vrYNcDm5DaHTGUuig1hKNTs8og2KiSNt2vu8XWklo+47OWNoVY9cVrkQTceOfZzxH+p/dc+phYm95+YAP1XxDn/1mP+6Wm4zpqGTMRjQMTrNBGvS0az69qj2TGKZtczza61aPYRcZjkhFuMmbRdkajvJs02UEyiWkWzsFKESltVWNJga3WDEG2DItoxIFqpsGQtiBbQzjUr5OLGpmsV0a5jooVtMlEbRckEkokU2yr7fiGez6YdWeJJ7R/T1aXHN3n8F2oVtD4BRFfNxvGK4bkVHYkgOgE41wWEyy0TuUT1HLnHe6smsXq6qj8Hl0bZa0vUIMwLYsf3ZyUiGfOH2cIrEHsmbd0aYvnhHxAeOAHi85/L0WlqZ4M4Eldq0qidPZr8pugtkWZGQyWlBCA21ZEcm4sCuM7lOMlZZvz0NKCgMv4ewbst8h3G4KHsQm6rncOYQjR4xGZBjs2jArgepoce8lMHAbxiHjfyOJDS0x1u5sa16lxTBsD6VeUaK3pzohy1nHUS3MVRfrdXa21O1PYLWL9ds20y00HEYz3cPy0vvCodTPveuW3KH2t1vseL25Q/bjvNJn/kDWpT/tgRJz/4oP8kG1+onr3G6+JzAG1+C7T5zfVkuBS+KZbFmuCzJiVXPTjhffB1E97tbcN7Z1o68O7T8HzGoBTwmhie27jn0nTglVjw3ruuTXgj2sNPzn/4MFlbupRAke+RAIyGf5AawybMcMeZVR9Hzmt1zueGpOPc2dZ56vWEj1rN7zhbn6XiYNSNY5mpTlxsE7aUcohFy1tSkO6vSkT8Oh2l5koVaLETBSSsLKvjjnMTM1G2MUaWhvHJ4AQYJyfkDuvczw4+yA5Iqf+62qTHT6+184TsiEfuIkKNvjT8acX+52qTfh6Mg+cGvH4HBu/JKTo+vu7YPjgvFCarVksaG5ecGmIpJl5X0kJ0Qx+Rqk4e4NtX6oVoV9e+vZE6//iX1U8s4HNx4aLJ1qSeWo335Mm4iTbbxljapaU6P0w4X9sA+r/KIY8tnECqA5e+9bkLX2g9OMAxKrK5rVU5FNQsOIdOWqZHqmh1faNcr66XZLjgQmGcc0pTK0WRGieDunBqK3t68F8ufLq98PfNwsdxYck6myohx40KesYqFayr5++IyjjvZJmfSJX8vKj5okvH2z90iS4N0VNSOxXYTAz+eydlpwIRIrowDCTDQPK4yEhBciSQ/NsEiSAwxSPhy3LIeYQz0jWHN1l+URznTi9HOn3mN630PE5fyFiF6uoZWTNXyJZrv1t3A4ULGijj62IJUmf+4gYr83YITnTMsf1y1SsT0Qr+66pmNvUM7/MWTtY9mVVXz8/sJ4WHuqX8t3Apd2b1VREGRshxRSTD3+h0TatbymBJKl1rZrnX1vxieNSxcF2HviRLbBumJ7OB763s32v0Gq7iFRXNp0Eeo0gtdnzkUvR5OER/jDfRdKQL6pACd4uwByOl+vppwKHn33gg/UgfN0yBDjDo0RboywT0GgZdrUGPFtDYwRhZCjRQ9MjLE0w2/baRG9xaucXrkX2qrlzcDaZQiAA58LGaiL6N1BM7J1IEAysXtuY+els6DSP40RnyIcAwjF3yhkkHdHTnPihjWocEEfh9Vx1Zgf/f/Mf86ibw/wrn/vGuDqt6BpSiA7tJrc2R2fHLSWpNX1ZbvUzmxV/ZbW3t2ZZLKH/c4eE1PS9aspJGOFq+BiIKsYu7ohRxq9iveYifeAh2Qfs+VjzEzySQo7dHsuffdZ22R+g=
*/