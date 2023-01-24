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
ldB+fUOAamVx7Zya6QHO6TFMCylDWDsXjJ2Om1JH59110/fbKFTJum1hQIV1kcVVxvnbzGl4rHUn7oWjKSQCXqf77iQ/8I/EgGeePmPC7OLcurcNyk0V+bYW4hZR6LeDELJyHSTwO/3t74DW13ksQxrVe3dtVrmCY/sueX03VUq/0v7AY/v5tOq5lWqTaPnKhZDXvIhlKNLW/fOkFpYQVncUZZpmXmI/a6DDe67MzZRI783G2s+N/gS8w1I1CujGmID4EjDl5zcKuB6gg7U/zteUD8siOeKxfGRmnF74JAXITzOg0XrvpXQHZvU73kzW8Wmn35ZEnylTlinPlhw2Xoe5ewuhZTy6kRYi71wTm9NaxhfL4LPECuXEiS9mtRScSv6QEy6BV8Aank8ULuctaJTPtWMSQmFPfjHnTlFhHj9i0VF4ZFRiZRNYK4OvVqgq7lPzEQJR1fqiGuBP3/jwFhmBig2I8UA+B/kp4FvfGRWIA6S1qNn5AA8vT+UyyzoTHiqXR4xOB0OXR+y/9ZgF0Mwm4pnYpJe0hy2HieZu8EB48iIpUQq+nHyQL9xAmDPljaXHvDTKwMFrde+bkrGH8wz8MrPRCBs5a7jFQWzIeBUiJrBvwDKcstPhp+1R4GtMt9rb8rPbHn91rKXhlz2Rb7YgSRmjXmUpX0vGKaZQNIhSfERpccSpwjK5Ee/2ddW3ED9Jy8Obe/Z9lpZI
*/