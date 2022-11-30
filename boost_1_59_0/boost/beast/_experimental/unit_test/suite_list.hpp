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
#include <boost/type_index.hpp>
#include <boost/functional/hash.hpp>
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

    using type_index = boost::typeindex::type_index;
    std::unordered_set<type_index, boost::hash<type_index>> classes_;
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
            boost::typeindex::type_id<Suite>()));
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
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
*/