//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_TIME_ZONE_HPP_INCLUDED
#define BOOST_LOCALE_TIME_ZONE_HPP_INCLUDED

#include <boost/locale/config.hpp>
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4275 4251 4231 4660)
#endif

#include <string>


namespace boost {
    namespace locale {
        ///
        /// \addtogroup date_time
        ///
        /// @{

        ///
        /// \brief namespace that holds functions for operating with global
        /// time zone
        ///
        namespace time_zone {
            ///
            /// Get global time zone identifier. If empty, system time zone is used
            ///
            BOOST_LOCALE_DECL std::string global();
            ///
            /// Set global time zone identifier returning previous one. If empty, system time zone is used
            ///
            BOOST_LOCALE_DECL std::string global(std::string const &new_tz);
        }

        /// @}

    } // locale
} // boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif


#endif

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

/* time_zone.hpp
G3piHn2qyv3Oa5e0CR92JOM4KZ5xduJ9U6JmINajuHcFRzY4PBuhaavKiGSdSGHw4ajN4eLFYil2BaXl9COzjNDe3GSuCuDr7MwYvxKcFfKuwBggAY+EpJSJmT3iz1gcWod8ci/VPfVi32ttWHBH7audbWW6M/ihke+H8/D9K3GwUYSNTNMNh2XUkxBK3sSPitFeqzX1dPMLWr8iXMPcO5iakDNT1Uu8g1Wpba2Tf3G2A7eCxBeJzGfx3dt1zluSi0MG9w7fqHcpLKqE/UuUCq9MuF4+cDmAGmyiDkpRbY55wL+phaoVQw+ZpYJnw2tI1/P8OpoAbqU6FUl0AwCxdEK7vrd+UaoeId7hh29bC+lv15OSZWEQQ5cYUdBuN0KZfeXrJixJuC7iq9/GV5Abh0Mz9HasrXDMKG09DZaPIARtjsUDBodH8JIi2PXFrwA2XxnUyTzYvyVXz6K0E4OBpcixv6Ut37+DPTJUoE2NzoQdMecQO9TlN+47zUzvHXMizuGaryXaMI7fIum4Dy84VdtpK79w+ZW8/Nq4pE67+Iddgja+J94qQAkSJA==
*/