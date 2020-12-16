// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
// Copyright (C) 2015 Sebastian Redl
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_JSON_PARSER_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_JSON_PARSER_HPP_INCLUDED

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser/error.hpp>
#include <boost/property_tree/json_parser/detail/read.hpp>
#include <boost/property_tree/json_parser/detail/write.hpp>

#include <fstream>
#include <string>
#include <locale>

namespace boost { namespace property_tree { namespace json_parser
{

    /**
     * Read JSON from a the given stream and translate it to a property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @note Items of JSON arrays are translated into ptree keys with empty
     *       names. Members of objects are translated into named keys.
     * @note JSON data can be a string, a numeric value, or one of literals
     *       "null", "true" and "false". During parse, any of the above is
     *       copied verbatim into ptree data string.
     * @throw json_parser_error In case of error deserializing the property
     *                          tree.
     * @param stream Stream from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     */
    template<class Ptree>
    void read_json(std::basic_istream<
                       typename Ptree::key_type::value_type
                   > &stream,
                   Ptree &pt)
    {
        detail::read_json_internal(stream, pt, std::string());
    }

    /**
     * Read JSON from a the given file and translate it to a property tree.
     * @note Clears existing contents of property tree.  In case of error the
     *       property tree unmodified.
     * @note Items of JSON arrays are translated into ptree keys with empty
     *       names. Members of objects are translated into named keys.
     * @note JSON data can be a string, a numeric value, or one of literals
     *       "null", "true" and "false". During parse, any of the above is
     *       copied verbatim into ptree data string.
     * @throw json_parser_error In case of error deserializing the property
     *                          tree.
     * @param filename Name of file from which to read in the property tree.
     * @param[out] pt The property tree to populate.
     * @param loc The locale to use when reading in the file contents.
     */
    template<class Ptree>
    void read_json(const std::string &filename,
                   Ptree &pt,
                   const std::locale &loc = std::locale())
    {
        std::basic_ifstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(json_parser_error(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        detail::read_json_internal(stream, pt, filename);
    }

    /**
     * Translates the property tree to JSON and writes it the given output
     * stream.
     * @note Any property tree key containing only unnamed subkeys will be
     *       rendered as JSON arrays.
     * @pre @e pt cannot contain keys that have both subkeys and non-empty data.
     * @throw json_parser_error In case of error translating the property tree
     *                          to JSON or writing to the output stream.
     * @param stream The stream to which to write the JSON representation of the
     *               property tree.
     * @param pt The property tree to tranlsate to JSON and output.
     * @param pretty Whether to pretty-print. Defaults to true for backward
     *               compatibility.
     */
    template<class Ptree>
    void write_json(std::basic_ostream<
                        typename Ptree::key_type::value_type
                    > &stream,
                    const Ptree &pt,
                    bool pretty = true)
    {
        write_json_internal(stream, pt, std::string(), pretty);
    }

    /**
     * Translates the property tree to JSON and writes it the given file.
     * @note Any property tree key containing only unnamed subkeys will be
     *       rendered as JSON arrays.
     * @pre @e pt cannot contain keys that have both subkeys and non-empty data.
     * @throw json_parser_error In case of error translating the property tree
     *                          to JSON or writing to the file.
     * @param filename The name of the file to which to write the JSON
     *                 representation of the property tree.
     * @param pt The property tree to translate to JSON and output.
     * @param loc The locale to use when writing out to the output file.
     * @param pretty Whether to pretty-print. Defaults to true and last place
     *               for backward compatibility.
     */
    template<class Ptree>
    void write_json(const std::string &filename,
                    const Ptree &pt,
                    const std::locale &loc = std::locale(),
                    bool pretty = true)
    {
        std::basic_ofstream<typename Ptree::key_type::value_type>
            stream(filename.c_str());
        if (!stream)
            BOOST_PROPERTY_TREE_THROW(json_parser_error(
                "cannot open file", filename, 0));
        stream.imbue(loc);
        write_json_internal(stream, pt, filename, pretty);
    }

} } }

namespace boost { namespace property_tree
{
    using json_parser::read_json;
    using json_parser::write_json;
    using json_parser::json_parser_error;
} }

#endif

/* json_parser.hpp
/dV+zo/7Kuos7CA7fm7xvXgMvFjJPpq/Kp8aKs8+T/33JnWHofCqgz7QNfKJs+HGd66Dz3fWx07JzworvN/5h7xMfeHSRPQ6fr28nH3u458V9vsX93k0w/XgHjtqqI6b85z9Ginex8/3PwU/PKAfPMz8Gton98vuAI+a8Qv11N2+J5Q50n1fZk+vwfsJ1on/Vct/xjyuLstOl8KPknz79Bw/Hs7P+FfeG/DCef/iQudbk9bXXT9Sf3KteL7A69llvsfwJFz0/+Ud+FN7+90Qn+FPk361P+JpkfmVw4fKtexnL/sZL37Uhffvi+v6HZ3j+pfnjk8ynx0n87sF8FWeWnEO+4drc+Dojh/gb0t5Qvw7j5/gjWl4gd9pK36K/vRLFkxWx8xkv/xv/SNxPVy8/rd9nao/7lxGsbpDspe4NRu/pKcCdcRc+fSIh+3/A/An7oveCifi35l9TvxUR+iqvt/gtQznxOHht3gdHtX1IfVL15/QTJ4yyD7djJdepc7T1rr5UeObxDf+3/lbvKyueR/vek+Lb+nyJfxg5Wmel1CMH9mHUnl9/t/FBfxveUfnHs6Dc/XE0VQ01nsRvz0C3z2RPVhPyXH4drb9rqafKv7wgnrPQfYkDhQstJ/58LFcvtFIHWa2fAqONdgQjWWviINn0hf8KJ+ZcK4H31kAx2M+0z4ay1uIIy34WT39+xPxcPXQnvwu90I4oJ4e0sBIH+aTvJ3d7HSupKM86gX6r5vO/vXjP5cfnK0+M5W9+H5B70vgWk/+upSdj5c/W+dSzznLH4Ff48nF98DHWngDPr76WLywF3xnl9P16/P+7nxdif2swz+vjMZS+FQQn7faKN5tE0e3qEes4Rf6fgWb2OtC/x//juaPPh+fD4a/jcfjJ/PsPz9rVyFfwydm9oA35/Kfm+jjWPGAPa67yjxKxblu0eu95Ql55rX5r/AzhdfdI47XSuEv8uLp9nEM3l0XX7nS/hSId9P5m9eX99FnaCxOPg7nClLOxdLrOvVWeUdWtXgSP7fiz/j5ZXi0sThTfHtH3fawetlt/OtUfe9lcLGI/zVP0b+6xFS4o15TNFGcbms/miU8hzjD+XD2P46/H6H+JJ/Pj79/fgT9dZDf7RN/iuBwE3qZKp6cwF4+wjf/Sb/8aUFzdjWKP7XCc35w3YnR2PoevFadeHZvddMcffUK9m5fOvekr64ZzmFFYzV/LeTfE51DqQj+GsUn+u8cjZUDxT18Ypz8KM/8m30nrjyL3+xyv6Pi3zmP+Yd6TQn99xGXatn/s+HcXXjIddE44hR2ewP+g7+ubgh3HmWXn6VF4zw8up48/874Obvm+6y4rn8y+HJ8YRL+zC+n38tevkmHN3DxCvxnv/XgpStnZMiP8MU5GfiR/PwJesmCz8+yt2P4a1N9Rb+ntu40eGa+FS38f448JK7/3W+/h8qL4eds9dps9ZO97/PHG9RRhrHL6+VJ/G3wmeqE/c0f38iUVwzrLk9IY7fXsZ92ePyl1nunfYj9XH6SKT+uGCdPFUezctX5suC5c825O/jxS87TwO12cG+5fKQUL8uVlzTjp3kPuW4auzk3/p0e8QqelDdRN60nn9xjXS3hcG3xdqC6QQN9lAXqon34ZVd8eC28nwLPz7RPefLQ9/CcjfD3WPoQByrpreiw9ZwDZ+Pf06y2n8dHr/d+mr7ri/tV8rLa4t7sdPOxD/fEfSV2v9i+fcrvToJT0/S9D8PZ/vYvft4iO1m5PRor32MvCf6dJw41wCPukI8u83fsB+JmGb3v/kJ8aqzf1kOe4NzZsAPqD8ex40b0wr4nWVfzAfJcemx4tT61+FSoXjCunfyklXzAuic=
*/