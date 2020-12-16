// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016.
// Modifications copyright (c) 2015-2016, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_IMPLEMENTATION_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_IMPLEMENTATION_HPP

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/is_empty.hpp>

#include <boost/geometry/algorithms/detail/envelope/areal.hpp>
#include <boost/geometry/algorithms/detail/envelope/box.hpp>
#include <boost/geometry/algorithms/detail/envelope/linear.hpp>
#include <boost/geometry/algorithms/detail/envelope/multipoint.hpp>
#include <boost/geometry/algorithms/detail/envelope/point.hpp>
#include <boost/geometry/algorithms/detail/envelope/range.hpp>
#include <boost/geometry/algorithms/detail/envelope/segment.hpp>

#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_ENVELOPE_IMPLEMENTATION_HPP

/* implementation.hpp
TBsicnn7jB0vBiHPVf2st9BltH6es+JVP5MduhcsdIixrFYb60WXhggovJAsJtYJjxR+3rAAXu4/teZgexYE3pvDM0G8WrBH87KNplsSeTwJ0mT84zxn4M1xXjVozHFeCNBIhqk+3gBfViugAc4Knho0ek8hT9ffcvaY4oXCvePh1Nxc3LsuLtXt4dx5ve/i5D6nuakPH1hougM8+shPY9WrT4I0qh+PB58FaGBGc5fGoy/AN3cJsEal4RPoXawk4eOgbhO+Gi7xCQpJuj/4WsKd+UT4DPn6bHH7XOp2qsbsGAZNSSzvmBvpG7wx5gACIODamEqeA8Fl1yYzkViyM9UR78TfhAqwP53NcMb0T5da7c9mI6Tu0kryk0FTvWr9gw18V45guIPfcgS8S/UikZgBa8YsjA7AursSPYIPBjzbOlfA9T4SXRLs0m4jYJlIlwxdWZ8PLj1gtLkjHuw/ieqLjnT+jxI8Tkd7qITFA36ONuB6Uzk4bXKx01JgQzej5gR+mBNPRR3YMg0Wc2DVAlZYXJFsPjAeM2Osm6xyi7tykWk1Fb54NBtXchsyzI9vTcfj+vpbA+274ms9m9EOLorn0/AergMceyUvriUPriun71Erbo3A5Rkvk8NldVwheyEZy8az5l64x8fTyUG/VlfeREGGqkBV7ULh3BQNvs1Cg4PTabpH2GiweIXpg9Bny9wftOrDWnfMegaTWahQYXxUIG6Us3HCRRUHrnPak+pWiSpCabUkxNq62yOn38dBV49+L6fNSEfnr3dgkzXYgw6sXYM958CiAxTsZQkj1wRWGH8ypI2wJxhnPWGNFf85Qo/rRFO1V940cJFYdl3IsyHvuHiBKnCO2XR8nSnDp63698EIi4wi8XV6zPJRHho9xv04QIMIlzZVzvXwn45AfrNn7CmLPd4o3hifW/GMoPHzPtdX52rfnDySyg13/aywA/huPJ5nz7/Jwdgomk9A4AIWz8TIcqJpDz5QwtsZ00c/OAfHV7bgEbU8bwsJF2frzFPJbSsJ9xbozv195kLpPxf650bOIJ8AjtVKVMHy7kq0GDb8n1Z5jxjpl5PcttQetNxqpJUm1hGPdvlszigbHdGavsdHB2hELNcSb412d3A8Fc2s1vVsbIBWxGvNvZFazgS8/sYZNGZ/0x3a8ZugFQGEniN8H3rMfaQ5w7l0rD0iHbviy07gaWUumXqWzr8f5KPD4el58C556DgvSwnn2a+xU92Zdo1uWj469kx3XOncJHwKdLklCnejx0G7CFxWzmC0JuuMpEaESt93B646UfPgTFfBI2WN4dKG8kWR8pr6SGWtG9/Mpe2Jm2GZsM1jHNu8wIFVFAErbB+I9N9im7+y2WZVI/EKI+CCdRFVDPH28cKRGo56Umur4mnlMB0H+zR+z9DbYfT1uGiRD4eSiLkEfahWcBkfrLd4RRb2UrDGEiis6Pq3WB8Xix2spcg5BuotWpFlvC1fEX2J+ftylRYNp/SshvFFdwXWOogxbHLeaphNzg3eGjlLQBd1f9Low7X5+LfMh0tx8wEmrumOd8Xi3rqX+2jgsdb3yiCuWNXJVuk4shNf74XpfHc2ZqsLjvDxYmJA5/HM5Xo9cGJQ78Er1Vc++oCRATzsdPTBjPmg0WuEE4M6C17VBi16Cz6ouhODusjqv2XNT6RmFh2aMMxW042ybhHMCBWJafCYC08xkcLk1kM22dob9NlYZWveNVKPFWVTPd9sd/Auak6/59EZz7ZHOhLNttrhFOtcDmGs8LL6SP2S8ApZEiF2mKF05DAbPoJNiWY8+R0RpAnk/0cZeOFg1Ri/sOKFlqg+xo0waLDHCn+00QfC1dZxrBU=
*/