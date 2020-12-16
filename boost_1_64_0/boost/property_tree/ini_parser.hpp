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
+N4Cn8HLGjxu/s/Jx2vhQ3+3j4/Jmy5Lpxdx+yx4NELe3AVezqSfRuKPOmIhvTTHiwsHy2cfk9eMl0c1VFdS9+7dlj7VIXr+ir+cyP8aR68XxvOLf98Dfy1fYl5Hsrej7NuaNPmZujZeNxsfXTBVfNtEn+rjrYfhOZXs1L7U6aKuVSROxM8DYbeNB5rXjT4/yrz1+7IuwffYW/Ynrj9WHrJFPhl/32mb6z3JL04071/T6Qdu7RXf+f2Ce/htS/noC/ogV6mT2NdC/btUnO+97+8+zvHw5x314WnHaCz9jp9cBe9T+Lz4krNTvK5tXs/D9QPw9xXxaRS+NsP6UvBvFV4mjvRuBA+b4c//Edc+TuI98PYc+puiPvIP1ztOHNJnTnlf9TLXayWuVsP97/WB28HTpLoku8h+ix3Hz5m5hn09QA+XyyPPxUveFO+fEifni2OD8JkF+Pzd8v26eEUr8TGBh1TrH3TC+5fA6Tlw40l+mGafvK/1dfH3k33+SPuWod8JP9f3EI+Oxpfxxmb2rWcr9ap8+/qRPLTc356j3vN2cTIrgZ/hCX+Nxry+/I0fbv6W/beFH/H3JdbCBfdd/Yb91udfzy6Kylz/Iuurhb+/C2dK8Si8viyL/s/mR8fi4dPp47l0fEqdvh3+8Yj8c6356v9WXo8HPwFvb4DvK8WB+LxsgzTxEW75fsSwT+z/DnZ2G14ubu3tBmfOlsfV0U+RN66bD2/W4GUN2Mcx8qc58ol36Svuvx9kfxPxLX3AcVXmMSrlOdgJ52HE+0P4NfvI6seeHhVvu+KNcd1pt/z2iGjsHD9fqT89t4DL+k2r4+clfcnf8Lyq1/GCwfpHu6MxV30wb5a+wb14+jX0U0kvSZ/7jn1uFV8z8QKvL03C6/n09FA0TkjXFyuzb+JrCl/YAR+r6TX5oTzxcfOOn5e9XN5cTU/4U52r5evvsMO5CfGIHzaGuwPw1KPFX/5QMDz63Pql0TgsXT71Nf8frA7lOt3Ps7/ns9cCdnoqXP7K50a4D/udOZ7fwsvUrXDgKf5eRv+fweEt8tKr9e/xlqb/kBe2wVfGOhe0SL7ZGZ7ar+bwZVw+vvc+feDDY+LfNauAh5V4kf7gWv2aendm6PuqU3eJxjLnoHsfCaeS1jcLP1vHHm6A93c7V9NTX6Wb9Ypvm58xf+fCi+6KxmHqevnsfulH1tsqrm+ztzXs9Ap5Cn8oqs4Q5+P6D/99Txx8A76Z93rXmzgQH7tEnT1+fssK9sWupm5jt6+y027ijDpz9kHzaAKHbrePcKPdG3hOD3z9YuvUN554Brt8Rhx/mN+2S0avPwlPj+FXnjuSA+8q1FHrHSlObIafe6Kx+F789Gz7hg+W/Bve/VPee7O4ugbuvOl+lezkCXrew19m65eYb2GKPzTXn5nEL/TDU/y9HftoNwlePEZP6nfrutvHM8XhL/UNxKVS1x/cRv7Nz5NV8OtW/tsf73tC/p6nXpyGx7c1zoMTz+CTj7GXz/nZEnWKhfA1Hd7JI0fByeKz8bTjxMWB1jEcXjyLh/DvUfdGY+ev2DU7azowfg4Ru7zNPvaJz/nyh7/xm+P41xb76ndei46G4/Fz25rBlQvVH65Vd7xQHvc4v1iHj8d1nYb6Zd3N/1Lx6yzX2YpXfABnG8HjpfHzqeEcPBv8gc/1xScy+NtT8tpZ+OFl7OFU/EZcmxPH05fsWxX7t7+lHfBufZKiYvv6rrwu/r2SAXjEZ+z1Mjhfxl460tcY8XcFfV8O3zqmyx/g4gx/00N1/LupzV3vOXjJjtf/R3430Pvj+s40OLAbLsP57o+qu8pnV56vv5OI/i513ngqHrhAHadpB3o=
*/