// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_QUEUE_CONTAINER_CIRCULAR_H
#define BOOST_MSM_BACK_QUEUE_CONTAINER_CIRCULAR_H

#include <boost/circular_buffer.hpp>

namespace boost { namespace msm { namespace back
{
    struct queue_container_circular
    {
        typedef int queue_container_policy;

        template <class Element>
        struct In 
        {
            typedef typename boost::circular_buffer<Element> type;
        };
    };

} } }//boost::msm::back


#endif //BOOST_MSM_BACK_QUEUE_CONTAINER_CIRCULAR_H

/* queue_container_circular.hpp
xBgr4tY7QtFZ9AXg3HWXTB9IHZ+PFG8S3i/TTdhmsS86mWnd+0vN+96lq5kCkp8vPYv2pTm7R8r1HlV8hh6v4Pu//CaA5qSh8vqj5uzMn8/hlhSD5sBv0yvGNVzYYz5n2yjb47LH+u/axa5Oji37XcVlR0u8Mq9ifFXcflvmYt1YMbLMmRtpTpY5z6eritNlrhhd5mXFhMs8zudUv7jjsbbM+fwY2ggVt/jGT3Qv8Xdue9yf3tvqOfcqu6xnfcsK5p73Yc32LStoW6zpti/femGO2748O3Vf6Oru5iRrTr8AO5U6x13PymzEOq2r8O+K6E/kU3+cpkno9qk/voNIRme1tAJNZ8R3EG/ralR9PO65v8O3/9AHtbROSYvledQifRvPMLP0DBLN206Evus3GWTcvfNykHHv0cUZs1g+OnViaeZeS2k8sFetN6QP2lW6uzffTffvee++Mjd19xkvL0HGzUs/yLh5GSrGRMPj5OD1vm6iYD16o69T8KSjz/P1tE3E2RgCW/9QWseLU3C06mhrj4W2OGvrFL6bq5nxiduv1GwdwlYf52iJ+R38n9dCM/0B2yn/XTpgMfr+L0Cv2XsLVZSj0Pi+Av92m8OmZkO2TvPCK6AOoDl2Vno1/i77WF6PfqLQtUNWxRrOk3xOO2T8ljSz7JBxPZY9ndLDfYCnUafJ45nQdKfJ/VP0Jua402S/rCh1/v0m7OXt0OEw4bfvcDW778x73axrp0n0VzE45TR14B8qRg7gHNaOz2FgZqarGWuazPQUYwdRwfQDDNUf2QQzA80g0Rj/NJPakwlJ9uuaS1uN6D+id4YZ02K3RDkVNJe1sg76GI+hDoHtjzXtnMk0a26/qtt3+Uy4bruK03XbV4yu26FidN1G7/YZXbdFxei6nVRMuG6XFafrdlsx4brtKo7rFu8woN177xPw36UT2MAc8XPQrdvBb1L0PE1+y3O7B811HiO2t6Fg/L6w/BbW/L6w8FbWdusLiw6n+8IydGk2rMdCl31lVqbLGCO9exk8lnF1id9Fb2OdnEv+Hf+dnUvRN/eh63ekR0iLrXrSMCY8IdOE4xmJcvi8q9ua3kSfBl05mC34hT+zzDy9c0Hf85uutMhNSZINYuAfDMDQM132cZ1IfEv7i5mOt6bNlte497gC9v+YoQMPfHfoy/h7LWmtnDMfPzNtCfb0Fei2WPmt+x1orv9Q/hr+Tt0lpwVjj9A3WivVDf4sC9Jb+DoYs4fH/tU38Xd6R2W9Hsl3GVmjNsn2vP1t/N18Ai7LZIx6/g70RKSX4/xupsN+mvz93/OMNnN4Gqt8t5qQ66JXhy4nyOwnf/JSVl9kL1T8vvQp1tkTZT32dZNzoQ98PXF/X3ruedDhXQp9OaBTjwB99DxHV9+IHYjf28B5H0j8FgHLsoPu9gjoYz9t84YeQdy1fD7/NksUxvTP2N+VpxamqNXRd/FtsYty+6Rm5LfnSzoM545HGfrdVCwYgz8ZYiiWiJmYw/FiEuFQXjMG7rXtjOA7dTXDHZIYq99h4/Mp+Y3/l9qwQiFF4n7aq21Y6VvK9o6tHQ6k7/O688DZ9/QsxPPw4ZskQ75MgOn/TjBedBjb/oI0LcwfK9uVdPFm9XXP0zpdM01W6W1GuixqCgJldT2P5VOlDfiG1/eYzZht7EauZt/FacOGb+bqck4x8jRrv23sud3c1e0F1LXqKu20izXWQYizszUCqyj/EEd3fM1dHNRjgKEmW6/Ju3e3UEz6EUkzuoh07ZDd+xydbmgk6S0mcAUdHmdThhfgyL06XR/bJnNRKZ+LRXhxLmeGDi63bc2R47VOtcXz5NJndV7rq2JGTf8j1vpIQfY=
*/