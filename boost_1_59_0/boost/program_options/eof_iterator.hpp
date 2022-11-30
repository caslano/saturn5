// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EOF_ITERATOR_VP_2004_03_12
#define BOOST_EOF_ITERATOR_VP_2004_03_12

#include <boost/iterator/iterator_facade.hpp>

namespace boost {

    /** The 'eof_iterator' class is useful for constructing forward iterators
        in cases where iterator extract data from some source and it's easy
        to detect 'eof' \-- i.e. the situation where there's no data. One
        apparent example is reading lines from a file.

        Implementing such iterators using 'iterator_facade' directly would
        require to create class with three core operation, a couple of
        constructors. When using 'eof_iterator', the derived class should define
        only one method to get new value, plus a couple of constructors.

        The basic idea is that iterator has 'eof' bit. Two iterators are equal
        only if both have their 'eof' bits set. The 'get' method either obtains
        the new value or sets the 'eof' bit.

        Specifically, derived class should define:

        1. A default constructor, which creates iterator with 'eof' bit set. The
        constructor body should call 'found_eof' method defined here.
        2. Some other constructor. It should initialize some 'data pointer' used
        in iterator operation and then call 'get'.
        3. The 'get' method. It should operate this way:
            - look at some 'data pointer' to see if new element is available;
              if not, it should call 'found_eof'.
            - extract new element and store it at location returned by the 'value'
               method.
            - advance the data pointer.

        Essentially, the 'get' method has the functionality of both 'increment'
        and 'dereference'. It's very good for the cases where data extraction
        implicitly moves data pointer, like for stream operation.
    */
    template<class Derived, class ValueType>
    class eof_iterator : public iterator_facade<Derived, const ValueType,
                                                forward_traversal_tag>
    {
    public:
        eof_iterator()
        : m_at_eof(false)
        {}

    protected: // interface for derived

        /** Returns the reference which should be used by derived
            class to store the next value. */
        ValueType& value()
        {
            return m_value;
        }

        /** Should be called by derived class to indicate that it can't
            produce next element. */
        void found_eof()
        {
            m_at_eof = true;
        }


    private: // iterator core operations
#ifdef __DCC__ 
        friend class boost::iterator_core_access; 
#else 
        friend class iterator_core_access; 	 
#endif

        void increment()
        {
            static_cast<Derived&>(*this).get();
        }

        bool equal(const eof_iterator& other) const
        {
            if (m_at_eof && other.m_at_eof)
                return true;
            else
                return false;
        }

        const ValueType& dereference() const
        {
            return m_value;
        }

        bool m_at_eof;
        ValueType m_value;
    };
}

#endif


/* eof_iterator.hpp
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
*/