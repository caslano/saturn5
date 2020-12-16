// Boost.Geometry

// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_SELECT_SEQUENCE_ELEMENT
#define BOOST_GEOMETRY_UTIL_SELECT_SEQUENCE_ELEMENT


#include <boost/mpl/if.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/size.hpp>

#include <boost/type_traits/is_same.hpp>

#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

namespace util
{

template <typename Curr, typename Next>
struct pred_more_precise_coordinate_type
{
    typedef typename geometry::coordinate_type<Curr>::type curr_coord_t;
    typedef typename geometry::coordinate_type<Next>::type next_coord_t;

    typedef typename boost::mpl::if_c
        <
            boost::is_same
                <
                    curr_coord_t,
                    typename select_most_precise
                        <
                            curr_coord_t,
                            next_coord_t
                        >::type
                >::value,
            Curr,
            Next
        >::type type;
};

template
<
    typename Seq,
    template<typename, typename> class Pred = pred_more_precise_coordinate_type,
    int I = 0,
    int N = boost::mpl::size<Seq>::value
>
struct select_sequence_element
{
    typedef typename boost::mpl::at<Seq, boost::mpl::int_<I> >::type curr_t;
    typedef typename select_sequence_element<Seq, Pred, I+1, N>::type next_t;

    typedef typename Pred<curr_t, next_t>::type type;
};

template <typename Seq, template<typename, typename> class Pred, int N>
struct select_sequence_element<Seq, Pred, N, N>
{
    typedef typename boost::mpl::at<Seq, boost::mpl::int_<N-1> >::type type;
};

} // namespace util

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_UTIL_SELECT_SEQUENCE_ELEMENT

/* select_sequence_element.hpp
h3K/mqDGLTlepZNqWb6E82IDx8FJ+zzM+beK++Tp3Fc/wHuLAr4PPJfvxfF3u11833Ebx+HQF5xHo1k/08suNa8GcDx20592JbPcevoD90+nZ3Hcz9L/X2I/uX75LaBefhyHTbzf2c+428r1y8HzHOOWnf3ZGk09XuN7kJzvybw3CTkJuaSv8Xz4Lvfdzfwd0sq/K9qj+j/uMvXBvuJbSOPd7y287F43LSpFXPOV9u08F3Zx/5nK/m+jvXgujef+yEF7HOS888Z4R0jKdnYwDu66SjtFKz8c9zTXgVOcn7ORinws788YT85zvsUy/u/u4u8VixgH7fSbBcqfLq2iX9Juy2dy/eJ7uyMZp7fSL6dw/+OI4z6a8XoXf9f1S1b7XY+NXM9nM36x/jPs15Y/8Xwyh/1OUe35cZ0ayd+PD8p8kTSdv9N+ST3d7zsxHh1j3Fwdx/urrYzT/L0yj/N9J+dHP+o/dSDjxir3OY3rPNfn7DuYP43zdQLXf/rrPo7nce5nh4bTTxKUHXbRXlNWcd69yHGn/55axHQ99+2MG5n0azvfl/E4xzjyOe1Hf933c8an4fR76rmLcXlAGu+3PuW5vojjT387wPNFNO3Uj35+oJN2y+H8Yhw8lcl4xfs9xxze66RRj7eY5qvUzvsUv7H0Pxv9bSP3EevYvy84fu7fQ8ezn89zHzJDzYPlH/Mecxb3XQHcr8ZxfFguj/N81xDWPw/+JSn7e5r+ePjvfM5914ZfMO641z33+18vUo9ttN97nNfu3wu4HiZzvgx2v9dOvezTGa9Gcd6kcr+SxnGdTn0SuI5yXpzje2AhnE/jaI/VqVz336adab/zLBfifg8tmN9Zb7963jfMoJ9YevHvV3ivN4j7WMbzwVGM36vVuGTT3n6z+HtzJNdfd3yvZhxu4L7wQ/7uz7h6Yij17M99IP/OJm8j7c173lP7+Lsu7RrSxThczH3TG9w/tDAel1J/7k+9D7O+uZwXi3n/4WBcdu9fmJ54luvMar5vNZv3NSlI5Tv3R9Gxal4fepzzivu62Ofc9zC0ezzj6FnuK85zn8D3qezcX1zo3UvFuY20B/3tKuO+Xy3jKPXfd4z3lIV8H+0S1xvaz0H/nUT/7ZPO891D1OsL9t99D8bxPM/z4MS+/N3mHP0tkPssrudXZfwk5bjvsHNfaON9N/3uOM7hoaLn89yvDqb/x1KfpxifmF4Yw33qMPod/SKBfutYxfG9g3GbvyNk0/+nFvB9u+cYxy9xnsXx94Q2+oP7/mUmz1kD2f8S+gPHYf7DXFe2cx/He4ldi7i/ox09SjjuHUzZj0kfcpzu5LhRr0nu+79H6I+tnN9p3E8y3zbGuwFzkUp53nMM5Xt5yXmch1O536Ufb4b/+iA9QPsd5r6uH/c72VxfC/h3NfvmK38+ynNFXhnXyXdpzyLu7w7xvMv2xg2gnlzXdj/LfTvP/dHt3MeFcL3gfiRkOMeZ69aYZ91/58PxsXJc+Hwb8xeksT9c13a1s33uj8/NY9zdwPFaqPqVwHv7cbyX2f0O498Srn/3cl7Wcx5zXM7QviO3ct2cyfqfUvYLoX+tjFXj4/Epz8kracdEtX90cH1YfQ/nAe0xJYTrCv1sJdvb+jj3/f3ZT5aLZv3Zfvx7cqbRTNcNod8z3zre6zhe4zrF8Z8YwH30Ftqff6ez8zz1dvIcNpT9c3EftZ5xrIbjyt+Jj5byd07ec7wzuKFxZkXkmoEbft17/qu+9iG3vFK3pbf3zCP3+OzzH7Q86kfWgd5FHou9Ijw/uO2tqKKqfpMHvDv8TW975QtFvv0qqutft675JMJrkOtj7yef6z0iaeodtn0e71g=
*/