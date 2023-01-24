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
nA2LcayRDUvyuDIbVo2OdDEbVn28qRrJZGBTS5mMNRvWN4opG9bceGs2rD2mcOpmBOSwIqAao9MH7mC2qd2qrZ0rpNOjwFIv3GGXCy2xZJaJkLXDiwEC7II2s+j/eAdt00wiUu0ORuYUw+12wR1yuz0T13q7/ef0mKwguN/6m/fbOTLdFMTYplVuIwu15Iiz4swr/dHtZBq9UCFeVA8ybKKRCXEke1nIMACTpi3R8Nz4AFDAhWYK+BekgG/f0poC9rm7bQrYS5wKvWPGw7H0M6AFw4MZmiv6CSTXZZI4sIHSxJmcThxV2eAK7vzhNrsSvhjC3khGHv03mVHJ6iCj0ibFJITzwm0dRziRMa41iZzku622RrTflsPaljloaZElKpiFAvb94gQUcHAfom5jTwXqdsepdLf0NLr+4zQkW4vo8pK4aPO/IcJWw1WO9RaFlfDkbH55Itw8/A1Sttb5aEeahCx3/2QSsozZj4FQZVRtGmhB5ZhGRQbwvXi0breDYcjZbkf8cJWvzmhErfGDYOIVX3kuZiLoKYB5ajefurFgXVMcxFncpu3eC4rhXWj/dmtHNMlNn1vMvVCRLqUTo3kSm3u1YYM048fUE+i977y1fRukRsMGqX+H+jjo8zZskMb0irVbbjX/P/y7rfmfz/NfEzv/sF//t/N/6x59/m+8pSNjK95+8vkv69nKXtUszysG++cf9KEWglgo
*/