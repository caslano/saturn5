//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_SUITE_LIST_HPP
#define BOOST_BEAST_UNIT_TEST_SUITE_LIST_HPP

#include <boost/beast/_experimental/unit_test/suite_info.hpp>
#include <boost/beast/_experimental/unit_test/detail/const_container.hpp>
#include <boost/assert.hpp>
#include <typeindex>
#include <set>
#include <unordered_set>

namespace boost {
namespace beast {
namespace unit_test {

/// A container of test suites.
class suite_list
    : public detail::const_container <std::set <suite_info>>
{
private:
#ifndef NDEBUG
    std::unordered_set<std::string> names_;
    std::unordered_set<std::type_index> classes_;
#endif

public:
    /** Insert a suite into the set.

        The suite must not already exist.
    */
    template<class Suite>
    void
    insert(
        char const* name,
        char const* module,
        char const* library,
        bool manual);
};

//------------------------------------------------------------------------------

template<class Suite>
void
suite_list::insert(
    char const* name,
    char const* module,
    char const* library,
    bool manual)
{
#ifndef NDEBUG
    {
        std::string s;
        s = std::string(library) + "." + module + "." + name;
        auto const result(names_.insert(s));
        BOOST_ASSERT(result.second); // Duplicate name
    }

    {
        auto const result(classes_.insert(
            std::type_index(typeid(Suite))));
        BOOST_ASSERT(result.second); // Duplicate type
    }
#endif
    cont().emplace(make_suite_info<Suite>(
        name, module, library, manual));
}

} // unit_test
} // beast
} // boost

#endif


/* suite_list.hpp
M19tcqtHxMxneMGpi0M1EDqQnqcQS7pyTB1MQB30+K2b9QnYRDlid1O0JI+r/KNGMsjqCueYymO2KRzObpdoaQC6xGS6cqOOEFj/esccGlY56IDiqJqugLp84Ieu0DXR3OZAokvdEOmEQQmvUt1LEtyhsii4BHFbYOzlyj00rcA7ZiOIsNMxWBdo2IapPQ5or/0us21CypzyyRnpij+tIBQCfZh2+j6boq6PXEvJvTAdVWbkfVAPZcDMZkXrw6MFrqzeXSbQ4Odo/1bEsSUjKWL+M1qZj6wnE1ixRqu3JuuhB9tL2ftlD8pR52QZXhv216O+Tz2RbeQlRe1vmTKLnzuauaGf+4GbOgJjxz5rzza6bw9p8dKjR2sY436/9J3R7zZSQ0y8ifKnC6ba68hfD64IWdkvlyFbDvb0weWUMfOmQhJtXCG5yXTDTSaINUaAeZI6T09ZWzbZqJaHpsd/1YWtzTfGnAV1I+CTW9Xv29KebWjX7oTjn3Liaqp0qXK2G7ug4tsTruktN3Z0Tbfoa9r3xo6saeaW9tZ02ClyTfNOaXdNNzWdcE3/Nupka7rFsqbjtp5kTbfgmhafeE0zRv2fr2nvze2t6RXdOLdkd1zM5XRZ0r3dNX177wnXdPrIjq7pdn1Nh43skP/Lp+2t6cQ03f8lrc01BdPb/+7R+11srGmdxO5bb6A1zTbWNFuu6fdg8bCcFMOY02tO
*/