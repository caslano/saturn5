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
1mh+7y7Gi0D+vW9zG9ZFoHNf/mE8N+020/PTeIwaZuMFh+sh+uMCsu+3blfaW04rBy0R3JfarKN6hWuo5SG0mq/49+cTdHcJhoo4z1jHWK63NiQ39OT1TjeHZlxZSGGpvVJ6CkXYZErPbNjnkf2gdSee3NK6kN3V9CTCtVakJcpbjFPink4FhX+H0jFSxJ/oMR5J4wNkdOODfrzhPhB3O+Tw9aFgsuNX8pTHQTjDjxbxxeri2ybGQmm84fb/Hcn5WSK47f9K9iRrL4yno6F9PsAaIt9pFGNJPqUjX3yH/gLZxyl++LVbFu5NBvPv7KeT+0/KLgXlZTIuvUgyMXXGRXfzyf19ZT3iUs+ufd1n11w/7yMvLUVcvcnNXwmwPIE94GgaN4LUNS7l1UvzTeNL9Iz2LKeQ2zVUxi0Qr/jOMT+rLfS2YF2GXU/D8ZLH5Qv0nJZWsot22cvwPugdFO8YpB92gzYXzON0GaXznHIfyqIuHQbF9OxPre76L581s9T9Ti2h+NegX4+whHFfCiC3V2Bvb5nI+g2GiLQEwQ45YfeCzMSgxtJdr9dNdJH8mX8XsBP/PgpClsbEF0HYQTFGwq9++g7qGhsnGIyNC8mN+r8YG9GHNeNlrcF4uc1gvHzrdjFeau5ZLeffli+1YswE54M78NzYO4zGS/plD6ZqZfnl5fl58i2rOu6dcFwx4g5JFtmzrB0sdrP7NhymizQeijtW2eKeiU5ujTRXUXguEsx3/UaRXJ4ljr+lPZPCmv2mjscN8h9hbYm/pfGPwyk0D6kV9nJ57BF95Gnye0+R+o/oa8fI79067+aPJZmJmJ96SWNSRXGpNM7+iWQqFZcdv4TYQGOSlJ4FYu5y+51OvxfYrsp2FXOqk5xe57NaU8vAW13Sr7SbwgezHb82ILsXbuFMpHIuM5lvyL9v/ho8xeYczNGmFE7MXXYKfT1XpktkxYbfPg/hu2loW6Kv8XdtqR2ZzkNi79Tq4RnNdjvbe25gez3vBxnfAzK7N3Tl91aM7w2Z3Wcxu0/0z7vnsojuE61eMv6TN+eVrraPDYjPWPLIL/9994OM72H98+5VXen9Kbrno64DeX3sq2ju+dD3gCLAX8GWoJXPF+xgV9ALHAZ6gyPAbHAq6AsWgA3A2aAfOAcMABeDDcEVYCNwNRgE3gEGg5ukewNh4BawCbgDDAePgU3B18FI8AOwJfg9GAX6ODsw6ADbgl3BdmB3sAOYDnYEh4OdwPFgNzAPjAWLwDhwHhgP3gwmgGvAJHAXmAI+BaaC74M9wM/A3uA5sA/ojfLsC/qD6WAXMAPsDfYH+4MDwCHgIHAYOBgsAYeCi8Bh4FJwOHgLOBbcBk4A94CTwf3gFPBZcCr4MZgN0veBxHyc1jNUv0n49wHQwvcnOoJLwWvBNWAWeBs4he8/FILrwFvA9eAqvgexFrwL3AjeC/4R3AQ+Cz4AHgO3gCfBB8EPwa3gZ+B28HtwB5+XPwT6gbvAYPAPYAT4R7AjuAfsBe4F+4OPgdeBT4DF4H7wRvAAuAU8CO4GnwL/CB4GT4LPgW+DR8CfwfOgH8rrBbAFeBzsBr4C9gJPgBngq+BI8CRYDv4ZrAJPgdXgaXAZ+Da4ATwD/h48C+4A/wLuAj8ED4Cfg4fBc+Ax8AvwVfB34HfgX8GfwQvgr+A3fH/APV9BnXF/bY9/Z3B9JvD9j0QwBkwFu4A9wR5gL7A/2BscAlaBY8G+4AywH1gFZoDVYH9wJTgAvAMcCG4FB4G7wKHgCXA4eAocAX4NZoLfgiP5+06jwThwLDgIHA9OBSeA88GJYDU4BbwTnAreA2aDB8Ec8FlwOvgRmAd+As4A/woWgJE=
*/