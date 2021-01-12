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
jZCQje9O+tyyn+4YcFzr2OD6uuth11zU17B7o3sTamyLe6t7G/rAdvdt7h3uO9073Xe7d7nvde9zP+s+6o6jf37Tc7nX4W1ArAPeaahFj+9bvgp/E8awv/iTqKnXAung1uDeYA166Z2hXaEDocvCgXAifCP6w4cxGnw1/Fj4ifCvwy+GXwr/LTw7UhO5Cu3vrsgjkZ9FXqa+u8sY24q0c7R27UHt+9pB7c9akX3I/k77Tfbb
*/