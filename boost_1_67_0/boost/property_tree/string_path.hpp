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