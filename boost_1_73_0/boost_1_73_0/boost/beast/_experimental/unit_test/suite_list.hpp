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
Uud1shrlS7JnVVPN8VuhNGVzKqRM5J+othfk+5Vmp3+Pvi6MD1uxqQpluz3OnHZyL0D82QLG24u/KZGp/0rAGItO4BORXCZ2XQK60odu1qQc7e/t7SIlcVG7wl5o62WdicIu7LiWz6tEj0RZQrvu6jrgnHYyq7TrNNreXhO/Rw8dRx/izlgOrmZOoKZRG+/Py9H12POmlkmMtGipjnDgTDi6HEd4wMyL7jybzUJ5L9BKZBjrvO8rRxjfqi0n14vk/nl69ffRNTy9f+EN+yLGu/H48t3p0cnpVdCy1PdxY1zWNVi2mjWm3nSI3sZ83bYtAwfzBPyiqq0Db6/1gwUaBieQXb+ihyZcm9LObepOZO6JJjhobrnHVPGAXYlhBdGEMlpJi0kDRR69rHFf06PcUe7BW7KmCezyGLHBTBM2Gx4V7DrYPJxVyspHp/I+lmVbxlzcpwkCd3d/sKCbaeSBk8LptH55dhL96/RqhILh2PYGj88d56cuHPPekpQzDWZclC9l3SDZ2JBnjTLDiCgqjTnMzRcrgzVAob2DTjGk2x88vqn91d6SWcuqDdhmBKw0Xsre5Gljh7egt3L/E4K0YPtcO/YGS1hQ2gB/S/u9VuF7XisimRn5NGijZlvKHx3nHkawtgRfW0a/5Ujg
*/