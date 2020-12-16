/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   process_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/id.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The process id descriptor
struct process
{
    typedef unsigned long native_type;
    typedef boost::log::aux::id< process > id;
};

namespace this_process {

//! The function returns current process identifier
BOOST_LOG_API process::id get_id();

} // namespace this_process

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >&
operator<< (std::basic_ostream< CharT, TraitsT >& strm, process::id const& pid);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

/* process_id.hpp
PBGph6xCpOzrN4QbwFEwEabDRnAcbAxnwCYwR8fRubAFvE/tP6Dj6J/pOHoXbAd/D9vr2sIO8HXYUdOPtQn2WNDQb8qWIVn9g9+BPY7wjl3GiP0H2uNE17daGS/qt1Vx4/gOahbifIeZuIVv3G4JjSdDR+gIHaEjdISO/9fj+3j+50MG38rzfxJz+bcwuNp1hf8tUl5WFroM0OIT0KnGtSFpXFvuv7Y0e9YC/z0LxXwo5r1X+M0JTkbhAsawMpfwI51L0PXjcnRFTKQLMgx3ZUft5z/mqueIr3pb9/OaQyfPZ+KmvdHaU1e5+sm/2sH3NfY+/s/lWhvGlD4PXeDeeizs56Fy3xNcofMj3dRRisQJvmXHiU33VloZns+fDWAPsd/ZKy74VTUd8ecK65qwijrshxPWfDuskvLywoBL5cPqFTbcVrb+wFtPltoX/e0lpF1vwnQ7AUI7Sc3omDqqM0Cea6ulZ9wZZ9GH5/H+Q3QeaFoUh3unxcZgWmidqlo6bKxmOmDfpZfmDpm7qbpemqrG16p7+/RbgmO17o3R+B6oEN9AHaQEVIh3gqVrU9yMJC3RdId46uqsZnpg39ZJvwIP5hPeO0mT6JpmVNeaYdE16xqedflP4m4Yexeau3T93yXpWXVd/1VNz4GankWq8IZ9GuJnKkzG/uC/VEjPxYvsFPWu/7FwJO4sPVX4p/585kxTzKqXppZ957oV5/zjRLn+pv29sbS35d2/I52z7PD9Tuz67PbqOs6d6xVGy/mvjT6YLUOSrPVT4uciMxKXozCfggT9LzI6qP9r/e45DyPkMbSiF8CxxHoCnA3nQ0vX1z1it5PYbYRY82mxx/zm7Rz+zzGStJyMEzfJvun49TFhMEyfHbefy7Vwh7tC+5s3uyT8mc61IamGo90+X+5Z27Y/SM41jlLYFgTzWK41qLJul6qUSX/fO4J6XCz9deH8nLlFhanl5l1bRRoaq8BRgDTBH+MdV1l1dPaVl9NwcZPnVefx71/rp6y6tV3DW1Md1UBuoi6XBsKbwWgoK29phnO8gBfnbjtbkFZFMHeGQdnJmJ+Tle32pIrzmmvvNDFf2+rArVdMaDOzy9CcU59sObjkf3de87TOYXJIm5wIL0Bu19/nqb6Ryda4S8d4ieX2bQ/SfdsXwBg4BDbT81ZwOOwAR8COcCjsoufivzUWgt08/L8Me34uVP+L1H9r3+US9X+p+r8Ypui5tX8qX/1PVv/t/VO6b03GfLA5vNKxv3ajy517f22yujsP1oGtYFPYWv1pq/7Mt/pB7acTy+2n66r71FJgK5gKu8HusBfsCXvDHnAYTIMj1XwU7AbHyLnqAbH6CO3HEmFj5Jjer4+Ge6TedxQMgxNguJpHqPkIeDGcBtNhHrwEroaXwjvhOPgzOB4+qf6cgJPgZ3AqPAOn6f626TAazoB14UwYDzNgMzgLtoTz4FqYC1+CBfAVuBiaPvIddoHFUPLZaqtAoUc+99Jy1A8WwP7wpLVGVN3VVHcmEqfu4rG3AU5n3rcYKd0S+b3PO2/jnvuRE0jE1kijFTISyUVKt4bmo/8dx/fw/F+QL0vw//Xnf/8z+72O7/+P1OfbtUgjZBEyzq/D8migL+bmGc7vQOfLWvvZi+d6Pyfhrvz6bN6Leuqtd9u9JM1vl7vlB8evmXJ9mrd+5aNnf2er9+cg2RzrTheKu4E8TdSwvnMuzxFLm1CNEf8YY5Uzb6vwftWfJvGaJu7vB0nc7XfpxBEzieNZ37luQz6UMUj8nseavTNw83MDmi9ulPPc6M7VH1NUdyzwz6ytS7fzQ8oRh3v/eT3Vv9FA++U42BMmwL6wIbwEJsFFsBnsDQ8=
*/