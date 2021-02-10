/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   sinks/frontend_requirements.hpp
 * \author Andrey Semashev
 * \date   22.04.2007
 *
 * The header contains definition of requirement tags that sink backend may declare
 * with regard to frontends. These requirements ensure that a backend will not
 * be used with an incompatible frontend.
 */

#ifndef BOOST_LOG_SINKS_FRONTEND_REQUIREMENTS_HPP_INCLUDED_
#define BOOST_LOG_SINKS_FRONTEND_REQUIREMENTS_HPP_INCLUDED_

#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/mpl/inherit.hpp>
#include <boost/mpl/inherit_linearly.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_COMBINE_REQUIREMENTS_LIMIT
//! The macro specifies the maximum number of requirements that can be combined with the \c combine_requirements metafunction
#define BOOST_LOG_COMBINE_REQUIREMENTS_LIMIT 5
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sinks {

/*!
 * The sink backend expects pre-synchronized calls, all needed synchronization is implemented
 * in the frontend (IOW, only one thread is feeding records to the backend concurrently, but
 * it is possible for several threads to write sequentially). Note that if a frontend supports
 * synchronized record feeding, it will also report capable of concurrent record feeding.
 */
struct synchronized_feeding {};

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 * The sink backend ensures all needed synchronization, it is capable to handle multithreaded calls
 */
struct concurrent_feeding : synchronized_feeding {};

#else // !defined(BOOST_LOG_NO_THREADS)

//  If multithreading is disabled, threading models become redundant
typedef synchronized_feeding concurrent_feeding;

#endif // !defined(BOOST_LOG_NO_THREADS)

/*!
 * The sink backend requires the frontend to perform log record formatting before feeding
 */
struct formatted_records {};

/*!
 * The sink backend supports flushing
 */
struct flushing {};

#ifdef BOOST_LOG_DOXYGEN_PASS

/*!
 * The metafunction combines multiple requirement tags into one type. The resulting type will
 * satisfy all specified requirements (i.e. \c has_requirement metafunction will return positive result).
 */
template< typename... RequirementsT >
struct combine_requirements;

#else

template< BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(BOOST_LOG_COMBINE_REQUIREMENTS_LIMIT, typename ReqT, mpl::na) >
struct combine_requirements :
    mpl::inherit_linearly<
        mpl::vector< BOOST_PP_ENUM_PARAMS(BOOST_LOG_COMBINE_REQUIREMENTS_LIMIT, ReqT) >,
        mpl::inherit2< mpl::_1, mpl::_2 >
    >
{
};

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * A helper metafunction to check if a requirement is satisfied. The \c TestedT template argument
 * should be the type combining one or several requirements and \c RequiredT is the requirement
 * to test against. The metafunction will yield a positive result if \c TestedT supports \c RequiredT.
 */
template< typename TestedT, typename RequiredT >
struct has_requirement :
    public is_base_of< RequiredT, TestedT >
{
};

} // namespace sinks

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SINKS_FRONTEND_REQUIREMENTS_HPP_INCLUDED_

/* frontend_requirements.hpp
KCPpdt7GVs6uaSIO2rluRec8cOj0KXeHdKjDTfOG9fheRSG56NcgWmvmcVseaOemVSpT1YesvBBumsZKcFayVODbjhmIHKM0uI92HW25Z5r70CqYLKvwuDsI6Zx1aZ0jSb/Ea3u2XC6W7Gb+x+zr2aCLwYWQIgKKo9uAui3wKKKcNhqdTokcVbj0jSBOELpESRYgkpGH6B/dhKUDwNuAa40XVDcluLXi1OA3b2i8Uw16b8ZQ0LWAF0sqMSqVhqXEuUBOBaXbIcQq0AL5jnQK/ZHaG2st22qxqxO+5sqcUifNFqGB2dXcsQDXbTvdNNfM5jk2LHSwOABnL6XGbl/I6l7LurOM4LfR2P4QVDMOUbzvvzmM3MULCPveT3L9LELbztXt5SVt/RIbslm3F5uZ8pIaDRbZ4tzZf8V7UV3R2mgG8B8MTRzKLO5nG/ejPGlZ+0nblOvnuzKJ48fdOkvo94apIEsWJZsvX08xGi4e6Uz/Pt6xplm5yvmA0ysi9QbH0uA9T4rX/yUlw38BUEsDBAoAAAAIAC1nSlKutwhDRQgAALAUAAAeAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfb3BlcmhscC5jVVQFAAG2SCRgrVdZcxs3En7nr2gxFZukKNJWaqs2vhJaR8KK
*/