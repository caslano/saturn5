// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2009 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_INI_PARSER_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_INI_PARSER_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/ptree_utils.hpp>
#include <boost/property_tree/detail/file_parser_error.hpp>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <locale>

namespace boost { namespace property_tree { namespace ini_parser
{

    /**
     * Determines whether the @c flags are valid for use with the ini_parser.
     * @param flags value to check for validity as flags to ini_parser.
     * @return true if the flags are valid, false otherwise.
     */
    inline bool validate_flags(int flags)
    {
        return flags == 0;
    }

    /** Indicates an error parsing INI formatted data. */
    class ini_parser_error: public file_parser_error
    {
    public:
        /**
         * Construct an @c ini_parser_error
         * @param message Message describing the parser error.
         * @param filename The name of the file being parsed containing the
         *                 error.
         * @param line The line in the given file where an error was
         *             encountered.
         */
        ini_parser_error(const std::string &message,
                         const std::string &filename,
                         unsigned long line)
            : file_parser_error(message, filename, line)
        {
        }
    };

    /**
     * Read INI from a the given stream and translate it to a property tree.
     * @note Clears existing contents of property tree. In case of error
     *       the property tree is not modified.
     * @throw ini_parser_error If a format violation is found.
     * @param stream Stream from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     */
    template<class Ptree>
    void read_ini(std::basic_istream<
                    typename Ptree::key_type::value_type> &stream,
                  Ptree &pt)
    {
        typedef typename Ptree::key_type::value_type Ch;
        typedef std::basic_string<Ch> Str;
        const Ch semicolon = stream.widen(';');
        const Ch hash = stream.widen('#');
        const Ch lbracket = stream.widen('[');
        const Ch rbracket = stream.widen(']');

        Ptree local;
        unsigned long line_no = 0;
        Ptree *section = 0;
        Str line;

        // For all lines
        while (stream.good())
        {

            // Get line from stream
            ++line_no;
            std::getline(stream, line);
            if (!stream.good() && !stream.eof())
                BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                    "read error", "", line_no));

            // If line is non-empty
            line = property_tree::detail::trim(line, stream.getloc());
            if (!line.empty())
            {
                // Comment, section or key?
                if (line[0] == semicolon || line[0] == hash)
                {
                    // Ignore comments
                }
                else if (line[0] == lbracket)
                {
                    // If the previous section was empty, drop it again.
                    if (section && section->empty())
                        local.pop_back();
                    typename Str::size_type end = line.find(rbracket);
                    if (end == Str::npos)
                        BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                            "unmatched '['", "", line_no));
                    Str key = property_tree::detail::trim(
                        line.substr(1, end - 1), stream.getloc());
                    if (local.find(key) != local.not_found())
                        BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                            "duplicate section name", "", line_no));
                    section = &local.push_back(
                        std::make_pair(key, Ptree()))->second;
                }
                else
                {
                    Ptree &container = section ? *section : local;
                    typename Str::size_type eqpos = line.find(Ch('='));
                    if (eqpos == Str::npos)
                        BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                            "'=' character not found in line", "", line_no));
                    if (eqpos == 0)
                        BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                            "key expected", "", line_no));
                    Str key = property_tree::detail::trim(
                        line.substr(0, eqpos), stream.getloc());
                    Str data = property_tree::detail::trim(
                        line.substr(eqpos + 1, Str::npos), stream.getloc());
                    if (container.find(key) != container.not_found())
                        BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                            "duplicate key name", "", line_no));
                    container.push_back(std::make_pair(key, Ptree(data)));
                }
            }
        }
        // If the last section was empty, drop it again.
        if (section && section->empty())
            local.pop_back();

        // Swap local ptree with result ptree
        pt.swap(local);

    }

    /**
     * Read INI from a the given file and translate it to a property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @throw ini_parser_error In case of error deserializing the property tree.
     * @param filename Name of file from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     * @param loc The locale to use when reading in the file contents.
     */
    template<class Ptree>
    void read_ini(const std::string &filename, 
                  Ptree &pt,
                  const std::locale &loc = std::locale())
    {
        std::basic_ifstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        try {
            read_ini(stream, pt);
        }
        catch (ini_parser_error &e) {
            BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                e.message(), filename, e.line()));
        }
    }

    namespace detail
    {
        template<class Ptree>
        void check_dupes(const Ptree &pt)
        {
            if(pt.size() <= 1)
                return;
            const typename Ptree::key_type *lastkey = 0;
            typename Ptree::const_assoc_iterator it = pt.ordered_begin(),
                                                 end = pt.not_found();
            lastkey = &it->first;
            for(++it; it != end; ++it) {
                if(*lastkey == it->first)
                    BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                        "duplicate key", "", 0));
                lastkey = &it->first;
            }
        }

        template <typename Ptree>
        void write_keys(std::basic_ostream<
                                      typename Ptree::key_type::value_type
                                  > &stream,
                                  const Ptree& pt,
                                  bool throw_on_children)
        {
            typedef typename Ptree::key_type::value_type Ch;
            for (typename Ptree::const_iterator it = pt.begin(), end = pt.end();
                 it != end; ++it)
            {
                if (!it->second.empty()) {
                    if (throw_on_children) {
                        BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                            "ptree is too deep", "", 0));
                    }
                    continue;
                }
                stream << it->first << Ch('=')
                    << it->second.template get_value<
                        std::basic_string<Ch> >()
                    << Ch('\n');
            }
        }

        template <typename Ptree>
        void write_top_level_keys(std::basic_ostream<
                                      typename Ptree::key_type::value_type
                                  > &stream,
                                  const Ptree& pt)
        {
            write_keys(stream, pt, false);
        }

        template <typename Ptree>
        void write_sections(std::basic_ostream<
                                typename Ptree::key_type::value_type
                            > &stream,
                            const Ptree& pt)
        {
            typedef typename Ptree::key_type::value_type Ch;
            for (typename Ptree::const_iterator it = pt.begin(), end = pt.end();
                 it != end; ++it)
            {
                if (!it->second.empty()) {
                    check_dupes(it->second);
                    if (!it->second.data().empty())
                        BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                            "mixed data and children", "", 0));
                    stream << Ch('[') << it->first << Ch(']') << Ch('\n');
                    write_keys(stream, it->second, true);
                }
            }
        }
    }

    /**
     * Translates the property tree to INI and writes it the given output
     * stream.
     * @pre @e pt cannot have data in its root.
     * @pre @e pt cannot have keys both data and children.
     * @pre @e pt cannot be deeper than two levels.
     * @pre There cannot be duplicate keys on any given level of @e pt.
     * @throw ini_parser_error In case of error translating the property tree to
     *                         INI or writing to the output stream.
     * @param stream The stream to which to write the INI representation of the 
     *               property tree.
     * @param pt The property tree to tranlsate to INI and output.
     * @param flags The flags to use when writing the INI file.
     *              No flags are currently supported.
     */
    template<class Ptree>
    void write_ini(std::basic_ostream<
                       typename Ptree::key_type::value_type
                   > &stream,
                   const Ptree &pt,
                   int flags = 0)
    {
        BOOST_ASSERT(validate_flags(flags));
        (void)flags;

        if (!pt.data().empty())
            BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                "ptree has data on root", "", 0));
        detail::check_dupes(pt);

        detail::write_top_level_keys(stream, pt);
        detail::write_sections(stream, pt);
    }

    /**
     * Translates the property tree to INI and writes it the given file.
     * @pre @e pt cannot have data in its root.
     * @pre @e pt cannot have keys both data and children.
     * @pre @e pt cannot be deeper than two levels.
     * @pre There cannot be duplicate keys on any given level of @e pt.
     * @throw info_parser_error In case of error translating the property tree
     *                          to INI or writing to the file.
     * @param filename The name of the file to which to write the INI
     *                 representation of the property tree.
     * @param pt The property tree to tranlsate to INI and output.
     * @param flags The flags to use when writing the INI file.
     *              The following flags are supported:
     * @li @c skip_ini_validity_check -- Skip check if ptree is a valid ini. The
     *     validity check covers the preconditions but takes <tt>O(n log n)</tt>
     *     time.
     * @param loc The locale to use when writing the file.
     */
    template<class Ptree>
    void write_ini(const std::string &filename,
                   const Ptree &pt,
                   int flags = 0,
                   const std::locale &loc = std::locale())
    {
        std::basic_ofstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        try {
            write_ini(stream, pt, flags);
        }
        catch (ini_parser_error &e) {
            BOOST_PROPERTY_TREE_THROW(ini_parser_error(
                e.message(), filename, e.line()));
        }
    }

} } }

namespace boost { namespace property_tree
{
    using ini_parser::ini_parser_error;
    using ini_parser::read_ini;
    using ini_parser::write_ini;
} }

#endif

/* ini_parser.hpp
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
*/