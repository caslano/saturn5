/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   from_stream.hpp
 * \author Andrey Semashev
 * \date   22.03.2008
 *
 * The header contains definition of facilities that allows to initialize the library from a
 * settings file.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_FROM_STREAM_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_FROM_STREAM_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The function initializes the logging library from a stream containing logging settings
 *
 * \param strm Stream, that provides library settings
 *
 * \b Throws: An <tt>std::exception</tt>-based exception if the read data cannot be interpreted as the library settings
 */
template< typename CharT >
BOOST_LOG_SETUP_API void init_from_stream(std::basic_istream< CharT >& strm);

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_FROM_STREAM_HPP_INCLUDED_

/* from_stream.hpp
vXZ9VJE7pf+i58b47LvfShx99L7ryM5mIH23nttNysOm9wxunv4asdPany/g7z+zP3fcqe7PZ9gG4j0g77rDLYu009IG0vABycLg7si2mPAaskjnbr/c3EeX1FKns6RSOmfoCdWc2RstqcG06mUaw7Pyp/mOVaDWGCM3eNOaNS0/LXNyxpRcazrxW5lO8lr0rWbnZbrDsI3vFP9l2u0qnazsQ+9ImEext+OCmx7GLSZHe0rs2wck3L1aLnq3uOFXmbjN0mrD1Rs/+dgPtjP+uchBE5RnhEnna2JTr56fU3FO+gd0Eu7y6MwpKKhU5lJO1jLvyeVxB0bSHnSX+7u0yyjziRAGlJMQVdswdLBJ+LaqOmBcITYZD338/734N7ePbwpe5ERAt6u6WvwTaeMTFtncv8Xi/AWB6nmz29FmOs1j/2Ce99/LsX8h9QGWGeUl4odK3Yh7JMxdMvZTZyb5kq3jP/Ps1Z81xdDjekD87kC4eF3vjshdpqEg6yRWqXv5WqU+RP6mjh0Z92LftY6Lbfl7Qw+rjE85J1clLI8VnAPMfddSHmmYn/rU93uXhF3GPOq8JWhNheZyoXsIy9ZqL3up+M3j7xCtWH7XtuhHmmiax/5O/O/lbwlPe/pD4lJRx/NjpM9h3hAfHRMRGRofPQl/m0ZfEj0AWhnDYmIjNV/lb6k31jPjL1bOPWIctEt3HeyoVCenjDqx9umiOna5sI/Bk/qeXicW0VNJ73rfc03wBTZ/XO9Jt+U7FFPXnqYSpDtdnaY0fKCrTFd6NdKlt9/linQdQFnlW9MlirBMfVotmxRgetj/LHU3j+f8USAd33LPK6zpyZ4pSXL2rRZeq16xrJnq+STCWr/rY+LP7btuHUflfZZyT4hVtNEE9BNLPuXsvcpyL65GuevtMyvO/h3c5J4nmdPDVUwafjmeJzFtIkcvc2yIdhTm5Zr1Dm6SMNH2+iC/df6Sk6HbpRTZCPFvax0TGe8q8WssMgtJ8EuI4xooLALDmrN1kKpu6+t1GwY3b34s5RlWT12/5ary9EThqDzLHdZ1VXPNJT7SV2FNX+HkaUVZeTNyq2yDFQ7TpWqD+txiJg+zVvFb+pQuNFtmTlOhcl0ZLmFKtBvw93blupLxWPTIUsce57lNxT9bu0Jtq5f8dv2E+ly6ofjfgtWmy77eJL9tXsO22kn8RiK7DQz9m+PFrZZt/ajPm1uIfzraXJhhT3dubPXWkSgX37oH+R1OKbN+h6fw92auGW81/K1j3k7a3a/gOuxL0A73voFRv3LvJrfIx/7d3yTc25CZqK09p7lUdcy4ON6wjhilMS7sljChWn3W2z75fVpbg7/vgJT7DLa6n5oxU62b0gjbFePOHLygJ/K9ES8ObRkRFdooum9ERGhj/BcRERZaL7pl9NWQoGoQFpEYk3SJ+08TW12a24tug7z1+x692rVQM320cNoICGEZ7dK6oIxSceq8CrhZC/XZhuIlnkXaZISrL256HNu1ZLgu0C5yNGer3J7qW75/rANbm0IZsk1d+L61TV3J31vYpia9r25T45MoW6/r8wPt7y5GQr1tyiN6XOWeovaB830nhrXtO9nagzLeKe6wMjeONfwjDR662cYKPXyk+DUMaO+huvtGEk5Pt9XN8l2pSLLO32qDtrrlNL314THokyZ3Baqc46Z8ENh3hXNc65zyfD0t3m9eDNb4fWxpwnrXQZr6VCNN+rduDW3yH+C3bj9oG8bCVCNNci1ExrHNcA+hHSTN9L25W8KuYMyKdQvTadMNzfE0Q/y3ia2d+SDdbsUqjjtZ8SLPKf+n4f/l4q6v9ZycM4TH7f7AuxdTn+Xhzk+inh/2/68=
*/