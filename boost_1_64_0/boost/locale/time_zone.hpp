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
bxbq1NvNRsEvMfJxDxkHUsZXZmrshn3+teCfYOyNs5wIUsZZZqrtJpPXwDuCf44xCv9Xgs5UfetIejJhH+b3Y+cszxovucBpoMpWficZnM7xVJen3ggX13PsKPdtgDUdpfv7/ULmAMRCRaj6ljr1755bBX+Zqk8pq3/33CT4D6r6krL6XJbtgl+r6j/IKt5jpG/wlYK/Hjn8kXaOSy9e67nEU+S/WyH21by2PxHHCfvr593/tZ3wn7kfzExgJ/b/pjS5/5tfAzIdGJduyvym6nvq0/d9lJD9S9X3lNX3/V+CH+9S9D1ldd8dQFHvZsZLszxaYxBacKUxwdZFXsB46Ryha4NxIeR08dLLRZlSZEkdI37na75Vpos46eb5O9uWgomjtmzsyc6G2BYydvQSg/eYFNnGml/LMB14p5A5S31/SXGeU8OySpvKANYLfqL6fpISOKfmAcGfSbtgeZx9njHO1sP9yvwas9GSUkX9HA9xGQ0c62tjHGrb0uti3yRlDk4q8DEeB/Ot5LUPbZrRSs8f65100m6cP5W2MZrfxEVe38T2J7Gj7+GiZr6Hxwp+nnqNyyC+h4uC+B4u0n0Ps6+OEPz9mC9l9o3+WzghiP4J9VvYunZXdvFUFM/nQ6z1LZwq94+zNddOEjIbVH1GffrnQ5ng/6DqM8rqnw+TBf83VR9SVv98mC74n/P5wPJojb2N6Vj/5XBbF3kBnw/Vgv8B3hoP1z4f/kz1XNNDYQft5Xwaiap471fydoHnwhZg1S6UXzNJ5NeMPuWRd4tio7Mavz107Y6q+5/5/+bXjBzgMtvzsdf+ih1S9cI5MS/2/eGOx7b8f/Juqjvr81n2xE3NxDwX81mAlpw7gFwB5QZQbi9JrjaA3HvMn3kHGM3fdp5PALkPKfc+5T6U5OpDrK8hgNynlPuYcp9Kco0h1rcpRDkjSy+3hP2wlP2wTOqHxAByDazvddbXIK9xFqJcfohyRSHILbD8qsAqxZpmGWyXLGAMMBcYD+wNbAfcHdgL2AW4J/fnAbOBewH3AA4DdgWOAeYAJwG7ASuA3YEzKMc8K/r8TP+pf57VEhx3W/M4uSbXXcy3uht4MPAeYClwBfAprq32O/ARoAv6HrXX6KJPCPiJYo2uJ8zyXGutO/BJrnX2LPB04HPAecDngZcAXwBeBnwRuBb4KvBj4BrWN9b2beB+yPpiQCNY35/MQ0MBcX5JwK7AZGABMAV4IDAVWAzsyPYyFY5lv9/A9toNtIV6h7J/DmC/DAMONM8faNY9HDjSPA7gYdx/PPBA4MnAg4EXmccMXAgcA6wBHga8FXg48D7gOOCzwCOBbwCPAprtejTQPJaJwD+Ax5jn50I7A9OBxwP7AScD9wGWAIcDpwAPA041jwdYCpwJLAOeASwHzgdWsB1qrfFWYFu2g/AHsx0q2Q7TaaczaJ/VZn3AU3n+pwGPBc4CTgPOBs4FngG8CjgHeAPlzDrOBK4EngV8CTgP+DbwbOCnwHOAm1mea9RxbA/vE4o16nBOwu4WApOBlwH7AC8HjgJewevoOuBY4FXA44BXA0/l/pnAa4Hn8Pe5wEuBF/A31wDkGJU5hue/BuBJvM5O5hp1lcBuXA9jONcEPIRrAhYDZ/L6OA1o6joDeB9wDvBhrin4LPAsrv03D/gb9US4hB7ejzheAuzs8r8fXcjjuohrAF4MHGTKAU3Zy4DXmu0FvMlsL+BtQDeP5yrgg1zbbiXwGmCky7OmXSLwJmAnYA2Pp4jf26JPFPmjw7lczghgPte3MNt5FO8Lh0jXfxGv/zGK6/8L6vmSc3z+AswB/so1Irfx/vYbcDRwu91e/H4Axivaawzb6zA=
*/