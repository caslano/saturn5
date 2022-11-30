// ----------------------------------------------------------------------------
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------

#ifndef BOOST_PROPERTY_TREE_STRING_PATH_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_STRING_PATH_HPP_INCLUDED

#include <boost/property_tree/ptree_fwd.hpp>
#include <boost/property_tree/id_translator.hpp>
#include <boost/property_tree/exceptions.hpp>
#include <boost/property_tree/detail/ptree_utils.hpp>

#include <boost/static_assert.hpp>
#include <boost/assert.hpp>
#include <boost/type_traits/is_same.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>
#include <algorithm>
#include <string>
#include <iterator>

namespace boost { namespace property_tree
{
    namespace detail
    {
        template <typename Sequence, typename Iterator>
        void append_and_preserve_iter(Sequence &s, const Sequence &r,
                                      Iterator &, std::forward_iterator_tag)
        {
            // Here we boldly assume that anything that is not random-access
            // preserves validity. This is valid for the STL sequences.
            s.insert(s.end(), r.begin(), r.end());
        }
        template <typename Sequence, typename Iterator>
        void append_and_preserve_iter(Sequence &s, const Sequence &r,
                                      Iterator &it,
                                      std::random_access_iterator_tag)
        {
            // Convert the iterator to an index, and later back.
            typename std::iterator_traits<Iterator>::difference_type idx =
                it - s.begin();
            s.insert(s.end(), r.begin(), r.end());
            it = s.begin() + idx;
        }

        template <typename Sequence>
        inline std::string dump_sequence(const Sequence &)
        {
            return "<undumpable sequence>";
        }
        inline std::string dump_sequence(const std::string &s)
        {
            return s;
        }
#ifndef BOOST_NO_STD_WSTRING
        inline std::string dump_sequence(const std::wstring &s)
        {
            return narrow<std::string>(s.c_str());
        }
#endif
    }

    /// Default path class. A path is a sequence of values. Groups of values
    /// are separated by the separator value, which defaults to '.' cast to
    /// the sequence's value type. The group of values is then passed to the
    /// translator to get a key.
    ///
    /// If instantiated with std::string and id_translator\<std::string\>,
    /// it accepts paths of the form "one.two.three.four".
    ///
    /// @tparam String Any Sequence. If the sequence does not support random-
    ///                access iteration, concatenation of paths assumes that
    ///                insertions at the end preserve iterator validity.
    /// @tparam Translator A translator with internal_type == String.
    template <typename String, typename Translator>
    class string_path
    {
        BOOST_STATIC_ASSERT((is_same<String,
                                   typename Translator::internal_type>::value));
    public:
        typedef typename Translator::external_type key_type;
        typedef typename String::value_type char_type;

        /// Create an empty path.
        explicit string_path(char_type separator = char_type('.'));
        /// Create a path by parsing the given string.
        /// @param value A sequence, possibly with separators, that describes
        ///              the path, e.g. "one.two.three".
        /// @param separator The separator used in parsing. Defaults to '.'.
        /// @param tr The translator used by this path to convert the individual
        ///           parts to keys.
        string_path(const String &value, char_type separator = char_type('.'),
                    Translator tr = Translator());
        /// Create a path by parsing the given string.
        /// @param value A zero-terminated array of values. Only use if zero-
        ///              termination makes sense for your type, and your
        ///              sequence supports construction from it. Intended for
        ///              string literals.
        /// @param separator The separator used in parsing. Defaults to '.'.
        /// @param tr The translator used by this path to convert the individual
        ///           parts to keys.
        string_path(const char_type *value,
                    char_type separator = char_type('.'),
                    Translator tr = Translator());

        // Default copying doesn't do the right thing with the iterator
        string_path(const string_path &o);
        string_path& operator =(const string_path &o);

        /// Take a single element off the path at the front and return it.
        key_type reduce();

        /// Test if the path is empty.
        bool empty() const;

        /// Test if the path contains a single element, i.e. no separators.
        bool single() const;

        /// Get the separator used by this path.
        char_type separator() const { return m_separator; }

        std::string dump() const {
            return detail::dump_sequence(m_value);
        }

        /// Append a second path to this one.
        /// @pre o's separator is the same as this one's, or o has no separators
        string_path& operator /=(const string_path &o) {
            // If it's single, there's no separator. This allows to do
            // p /= "piece";
            // even for non-default separators.
            BOOST_ASSERT((m_separator == o.m_separator
                          || o.empty()
                          || o.single())
                         && "Incompatible paths.");
            if(!o.empty()) {
                String sub;
                if(!this->empty()) {
                    sub.push_back(m_separator);
                }
                sub.insert(sub.end(), o.cstart(), o.m_value.end());
                detail::append_and_preserve_iter(m_value, sub, m_start,
                    typename std::iterator_traits<s_iter>::iterator_category());
            }
            return *this;
        }

    private:
        typedef typename String::iterator s_iter;
        typedef typename String::const_iterator s_c_iter;
        String m_value;
        char_type m_separator;
        Translator m_tr;
        s_iter m_start;
        s_c_iter cstart() const { return m_start; }
    };

    template <typename String, typename Translator> inline
    string_path<String, Translator>::string_path(char_type separator)
        : m_separator(separator), m_start(m_value.begin())
    {}

    template <typename String, typename Translator> inline
    string_path<String, Translator>::string_path(const String &value,
                                                 char_type separator,
                                                 Translator tr)
        : m_value(value), m_separator(separator),
          m_tr(tr), m_start(m_value.begin())
    {}

    template <typename String, typename Translator> inline
    string_path<String, Translator>::string_path(const char_type *value,
                                                 char_type separator,
                                                 Translator tr)
        : m_value(value), m_separator(separator),
          m_tr(tr), m_start(m_value.begin())
    {}

    template <typename String, typename Translator> inline
    string_path<String, Translator>::string_path(const string_path &o)
        : m_value(o.m_value), m_separator(o.m_separator),
          m_tr(o.m_tr), m_start(m_value.begin())
    {
        std::advance(m_start, std::distance(o.m_value.begin(), o.cstart()));
    }

    template <typename String, typename Translator> inline
    string_path<String, Translator>&
    string_path<String, Translator>::operator =(const string_path &o)
    {
        m_value = o.m_value;
        m_separator = o.m_separator;
        m_tr = o.m_tr;
        m_start = m_value.begin();
        std::advance(m_start, std::distance(o.m_value.begin(), o.cstart()));
        return *this;
    }

    template <typename String, typename Translator>
    typename Translator::external_type string_path<String, Translator>::reduce()
    {
        BOOST_ASSERT(!empty() && "Reducing empty path");

        s_iter next_sep = std::find(m_start, m_value.end(), m_separator);
        String part(m_start, next_sep);
        m_start = next_sep;
        if(!empty()) {
          // Unless we're at the end, skip the separator we found.
          ++m_start;
        }

        if(optional<key_type> key = m_tr.get_value(part)) {
            return *key;
        }
        BOOST_PROPERTY_TREE_THROW(ptree_bad_path("Path syntax error", *this));
    }

    template <typename String, typename Translator> inline
    bool string_path<String, Translator>::empty() const
    {
        return m_start == m_value.end();
    }

    template <typename String, typename Translator> inline
    bool string_path<String, Translator>::single() const
    {
        return std::find(static_cast<s_c_iter>(m_start),
                         m_value.end(), m_separator)
            == m_value.end();
    }

    // By default, this is the path for strings. You can override this by
    // specializing path_of for a more specific form of std::basic_string.
    template <typename Ch, typename Traits, typename Alloc>
    struct path_of< std::basic_string<Ch, Traits, Alloc> >
    {
        typedef std::basic_string<Ch, Traits, Alloc> _string;
        typedef string_path< _string, id_translator<_string> > type;
    };

    template <typename String, typename Translator> inline
    string_path<String, Translator> operator /(
                                  string_path<String, Translator> p1,
                                  const string_path<String, Translator> &p2)
    {
        p1 /= p2;
        return p1;
    }

    // These shouldn't be necessary, but GCC won't find the one above.
    template <typename String, typename Translator> inline
    string_path<String, Translator> operator /(
                                  string_path<String, Translator> p1,
                                  const typename String::value_type *p2)
    {
        p1 /= p2;
        return p1;
    }

    template <typename String, typename Translator> inline
    string_path<String, Translator> operator /(
                                  const typename String::value_type *p1,
                                  const string_path<String, Translator> &p2)
    {
        string_path<String, Translator> t(p1);
        t /= p2;
        return t;
    }

}}

#endif

/* string_path.hpp
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
*/