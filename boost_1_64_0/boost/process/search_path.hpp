// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

/**
 * \file boost/process/search_path.hpp
 *
 * Defines a function to search for an executable in path.
 */

#ifndef BOOST_PROCESS_SEARCH_PATH_HPP
#define BOOST_PROCESS_SEARCH_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/environment.hpp>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/search_path.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/search_path.hpp>
#endif


namespace boost { namespace process {

/**
 * Searches for an executable in path.
 *
 * filename must be a basename including the file extension.
 * It must not include any directory separators (like a slash).
 * On Windows the file extension may be omitted. The function
 * will then try the various file extensions for executables on
 * Windows to find filename.
 *
 * \param filename The base of the filename to find
 *
 * \param path the set of paths to search, defaults to the "PATH" environment variable.
 *
 * \returns the absolute path to the executable filename or an
 *          empty string if filename isn't found
 */
inline boost::filesystem::path search_path(const boost::filesystem::path &filename,
                                    const std::vector<boost::filesystem::path> path = ::boost::this_process::path())
{
    return ::boost::process::detail::api::search_path(filename, path);
}
}}

#endif

/* search_path.hpp
8uFwLIgjMBhHYk18STPH00WNp7HNeB54aDkOZB/LCQMPLI+e2Ai98Dpe059lgf9U4ymG59V4JjHfATgFQ3Aq1sQZ2BBnYROcja1wJbbBV7ALvoZx+Aam4lwcjG9hFi7A4bgQR+Ei/AcuxjH4No5T45uKuTgT38VcXIor1HRX4Txch/NxMy7H7bgCv1DlruNw4zkGjEMtdwCmqOXuSTmnz2Mo9sHyGIvR2BdrYRy2w34Yi/GYiolqvpNwMQ7Ed3GQmv5avU1/3K6mH4K5avoL8lPv+DYWxyVYA9/B+piLbfBd7ITrsSsuw3hcjgPwPczEFTgOV+IkVX4KrsY5+D4uwDW4HNfiOlyHW6W82u48Vdv1MNVb5ls+C9by1OTvoJ+WUxIPYWU8gc3wNHbCc/g8/oDx+BMOxZ9xEl7AFXgJt+NlPIVX8Tf8Bf/EX9HfwXBYAX/HmngDm+NNbI+3sCf+gYn4J6bjXZyM9/BN/BduxPu4Dx/gZ6ix3N+gB55DT7yNXujhwT6HQeiN4eiDFdAX26AfPq3K9UN/TMAAzMRCOAIDMQcjcR0+gR9hcfwWo/AClsRrWAr/wDLoT92XxcJYDktiBayJT2JTrITtsTL2VOXjsCpmYU18B+vjCmyAn2JD/BJj8Bo2xhvYDP/E5ljIi2MZ1sG2GIPt8Clsj5nYAV/DOFyICfg+JuLH2B//iQPwJKbiNUzD25iOHhzgMjAQB2MUZmIpzMJoHI71cRQ2wtHYEcdiLxyHw3E8jscJOAdfwndxIm7CSXgJp+OvOAN/w5l4D2dhoDfHEKyML2MDfBW74mvYG1/HfjgX03Ce2o/CHXr7xK42on2JKF4HoPPvFY7z+fENDMG5WAnnYU18E+viW9geF2IXXIQJmItj8V18GZfhfFyO63EV7sPV+AW+j+dxD/6Me/Eirsd7uA19HByrMAI/xNL4ETbAndgE92Iz3IDd8QPsj3swWfUfhLswG3fjJNV/KtJf6md5hN4urrTnK/XTzZPlVc9l8VHvZ35YA/2xAQZgKyyAXbAQPo9B2B+DMQ1DcASG4lgsjNMxDF/GSAximiWwLUZhZyyJvbAMJmFZHInl8E0sj0uwAi7FirgFn8SzWAmvYGW8j1Uw1IPzLyyGNbEE1sVyWA+rYEOshY2wITbD5tgc22EL7IKDMIJ6SsEoTMVymIaVMR1rYgY2wcH4FGZhXxyO6TgCx+FIfA1H4zJ8EbfjGDyGY/F3HIf38SX09GL/wUCcic1wFj6Ns/EFfAX/ga/idJyD83A+7sJl+C0ux1O4Gm/i+/gnrkMtH9snhuAGDMdNWBw/wOq4GevgVozBbdgNt+OzuAt7427si3uxH+7HNPwMs/ALHIMHcAJ+ibPwIC7CQ7gKD+NOPIJ78Sv8Eo/hUfwGT+NxPI/f4a/4Pd7Ak6hxnDiF+fAMBuFZDMMfsA7+iA3xZ2yOF7ElXsZOeAW74y/4Av6K/fA3HIvXcSL6eLG9oy++jvnxbfTHpVgAt2NB3ImB+AUG4SEMw5+xCF7BCHT4cA6JfhiJlbEU1sbS2ADLYissh+2xAvbAitgLK2ECVsZkrIrZWA1HYA2cgLVwCjbEORiD87AxbsAmuAVb405sg7uwHX6O7fEAdsCvsSMex874A3bBH7EbXsPueB2fwXv4LN7H59B5MaQXlsPnsA4695NWWCMf6wVr4nPYGAfgQvpn4iIchvEMNx4TcBr2x5cxEeep7jcxCZfhIHwPU3EdpuEBzMQvMRu/xWH4PY7An3A0XsAxeANz8A8chw4/3h/RDydgQZyIYTgJi+NkLI1TsRJOw5o4HevhTGyKs7AtzsaO+Co+g3OwD76O8TgPU3A+ZuM=
*/