//
// detail/dependent_type.hpp
// ~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Copyright (c) 2003-2020 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP
#define BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP

#if defined(_MSC_VER) && (_MSC_VER >= 1200)
# pragma once
#endif // defined(_MSC_VER) && (_MSC_VER >= 1200)

#include <boost/asio/detail/config.hpp>

#include <boost/asio/detail/push_options.hpp>

namespace boost {
namespace asio {
namespace detail {

template <typename DependsOn, typename T>
struct dependent_type
{
  typedef T type;
};

} // namespace detail
} // namespace asio
} // namespace boost

#include <boost/asio/detail/pop_options.hpp>

#endif // BOOST_ASIO_DETAIL_DEPENDENT_TYPE_HPP

/* dependent_type.hpp
MxxwRxJtX006yG81cOqpNYplnZozkkapkeLScNUId9QqaaaDIIBBcWyfNriwKZdJbK9puGOaNb6Dh7vL8DfgzAPMiZelfPxQYd/o6kL/IE50I8PpI0EOiVXLpuCR4DaMjA8X8Ppd/Pqcy0Cjcpa1c9l5xleODvT2p89wwaWxLFkyTAHs5bATMgXZZ7xyhbm1wfL5AnAbY2u4PHpv0QiS5VBm8+16Add17VqCfHVgNbeO6HZatnJEncZMtQTXS7uJIz/smewGTBYrvcmWZubYIsyuGau0y87BJYsyso41g+1cAga3s8MY1U0Wh5vCMZO8Tpq+P2rxS3N5h9WX/E0GA1eDaVOy1bQKuyxgc2GPlgWW7Vw2Cc5apmtzWbcE7iskt6QTCj2pZNN5cnDRsy8JOeWM/JQxxi7r9nfKGGOH7VgijnIWCc6uA5PLYppY7/Hgk2Zdt5my3MZ4Usii0IBhlngRxoPI2OGE10ETwYzhG8gSPfmgMQ6HGYRhShDasFtH71uus2iJ6zCuHAZ2Ss7nOI3SRDzgJpNEWJttzMbnU0276oLNUQWsO8og7VEGZY0yGGc8wVnj2cib1tb0TS4lF0utdrEWPmttS5Ab59VK2eIxXaysevBdslBu1POzh13tLKlGb8eYGbArcKh9zMZdXw4in40eWEzJTo6MPRicM4PqGbglz7VSDcZXD6/Aq0zDo9FLIgaBibMAC9MUtsdYcrOicLeS7j2wa6k4UpeFT8RYt5S2gQayDLaDRo7Z9kQNSyIOwDGLynQqvAcbPz0JFrsYXHHeUBhY17s63ZTn8ag6uorRSYhzaNCuNDuKoTjM3Wh2qr2A22W5MiidRwfJmbiTsLNC8bNIxSaOLhmr5+ZMFYOVa3gs1LiloMl0Srp8LpuTFwE1rw64jkXgHoWTyyUa+SqlNyz64+9VlDbiYn8XkNEz4Oheic1kcfx2D2rDzhVbs6jSVJxovjAE0HqhURiEicuVhY4OFZCpIi7tkg07b5LuzoKeBGj9JtMS4T3mSnFjaib8LQToaxkIG35bR7dJMFmc3FQM07N28b1x4ywzCk0cYTFDk7YxXHY6Mju0yXKIcxaLW/DZYYnfw8Ftux7kD0wubWKLod3Kwqr+5Xi4pbCopwtgGM+Hj42tRjK8JYm/kSppIrnrqDHuMKJqENnH4QHDw0sbm3lITQhfwm4e/QCLYFTBX/3UB8QGRnvw6xauaXWgsVhAEkUgvH6Lp8FTiLrS9OzeU3E6fFij0L1kQYzD5y3m7kGbePGSEDunSrDZ/VYM41d/gcJsBSw5SOvHnFOAvAvSF61NFmHeyIfne5KHBrK0aVjNx9uRLJUMhmZsQ7sCPcJahopbKYFonaaD3N6A7TZ7E+T3JujQm8DtTeD0JujUm2Ce3gS6N0lH8EcPrXlLPiK0JwWpJyGd6xmB4Rmm1kHWTYCMctgq4W/mYVSg+FlUpKJezHmVBuhEmp7FLLcgqkHmQTz0hpVvQ+ZNUptERQ4Fm4AbG1ndu2F8YP14XE4TKGNA5O/Sl0wKQ73xa7Y2iXI2ZZW1i5klrMzRIMxGrjbWq8MX0mODUXcTEM6xFKCeNB3EgmjIkTAjGXA5urUUpZObRxHCEPWv7EIybcx0ShC5wQx8p2gGUTacpVjXl7ghQF6EAp0NUSnW4jRIpUCr74Ypi07MnRuowNsRyeC0Vc3wYjLoKYxjcLktRJZzsmKwchgMdKttlddDqYMbQF50A22HN011MEKQY4TANULgGCHIMQK4/BZcIwSOEYIORghMI6D/yd+Mu8TxBSkdWgDMYBkz2k/TcBmBfD8NTD81rQOUzZx2yepJFD2RyIZPwDR+Iqn7qGOpRro=
*/