//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

#include <boost/compute/type_traits/type_name.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
struct capture_traits
{
    static std::string type_name()
    {
        return ::boost::compute::type_name<T>();
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_DETAIL_CAPTURE_TRAITS_HPP

/* capture_traits.hpp
ByMYjnyYMcVVAC+H47OLF2N4Obi6GpyPr+HiZxicX1u0X4fnJzQFnPgk4NtKoiJ+Cbyoco7JmnaHK+wVS+jMqVTU9CP/h/C7g3Dff+p51B64vBgNf4e/F11KKdW8wN5Ta54w6sgRrE7BfziDh1T8h9d+ALmIWW6OG9slMtm2/cDIqyQvNRwenp0OTk6vvHAy8XeYocP7vERZ3YFtmVp5/Q+lslJ1D7bb1Oput08J1j0IJ41obVSLZGulW437CqWtXgePH/9I6mVb+Gn5mnysX23Qr1cxB/TVQuZwvkLL2pntTNEc3g5EzSF9sa7d0bovVjcHeKfAtfh3KALjMxq7meltXy2LmcgVfAu+VTIffPfRWgi3jpy174WjMzgf/HbqfYgzmfShbQ0OhmY6FbJgZg6t/8eotsIF1bFiN0jboGki1W3+QE/NHMUrb6ikmPNkvTuryCBDZlptOqrCpok0flq5BZNKbzE0O2Y/ctEvmPJIkqVI6thsF02fIVeiwDW1XtD6JAk3obG8FSjNcIzqieeN78Vm85dviMhPkAYippYkPulOgaQv5Q3ZMu0pXsZoH9dgpYASF7Q0Ca5kYYawkFyTRLl93CYilaAFoh1xdCanG9TacEgsxLwpJKPl0bWkXbAJ5GwrfsufIjOf
*/