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
/cs4Ge7/ZTbj/2a2so25haPbf3riOO7aIx69Nwx0GFGA4IapGelVJPu/zr9PlHxbvHTRuBrE/b7RaBIf71zad9oWeL1tKOnprBtlk0MFpWtnUqFszWkuVaBwMs9tV81e9TBsU8lpVQDkflJZX2e1WWeyMc9eEGwBnwtIPDc/hekEuM678cA2YYdTm1nPf6PsqoLqapIw7u4WNAkJbj9c3CEQPLi7u7tc3N2Cu7u7/kBwdye460XvXdZqax+2dvfhVHX3981M9UyfU6emZrrZ3Uwvxi9SexqP9mO1u4/xf8a5KhJ3pdcUc4ubyOR9Q0XGu3mZ8BbQ+zIJYXjrkRZEsCRq+WRJRn91YKSLXAmjCnsIY+Xf1OvR+xThalgu+jRrceKb4sszR1UPTX6MVwy3iREto41iKjNW2p9zuy5IrqFOP6oXtxBvuDr5e44/VQCMQ5+KLl6eSy49i9WL1QkSicCNG8H+RK4xQmu63ZPd6GA1eT/Sidj64web+FYT72ITdyuj5wZd7Pem7alDuBzapTGITa8n3dXWhm9TB6MzN58XuOiEAkpg/7THC1Rmz3fXW10immFmEBjcsN2DU6oms73l+8l77OyR3Vp80OfE8+m2saC+FwKb5xI/0TcMTBXVCqTv6F7o6v74NSVA8NJSEfm1I+zVp6nXTxwEm0e/M7cz24q7MNEPjqcGe0MOqntBjrYDpzoQwjgk6KDN
*/