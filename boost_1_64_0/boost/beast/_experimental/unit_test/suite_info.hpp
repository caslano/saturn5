//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_SUITE_INFO_HPP
#define BOOST_BEAST_UNIT_TEST_SUITE_INFO_HPP

#include <cstring>
#include <functional>
#include <string>
#include <utility>

namespace boost {
namespace beast {
namespace unit_test {

class runner;

/** Associates a unit test type with metadata. */
class suite_info
{
    using run_type = std::function<void(runner&)>;

    std::string name_;
    std::string module_;
    std::string library_;
    bool manual_;
    run_type run_;

public:
    suite_info(
            std::string name,
            std::string module,
            std::string library,
            bool manual,
            run_type run)
        : name_(std::move(name))
        , module_(std::move(module))
        , library_(std::move(library))
        , manual_(manual)
        , run_(std::move(run))
    {
    }

    std::string const&
    name() const
    {
        return name_;
    }

    std::string const&
    module() const
    {
        return module_;
    }

    std::string const&
    library() const
    {
        return library_;
    }

    /// Returns `true` if this suite only runs manually.
    bool
    manual() const
    {
        return manual_;
    }

    /// Return the canonical suite name as a string.
    std::string
    full_name() const
    {
        return library_ + "." + module_ + "." + name_;
    }

    /// Run a new instance of the associated test suite.
    void
    run(runner& r) const
    {
        run_(r);
    }

    friend
    bool
    operator<(suite_info const& lhs, suite_info const& rhs)
    {
        return
            std::tie(lhs.library_, lhs.module_, lhs.name_) <
            std::tie(rhs.library_, rhs.module_, rhs.name_);
    }
};

//------------------------------------------------------------------------------

/// Convenience for producing suite_info for a given test type.
template<class Suite>
suite_info
make_suite_info(
    std::string name,
    std::string module,
    std::string library,
    bool manual)
{
    return suite_info(
        std::move(name),
        std::move(module),
        std::move(library),
        manual,
        [](runner& r)
        {
            Suite{}(r);
        }
    );
}

} // unit_test
} // beast
} // boost

#endif

/* suite_info.hpp
xvkvMij/HM7/dM5/Luc/D+wAzgDTwSJwIFgMDgcLwFFgITgJnAnmgdeBM1juArhcnLkhrTzONYRZxM/fye1/N5gA/hGcAO4FF4Ivsh6wl8DbwMfBreAB8FnwIHgMfBo8Cx4GFTznCOgHvgiGggjv1qvD49CtXB6yXp1W3H9bg8lgO3Aw2AGcAMaAeWwvZ3sV24XeoO2sV8dgvOjK41w3MAiMBRuz/QJoEecTGPu5vJrDfMvhU1kPqKq/sCcYDfYFu4DpYCw4B+wFZoBDwf7geHAQmAMOBWeAw8A54HDwRnAk+DtwFLgOHA1uBseAD4FTwGfBbPAdMAf8GswFfZHefLAZWADGgjPBdHAWOAwsBieBs8FcsAScBZaCZeAcLocTMLQHDjblcmhC9ct6qJzPAR8C24EPgzHgLrAP+EewH7gHHAHuBSeD+8CZ4OOc7yc43/vBpeBBcBN4CNwFPgMeAg+Dr4FHwNPgUX5fvgR+CR4DvwOPgz+DL4POdrgb9AZfAXk84j1h1KHBeJRKep3gBzYDe4LRYC+wC9gbTAT7CD1RvNcKlhm05/6sn2sA2AkcyPFcy++VQeAQcAg4GRwGZrM/pxf7nubjZxynN57Tm8DpTQRjwO78PNj5fch7e+DXBu/DZZBrB97E4ZeDceAt4EhwJZgFrgKLwdXganAteDt4O7gBXAduB+8A94AbwH3gXeAL4EbwdfBe8BRYC74F3g/yuIl9MvNxsxXnuzXnuw3nOxrsALYD08HO4ECwCzgcbA+OAmPASWAHMA/sCM5gOR43eZ+I+oLHuJnPevpmgFFgAdgRLAZ7giU8/y8Fx4Nl4HSwHKwCK8El4FxwJbgAvBVcCN4LFoIH2S7mYdzOOhiMa+NZX9gEsCU4kctjkphf8D4AuMRgfnGS9bCeBtPAt8DxbM8G3+Nx9wz317fBE1YL6R47DFOXzjHoG5P1jAkdY5mlQp+Y0CE2TKc3TK8zLBFmcp869YEJXWAnYL7tAwM6dXnFwMj6u5aD22Cgn0vo5joLcxFGp4+L9XAJHVxC19YpmEtwj4wl3VmsN0voyhI6srbAGOnD+gLMA7ewnitHHJ4JkwczRqfP6jCMqsfqWxhVd1U0TC+YLJgKGOijIl1US+Mvr3sqsD/pnBL6pkJhhG4pSa/UThjWJ0W6pDqDxrqjjHVErYGJZL1Psq6nizCSLieht2ky62laA+ObCl1LMJkwFTAbYA7BfAoT2AN68GCqYGphjsFcguncs4FlDMxSmG0wb8BYesEdZjLMUpjdMF/AhPZG3DBLe1/VxXT1z9U/V//8p37/X5JbQT///8d///+q9Pv/s3ZXHpx67CPAj8Hdznv9q4zOQ5CGeNqzNzsD4XAdxBnI42R/1trJYvU4+4mAzFAR5hN8XyYMN6AiMf/wovMizLPEN+Zwl6wSczBxthizxhmmBnKVFE+mFM9AnNA+b3GIeLCPIZ2/0Ee0xD3JXRSmBX6zb8N3Vnz4XESNq6X4Nt3B1U77k5C4TzH7nexxkrlTMQojnzEibnHGWGt4fp5Ov7n8E8kdtbr952dPn1lBzytBXD+S/yKr0T0jK5XPdEW6b1Y1U7rT9An5x4vvdI8ne4TS0vKA+N1sE3IrQNqp7MQdOZSguLN0E+XxL/SchW1JpqSsGPXEd+EvUBq/U/KVluymeZZ8D0rczQsg/1GK2T0onGVx2T6Fsm1skX/Pv3OV5+/5Pya3O63fIiZ3XvA5NMqJ+7tuKyjO4TjDQDvgO38fkFswvnc6kfIzOZAM/c79dRj82/B3u8/CvTc4GXwj0m3fCfPmFf5Gvt/aOn/DS27LDe5ZrRHfLeS+A7cN4jwOeWe3WoNzt+8=
*/