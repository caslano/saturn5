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
G+wRn8+/Bc9tJD/MjPsu+jT71bv/ge8s5dcfijdNU9G8xZuVN8mH4u9pnqPuMdC8XkyLxmJxMMP+zpTXFopv7aJxbYH+WQ/2vEA+vUO+sZFddVF//Dc+8Dh9fhCfe4FX1YlobA2XG0djc/6bOpve9VXnncNvZ7BT5xYyL/D3UHb/IN7scxVz6Um8zsMTm+HRI/CHonuT+Ag+1y4aM4fC4fr0xc+y4Gj5B+zyA/X1I8WblfDga/xmCv6yPaEuiN88S+8L7be6UsE16puT8aXh+N3P4kdbcbW/fLixfHg1nGJPe+eK41vppxb7uBX/e1seuoq/7fe+bOd5fzFPuDNH/M3+nX3FdY3TfI5fTYL3I/ayux/gVyneUBtu7cRX5sf9b/6yWv+sZfw8NvOtl8Yu8J/W/Fw9rVr8SMbPoz7RvK9JOY8qTun7zMPz9lrf5vrqnNaXk3Ier4n1ZMtr9UdnF2aoF7HHKv6gr5v3ingwTj93u3rFOvqOz5ON55eT4MoJ4nAPOPswPsQvsxvQ87HmmaOury6bPDV+nrN40hxPmeK6d8KfNDz6Y/F/Gv72B72e4XpXmf/YuF6fiEb7vrQTe58lXqfj8fKDYnqrjp9v/az8/0LxfjT+1F7d9UF1ijf9/bB62r/xaXbbux6cHhS9XjRPPMIH8i+IxvK95r1VP3kBnOnnHPdk9vadPGiAvLm9usCR9NeNvzbHF85XJ5HvVN1DT7NcV35fpB5Y0VzeMz0a144x7wLPD3JeshTPLjrfdUfqb/3GP9RHOz8e16HFNflpyZfykmHut1NcFsfyW7svHM+W3/aWF47abP/Zd8lfxP2Z+vz2r/Lf6kbnsvdh+PmlcOMSfZ438Yj4+0/Hy+8L2S195n3GHuXjneULE9KicVxLODDNPsrT6zwf5z3wxvN3sjPgY4k49zl/PQZv7WD/zoADeHnOIPk1ext2Er50nb5RHryulF/BhwL52vJ94lJKvB7j8+nOvXyNB6s/zznVPnaDC0vp9zbxv5Tf3mD/3zffa1PObcH7VnBoN350Fv/8QN5whfM4e/HWI/hXI/x0v/c9yE9Hyz/t96TL5VuD4vOS7GcMnLiXXe0VnwbG+KEf8KFzL1l4lLiT9xB8fQauiiutS+H5efpcDfj9T/H5HLzzMfFxujz+8qTni9vnh6OxtI56WR58OYV/ONe0dL7r7+K/94nH7Y234zOXyLfxu/XN8Aw8edIn7LeVOHUBfjoPjp2lTpLNrmtcRx7YAA8Z/E95V5wv2Le9Nfjg5fyvQL3yfP552Ovnsdc++G5Dduqc8G5xcepH5nsEnJqQVMdWRzwGP17E7+BS09rq3epWuZUJfQt2MVLcty+p1fReJm6V0/MofEtdsawvfZTB2/n6Qn3472vwfYb/j89ZLkhEf2ezw0Pyv1fxVzjXuAJe9RD3V7muPGnwefCwP71WyavHy0vvwf9e4qcD6DU+h942Fc2/Kf+Gq53ZcQP7t/pz+dEZ4vnVeFV1Er6Ld/KmBfqcWW3ZaRu4+gj8x4Ny2VH5RfbvbLyb301vgwcXwpVsPGshviOP2c0e5mSwx9rm5RzrnJvg+QPqSF/jYVXw9gQ48Cr8WIv3v40PzOVXP+ODe/HIHQm/c8LO8KTcO10Pfk+oUodo5X7W0b0b/18hPqi7NNfXzpT35utLFrVjD7nwYRU/HI5HfSJPS1nHQvfpqe7UyznWb9LMA2+4X1+U/pvKX5vfa2yJl6gX5TyqL7lLPOOvS5eL57vlG63lnf/iN7vUOZ9mv6/aj5ejMblDH3ome+zn78/Vnf8ivy3n584N5l6g7js7fn5nOv6uHpmAM1+y47wM388xX3i5tKl495U=
*/