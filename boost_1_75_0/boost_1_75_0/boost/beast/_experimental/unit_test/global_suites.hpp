//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP
#define BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP

#include <boost/beast/_experimental/unit_test/suite_list.hpp>

namespace boost {
namespace beast {
namespace unit_test {

namespace detail {

/// Holds test suites registered during static initialization.
inline
suite_list&
global_suites()
{
    static suite_list s;
    return s;
}

template<class Suite>
struct insert_suite
{
    insert_suite(char const* name, char const* module,
        char const* library, bool manual)
    {
        global_suites().insert<Suite>(
            name, module, library, manual);
    }
};

} // detail

/// Holds test suites registered during static initialization.
inline
suite_list const&
global_suites()
{
    return detail::global_suites();
}

} // unit_test
} // beast
} // boost

#endif

/* global_suites.hpp
iYsF53zK1SkKHM8wzuN0JMqj9Tg/MSF491TajWCTFIf3mv9gmkt4+TrgZ8HSpYuj+habPGRTRUidNn+une0Uyrxk5Awp0qY3Yoq06fNNKdK2u1YkIB6ClBfisIkCnMMKNVmMIM7Z0CJ87Bedy6k0m3C2ymlWrJcWx/rwm12XpXEZBrHe+Tg3mam/nGl6uZ2shMW6MNqyG0sBxpY1J2P0NoCRAvXW3gUqxLaeBMmO9IB/W4aw/z/DmseFZMdFF4RFNOBcNKRdX7yLu5xQHpr0eOv0ODWIb4tADnqbR53ThOFa/ltBW07urE8qOoKEtx1KVtr2qft9sNxIPw020QxL7puHU0/Y92EVrfs+H/s+xhOaA+aFA3bkdpvi8Kiu3p6cgdsDTm3Oq4kGcojDIdijH0e+Pskw7DyMolb44ILB5rh5Mn5kbWcLAaG+xwh2Z5W31/sbuPfovLdT++1FU5+Hl3dk2osOJjMra814OXlQG/Lnzp1PJH/+97T25c8zDfnzh9M6lP/uvxKvmqbwp1wjbqUee5ACRpR2MgJG5ENAGjGVh2U0GkCjeMIUHS5WdC/tgdPM81qM8zqTKA/6rofmbBdoRsp/3QLTkiSUws9OBmMFcdLgsLds2gVpviZ3tymCVo+jPYCfWjdVDtrwPLMMGoMTbP4PDJoTqssoLUbcIu2KNnJaPZJyojW5bmpr0KG1GMbD0x7vZkqZ12dq
*/