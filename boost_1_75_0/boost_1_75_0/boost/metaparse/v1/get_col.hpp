#ifndef BOOST_METAPARSE_V1_GET_COL_HPP
#define BOOST_METAPARSE_V1_GET_COL_HPP

//    Copyright Abel Sinkovics (abel@sinkovics.hu) 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_col.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class>
      struct get_col_impl;

      template <class T>
      struct get_col : get_col_impl<typename T::type::tag>::template apply<typename T::type>
      {};

    }
  }
}

#endif


/* get_col.hpp
ykqpdyhjjRCmjGDKbfDJpjjGjdPUlTT+6gxg3Ibs380YX9oqgu0qUO+wRrkALISrcIB/3MUSgxACtTFR4sDeeTbJ7IU9UYSfzQ6aOheRNZ49B08Fz6E7iunnHPip3dqTTubSyWl0uJcOd9LhVjr4+PN9e5prqYGBexPbxEg5i/ruQ+nWg1x9REavASm1RsC9AEyn4iWIy8+86pO0E9SCp7aVMkriQSitIbt0vMVc8gFy2YJ4D+SAe7DYjRWyKVDgMCCQAhP3YAEctHEKCzXaZh+1GYbnetbWZtbAet25cTFM5OO4d2Tuxzisos/ArIFX31iMuQjRipE0Ec3fNwTb5Y4WJXKqqKYx9OmZSJTNubFUd263vCUkWwKr0qDRuw9Eh5kMMUX3AZjgNtBR3dVMMeCV1iMo/1kAUVJZUFEap9UKCTumFO0I0JV9T5FVVxc+cN2gepOL3EHjLA2+8eL2+LDbhZ/n82jU3YEaROUcZzzRTSw/RsFR03vRr9ZeplpHJqfJUUZTtOKiSioETbX6mHAMXqvfmXTkVac86FXfXwwLX8csy+12DpnzLxQaCqooT7LKGKB1dKEZRI+grzlNdT+WzuExEC+I6WYKJh5sZB1qRg3sTnpkD2lhexgbrXvckri0RyQu7VFMLtA9+BI4SYlLfZHRAVoB1UDajXER/d1EHehAO4eIqp4RFQDmOUqgMHLjQsWQY+GhNVpL
*/