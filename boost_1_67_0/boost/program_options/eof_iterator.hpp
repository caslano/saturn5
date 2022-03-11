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