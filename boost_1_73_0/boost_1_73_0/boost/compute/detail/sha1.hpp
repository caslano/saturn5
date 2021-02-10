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
DMghwU5oPwx63xWmZUNvhXaoKufjrDXOsy6M9WwsWsMmtWxZhuz34eY9KY/RqeiMYxZCP/GHIGBkjyWgt9kOajM9M+g6WagKOgu+IkLh2Q1rpFLbngllW24BRx5P4nyHNcigM1SOwjATrUTGptmI4pPjWDsZ6sQK2Sm8beLXiFfZNKPovRV2j8agf6XwIkMlx+UjfTE5JRyJQFqiHLY978oK4xIpVQ6sw+EC1cyvl2s8jrZGN/tEeSjTSjjtqe3BKuLmDNnwGO4U+swvMgODjFubA4sTmupghc62bYgZQKTAyPMo/z+XN2/mi8uIITtSUcumi0tbShSP42HSeKEYbv1xMdXGlDlhkkKmqm8CXVkpN/12y6Zcv7wXWBgy7vT/p6xFPZ3YskZBNDQOMAqZ7rO0+HhisQeePepCUimYnVUBNOBCStQBJ+oJt06jPkkegU0j9KfQDCyyO2V61wTZH6QeepXx4Ddx4tK05JQEGzRyWgFWohwK4OEfLPmqylqBzIKKxmjJ2xvnj8LSGWs9AMJgPEYyjusnO8lU9l30i9lQclhUwT14910E6lnaQ89QNy4gVBZFfZi3ryRIdik80SwJwocBSHsIC8My7dIKPyy8ncEoZxYILBYnLLigqBbUfeb6osB65H7u+faA
*/