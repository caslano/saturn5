
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_BARRIER_H
#define BOOST_FIBERS_BARRIER_H

#include <cstddef>

#include <boost/config.hpp>

#include <boost/fiber/condition_variable.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/mutex.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL barrier {
private:
    std::size_t         initial_;
    std::size_t         current_;
    std::size_t         cycle_{ 0 };
    mutex               mtx_{};
    condition_variable  cond_{};

public:
    explicit barrier( std::size_t);

    barrier( barrier const&) = delete;
    barrier & operator=( barrier const&) = delete;

    bool wait();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_BARRIER_H

/* barrier.hpp
4LCWm9eZEs9+hDRbXfFxfJTgX/qCQm0AbLyjPQzQC7B8HVW+jrV85Fda+acx/Ilo34rNFEkszpEnE9aKswQhtQtYou+qcUahvxJ0GB7cE6SJbT0RgijLKceleDg4xrT1+wfgqSAxrehFsuM9lE83x2VefRFnhmIZlbzlweZCnug1jOZiBd/pqGOKueKPlcl1Tcky0WWX6Kg+ER/soe0+qoFYwbvS14/1xVccfVXU11qwLfXHSLBwEi0HZx8q9RkMdH8bys0Mys0D/OSwHCsaSywD3ggn/bvEiY18JsSN0/5nqxraNJcVvolqTPnku9iop9l1sjIQjGtmXVoJ0jkmV6LcGydRDK20ondpIK2Y6pGKnqEPkaLnfMjOq4O//FGIpeah+fk8E2Sff2QOv3+3QLPPp+ncwuq/kW1/+8yW6PVx/aeZhFYYyoAaDLCLT4jG6IdPpDhmyknxUAS9LKYH7Qu8214PkVVMgTJs6o/T8Cz+opmY7P+9iD+YVtSIoqxdk0czccRlyjWqQEaDz5ZOUufiyu2hYLad81iwWsIr9+fj5Mpd8b0LPj+ZYfUpecYF5fHkhV2dbLziRp0E/d7gJs0yVtwYOAWl1dy8xsUA4KAC90IBOOE7OWGWW2tCXKx8tFgpMRhvk6nkMGvJYR5VcpgsOYxKdnGLr3701UaHSy72sK3Crmz5ECtG5eV2yqJf0JGi/bgnFcNfQkwkhS5mwUTpjLBbYE9E/d1edr22+iNgIbG0xVdRzii+X3PsIVVfT+qu26eQqs/UXRfeKqMa8zNRiIgPEBySLsdo8rlUyRmBYevMi8WTQJ6uWuq0IVqt/CUtRCMYA4ebFE0Up4Ijw6dNlvqie5WiiQgOu0rM4X6gilO6pmR+VjWZYC++XCqQhvPDqskBRVMm09gwUJY7V4amugI40qZGnoe/cEGGTQZnkL83lZ5iKY1vJ15JM6bjZBUP7uD9cuDrXgcP3fW/6XUQ/h+vr8HxH+4w3wpa3idJZysTko2HHq9ksYn3DFEqYD/iM4aPo/uqtKIR1IGjctSLmefcR4rN8yE7T7wLNJImTloOTpypODrv4onjGkulaV+pvZ261TT4kdtt7Is3H6sks+Dq4UcQPC0NGopcRhHyPpBxNGceBDw1odsYdhMkkwzmlHr2FHKTaAlfREeKKMlQhDhAkmHGH109nU+IcXKHcuOHG09YkfHip5TEOL30oBuuoOvDDhi6hKfaEi1Cl6BIdRhFHW6+w7/mrkb+zzfLPywpVHEFLuwzKSRvoRSBso31sFHz+7mplNYW0kgKej7XfMGIc0cTosi9TKz1TeVgSaZEPFdywRRKe5El7maclUpZqM7wxwaweCl5LlusFleqYyqOo6j10erDgZuEkmnPiDxra3/fZ5pof3IVpOHtoUVg5BDpXWYdzaEGMmHmMfzxVPMYJlOLxI7UAA3iFwNCGEc4viin1HBXlempKrOFfSYRh1QYtDUesel2ruV1qFZsWrNtGknenPAoOAXTbb/SCWbhsEzEYZnMpUbMxluWSDlKEtlsJxPeWuEIuMmcnAbJ/BpyVMU2+Cdg8MFIr1lMd/uZ7MHq5bwjIH0GxjEjNuB2MTCGOXmfnuzl5GI92cfJT+nJmZx8NyZzNF9Ozvu58td5SNl2vA/I1cc7r+n4vIdxvvQ4qUn8Fq9o3Cl0v39ith5HQSrsWpBy56Jb+IiQh1tnB3Ed8Huh9SqF32KdWAa3qjzNpPjs1i/5fcYPF9BTMUIPezbh/jTbBvc4wO2/weg8zBz1K0GLk7neDq4XwiWQEo5Y8brFavpjtjQfksyl+BvQhho5DmtR630/DHlAHJULJvOCkkqeeCVxQgg=
*/