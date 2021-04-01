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
aK4QByhEBR4Pbqbzr77y5gPou6m1cB9Fe+1W0zIMtwuFBdB/dxfMISRqbmlSJpupaxRFMwC9EPYM2LdlexgJVy8BLW00hQMqRFjXI2YPcgh6Ry1xIGxsL4aOa/0fBr9gsciOi4Nh0vh1U3KkZUOTfDtoCjqyVHOjQl3MM3PxrQZSpv/+Ktuztv/fKvYLiNkT8dWO8AX44tR9aSkLHW0XaQgsPEvfUQGCCyoPN7mVcbESRecEproGbQsGQ3a0T4Zr1n850Kp/DbKZwfUTv+PadyfPji7E7xujHShX5sbozeirmulKxKS+nKztsP30GEqVzgl3WEuhjRtG0+38/AZiUdLXnrRIompbquMluYvxjSLnKZOV4zSJPa3/4pyar0ftyuFROykOBNQfScY1Zkt5r/y2MfoAy5R87r54agU2VgIsjpqPSn8doRzZyV9e21vqY9ziMKsSTjh+3tLqWaED1mAihbx7CfWtsGqptSo1GuO3PpqPOsuESaUXDPUlruqTGLFavMChPEGbCNyw30ClGQQ3dM3bxNWoG+YJgC8/QNXKZk7L/nJ/Q1lJDQ==
*/