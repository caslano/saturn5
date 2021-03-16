/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/norm_inf.hpp

 [begin_description]
 Default reduce implementation.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED

#include <cmath>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

template< typename Value , class Iterator1 >
inline Value norm_inf( Iterator1 first1 , Iterator1 last1 , Value init )
{
    using std::max;
    using std::abs;
    for( ; first1 != last1 ; )
        init = max( init , abs( *first1++ ) );
    return init;
}


} // detail
} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_NORM_INF_HPP_INCLUDED

/* norm_inf.hpp
tsM559lco1ndy36/6+fHQt1xXD20dqlVa1LmXj+ZFWFwgwi8233xXLS5RdtA88vTmj6txgwR7fOgF0ZH4hbbQxR6wNlz2mpshJa/5LYrVXxvhMBbpH1s+N13lxpj02WMpFfnFtCxUKzkyXJ41xQdUn6+UNpT6NAHeOW9rg7Cl4f85MzygBb+es7Q25a3veDxAy8875Sov+xaE/aBBI8n/XAUuOaLVoX3bNdXo4a3n0I8CNvWAGw25wIETZ7ZloU=
*/