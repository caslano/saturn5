// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_IGNORE_IPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_IGNORE_IPRIMITIVE_HPP

#include <boost/config.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/serialization/array.hpp>


namespace boost { namespace mpi { namespace detail {

/// @brief a minimal input archive, which ignores any load
///
/// This class implements a minimal input archive, probably an input archive
/// archetype, doing nothing at any load. It's use, besides acting as an
/// archetype is as a base class to implement special archives that ignore
/// loading of most types

class ignore_iprimitive
{
public:
    /// a trivial default constructor
    ignore_iprimitive()
    {}


        /// don't do anything when loading binary data
    void load_binary(void *, std::size_t )
        {}

        /// don't do anything when loading arrays
    template<class T>
    void load_array(serialization::array_wrapper<T> &, unsigned int )
    {}

    typedef is_mpi_datatype<mpl::_1> use_array_optimization;

        /// don't do anything when loading primitive types
    template<class T>
    void load(T &)
    {
    }
};

} } } // end namespace boost::mpi::detail

#endif // BOOST_MPI_DETAIL_IGNORE_IPRIMITIVE_HPP

/* ignore_iprimitive.hpp
BfZcv2/4sMY+vIdFJdNk1Lgv0tG8m/XHPpmQeX8VAGha7/D6Y5/FMh+tkj3rvPtgdcTkWXfivweQCu4hcvlMmSmukjzrZI2DUZyE2MyQeR/wcxEHbtTHQqvM3o/vm4uSgyk2EZ8uqj/lRPW7qf4MXn1yM1X1lBKOQ6pJlAHto4vSxVdbLv7zk0Nz8RDQpMV/Al19reXqu4RH/8VJobl6evR8pZP4nrPO2u7OstOHXKn7dPJGFifqq78f2KLGsCMU2AKAQuRd/YXczIV3+a5mArmbp8y8t0rywn7v7Iag/Xrz7C48CXHgRkaJznpCAN/3sSj5o2MT8emi+lNOVL+b6s/g1SendK2p4lH9nH1XPyldfa3l6r8+ITRXj68GzSuN+Z6z9jL3+GwBXD0tnfvt8frqm6IW4bkDYEvAy+97V38KN3PK3fosWMPqTck85TyNo+whGz67U870aUqEznpCAN/3uShJeGwiPl1Uf8qJ6ndT/Rm8+tyTNK80Luj9ZILef9cXRr2fXND7hKD3PxwXGsn36X2noPdTCHr/47GhuXqf3k8p6P1Ugt6PHRNGvZ9a0PtpBL3vOCaMej+toPfTCXofPTo0kk96z1dqax33Sf70Wh58kt91VGgkH1+Lmlc6gzDOn1EY53cfGRrJp3E+X+lMgs2fWbD5kx4RGsn32fxZBJs/q2Dzew4PjeSjzS+/C+/4zcudRTD8swqG3zosNOLvM/wzCYZ/ZsHwxw4Njfj7DP8MguGfUTD88UNCI/4+w28Lhn96wfBPfnBoJN9n+KcVDP90guFXB4VG8n2Gf2rB8E8jGP4pDwyN5PsG+1MKNn8qweZPfUBoJF/bfHgmnYLeTyHo/bT7h+bqfXo/uaD3CUHv7f3CqPdxQe8nE/R+hn3DqPcxQe97BL2faZ/QSL5P76OC3k8q6P0se4fm6n16P4mg992C3s+2V/j0Hp6JMM7vEsb5c+wZmqvX43ywVcKjjwqPfu49QnPxPpMfCZh8Ujnh0c+7e2iuHh/9PlGa499kNz3HD0CqtrGzKgO8wAjGDlR17EAJfqC3Aim9XPSFK1hgSTgOgWrVsBZH1BYtX7jCBGDGUQ0BZnBzfNwUcxuLTMxN+bh1ErcEHBNx62RuLYkz1WDiTA0Ady/rOm+A5S7mvMO/NTmkfbSP9tE+2kf7aB//iwPjUaem/Q+eGFc8ajOc88htAuGce2zzJ4VzzrxNaF6Af3s452xbh+bif0c45xxbhebqf0c451xbhuoV8DeGc86zRWiu/neEc87XG0aP73jDORfYPIx6P95wzoU2C43k/45wzkU2Dc3V/45wzsU2CaPejzecc4mNw6j34w3nXHKj0Ej+7wjnXHrD0Ej+7wjnXDYdGsn/HeGcy28QGsn/HeGcK64fGsn/veGcy60XGvH/HeGcK6wbGvH/HeGcK60TGvH/HeGcq6wdGsn/HeGcq60VGsn/HeGca6RCI/m/I5wztWZoJP93hHOuvUZorv53hHOuu3oY9X684ZzrrxZGvR9vOGd61dBI/u8I59xoldBc/e8I59xk5fDp/fjDOTdbKTRX/9vDObdYMTQX/zvCObdaITRX7wvnPHl5uio9oY/rRndOgbQazP9rmo4XAFqMIyDx2nktRFzADhm2IyDbR/toH+2jfbSP9jGe/VjSl3/d3o+F9mPBLfB4P5YLdtC7r+j9WE5ihHb75f1YDtyhvR/Lv3w/lsVQvve/tLkfi9OyhW4j0zcTBNLeTav4N2it/QrIDayRz0lFeq39ioQrA26LOHg3JM5VCVcG3J4Id2gVfwdX8XdgFX/aGNSBVfw/gKvkLS8pL8rKPBbYHLMm4cqA2yIO+iRxrks=
*/