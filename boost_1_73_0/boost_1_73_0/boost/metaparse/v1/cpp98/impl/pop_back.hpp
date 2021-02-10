#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_POP_BACK_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/fwd/string.hpp>
#include <boost/metaparse/v1/cpp98/impl/push_front_c.hpp>
#include <boost/metaparse/v1/cpp98/impl/size.hpp>
#include <boost/metaparse/v1/cpp98/impl/update_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class S>
        struct pop_back;

        template <class S>
        struct pop_back :
          update_c<
            typename S::type,
            size<typename S::type>::type::value - 1,
            BOOST_NO_CHAR
          >
        {};
      }
    }
  }
}

#endif


/* pop_back.hpp
d+AldVWEsBJbTB2R3cKh/7M7PmOWORFt8dd35RGeAwy3226FzXKfsJLZHhqti8xi1fDthAq5MPCCqMAzubZUZNvkUomy0lYnupgyx2ALsfsyeuxGGxvCH5P02CPtwL9YU3NSNo3A+09Xy9Xt/KHHLpIES3J/4B+cHCN+bEFrpqECaCTtEbu80zXR1um2SelyR+9y270dsv/Xr/efejjo8Y2xA1MjxxR/Wyc//jZ/A1BLAwQKAAAACAAtZ0pSUUiPt0gCAAANBQAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEzNDJVVAUAAbZIJGDNlN1u4jAQhe8t5R1GqbipyJq/XalRiFSVqq22WxCk3cuVmwzEarCj2IHl7XfsQEHaF+gN2OPxOZ9nBhKLxubCYMoSqdaavj7wsNdNYVL2mGUL/wEP9xlL+Pkk4V0yu2JJg3V1oFAhrACl8xLzj2l4QBN2Cnz4bQijwQDmPwM2ExZjyFrsw+AGXvSOToYDGE7iyU1MOQ+/soCtsNlhE4Nji4zf8LX4wIDdaWVR2egZ1caWMfzwIYW5lVrFkFfaXGRlhxqdyl/LS7utAhaw4Wg8+U74DtY94whP77iCu0q6W0YWyJLcb1IK21IaaJD2BrSiLUKB7+0G
*/