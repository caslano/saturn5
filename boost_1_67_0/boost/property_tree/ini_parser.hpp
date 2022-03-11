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