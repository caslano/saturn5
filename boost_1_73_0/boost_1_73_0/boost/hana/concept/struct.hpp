/*!
@file
Defines `boost::hana::Struct`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_STRUCT_HPP
#define BOOST_HANA_CONCEPT_STRUCT_HPP

#include <boost/hana/fwd/concept/struct.hpp>

#include <boost/hana/accessors.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename S>
    struct Struct
        : hana::integral_constant<bool,
            !is_default<accessors_impl<typename tag_of<S>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_STRUCT_HPP

/* struct.hpp
sjypzciBaqfnR0gAlbc8zDtJzT8ltRIjY+bhKd8zI7EX3q38OKadafdQ2GmxbZJKBTBJB/AUCj7Fr7uv4MfvqtE/sW5yXBiu4/F6Zjyjc0X+3MFjPLOCH1jL02NRXBNn0K1qSzttJDHYnS8Dh1v/fwd17U9NCDflakOuwj77LaK8Vq+Lk88mcx9YJkkw0e+H3MSOs86t7MM2TFtn9AGoszm6HgKmlj5SUbyO+IGmw2ebGceIRp9sJ5xP+TdOT1ppP3DIlRD/qDG3u00gc6fT/+1HveSPSdEftdEKAeg2jGJiNGS5kyf2Ky9az+OTxNcAz3bOOkPqAJbT+w9KrRAH6NiO4Fe47DpDXqxWZ78yTgmo6Dug3H++38PCe1Sanw6JAvLpifB9yu/CUoGvGcbO2q+v35zXuBeG9URWO30CUPfxBEoQMYq55GD4XcTIZ/W72zWr4TJjh/vH9T+C7UxjEqiGgGkFsnEMfABqI1/kzAEdJD/jgaU/u0dPS/RxlOeXtecNdthg/cvm6Lw3uELn2u6oiuuCtCZdtodD4IfNrtP++3XzUqlQILtL92PU0KRr5fs+q/WGmjHmsI7uxBGbezfu5J5BjWl0636EJ/BNwgFaRAg84HYhjiLQ/xzP68ZeclzHxvfk9AxSBLa+
*/