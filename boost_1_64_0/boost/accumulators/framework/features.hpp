///////////////////////////////////////////////////////////////////////////////
// features.hpp
//
//  Copyright 2005 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005
#define BOOST_ACCUMULATORS_STATISTICS_STATS_HPP_EAN_08_12_2005

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/accumulators/accumulators_fwd.hpp>

namespace boost { namespace accumulators
{

///////////////////////////////////////////////////////////////////////////////
// features
//
template<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, typename Feature)>
struct features
  : mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_ACCUMULATORS_MAX_FEATURES, Feature)>
{
};

}} // namespace boost::accumulators

#endif

/* features.hpp
0NebaAjkPSNIA3A1RRvKmvtU/Xli2JATMqbw+XnsW6/Q6XNs85d/XHyhcfHmztUETKB9gB0EKNMpChmPdNmfnNjI8i4bblwEIaYgc1bAVDH7KU1Ikm/L9V1eIyl6wYTYVpX3eyfRcuiHJUrmuTS3H+1E+MuptEvWsEPDNScP/oQu01H+EkrPYsZJk2GPz+OJjXJYnKI1iRMpnqBR1aevM0v+ZV7kn+f8+R3mQRnfSX8GJZ0Wbbh4oOfW8IJMk89VT0VI3SxicNHn2XP/YuD7Abi6Pq3zKbT+NBhGBJjiXxH95srkfHA4tei9ndC5sGkaVk16sX1V3jXgxCjJNcODwBWmnWsPKnRLTkBaqSImFcBEufuhWTFoWmttcoxuQ3PcjCjM3Hc3P/DpxtE9KRhlUAc0L9blhFKpiu8rc0TNSe9uPPF9o7jaasqCfdXV4WB+QdOV0bR1qVWz/wqiaAy+/PuyxpB/jhzExx0HllcfzZr1HieTqdhg4QFNeIvxsOcF40qeDM5qXKVPFzr8kwEkaWNcWFfZ/Ad7SV01FL5C+woT0Pz0PYH58pJucA==
*/