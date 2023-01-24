///////////////////////////////////////////////////////////////////////////////
/// \file end.hpp
/// Proto callables for boost::end()
//
//  Copyright 2012 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_FUNCTIONAL_RANGE_END_HPP_EAN_27_08_2012
#define BOOST_PROTO_FUNCTIONAL_RANGE_END_HPP_EAN_27_08_2012

#include <boost/range/end.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace functional
{

    // A PolymorphicFunctionObject that wraps boost::end()
    struct end
    {
        BOOST_PROTO_CALLABLE()

        template<typename Sig>
        struct result;

        template<typename This, typename Rng>
        struct result<This(Rng)>
          : boost::range_iterator<Rng const>
        {};

        template<typename This, typename Rng>
        struct result<This(Rng &)>
          : boost::range_iterator<Rng>
        {};

        template<typename Rng>
        typename boost::range_iterator<Rng>::type operator()(Rng &rng) const
        {
            return boost::end(rng);
        }

        template<typename Rng>
        typename boost::range_iterator<Rng const>::type operator()(Rng const &rng) const
        {
            return boost::end(rng);
        }
    };

}}}

#endif

/* end.hpp
+/oDE4EodelKRlYlVhfnh+dTiWBcbk9XTqHCph9RJE8x8ASehTDa+8CjtAEIpHkK9UiJxPi73rI5HJyUPY+PBlYvhjQwUm+S/qiFX6EYv4JzrgxnDwGRrfvHrAjwEs7hFaoQuxKGEjBCdqBQzstwKHqv+d5R/S2KDZ4/m2CIhDJlEUuigjkaabKZEUGKCIHoBdQ/nBFL7EmUmf+zYMLwX50RQn/PWrb2jl7etp7/oYtIZTPkb2KPRwfURX7cWE31W2li+wgoDYnhGxhtjP/gYfJg1Jm5bHaue7HVyhYzUTXgqLiGQ5jHUJlFz662EOX6Jf1TS/h8VEuLYi4c3TGnBXOnJWAVT0OcnHzwViCpx2iC9UPlM0Evp1evF3Qzm9eL+u+FlLPQawrcAhT8o36PBOG8L8tPgWtdHU2d0fexOspFyRD3g+sHKQ9k1jFVRujbRS63uEXBzN2Zse53gtgGmDVYvzCX0Q7RD1nXv1e+3c9S17qbgsdl36ZiflYAco1cghz9d7S4bI1U9i/yDsU97V0TmMKU9PyIF05IICaotOHm6aHTUxtDob+jPlrUdg+hFmW4DIjJgyk2OBgH6axA0XagIn/ANVs9ERy0Jy0SKML/0oh2YaVDcCl59D5v+9qm8xmCYaKGiRRZN3sNiqJ+Dc5Bxd/cobv73EAarZkocal+Ix0chthcNHARDznchMipL/WBDDB3ERozPhEk
*/