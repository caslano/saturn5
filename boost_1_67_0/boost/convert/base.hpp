// Copyright (c) 2009-2016 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_CONVERTER_BASE_HPP
#define BOOST_CONVERT_CONVERTER_BASE_HPP

#include <boost/convert/parameters.hpp>
#include <boost/convert/detail/is_string.hpp>
#include <cstring>

namespace boost { namespace cnv
{
    namespace ARG = boost::cnv::parameter;

    template<typename> struct cnvbase;
}}

#define BOOST_CNV_TO_STRING                                             \
    template<typename string_type>                                      \
    typename boost::enable_if<cnv::is_string<string_type>, void>::type  \
    operator()

#define BOOST_CNV_STRING_TO                                             \
    template<typename string_type>                                      \
    typename boost::enable_if<cnv::is_string<string_type>, void>::type  \
    operator()

#define BOOST_CNV_PARAM(param_name, param_type)                         \
    derived_type& operator()(boost::parameter::aux::tag<ARG::type::param_name, param_type const>::type const& arg)

template<typename derived_type>
struct boost::cnv::cnvbase
{
    using   this_type = cnvbase;
    using    int_type = int;
    using   uint_type = unsigned int;
    using   lint_type = long int;
    using  ulint_type = unsigned long int;
    using   sint_type = short int;
    using  usint_type = unsigned short int;
    using  llint_type = long long int;
    using ullint_type = unsigned long long int;
    using    flt_type = float;
    using    dbl_type = double;
    using   ldbl_type = long double;

    // Integration of user-types via operator>>()
    template<typename type_in, typename type_out>
    void
    operator()(type_in const& in, boost::optional<type_out>& out) const
    {
        in >> out;
    }

    // Basic type to string
    BOOST_CNV_TO_STRING (   int_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING (  uint_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING (  lint_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING ( llint_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING ( ulint_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING (ullint_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING (  sint_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING ( usint_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING (   flt_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING (   dbl_type v, optional<string_type>& r) const { to_str_(v, r); }
    BOOST_CNV_TO_STRING (  ldbl_type v, optional<string_type>& r) const { to_str_(v, r); }
    // String to basic type
    BOOST_CNV_STRING_TO (string_type const& s, optional<   int_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional<  uint_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional<  lint_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional< llint_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional< ulint_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional<ullint_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional<  sint_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional< usint_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional<   flt_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional<   dbl_type>& r) const { str_to_(s, r); }
    BOOST_CNV_STRING_TO (string_type const& s, optional<  ldbl_type>& r) const { str_to_(s, r); }
    // Formatters
//  BOOST_CNV_PARAM (locale, std::locale) { locale_    = arg[ARG::   locale]; return dncast(); }
    BOOST_CNV_PARAM (base,     cnv::base) { base_      = arg[ARG::     base]; return dncast(); }
    BOOST_CNV_PARAM (adjust, cnv::adjust) { adjust_    = arg[ARG::   adjust]; return dncast(); }
    BOOST_CNV_PARAM (precision,      int) { precision_ = arg[ARG::precision]; return dncast(); }
    BOOST_CNV_PARAM (uppercase,     bool) { uppercase_ = arg[ARG::uppercase]; return dncast(); }
    BOOST_CNV_PARAM (skipws,        bool) { skipws_    = arg[ARG::   skipws]; return dncast(); }
    BOOST_CNV_PARAM (width,          int) { width_     = arg[ARG::    width]; return dncast(); }
    BOOST_CNV_PARAM (fill,          char) {  fill_     = arg[ARG::     fill]; return dncast(); }

    protected:

    cnvbase()
    :
        skipws_     (false),
        precision_  (0),
        uppercase_  (false),
        width_      (0),
        fill_       (' '),
        base_       (boost::cnv::base::dec),
        adjust_     (boost::cnv::adjust::right)
    {}

    template<typename string_type, typename out_type>
    void
    str_to_(string_type const& str, optional<out_type>& result_out) const
    {
        cnv::range<string_type const> range (str);

        if (skipws_)
            for (; !range.empty() && cnv::is_space(*range.begin()); ++range);

        if (range.empty())                 return;
        if (cnv::is_space(*range.begin())) return;

        dncast().str_to(range, result_out);
    }
    template<typename in_type, typename string_type>
    void
    to_str_(in_type value_in, optional<string_type>& result_out) const
    {
        using  char_type = typename cnv::range<string_type>::value_type;
        using range_type = cnv::range<char_type*>;
        using   buf_type = char_type[bufsize_];

        buf_type     buf;
        range_type range = dncast().to_str(value_in, buf);
        char_type*   beg = range.begin();
        char_type*   end = range.end();
        int     str_size = end - beg;

        if (str_size <= 0)
            return;

        if (uppercase_)
            for (char_type* p = beg; p < end; ++p) *p = cnv::to_upper(*p);

        if (width_)
        {
            int  num_fill = (std::max)(0, int(width_ - (end - beg)));
            int  num_left = adjust_ == cnv::adjust::left ? 0
                          : adjust_ == cnv::adjust::right ? num_fill
                          : (num_fill / 2);
            int num_right = num_fill - num_left;
            bool     move = (beg < buf + num_left) // No room for left fillers
                         || (buf + bufsize_ < end + num_right); // No room for right fillers
            if (move)
            {
                std::memmove(buf + num_left, beg, str_size * sizeof(char_type));
                beg = buf + num_left;
                end = beg + str_size;
            }
            for (int k = 0; k <  num_left; *(--beg) = fill_, ++k);
            for (int k = 0; k < num_right; *(end++) = fill_, ++k);
        }
        result_out = string_type(beg, end);
    }

    derived_type const& dncast () const { return *static_cast<derived_type const*>(this); }
    derived_type&       dncast ()       { return *static_cast<derived_type*>(this); }

    // ULONG_MAX(8 bytes) = 18446744073709551615 (20(10) or 32(2) characters)
    // double (8 bytes) max is 316 chars
    static int const bufsize_ = 512;
    bool              skipws_;
    int            precision_;
    bool           uppercase_;
    int                width_;
    int                 fill_;
    cnv::base           base_;
    cnv::adjust       adjust_;
//  std::locale       locale_;
};

#undef BOOST_CNV_TO_STRING
#undef BOOST_CNV_STRING_TO
#undef BOOST_CNV_PARAM

#endif // BOOST_CONVERT_CONVERTER_BASE_HPP

/* base.hpp
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
*/