///////////////////////////////////////////////////////////////
//  Copyright 2013 John Maddock. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_MP_CPP_INT_VP_HPP
#define BOOST_MP_CPP_INT_VP_HPP

namespace boost {
namespace multiprecision {

namespace literals { namespace detail {

template <limb_type... VALUES>
struct value_pack
{
   constexpr value_pack() {}

   typedef value_pack<0, VALUES...> next_type;
};
template <class T>
struct is_value_pack
{
   static constexpr bool value = false;
};
template <limb_type... VALUES>
struct is_value_pack<value_pack<VALUES...> >
{
   static constexpr bool value = true;
};

struct negate_tag
{};

constexpr negate_tag make_negate_tag()
{
   return negate_tag();
}

}}}} // namespace boost::multiprecision::literals::detail

#endif // BOOST_MP_CPP_INT_CORE_HPP

/* value_pack.hpp
p/aurqlsqHV2uBeYOR8sVlbCCff5RQznbxZ1GBm50z6rw2zMt198hWP05PGUrAcbD6nDMMDXUTYNnpLHI/YViB0ETUl1YkVYz9kD6odRxdpWjfOr6oFPvLIa7NOTSD0qPTDznDZnfZmC80q3tOFiHWN8kryONauVtcltDsD2pV3bhZd3ybeZ+oLIgq+vbVtbQKW5D07k/eS4IsHylImCXxvsOgTfMOmstFII8GBe/u9lvel50Vyhd08W/7YXby/+K/2zGb6lhrF4RzGmUoem0iENxrJObNdBLx0cDBzP95dyqaXTsvGr63BgZ8XeYR0fJXW0rG1izQWXDEdlHYwwu6Ab6jaYaVM356Xt6tukDsl0rFKI9grrmGLn6KtPsJopDzNM6hZls9wzSuGgbM4dZnhRMw9K1ThjUDZlPeuL7XcQ1XyQVC6bq4dUX5w2vONcYZ1jbcNjC/TFaIbv00M6rrZuqiqFxVkyxCjow6Y4mGlFg/p34WWDjwapyzGrnU1BC0DO/48GPr/0cXrPYZE3JrhQ140v+rmwrtutqf7dKfDaRemVsFm74EnK1slmMh/y43ycbg9t+Bypo0qLfScqWWEd42jPs7nJqkH3Clk1MVgTlMM+pKV2InW6vv2c1GGYVZ3zujKkDW852OyTFBTXI2f0IKdz5AycfP9E7WvvTqnn2sIIim0iEmNnMn28/OZCTqZrQ+vyteL6dnJCWTytJm0TQx2uqKNpo+6s4Fkd3ez28X+sY4vU4VjjvK5TniOcD6cuFmJYK95F6lAsWKUFNwrrmGL3c9/zz5Av2WV6NnJ/fTegoV8PSDTmMEeadGDvT+TJ3pzZRTKao93eYL0kwTPwhbNIM0xjUhf6ni/owBPzeANcJC4t7dpnxnJ3Tyjvv3HTwWBr2WI8+/44lf+X83G8F9KU52M8834z0fwP36fy3kD3P3yffi3RnXL2vXgOyybfih/fpd+KtY0qVPJ/jpGaRorE5svru2y5dm0X2fbx8SF91/X7nO5S1Ja3Stbs6sXC3/nPOd2V5CYWuG8XFc4HP5GhzjN7+dsmU0dXpxzPly8v30OS79PP5reNy+95LH/S3aA808mdLZpX8jV3p+XHB0CSxzW6B5YDdHPvMJ8TeVl/udGTYP3mLNIsAxyfHO3m71O3icwca2rVNfx/zznRywzHeHv7TCYL531dC94wspcOtO99eU4bhW10B9qSv01D2g8QXTCiUdZEx2LAPM3jO9APETkrL2QwQjKx8MeUXU8/5uT/cE5/1YL+cCFhBC72K3mG2V3EwMd7DJiL4nofd2TUh8+R0sXtAEajwdyLdyvpFhc2WM/XJuV9lPDZXv/eF3M8lHRJn0efiWk5XCxnsXHvMSnfh/pJjKYV5SlyMMmRS2lont14r0n5HDInpAsGrOP7SANl+1tQtOgmln/g3pPy/XwcLpyblkMb0Db0cyzvI6XfxrW9D4o0rtu375Nol9MlDebrk8fcc7O74DcV65zhDa/t/xxEAedMpjOfL25sl1oDO3cSV+6LcbfVtIk018Pzd5/SLe5pj2eJFHm/dxUdaFriXcaHZvdYTdvzHu25p9Mtrtw6K5F26+x/pg1Vg7bSs/f8z7Sb8MEM3967eVs+/B8w/dXXuO/fq6fFjZYIAfX5p1M6FADeS967oMkHP499W9LRwR9j4J1bQZfI8tzJ9yloykHPaD9V0haDnvtxveK+p9DSQcc+/f1UenrXeHw/oCPnPjrg6N9wvqTDAR/XywkNGXCkc/cv6eiAYyySlXSJbBzD2w8oacoBH2kf9sCSthzwcbw/chotHXCs+/qDSno64CRudE9LD4BUz9GO/+BTaAu9u/CQko4=
*/