//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_7E48761AD92811DC9011477D56D89593
#define BOOST_EXCEPTION_7E48761AD92811DC9011477D56D89593

#include <boost/utility/enable_if.hpp>
#include <boost/exception/detail/is_output_streamable.hpp>
#include <sstream>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <class T,class U>
    std::string to_string( std::pair<T,U> const & );
    std::string to_string( std::exception const & );

    namespace
    to_string_detail
        {
        template <class T>
        typename disable_if<is_output_streamable<T>,char>::type to_string( T const & );
        using boost::to_string;

        template <class,bool IsOutputStreamable>
        struct has_to_string_impl;

        template <class T>
        struct
        has_to_string_impl<T,true>
            {
            enum e { value=1 };
            };

        template <class T>
        struct
        has_to_string_impl<T,false>
            {
            static T const & f();
            enum e { value=1!=sizeof(to_string(f())) };
            };
        }

    template <class T>
    inline
    typename enable_if<is_output_streamable<T>,std::string>::type
    to_string( T const & x )
        {
        std::ostringstream out;
        out << x;
        return out.str();
        }

    template <class T>
    struct
    has_to_string
        {
        enum e { value=to_string_detail::has_to_string_impl<T,is_output_streamable<T>::value>::value };
        };

    template <class T,class U>
    inline
    std::string
    to_string( std::pair<T,U> const & x )
        {
        return std::string("(") + to_string(x.first) + ',' + to_string(x.second) + ')';
        }

    inline
    std::string
    to_string( std::exception const & x )
        {
        return x.what();
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* to_string.hpp
nJaoiEUhURH/2FtuxrKhbK2BEVPdMjDiAFNgxOVu7shgq2S8Fym8xxDfJnW6o+wofslWd0eUcPc9RTFG49G+1hJ6O0J3NGeOP09tnyGJ8XiEenQYcJhJoSlxDU5IQm1mcjp1aOIThupUrPVcw9WhrlCUOfgrSUFCNEqfJRrl+62U15M0V/7LIz2G0y/Nvy0Pf3tluDSvJVyah19lk0ee0HBOzEjUMkTFJMqMJC1DTUTOMmc9Ombt8aD1fDGPFAQruu74ZyNN8QC8Rr6TZ+GI8c9G8vozCJfHcBHm6+DJ/DxJk9c/d+RYL3yuJ9+7bL5NfF1Xqd14aCunGulFt8DIzgpzQ9nv4XgE2duud6KsZ0t/Top+6OT7m6r7pRprc6gInOrvliuxHGOYFxLD+O09D4uyRngxhn//x6/Hf0uwtR/o67fsB2Im2IlH9+355Cq0tUtd9/UOUEm/FiGuZ933AddK/Bcz/nD7n/P1/U8be/HuhobwM6RnPeLdnRhhqa+/qhuLdcaTs67nNhMqOoawHlWkOcjuJ4biLHnkwFNXqRhemzscHPeUpq9eNH0l9cXpaxZOX9fw9DUGbAfVjzVBa0Rz3e4vQU8n0E/70KmxCbQtgpYDKJJyFXblGcIlZpqWakKs8C6nXzxDRsEFjKV72PHl7Ely9Ue9kCgPJsrXCcqLzZTv6QeUhzXRFru4FJLzCE81+cZdMLtpEwqukrJK9qtyZAOFcnJW6dRBixi7UDAxjJio7I1MFJqZaIdMzHBpYnlRrFw9xQP10IJbsPp58/rcDwvV9Q5akWJDwuetegncQnRrKW++A5KBvGQYKJYMA3n9fBmUSoeE+aNKxmnJ37Xk8z2fsRE+1ILGT3K16B2mWc9JBbmqnUDpzkDLIC8+v35RUnq0bWDTrbtlVQ2f1RCRMURkYy8kEmsm8tczgMgSJ6R5GEWhp6qGfnUbTy1BX50ypW8eNcw4St2bQAcIIkY+UTpHUJpippQPlMQhw4gMdQRy4/zm0qvzs4nAxhP66sYpdLe5ulhdvVqetvjZcN3Po3UwuNU0g1s7CSBdgSto8fSneFjrV2Dl49c0LzVjEV6e2CJFLjK2nY0GDWdBD5RiNkkxJwWlyDdL8ejpYC0fJbji+joeLaxo28H0QkRuibeoV0ECq1ZBDGlBEygjlvVt2NC/GX+JgCkP/6cu7//lf5HH8w99piAFxmRPmGF2LPkmL+jB/bGAm/7JvqCj37osO3uCu4TgRgi4m8xwsxHuOQ2ON8/k1io9pYvTogoErssI1w/dEdciM64+iGu69XQxR2q+8IeWYw4ODTn6jJRtJEHft4yrVxGtlYLWLDOt5/sALberodPKA3xdpGo877JDZwkOlp8vmeVg+UVG68HUo3It0wYUJr8M6LpyzjBah8wZN5BsTyXTnGGS7ePeIFsvp3XOaO60zBlJaLujW3j6ILshloJXBPpobQpV708MU3hmrBbpgtRlLrHWTrAWa2bNj6ytdJhG5I9dVTXbo/mz82g1QC8erYs9hhIHeikRKS0hSo93oxHZROlvYJcQi6QtQ9WI/N5sNSLnXAwDXYwa6CjChYM5aNqEglr8z41Tmmly1TDtlt7vodWE4hckUsLzsIqjmUhu2cTUcjY1R+dTsTmmYnNcy80xOsXGXSGr/Tk2yESuEU8z4kDQhoFwdRkJfuWg9u+KBG9EgtcF2x9W1nQp+3ciXAoh+QH0TDo5pOmOfqwK2nk0roDEKfRotF4R/HaGpxhHPtKYlcJfvSBZnY+x98pVZ4gMGTIrETbpbQL3EmEZlehk3uCwuuodGKKHzmJ/HfLLS6PFwbJoHPCoPl+g+rwsCevzGqzPaVw=
*/