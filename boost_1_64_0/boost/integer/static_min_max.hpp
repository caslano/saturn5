//  Boost integer/static_min_max.hpp header file  ----------------------------//

//  (C) Copyright Daryle Walker 2001.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history. 

#ifndef BOOST_INTEGER_STATIC_MIN_MAX_HPP
#define BOOST_INTEGER_STATIC_MIN_MAX_HPP

#include <boost/integer_fwd.hpp>  // self include

namespace boost
{

//  Compile-time extrema class declarations  ---------------------------------//
//  Get the minimum or maximum of two values, signed or unsigned.

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
struct static_signed_min
{
    BOOST_STATIC_CONSTANT(static_min_max_signed_type, value = (Value1 > Value2) ? Value2 : Value1 );
};

template <static_min_max_signed_type Value1, static_min_max_signed_type Value2>
struct static_signed_max
{
    BOOST_STATIC_CONSTANT(static_min_max_signed_type, value = (Value1 < Value2) ? Value2 : Value1 );
};

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
struct static_unsigned_min
{
    BOOST_STATIC_CONSTANT(static_min_max_unsigned_type, value
     = (Value1 > Value2) ? Value2 : Value1 );
};

template <static_min_max_unsigned_type Value1, static_min_max_unsigned_type Value2>
struct static_unsigned_max
{
    BOOST_STATIC_CONSTANT(static_min_max_unsigned_type, value
     = (Value1 < Value2) ? Value2 : Value1 );
};


}  // namespace boost


#endif  // BOOST_INTEGER_STATIC_MIN_MAX_HPP

/* static_min_max.hpp
7U0H09F0Mp1NF9PVdDPdTQ/T0/QyvU0f09f0M/3NADPQDDKDzRAz1Awzw80IM9KMMqPNGDPWjDPjzQQz0Uwyk80UM9VMM9PNDDPTzDKzzRwz18wz881fZoFZaBaZxWaJWWqWmeVmhVlpVpnVZo1Za9aZv816s8FsNJvMZrPFbDXbzHazw+w0u8xus8fsNfvMfnPA/GMOmkPmsDlijppj5rg5YU6aU+a0OWPOmnPmvLlgLppL5rK5Yq6aa+a6uWFumlvmtrlj7pp75r55YB6aR+axeWKemmfmuXlhXppX5rV5Y96ad+Zf8958MB/NJ/PZfDFfzTfz3fwwP7nht13hSle5jqtd47qu5/pu4IZuxI3iRnWjudHdGO4v7n/cmG4s91f3Nze2G8f9rxvX/d2N58Z3/3ATuAndRG5iN4mb1P3TTeYmd1O4Kd1Ubmo3jZvWTeemdzO4Gd1MbmY3i5vVzeZmd3O4Od1cbm43j5vXzefmdwu4Bd1CbmG3iFvULeYWd0u4Jd1Sbmm3jFvWLeeWdyu4Fd1KbmW3ilvVreZWd2u4Nd1abm23jlvXrefWdxu4Dd1GbmO3idvUbeY2d1u4Ld1Wbmu3jdvWbee2dzu4Hd1Obme3i9vV7eZ2d3u4Pd1ebm+3j9vX7ef2dwe4A91B7mB3iDvUHeYOd0e4I91R7mh3jDvWHeeOdye4E91J7mR3ijvVneZOd2e4M91Z7mx3jjvXnefOd/9yF7gL3UXuYneJu9Rd5i53V7gr3VXuaneNu9Zd5/7trnc3uBvdTe5md4u71d3mbnd3uDvdXe5ud4+7193n7ncPuP+4B91D7mH3iHvUPeYed0+4J91T7mn3jHvWPeeedy+4F91L7mX3invVveZed2+4N91b7m33jnvXvefedx+4D91H7mP3ifvUfeY+d1+4L91X7mv3jfvWfef+6753P7gf3U/uZ/eL+9X95n53f7g/edxje8KTnvIcT3vGcz3P873AC72IF8WL6kXzonsxvF+8/3gxvVjer95vXmwvjvdfL673uxfPi+/94SXwEnqJvMReEi+p96eXzEvupfBSeqm81F4aL62XzkvvZfAyepm8zF4WL6uXzcvu5fByerm83F4eL6+Xz8vvFfAKeoW8wl4Rr6hXzCvulfBKeqW80l4Zr6xXzivvVfAqepW8yl4Vr6pXzavu1fBqerW82l4dr65Xz6vvNfAaeo28xl4Tr6nXzGvutfBaeq281l4br63XzmvvdfA6ep28zl4Xr6vXzevu9fB6er283l4fr6/Xz+vvDfAGeoO8wd4Qb6g3zBvujfBGeqO80d4Yb6w3zhvvTfAmepO8yd4Ub6o3zZvuzfBmerO82d4cb643z5vv/eUt8BZ6i7zF3hJvqbfMW+6t8FZ6q7zV3hpvrbfO+9tb723wNnqbvM3eFm+rt83b7u3wdnq7vN3eHm+vt8/b7x3w/vEOeoe8w94R76h3zDvunfBOeqe8094Z76x3zjvvXfAuepe8y94V76p3zbvu3fBuere8294d7653z7vvPfAeeo+8x94T76n3zHvuvfBeeq+8194b7633zvvXe+998D56n7zP3hfvq/fN++798H7ysM/2hS995Tu+9o3v+p7v+4Ef+hE/ih/Vj+ZH92P4v/j/8WP6sfxf/d/82H4c/79+XP93P54f3//DT+An9BP5if0kflL/Tz+Zn9xP4af0U/mp/TR+Wj+dn97P4Gf0M/mZ/Sx+Vj+bn93P4ef0c/m5/Tx+Xj+fn98v4Bf0C/mF/SJ+Ub+YX9wv4Zf0S/ml/TJ+Wb+cX96v4Ff0K/mV/Sp+Vb+aX92v4df0a/m1/Tp+Xb+eX99v4Df0G/mN/SY=
*/