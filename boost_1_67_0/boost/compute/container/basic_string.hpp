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