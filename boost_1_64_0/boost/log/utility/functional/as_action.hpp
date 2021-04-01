/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   as_action.hpp
 * \author Andrey Semashev
 * \date   30.03.2008
 *
 * This header contains function object adapter for compatibility with Boost.Spirit actions interface requirements.
 */

#ifndef BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Function object adapter for Boost.Spirit actions
template< typename FunT >
struct as_action_adapter
{
    typedef typename FunT::result_type result_type;

    BOOST_DEFAULTED_FUNCTION(as_action_adapter(), {})
    explicit as_action_adapter(FunT const& fun) : m_fun(fun) {}

    template< typename AttributeT, typename ContextT >
    result_type operator() (AttributeT const& attr, ContextT const& ctx, bool& pass) const
    {
        return m_fun(attr);
    }

private:
    FunT m_fun;
};

template< typename FunT >
BOOST_FORCEINLINE as_action_adapter< FunT > as_action(FunT const& fun)
{
    return as_action_adapter< FunT >(fun);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_FUNCTIONAL_AS_ACTION_HPP_INCLUDED_

/* as_action.hpp
m1SY65KFsVyTd3VBpwM/Ic69J4Q933kDl3aJntsh1MAi5vXBxkglfCzlYFKgJ+g6gC2y9QUmJ7IpzyNFcMMQY9ycepBik/EnjuCiwhNOd/whRqPUYa6odbhn5aEkokKNrYZ9jM4mnmv7e+g1MAbM8Vdflh7ZhJlHRlPRzkuCv+0l2cf2QjIJh8P9iVf6tEzSxyq4ATdxyCi0wemSG1MPMhFBCxVWH64EvBE6gJ76hKi82BLHKensjU5+WOTrwCusXieuqdYLA+cWZWwXROzPFG6YxBna+qtQX0zDF23FtKzua51YRs6qcHglj2G0vk38CE6uOU5YIevujFZ55V8D+Ed26yCmJquoikraB+yZkjqiq48Uc7ng4rQjCJM9VQuW6yAxCq/Hho6xW+PA763L4ErHiFqgKVqJbAlXPjqbg5uFLSplbDYzh63xFX7lFpUoRRnakt4c0DfzBiMG9APSvlei+zC8o+N5HNqIaK7MU4PohrodQJ5t2ov+QkPJ2TMF9T4fXC3CmG/RlYyofFTUKPOfMXiS71chJ5gc22RDKBgDtIurbtPmn/LYKA==
*/