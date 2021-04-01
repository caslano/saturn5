/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    remove_rvalue_reference.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H
#define BOOST_HOF_GUARD_FUNCTION_REMOVE_RVALUE_REFERENCE_H

namespace boost { namespace hof { namespace detail {

template<class T>
struct remove_rvalue_reference
{
    typedef T type;
};

template<class T>
struct remove_rvalue_reference<T&&>
: remove_rvalue_reference<T>
{};

}}} // namespace boost::hof

#endif

/* remove_rvalue_reference.hpp
g6GVUz093Zn5kWtMpX0EEH4OgRmKz4cqZNdqw4G9dYRKrYwlB1nVatLnhrtHokMlsCC+56kB/PCU/lB+K+y2KCL9Qu4etgoo+9DHKHDGHMT3SQd5Zw/YxftlDXblScXQRhcZ0wBSsAubvUlHVmMx+yAnGDZlTLGN05APeulf6FfM1/9nErEYqg/eGs08bvIzdf2RZdZCXatC6CystigHb1go4+djRIIN5tmzarYLIIWyJfPiP3TexfwDo6ye7oJROpQLwlcJtdspX2eBcnjixj/7/4NpLQyizap4To8tD6rBfjasxh7jJTtxrqGpRi4dSo7mH2KZx2dq9pMev+FiZVE9m9WIYYsRtFYabKNoXAWg4+KlTzsRZ8QX2EGHtBXYn5rwpiKZU0QtZgJvubZ4QmbSnDDK823YL6fd2x7lBIfvjaU4uqAqK14tmd5n8FmPq1clSwAjAksW1vcmvVfowswE5tLaSexzfdW340NOYdk/ItjnRTrVryqnE7eATcgYl91zaZooAs8PWbItBXpHUtF5ciV+nq2KYvhOtQJJHnxKDXP+zX8dPXkztA==
*/