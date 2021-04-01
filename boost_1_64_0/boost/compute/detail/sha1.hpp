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
J2ctrasFjXdiZ9ypjwOXp/zoIF4JO1Bf8o3rta+y8U9V2EOJLHizQcBdBi08y9GzNKIQlD8+znqQQ8vDg2rkvOhQFmwD3Q0wgZEyWneYqJdfMqJJdmfzGVRjWZSyzV/CvS9inF4NQ7rzBbZ+sXzOF96lUmXwQ+qh6mPKQRELaPS03U+UqPBUaVszozHORCdpKUo8mCkwPUTXUi45xfWSNopNrCLv9ejMkVYMcRqzBU7v5WnxnIordJo+eoOF5W88GWqF8MyHdjLKkUQBwBJj9+9MVCy6kzF6MLEzZ0gTxl1UPjI3nbl77lIAxLvIJk2dK6RgPrYY9tojkmENNJRSqRwqGG3iU201YwPiM+dVuimpXwcdfYxHHi0Mcrlc+f09AMOI6o3Jk785fosSSCPYr1/GZbOq8umYaX28oQn3Q1RfgxsVI2aK3qI6IqRb3xYZoHhm0/lawiVTg/DxRYwH1yYHUfBqb3k5IHABlK5ehhlcdjlqPCBnshNlu20W4F6wYM0BgTYTqbaVIGdHLP7N906kJHLXeGI/6gMvjg2N0LMUYauEYsolBl6ztw==
*/