//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_TEST_ERROR_HPP
#define BOOST_BEAST_TEST_ERROR_HPP

#include <boost/beast/core/detail/config.hpp>
#include <boost/beast/core/error.hpp>

namespace boost {
namespace beast {
namespace test {

/// Error codes returned from unit testing algorithms
enum class error
{
    /** The test stream generated a simulated testing error

        This error is returned by a @ref fail_count object
        when it generates a simulated error.
    */
    test_failure = 1
};

} // test
} // beast
} // boost

#include <boost/beast/_experimental/test/impl/error.hpp>
#ifdef BOOST_BEAST_HEADER_ONLY
#include <boost/beast/_experimental/test/impl/error.ipp>
#endif

#endif

/* error.hpp
gOZcYzgODoQT4VBYAIfpu5sFfwZHwLVwJLR7Uul5uR7fu4fVbntE7fTt+n3xKBwr87dRAbs3j/+Zlv/efXuSoNm7R3v2ZA7+H9m3579g757JSGE19+5pavbv+e/au2fdf/H+PZnV2MNn05OchYnsQ5o+FRNIQcYhC5B1yK3IC8i3SNIuztdECpE1yAZkJ/IOEvM0bpEcpBRZj2xBXkO+RRKewS2yANmAbEXeRGKfJY2QBUjFszX7ANVcNVfN9Z+9fpL1/wzGH4v1/204269bcG13ZrBNyvScpeVleWU8dcnipWYffey7Yx/IdtnPW7Z4bvlSs3fAfYkBO882P0LnrGvsf3AAu2b8PtJa/dzcvJIlBYV5lb4QjKVVZ9A9gg/bjRx+Po/GDmkf+o11VX9syXvsyn9saYsZk8v+fMAT59/c8cUne/bcevWDL0X5jXX5jUX9+8cgnd/FJg+UN6eH7anbUv0/Cfo9mwi7wzawv36fDobJsAuebPqebz6idrPazGon2zZyaNuYdrFtA6+B1yHhZ7tPVlv2AHS3TzeqHaq9I2ln2vPY7VnstCF1BjtUu5D2X8i56mrjhbft7BnqOYg9Mz2sfaa2mW1zjfM/C522Ejrf17RFaq6aq+aquWqumqvmqrlqrprr/+H6SX7/z11efix+/wd/w9/Jjz67zk572K3VXONFyDIGMzdEO+t3RuaeOCUnuBuJtiIZOSINpXpV6ws1d9hx09uuUXjWmKe7dAuM3Vir28POw95lzGNdunPsHO4njN0kY86xbrt67o0wHvvHjf1MY55o9TsZ/ZUdQ8+lHY3968a+j+eec6Owf8HYx9i59a8mVO41dxcy7Qj27jhOc761HtKYR1lzgTHnWPMcv/06bJ510ILg3ynPzlKe5dTyz7PSgGeeyU1vm3ZnG/NcrzyTbg+bvyuNuSQ0z5SfK4xdns0z3HrnmfJ4ubG3Z0qjf+g821DLM8/s3g4XGftGpBv7ZZFvtQP42Zw5d+TXZu0VeM9PnH+fwcxIvz4jv74tv74qv/nmfvPK/frI/ObdV39ednXnWb9j+tQ+/ybr97+6os3VjZoP3rP8/jemVX9+97+7T817XrzfPHG/9Q1+6xj81iv4rxtw5gab95re3TFhc4MnaG5uLkyHk+EQOAVmw+nwZHgSnAdnwIVwNlwEsdNcRdVFvW9iwuYqJuo5/SESOAFmwoFwOBwCc2AmnAKz4BKYDU+Dw+GZcBQ8C46GzM877Hh+PvcZK/Ucy88p9R7D9x+/r/5ZO+5+zPCx+bVwI+Iaj/cZiw8fh/c4Nyfl0OPt1yEaY/ccX7/Ojqkf8iwcjaW7x9BD+1LLkaox88OPl2usXOPkYWPj1TzTRuPhnuPfFb79siFj3HZse5bGtCuQ2B9iAhk/1PTb1lw1V81Vc9VcP+76aX7/B3/IBXsAju73fzLj+9cH9+9jMURkIDg0P2l41si8rFFDc9Py0vr0H5saMDob0aEhJp0JoydNdnQy+owNVOrcgk7pIm+dYdK5Paiz2EMnPaW/48+d6Gxb4q3j+LMZnaRTPXT69kt1/LkPnb1l3jqOPw8En1Xu6Ezvn3d8mpRSj+8zNdXqlC7z00mzOknL/XT6GJ0/obPbW6ff8XrWNnRKT/PU6Z/q0kk53U8nzers89NReLYH832Fl05aSsa0ymc9HgzPGV46FI6pVTo5Z/rppFmdlJU+OgrPE+jErvLU6Zem8OxCJ3CWl06flHTpPBvUOdtTp68T5j3oZK721DneifuLwbif46WT3ic1N9XMjXk5mKfnOjrTJo+blJdqzs3A7lXsMs9z7EbnTOJvat++eaOz+xj7vwXdhttnBO3TA8k=
*/