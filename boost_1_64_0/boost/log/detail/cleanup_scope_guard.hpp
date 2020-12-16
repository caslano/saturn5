/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   cleanup_scope_guard.hpp
 * \author Andrey Semashev
 * \date   11.03.2008
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_CLEANUP_SCOPE_GUARD_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_CLEANUP_SCOPE_GUARD_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Cleanup scope guard
template< typename T >
struct cleanup_guard
{
    explicit cleanup_guard(T& obj) : m_Obj(obj) {}
    ~cleanup_guard() { m_Obj.clear(); }

    // Copying prohibited
    BOOST_DELETED_FUNCTION(cleanup_guard(cleanup_guard const&))
    BOOST_DELETED_FUNCTION(cleanup_guard& operator= (cleanup_guard const&))

private:
    T& m_Obj;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_CLEANUP_SCOPE_GUARD_HPP_INCLUDED_

/* cleanup_scope_guard.hpp
kA+Ydex/ATnVfOmwvHr+UuJkGrW9tWNEONbzgcB6drApEDnHZ8uhqeFyrGdNw8kmh2k/Y4Ck0Y5cxKgbbx2rWwyWggLf31tZTr2HnnO9298rvljOyTOyKXabYCPV6NkCTXw+Uoc0184pq/fC/GxHm1XV4DpfOKM2JRxIymnO9U16gfbQ0qeLDRHt0/vEf4L06Qs1DVt929OQc7t4hzd/qvN7wYQNtDNHWGe7lGZYsfdTob4/0LkNAmywaRlx0/zhpnnGjXyYNulw87XTb9pOTbSd/GPQArVR9x4Spd9KTiXMpGvNdiIDk2elZWTk42Upt7g4tQlxA9tkSnba1AKHureHpbzS1612D6aJ/04jiX/7Wq8Jaz/U62qLhL3KcLI5Uws+IP63c95QsRMzJozxIZzn2BtQX9Oim0Q3RpqFu0NqhYd6osPMdvvFZ1NB0j1f8ijjuTnuvXltmY04f7qhEb50PWFGdAtvwuFuT62I8HDPefUqnG6mpBtjs/dyL+H71a/YO9zaj7QvSHsF9CNpF+kf98u52JdWewBsRKtutyebqC/8VjbPqXZbCK/9RRJ1mK/MchVK2EinvqPpuP6l+cE6/syMMvu1lGOP5rPYks/8TKexXu2+SLhdYvPhT9LvenE+jU+qCRb7Tepus50qdn40zgrxe0bswyRTf4eR+WJzrniR/73rYwH2YarFWt67VqlcA/6LY3gVdVMbjtLGW7WNG2mbf2fq9jEiRe0QNjO/K8l1S5hF15l1OTWz/PnTnLOWSPiGMn86tD3pWe1VnnWsLKes9vk/NlrfKdRI7Qyf/bzNZt7Vel6qaT4v0H6eU141vqvca/cV8fdYrvVzK4/Fvpu0zQ+SHtdfwDybqBfiASQc+RRpRH5iiv3lEytKFbLLEVN8drsc2RIm2mksJ769TlxSJ47zKGEd5wineVTDOs8RNWEN8f/QaCtXptWmi9coYrqYaPHbVaglYfdQf26u7lCxq1ArWr5Ja1xUn7yFdvKERNntP57Utjul7Fr/7HYQvDaaPij222g6t3WVf14/X8JKHYpbjMO4vaFYr9mAcXqT2o0ci0QgY5AmpJdcYvYLMW6Es+P1Wg2mSNghzL1RDv1F03K26WTOyd0lTEvH/lJ+/LZOfYbwZ14XV4cdJMwgrDO5dRz5I9e9Z7R/JO2RKudnrAy4Tuue5ztZtJ60ElKbc60oa4+czBlqz0P63NnHCqudnmka8oAPMg5MJg9rbenLjWgua8fAa9SpfYnreN2ZdmX3iP9GsXVyKXKP2kBLoKy7kRu9c1xYH7NM3+kc5w9zDNF58IHAebAlepSOm4G2a8ig+XfX+hVvW8v1JG01c57zfLetqs4VFpv5LQize55Zl3lphdN8i+IKromJa9ZlnoT1JuFot5mwgWNjwTXA6Zog7JnnoffmnfM8NPBsa8c8vbeQcclmn0fyKXXrmq/rx4C6rat2/57WddlTSDphYuabdVtQ7lrC0vdqSPjHjBTvLI3c6mxjh3TPcD+udXS+hOliNHS+PySNwHEnPTcvi0nFcm8xUcL0NZpQWp03bPfdy/4wu8Fm/m3jfawa1+irifXR9e6RsnotykvNz5yCe3nrs2MStqlYx9P1rsZvR5nCzTpR98D1rhmn0gKx10+M6rZ732qxZx/TKrJ2tdps2qDlpr5Nbk7CZsMCq411WetXyI488Wxr0GPnYDPdtA0fMDYn1Dg9j6+Sx0m2PMr4nFOUnV02Xlbg3P/PtpTeuMmF+yurx6xMr3VB3FeJp365r/7Cn4PPIP2vn0E67l3baS+60WIbab75t28tvEhsDcg+hvzdUe0k5Zl7wbJ3LX7RSIam+ZjaSVoLY+A=
*/