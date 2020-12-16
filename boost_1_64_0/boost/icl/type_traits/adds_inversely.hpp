/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829

#include <boost/icl/type_traits/has_inverse.hpp>
#include <boost/icl/functors.hpp>

namespace boost{ namespace icl
{

template<class Type, class Combiner>
struct adds_inversely
{
    typedef adds_inversely type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (mpl::and_<has_inverse<Type>, is_negative<Combiner> >::value)); 
};

}} // namespace boost icl

#endif // BOOST_ICL_TYPE_TRAITS_ADDS_INVERSELY_HPP_JOFA_100829



/* adds_inversely.hpp
lGgVo0RLjloep95nylw3jivbrFFeBzqvKAzuR+GiGweD8R6zm5B4+VGMkZ6aliz7x/YVe9FMSFlpaamSjO8T0uCUWJnF9sljkREVE5tIXN4lvkwFMolW+PHRAXzQRL37yDxsiXJyAbtrfC4bDUpJzspOkMRsX+nDvT4ui7LkWDiP76PuZtELb6L8NdYykhE/MMqcAQ2S65Xl0TVWlQdnqPMAQ50HSK7H84hN6KLKgzPUeYChzgMk15PqOCAtIyM9We0s5/F4W3DNs+O04DSXc+fUPLACbUCr5dwZNQ+sABtOD0hNIJx5cVEOawIhZfVLjiEihYdn1xiS72WiOJ/vRylF0uB03LGk4h1jIvLY3KLDiq3DCkbV57ZFeuiRHtmr+7sR2PAnrWr0qYpqVC+MXEtdstS34g7MNCB5uGlAqikr/d40CkwNQonCiUggZRtrrEuZP2Je9grruwxULk1jNkYiCqumzUPMpmEQNrO4b0HYvAobI/PtJiLy1o+hI++jP/8QffLxCONXIVSWjhxV8nmN2TQMwqaU2QhB2Kw2MN8YQvCvFLpHTlRcn1V+G0WF2ZR8UrHN0wawVeWEMZukkxXbPKOxCWU2pZXYzAnR2JBic/pUxTbzK7DJrMRmdmigTQ1mM/V0xTZrDeyYBhHrNdwmiFivY3FrGESs13ObIGI9N4TZBBHrh7lNELH+SyizCSLWz7K4CUHEegO3CSLWG1nchCBivYnbBBHreSHMJohYL+A2QcR6TiizCSLWU5gN798K60fTirOI9Vco6wz6HlW/U3pGyWc6P6ZB2MzgvgVhs0hTn3H1DZR0Hn3iBUUerrJZ+LXC+yuzSQrCZqomBuPhm/G7COOl7xR5pipuoy8qvAd5DIKwmcnrE4RNfX5tDOJ6GsmvjUHY/Jn+e1JV92+iCXfFqtu3kRTYRmoS0cJrOLcAQuqH/6OyyVhnJBmJpfuIyKCyqcVsVlDNCm3u19jcxGwuGSq2GcV0OSOC2YwuZ1P93xeq05WQ8te+pNCaRuMNSv6CTlv/RWtDik30jRXb/F6BzYpKytmnvfYxmyPhFdt8F6K59rH6CGEV21wO0Vz7mA3VqNiGNH1rGLNZWInNT/yaFESsf+U2QcT6D24TRKzf5vUJItbfsrgZg4j199wmiFhf5feoQcT6R24TRKx/5jZBxPo3bhNErF/n18sgYn2Jxa1hELH+gdsEEetr/DwNItb/z6nqawkfzQgcD7DrXFMu1URbqqXE8SEq3287tdcUZkM3VWzj0l5TmE3mzRXbOLTXFGZTWlbOP3dN+U3Tl0QT0YraNY3uOkr+RRR8qsZxyDfjLzba5HbZi2PiohMCDkgzVmeOkBAiaozzp4ni02xVnZMaK7ymRGRQ2YQym8ymFdtEaWzCmI3x9optmpTpK8nAbKY2rthmYYi+b+5mFdssqsDG2FzX5rqOvTZdYWXxPugWY10qaYG+rgMrU6c/uUNz7oTcQpQEmxWty9sYWyq8HprzIJTZXGpTsU0vjU0Ys8lsVbGNoDl3DNy3lhXbdOQxUNWnpIr69CTWD6vqU1JFfe7iNqr6lFRRn+bcN1V9Sqqoz19D9H0b3a5im8UV2JS0r9jm7pOrOhZ/1bwG/QdS1f2NNPMR2Oe31LZBIlrRuabxdKxSn2M6/WonbRtkNkdiKrZppW2DzGZhdMU2LbTnFLMhXs4/2efrPRafjkN7jateP9Ja49/dkn0C2mGiYh9mIIrugrgAxHhtNbHrz2ymdq3Ypp3GJoPZHImv2KaNJt7pzCapW8U2a3g/G0R9cphujSBs/tlUdTvH7Fql73vbpUkNNt9sK+QzzTVUcSZWn9Pdcb3tofgdHkY=
*/