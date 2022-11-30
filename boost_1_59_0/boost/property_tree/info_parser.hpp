// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_INFO_PARSER_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_INFO_PARSER_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/detail/info_parser_error.hpp>
#include <boost/property_tree/detail/info_parser_writer_settings.hpp>
#include <boost/property_tree/detail/info_parser_read.hpp>
#include <boost/property_tree/detail/info_parser_write.hpp>
#include <istream>

namespace boost { namespace property_tree { namespace info_parser
{

    /**
     * Read INFO from a the given stream and translate it to a property tree.
     * @note Replaces the existing contents. Strong exception guarantee.
     * @throw info_parser_error If the stream cannot be read, doesn't contain
     *                          valid INFO, or a conversion fails.
     */
    template<class Ptree, class Ch>
    void read_info(std::basic_istream<Ch> &stream, Ptree &pt)
    {
        Ptree local;
        read_info_internal(stream, local, std::string(), 0);
        pt.swap(local);
    }

    /**
     * Read INFO from a the given stream and translate it to a property tree.
     * @note Replaces the existing contents. Strong exception guarantee.
     * @param default_ptree If parsing fails, pt is set to a copy of this tree.
     */
    template<class Ptree, class Ch>
    void read_info(std::basic_istream<Ch> &stream, Ptree &pt,
                   const Ptree &default_ptree)
    {
        try {
            read_info(stream, pt);
        } catch(file_parser_error &) {
            pt = default_ptree;
        }
    }

    /**
     * Read INFO from a the given file and translate it to a property tree. The
     * tree's key type must be a string type, i.e. it must have a nested
     * value_type typedef that is a valid parameter for basic_ifstream.
     * @note Replaces the existing contents. Strong exception guarantee.
     * @throw info_parser_error If the file cannot be read, doesn't contain
     *                          valid INFO, or a conversion fails.
     */
    template<class Ptree>
    void read_info(const std::string &filename, Ptree &pt,
                   const std::locale &loc = std::locale())
    {
        std::basic_ifstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream) {
            BOOST_PROPERTY_TREE_THROW(info_parser_error(
                "cannot open file for reading", filename, 0));
        }
        stream.imbue(loc);
        Ptree local;
        read_info_internal(stream, local, filename, 0);
        pt.swap(local);
    }

    /**
     * Read INFO from a the given file and translate it to a property tree. The
     * tree's key type must be a string type, i.e. it must have a nested
     * value_type typedef that is a valid parameter for basic_ifstream.
     * @note Replaces the existing contents. Strong exception guarantee.
     * @param default_ptree If parsing fails, pt is set to a copy of this tree.
     */
    template<class Ptree>
    void read_info(const std::string &filename,
                   Ptree &pt,
                   const Ptree &default_ptree,
                   const std::locale &loc = std::locale())
    {
        try {
            read_info(filename, pt, loc);
        } catch(file_parser_error &) {
            pt = default_ptree;
        }
    }

    /**
     * Writes a tree to the stream in INFO format.
     * @throw info_parser_error If the stream cannot be written to, or a
     *                          conversion fails.
     * @param settings The settings to use when writing the INFO data.
     */
    template<class Ptree, class Ch>
    void write_info(std::basic_ostream<Ch> &stream,
                    const Ptree &pt,
                    const info_writer_settings<Ch> &settings =
                        info_writer_settings<Ch>())
    {
        write_info_internal(stream, pt, std::string(), settings);
    }

    /**
     * Writes a tree to the file in INFO format. The tree's key type must be a
     * string type, i.e. it must have a nested value_type typedef that is a
     * valid parameter for basic_ofstream.
     * @throw info_parser_error If the file cannot be written to, or a
     *                          conversion fails.
     * @param settings The settings to use when writing the INFO data.
     */
    template<class Ptree>
    void write_info(const std::string &filename,
                    const Ptree &pt,
                    const std::locale &loc = std::locale(),
                    const info_writer_settings<
                        typename Ptree::key_type::value_type
                    > &settings =
                        info_writer_make_settings<
                            typename Ptree::key_type::value_type>())
    {
        std::basic_ofstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream) {
            BOOST_PROPERTY_TREE_THROW(info_parser_error(
                "cannot open file for writing", filename, 0));
        }
        stream.imbue(loc);
        write_info_internal(stream, pt, filename, settings);
    }

} } }

namespace boost { namespace property_tree
{
    using info_parser::info_parser_error;
    using info_parser::read_info;
    using info_parser::write_info;
    using info_parser::info_writer_settings;
    using info_parser::info_writer_make_settings;
} }

#endif

/* info_parser.hpp
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
*/