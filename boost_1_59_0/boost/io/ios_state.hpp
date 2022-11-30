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
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
*/