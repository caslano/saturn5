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
T1VIsx/klzXamX+4dNzl7yezGlS+eEN140xmpGXq9ag4L9+4+2LnI0evungOzPpk40H9THz9qJGnVWePDZNaLrz/8OPaUTfie3s8+eg1Ynq9ZkEfnG0l0z9SVt4fL5km2Se82xPPW3RpYNNylwa8o9psv7Tdd72AF2r/oUMDf37TWeqQRtW9Msftr/9tRtf1U7bOvHjrnYLfOjv2efk9+9Nn7S2Vl7hmuFn6acfNzZ/N9O7wPfJhgPX1ueanVlunhNq8szULv57Ryvxr4rYnMdVvxvMknf5acqBy/MsJOc0X/egYMn7tmMdl8sdv3Xbl3aAhDc6ueh7V/uKcxSlnfVokeLXN+kHtTH97bfVfHV6OC67q9vHLyfrdayV2cYxd3GzTrPtP1V9krk6+fW59fOQd/5VKORX83vzrrM0/rq7p7sVvPqPTLlfX8MgxE0ZR21cm/OgyY2benrgVkT3nWuUIbVfmtrlxd073zi2WfbZ27Fhv2Lv+QxxtJ5s+/vRd0bq5WV+r3Wn3W9mU7mR1cEbjxGMPOlY72OlmhsXxlyc/l7VoaOa9JDXAq6Yss9+zblFO5w/Muzzp4J43orZVvJ1TBltHz28Rvfjxpzt1pcKGh7ZUrZzldNf0fEjseqsR50/lz2iScHeqZ5uYCk3dGu/c97Lyok3pcyrteji+ovK2zcdFdvyUqnnfp2+fEVNuqKjgfe4j+eLAiC+dho5p/n3B4QYTPN96CwPM1T/t56yWyV3bf//0Lvpm1RWfbj3LCbpbd06lBNkNy8jBx9q3ikt0uyRubvY47+bxSravF//k5U616LC1wgsLydeFg2PnD71xtsK5KdmL+1tdy2xdbXfTtX267U+dPvjZFbekzfYd2qf2qpI7616zNAxb3y1f6xPv1nLAsdwgTdV6r+1T2vtUHfCo29TtD3fnlAkVfu1SyzKhzpcXp6pc3WvtcfLw3Xu9avj4ZVSrai57XvFai6erLwfHrRdFrci4nvlk/74fhx+IeqTtWZBx4GPBp8Ep0V2jS0X7j/p+fkNDlw9m6/jJud/a/dUmwWfUwNUNCsZ4p22I6s9z39cjO7npusd75/j4Rwrse+6f9K5n8KLvt964vFK/O7R37JjDn2PD1RM3n4h8o9my89o3f0GzZ4NG36k/LrXygNH3ZkRNmdhL5q/osYWaEnl5fNBt05N311TYmVd65O5OMSuqZK1Ua7bVHr69/M2V+Tnl7WLb+DsdMW3Y+/H4fQXlrbPndLb8Iatf32NnnTtLllaweJORI3kdbzPq+vabP8p06DHv7L2csOFnQkz6Vwn9MqrM8iNbTbOb5z2s1Hz8p7neGR2TywRFH95aZoXAZlDNgvyM9wdW9YzmxQy96fBX1sMqwqcuTabfOhTuXOPQoe4vT+++vW3P5Jyh354l1e91tvyD0vJMkyFdPMyVHZoOmTokSnk/Y+eCrsotfQ7W+bYj62JKZMSLrUu/lbs4xOPqEYu1Xfu/Cm3w6aFg47Xq6Yvcq3WTPjp+WX4k+G73s/tbtGt/4tgtZ6e5f1UdKZw68UvluHxetFf7sx1cz73/crF98qHVde2O9s6K29DXp/3iEK/mIy/um7dnzoKJVS5bqSz2D6tnd2XwEd7xhLrjt/Mn5zTat1G2aYus3YDWqzv1SJVN33MhafGxE4cCxS8/WYQPvT3Bv7656vKxrnlBN3Z3sA3137XycbMZa8zu999XcPlLztxudgPujX8lbPwyY+6OQ2MPfLBv6ruqVIOlS/LezN8lODCq64An80Kt/jnpSh/Rrs+LmtncdXVdnjFjZZcnMZGvLr5qffz6x7CPErlZx17mX5KtVj5IM8nYMGbtw/Lzpv0=
*/