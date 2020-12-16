#ifndef BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_binary_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_binary_oarchive :
    public detail::polymorphic_oarchive_route<binary_oarchive>
{
public:
    polymorphic_binary_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<binary_oarchive>(os, flags)
    {}
    ~polymorphic_binary_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_binary_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_BINARY_OARCHIVE_HPP


/* polymorphic_binary_oarchive.hpp
1s5z5CLube6KzUGWiR00TGbl0nbJle673OE7XEWHUzwJRYsCKZ4YHhyXQlikQOJ5n8bb1FA48fjrFdKeb99t6uqNd+DWkTllaWESyFiOF3DVh/G28izqlv1NBBIvQoJg2wDcuf38V8P7hDe5KDPFW+jSQMzGY+yJGDvQpik73OHvBRKf3Ee4sieXR+8f7M486umYD8VUUl5/w51clZdZ4d0POy7u7z4u7MUzNNEuQVmQOH2fOdFfzSBP4nlOQYfjHLQ9WowLgRg8zfB/gieW8QDq21EFw0NPpO9wktefXRphy6xEZi8zc0RpBKK4bsoF2ErJT97hToYH8915Bz+Ytgb3OSLcRVGKczrZOjlyMiq9GyExzCuNC8/L3Lx4L9dPq2j0PH55P5vdalgrkLFCDAInfE16UnMnScTBnNJlduADbrzXu/R3mTGUgMkOiPf2dA9Y4PC68H+CN9N3NMzTtvgDAAW81p/o5J6Mt3yseqs9aADgot0kAheLn3NlfuKNlx0eX8Zv9Sjy3qb/PJF7zVmj4rlPsXbYQR7r7fJYbyL4XMz9eHrxQ62Co780kR/qVxowx2Ts1b9366n7qPfvZl7LHHAWfLrdueJZJOIbOHf4P8yTzv93xBmx43amIdNUQiTdc34vHwZDrlbCeipmTeh9lEDtUCS44GWqEH8L64MFW6PBQsbH5m2pP5ofj54iuapVNe/+NQqCzEFHR9AXIEibQGLv3UpevoOwggX2Xs7iN/hbGL6tM1yVlGcw5jU2nK/6z+9zHW+v0sJenPCFSmiPX+nhv4Bh+MOSq1Amka9pXT3AosEp0NCZ4sTq9YPWI5Se8pI3ucO3+GMGRCNKxpQKNj0GoJr8UbwtlCIhr2+9xH6/rkeLIH9ZEQYZN1kW+bDWhmJ23x0NLZTHTIRkdBQwjzADIYkkhCSCkJLaCMkFuELQY7xbMJH0HNoExkZU/Igl0HD0zySEBJYIdfGRJ66oh48UoLwVHwmrtuIjqXcJhhF4NIiPUHrOlYKPOFFbBZ5QCzr9BCNnNu6j8N9Si776hBD8L0t+2R9C8L8s+Z1C1L/dkr8gRH2vJb/P1BD8P0v++vEh+H+W/IwQ/LVES/4h8AIa8L9+YDUXhTMatpz8Dlhx1K2GA5fBd4lqx+zpKlLJFtIejNZ9K3E24ohOQgF9FHLxfdwddi7c9hHGrStuMVpJVa0kT5cYJvhOkv0/3M7VOqlqn/OTQN4+s1iS1c340p60RNAYY/vS4rE7pcU9lytlO/PUuE+YA9M4erxKE7PbtM/gVICkPFngOuaXPNLlLuTSb7f+evEBocC/cWlf6LHjhAJ5HSMTmuMaMFWUNhwrzhcgB9HdB2Z54vMHTIHN5UAkDMzyzmTfqdtftVO/TVYGVZNeYc25D+m6/Gks8SuW9BD2SSJaJh6im7ovXUFjYjPrLP2+MGJvkEzJu8mtZAcoXFwj3fs7qWpbalebhmrU41akCD0wcKzQA71VoMEsNgL4Bw2xAgzqyMvxvLHMCYGYBmA1PJ2JO3EmC5hIyF39pmJYODhpJVPz+un38ZKYTsuTxWm5i73eEENW4qGX2ElXSoKblbjwRY21JNzYgernVfPHWNR7t8XJ65HbycnrQj1hnunk9crJhpPXqybXMWLKmVzPyevVD+Gwd6LGO/DYf4+S5fdI4/dR48NX6i94D8iy6Dsn0bfVPCo9eoIku41x6mRvBals5QIitD7ECFZNZpJLv2EZ7SELUqrqMRJOMIjrv/FzovR/1qgLzYs2yUHxv1cZih55H8YZqqeFyAFFIoQJWXUn3hZtw10ENcJht/Vc7Sc99h/CeSTeZMGArp5LacvG83mg3Sq/Q7Y=
*/