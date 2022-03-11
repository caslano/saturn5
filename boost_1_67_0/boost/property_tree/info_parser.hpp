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