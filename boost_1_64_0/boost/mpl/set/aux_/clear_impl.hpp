
#ifndef BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/clear_fwd.hpp>
#include <boost/mpl/set/aux_/set0.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct clear_impl< aux::set_tag >
{
    template< typename Set > struct apply
    {
        typedef set0<> type;
    };
};

}}

#endif // BOOST_MPL_SET_AUX_CLEAR_IMPL_HPP_INCLUDED

/* clear_impl.hpp
Mr7gIrCIcTQHgBeDBzGephq8FDyCcTV28HJwDuNrvOCVYAvjbFoZZ3M6eA14BngteB6ffXUZeCN4PcfPbwdvBh9iHMRz4DKO2z8HdjAu4i3GRXwHtoMx2NYVoAV8BRwCrgL3BDvAceDrgWdh8brCz6HxLYMYXzQYHMS+xBRwKDgF3C3QN8hrAa8RoePW+ewbLGDfYKEhXiOF5U6WNo/XSKH+MDAeTAUHg8PBXcE9wJFgGjgWHMn9NxosBMeAJWAGOBPci3ETE8E6MBucDU7mftqH8WP7gieAucY+WvoZF2b7pnP7ZjDuoYrlSpC6WO4IluM1HabFs8WAJaAFLAUrwQPAg8EKHmcHBvzg+RMcEMaPufTjWLA/OB8swcLLZ4Z/T0zXTG38PyZbHT9nHAC+VyNWoPqPxwLocQA51XxemSEOID07OA6gsjp8HIAH+YwFCIoBqMwO/5wyO9bhQV6rsr79kLcVzylbgDLrwEXgEqR3kGJrLFImUhXSGUiP1Ij+amHChP0xi0EaxPb/AUXTK4rKxmdlKBPrYaOkQfFa2wrGdkXjEcHt9bLSigMkk9YhTJgwYcKECRMmTJgwYcKECYuOban9nyFN6W67s/W+g/S4TZLCt99TpT7qejxcetEq9AkrPcvViM+WizGWr46JmaaXQb31XPr7gJ7DLhc02LxV7nIMijv2a/FD2VztLGo7OYbj76D2wfoQZ5E+ElmsDnCarJ9G/U7q76/rVzl9M2T/TDyyzvRt1jWrGAtQaNCcFiXNVGoupWalQbPYK0dNbwIL5Br08p14RovJeqOodycLnBbQ44QCuVJ79Z/JuhnUTeeA+1mrqDujxeeXG6scjXKVW/nLKp9M1k6j9lXUdga05zn8dQ3QVZ7YZq5mNjVTOP5/jF7P+LNE+suafWzp272QPlyyqtuHMkQbFXm97midJ2L5jL4Gw3YXuF0+t1MuR5BOVDTnU7NW15yOaBaKVkdpO7uoeXgYzXyTNfVrgIcTT/romgc1yd6WStmrTi/Cw+MK3E2uKBxP+rljHfXvXkX9A5v8niZ/oRLGMsPvRSxdtam6+rnDzgCnNl03cLWtcvMSbPo26/t5DbRV6tplbpu9zFHrtXlbonVslfG5g6+F0TT72NLreDk10zp0Tdk2Vy7ghLcZ2pPITNbOonYJn/V3jq5d6uPFyO0tlm3+Jq9cqUUzmquvH9dt1L+wW7+QoVlR0dXrfAqf+3dNQDcQQjijzOHzl+CUYvZxnavvb2qP2Uw7dKfnu+wzPA4Xzi1m14Ne/3kWPutR92Wa011rc5bLjW5vyww/DgCfqbpp1H3AwqUDurK/Cg9kUzfV5HrPouYEPrNv06puze5boXwfb4VMv9/Ut3kR9U8Jp29yu0nXTOLz+K4yavrtJcrNkNn3fKP0ex9qXmbYt3yzbilCfqujVb+xfObfY4ZtVU5m+eqDIs09jvVtbaXmAwbNcvU5n0oVm38PpOtupO57EXSLms29H9Dr2Mko2QUB3ejf13ZS8waDpvpfbfGY/l/VzxWz4iXVhhqO4SLXXIfX7WqUXWgHex3K41RNP5b1/buG+jkGff3R3erjAErtpupm6O3+nTnrYXNd3heUmn5d1Le5ndqtEbXN1U3Tr4EDJdVmBnSj3256gJrtq6ipdHTwPtPs+tU10/mQv+MDmkrbxV+OisW0huicL66iZldAE7NGKuRm9Q9cHZ3tjNtFUu0zo2axw+tTRE3eTr0vqZWaa42aBU63L0rX9Q3Uc3VQr6jZof9LzD5+MvQ28CDGRgc0lRZvdNsp+vaupbZXr99CWXn8BnqRzG9z69s7a7CkWlZHkGbIBpurrW9vB7Wb9e0twEk=
*/