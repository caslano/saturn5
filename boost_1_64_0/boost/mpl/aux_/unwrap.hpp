
#ifndef BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED
#define BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

// Copyright Peter Dimov and Multi Media Ltd 2001, 2002
// Copyright David Abrahams 2001
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/ref.hpp>
#include <boost/mpl/aux_/config/gpu.hpp>

namespace boost { namespace mpl { namespace aux {

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F& unwrap(F& f, long)
{
    return f;
}

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F&
unwrap(reference_wrapper<F>& f, int)
{
    return f;
}

template< typename F >
BOOST_MPL_CFG_GPU_ENABLED
inline
F&
unwrap(reference_wrapper<F> const& f, int)
{
    return f;
}

}}}

#endif // BOOST_MPL_AUX_UNWRAP_HPP_INCLUDED

/* unwrap.hpp
uAlCfVaStTKeaHlgEm1h84GEoEyMM2+CmW9ekNjdd/BdoB8w+N3xQ7UkmnCborMdFxo7bYRdLZ04TDehQRsb3V7GPOM0vWBkYzUGDhwm/uovYW4kGzmexIs9akn0fmEEJKb4o2wBGxoJ+tHwt5mQZVOD3nN0MdJCHL0qmuHN+jCQ8o/EO6urac/zWNjLlPta2IV7pnBjqQlChngyLWs+C8JSLuiz1wlMFmVBhKQKbjnWRj8v8gKDjzF0l9lRiLefhx+e9eHxvDvMO+ZYFIl4DieSj8MOvTGSstYTE4cfUiJzE49obSWj9jpgpvoRY3qy8ZXHSapRaYYqYQfQTD4JNw2fQeezrdgjOpmq+01E3pFesutQMFZ96Yf6GYoolZ1OpPiK8aFbFBXXaGCekzx0MLEd8/Y645YFF4Br3jjUma8EDP1UvG6xFSoWbqZx6pW4ujkfVlQbwrYQSWjbNgjKp4uI0Hhh2Dc6A/zC3kGC22kMca7Ge515mFN0CjdwUQyY1odXd35EE9V8HMzyoU2+cjA4XpY+lNSGKIunsIHPHajxPNL9eAOK1m4n7F774JBVK73a9xD6Kn2wYlYXqrAdhQsh68D8lBFoR0yCURtXkr3CHckiWwwsrMUJZ93J/sRd6LapCL0/2qKW5DAktn4EbntO2H5GE590f4SkC/woGWmLNrUF0NVhRmcx73lSF/ijHb8ajlPPAhtLXbDsYQeDhT34KmELWV7Bhj7vfJB/pAlUDK/QweHHmGT7gGK8PVRNoOA7yRnM00+g6BMPvHHyGMZuCoc1b4QIV/V0VJpvR3qs0lDnhD0Gpa4Hvbab1DrzFKwenoJd/gwYXHOYPnerR2Wj56ThpB8GZ+ui1KyJMOAYSGrTtPB8VgTeamPBi+ftSUdhAByoKMLne1ejWrcyNZ5xDfMlJ5InPKO4WW8HqK3wBMP9zP8lXjVoMmUL5ZhVAB85LoJiFfPeOdEUc3kU4Vl2AOxbeRBZS0Yh+fEnFLpmQMPrBjFTRQ6+TnKCvNRq4lhwBnt2XgfR+yW43XY/yC3QAlWBcHzFyo6RvY5YVNsJpjL3ITKiAXk0FpKli9lhqo8KzrimDqk9W8HMSARY5BkgHHcDy/c+p3lqerjr1iq6JjgQJw1cRjPHMrhvl4i3eW7BkY+fiZ0aL4zrliD1ijZgvcSaTG6PAvbxxyHQKgYbWNjgeGsCZprPIh2Ht2L15Nfkq3E7LIo6Q0z9mOdcFQu+jcpEtpN+EKt+CvcnxODN/ms4s9AJgyVeYoN3M3oIqkOBqB/pW8sBOysRO66GAZ/8VCrvfh6lMp/jpuyvuKi+mIh0HwHjyFngE14EVV+EqZyxL9aL+eKa2uM4dowPX3hOwzIvV7C1mAgZ40OJErs5Zr03pLNmXAQtXgc8aLkJKkraSHn6ExBZPYDVudqQJK5M4hYAruQKwkqOEHxh2EYOzXSAQut9uLpGA0ePLifj3paBmFYtREZtxMd8EuRBijqK1XVAkdAbHLyrhMlZTTi/jhsO9N7DtgVRZLr6Ysx4Gw/hmbfhRSkli6tlscNghKyJvgrTw3vhqrouuvF0oIEjC+QqtUPzA30MNU7ArL6XcD3/FXmrdBXlPZ4Rl0ktmCnGvE8IPIshr7ZAd20NLOG+REY3n4Qjgw+oSR0/bmm8DDELOXBY8ijsfHEK458tovVhyqiqF04esRBo995BjmofwjdnCer6akDGuRq8JSCNTSyPSVtEEW5NkEMRvUDccFiP7uaOgANTZ5G5vE9wFl8lBvXKYaucOwhqPYInSSM07WI7LH9kTfblD2K82EsiYuGJSQxD2N1og67rgeqseoduae4QkDwKJsJhdOSuNF4=
*/