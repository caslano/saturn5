//=======================================================================
// Copyright 2002 Indiana University.
// Copyright 2009 Trustees of Indiana University.
// Authors: Andrew Lumsdaine, Lie-Quan Lee, Jeremy G. Siek, Michael Hansen
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//=======================================================================

#ifndef BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP
#define BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP

#include <boost/operators.hpp>

namespace boost
{

namespace detail
{

    // Iterator for a component index linked list.  The contents of
    // each array element represent the next index in the list.  A
    // special value (the maximum index + 1) is used to terminate a
    // list.
    template < typename IndexRandomAccessIterator >
    class component_index_iterator
    : boost::forward_iterator_helper<
          component_index_iterator< IndexRandomAccessIterator >,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::value_type,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::difference_type,
          typename std::iterator_traits< IndexRandomAccessIterator >::pointer,
          typename std::iterator_traits<
              IndexRandomAccessIterator >::reference >
    {

    private:
        typedef component_index_iterator< IndexRandomAccessIterator > self;

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::value_type value_type;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::difference_type reference;
        typedef
            typename std::iterator_traits< IndexRandomAccessIterator >::pointer
                pointer;
        typedef typename std::iterator_traits<
            IndexRandomAccessIterator >::reference difference_type;

        // Constructor for "begin" iterator
        component_index_iterator(
            IndexRandomAccessIterator index_iterator, value_type begin_index)
        : m_index_iterator(index_iterator), m_current_index(begin_index)
        {
        }

        // Constructor for "end" iterator (end_index should be the linked
        // list terminator).
        component_index_iterator(value_type end_index)
        : m_current_index(end_index)
        {
        }

        inline value_type operator*() const { return (m_current_index); }

        self& operator++()
        {
            // Move to the next element in the linked list
            m_current_index = m_index_iterator[m_current_index];
            return (*this);
        }

        bool operator==(const self& other_iterator) const
        {
            return (m_current_index == *other_iterator);
        }

    protected:
        IndexRandomAccessIterator m_index_iterator;
        value_type m_current_index;

    }; // class component_index_iterator

} // namespace detail

} // namespace detail

#endif // BOOST_GRAPH_DETAIL_INCREMENTAL_COMPONENTS_HPP

/* incremental_components.hpp
A2fhTJyLf8FXcTYuxVdwFc7F9Tgf38AFuAUX4k5chPtwCb6DS/EYLsfTuALP4ir8CFfjp7gOr+J6/AZfw+9wA/ry+m7ErLgJc+CbGIJbsA5uw5a4HTtgEvbC3piKe3AI7sUReAAn4EF8Gd/BOXgIN+NR/AqP4zd4An3t43ZiEJ7C3HgGK+C7GIHv41P4AUbiOWyCH2G0mo5R0y3xY+yMF7G/ig/BL3AiXsUZeAOXY5T9/YYNcDM+jXuwIR7CRngRG+NtbIIBPhz3GITNsDx+QnlV8BI+hV9jbbyBjfCv2AxvYxv8DuPxLg7B7/EF/AlfwXv4Kt7HFfgrbsXfcBcaMg4g4AW04U30wR/RF++jH+a0jxeKBTEbFsPsGI458Cl8BKMxJ7bDYIzH3JiCeXAs5sXJ+CguwEK4BAvjLiyGZ7AEXsaS+A2Wwh+xNBp+/GZFHyyDWbAsZsNy+CQ+iXUwDJthBXwWq+DzWBPXYS3cirXxANbBE1gPz6GMg4hV8XuMQMOf1019vqXp3+sc8+r7MBD7qO/DLeQrjruxEe7BZrgXe+A+TMH9mIrHcDS+jVPwEM7GwzgPj+BKlS+vr9lHXsR2xpchpZAmkBaRtpJOk65st/5um85ftnvbdHrbdHrbdHrbdP4523QW2GE1KpOakhJ3/Hnbd3of3of34X14H97Hf6T9P02AuvZ9OH0AzHVv/0/Mvf0/Mef2/zpm1e38zZhNt/M3Yz4Si4tqG2fGfCXWLMaeM7eK+WW8n4B4APHM279vDOXcz9FXoH2nq36LCippP0gFi1wL0nvNQ98Cui1I9V32/BVoFeqr2sA4ynjaQ7tBPd+13aBu07swfRuc2sANTEgbaPZlt03md7J4uq6zWea3lza6c13a2J2Rec+wP+Jd2+7pNjvHJU+cJbO2W7rPPcnT1pJpGynVTnCP3k63Pv3k2tkamT/Q4tIGWPcJuCl9Wy1ObYN0G61VMi/NaR8k96N01bcCvy9lfkdLa65thXpoF9Cf5LjOL/3nqbQoxLwO9hf+fkXa7pp95c1Q18SK/APX4ovsNq/FF9nlfj99fjOmryX77nK/n/5neT7m/fTf6ukImS6pl6kq09dk2rzeW3uX+/XeLpncg5/ocVwMT9fQPF3DefBrdA96DS3za3eerqE9vPvyM7925/naWrxco8t/eb1PWN7x++eM3vfxwlvVJ3u6RufpWtbDu88+82uqD37NLfNrg56urXm6ZvjHX3PL/Brgw7sWxyqMLo7PdfVdEkF6XK5BmffTF8SSWAbLYlMsh63wCeyPETgUq+EwrI5jsAa+gLXwFayN87Auvor1cBHWx6Wq3OVYGTdiOG7GhrgDG+EerIDnsCJewKb4DUbjdxiD/uo++kBsgY9iSyyEcVgBW2FNbI21sR3Wx/YYgx0xDjthAsZjL+yG/bA7DsUeOAoTcCL2wsmYaDjGD/n9e9nHEr+y01v36a379NZ9eus+/5x1nz67vPWd/y+PP7b/P06pHlL//7Pdzv2JuZ/7E3O/95+YPvdXt7DruD7/lxlm3Mf9XniJ++o4y+i4W12A3hZ/tV7nWIBjnU6xLM59C6hYVkeMrM7LB+r6CTOW3ayf0LEcEouur+omiGVeN7HGqc/DwwFqLDUOjIKiurdxq66bUNUSnuslpm23523JPsyv6iUcy4/X9zfOII/n+xt1fvd7/NT5+z2Zf9BS1NKP37xWfd9vfik3/V6F2S71D7/JMtM5px/lWr+h+yM8J3nibavJlVnfiKG4RfKMsO21hBDT96Akq57/pZ7gEpG5km++zZ6H83ke3ZNSEqWJr76f0tM9aiNxjyw/xJbJPWq6vuR9ydPN5ul+sS4=
*/