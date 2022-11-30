// Copyright (c) 2009-2020 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_PRINTF_HPP
#define BOOST_CONVERT_PRINTF_HPP

#include <boost/convert/base.hpp>
#include <boost/make_default.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <string>
#include <cstdio>

namespace boost { namespace cnv
{
    struct printf;
}}

struct boost::cnv::printf : boost::cnv::cnvbase<boost::cnv::printf>
{
    using this_type = boost::cnv::printf;
    using base_type = boost::cnv::cnvbase<this_type>;

    using base_type::operator();

    template<typename in_type>
    cnv::range<char*>
    to_str(in_type value_in, char* buf) const
    {
        char const*     fmt = pformat(pos<in_type>());
        int const num_chars = snprintf(buf, bufsize_, fmt, precision_, value_in);
        bool const  success = num_chars < bufsize_;

        return cnv::range<char*>(buf, success ? (buf + num_chars) : buf);
    }
    template<typename string_type, typename out_type>
    void
    str_to(cnv::range<string_type> range, optional<out_type>& result_out) const
    {
        out_type    result = boost::make_default<out_type>();
        int const num_read = sscanf(&*range.begin(), format(pos<out_type>()), &result);

        if (num_read == 1)
            result_out = result;
    }

    private:

    template<typename Type> int pos() const
    {
        using managed_types = boost::mpl::vector<double, float,
                                  int, unsigned int,
                                  short int, unsigned short int,
                                  long int, unsigned long int>;
        using type_iterator = typename boost::mpl::find<managed_types, Type>::type;
        using      type_pos = typename type_iterator::pos;

        return type_pos::value;
    }

    char const* pformat(int pos) const
    {
        static char const* d_fmt[] = { "%.*f", "%.*f", "%.*d", "%.*u", "%.*hd", "%.*hu", "%.*ld", "%.*lu" }; // Must match managed_types
        static char const* x_fmt[] = { "%.*f", "%.*f", "%.*x", "%.*x", "%.*hx", "%.*hx", "%.*lx", "%.*lx" }; // Must match managed_types
        static char const* o_fmt[] = { "%.*f", "%.*f", "%.*o", "%.*o", "%.*ho", "%.*ho", "%.*lo", "%.*lo" }; // Must match managed_types
        char const*            fmt = base_ == boost::cnv::base::dec ? d_fmt[pos]
                                   : base_ == boost::cnv::base::hex ? x_fmt[pos]
                                   : base_ == boost::cnv::base::oct ? o_fmt[pos]
                                   : (BOOST_ASSERT(0), nullptr);
        return fmt;
    }
    char const* format(int pos) const
    {
        static char const* d_fmt[] = { "%f", "%f", "%d", "%u", "%hd", "%hu", "%ld", "%lu" }; // Must match managed_types
        static char const* x_fmt[] = { "%f", "%f", "%x", "%x", "%hx", "%hx", "%lx", "%lx" }; // Must match managed_types
        static char const* o_fmt[] = { "%f", "%f", "%o", "%o", "%ho", "%ho", "%lo", "%lo" }; // Must match managed_types
        char const*            fmt = base_ == boost::cnv::base::dec ? d_fmt[pos]
                                   : base_ == boost::cnv::base::hex ? x_fmt[pos]
                                   : base_ == boost::cnv::base::oct ? o_fmt[pos]
                                   : (BOOST_ASSERT(0), nullptr);
        return fmt;
    }
};

#endif // BOOST_CONVERT_PRINTF_HPP

/* printf.hpp
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
*/