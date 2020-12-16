// Boost.Geometry

// Copyright (c) 2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_PROJECTIONS_CONSTANTS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_CONSTANTS_HPP


#include <boost/geometry/util/math.hpp>
#include <boost/math/constants/constants.hpp>


namespace boost { namespace geometry { namespace projections
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename T>
inline T fourth_pi() { return T(0.78539816339744830961566084581988); }
template <typename T>
inline T third_pi() { return boost::math::constants::third_pi<T>(); }
template <typename T>
inline T half_pi() { return boost::math::constants::half_pi<T>(); }
template <typename T>
inline T pi() { return boost::math::constants::pi<T>(); }
template <typename T>
inline T one_and_half_pi() { return T(4.7123889803846898576939650749193); }
template <typename T>
inline T two_pi() { return boost::math::constants::two_pi<T>(); }
template <typename T>
inline T two_and_half_pi() { return T(7.8539816339744830961566084581988); }

template <typename T>
inline T two_div_pi() { return boost::math::constants::two_div_pi<T>(); }
template <typename T>
inline T half_pi_sqr() { return T(2.4674011002723396547086227499689); }
template <typename T>
inline T pi_sqr() { return boost::math::constants::pi_sqr<T>(); }

template <typename T>
inline T sixth() { return boost::math::constants::sixth<T>(); }
template <typename T>
inline T third() { return boost::math::constants::third<T>(); }
template <typename T>
inline T two_thirds() { return boost::math::constants::two_thirds<T>(); }


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


}}} // namespace boost::geometry::projections
#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PROJECTS_HPP

/* constants.hpp
UqV+cegyEbl+LdnBljObCMuUanS3TasCwsy7qa1zxQm10ddkPC+v0n72EKYn4+tscWxWCWEGMp7rMV1fnhbmKtm41TMThXmQObC1BMYt90EPSnYpzt5JWDCZC7PShnI4PyPJKjHbNSa2jrBkMm9m1fyWT8E6A2ivMts7NnMUepeM92DeWaXnoXfJdMyuDJ5sQO9K4ya75T+I/iQryMyzfUdPYTGSdcn//JywBMkcd9yogfjICjPrFrfqOHpCsjsvCvmjtv+i/zEbErcBNfKUrO/AMh44C8hUeSk7DnUPIrPk+33Zd8Q+lsyK2fu4Q4uQTzKez2LPlLzIpzRnuT3vFiKfkrWM6jgW+STzYhZrG3ZLmNJdvR/KFP8QgHsAmYHZ6Sp+3sgLGd8Px74deSPMh4znZcmMKk2FtZTG3TYriz7rQJaP2bwzc1YJC5Ds4NgmuOf0keac5uW7BXtFiq/QrKK9hYWS8Zz5XKlzQthiKYa6Bs9U7DHJTBzSZ+NsJVPV/eSIUjg/pXG9yxT4KixJMqX5k/LCHpHpmM042beMsAzJnu+e/xm17aG2sMVzxqK2kr36FYh7v4GM7zGzqX//gzNLsj5vm5ug7mS8r/s9DtuG80yyfAt7jhMWSGbJ53x1vAPqJ63zQofWM1A/Mkdmneeuui1sLRnvF+WAvTv2ChnP9c2rU2AHyHgv7XWf0hX164HvK/kdw9F7DVAjybJSa1xCHQIpfrPf72o57/EH673HeRaE/syxuC9FauE8kyzqVSHUKJ3MklmpS8cycNZJ9iRixT1hpgOQlxyzm77qC3qCjF/v5a/IlXiuk8a1uvT8Gu4dZDo27sW+I49xTpDxtSR9vRGPZzCyAsw8LXvUw9lK5sCsn7n3FZyfZIWZfct8Wh9nJJkjs33OtfLiHCQrwsxr1UrjvZHMjMWX2OzyHNSWzJ6N04U9e4VcSzkb3sAV57z5QEUpyuxHXNRm5IysELM6u+pjv3uR8bXMXtsY+6ixZMU2f+2HPSbNaRn97CXuR2S8RrMmjL+JfJIVZObUKKg77kdkFsxmH+h8AbmW5ny+3nk69pg0Z7+jHj9QB2lcwYV+dtgP0jjrU1OOo0ZkPNeXhnf1xn4g47302a1gGmokXa/1uSvlUKNB6r4OtGyJPrMm43OuPr1NwRlJZsrGjT52LgC1JeN18F1RvS7OSDK+ljSPlHaon2RFz7jPwxkp2e4v7R/ijJSsXZ6/8+OMJOP5tFzw5RvucZJ9f/FXGO5xkjVsMW4M7nGS7a98Lh/OSMmuBV/5hHucZKsPNRiHPSbZra0NKuEeR8br7uCcWQzvxWT5WR06BPVfhdoOVo9bM7mTLZ71yfg+elj85GfUloz3fPsp+fC+6UFmxaxCUHAyakvG617Lb9ZOPNuQ8T5z3Nm5FmpLxus3p/yi7agtmQ0zr+0DMrA3yZyYnU6KLYMaSTHcWzByHWpExvv65oy0NqgRWVFm8U9PvEcdpBia3P3ZH3tMynV6i/uVUIchahtz3Lom6kDG56y2uUF71IHMhY17t244+sWPjMcXsXEk6hcgzWlikV4V5+AQ470j+9A5tObVYeSTrBKzbglvRyJnZGWY+S043At5IavArHu34r44C4ZSrZl1nf4Mdfcls2DW9MThW7j/kZVgdvrTrhvY02S2zKy6fWuGM5msILPHNf/1A2eyNC7yZ0YVxCeNmxle9i/0BJmO2ZCB70Zg35I5MAtuG4J7uDJMfb0zL5bcxzsXWQFmM4b02YScSeMGT6k4DHuM/smJWVXDqbmoLZk1sxu3KyDXoWRWzPK+feqMc5DMhtnXg2HhyBmZHbP9a6z/hZxJdvTFyom4V5GVYjY=
*/