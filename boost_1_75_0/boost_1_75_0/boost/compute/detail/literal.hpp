//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_LITERAL_HPP
#define BOOST_COMPUTE_DETAIL_LITERAL_HPP

#include <iomanip>
#include <limits>
#include <sstream>

#include <boost/type_traits/is_same.hpp>

#include <boost/compute/types/fundamental.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
std::string make_literal(T x)
{
    std::stringstream s;
    s << std::setprecision(
#ifndef BOOST_NO_CXX11_NUMERIC_LIMITS
            std::numeric_limits<T>::max_digits10
#else
            // We don't have max_digits10, so add 3 other digits (this is what is required for
            // float, and is one more than required for double).
            3 + std::numeric_limits<T>::digits10
#endif
            )
      << std::scientific
      << x;

    if(boost::is_same<T, float>::value || boost::is_same<T, float_>::value){
        s << "f";
    }

    return s.str();
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_LITERAL_HPP

/* literal.hpp
F02z4ICbeU7RFJaIKSyKfhep0pEz1EbdWQzTjYtaO7Iya7UsA1mx9ImFv4piN6ldrFlVnrUMUV6smaLdrmzDnqVawsVWKqdC4mE5vlapo1PV9LdEdRWcEhXPmiOzR53WvpAaNK/nK7AC+YWQ/qR85QzUVM5AZd2tyr7cb6lusYYiy1Xl80/lJVf2/FPV4v3OQt1i5eWgjv9wu/KS+fWbU8ritgPff9CVcC0kq65lkKpaxCWHqiWWn81VMm/OMV/d8qXUS9F/nrxOmsm7W+NVNyREeY28X5SY/jnHXkpn7IGrZa69rLkfOntlo14NA/r55yp36Nz30ooXziWVch+eLf5hJglzn+MtnjJXtnycpHTu4GfxoZmyYRvD++5H8k63uDhuHSpy4jJLfxMSADYsydPEfnJEQ7J69D0tWD0EypKvuonaypvI9yppCjNT1pR4OgORpheFyDyIBSEfNoW7URQxR8a1hHC96Ft55w7ScvIrGi2X1pykHfmtohZSL0ip6hYaD67a/IPpWtXi+MOgPzJLqBxl4cqLFWzx875++aFXw1ytbX1r5VXwWi3hunZrWrl0AzaHhsnx82rU7iSaPJ/Sua/+Fo+US2NHw9zXEou/C5ZtxkbO/nBCkA1JNXrTY6DKOYFYBKYrFCzEak/UrweoXIvJDHM5TkEtLmo9HVyvqgrFDx0NVBRrrppz4vJ0Hyhzi7rQMNnAhB5W
*/