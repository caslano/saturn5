// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains machinery for performing code conversion.

#ifndef BOOST_IOSTREAMS_DETAIL_CODECVT_HOLDER_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CODECVT_HOLDER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <cwchar>            // mbstate_t.
#include <locale>            // codecvt, locale.
#include <boost/config.hpp>  // HAS_MACRO_USE_FACET.
#include <boost/iostreams/detail/config/codecvt.hpp>

namespace boost { namespace iostreams { namespace detail {

struct default_codecvt { 
    typedef wchar_t         intern_type, from_type;
    typedef char            extern_type, to_type;
    typedef std::mbstate_t  state_type;
};

template<typename Codecvt>
struct codecvt_holder {
    typedef Codecvt codecvt_type;
    const codecvt_type& get() const { return codecvt_; }
    void imbue(const std::locale&) { }
    Codecvt codecvt_;
};

template<>
struct codecvt_holder<default_codecvt> {
    typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_type;
    codecvt_holder() { reset_codecvt(); }
    const codecvt_type& get() const { return *codecvt_; }
    void imbue(const std::locale& loc) 
    { 
        loc_ = loc;
        reset_codecvt();
    }
    void reset_codecvt()
    {
        using namespace std;
        #ifndef BOOST_HAS_MACRO_USE_FACET
            codecvt_ = & use_facet< codecvt_type >(loc_);
        #else
            codecvt_ = & _USE(loc_, codecvt_type);
        #endif
    }
    std::locale loc_; // Prevent codecvt_ from being freed.
    const codecvt_type* codecvt_;
};

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CODECVT_HOLDER_HPP_INCLUDED

/* codecvt_holder.hpp
3zG7N/yJMt9ROnlqfl55Yb5l9jmsljA3m3Q+K9f1fMbkfnkumJnPwkp3n9Xr4n+Niavj8bIH0/e77N64ysK6F1jLr4q4kqUsSkxcYyWuFDM/sl7uX2BfYlVJ/Gme+NM0fnc9wylyfmKehFtP3I5bme4nd/dX1dXnJdiJ1hiafvSchZndLM8e5Z8k3hyrGy7u+ochcu8ge6z1nO5ZcOvyOanLm3lyktYZK0vNOobDJUxDO8uawsqIoWbeIFHyegAlt49nDUTpxJn5ltnzd57cu0D8T0132kdZQSSdgylr/SabE4Z4U3Frru22m7it5g072mrphOUK0fQ+ZG1D+IvwwU/ywT3xeZE6WkM59hH3YbZT7ruUD7Qct87i1tS0EYs24j3zcs2xug9Xy+59ud7LzEOtleuj7BA7gNw9DR+L22LbUyeZbp0kw7fF/3z7AS1/8hSfH3Puwq+6Bz/DZ+7D75xMnQcx8xuWOw/induIzoPgh5u+l955EN4/3M37p9/b1zj0PcJN2nGZuLnvQ1Nps6fI/XlOGCn7U51rrXPzPX60z+Pkx54/6Pvh8/p/+3rX18//8rLhZx0dGUMvdd8L/X20NL2LNfMp+u3rNjAHtoXTYAd4DUyHj8KO8BvYCX4PO8O6xJcBG8GuMAfuBPeH3eAYuDM8DPaApTALngh7w6UwG96sY+kGTrtjXLQMXR6MjwIJJJBAAgkkkEA2q2yZ8f/kWhv/22nR8X+udhW3CmELgonwDDqubeaY8f/kPx7/D6IvT1xznXteMeO1YXL9AuOF0zmnIM13XoDn+M8LaJzjxP9luW7FdY7E+baO/bAb6TMaWHeaMecI7iEMRXSW37wAz6x+XiBVnqthKJW+PDvTXmXuV7/q5gn85gEI7z8P0FLHdGPE/zG7tTXCeo07Gtoj/OYAiMd3DsCUd3fx/9ZuRSwN7bf8xvnetOt+Ca1YzXsrT94HUq6d7JfN/a0893vnBFrqnEC2+H3AHXWtL3n6E3ZCtfMCt0jYHynPd828wCxx24HVB7d4x/9mrNtb/D+xv7USxb+NhehZfLbThudG4kywPt9onM+YXuNj76HEk2RvY6027mH0vUi+7ebW607ZyblXjaLPmeyOy0PwK3lWw5hxu3eMXSxxzbXPscZYLXWMPVHcHrEbs9tzFa3zF3aF+o3Rm8JpEjYkaXHLbI64NaSdPGfOyWN8bsbo9TZhfcLfNS537m9l9npom9M0bPid8fk0GZ9nPPnmGZNnXV5x0ZtPN2+7/92fyPicxqvtUX+/EPkN+9qzFz4Jtobt4HZwEGwDh8K2cARsBw/QcfvFsBN8EHaB76stfB3sCj+HO7l752Ed3aPdBA6FybA77AZ7wN6wJxwEe8HdYW94GsyGy2A/+BwcCNfAQfA1OBi+CYfAtXA3+KM+L1Ft395xf1Uw7g8kkEACCSSQQALZIrJlxv+1s/8/lW/QnZnunP/snPJKjOPLJk4qzJd5gYQ091wA/HX//jdoU+1TL+S+qqPdeYHY/fsnxu3fT4afSdj3df++e28P7/gft03fv09Yn/37PrZ833gnFZSVWiYtycc4/g8aO+taCb+12ec+TvzrmbHnz+I/gTFEmt8Y3zzPc7ayiWuuxNXT2HB7y3Vf9WdFvFyHPWPqAnPvjxLvJGPH/1au72MEXOgJf6ixc0+WuIotv3NaK47RcxXNmQWHMd6Knmt4g/i3/8Mz192x5Il/Yi+/49bEDad14h3vLZHx3rKbbk5cuP0X79X7+dMT2/3C4E3tsVrO2i7j7bE763ivN9wB9oc94CCIWoPhSLg7HANz4ES4J5wBh8LD4b7wJDgCXgJHwsvg/nAZHKXjwwM=
*/