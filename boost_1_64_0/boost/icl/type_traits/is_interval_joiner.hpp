/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_joiner
    { 
        typedef is_interval_joiner<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_joiner.hpp
40EMGQGYsDxUvwTzexLDQQMm9yxM7TF0iTvIBMJ0NmBWV8Dc/QPdtRumOUhDEIaHm6HyLehiFzBMBNBlzkPl29C9dmDIuxFdM41hrRtD336Yy1aYmgMYGg7D/B6FmfsJzEEfussUTNR1GO7+gaFvJUzOPphOA8PVQXSpFeiOO9C9Gxgy0+iqRzFsrsSQuQrDhu27RXePo9vfia65HcNCEsPLHTCr18KU3Yah5xRM/z9gOtsxvF0Hc5CH+duIoecYuvhPMEweh5m/FsPAEgxPSZi3LpjeVRge22E692MYKGBIOASz24nh7ScYBlfBnN0AU3oKw0sSQ8MiDAX7MQTeBrM7gKFvH4bhgzCzp2GyumCe+jC0HUNVvBlV8Gx0ra+hq34dRUmiGPeG+h9BUR4Cdd6CaopBnYOogsuhSltQHefRDW6FGuTQ/QyYhG6oqEEqiKo/h67/I6jFCXTlZeiOb0ayz0VTLoAaWSjWB9EFlqHbfA1d5kdo9hqqcx+6dQe6/xEULwKV/Sq68+/R3DWo4jlUz8vRxRagK6WghkmYnRSa9/1o1nkotgGTEkS3tWAODkFtglCrE1C336PoX0VXNVA9P0ZXr1MVoIlfiS71VXS/56AJboFp24nqTVKXQPP8GGZjHprgA1DpV6AZY6iiD0J9R6B+t0JlazCRb4GKXQ6z+Fao4lfR3bIwgZ+GSh79D3vXAR5VsYWXjhFkKUoQnm+lSDFAEjoCsiRLEkgjG6po2GQ3ycpmd9m7CYmCIkVBUVBRUdGHgr0hNlREQKSr2HlWLO89u2AvPH3/uXfO3rmTDSS8+n2PS5Zz55yZuVPOnGlnzkCEOFHNBWjOs9B8LkGTt0FktEez1LfNwKZt0XRtqB43xMq3EGkfgAUOgYUjEEm6aAL7rYPYWYBqb4wmugZN7nY0o2JU9bVobk5UuwdsEQbrN0IVN0YTfQQi9CM0q28hXragyheAne1oDt+g6cyAKH8FzbErRG0amnc7iODGYOHTIb5LIBKLIVIaQ+QcQtO8BmJnPpqvDaL/EbBpBOJhH0RmBKIhDWLgGjSLD8CCXSEK50Ek3gbx+irEwW1g4WSw4QCIudsh1lPRpNtCTHVF15IMEX4Q3cAaiHAn2HA0xM0lEJMfgIXnoWldi6aeApZ9Dmy5FeyfDJE2C11FW3Q1z6FJXgKRMAvi4Vs0mVcgTg9CtC6HWJuApjgf3cRmiM9vIU6caB4pENslEOGb0YU9B3H5KrqvdRBtTdBVzIeYHwOR1Q1d0dXoamZAZL6K5rIaIjwZXcEhNPfR6Gq2UteG7iUF3eHpECejIUrXo1tJRZe1DiJ6C8T+7RBt69HljEGXOAFNaQDE6j6I4xkQXRrE4HJ0OfvQvMZAxBRAPGjoDldDDHwAcTAGXeTD6I66obl7IJq+gbj9CN0AifqHISqvhXgqQPd1COL7Q4iU9egSUiDqPoQI9EDcuCEaDkCUHUQXsgXd5jx0k+0gdlMhYvLRje1DV1yMLvh0dAtN0CUPQNd+AKKqPURhI4izWegGlqNrKU7ACABdwTWoopbwshPZbQ3WvhRF9xJY5sUBGASi+BaDzZdRE0FWXaiSHWjq6SiiPLAPNcPxYP3n8Mkx+FQTZG0RPn0CsjsPImArqv2y9phUtKVBFwZ1YL3maKqtUJRLwSbNwZLjwbovIRuLUSXZaP6LO2LSgGrdhmw1B+tsQ5VsBeu40FS2QERth5hoQ9WDKr0KzX0xxE9LVEXuYEwYaKAGcbMIxbcLzbg12PMlVMVOFPeJYPWxYOVxaGIt0NTapGDQB5FAbDEGxbYNTdcJ1tkMMZIGNsqA+FuKZnjFEAzU+2KwC5afh6bcJgE=
*/