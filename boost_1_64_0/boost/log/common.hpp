/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   common.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * This header includes other Boost.Log headers that are commonly used in logging applications.
 * Note that the header does not include any headers required to setup the library, as usually
 * they aren't needed in more than one translation unit of the application.
 */

#ifndef BOOST_LOG_COMMON_HPP_INCLUDED_
#define BOOST_LOG_COMMON_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#include <boost/log/core.hpp>

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include <boost/log/sources/basic_logger.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/channel_logger.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/exception_handler_feature.hpp>

#include <boost/log/attributes/constant.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/attributes/scoped_attribute.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_LOG_COMMON_HPP_INCLUDED_

/* common.hpp
1U2ZJ3ulFfZDL5fWRT9sunqVzSzlL3vouL+vDHSltTz7Ra60Xpy/sEAqes+0Lg4hrYscadXXkNY3nCKti6qR1kU/QFr3DSGtH5O03uBK630DK89JuhidMldaO+YkucukKU2xf8rvqs54OctL0LvipnS/8vmBb+RId8JX7g7fykrv83rf5oT1tu4IvovWMoYVt9zv8qZ8Rs89zjdfTr4x53W5+RnW7/rfKvO2aq1lnNZv5mjjTX4WiZ8V32PCVPya0s6Hmdp+3Aj9fcDp3yWpwftio6/WhNpmlyozvR+6jkO0Cku+ekfeT9naOZi0sNc7dYmMiE2sy3+t2gXeG+vKeie7jERUs+xXude7zhfZ691VvmSvd9HV6Wl890BXxZm0CN4XXty9VN2XdJBnbbZKA9aNub57lJxtqd9v5d38bqRzKvfXB5dl5te5y7KeX3e10r1N1UVDkbXITvO4obgr9Zrh7LaPlXmGOrttrD67zTm/7vud3WanRbMN/rT4qev9ft/Qyu/319p1/IbgtFjxHd/vizec+v0ev6qu9zdU+X6Pfdf8FXN/3q1n7s+b9Mzv9+iF/jwXbfhh2xs9L8bV71/rer9fe4r3++elnPzM9c63a7ilflcjgT16f43/5e5yUs33ezt/P1NuXGF14v9Lvda5epcRFY+2P/F/K56KtrHNCLGMlIdYRso3hP7OJ7r+NbiS9/Vaf/fvwN8l/73e+4aodGNPE1d+7xxpqd+Nkt83SH7v/kmI+a3f8SvPH9qr3Nhqtef/MUiJOc/xy5jneh7F28p8gZrbOsec77gRWr7v/klo+b77J6Hne0A3nnyPUPn+n5X39TbqvA+eizqq8jvpr/Bv/cbKeV+8VL+Uen/j3Xjqd1LcrrINuGtjle+k2P+h61fqRkmvy1zpVTrG7+BF0n+/EHnErhuD02tF0IuSeZ2EyqfPsGeXv678P9WrPtxoPJdT97U7bLLN05ktF2VML7Ev564Ena2p69Rk5cZgZiNEmOvKjaGPgwV0TWc5dlL+DCKvok6Zf3HVyD/3uUKxkLg6+4+eY2ZDVZjYP9b1PawlG+krWprq/NiSTe685kWoirWWW2x9QlXX/C6Ee6G9C6Hndd6rKc/QN5Ubc56haz5/1VzfoV+9c1bRN5Uf05mqWtfxzhLyXKHQ31d++LOp7LJ1u5Stza6ydVjKFlFT5gmyp0apLltBh2577qnxhNJvZp5T4ErH8Nahjxnil/E86M0TlC5mMjdI1uCUbwqcpaXs5K4oXFy0qMCxFCfEdVXlrjC/GR/6nDevdXj7J/qVi5BwZCmyjrSOu1jCHLTKRi8Gdae5bp9aKnuzrQnmuRy4G1zWLdeZwgnKPNcaS2hM5/42golah68VpEVt2bOI+cdqL5wbkPP9exAhp56zZa+9WnZxlWfX6HNqksK8zpep/nkxXufXxBb5uD82M7vbC8NaHrsjeUHPyze9+rTXOTX/vnNnzOfIeJ8XYz6nxvvcGfM5Ml7nzlT//KAf+jyazx1zSvYnyB77xPVm+dsucL+Rv4fy9xH5eyw6u+Tv6dz3tfb/PQyJlb8v42E9DkfpvQ/VmillFokMEH+f4yG2+TysCw/BJPgi7AJfhl3hYXgcltgi7u0W985ANol7RXL+zDJYFxbDeLgKtoLnwXZwDewNz4d95XqwXA+Da+EauA5ugBfAn8IL4fXwIvhbuN6Sc2B8sg+e7AGYBzshw/hbzc8g/DHwLdgY/gk2ketusAymwQS2I+8D3+F6NHwfToAfwCwxz4FHuc6DH8JC+Fe4DH4Mz4OfwAvg3+ClsBxeCf8Or4fH4S3wU3gf/Aw+DL+F38Iw/OnvI6/gBFgXToI=
*/