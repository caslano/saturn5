/*
 [auto_generated]
 boost/numeric/odeint/external/viennacl/viennacl_resize.hpp

 [begin_description]
 Enable resizing for viennacl vector.
 [end_description]

 Copyright 2012 Denis Demidov
 Copyright 2012 Karsten Ahnert
 Copyright 2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED

#include <viennacl/vector.hpp>

#include <boost/numeric/odeint/util/is_resizeable.hpp>
#include <boost/numeric/odeint/util/resize.hpp>
#include <boost/numeric/odeint/util/same_size.hpp>

namespace boost {
namespace numeric {
namespace odeint {



/*
 * specializations for viennacl::vector< T >
 */
template< typename T >
struct is_resizeable< viennacl::vector< T > > : boost::true_type { };

template< typename T >
struct resize_impl< viennacl::vector< T > , viennacl::vector< T > >
{
    static void resize( viennacl::vector< T > &x1 , const viennacl::vector< T > &x2 )
    {
        x1.resize( x2.size() , false );
    }
};

template< typename T >
struct same_size_impl< viennacl::vector< T > , viennacl::vector< T > >
{
    static bool same_size( const viennacl::vector< T > &x1 , const viennacl::vector< T > &x2 )
    {
        return x1.size() == x2.size();
    }
};



} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_RESIZE_HPP_INCLUDED

/* viennacl_resize.hpp
zX+MKDu3qeT6T+8/1Xnh+VW9x/kVfUr8RM1/pnttufOTttz5SXS7l7Duy25nX3bHQPOiIebr87nLzIvuzpkj8zulzIuIiZ4X3evb2bDqJNNP5J8X2fzuNPOi+xFe/sHz9IOzZrIP+CBlUO3/A8kFPjlyKZ1wrWrmNdTJr0x95Vvb/ho0qXvRsf6m85D0Mxx7uPcka8LIceI3wypza5upf5HB7W2be/Zyvw3lN9/ZKPcTUrY83+LwZmzIluCvUO7jI03um/q/FZ68Xwic4fk7ttHn/H9Pkb/tXrn1Rf8C0z1t1q7ERn5L/APTvKy+GzwZ/E3egqPtkF8UT76BQJ4vKZ471d+vmD7jVYRfw+8vZh77uvpuoMv3pknv5+PzB9/wN1+EV4XmJD3ZvbSra1Aqnt/MhEdjFy7zd6nXkfWbl3bf0pLx9lhw9qWBffXfVV9d6XW3tzXou+oSRm/pxp3+zHdC99YU5GJesPlgUGB+bzu+7YlUV2+PO9fD9vAO4gsHbQ9BXv+cLPcYS5jXvxzfYDyazPOT/5YyALugeXUMdF/84E/Xz0eegRq4vK6e3tM2yznFfxCn28N/Zc5BmrTREVPUGzx51tu7TqGNqHBfqM4bPf6N+m7i374e5/Nvv94XZP8u8pZ3hfeOl2ftYAb6yHFiM46+xrcp6qgQBRo5RTT0KW/ZgoOcS4WMjlQYOorUa940otfCKbl63R1xWq97IEy9kiZ6HY0w04Jm907wLoToHfTo7/ZFWu8M59PBTFOemUPQQU4ao4PSCB2MNTrYW3QAmun/RQeg5eqgXHQAerQOKrQOGJ41wFnGnt72bIkkRsq0P8vUoL9xKnurBL3A+Vx1YfYlbnvvzcx5tQOU7kcPMd9K5rvfLtynczxaPfd+aJE7K9fbnQzyLC+SPKX9oA04nilpRy4u3oV+jRTdppKefIdJ4kOMp84s9Cfh0TDeDrycV2iHI88gVs4q+Pxx5qE7lY2rc3GJLUl8zU+p9PUqHt5DnFCaPt2nu5ltX7wtLfxmhuIzKYU+29GdQttAQr8qPA8O0kJvubR5gew9OFGR1vEL/Hhkk+yKt+lzHItcfHuiK5FOaPxS6p2krFwryQenTBKbE6LbllB8rLszJWVZo8oCobPypl0bTvT19fa5c4bjYGM1ysaOo41p89LnEb5ZFG6ntWxLelyfiDhN/3BRuC1Okrbo6D+IODs5RbX1WtPWp+p2yjCwkE29NzzFvEeKsD6f1xCWkflLGWYKHW1EztwD6+izTHp7Dm/2FM6vSIfs0IMpK+fmc7Q+qM8qYoK2C783kh/KQj/lKr+5ht5tdD5virwzfmRFMN7TJugbKJVoU2260A/7ny6I+Yk/n0Jcol31EwV+OPi+MZdzqCZlS0UFLUtXz4itXLUQj8U2HxWb37LGGVVObN7zQENP794YZp1zHwHllDkG/41Yo47yFk4J3+uqxBzrpPy6kveWRVcI0ycSMaO5DyD9J8IOIvos9dwzztKPFvjhgM8s+lA6VOlzXMGiJQuMLhCj9cC3XmzZo3UgZ/t295YgH4apkyHosSCcZnne8XJwuf36W8n6y+PPLZXqctvr6I56k5kOKieWvFaRV+YMzWtuLRqcC+tjHaxW42/GP1+L0nfhMPJkPjxTH09txdEGOVOP/tZ5ihZfxUeE8kl3YDBqd55/A87Z8+iRFOS3N/MLznXGk0l3sA37FFwHrFH8C3Q5Euk0HEFn+UdR9Bv1r5l19tHOLvR8JrWVazDq2B23z+7/f2rKUPYWM4fgoKEt/v7/gdn9/4OLwmvDKp5BO1aNCaPQP8YQ9vHHSb9f9G6NjAetZn5ZjV+bmV+2Ixzpw/V91I8=
*/