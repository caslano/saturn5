//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_SHA1_HPP
#define BOOST_COMPUTE_DETAIL_SHA1_HPP

#include <sstream>
#include <iomanip>
#include <boost/version.hpp>
#if BOOST_VERSION >= 106600
#  include <boost/uuid/detail/sha1.hpp>
#else
#  include <boost/uuid/sha1.hpp>
#endif

namespace boost {
namespace compute {
namespace detail {

// Accumulates SHA1 hash of the passed strings.
class sha1 {
    public:
        sha1(const std::string &s = "") {
            if (!s.empty()) this->process(s);
        }

        sha1& process(const std::string &s) {
            h.process_bytes(s.c_str(), s.size());
            return *this;
        }

        operator std::string() {
            unsigned int digest[5];
            h.get_digest(digest);

            std::ostringstream buf;
            for(int i = 0; i < 5; ++i)
                buf << std::hex << std::setfill('0') << std::setw(8) << digest[i];

            return buf.str();
        }
    private:
        boost::uuids::detail::sha1 h;
};

} // end detail namespace
} // end compute namespace
} // end boost namespace


#endif // BOOST_COMPUTE_DETAIL_SHA1_HPP

/* sha1.hpp
Dq4tbir23Eh2eesLL2ijczn+nb+Hjumw9BVZaV+ZjWX0JX+d7+vI9NVQTODffkctROIhu086Fohlgb0M8gePsLbC3/5prOVrubFsLqp2/Ub6b+7A7vLm6uFY85OPyNY+68UFytqff+zvPvIofyvO3Kbd+pt0feZf9EEPWXoIJ7F18aiwQhneLY7OFq9rxbUDHXdvcofQWrqx2nPauRJ7805ISewJDtQ/uVqIpJwzJ2amL9fXtgprqmL0XvzrC/n3Yjrrd+6auPdDtOlzdfHF6N4Y2yKfY/jyIXF6FIMOsb410z0n0Zv3e9PL4uJgaM+0CeJ6jNymiBt8iE6Sa/gpOSWniIG7sVX1N4iRyYPcY3wvyemT5iO5Yfnd4ROD7AlyjXfYwbXGr+/4/ynaaL2jJHfNWZsPr4jrL9udq61iaNE7rqkF4njXGHktXdzENhPmmfpaFN9y18tdNxor3rNT/hR+Kg5uZQ1o0Fi03HzjBnnea+Tu/1zlNhg/zG/zJ5rLDPBRf6fjbHROnDsb6+g35Vi42LFe7XqfXOij0DZBG8URaxe5OjJ5m11dMEEfJgapBuPlJ/r8mXovID/xNqzVl9vpuOT+S8hgM+W/PiFIv+26J/j5B/KLB9jLW3yvXzmHk2uZPn0vLdH/h/XzOfZ7szg0yzjZID9+hC94VyrU71A90W3sdl+6GUWX5iPZw/jBXdosrkXKSb+mrgEykNcnk/z/TfXcQcfaFNBRQV8z7+v/JeYyf2Ov1uiS+pHK8j35XqY0wZ5i6prOnq+0Htcql60l19/LH0dp24XO6VfRXCJ9lz7uzb9Ha+N7xsqN6WOYz+wTZ5vkkSb7aXLPfbX7fPmNsS8r3peu47Nr2O8cbdpbvp83Ln6q3T9hJ/3GqdH0ZXxJFar56Bi5X6V3530i3FQ9+yvvFv1qE9/3U9fvyd1+LEV5RGqMNoibOWtZ+e3cvz3/2IwvVLO9ZvOnp9QZM0adQu5niD90WX6EL5JzgS6z+lZSTshXc4vMH8gmeIFtrBArH/X/IqxRpLU18TCf+5bcnC9tIfd6Wb5zq9jpWJIeEva+zhbJbRmZ3kfOeePEzXKcB8lwE7HvMmP3pfoyWZ6rnvJZ8jh9yX1lfBbDy9+pd4S8bfQY95GbPmd2dbykj1uwlSXir7qDE7C5XO+pMfqjf8NsYDaZH++aq+npZnlR+wjrivpmPErKUQva3tIqnzuKn8Tjck75Tk7sPtZYeYH5xtls5Ap1iY/Rb8Vn+VXovlzEtjcXj3ah7+na+zcyXKu/PzBe6nfYwmfcn36UvgblHj+0XmO+H6TI1LuXwbvaZy0iFI/KbCTL53LytEB9pVX0aW2n0C1fyomLbCFxE5vbRf/3UtfTcocvR+mjtimrsLNYvyM9zzaOruYD75LxkDVQa3rFSn25wXgQeIaGzUdk1DCoro/JnN5T17KbYfY1kc5+bjwYN1bZMefY62ryuZad7cF+rlHe2fq0znXvujeuH4ez47yx/w5M1u8X5LQDfM+6a7CTvqw2XuyjPuv0idvlYPYvjHal81ZjvrXaaLJc4xltuJKPy5uKO6tL/yL5dPpQupUr5P/p/gddN1HfrnG8h35WkoE8I/gr25dTJ5aYN6w0F7yYn8sFS9obGvcLctVgDTm6JxIL8u/q/8fGydH+bjU+DNMPu8hpV2jfnfxYOcU3Pu8lvz/IPz5jj+/xmW/lJGv5zyhrO9oQaVOSDUbibrAPmfxYe8SyaCW7a1WW53UL8pZcis0fTU7yzfx743ynmy2myHvJe0Dd3fLELcVma+BBVRU74Sszjbmj5K7yzPwZbNWcOCc/ya1Tx0rXHcyOd2P/1n5S5gHBnuo=
*/