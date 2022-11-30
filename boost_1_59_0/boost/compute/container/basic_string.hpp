//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CONTAINER_BASIC_STRING_HPP
#define BOOST_COMPUTE_CONTAINER_BASIC_STRING_HPP

#include <string>
#include <cstring>

#include <boost/compute/cl.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/algorithm/search.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <iosfwd>

namespace boost {
namespace compute {

/// \class basic_string
/// \brief A template for a dynamically-sized character sequence.
///
/// The \c basic_string class provides a generic template for a dynamically-
/// sized character sequence. This is most commonly used through the \c string
/// typedef (for \c basic_string<char>).
///
/// For example, to create a string on the device with its contents copied
/// from a C-string on the host:
/// \code
/// boost::compute::string str("hello, world!");
/// \endcode
///
/// \see \ref vector "vector<T>"
template<class CharT, class Traits = std::char_traits<CharT> >
class basic_string
{
public:
    typedef Traits traits_type;
    typedef typename Traits::char_type value_type;
    typedef size_t size_type;
    static const size_type npos = size_type(-1);
    typedef typename ::boost::compute::vector<CharT>::reference reference;
    typedef typename ::boost::compute::vector<CharT>::const_reference const_reference;
    typedef typename ::boost::compute::vector<CharT>::iterator iterator;
    typedef typename ::boost::compute::vector<CharT>::const_iterator const_iterator;
    typedef typename ::boost::compute::vector<CharT>::reverse_iterator reverse_iterator;
    typedef typename ::boost::compute::vector<CharT>::const_reverse_iterator const_reverse_iterator;

    basic_string()
    {
    }

    basic_string(size_type count, CharT ch)
        : m_data(count)
    {
        std::fill(m_data.begin(), m_data.end(), ch);
    }

    basic_string(const basic_string &other,
                 size_type pos,
                 size_type count = npos)
        : m_data(other.begin() + pos,
                 other.begin() + (std::min)(other.size(), count))
    {
    }

    basic_string(const char *s, size_type count)
        : m_data(s, s + count)
    {
    }

    basic_string(const char *s)
        : m_data(s, s + std::strlen(s))
    {
    }

    template<class InputIterator>
    basic_string(InputIterator first, InputIterator last)
        : m_data(first, last)
    {
    }

    basic_string(const basic_string<CharT, Traits> &other)
        : m_data(other.m_data)
    {
    }

    basic_string<CharT, Traits>& operator=(const basic_string<CharT, Traits> &other)
    {
        if(this != &other){
            m_data = other.m_data;
        }

        return *this;
    }

    ~basic_string()
    {
    }

    reference at(size_type pos)
    {
        return m_data.at(pos);
    }

    const_reference at(size_type pos) const
    {
        return m_data.at(pos);
    }

    reference operator[](size_type pos)
    {
        return m_data[pos];
    }

    const_reference operator[](size_type pos) const
    {
        return m_data[pos];
    }

    reference front()
    {
        return m_data.front();
    }

    const_reference front() const
    {
        return m_data.front();
    }

    reference back()
    {
        return m_data.back();
    }

    const_reference back() const
    {
        return m_data.back();
    }

    iterator begin()
    {
        return m_data.begin();
    }

    const_iterator begin() const
    {
        return m_data.begin();
    }

    const_iterator cbegin() const
    {
        return m_data.cbegin();
    }

    iterator end()
    {
        return m_data.end();
    }

    const_iterator end() const
    {
        return m_data.end();
    }

    const_iterator cend() const
    {
        return m_data.cend();
    }

    reverse_iterator rbegin()
    {
        return m_data.rbegin();
    }

    const_reverse_iterator rbegin() const
    {
        return m_data.rbegin();
    }

    const_reverse_iterator crbegin() const
    {
        return m_data.crbegin();
    }

    reverse_iterator rend()
    {
        return m_data.rend();
    }

    const_reverse_iterator rend() const
    {
        return m_data.rend();
    }

    const_reverse_iterator crend() const
    {
        return m_data.crend();
    }

    bool empty() const
    {
        return m_data.empty();
    }

    size_type size() const
    {
        return m_data.size();
    }

    size_type length() const
    {
        return m_data.size();
    }

    size_type max_size() const
    {
        return m_data.max_size();
    }

    void reserve(size_type size)
    {
        m_data.reserve(size);
    }

    size_type capacity() const
    {
        return m_data.capacity();
    }

    void shrink_to_fit()
    {
        m_data.shrink_to_fit();
    }

    void clear()
    {
        m_data.clear();
    }

    void swap(basic_string<CharT, Traits> &other)
    {
        if(this != &other)
        {
            ::boost::compute::vector<CharT> temp_data(other.m_data);
            other.m_data = m_data;
            m_data = temp_data;
        }
    }

    basic_string<CharT, Traits> substr(size_type pos = 0,
                                       size_type count = npos) const
    {
        return basic_string<CharT, Traits>(*this, pos, count);
    }

    /// Finds the first character \p ch
    size_type find(CharT ch, size_type pos = 0) const
    {
        const_iterator iter = ::boost::compute::find(begin() + pos, end(), ch);
        if(iter == end()){
            return npos;
        }
        else {
            return static_cast<size_type>(std::distance(begin(), iter));
        }
    }

    /// Finds the first substring equal to \p str
    size_type find(basic_string& str, size_type pos = 0) const
    {
        const_iterator iter = ::boost::compute::search(begin() + pos, end(),
                                                       str.begin(), str.end());
        if(iter == end()){
            return npos;
        }
        else {
            return static_cast<size_type>(std::distance(begin(), iter));
        }
    }

    /// Finds the first substring equal to the character string
    /// pointed to by \p s.
    /// The length of the string is determined by the first null character.
    ///
    /// For example, the following code
    /// \snippet test/test_string.cpp string_find
    ///
    /// will return 5 as position.
    size_type find(const char* s, size_type pos = 0) const
    {
        basic_string str(s);
        const_iterator iter = ::boost::compute::search(begin() + pos, end(),
                                                       str.begin(), str.end());
        if(iter == end()){
            return npos;
        }
        else {
            return static_cast<size_type>(std::distance(begin(), iter));
        }
    }

private:
    ::boost::compute::vector<CharT> m_data;
};

template<class CharT, class Traits>
std::ostream&
operator<<(std::ostream& stream,
           boost::compute::basic_string<CharT, Traits>const& outStr)
{
    command_queue queue = ::boost::compute::system::default_queue();
    boost::compute::copy(outStr.begin(),
                        outStr.end(),
                        std::ostream_iterator<CharT>(stream),
                        queue);
    return stream;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_CONTAINER_BASIC_STRING_HPP

/* basic_string.hpp
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
*/