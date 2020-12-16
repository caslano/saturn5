/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden
    Copyright (c) 2009-2010 Christopher Schmidt

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP
#define BOOST_FUSION_ADAPTED_STRUCT_DETAIL_AT_IMPL_HPP

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/int.hpp>

namespace boost { namespace fusion { namespace extension
{
    template<typename>
    struct at_impl;

    template <>
    struct at_impl<struct_tag>
    {
        template <typename Seq, typename N>
        struct apply
          : access::struct_member<
                typename remove_const<Seq>::type
              , N::value
            >::template apply<Seq>
        {};
    };

    template <>
    struct at_impl<assoc_struct_tag>
      : at_impl<struct_tag>
    {};
}}}

#endif

/* at_impl.hpp
ZGMrXvQeOHnRbeDEtl4CmApXCncL3Bq4FYewuXcAbhv87IdrXojfw6XClcItg1tXiL/DVcM1CuD3cMMCyi6fq/2PyQG7DZBAAHHBbQyY9kC2BbRNkGrQPxNpn2naBxk0M9xGSBae7QWbdLXbClmC5+VwVfJ3uN74+2Q8N4rgt0jbEWkPJjnsBpbheRKe58BVDoDDs3lFdjsjZfi+Dm4H3EG4NsXa9kg/MBWutDjcDsniYtMWSUUx8il+8H2f+KdtEn9Q2ydpHYR/PBsEZsEZg7T9wjhwXhDhwa3rpu2XrA5qGyZbg3Y7JvuC2pZJCr5vBrNAfwnSWmLaNhlWgrTQDmJWibZzMg+8BW51ibZ5shWshksYrG0kNpgFzjLtoPTD/yfDdYnXNlEWzdL2E++cZdpPXI3/V8LlxSN/YPUsbTvFmF27/ZQ28NMFrh9cClwe3KLZpl2VO2eLbRU4kPZVlI3GbbO1ncZqsNNQPC9FOHBZtN24hPZXUvAsBy5pKO05yt9L7TZZaNuRtllA/H0d3A646lK7rZbWc7S9lkFgMlyQtluy5iDcOdqGyy3gmjkRbbnQfqTdpstm+N/W09W2i7IxuRd/7wc2utRq58W0PRmH570vNW2+JOP/OXCL4Mrhkobjb2DWcLt9yj2X1m4XptFcbb+yC5iA74PAFHH4f6n8ba5pM2bNXG03Zgd4EM5pP6bNPG1DprcQ31PBeXDNk/D7eaZdzDX4/064eDyXzYMAnrUHU/E96TLT5ky6bCzgb6WX0f6MPMf3JfIdrgpuD5xsPMTBDYPLg1sEVwZXCbcH7iBc6yuQLrhUuPlwd8JthNsBdwCuzXy8A7hUuCDcUrgKuK1we+EaXYkyghsGlwW3GG413Fa4/XDNFyA/cMlwAbglcOVwW+D2wTVYiN/DDYPLglsMtwJuM9xuuINwrRfV29ap/9R/fquPH276Edf/n1k0JxAsnFyKo/uzek2e1Qs3AMUIwK+0ASB645d3xnDiPplDyb2ASb2s2u/b4e9F/bH3s8r2d2q/N3XLH2uxI5jK9YBkQ69bjob7fXPE8U+7PnQdWt10le+X9VJP5HPU7ufhI59vdz9vf+TOvbvfF4h0Hr7u58Ddz59Hvi/gfr498v2F+3vK807nHX9m1aqv3hhw8LqMJzq9fkHk+wt6HY/vmnUgx2Nfx3uc57Gf5Pnupwx97m4tz3evp+31DWCpD7+7B2MvuHWFnENEMX+w2BLknKH2+YL7XCHSHIHzAjUnqH0+oOYBUcwBaJOQY377eN8c60c3zt88yD62r6hlTJ8w2H0czzG8Gr9X1jJO5xidY3P3cTnH5BiPu47FOQaPZAcRrGWcnQxyfM2xdXQ2EjfPcR1LcxzttJXoGDu7jpujHyvrcXJ0Y+S6jo/t42L3MbE5FlZjYCzw1Y8Z6z/1n/pP/af+U/+p/9R/ov38NvP/tJJgniwA/Lr5v8zdd3Xn3L3mbA9tzrQBHwETZP6/Uc3nOGVXaidEeRL0pyiDarXqoaOuIlN3i0WvVUELeZYFnWQzqNeqRj9QZo5SamTRsU3dS3klMPCHQlLPs0LPRWm2ek7dMXbdVumh7/nQfWDqaQ84bBo1VOmZ5bAFp1Ji02O6xct7JiyrW8G+YrvgWWtZQTuKVrVQq54D0e80Y9OpYbrG2zex66XNCT1T4Yb0jJ9N/XNBUQIZpvc7qDxbbS0xn0rfMvU50K+pB7ymXgR4hn8i3Imc1/fvD1a65jVtSmFhXl10dFnz2NKmWyKjuKCHCo75CcunLZ2taSdvGNM5kOmsPEQ60wqm/mbpPIfp3MN0zqcukrmSVviP+7NrOqPWyzPIWV/YDs5pqtKIYKg=
*/