#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <char C>
        struct is_whitespace_c : boost::mpl::false_ {};

        template <> struct is_whitespace_c<' '> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\r'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\n'> : boost::mpl::true_ {};
        template <> struct is_whitespace_c<'\t'> : boost::mpl::true_ {};
      }
    }
  }
}

#endif


/* is_whitespace_c.hpp
bwP++yk8BRoewH8xDU9mDwrSetDNo67TXQ2fVKoUak3Pqr8QJNPx1amWWX1DMJYxqfhbRIoWVvs7w0cLh9OAPA8aJgiXE35ZQH5TvuYlSLzAHQ19Dr2mDZPciTy85OIF9l4d7DvhywJOvPNwdQ/ed1MO4L0P4aBDZ0131wXshKd1eavYLhzX0taUC6k9JaG40IuDhYHZhOGG7cFCwjg/NA/TvzdBXgSh2tN83geEZPGg9wfRnz7YyxhSCkoaK9K7v6MM5R4deCA04MXAGRs2rchsaQvNEd68ozDkqXa+M1lVJlS+xRih9nk2IpRHxZawHP4gaN8feASmOB3yt9hKQlR6eyBLlInZh3xoLRCpGQB9BVjvPwIIuiRLsLSIZldrA0jCW279ufSIYj1x1l4aKqVDHFOfs7YiVAhrCJNdyLnj6yfr4uZ5boPZ1Q4s2EecgP90FWc36CtWNebEZ4ISrR0INywfuthJzxAWc7W3D0B0rurqAYuONGL5gwXLz9/v0LJblzq6YGUBA+niRnmo2kdUTwISHcboVNvWzoCabHBhAWJFVntaF+EnQL4IENGPz4oz5V7s4HJvvgphC8kZrQ2FZjcauqr5NSpacYjhSSxCf6F8sUFWMk7FUlW8+4vdiZnI5SnuIifdX3bZaZwYh0o8ua61JewKgD1+PQ5uU+yChFkGwikduOsbqvazB2+RpcIIS2PJkXqWNI2TwZvyNQ4kdqGf2BTDnHkifVAurS/UWolz9NNGeqx+pF0tPpTrWjqeJ2Y96hEUNqOkvwcfc1AUcmoA2IJNHoM5gMfsy8uYfWNwu9OUhh9DraOGQ021q5EEdaIf5YPOkWdMI82RATC/2tkizwZtciizYbXq15/G5VHvvNbX7y6Ex8QnJdzilogDSM+wMpxF0giJH8UTekrzKdgcu34AaQ3JQ0nQaNVLgtkJl0aOcIRPlseNXO1WuUp7hX4QVUi4pprezje7851mdyn+HYt/c/BvHv6dj3+dRko/v2iFta2aezjdzdjgDWF/vHCDsmfZOF8x3zkfuburYBl3dyEY7vGT1H3Q9ZgnGPFWr6Tb3WHw6NS3KqJfqs5LeUQH4dmrtySm0+XUxGNm0oNwdVoGg9QldHENYgkmnsT2i22iBZzKHv2+N4IZ/t+59P+CKfD/XjTMX17Clukvr0dv3z0xu/PXW5Xp/G0al+b8veO0w3P+pp3/I8pJUU66YdO8CQOyN8FcpzaIgeKe9aMknZusNoCC+rka9Zdzs02nGA0o7gQfzlHqyipmkOMCBujHBSJBNuboyOOOfRDjEpTHhcc2nyp/v+OijcdfqjEerWdwPBbWDfPHL2aL9MdvkzsVmJ19SB47NXNIhorThuT1Uw5vSDT/lQ/0UQIKibVC/uwQbiEdQO7bjlAO/HwJP8MUTrc1ih+L1HGSHEexSbvaHVF6rFgApQ1jFPfizUXISDa5mcExX3mjALOO/mBDZ985tACTWTjbS7/5gXKUrqurIXnSAXBjeDnqp1mHwVziQADNKNr7ap7SXub4FpwOpahwjffsqMy5z7SV81eVdyjkAXvgeWe/Z6mWerlGxmNYWuohEcC443xrTyInYR31UKb6j56fCHSYB6g3wnhfXpUab91gtpf+aweT/LRo/Py0VeHnCOUHrAcfXw+ozVI/bXzX2A42vpnwp+eMAl6h7y51/o0wX87MPXj/puSOOJ9+irWu0tXKz/6MNROWNgXNf4o/EbN+Q3N4SAzK1BtyOSw3HyFmDi2xXaa3fkvr1BJdbEssQiEcVYDmiNUfUdlWgfuLeDdNwkxVoaYFxqCZwC0QRwE6WfigRHqpQpVIixNnqy2WKC26lbgZO50=
*/