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
gnG6s3zjFLKHG6fTxaji9p85u1l+ZuyWdmt2u6Kw24FjnN02Q7q0urwYBIoWaojMYXQpDmNoVf3++zF20Htib23AG5onNnuD2e9fMFXbpFyUv+mt7Ft71wYNxFhCME5BUNe3FwDFLUeMKIomFJceMaKY5O/yx3KXP/cIR7FYj+KNsMAoVuBidN3FUWxchE3f5yhHMekoQ1GsPIqRRzmK/xwhFI/sDIxielXc/lmHTQgeXGdAsGid2e3f+xIiiIMGdGhIYG//ZAfw9pMn+3zxe+ETJ3J7tQz8IofR4ffd0l6dxnFpvaloR7XSTMWd69Dh72Vw+OP3llpxck+0g1x/N9v47QByVfvnoVSoV4ot5QYRnsHv/1Ln99dHE/drgdHExe8Fh7r+KcXzn+Hv+SOLLe6NzugVnfN/xynVU0ueobhmbdaaXLOdAYnLlvMt1akapT+ldiw6SKJf8h7z72eeZFin6puR1g/F84V1iw5S5T11eTdqCR57p9v89/Aa9soCzexKa/Rm92hmA2Of+275LDVPsMHkyuiXnwWTqyhmgkkxqx80KuZOf99/Hff9zx0oRzHnYDGLqqSYH/3AFTNnK+0DfZAr5pKDlfb9VcWceJAr5oiD5Dw6fmDO4xWuk1eDq6CTf+436WSP1QadbL/a7Pt3nWzw/Qf3VHh113cmAbunUrw6Zr+RV+NM8PXeb4Svtb/nfzv3/O/db/L8
*/