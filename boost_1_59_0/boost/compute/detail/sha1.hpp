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
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
*/