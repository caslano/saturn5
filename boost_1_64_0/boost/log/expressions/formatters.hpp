/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   formatters.hpp
 * \author Andrey Semashev
 * \date   10.11.2012
 *
 * The header includes all template expression formatters.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/expressions/formatters/stream.hpp>
#include <boost/log/expressions/formatters/format.hpp>

#include <boost/log/expressions/formatters/date_time.hpp>
#include <boost/log/expressions/formatters/named_scope.hpp>

#include <boost/log/expressions/formatters/char_decorator.hpp>
#include <boost/log/expressions/formatters/xml_decorator.hpp>
#include <boost/log/expressions/formatters/csv_decorator.hpp>
#include <boost/log/expressions/formatters/c_decorator.hpp>
#include <boost/log/expressions/formatters/max_size_decorator.hpp>

#include <boost/log/expressions/formatters/if.hpp>
#include <boost/log/expressions/formatters/wrap_formatter.hpp>
#include <boost/log/expressions/formatters/auto_newline.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_HPP_INCLUDED_

/* formatters.hpp
5XuonwNeP1FrX46Pbh8f2d46r178ZkSRP/xGZsedGzcgOob58hGRycybT447lb9S405jNv30uMFc6cl5IldSPIybJf8O4jwB6eY5Q0YxHi0lMT6yxzTul6jjmB5KCJRP/NyO6d//CHIzfzcdv2XGzR0R3aynJFxi1ma9RcpNolnn/4D4ed316OZgBP3Y5PefnvyuXcMyAOnRUfFdE2Wsto4huDlF7uu3VqeMmTX3HDk9WkZXxjkdRY8y/lR1WRDlnQufaZ0L7z1/qBVrEacEjHEx76cZ58I7hzvvnPqNN2NfzLsk7gmQf3A374G4y5rNErcp7wFjAW9rzz86dqYXvA8+g//ZeaYukWokxLhGib9Q/N7hXm1f/5y4rHWIqYPWy/VKN99pZxs7RPiQ9YgZQ3id+NmKXTTSVl8QR8vv/xfET5Kl/jDhQ5bR4kYdYBO6wZTRrjOkjJo6YKn4uVXKKFl19kZ7y2j+cZXRe2YEltGZhE0Kfhd5t47vffSU3Sj/stuKOc3HU25t5fNcHbO2P8Y3bt1VO/ce/FfOtIzDLS5ftqqqrGb5ympTaKXM2uaXSPhJzsBQ80tmWsuspXwavyGf02VyfRDPqbuZr/OR6FqfsW2e2nHq2n8M8zHtPl7s+Pg8uttrdBc8BxqguWWtmmtMPAFj+v7Vivm7nZx4wG/qLMLqONXoxr/T82aOkXPHnI+W849nes/PlPP3zfkZcv6eOc+S84PmPDP0WGgtX5s72Mepzp51fONUZ886eeNUvWlcF2cft1k06/jGbRbNav24zaJZn+64Te9Y3Eydb35Q7fP7kecIX9mYRzNJQV9sM08i1jGXcJuU6LXDfkfCFYpbquZ7m7its7/vs0J851JsD3j265Xrz/n2bpHzDtbfGhOXWW9+GfO2fPsvfE2u75Q8/CJLr/Pe6fOSfYu9+xzMIcBCMrWLeDaSrrmcv8LfI6HnOfRq5Z7F8p1hmfMhexQH19eSBtKGm0mbGWe7yQ01nrbt40u/IeNgtw5/a+/diXem3/fBC+PvOP+Tb4UeL2offxtqfGzbx/eerPGubR2Xax8nHGo8cOhxzh/6xopI22C5q2NofX/LN0cu7Ip8rH9PRWQckGnrSPuSa4HjgGp0fePV8BRYCzPhpTAbXgZfJvAa+Cr0nP9Gz9+Fl8N/wFoYT/xX6riKg+Ybi/u73Ffrgdf1vpzL+J/pMA3mwVFwNsyDc+ASOA8uh/lwDTwPXgNXwVtgJdwIF8I74CJ4D1wMn4FF8GVYDA/CJfDvsET3A14Ku8NlsD9cDkfBL8BJsBzmw5XwOlgBN8FV8D5YacZN6neD6j63ybjJZB1P1hV2gt1gEkyFfWEPOAz2hMP1PFfPj8BN5veZvGn8CcgGv3WTPcyCqfBMfZ45sDccA/vrebpv3JKcD4Lj4XA9z4Bnwyw9PwNOhGP1fBycBHHj3Iyj4bfSjKOhbIYeb1PUCn9F3npXy1Juk/FZvTVffeCpfuNB0+FlcDD8PhwKn4TD4AtwONwPM+DTkQ7jeP43x+6Ex+18uuN2/hfG7HyexutsezTWeRZ5E0nYxfuJFCA1u8JjasJH+Agf4SN8hI/wET4+j8dnY/9fxdZ7l3qGAJyQ/f80+sxH0RhPW+E6EY5sr5s3a9L0wpy5U8/NL8yflTd57sSZkybLOAG3r2PWPdrsOnIMQlxkILKXRnpCrvSpEs/sWXlTJy0snDx/Yp5s2SvrHDRdL9/Y+rtKuHRr/6nEadbD0j3H27iOtlkHvIkdIzcieJ3UX+F3dqh8yJLLsm9q0JojlrQTT9vW0rm7STrP9e6vHRG07qyks6jZdJpty1uV1qITTOs0TeuWyOC0vog=
*/