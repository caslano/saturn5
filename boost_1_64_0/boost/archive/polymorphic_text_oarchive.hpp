#ifndef BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP
#define BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// polymorphic_text_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <boost/config.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/detail/polymorphic_oarchive_route.hpp>

namespace boost {
namespace archive {

class BOOST_SYMBOL_VISIBLE polymorphic_text_oarchive :
    public detail::polymorphic_oarchive_route<text_oarchive>
{
public:
    polymorphic_text_oarchive(std::ostream & os, unsigned int flags = 0) :
        detail::polymorphic_oarchive_route<text_oarchive>(os, flags)
    {}
    ~polymorphic_text_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(
    boost::archive::polymorphic_text_oarchive
)

#endif // BOOST_ARCHIVE_POLYMORPHIC_TEXT_OARCHIVE_HPP


/* polymorphic_text_oarchive.hpp
49DSHCvvvBBmzkkl2sOOn8xW0O0tM2DGvCU6g3iwSXcyBEfi51/4VKRZoLqdXLbr90T2a9UNfkGEViJQhbimVlqZPZIuzo2kIfafwKqb6xhFCIgTWtD4hiVhbP1Wu5USAmolD17eyf5AgLx2yAJNXGbjvMS1ESNN027rOCdg41SiF8gKPfIkWR/t3ELViMhwNFpK+YTrL2bvR+C6dTE+S25zRujzSmeRHwsenQctVZNX8j/7NsBCqhgubPfaz8PXEclA96adloQ7+z0VYEFHhqfZXkXK3utKLgz16nBbYGZjx39A3DEsigoWLQbj+W9hbMlzUk9MbDZFK+vtMLdCyFGIOyyPTkwbHuakxN+HyIrZWpyD6C/VHnXA60rwIMfj0eoKNw79NuN/QeNl+8Ui+egI0LAP7kjKlaARnBhv6Ar18h6T4gFXH2ZnCO4pz/VsdA6ImdDqsH/sXefgv+vP23y2vMUhelTjND23w3++n3/QGdUG0EaFDF7IAHz0rIaSjysyU27VBrlCN03DUtH380sALKA6k1F5WiAP78iRCIRrcmAjvrwBJXG6rA==
*/