/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   common_attributes.hpp
 * \author Andrey Semashev
 * \date   16.05.2008
 *
 * The header contains implementation of convenience functions for registering commonly used attributes.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_COMMON_ATTRIBUTES_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_COMMON_ATTRIBUTES_HPP_INCLUDED_

#include <iostream>
#include <boost/log/detail/config.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/attributes/clock.hpp>
#include <boost/log/attributes/counter.hpp>
#include <boost/log/attributes/current_process_id.hpp>
#if !defined(BOOST_LOG_NO_THREADS)
#include <boost/log/attributes/current_thread_id.hpp>
#endif
#include <boost/log/detail/default_attribute_names.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief Simple attribute initialization routine
 *
 * The function adds commonly used attributes to the logging system. Specifically, the following
 * attributes are registered globally:
 *
 * \li LineID - logging records counter with value type <tt>unsigned int</tt>
 * \li TimeStamp - local time generator with value type <tt>boost::posix_time::ptime</tt>
 * \li ProcessID - current process identifier with value type
 *     <tt>attributes::current_process_id::value_type</tt>
 * \li ThreadID - in multithreaded builds, current thread identifier with
 *     value type <tt>attributes::current_thread_id::value_type</tt>
 */
inline void add_common_attributes()
{
    shared_ptr< core > pCore = core::get();
    pCore->add_global_attribute(
        aux::default_attribute_names::line_id(),
        attributes::counter< unsigned int >(1));
    pCore->add_global_attribute(
        aux::default_attribute_names::timestamp(),
        attributes::local_clock());
    pCore->add_global_attribute(
        aux::default_attribute_names::process_id(),
        attributes::current_process_id());
#if !defined(BOOST_LOG_NO_THREADS)
    pCore->add_global_attribute(
        aux::default_attribute_names::thread_id(),
        attributes::current_thread_id());
#endif
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_COMMON_ATTRIBUTES_HPP_INCLUDED_

/* common_attributes.hpp
bOPi+eh8HuOzYynX1sa0l/X07Q8t148BwA6yL6/3eEPJi80hH78ImMt9iCGy3/B44FTy9Gdyf+VZwDv5TdWF3Ld2OfetXcl9avdwf9qPuB/0J/RL+JJ+CQfoh3AY+A/y8u/SZD0S3mxt4EJgS+Byfpt3BXAQcCVwKHCVUW/g/Ua9gY8BC4GPAy8DPgO8ErgTeDXwNeACYDZwFXAg8EngIKO+wIuA7wOLjfECnA78GXgFEGNCu9KoJ/AGYFPgjcDuwJuBI4DzgaOBDwBnAdcAbweu02TeCu94HXARcDNwMfAp4BLgC8ClwFeAy4A7gZuBbwOfAH4L3ALU3V5/gFTgU8A04NPAWsAXgBnAt4H1gXuArYB7ga2B7wLPYfiQ9J88q1jmf4wm5y+/dpz/HYGRwE6c950577M4rrsB65Dn2xbYA9iNfN+e5PteCDyf47kX14HeQI081uYfnJjHmo00hRDwWf+v9y+e90HUaeevLv8gqkIc1pPlr27GcfZCjkJS9kVprSAXQy6DlEBWQ7ZD9kJKIdEfhniroV/oF/qFfqFf6Bf6hX6hX+gX+oV+f5Xfn8T/Bxr0/1Pb+199/3+4hf+Posn9f9Fv3//Z5P4nKzsP5GoYgJofVBxvoegaWxIKJwf/XTI9f5oj79huv5ZyLDzj4UkV38+vgPwhVedWunOdsx3qLHb3nHHTc4typxbn5wdV5+w/oM7KP0DZDGuQG1dorbNskWZt6eDaufA01lnx/7PJRX+cNrrHINeinZcftPg0IGNOYe6EIuG8ZNZnPVvkBN4/0VtXST9deArSS6Onj21hcgd2S5p4O8/Bl996vMwcZ/5+ucfLNI/3naRJcP7GvWpbHz/a3Kv6nxLXTasETR2Ulqz2GBN9P5xvda2RVstxv7RE4FpJt0b7u7+fh5yPjxe5RtI8CL983Zqmhe/74hskzTJwiMI1te/gsCSvDPeT5XGGnHjvMrW/ndG+SX79qfaNnS7zzuw30Uf7p8/0pY+zpc/08mc4ztbSwaQ/hLYA7TqMs5JS3zgjH9A2F1QbLZC0vbQ6Abi0Uhbb+Fii7/vv9vFlTVvs4/nbx5YtrZ1n+obEJ5jfuJgdZ/RDhXmV3nNl26P+Ab57LvW0tO0O7u/fkYV3gMxtbxjarW3b3LltZYyHSdrWWLMqO7Utygq+bf3TJjjwjtpJfNgJ2yuYtczeXta2qVPZedxl+7WNjNhyxt2FP5Q/7rIr0DbZPwQ/7qxp7ePulh/+s+MuK8p53G0v27bNA4+7508w7rZXoG23n2Dc/fInjru7opz96uIOmW0jt2vB+tQp/n1arOi1l3ScF/FllFv4rZSLEuUew9bebThmiiXdc3o7tNhIyBWo/b0YbRs1D3guEVpNSBNIF8gKV4xTn+BYwftTSVq7P5V5TXtC4rvDv1G3zwGV3+43Zb+Gm2nt/T+U/b9B4pe4dFw968MvYCDueIZgVs/GFWwx/r4XVsdHINs12JFQymfAw8BIVyJs6fAxQnu0dyVofYAjoCty1Zf7hRvby7Xa/E7EFXKcLXpb/D8cMhcyH7ICsgmyG/Iu5AvIEUi4y6VVhzSEdIQMhYyCFECucoWJv9Uy+MHtQh0S5Hhq/9Sc0f6c48zvjOOmmlzM9VIPt/r+gckTXgx5KQPXDcjLkFcgr0J2BuUrEi3jcIUcyxfORlhxhut+p9u+LxDn07VROk10Vm7xdwfs3OKPTF1mO6Xb69OZx3jSpzOPcf8Bu6/RnT5dK6W7xqcz6zLNp8tUujEH7JzmC306s879TF0Ls84tfTqzLrV9OrMu0T6deYyIA3aO9PFvla6dhG83w62c1qxT9olS+8s25gjpw2tqb7U=
*/