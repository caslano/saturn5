#ifndef BOOST_ARCHIVE_XML_OARCHIVE_HPP
#define BOOST_ARCHIVE_XML_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// xml_oarchive.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <ostream>

#include <cstddef> // size_t
#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_text_oprimitive.hpp>
#include <boost/archive/basic_xml_oarchive.hpp>
#include <boost/archive/detail/register_archive.hpp>
#include <boost/serialization/item_version_type.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

namespace detail {
    template<class Archive> class interface_oarchive;
} // namespace detail

template<class Archive>
class BOOST_SYMBOL_VISIBLE xml_oarchive_impl :
    public basic_text_oprimitive<std::ostream>,
    public basic_xml_oarchive<Archive>
{
#ifdef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
public:
#else
protected:
    friend class detail::interface_oarchive<Archive>;
    friend class basic_xml_oarchive<Archive>;
    friend class save_access;
#endif
    template<class T>
    void save(const T & t){
        basic_text_oprimitive<std::ostream>::save(t);
    }
    void
    save(const version_type & t){
        save(static_cast<unsigned int>(t));
    }
    void
    save(const boost::serialization::item_version_type & t){
        save(static_cast<unsigned int>(t));
    }
    BOOST_ARCHIVE_DECL void
    save(const char * t);
    #ifndef BOOST_NO_INTRINSIC_WCHAR_T
    BOOST_ARCHIVE_DECL void
    save(const wchar_t * t);
    #endif
    BOOST_ARCHIVE_DECL void
    save(const std::string &s);
    #ifndef BOOST_NO_STD_WSTRING
    BOOST_ARCHIVE_DECL void
    save(const std::wstring &ws);
    #endif
    BOOST_ARCHIVE_DECL
    xml_oarchive_impl(std::ostream & os, unsigned int flags);
    BOOST_ARCHIVE_DECL
    ~xml_oarchive_impl();
public:
    BOOST_ARCHIVE_DECL
    void save_binary(const void *address, std::size_t count);
};

} // namespace archive
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace archive {

// we use the following because we can't use
// typedef xml_oarchive_impl<xml_oarchive_impl<...> > xml_oarchive;

// do not derive from this class.  If you want to extend this functionality
// via inhertance, derived from xml_oarchive_impl instead.  This will
// preserve correct static polymorphism.
class BOOST_SYMBOL_VISIBLE xml_oarchive :
    public xml_oarchive_impl<xml_oarchive>
{
public:
    xml_oarchive(std::ostream & os, unsigned int flags = 0) :
        xml_oarchive_impl<xml_oarchive>(os, flags)
    {
        if(0 == (flags & no_header))
            init();
    }
    ~xml_oarchive(){}
};

} // namespace archive
} // namespace boost

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::archive::xml_oarchive)

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#endif // BOOST_ARCHIVE_XML_OARCHIVE_HPP

/* xml_oarchive.hpp
+dqB7KdncDj/bsB+NfZLse/NvhP78n3yT7G/n/1svnYT/87ic7pyea7yb98MTof9VxlcHj7Ti2OzOGS3kZ8PhyTw7/F8zpP03POnsj+Yz6/Jd9Gfz+/EfjP2v+JzWvBVAezXTefy8FXF+Zy5fM60jNzw7hn8/PnMF+lcTvYLcHg1q/If5fCH7GfC34QdAN/975/wu5oim7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7M5m7O5/zKXuz+S6fpRm7M5m7M5m7M5m7M5m7M5m7M5m7M5m/u/cEHYuSRdL2GjpagA7HKSoFmYKCV2S7LEil2p0meFB/EOIsYabkbTO3FyVE3s6xYeIE7ISydYX15NZCB58YY62NDIFxv995hH+3KFDJfaY+PU8J7yj8FG01zatP337VFiczZnczZnczZnczZnczZnczZnczZnc/8TTmVzNmdzNmdzNmdzNve/6n7o0yd5+sSJOUvGjHkYO2FCtkdWlunXIUPObv7ii6vtDhyY16patZ4Odnb2Pw8YcHxSpUodCr15c6/3uXPb7q5bF7509Oj7IYcPz/l22rQSQYcOxcycNOmF9sWLRxmffbblUNOms90yM1/e37BBN+D06T++XrmyR/rGjSF7ly0r/Wz16raLRo683SUh4Q/7duyILPr69Y1fFiwIHFyuXFjn2rWH6ho2nGz/7NnTlkePGrrWrDnwyQ8/tK55585Jl8ePny8YMeLmqPPn17WtXr13Q622orujo0ublJSv+5Uu3aR7UtK3fj4+1b5ftOhTjVrtum3p0qp5nJ09a+fLV+YPU6cWCbx581q5jIxjg8qXb3Fsy5Yp30VGphfJkyffcoOhWMQnn3SqUrhwzcpFitTeMmzY5YedO299uWJFl+w2bVaH16s3utfZszuO//GPkyZUqNCmwa1bV0ZUrdr9m+nT8z9t2/bHgSdP7qRn+cmDB4k9fX2DSrx6devg5s3jHnTpsn3P4MGnmxw5Enthz54BzevUGXm1WbOFp8PCFsudOm1qduLEjCGpqbsqPnp04M7atS0LvHz54EDjxl+eCw9f2t7fv//CGTPynggJmeX1/LnRyd7eMWrKlDeZrVqtCK5ff2z8d9+VvfXTT81/a9165ZtVq7olBAVNnTVnjnrD/PkNd3/7bUl9QMBwx6dPH1/bvbtP4vbtYyIvXtzYp2TJRtW8vHwLm0x3PH/77fXnp07tDTt2LMrb3d2nVv785arev590o0ePPSu/+abW0eDg6DoFC1bpuH//gqw1a9pPmzz5VdPAwPHr+/Y9eK9bt/hKhQrV+HrUqLsrevZMWBwVVehky5bLp1y+vKp/qVLBkytWbLdu7tx6huhot8NNmnxV4eHDlLS4uCH1vb39xl29uuZm9+67i7m5FRh96dKGetevX+pQo0bfFnXrRhR3dfW+FBo639XJyX1omTL62127xnXbt++7YWlpvz5av77xj7177/9p3rw6q7/+uvqnt2+nSePGZdW4d+9M44MHpc8+/XTYjs8/v/hVbKxd3zNnNp9q0WLZ9Z9/Dt06dOj5Fx06rHd+8uS3sunpJzb263d49vjxT4y//NLUx8XF60x8/BfRY8dmflG2bLORVap0LVO0aMDjH3/smLJ166jWycnflJblIxOvXPl+WUSEXLJEiQZXmjdfdPnXX3t9KUkeM2bN0swdPvx6owYNJu7ftm3E2v79j57X6+eqHRyc7LKzn+Xz9Cy6qlevfT0=
*/