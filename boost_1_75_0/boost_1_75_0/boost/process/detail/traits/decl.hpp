// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_DETAIL_TRAITS_DECL_HPP_
#define BOOST_PROCESS_DETAIL_TRAITS_DECL_HPP_

#include <boost/process/detail/config.hpp>
#include <boost/none.hpp>
#include <type_traits>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/handler.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/handler.hpp>
#endif


namespace boost { namespace process { namespace detail {


template<typename T>
struct is_initializer : std::is_base_of<handler_base, T> {};


template<typename T>
struct is_initializer<T&> : std::is_base_of<handler_base, T> {};


template<typename T>
struct initializer_tag;// { typedef void type; };


//remove const
template<typename T>
struct initializer_tag<const T> { typedef typename initializer_tag<T>::type type; };

//remove &
template<typename T>
struct initializer_tag<T&> { typedef typename initializer_tag<T>::type type; };

//remove const &
template<typename T>
struct initializer_tag<const T&> { typedef typename initializer_tag<T>::type type; };

template<typename T>
struct initializer_builder;


template<typename First, typename ...Args>
struct valid_argument_list;

template<typename First>
struct valid_argument_list<First>
{
    constexpr static bool value = is_initializer<First>::value || !std::is_void<typename initializer_tag<First>::type>::value;
    typedef std::integral_constant<bool, value> type;
};

template<typename First, typename ...Args>
struct valid_argument_list
{
    constexpr static bool my_value = is_initializer<First>::value || !std::is_void<typename initializer_tag<First>::type>::value;
    constexpr static bool value = valid_argument_list<Args...>::value && my_value;
    typedef std::integral_constant<bool, value> type;
};



}}}



#endif /* BOOST_PROCESS_DETAIL_HANDLER_HPP_ */

/* decl.hpp
BAH2uCPW5m0fbqCF+UTIqXvb1VNRLj9jGNXtmT0iDtadblmL9ugTw66HisSWPg7gGwCGw8i22pFFQIf1yPdLtMhOnGd/5GFRN8yVs++2H4mVgJB7/+yEIoK1jOWN020UIGyKYcpsSmoqoECzjFry8gztDPUMQxPVNgLBPyPRvccAS+pjsUPxCPIVR+1Gc0aNe0GOIocy9GIIRSXoTVBikGU3qzj2lRVFPm+QtsxS6Cz2JUozxXWuB0m31gzKkebTl+mG/U4MWA9OZt5Jqroxighac5nz0udAnA8vvPV30NXxUCRfuGGeI0876sfe8vrF9tSskOEO9BVN8fTOxG+OuMxR4A4N0Ynx8n8z2Isjjq3HvSoXIMfUa591kBtSWUtr9z9IIHaVRS3i4zmpF4xzwB2k4l2023RfVemLXDvsRhP+tqr9rf+rDI5f3dTrIYkAexFybvpJ8QxRQhopGXfFAmHJ47KpuglaZls1vExe5jZcKyIN5zNrXVUP8Q1c92CzbhxQOQIqonFeBt16oeASv4dqrDlwBp9tMB7DzCh1OU+hcvsiIOa2HBE+12RMz/PtxwLP3Ju42zRPnMwpivj4Zm7z7CbzOGZfDSzvvNR2yGWpKwNhAy8fQb0sXYgjiKAuP7t5T5pejI2fmp/p+2TNei4vGf9aLG0ifcgiR9WfEo4a6rFID2nzOAI8CkOs2hKqqF+etnjxZnYMjtEk
*/