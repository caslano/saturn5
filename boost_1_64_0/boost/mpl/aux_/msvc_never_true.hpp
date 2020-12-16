
#ifndef BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED
#define BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace boost { namespace mpl { namespace aux {

template< typename T >
struct msvc_never_true
{
    enum { value = false };
};

}}}

#endif // BOOST_MSVC

#endif // BOOST_MPL_AUX_MSVC_NEVER_TRUE_HPP_INCLUDED

/* msvc_never_true.hpp
IAxEghgQC5JAMkgDGSAXHAH5oBAUgRJQAapBLWgAjaAJtIBW0A66QDfoAX1gALwDw2AUjIEJIErB7IEX8LsYvkoReIz4//H/4//H/4//vOPvn7dCnkD3d+5nTp6V6KxN/tHfnZa6IXLdmkjc3vV3j//x2/7kXuoCVyE+Hfof/v//xck2+vHA3B7//N05luTNl1ew/6H/1u9O1fxnz9v53emn/+z3kGc5/uP3wvz998Su/923/MVht+Svr2m6iMfMf/d8/sljvwj662uQfrFUQ3Y5vi7/k8e+BmvIbsXXrX/6WAjulYavV//0sZ9ryJInI8z4k8dW/vV5eN//xmNExF8/1i82eJWjeaMwSLgx7Yed79TRM2vzPrc+5Fxds17U8fLQqg8BMitXjrGb01Xaktj5/ts8g6siKz7vu3fh0cLQ8103g9uf7lquudRz36s9dfNfPu588eLGgUf0OTy7jtT3hzb0bni0MVz/2M8sTh6XcpyOzwhdv/xtc9Y3ya9Wxx5lVlfUSVZ+rJ/gtv/o39jmzTzqmUNTURy94aq39+TA3uMe2cumGTOXmLFrLr7j7E65eKWsf67B5rRf1d4Znxvn+mpvyppkoVlC+I5f1+o5dXK6WYes7XNn9K4d23vM2Hlqj2JRQY+fF3/exu9Vzd2paQs9nC5c6pc6vjxfYVdi3a0q69T7nyI+bN49s/fZW92j9f4Xtgq/3j/B279Ykb1p+Suvshu+z1tZa/1DfEK876h6hZZ9vLL1Zz8d+axZ0l2f9EvlHUYjVZtY9nWVjsMFcdNzjzPkSmm/2ffo+/r+8Pz4hSELopnPua82FT4WuVVz8MJk97uv3F/Fbmu6f3r08CKjxxJNSRqz7hxj+90TiZuXUflm0+tZ+1nLQ39RzRnrnjQR+fbhQTxrU+my5M6zejVM94VzEr7ufGNZEKQ2WzlDvO7BSOqKNcJN2g0blbZOMh3O593mJShEuWkZapY6N3UK7gfGbZj+3C25gXr6/bK8DzmJE/4Xc6Q4h8pU2G/PfOucFFVbWe2gdFQ5d3nb2YjaoUh7ibfzp2Y9LZuTcpdqIeJVLs/sdCqKSIh/kZM6dOTE+VZ2XPH85TVOBw9YfBf/mKEafmF9JWfxLvqy5ytH8o/OtRR0R/00/Yfj9gOHMu32bV77ZKdefA/qFlqUv95wwgeXv85+cunqTkrCmuDQTQHKffXS2knKKsaMBStW33KOm7nx8QqJ3U/EvnFGoj4+UDN40H+vIFR/7ouDe7W6rCjde381Vn7zVd+pdFpedbK0WHBA7PvdksPdi2elT35YcUmjt1zH/7TVpvmzqMpWFaa/PrN7yb71irKi3w6rGDxQfL069/1mz1x7FeXFuV9ajZ+3LPhZzKfg5pqsk+IfTqax8kV2yKiYJBzv592zMZu9bL/lZh2V2xJrNozMOnx57jyudET0oUPrxNmdx+sXpGsvGv25xqGK4mfM4PC0kDa9qdN8pcijHf4aNnOeHhZtDCu6uJm47hT06oPvSkPPNwyvzXJ6hb8qKdy1ZDLK7uNQrdjnC0unpaKGbE+9c/3Z5xtblv18Y036K/frvtHR3D4fW4WQ30RLGpurCx3uVqvmDvfMst6XKDHXVzefzjt1RWrmhjsRuyXmzWS3azzbuufnN35tfX2VzsmntJbpvziOWIhZt3A/e2ddPbX/We30jms9WZmH35/PKVtytpOVLXZfY846nY096hcru17eW8cOZQwNBPnuKOIxTzbtP+Fz6NyR4KtR8zwCNxueun2FofB9n9nEvuezuq/Xd7/92UOj2+/S9J9KKV6wXnVQzfHl59UqrKYjBkGXGmSPxu7sepNRKu+4Xm2GhM4=
*/