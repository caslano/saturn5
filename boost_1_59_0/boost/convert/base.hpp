// Copyright (c) 2009-2020 Vladimir Batov.
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. See http://www.boost.org/LICENSE_1_0.txt.

#ifndef BOOST_CONVERT_BASE_HPP
#define BOOST_CONVERT_BASE_HPP

#include <boost/convert/parameters.hpp>
#include <boost/convert/detail/is_string.hpp>
#include <algorithm>
#include <cstring>

namespace boost { namespace cnv
{
    template<typename> struct cnvbase;
}}

#define BOOST_CNV_TO_STRING                                                 \
    template<typename string_type>                                          \
    typename std::enable_if<cnv::is_string<string_type>::value, void>::type \
    operator()

#define BOOST_CNV_STRING_TO                                                 \
    template<typename string_type>                                          \
    typename std::enable_if<cnv::is_string<string_type>::value, void>::type \
    operator()

#define BOOST_CNV_PARAM_SET(param_name)   \
    template <typename argument_pack>     \
    void set_(                            \
        argument_pack const& arg,         \
        cnv::parameter::type::param_name, \
        mpl::true_)

#define BOOST_CNV_PARAM_TRY(param_name)     \
    this->set_(                             \
        arg,                                \
        cnv::parameter::type::param_name(), \
        typename mpl::has_key<              \
            argument_pack, cnv::parameter::type::param_name>::type());

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

    template<typename argument_pack>
    derived_type& operator()(argument_pack const& arg)
    {
        BOOST_CNV_PARAM_TRY(base);
        BOOST_CNV_PARAM_TRY(adjust);
        BOOST_CNV_PARAM_TRY(precision);
        BOOST_CNV_PARAM_TRY(uppercase);
        BOOST_CNV_PARAM_TRY(skipws);
        BOOST_CNV_PARAM_TRY(width);
        BOOST_CNV_PARAM_TRY(fill);
//      BOOST_CNV_PARAM_TRY(locale);

        return this->dncast();
    }

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

    template<typename argument_pack, typename keyword_tag>
    void set_(argument_pack const&, keyword_tag, mpl::false_) {}

    // Formatters
    BOOST_CNV_PARAM_SET(base)      { base_      = arg[cnv::parameter::     base]; }
    BOOST_CNV_PARAM_SET(adjust)    { adjust_    = arg[cnv::parameter::   adjust]; }
    BOOST_CNV_PARAM_SET(precision) { precision_ = arg[cnv::parameter::precision]; }
    BOOST_CNV_PARAM_SET(uppercase) { uppercase_ = arg[cnv::parameter::uppercase]; }
    BOOST_CNV_PARAM_SET(skipws)    { skipws_    = arg[cnv::parameter::   skipws]; }
    BOOST_CNV_PARAM_SET(width)     { width_     = arg[cnv::parameter::    width]; }
    BOOST_CNV_PARAM_SET(fill)      { fill_      = arg[cnv::parameter::     fill]; }
//  BOOST_CNV_PARAM_SET(locale)    { locale_    = arg[cnv::parameter::   locale]; }

    // ULONG_MAX(8 bytes) = 18446744073709551615 (20(10) or 32(2) characters)
    // double (8 bytes) max is 316 chars
    static int BOOST_CONSTEXPR_OR_CONST bufsize_ = 512;

    bool        skipws_;
    int      precision_;
    bool     uppercase_;
    int          width_;
    int           fill_;
    cnv::base     base_;
    cnv::adjust adjust_;
//  std::locale locale_;
};

#undef BOOST_CNV_TO_STRING
#undef BOOST_CNV_STRING_TO
#undef BOOST_CNV_PARAM_SET
#undef BOOST_CNV_PARAM_TRY

#endif // BOOST_CONVERT_BASE_HPP

/* base.hpp
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
*/