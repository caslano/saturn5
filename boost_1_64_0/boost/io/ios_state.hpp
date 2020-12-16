/*
Copyright 2002, 2005 Daryle Walker

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_IO_IOS_STATE_HPP
#define BOOST_IO_IOS_STATE_HPP

#include <boost/config.hpp>
#include <boost/io_fwd.hpp>
#include <ios>
#ifndef BOOST_NO_STD_LOCALE
#include <locale>
#endif
#include <ostream>
#include <streambuf>
#include <string>

namespace boost {
namespace io {

class ios_flags_saver {
public:
    typedef std::ios_base state_type;
    typedef std::ios_base::fmtflags aspect_type;

    explicit ios_flags_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.flags()) { }

    ios_flags_saver(state_type& s, aspect_type a)
        : s_save_(s)
        , a_save_(s.flags(a)) { }

    ~ios_flags_saver() {
        this->restore();
    }

    void restore() {
        s_save_.flags(a_save_);
    }

private:
    ios_flags_saver(const ios_flags_saver&);
    ios_flags_saver& operator=(const ios_flags_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};

class ios_precision_saver {
public:
    typedef std::ios_base state_type;
    typedef std::streamsize aspect_type;

    explicit ios_precision_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.precision()) { }

    ios_precision_saver(state_type& s, aspect_type a)
        : s_save_(s)
        , a_save_(s.precision(a)) { }

    ~ios_precision_saver() {
        this->restore();
    }

    void restore() {
        s_save_.precision(a_save_);
    }

private:
    ios_precision_saver(const ios_precision_saver&);
    ios_precision_saver& operator=(const ios_precision_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};

class ios_width_saver {
public:
    typedef std::ios_base state_type;
    typedef std::streamsize aspect_type;

    explicit ios_width_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.width()) { }

    ios_width_saver(state_type& s, aspect_type a)
        : s_save_(s)
        , a_save_(s.width(a)) { }

    ~ios_width_saver() {
        this->restore();
    }

    void restore() {
        s_save_.width(a_save_);
    }

private:
    ios_width_saver(const ios_width_saver&);
    ios_width_saver& operator=(const ios_width_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};

template<class Ch, class Tr>
class basic_ios_iostate_saver {
public:
    typedef std::basic_ios<Ch, Tr> state_type;
    typedef std::ios_base::iostate aspect_type;

    explicit basic_ios_iostate_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.rdstate()) { }

    basic_ios_iostate_saver(state_type& s, aspect_type a)
        : s_save_(s)
        , a_save_(s.rdstate()) {
            s.clear(a);
        }

    ~basic_ios_iostate_saver() {
        this->restore();
    }

    void restore() {
        s_save_.clear(a_save_);
    }

private:
    basic_ios_iostate_saver(const basic_ios_iostate_saver&);
    basic_ios_iostate_saver& operator=(const basic_ios_iostate_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};

template<class Ch, class Tr>
class basic_ios_exception_saver {
public:
    typedef std::basic_ios<Ch, Tr> state_type;
    typedef std::ios_base::iostate aspect_type;

    explicit basic_ios_exception_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.exceptions()) { }

    basic_ios_exception_saver(state_type& s, aspect_type a)
        : s_save_(s)
        , a_save_(s.exceptions()) {
        s.exceptions(a);
    }

    ~basic_ios_exception_saver() {
        this->restore();
    }

    void restore() {
        s_save_.exceptions(a_save_);
    }

private:
    basic_ios_exception_saver(const basic_ios_exception_saver&);
    basic_ios_exception_saver& operator=(const basic_ios_exception_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};

template<class Ch, class Tr>
class basic_ios_tie_saver {
public:
    typedef std::basic_ios<Ch, Tr> state_type;
    typedef std::basic_ostream<Ch, Tr>* aspect_type;

    explicit basic_ios_tie_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.tie()) { }

    basic_ios_tie_saver(state_type& s, aspect_type a)
        : s_save_(s)
        , a_save_(s.tie(a)) { }

    ~basic_ios_tie_saver() {
        this->restore();
    }

    void restore() {
        s_save_.tie(a_save_);
    }

private:
    basic_ios_tie_saver(const basic_ios_tie_saver&);
    basic_ios_tie_saver& operator=(const basic_ios_tie_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};

template<class Ch, class Tr>
class basic_ios_rdbuf_saver {
public:
    typedef std::basic_ios<Ch, Tr> state_type;
    typedef std::basic_streambuf<Ch, Tr>* aspect_type;

    explicit basic_ios_rdbuf_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.rdbuf()) { }

    basic_ios_rdbuf_saver(state_type& s, aspect_type a)
        : s_save_(s)
        , a_save_(s.rdbuf(a)) { }

    ~basic_ios_rdbuf_saver() {
        this->restore();
    }

    void restore() {
        s_save_.rdbuf(a_save_);
    }

private:
    basic_ios_rdbuf_saver(const basic_ios_rdbuf_saver&);
    basic_ios_rdbuf_saver& operator=(const basic_ios_rdbuf_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};

template<class Ch, class Tr>
class basic_ios_fill_saver {
public:
    typedef std::basic_ios<Ch, Tr> state_type;
    typedef typename state_type::char_type aspect_type;

    explicit basic_ios_fill_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.fill()) { }

    basic_ios_fill_saver(state_type& s, aspect_type a)
        : s_save_(s)
        , a_save_(s.fill(a)) { }

    ~basic_ios_fill_saver() {
        this->restore();
    }

    void restore() {
        s_save_.fill(a_save_);
    }

private:
    basic_ios_fill_saver(const basic_ios_fill_saver&);
    basic_ios_fill_saver& operator=(const basic_ios_fill_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};

#ifndef BOOST_NO_STD_LOCALE
template<class Ch, class Tr>
class basic_ios_locale_saver {
public:
    typedef std::basic_ios<Ch, Tr> state_type;
    typedef std::locale aspect_type;

    explicit basic_ios_locale_saver(state_type& s)
        : s_save_(s)
        , a_save_(s.getloc()) { }

    basic_ios_locale_saver(state_type& s, const aspect_type& a)
        : s_save_(s)
        , a_save_(s.imbue(a)) { }

    ~basic_ios_locale_saver() {
        this->restore();
    }

    void restore() {
        s_save_.imbue(a_save_);
    }

private:
    basic_ios_locale_saver(const basic_ios_locale_saver&);
    basic_ios_locale_saver& operator=(const basic_ios_locale_saver&);

    state_type& s_save_;
    aspect_type a_save_;
};
#endif

class ios_iword_saver {
public:
    typedef std::ios_base state_type;
    typedef int index_type;
    typedef long aspect_type;

    explicit ios_iword_saver(state_type& s, index_type i)
        : s_save_(s)
        , a_save_(s.iword(i))
        , i_save_(i) { }

    ios_iword_saver(state_type& s, index_type i, aspect_type a)
        : s_save_(s)
        , a_save_(s.iword(i))
        , i_save_(i) {
        s.iword(i) = a;
    }

    ~ios_iword_saver() {
        this->restore();
    }

    void restore() {
        s_save_.iword(i_save_) = a_save_;
    }

private:
    ios_iword_saver(const ios_iword_saver&);
    ios_iword_saver& operator=(const ios_iword_saver&);

    state_type& s_save_;
    aspect_type a_save_;
    index_type i_save_;
};

class ios_pword_saver {
public:
    typedef std::ios_base state_type;
    typedef int index_type;
    typedef void* aspect_type;

    explicit ios_pword_saver(state_type& s, index_type i)
        : s_save_(s)
        , a_save_(s.pword(i))
        , i_save_(i) { }

    ios_pword_saver(state_type& s, index_type i, aspect_type a)
        : s_save_(s)
        , a_save_(s.pword(i))
        , i_save_(i) {
        s.pword(i) = a;
    }

    ~ios_pword_saver() {
        this->restore();
    }

    void restore() {
        s_save_.pword(i_save_) = a_save_;
    }

private:
    ios_pword_saver(const ios_pword_saver&);
    ios_pword_saver operator=(const ios_pword_saver&);

    state_type& s_save_;
    aspect_type a_save_;
    index_type i_save_;
};

class ios_base_all_saver {
public:
    typedef std::ios_base state_type;

    explicit ios_base_all_saver(state_type& s)
        : s_save_(s)
        , a1_save_(s.flags())
        , a2_save_(s.precision())
        , a3_save_(s.width()) { }

    ~ios_base_all_saver() {
        this->restore();
    }

    void restore() {
        s_save_.width(a3_save_);
        s_save_.precision(a2_save_);
        s_save_.flags(a1_save_);
    }

private:
    ios_base_all_saver(const ios_base_all_saver&);
    ios_base_all_saver& operator=(const ios_base_all_saver&);

    state_type& s_save_;
    state_type::fmtflags a1_save_;
    std::streamsize a2_save_;
    std::streamsize a3_save_;
};

template<class Ch, class Tr>
class basic_ios_all_saver {
public:
    typedef std::basic_ios<Ch, Tr> state_type;

    explicit basic_ios_all_saver(state_type& s)
        : s_save_(s)
        , a1_save_(s.flags())
        , a2_save_(s.precision())
        , a3_save_(s.width())
        , a4_save_(s.rdstate())
        , a5_save_(s.exceptions())
        , a6_save_(s.tie())
        , a7_save_(s.rdbuf())
        , a8_save_(s.fill())
#ifndef BOOST_NO_STD_LOCALE
        , a9_save_(s.getloc())
#endif
        { }

    ~basic_ios_all_saver() {
        this->restore();
    }

    void restore() {
#ifndef BOOST_NO_STD_LOCALE
        s_save_.imbue(a9_save_);
#endif
        s_save_.fill(a8_save_);
        s_save_.rdbuf(a7_save_);
        s_save_.tie(a6_save_);
        s_save_.exceptions(a5_save_);
        s_save_.clear(a4_save_);
        s_save_.width(a3_save_);
        s_save_.precision(a2_save_);
        s_save_.flags(a1_save_);
    }

private:
    basic_ios_all_saver(const basic_ios_all_saver&);
    basic_ios_all_saver& operator=(const basic_ios_all_saver&);

    state_type& s_save_;
    typename state_type::fmtflags a1_save_;
    std::streamsize a2_save_;
    std::streamsize a3_save_;
    typename state_type::iostate a4_save_;
    typename state_type::iostate a5_save_;
    std::basic_ostream<Ch, Tr>* a6_save_;
    std::basic_streambuf<Ch, Tr>* a7_save_;
    typename state_type::char_type a8_save_;
#ifndef BOOST_NO_STD_LOCALE
    std::locale a9_save_;
#endif
};

class ios_all_word_saver {
public:
    typedef std::ios_base state_type;
    typedef int index_type;

    ios_all_word_saver(state_type& s, index_type i)
        : s_save_(s)
        , i_save_(i)
        , a1_save_(s.iword(i))
        , a2_save_(s.pword(i)) { }

    ~ios_all_word_saver() {
        this->restore();
    }

    void restore() {
        s_save_.pword(i_save_) = a2_save_;
        s_save_.iword(i_save_) = a1_save_;
    }

private:
    ios_all_word_saver(const ios_all_word_saver&);
    ios_all_word_saver& operator=(const ios_all_word_saver&);

    state_type& s_save_;
    index_type i_save_;
    long a1_save_;
    void* a2_save_;
};

} /* io */
} /* boost */

#endif

/* ios_state.hpp
J88FurBP23Nv4ziHQM83GfnKsdMWdLbKNxJ8jRb5xDwuSb4C9RyQIPmWJ4QqX0HAPJUGytdVmnd1AjrXWuUr8Wptz6fwoB6/QP0cEvVYugabgYuEsk1G8NEmjgl7gaaizlqsZWIenWbqusKFrvL6gsZoq+33opz4D1hOsMMKD/H7SE97H0H69vtIT/qILGdVF6ucD0DOdDs5hadQTntfQfr2+0pP+krAnOMual+pblbLiYp37S9bFP5irlnravWXabBPlp19hNeE7jdns7zobtb6eBDllbO84M4JbiPq4koHnykPw2euVPjMboWMd4Kv2kZGugzltPeZ6jB85kqFzwyNUftMnVpO1L37Pib+cavPsA6x17nVZzJRhw025cJl2u0vuYzt+BIoCvQiaD1s0eQvK+vcmTln5SHKk3SVFnPaHkZqzGlbs6q4zFxH9rZIsxp2PEVbjm9xKA62ZV69pLriMfx5kNdZQhJvpRdTCpfrAaUqTq7BrvlQ5+sv6v592B7eaOb7gcjjKS2R8ujhztYVl+LGqchcO5Qt0hdpM4Q8OAb8XKQbqPVHurmBZa+vKCgv18tPZPllIv0off6mWHu0DXXT3B0+7NHjrvrqYxNiTdtfnRAY02cKY8l09Qjkb/dzPnWdkmljw09hAxwrD7gmHethbU8voA5bhOw++SbMvI9YaN/eka797X2h4j5iW0+rfIfBF/83i3y8j6B86naOdO1v5wsV9xExsep2Ht8cLF9o9xG7H7W/jyiPtbbxRfp102KT9t1HGO07qZfV9kdggyyWE3iDD/dgP5tk7x9I237/SKJ/yDLWK2R8GXzlKhmFi1BGBx8pD8NHkhTXgvQ4pY+gM1DJiNoOwU8a9ttfC7bHWf3kIX09s9I2cJV23DuMZ1mTelvrYR/KqmNZ4kFP8pGxTs8iYfjIWPqILNthhWxDIVujLJvkG2OdnkPC8I2x9A15/ceseLVvtMiyhegTryl8wrDFrnirTzycpqFAqbwwfWFWgtXej6CMVJbBB2rzerLE3heQpv2+sEThC00K2YZBtoxA2XgtoWxqX0Ca9vvCEoUvZCWqfSE/QLbQriOzHrP3hT2JVl84DbYoDygvvGvIkj6KcQroXs0yAgZnpP5hloNPVIfhE7MU15BWhYx7wFenklHqJ2Y5+EZdGL4xS3EN8SapfSO1WSFjiP3FuwfsryFNSVYfGaT3nSrbtLPf4H0NJupZ6+G3KKuFZUmDfWbfMdvpXjQMP5mtuBdN9Vjluxx88R9Z5GP/QfnUPoJ0IfnI/AD5FPei2zxqH0m3yBdaH1J9wP5etNVj9Y8svT+1lNm+fsQoZ2AK50WToR9oP8rJ95dTNL4kTxo/8/tGQ5qd7ZmOa6yaxRp3xOdTrbEK4kXd41tpcZldLOigOr3ahZ5GnUJeUafGOixdrmTKhWMsC8dYvjwuMquf1T6PIT+fZJ/g8SJjXORRBzv5QrCTLwQ7+cKw06PtsJPRn63sb7XTRrSlWslOQWMkwkZXO7Tj2hBsVBuCjWrDsNHVQ0K3kdHWtgwIshFjIzWctJH0jOn3occdfKghBPs0hGCfhjDs83gYPrR7oNU+TyO/Jtk+8rMV29mTDjZqCsFGTSHYqCkMGz3ZDhsZ/dG2U8y4M6atnkF+2lEbG+UtK1mD09zrBjzLytVr3JkH/iSbKuxEPkn3P7u4/idSd12GZMoQR/1pjwA9Nwyy6vl78KXb6rm8XKOeuLcCj/itfo/hUs/0ID3fDEFPyACdliv1lJ8Vak61+vxz4MsP0BPPjvT14fa+jjTufT3/qHtfzz/afl8f3g5fN/rLqlSrD4xEfr5g24Tg4yIt/iRbqq+5Hew=
*/