/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   fake_mutex.hpp
 * \author Andrey Semashev
 * \date   31.07.2011
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_FAKE_MUTEX_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_FAKE_MUTEX_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Fake mutex that doesn't do anything. Note: we're not using \c null_mutex from Boost.Thread in order not to introduce false dependencies on Boost.Thread and Boost.Chrono.
class fake_mutex
{
public:
    BOOST_DEFAULTED_FUNCTION(fake_mutex(), {})
    void lock() {}
    bool try_lock() { return true; }
    template< typename T >
    bool timed_lock(T const&) { return true; }
    void unlock() {}

    // Copying prohibited
    BOOST_DELETED_FUNCTION(fake_mutex(fake_mutex const&))
    BOOST_DELETED_FUNCTION(fake_mutex& operator=(fake_mutex const&))
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_FAKE_MUTEX_HPP_INCLUDED_

/* fake_mutex.hpp
3Igg0x3Vd5ozZ45NTxfzk92xmF/mPSeLsde8BZ6R1wSdl54vMutcbXA7j1jnmTJfap7ox7jDCIHFfuUcr3WXcdZigch1Iv7a4CZ63K0QvaWuDoR2MG5yfpfMr1og+m04YsIzRSpE/E0AuRYY4Rc3b/fIYTdW3fuV3J/P+88w4+SnovcRvo6jP3+GvJ8L8ONbRP7DCGzr4KuaN3+tLLvx/DXSFP7VNIVehDkmV2Wfe6ppQMfJVU/erW3uQkqI/fntUGMT8eOghvNR2chA4qc/+qQPiXSH9Isd+7jikOSjjysa4fK4Ha9uyzi++i9K583nab/zBaiBiZ6MbfqvYGGZbcsNnq9+dR4rVbtui9wcp3FS5OzrOL5OMFRz9oawhmu2vivjfo4tjPk6UW4dyo26E3UuculnNIRxUdmSRvuKnI9t5vYuQtwpnGrfbXl3cxcvWug4Joys79mRs81vzywxG2/Ozdwg9735poaZ58/fJ3pB+p0z7t2WfTYcz8uCzZ+n7wlvvIY31hafEi4991fTdbhLrl7qUE9N166GOF1YXF7O994Wrc1K57jhsx+Jzu/Ub2a4x5xQJbZgPYsl/dvWR63QhDVaLY1CnY3srob0L/5n15uCRYVFmi6a9D92fedflTEZ1TFdIOs771rnJzvPHUK+6bh5R8zTGDcMM/PVUD2X7YVm7G9rSwsaRtucLQ2Lzzxe9bM9bksizTFQudqjJnny3WCfuC0q9cRts9IGdu3zMPzHLbL27+VZx/i9tMzF0PDbw7m3VeP5e4Oxn+MTTq26+NRdHMOpdt0+ceIYTmR901BxaWFRqfP8Mx+3zxC3ObbTzz5FOT5xmN2COLSUpRqH9ni1pyH1s6VMxW/o4zefdLVO5z+vcONH5QxPfA9piG8ekFdQsbgE42blWez61vHKgNRnIgxznpTNyO1OV4FpV8185lAyW66/U9zbZYNDVDbDMe59/cRVXlpcSHi03lYj5gss5vMxb6gT3iPmo83zfb/w3GtdbKDE5OwS/GnWRdeIOTMkNczqvk0ev4r5Eafnq/9i1dz7vOuIo25+/ThwaMv82FXkOQtU/Wh7ht2fWr+1+YM0NEPeyVs8PAvZQ+Tp6i7Upnlxlfze5ajfuD4Z0qg+EgWYRy/+854pucb7u8eESf1Pd6ne8ga9gYbeN0NMvXSXUTc19TL9f5Mt8zsbzaPVNGibx6lpzVgnIXb1nRnuEX8euRK1K+/R1MtQvWbaPWyza8/Da3Q++DIC2QYugcM8efi0hjxMA0aL3WbmYewa+eWsRJEd5Dzv2S5rnqFtWRNUKuYz3Ym47G+d0jyRmc1p76EWGWkDyDMP6Xm+HaLRtswljuXuT2I33lzP5LtmqV7tqt5CDYfEvVPZ3wFWipuT3e2QtPhnAUWz2D2odgfEij4vxevmAV0fdXqM0W4kii1t6l+Lu3HuoeSdttzv52FfYzDMs38f6i7uU7B7n55J+x7qBV1/9DLqfe6Ha7mReJQ22ZaBku4LF5UWSd7Y5L0noNJME72bVK+oQPWayB9nJaKn6QA9eSeWtpqZTnlH6Ok7Qq/eskZI07xxv9Bw66DhlsYxehKXxC96Er+2ND8f+56rI56PgUlwFP5LP92e5otKG9L8CDMdO6Z57Da/nmDIWt61Mf/VbHuMEJlQ9+9ckZY0VFhG+Mxv9msi00/vaYMMkvYK9w1pCE+Y7Zs6kc812zIJIp9pXdtXZk3fGaSz1twPSvDW2fJwc14XSUPyPf4ATyzXc4Cz4hvSVohzG8dMW/izUXt/hKYPP3UUfffmmrIy3zrunjjnul/NYNs71apf8+p+NS2o+9W0sO5X04K6X81/UN3P6CPcrOs=
*/