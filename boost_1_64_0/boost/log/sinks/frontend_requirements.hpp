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
j5a0m3kZXhXn+QD+8BeGLHXPd2QuMChlNSfwF0L79DHsmsSREv9Iz3Wm/WPidoid9+0t18mU+B12/ft4sWuDXVV7BsEp60J2Pf1zx9qf/HE8bP5uEh3x1PatWY1EhOTbtdizJF5aj67JNJHFRM5YLzF2vf1Hud/J3jHMcJzjWw+rJPHP8+8lbGd8a8NDxL2DqU0dtzYBu25VXeK7IpBaFm50Qd4YkYs9NF9p4qdfoBLzj/UwzTGdMH0wp2JyMedhZmCuZs72cVp5n0CAuYezuPfw+v9tmN1pZWdY78lknQfzLuY2rtsg0yc0FGLCdkv0nPy308q3/jJI7tGMLSoqluvcdfHOKaDvlmsPsfQpsUu2c8L0HQ1bx9rR/tUu3S+vYvcZO84IOAx50+ueiLwpLLGSphz6VISL2Tdo6869JqL+0/zndmQX55SUFHBLTtlBGGf/dckF9WvnoKnHn1+PitXzSPPXie9+MmK/P2LzrfXjKPceMWtpq4Lh9avl8N6OxhTvX+4jc0pK5cgfKiCq/BuqjFggYaYHU6iBfvS/XZhpgXruOf349WP781rx0zHYjnXVh7wqqtfGyvWGkH1t91z/gevRrhmcuF72adIrG7rq1saTYfPHeQmlEwpzxoY+1lJYwvKis56L3W3CrpdnSLonk2oD5zOB8O61H9URmyXuC4IxMt/q/L0lZXOolZsDJL0TSauZfS4sFLvnRD7FlqmuK+u1Fw4D35cw+wjxgUlVHcHBYveEFzAtJb+z6oZlMiM/+4y5UvI7J+jS68qTNC6ISaOlRxpOnZm14r+BPk8i/puI/wSvtk9nonc749OdXCT+Rnsx96b+rVy3cn+t+C+MXqvXNp4iYdH502dLOA9Hkofq2JWln10kotDqUCwTfxO98Jk5+uzytcfv7w25T6CWTrL39zexSw8EzUBWZO/3MlnjX0IjL00KPwOCM2+r3rdyalKN5Mo1gs1Z6E+qImv11yFjmoZkjO5zf60CZihhJjdmjhtjn0k+swKTnxFah9W99fptl+sxN2Heywzr/bwPyaN9Rk2tVz6dxNc3RJ5Lv478a+jf5+vow/qsihlHd0vpvD56nJy73j1OXqo3UVn1jBJgSmjR5b7Iuiff58jNyR0bGSfnj47dh2/7ZWcJ84hZ4da1I87yn1OCX9e41o4th4j7UnMJNg755wivz3Ftr9PE/RD8VnLJQcI7z8GycqmWuH/FGkDAJQc1fPzvOx0i7p/4+nCp7fP1YHNxn273vH8h18kmpv9Z2bJR3DPsmHSlXA+lVx9t2tOfqvu+MVJI38iCbTGhtv51mvQXKO0dUz59t6X3RY/Jvrov0vYrfq5L7Pgr2TH+cn1r5lhtx730gJdReg5KAaxLOx60MW475iVf/ozbnl+UsNvNGlPX1Z6J29mebRsZIe5DvM5eUORtVRtmlJdvPrNxqb2rvdnn4mzccXW1dQ0bv62NFveBXpptazrLIdMPZX3qOvHXyPN4Isb61RkR+z61Rvy+ZBaaFraN3rpJ9M2tbuoG8RP04rXZIeI/zT4vjpXrc2mzh5ojiTeiR35Hqk+Oa5ulDYvsfqRhWFfzA5XbtGPcKtaO926MbsfLN/3z7The+0zAXkpT1yzGm3D7TL4/fvukFidM2f88MatnlCFhc8xppHSmqeJso8Tvno/QOq8r7oVmGP/nu/VPiKP83yq0fuPU+Ynifqit805yfRx13sp0NQn6jUOpQ63L8n0Hafz9ts7kOut+W6e/uA4jZy3104f/Io804LWwFnW4NFyH0RW4f73ZvvOU+B/mtTQ1PFedLXXXmdUdv1fci7xuSPadrIJ7XntznNfYWXcal51z8HTOIaI=
*/