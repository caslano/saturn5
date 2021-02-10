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
X3ByZy5oVVQFAAG2SCRgrVVtT9swEP6eX3GCLxBlDezTNqZppbxVQ03VBiEkJMtNLo2Ha0e208LG/vvOJrxNZf2CUWv3fM895+fOZltUqsQKzo77R8cTNriYnLM8y87Z4JCNJ6fsLNqmbaHwPx5p/H4jghg2DhY+jAbNATE2+icWbr03Y/fw8Eeoa5o3kaTwDLlnu7AZcg87AcI6lq9+zdgmomufm/9KPfKa+SVZCOaRA93cGTGvHewMdmH/8+dP8AE+7n3cS+CIK4ESpg7VDM08ga9lsHyv+e1tz+K3BNABl70uVF4LC1ZXbsUNAq2lKFBZLIFbKNEWRszoh1DgaoRKSIRBNr4ajk4TWNWiqH2QO92CrXUrS6j5EsFggWL5EKPhxoGuCE7BS2EdBWyd0KpH3AgOzcL6GJ6eS6uBL7mQfEZE3EHtXGO/pGnRGknZp6UubFo8Hr9Xu8XTSa4oiQW/A904cBpaiwl4zwQWuhSVn0kQMjbtTApbJ8/ZEJUqU23AopQ+FuEE2oe0EaadPIl3g4YyFs5PVivrqVa1XrxyJB19lKo1iohIB3IqNcmcQEuXygTncPJHik7TIPCbpXnOtwStKBnY6k9hON2CGbfCJnA5zM+yixwu+5NJf5RfQXYC/dGVD/ZjODqi
*/