// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_PRINTF_HPP
#define BOOST_CONVERT_PRINTF_HPP

#include <boost/convert/base.hpp>
#include <boost/make_default.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/find.hpp>
#include <boost/range/as_literal.hpp>
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