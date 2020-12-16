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
6qHfZ0ga+o7xYq9bPw226SIVTtLwHtNwVVS/xbHVnNDB5DeT0z2XJX3n4LE8d1iTD27PTwj/PfK7I+uj2cyvwtVtnvb8Yydtf5F8ZD4KX5stuq8me7uIvPdv82rXvw7R/Tgv9t0T9fhm/FafW1n7J/jm54g+ut1bgatyrf3neC92MkLvNrvIwA40NifLcV3dJe/fZhp+Culupgn4T3VwmshPqvc9wu89wYv9fV0+DN8O6/7b5P9Sj4/e10XbaxEbWBfvxoTavQt7v7V/kbk4xDR3cjji4f8TcbOicZOG7hO92BeG6/64+/V1q+QD0/BiKB/s+TUYfPJFN+Nd10le7G/C9c7se5gJkKFr27qk3j1P/mBIdxd7H9LPLl7KtwjDOpvTCOhilPcapJyfIHebENflmQ/J5926eS86lM8uzn3Y+19kvh/WFwazsYyuzc7e/+7xYv8W0pNnIgreTkJ131ZXZynjW8kfC+ns8ozCEtH9ZC/2I+G+DCen7Py5gtY8gbFcuY5Lmd/INAwF0jDQf3IsMaF9z1DKfP1TvNh9YaadvAGDfJ9S5kuZT5O/OhfBd3yGbC3ZqyLZGLyVdbbnf3q92G9GctF5K5/9lbz+ltyTo8qaF1q1+1DRObnMi/18UOfTB81ArX/eWXT+gtyPAzovG+ztGfJdtdS1vQt7+an075SNZkNr9THLnn8he3kddkb53KA9/4KfjB0xIr9Rw9Ttlfb+H7m31uprDnkVM4Wydjnb9Q8ftH5PdB7sOZ2PDeEymM+zlvJ9T7v+If8dH9/YI8N45by39x9P5/k2yfuBwZ5+YM1ldYwfruZIz5P7rtg8uuHYa7Ld2HhSyvej7Py334t9n2WGnZjpnrMS7mPkFnM+LicmLriSxzsNUF8p25OWDZjlPH67dluW85IryFyc9zHHDNHw/osv5P8vUby8UM57qv4tv/sav6PxNb7G1/gaX+NrfI2v8TW+xtf4Gl/ja3xuvnnW/3/bzhH2/7/iKto5SvDDf+Jwf3tsWf9Izyk9Q559RY3bIvsAjN1dMVzv3YFzjmg7umovVGZa+/869Dc8HWYO9ZzhkDtL7vszYe7gmSed1nNukzK3JeT7/5Mabv+Jp/foMkXXt8ncZSrMXDrU5yCPxV53FP/BZ2FdlXmi5zP8Bwfc5OONDKMmDQ9W1XRVpvuuz/3xG8NcU4NVmdb/A5nf+NvN0PCJrL7qXNlP2WkD+gkKcQcro9lMArcJHdQn6/+L7M9CbHuV0cB12ZLfm9O8/MOVPvYcWD2/pW5Nkzt77RzXVRkL80cyJwPM05YOH6Wfv0tkzNuI9zxqmYNDy86KQV+MficPuGjH1v/tRtT7+lAajqxSzQ3B+IQyW/I8Db/7JpwKs/XzXJizZPaF87y9Q71uSTsa2YR3Y6/2MQeWDg+aXnqgf9jRGLia3PMiuGec2TM8olyuwu3elH5+r/Bxe5ayCeuXrT3/uCn1DXLZY7npp63/183ogynEPm0Qx62xJ4mjFapcqc9Pkfvz5T5u9/CJ5pR3yY2u+25On7MBpvtx+BFy3whw3Y6F1v/pFjyPFmD3TrnIZ2GuIPPkINNDOqrHiOZ9l/mYS08f9o0GqlzRtUzu5mUf16z/Rs4ddNQ/fkvm7Fz+jsa8SZ2TumTXf1vxHJaPuxDzqk/I/TLAPes0F/ML0XVwEc/3zZVr3CvXgZNO7Vk64or7NrmbXzrHXQh7QufW9OEqXLwn6Nqe8DyZN07PMRfCnrB4G94F9enqco1tz/+Qu/dNc9yFWPPutC3969w4x3W15rXrPzKf8OWx67WnXf9tx3d8bgixbVflhnsjuU/7dF6I/nEtuc/7uK7mNPb9L/o=
*/