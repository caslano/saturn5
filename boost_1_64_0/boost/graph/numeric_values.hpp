// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_NUMERIC_VALUES_HPP
#define BOOST_GRAPH_NUMERIC_VALUES_HPP

#include <limits>

namespace boost
{

#define BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(type)          \
    template <> struct numeric_values< type >               \
    {                                                       \
        typedef type value_type;                            \
        static type zero() { return 0.0; }                  \
        static type infinity()                              \
        {                                                   \
            return std::numeric_limits< type >::infinity(); \
        }                                                   \
    };

/**
 * This generic type reports various numeric values for some type. In the
 * general case, numeric values simply treat their maximum value as infinity
 * and the default-constructed value as 0.
 *
 * Specializations of this template can redefine the notions of zero and
 * infinity for various types. For example, the class is specialized for
 * floating point types to use the built in notion of infinity.
 */
template < typename T > struct numeric_values
{
    typedef T value_type;

    static T zero() { return T(); }

    static T infinity() { return (std::numeric_limits< T >::max)(); }
};

// Specializations for floating point types refer to 0.0 and their infinity
// value defined by numeric_limits.
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(float)
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(double)
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(long double)

#undef BOOST_GRAPH_SPECIALIZE_NUMERIC_VALUE
}

#endif

/* numeric_values.hpp
RpUpiQVDRs/P+NF5ivepXYV9eZooCXJ+vi3ouINxD5oodcP/uEehd6TzqPwdJqqL4BH3HPDoi+5cptYlDriCdNeZmjGT4JWuxcWlYp5yI+ncYKqDecMYMb/IbZ9ViIlG8T133fU8Z25OYRHVaY/cn6mMVaa26JchiL+qm1M8HENBJ3Oebxznud/StalK9D1dP+BpW5RxH2nO7Rz9k9oazgVpoh1TnhTx7sip/VGermJeQNjLUAe9rZS0NONxOGcYN4ibJpSP84XxYVuQ8/Xql2Al/n0j5/ctZ/l40REhFKEdwq3QSbQpPquL8vNLFhjnaLR3elyvDu9Xvr9rE/MiTKlfT5t2/dU/5w26Q8m8eBLu5zhuQUq2Uj96kPDkUzuG+39ODJN1s0I2S63YrOD3xdimlDFUXC8eoniwZPCzLZ7X9lF6d0u5abPExzheRoZ4VvssnPq+Rckj8WMvkfLZHuXZQchukdqzE9QXVlFfyMVzQ1FRYQ5tLiQ+K826/ivGSdriJ+p8tq5cVl/x3PJmND0DSarP7ZepfrGTjD65xboKu5w+zlwobca4A5mo3+sB2XgSTpBi8a3LHywoj65l+0l/bBDGPb4/uViMJc9TWrw5krWUMqVDku45pDSrID8nL79UjBm5seQ7XJrF3uUyjK8ka4fPQx4RtmtHdXlw/ArpWGDXkDi34/YseX46jnxID7Oyl5P/nLzDMq/dbY0G8LHHTvU6OKGpaYX0km0TK7M3Z1O6WFlADytbdt0WNiPti+AFg9dIYRnfmloOn86qhw9li0dUsP4j27CosZ+wMDqGxOtyo5RA5UqibpHYAbon+OkO03t2te0adCxCPu9lyly43DpnqtedKqDGyazCspwivNZT0tCs3beFDkr6AauSdzNPLyvXyo2QPOTla7Xg29fpOpXAr+W7h9Azhv1G9IFNpi9NzQNasDpBJ8zx/Brz1hg5vVXgy1jTdMK0wrwxANd2yiuxB6bTtRBx6OrjOE4x1WPqNNSAjn8yQKn7D7Kc9pvL+9H5tTiWUZ4o3TN5Ar9uNlLaWloE7BYS1Vt6uUs/Ngf2as7bUEWmnL67zkZ8nfSsab0pKuANaUZQP3MH+wypZdi3lmQqR7NTI/YxWy6dCOseeXvSpU4FgQt7fmH5sc9fLc0HjYmcyttgFXFyILo7ntyfNo1gAyxr2NeWaJZsTWR/si5lYwL2SF2CRrCXgtewwpBo9kPIQLbBdicbYB/CNoQuZ23DHGxp+BrWNiKaLY4YL3WKCmOTolLMO6OVuf4o8R6P3+Pxc/lhipnWfgbhXms05rfjeX1uz5LlZ6VLWMd5lxTNnkYvlftiP+RpTvw8MZHPo+BneK7iY1JCX+rjwcNZuSU56CTKhlzXfpuwExihtnUf3bNFA/Q7WhtylMaNgEnLBvdAvzgYLtd9LdmvMC8/R2t71ZJ+jNKmeBCheuYBP6Kyfp2o9+2ONJoff5TSkifJ5a+n8ktzU6l4PgaalPIvUlp+rmg9PD07Vn98unbjLoXShd/+p+kYTSdp8zR4wCycnZ9VmMfug858SN4knbBJSfYK9gjGh67hQ9lKvGE6HulAC6tgLaMdbH6Mgx2KdbC4eg5WEO9gT9V3sKCGDjYuwcH2NHKwi4kONqiJg21p6mBnkrDSq7mDnWixiE1vdZgNbv0qa3HNYRbY7jD7LOUgO5h6mO3ueJgt7Pwce61nBku+ril7ovdyVqdfJes4cDlbl17J8jLnsmHDKtlbo5bo+u9M8Z7DRGPeO0Mbs4+HRPE+k5hLzy+W99iHuHeDnmj/c0PG4Bo0W+ob9JfgJShD1zfQK9A3qB9eIp61/lkTq/TdHxXbOPXdNJ4=
*/