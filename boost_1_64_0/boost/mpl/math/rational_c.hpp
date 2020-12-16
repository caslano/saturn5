
#ifndef BOOST_MPL_RATIONAL_C_HPP_INCLUDED
#define BOOST_MPL_RATIONAL_C_HPP_INCLUDED

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

#include <boost/mpl/aux_/config/static_constant.hpp>

namespace boost { namespace mpl {

template<
      typename IntegerType
    , IntegerType N
    , IntegerType D = 1
    >
struct rational_c
{
    BOOST_STATIC_CONSTANT(IntegerType, numerator = N);
    BOOST_STATIC_CONSTANT(IntegerType, denominator = D);
    
    typedef rational_c<IntegerType,N,D> type;
    rational_c() {}
};

}}

#endif // BOOST_MPL_RATIONAL_C_HPP_INCLUDED

/* rational_c.hpp
r+A1/B1pT5pnruxHdMH2WBWDsRrGYHXUYw2chjVxJtbCO9EV78La8j29pJL59z3XVbm+djSeX3LfKudZZ3THLtgYg7E1dsMO2B2DsScOwF44Dnvj3dgH78O+uALDcS0OxM04GJ/DIXK+DMN9OBw/wpH4OUbidzgKizEKf8GxcryPQ28cj00xGv1wAgZgDIZgAvbBRByEeozEFLwTU/FunIb34XRcgWn4OKbjk5iBT2MmPocGPIQzsBCz8CpmYyXKNwebYC62wJnYGmeh6f0N+f2PQaQSm/c32kicsx/WwLbohu2wLbbHDuiPgdhB/V6ILLebneV2luUGynK7yHKD0B+DMQC7YjB2w4Uuprjpqy6uumj0rOJ63fjpNGKll5LUsdP+zHOJf2tJfPQAkjmOOqdYG0u99Abx1P4YSrrE33EjHYutLhppiq+OJuVJnPUa3IYFaBtvnU+ezkjcdRV+2ERhSzTHXw8bVXYMdoEqDvtwsSkW+yR/l5DsxWT3krjsGMwhlRWfXcC4QlIMf19C21jtkmJzvDZKzPY5kmuUNXbbP+r68dvDolgexuFCkimWG6Os8dw7osgjyRzX7XeB9URp47uj8Hox3p7jrHHeg9Ec670cd5COkAZf0MZ+u44vX/z3UsYVkApJRaSy4sF9o60x4dGk+RIbvtcmPvxItDVG/Cp/N5hQOlY8iHFHMQbnkFZK3PgOLCSVKMvjPIgjLSEVkApJl0ieVV11/qQBpDjSHNJK0jbSYVJRVWfMuHNwDs7BOTgH5+AcnINzcA7/K8Mtif9PnZpRUf3/fafq/2+HPEN6jFSb9DBpjxKj3tUao56ao083ZkDneFy09C9uiRPsyNri06ZmZnWWmFb1uEBzX4DSvxeris/JpdUobZwgRWGJaR3FdIbpektfeL443sccM6LqU58Hxok5edp46pnaWPYUeb7cE2tjN3xNidnrZqcMYlmalIPfDfoFW97D3A/YX18udaRczNtbT+JqJC6QyDuJL1WNIwbHEv+ba2rjThPPy/qIkbL2GZgrcTtpUuZXVeOAvFpjtGn0Kz5ddoY5Psi6zySO2Lo/LO8laPdhd/fMEGk3pLe2n0AfiXWvLvusCr7BNPk9LfvMdMg6uK+m9im9ry6zr+gI7D/eV+rYbOm30uHjuDz7sVhzvEtct+xXiUeWeL7Scdtpsk+O2sR/lqimUZ9Xxu2WfdS8N2Un5aV8fsby2RojtLsC+yCzH6NSVuxQxcXSlLcPMvuxSf+9vsnKG4P0V/dBtqCBMv7YPUkPbvb++aVzXglfH1z4ejvqeY0xRfvHxnvlvt62/zdvtHQdHXahdlkxP2XFJpW/z7KyYpakDyT5TmR+kp9NH0i5Uuc6C71wNjbCO7AL3ondcC6OwbswFudhIi7AxbgQV+AifBgXI+unjk++j+R7Sll/sOr7+wFZ/4Oy3ocwAP+JfXEljsdHZH2P4t24Sta7Gh/CNfgsrsXtmI+v4Xr8Fjfgj/gkXsat+DsWYH2JyfDB57AZPo8tcBu2w+0YhC/iRNyJebgb5+Ir+ADuwZX4Gq7Gvbge38C9+Ca+jfvwLB7Aq3hQYjDewXb4LnbFQ9gbD2M0voeT8UNchh/hSvwYn8cj+AJ+iu/iZ/gxHsUv8HM8hSfwAn6FOvbL19gQT2EQnsZueEb2I/VN8h3Fd5fsR+W42C/70Vf2YzP0wubYAltgCLbGPtgGx6EfTsJ2OAvb41z0x0XYER/ATvgPDMB/Ymdcg11xK3bDXRiCh7AHfoE98QL2wl+wN1Ymr33RDUOxJfZDfwzDQdgfh2E4jseBmIWDcRZG4BwcKvt7mOzf4bgTR+BhHIlHMRK/wlH4K44=
*/