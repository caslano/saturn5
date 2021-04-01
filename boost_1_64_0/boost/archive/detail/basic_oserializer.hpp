#ifndef BOOST_SERIALIZATION_BASIC_OSERIALIZER_HPP
#define BOOST_SERIALIZATION_BASIC_OSERIALIZER_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_oserializer.hpp: extenstion of type_info required for serialization.

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // NULL
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/basic_serializer.hpp>

#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4511 4512)
#endif

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

// forward declarations
namespace archive {
namespace detail {

class basic_oarchive;
class basic_pointer_oserializer;

class BOOST_SYMBOL_VISIBLE basic_oserializer :
    public basic_serializer
{
private:
    basic_pointer_oserializer *m_bpos;
protected:
    explicit BOOST_ARCHIVE_DECL basic_oserializer(
        const boost::serialization::extended_type_info & type_
    );
    virtual BOOST_ARCHIVE_DECL ~basic_oserializer();
public:
    bool serialized_as_pointer() const {
        return m_bpos != NULL;
    }
    void set_bpos(basic_pointer_oserializer *bpos){
        m_bpos = bpos;
    }
    const basic_pointer_oserializer * get_bpos() const {
        return m_bpos;
    }
    virtual void save_object_data(
        basic_oarchive & ar, const void * x
    ) const = 0;
    // returns true if class_info should be saved
    virtual bool class_info() const = 0;
    // returns true if objects should be tracked
    virtual bool tracking(const unsigned int flags) const = 0;
    // returns class version
    virtual version_type version() const = 0;
    // returns true if this class is polymorphic
    virtual bool is_polymorphic() const = 0;
};

} // namespace detail
} // namespace serialization
} // namespace boost

#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif // BOOST_SERIALIZATION_BASIC_OSERIALIZER_HPP

/* basic_oserializer.hpp
kulQhNJ3O8DTg5Ocdt1IVqvTCXf8oGdZQm4z1C/+Cz5lsHqm2TsVC66nra8Vxic4Nj6VDf79KW1TO0d165y1wUWRikYLbxmqPoY1nUCWn9kr++0WgxlSaLHNAOIx1uoIhEH/dNcBzP8Sx2c8g0HVa4OcvKTc+o6QTME5xsv4OKIg2wawKPbsnazX1MkgOi9lLLcCfJ1Or8XN2SfUdO+ZM/ia47JYY5wFpbfunKQMM0+hA9J1Xo3x7xdjQqyoWSpKpgr1+QM4YEspq58TfO9UC1xGR2QJ3XpZ75mkJfbzOHlST3Ej0y2ixiHUFVmrCQI9FlzH7OkfvLdsS53CA05nrl/yP0J41tdV/5zlXyLP06y0OnwAQjUihjUlALHPXHp9abHZfWBW9JMpC88MIGpNqJSdYK2fB20vJbVLtJUkTgmnw6eKnm+O51WTC7G5/M6Afgkt2mLS2bP3My0nrZD1CMc73xokqz/nU27QoxORSIgE4sCIAGiTKUzQwHVtf0AdD+wGpH5jkDDNflrlRUa7tu75Nj6cecgcdOhNw7Af2GNfDN9Ugd5AnlLWMA==
*/