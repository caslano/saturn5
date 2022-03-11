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