#ifndef BOOST_ARCHIVE_BASIC_OARCHIVE_HPP
#define BOOST_ARCHIVE_BASIC_OARCHIVE_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// basic_oarchive.hpp:

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

#include <cstddef> // NULL
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/tracking_enum.hpp>
#include <boost/archive/detail/helper_collection.hpp>
#include <boost/archive/detail/abi_prefix.hpp> // must be the last header

namespace boost {
namespace serialization {
    class extended_type_info;
} // namespace serialization

namespace archive {
namespace detail {

class basic_oarchive_impl;
class basic_oserializer;
class basic_pointer_oserializer;

//////////////////////////////////////////////////////////////////////
// class basic_oarchive - write serialized objects to an output stream
class BOOST_SYMBOL_VISIBLE basic_oarchive :
    private boost::noncopyable,
    public boost::archive::detail::helper_collection
{
    friend class basic_oarchive_impl;
    // hide implementation of this class to minimize header conclusion
    boost::scoped_ptr<basic_oarchive_impl> pimpl;

    // overload these to bracket object attributes. Used to implement
    // xml archives
    virtual void vsave(const version_type t) =  0;
    virtual void vsave(const object_id_type t) =  0;
    virtual void vsave(const object_reference_type t) =  0;
    virtual void vsave(const class_id_type t) =  0;
    virtual void vsave(const class_id_optional_type t) = 0;
    virtual void vsave(const class_id_reference_type t) =  0;
    virtual void vsave(const class_name_type & t) = 0;
    virtual void vsave(const tracking_type t) = 0;
protected:
    BOOST_ARCHIVE_DECL basic_oarchive(unsigned int flags = 0);
    BOOST_ARCHIVE_DECL boost::archive::detail::helper_collection &
    get_helper_collection();
    virtual BOOST_ARCHIVE_DECL ~basic_oarchive();
public:
    // note: NOT part of the public interface
    BOOST_ARCHIVE_DECL void register_basic_serializer(
        const basic_oserializer & bos
    );
    BOOST_ARCHIVE_DECL void save_object(
        const void *x,
        const basic_oserializer & bos
    );
    BOOST_ARCHIVE_DECL void save_pointer(
        const void * t,
        const basic_pointer_oserializer * bpos_ptr
    );
    void save_null_pointer(){
        vsave(BOOST_SERIALIZATION_NULL_POINTER_TAG);
    }
    // real public interface starts here
    BOOST_ARCHIVE_DECL void end_preamble(); // default implementation does nothing
    BOOST_ARCHIVE_DECL library_version_type get_library_version() const;
    BOOST_ARCHIVE_DECL unsigned int get_flags() const;
};

} // namespace detail
} // namespace archive
} // namespace boost

#include <boost/archive/detail/abi_suffix.hpp> // pops abi_suffix.hpp pragmas

#endif //BOOST_ARCHIVE_BASIC_OARCHIVE_HPP

/* basic_oarchive.hpp
5fqbW3fbDDu9xLva15jHxx6cvX6KemUSlNzuR9awvC0NX7fsev3GjNlTJq8bOHHt0+zL0xLyzk/My7c+vr51H/eJ26drJn6992GSqGXVN1V3ZGbWK6g0Obv/2pB6hyfFT3l97vzagys212rcunVyzcr7fthpnuY0NB1nkZv9z8dq+dYrb9fUmnNv7Nn8kBVbtudX+z7C7ciQayvWXohdFFWjdPKMtOqq3GnJ1es0ElNrH2Z82Zr83ifi+Lm2C75WXH/mWfZYz8EX63pfCRzWYJ1dZWte/80Dqd28+Mbr83f0mNdO1LTBzvIF9acII1ctu9NrrO/BlOHhva8t6jOUOrrzn6ZJpZqNWnluRkx87RNVvDurgk/ZBWzuvLL64DBet7pWtuFzO/awuPLg2Lw9SUuiW/LUD0dsle8q1/BJ3R4Jz2e+sbpWqUUjsXDbts87H9mXdv4p6p5+tJ/dhvCcSQtXzgnYVW5A2XTZE8WgLn62m7fal9fcaNKs9pENy2Rrh95ZHrgj+uX82E0vJg0cv+r5z5pzJdIwUfe7WRsPLTVtV9s2qLzGq1qvbE/XWg/mzo7oKF7g0+fKg0kJVzp+nFN2/oWc9w6PXz10set6sJ91QQZ1K6jZM8XoY09GCvvnNjDtmBBf/uSrXZ7Va81yz1EMSBjddnh8xr3ssNLh87e3Lxu6qt7osp59190e/txv6MQdb2r0aH/ddUOliqEFZg3rFfzczDOt877iuk3qre49B42y3tuo/M3P1aac/9B65RBVgNN0k4D3jUf885+uN68fau+ctPXE8ltv5/oL/FZWLpVn4Xn8xHPvBpolc8643Gtd+albzu40J8fNnrVcxkUEl9uZGFKqko98v5n5h8lVd7RKHTKrqXJDavf1Y9fvaZg897ZluWnXqq4bt9m+47mbDZVVI5sOTLB/eKtO6JgzoxfWCug5qOb1cuo9cxfuGT+0yxPX54Oef6mffiPWt7zwwmHRkYBa9V6Vu2bl1N7N91aNXYea+nbNqdrtiLiFKW966K0HrtWyPt0ZGBnsaHklec2IebWrRL3u3tYs4fjiv9xqVXEvv7RprxcPJ7358vX1rFb7d2XJ3K0aKPj3MzbKnzw17185Y3MLz971HjVM/lLGI3jnTbGtRf1Hc66M9UyzPhEblnIyyH7AZsv5uypbHUt5em96uPu3pe/szBssD/74xqNl/XYWzTrUjk49VLvc8iZh26pW+yj7sfZZbMPDT2fw99wfdWLwsvPth2+0+Tne5NUtp8NLe0v3pTfqKTadvTreYunZl24zWt9YO/RVi9GtZX1stjWyUgjK2moCbj23tFoocFiRW23mXsGzBj+cS50Tllo1ua9qa4dFiqAKWVmXq99edXpPRu7L5a1iolf3XT1fNvrtpvUNxolOFeytvVPSJDt0d2+xU+94r81bWrhffpLl+HFHowO1K0TMm5MdNWbYnI8zVgz1iJmb2f5Tst39WVHTXlQZUTW+hm1m28pXGj48nnPn9sw5u3qmLB39vodQ2bjuz8Oj5s30P1TnmfnmMxEO9uEPOl2bZOO4J/HVm2c9n/485ix4YfND5T7k5bXqnfvd3y56XL2fpU9+NU9q272X/KerVy22CpHeyAs5/cXnnc/xrbsHvKrvFiIu3eiMd1Zqg6vHu6ZnDAjo8iA0ZoTHm5yYc/7NJvTJHpX5bfG24wcPN7UaPlV9WlLhH6MD0jdN7c7b36f8gk6116o3xlTnVR7ZpMUEn55P30dW9Hy3tr5A0bHJ1AJlG+9h0ya8fh515YZbY2mv9reHRKtfnl7+Jt1L5pR8dnRa2WVZoZ9qR1599bjtrGuCVcslKw+VqXj022qz3jc=
*/