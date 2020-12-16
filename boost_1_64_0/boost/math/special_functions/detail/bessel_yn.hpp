//  Copyright (c) 2006 Xiaogang Zhang
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MATH_BESSEL_YN_HPP
#define BOOST_MATH_BESSEL_YN_HPP

#ifdef _MSC_VER
#pragma once
#endif

#include <boost/math/special_functions/detail/bessel_y0.hpp>
#include <boost/math/special_functions/detail/bessel_y1.hpp>
#include <boost/math/special_functions/detail/bessel_jy_series.hpp>
#include <boost/math/policies/error_handling.hpp>

// Bessel function of the second kind of integer order
// Y_n(z) is the dominant solution, forward recurrence always OK (though unstable)

namespace boost { namespace math { namespace detail{

template <typename T, typename Policy>
T bessel_yn(int n, T x, const Policy& pol)
{
    BOOST_MATH_STD_USING
    T value, factor, current, prev;

    using namespace boost::math::tools;

    static const char* function = "boost::math::bessel_yn<%1%>(%1%,%1%)";

    if ((x == 0) && (n == 0))
    {
       return -policies::raise_overflow_error<T>(function, 0, pol);
    }
    if (x <= 0)
    {
       return policies::raise_domain_error<T>(function,
            "Got x = %1%, but x must be > 0, complex result not supported.", x, pol);
    }

    //
    // Reflection comes first:
    //
    if (n < 0)
    {
        factor = static_cast<T>((n & 0x1) ? -1 : 1);  // Y_{-n}(z) = (-1)^n Y_n(z)
        n = -n;
    }
    else
    {
        factor = 1;
    }
    if(x < policies::get_epsilon<T, Policy>())
    {
       T scale = 1;
       value = bessel_yn_small_z(n, x, &scale, pol);
       if(tools::max_value<T>() * fabs(scale) < fabs(value))
          return boost::math::sign(scale) * boost::math::sign(value) * policies::raise_overflow_error<T>(function, 0, pol);
       value /= scale;
    }
    else if(asymptotic_bessel_large_x_limit(n, x))
    {
       value = factor * asymptotic_bessel_y_large_x_2(static_cast<T>(abs(n)), x);
    }
    else if (n == 0)
    {
        value = bessel_y0(x, pol);
    }
    else if (n == 1)
    {
        value = factor * bessel_y1(x, pol);
    }
    else
    {
       prev = bessel_y0(x, pol);
       current = bessel_y1(x, pol);
       int k = 1;
       BOOST_ASSERT(k < n);
       policies::check_series_iterations<T>("boost::math::bessel_y_n<%1%>(%1%,%1%)", n, pol);
       T mult = 2 * k / x;
       value = mult * current - prev;
       prev = current;
       current = value;
       ++k;
       if((mult > 1) && (fabs(current) > 1))
       {
          prev /= current;
          factor /= current;
          value /= current;
          current = 1;
       }
       while(k < n)
       {
           mult = 2 * k / x;
           value = mult * current - prev;
           prev = current;
           current = value;
           ++k;
       }
       if(fabs(tools::max_value<T>() * factor) < fabs(value))
          return sign(value) * sign(factor) * policies::raise_overflow_error<T>(function, 0, pol);
       value /= factor;
    }
    return value;
}

}}} // namespaces

#endif // BOOST_MATH_BESSEL_YN_HPP


/* bessel_yn.hpp
PByf2jYR68yCi0coaDRJiuMdo97zjP4Ll/SC29L+b3wop/V+3YnxfOhTQ+4wCXJjGueXW0zlUFVl/SKfykWxei/UkyfChDNmbSIp0+s/nBHALIKvvpU+vBP7C7cPIRhcJ7w0TFQdN4+5vOEY5q0TdW+hebHeqrN+1pga61YSAJBImmL/k3dxuXpyKH49d1eXZ00O11nXjro8VzjyzaaOlgmd607yaVt6IjoCb4EcoVPqDtot7dsxqVxBPIQRB45d3hXOF4IcOHXhdItBDhy6cDrlEGfkzOWsXpiDsmTcuk+Qg3e4UW8j+tAupPJQd+ENiqk81F94/XIqL26DOt+XzkO5crfkvVJ5NKDznZVwSKlchOLYIIYhyJ1JaVwZeBJ73Lx7Gtd3Ljfne1PHP0N0uSMj3E5qo8Szg2AbuX3S//cL8qhtUk9zjxDPa5d8PyLYLrtNPD7e3uau1TF5VmdxIktHMfOBamp8UPBwqIbg+ZKLQxUVPllx8VgFBe8sezjylzvnBvdyceoOfd/eXpfjx5CRw3FiSNlzu4nLoxhN64kts9Q4M1O0eKlxZmTLMDXOLNqyTI0ze7ZMU+PMzL3DPJGx6Fx0vzQuqTO4ia0W75HC9VRabGByaewzRJd78idvmsan6ZoeZ5y+9+Npmf9s+e2k9smdQ10vP4qBweF9aYfjx8AyJ+vbXC/GNfss3ItxJ30csYIfk2aOWbz/GsPmbH5aDCvrL0F+euDEPsquP8W+0n89V598PZIzUI4eufrDNmzX1Y3BVlkftK3jFWgdeXDMWUzjwNxUXt1SCg9mzvWvhDlk4lx/s5LGQ5nKTqJ7h3li4nKX1eB+YS6bALiJjffvEeb6XSM+pLc05hmi87ijxy3ZR2iwLKn9c3NYUMLR9kaj3vDe3whxzsQk9Z5cNeHQFsGQZUpcD8bpeXIvvP9z/yBeWBedxP4Nc2LdtzPS58BrzMOkgGpi1HmvNR8v1BDrQxuSsrLrKZyhcKSv83WLh8mkkBcbpcZ5/b04i0uzGXV2IooYx8NW82TsmrsIc+AUhp9vJA50RGLXyZMXdXgnZw8LUfayP23zDs0cZxb3/18uZnNmmcKczB+22ZwTR/x8HrHd4uDC84Qja0p/dji45DvUvsGlL7B5uEQ4xMvf2OHRRVLEFDvY5/AWmCN3KGUu1By4Lp9TPGJz4Lo8OZgHuhxf5r2FHRZnWjpPZIX4WXHIyP22ZU/bPPyP3zdzu2zO3fMeZ/IKuy0Ozo17nNxvbQ7uy/f6OLv94jbn8LzVx7y+fzebl58+5uXV/4fDuevh+T0TIgOOIfOX8Hi3YprwTNXmxcNFqG6Zrzi8QD/nd1zK4uDOac9u2vexOSdm/H4uXu8yFueet8zd+u57/TZ2vnMpj6frzv7R0QeiyLq84FGlcoodKLe94ePkQOVuq1SOfb95sWnzsFpIDlSdq0jlIENZX4OHH8ejglW82FP8eoStKmxENU6JnLqbgkNClJeymTCOu4RMjWX18DBnOZL71M0Z4WzIeCV3yp9lvIE7T7F3aw0Ncq/9uYRHE1QaYnhM8PDWKjIsE03mgcJDQGfFBPJtZ5sTC0782/kEQ3CiNQzPs2x/fckhZ35++J3WwszUcHt/hXXQw+13dQY+jkUxNWf8DeMz8/MnpucK89NzM7ieDKVo2ebSeHFpipdP4Y1KFdlFwsNbK7N4V35UPxRrWJ/DHCpS8uql8FAkyyEzP/LbcNeHzmNHdqGOD2siD45F78H44Zn8nVFv3M82uiCVXj1R3029Z4iLvfPCeh07jVjGV98tDXEpGNZzxmyYJ+f5kCePUweDXJwYEZm0DwU5WIOQNk8Gy6RbjqCHRpU=
*/