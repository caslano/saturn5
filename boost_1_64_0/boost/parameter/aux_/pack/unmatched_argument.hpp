// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP
#define BOOST_PARAMETER_AUX_PACK_UNMATCHED_ARGUMENT_HPP

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
#include <type_traits>
#else
#include <boost/mpl/bool.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#endif

namespace boost { namespace parameter { namespace aux {

    template <typename T>
    struct unmatched_argument
    {
#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        static_assert(::std::is_same<T,void>::value, "T == void");
#else
        BOOST_MPL_ASSERT((
            typename ::boost::mpl::if_<
                ::boost::is_same<T,void>
              , ::boost::mpl::true_
              , ::boost::mpl::false_
            >::type
        ));
#endif
        typedef int type;
    }; 
}}} // namespace boost::parameter::aux

#endif  // include guard


/* unmatched_argument.hpp
xnwVGLfUYtwZxpVh3FOmcbYwaf+NcZG1jOfIPxnL9HguLNctdf4JyMbvrSGma4mfxfOugPs87wqyft5lPKNoL4Fi9jpZZ9yIEaR/8jXjPOb5jMK4j7itppntLEPqluf11yzOVSkZ5wZXe0r2va5hc50Rsv2+U9M3cbpqi/Ql0tMePdj+ic9APSKzTpqafoTDrtXSo/Xj+nZ7Xf2az3g59+na0gPq3Y5elt/hvfTO2na9ptW5j3x5fZ5h3HP/qqZ5zFmEY3gW94UPOX2szoGk5fX5hnGM9nndNXw6MWt6G+cR7WBGnYaTWiur5yBGuh7tvhj3holq/kHUcivHNdkhw2l5Rg3fypOGelqCtM/QiLJOVsOL6O9pUSqvjYvLu3d1aXS332L1DO2qyn+I8QzlpCrnKOPc9pMa72Pcl29T49/X/YjapNLzeE83eT/j2QPLqX5SUvM/6hOojdCf0gOYM4T4O09pT9uS9SBORlbPasIkrWfVek0mbV+eU+ZV+1Zr1qOA2lfGO93n8cGp6re6lF+AWuYQWy3e8bXU/bVY7rLDbOWNa/Kf1Pw1HU14GrNfa++TeS2ZqfJe2CjvXWpdD+thRAxboNc06uCtU8P/pBfSiunt9AraRPbKTYx3bY8o8heklj/JJ8onyrSNVXUPo5yKvqHerxn3NUmqv6hax/akkVflMc3p8UzKeFYwR41/x9GTPeR7tuda/W09zKeQ1sYniRL2yKe0R1OfdOer+TRnsN7O83mVcV+2R5V7CrmrbuwXo/dnXuOYxsivTdXDiSbdDvtc/Y0dVWnL5ntZ76ZqP3S/B+37i3kfHOF+76LSrnPP865Scm5YovL8isOfI7w7z9Kvkrd49sD5ehmfMDk/XFVpLKHdl3XEtdumfjs1JV/L1by3HFw5iGvXXRuoB5rrqRrHweC98htf1m+a6r/hKMH7eYrRcd4RZCqv4WM5tIzj9aSa9rhWk320A2mGy/5TXJVJV0dprZ99gX2l3pg0wuWY/VjNs8txmOlj9Df1NT7vWebrwD5Tvow0u5PmOiJKR/uQpjqGmqmydlWJ5LutzGOe8nbl+RE1zh1X+CTLdx93qTzPz9qe0jm1/fMb27qRbGvXdXAf18CmDeQ+IM/sSq5hofQ3ouP6r4YZ12KZ/iTjXgpVbVqEcm9gtAESzfDjdNODs44LY9wAhh+hkzZAinq7L/jqoPtbpclMf4hO2ooo53mNXsQ1utR96u+Nohsi/buM37GW0xvjUqVLCsr67x3u+enuTWe3PJM9acvu71P5veLtfiEl589mM9tM4HrBcPf1grTVsdpUDef4zZyWYc3UMPd+xrRqf2IfkxjIGb81e79hPPPNck8S11RTf664kSVxjdQZbPqW+56EK4HX+oID1HSzbHt1y+9WSMfyN5Q6r56hLOPV+IW2zOeLvVV/O1sIUf7+qjcynlMOOeQa/izHc3mj/cXqh71+o8tyLeoOynIvstxRavwMow7xCNWfx+q+g7S83ncY1488Kn9bre4vjPnD3M+uUpPjB45UBWs6z49R01XRCsv7hwvkc64a9pjNl/U01zU0fvuo8SHGucF+yN1G3mXmf0WNb2hL5tphdb9x9HDW+T9R/eb24cwxt7n2GMu4rBfXA63qIaoyOJtZxzfo3rqFC1WeirvWUtLkHKGGRWoBsuwmFnUDr2dNk4y56wIMVfNPsb2kF1TzLw7Kcv41yqOiyvtR3VUaLTn/MFmWc8kIfDnUs05g1rZjXqG/Iu4xtSFTJZvPtbLxbvPvqut31rqunyqzJvfW6VNlQRmZzh3meOje4nr/8+N35zRO9y0VZ/xSdFCdmU3/XKN+6rVrj32W3iTn8bs=
*/