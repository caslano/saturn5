#ifndef BOOST_ARCHIVE_ITERATORS_ISTREAM_ITERATOR_HPP
#define BOOST_ARCHIVE_ITERATORS_ISTREAM_ITERATOR_HPP

// MS compatible compilers support #pragma once
#if defined(_MSC_VER)
# pragma once
#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// istream_iterator.hpp

// (C) Copyright 2002 Robert Ramey - http://www.rrsd.com .
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for updates, documentation, and revision history.

// note: this is a custom version of the standard istream_iterator.
// This is necessary as the standard version doesn't work as expected
// for wchar_t based streams on systems for which wchar_t not a true
// type but rather a synonym for some integer type.

#include <cstddef> // NULL
#include <istream>
#include <boost/iterator/iterator_facade.hpp>

namespace boost {
namespace archive {
namespace iterators {

// given a type, make an input iterator based on a pointer to that type
template<class Elem = char>
class istream_iterator :
    public boost::iterator_facade<
        istream_iterator<Elem>,
        Elem,
        std::input_iterator_tag,
        Elem
    >
{
    friend class boost::iterator_core_access;
    typedef istream_iterator this_t ;
    typedef typename boost::iterator_facade<
        istream_iterator<Elem>,
        Elem,
        std::input_iterator_tag,
        Elem
    > super_t;
    typedef typename std::basic_istream<Elem> istream_type;

    bool equal(const this_t & rhs) const {
        // note: only  works for comparison against end of stream
        return m_istream == rhs.m_istream;
    }

    //Access the value referred to
    Elem dereference() const {
        return static_cast<Elem>(m_istream->peek());
    }

    void increment(){
        if(NULL != m_istream){
            m_istream->ignore(1);
        }
    }

    istream_type *m_istream;
    Elem m_current_value;
public:
    istream_iterator(istream_type & is) :
        m_istream(& is)
    {
        //increment();
    }

    istream_iterator() :
        m_istream(NULL),
        m_current_value(NULL)
    {}

    istream_iterator(const istream_iterator<Elem> & rhs) :
        m_istream(rhs.m_istream),
        m_current_value(rhs.m_current_value)
    {}
};

} // namespace iterators
} // namespace archive
} // namespace boost

#endif // BOOST_ARCHIVE_ITERATORS_ISTREAM_ITERATOR_HPP

/* istream_iterator.hpp
S34Cm/sXWezeWNi+dReD6Gtg3W8GvK7dBIYVO81fbRgEdW9I3CuzFLxfeoI9HZ6JU1regBE907DxhPy8TamDaHp6C6t+9Co0sDvLar5ZCWcrFuCLe9SAq/bTcdiQK9ituQWuK1YQ0l9780/Vm0PjtKWYrGkCGVJJPsMxEypMW8ai44bBu08fQNPvGJ6YdIfb1dkBY4sW4uHrL+Lxp0dYttN8sF7YAOc5N8b0ldV4h21bIb11O+Y9OAAub7+Gfeo8xBcwH1532on9uqxlJVL/DOv6tgP7fu+gxJw/8eMXWuPGV8X5MuudYNMii+/oexRO3ivAfs5vjuPrPcOwmcbQq/MzrNWqEzbseo5NLhOHmkclWJ8KzpD/Z2+suiYFZ912BaMLFbHu6zXs+jNzrHIphE96fgOSPF7zSG4KN30OsFuFsmG622UMOxOMrWLnwVQXa6h+LxIOVT2MUWkHuHbuHCgb5A12Hd7BnZNT+OllGjzvt5+9Di4BD95UwbIzXSDC257f2d4TzzfoxaP/5IFVY97B1rk90GXqT8z7eQV0kAYy1skFmiXY49znnmBvchge1nqMJ6ulwM02G6B305f8+sVEPFTwDZ9TfS8cfboSIvuehctvk9n85Au44GFhcHSvCYPfB7IqJf2wZe/37F1yJzjeag2PKdwVdj0dyC+fOoItAj/xGvl/xUG95+GIzpVpn7eOP7sSiX9u6AIvssrCkVk3sObtm/AIt/G4rsnY9MJPbMKjZFi8uT4/Qn3a++19Vqn/QbhxcxOf9aQuzLlXnqfT8mJyt4swa8QBTHXqx2PHZGDXE7Gw6MZ1WK6pAcejLSF4/SpeZAf5Sl33od8+M3QpUBhOzpiGJoW0zCltE17dcAE8ElfB2/vGfPXOodir0mm+qVkWFqn9joVZ2eHUn47y2R+GQ0pvJxbf/Ca+PvwCKqftxySj8uAxfxl0uh7KMs90wEar+mOMayG4168BVvm5PFZP64ktNk9EzzvLsePI9ZBU0xx8xs/FK0OXsM59AWZ2XcSPjvyIVr+64cfhGbAooCU/V/A2+rY5ChP3LMJRJR9inSQO9tda8KBTrjCpYBHcsyIVLAYPguSX0+D8p0fYO3UHTjH+wN9f6QArq0SydYVuwf0h1VifkRWw04J67OiEStgswx3Gmb+FsAQJOn/Yj753P/Ga2S2h5cZhuCCyLxZ+cJb5HbdCsGnKnT4UgxIfZ+P18IuYf+MqXnfEfnhSfQZavp2ErpOMsX8owttextCwbh0wqpIFxs1agbd7DRi4ehscaHcYTy5egQ4m66FT1aLg1CofzOtUFdfzIHbvhjH2qMLZ9NrdMeX0Cx42yRz3vhwLF88nQpt6pry9b0vo0rwcri1QA/O9rwDVU8OhzIhGWLr6bcxs0QQdrhaAKUO94enw1nCh5k6s9rwAbpwWBD5lLsGx4vN4fa9HGFttOnv4oQNWHBPI+uw9imtPREF8pTpwoa0zVO5iAZXXBLIfNyyF0Oqx0NK3GXYp6sLGvjiA1z+VgOXXHXD8+H3oGRQOvgXcIPPmRdy98QxrvjgVi2WnwfoRE6Fv8Es4tPAj/BBbBW53WQyJj9LhTqVT8LjiHIz9IT++NG2AVUsVgPEf6/KKFq9xZ9owbpUwC/ZQHD1N7oKLN/BTY2/DLxtPwYx2u6BEQm3eL787nbORRffFNvg49iFbnnIZLr6P4d4j9kJJExve0nQqLnG7BGl2XSE89h7vf+sUdvxUnM1vdx3LFuvNJq3xxe07kuGDXWPIzLzMN7VaDLWy7Nni/TUw1aobk7a9xZJBFZhXOT90KX0TZk4YjNdTn7BHpxASms6AuwXnQ8MyM5gruw1dx1g=
*/