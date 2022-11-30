/*=============================================================================
    Copyright (c) 2002 Juan Carlos Arevalo-Baeza
    Copyright (c) 2002-2006 Hartmut Kaiser
    Copyright (c) 2003 Giovanni Bajo
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_POSITION_ITERATOR_HPP
#define BOOST_SPIRIT_POSITION_ITERATOR_HPP

#include <string>
#include <boost/config.hpp>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/iterator/position_iterator_fwd.hpp>

namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  file_position_without_column
//
//  A structure to hold positional information. This includes the file,
//  and the line number
//
///////////////////////////////////////////////////////////////////////////////
template <typename String>
struct file_position_without_column_base {
    String file;
    int line;

    file_position_without_column_base(String const& file_ = String(),
                  int line_ = 1):
        file    (file_),
        line    (line_)
    {}

    bool operator==(const file_position_without_column_base& fp) const
    { return line == fp.line && file == fp.file; }
};

///////////////////////////////////////////////////////////////////////////////
//
//  file_position
//
//  This structure holds complete file position, including file name,
//  line and column number
//
///////////////////////////////////////////////////////////////////////////////
template <typename String>
struct file_position_base : public file_position_without_column_base<String> {
    int column;

    file_position_base(String const& file_ = String(),
                       int line_ = 1, int column_ = 1):
        file_position_without_column_base<String> (file_, line_),
        column                       (column_)
    {}

    bool operator==(const file_position_base& fp) const
    { return column == fp.column && this->line == fp.line && this->file == fp.file; }
};

///////////////////////////////////////////////////////////////////////////////
//
//  position_policy<>
//
//  This template is the policy to handle the file position. It is specialized
//  on the position type. Providing a custom file_position also requires
//  providing a specialization of this class.
//
//  Policy interface:
//
//    Default constructor of the custom position class must be accessible.
//    set_tab_chars(unsigned int chars) - Set the tabstop width
//    next_char(PositionT& pos)  - Notify that a new character has been
//      processed
//    tabulation(PositionT& pos) - Notify that a tab character has been
//      processed
//    next_line(PositionT& pos)  - Notify that a new line delimiter has
//      been reached.
//
///////////////////////////////////////////////////////////////////////////////
template <typename PositionT> class position_policy;

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} /* namespace BOOST_SPIRIT_CLASSIC_NS */


// This must be included here for full compatibility with old MSVC
#include <boost/spirit/home/classic/iterator/impl/position_iterator.ipp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
//
//  position_iterator
//
//  It wraps an iterator, and keeps track of the current position in the input,
//  as it gets incremented.
//
//  The wrapped iterator must be at least a Forward iterator. The position
//  iterator itself will always be a non-mutable Forward iterator.
//
//  In order to have begin/end iterators constructed, the end iterator must be
//  empty constructed. Similar to what happens with stream iterators. The begin
//  iterator must be constructed from both, the begin and end iterators of the
//  wrapped iterator type. This is necessary to implement the lookahead of
//  characters necessary to parse CRLF sequences.
//
//  In order to extract the current positional data from the iterator, you may
//  use the get_position member function.
//
//  You can also use the set_position member function to reset the current
//  position to something new.
//
//  The structure that holds the current position can be customized through a
//  template parameter, and the class position_policy must be specialized
//  on the new type to define how to handle it. Currently, it's possible
//  to choose between the file_position and file_position_without_column
//  (which saves some overhead if managing current column is not required).
//
///////////////////////////////////////////////////////////////////////////////

#if !defined(BOOST_ITERATOR_ADAPTORS_VERSION) || \
     BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200
#error "Please use at least Boost V1.31.0 while compiling the position_iterator class!"
#else // BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200

///////////////////////////////////////////////////////////////////////////////
//
//  Uses the newer iterator_adaptor version (should be released with
//  Boost V1.31.0)
//
///////////////////////////////////////////////////////////////////////////////
template <
    typename ForwardIteratorT,
    typename PositionT,
    typename SelfT
>
class position_iterator
:   public iterator_::impl::position_iterator_base_generator<
        SelfT,
        ForwardIteratorT,
        PositionT
    >::type,
    public position_policy<PositionT>
{
private:

    typedef position_policy<PositionT> position_policy_t;
    typedef typename iterator_::impl::position_iterator_base_generator<
            SelfT,
            ForwardIteratorT,
            PositionT
        >::type base_t;
    typedef typename iterator_::impl::position_iterator_base_generator<
            SelfT,
            ForwardIteratorT,
            PositionT
        >::main_iter_t main_iter_t;

public:

    typedef PositionT position_t;

    position_iterator()
    :   _isend(true)
    {}

    position_iterator(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end)
    :   base_t(begin), _end(end), _pos(PositionT()), _isend(begin == end)
    {}

    template <typename FileNameT>
    position_iterator(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end,
        FileNameT fileName)
    :   base_t(begin), _end(end), _pos(PositionT(fileName)),
        _isend(begin == end)
    {}

    template <typename FileNameT, typename LineT>
    position_iterator(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end,
        FileNameT fileName, LineT line)
    :   base_t(begin), _end(end), _pos(PositionT(fileName, line)),
        _isend(begin == end)
    {}

    template <typename FileNameT, typename LineT, typename ColumnT>
    position_iterator(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end,
        FileNameT fileName, LineT line, ColumnT column)
    :   base_t(begin), _end(end), _pos(PositionT(fileName, line, column)),
        _isend(begin == end)
    {}

    position_iterator(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end,
        const PositionT& pos)
    :   base_t(begin), _end(end), _pos(pos), _isend(begin == end)
    {}

    position_iterator(const position_iterator& iter)
    :   base_t(iter.base()), position_policy_t(iter),
        _end(iter._end), _pos(iter._pos), _isend(iter._isend)
    {}

    position_iterator& operator=(const position_iterator& iter)
    {
        base_t::operator=(iter);
        position_policy_t::operator=(iter);
        _end = iter._end;
        _pos = iter._pos;
        _isend = iter._isend;
        return *this;
    }

    void set_position(PositionT const& newpos) { _pos = newpos; }
    PositionT& get_position() { return _pos; }
    PositionT const& get_position() const { return _pos; }

    void set_tabchars(unsigned int chars)
    {
        // This function (which comes from the position_policy) has a
        //  different name on purpose, to avoid messing with using
        //  declarations or qualified calls to access the base template
        //  function, which might break some compilers.
        this->position_policy_t::set_tab_chars(chars);
    }

private:
    friend class boost::iterator_core_access;

    void increment()
    {
        typename base_t::reference val = *(this->base());
        if (val == '\n') {
            ++this->base_reference();
            this->next_line(_pos);
            static_cast<main_iter_t &>(*this).newline();
        }
        else if ( val == '\r') {
            ++this->base_reference();
            if (this->base_reference() == _end || *(this->base()) != '\n')
            {
                this->next_line(_pos);
                static_cast<main_iter_t &>(*this).newline();
            }
        }
        else if (val == '\t') {
            this->tabulation(_pos);
            ++this->base_reference();
        }
        else {
            this->next_char(_pos);
            ++this->base_reference();
        }

        // The iterator is at the end only if it's the same
        //  of the
        _isend = (this->base_reference() == _end);
    }

    template <
        typename OtherDerivedT, typename OtherIteratorT,
        typename V, typename C, typename R, typename D
    >
    bool equal(iterator_adaptor<OtherDerivedT, OtherIteratorT, V, C, R, D>
        const &x) const
    {
        OtherDerivedT const &rhs = static_cast<OtherDerivedT const &>(x);
        bool x_is_end = rhs._isend;

        return (_isend == x_is_end) && (_isend || this->base() == rhs.base());
    }

protected:

    void newline()
    {}

    ForwardIteratorT _end;
    PositionT _pos;
    bool _isend;
};

#endif // BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200

///////////////////////////////////////////////////////////////////////////////
//
//  position_iterator2
//
//  Equivalent to position_iterator, but it is able to extract the current
//  line into a string. This is very handy for error reports.
//
//  Notice that the footprint of this class is higher than position_iterator,
//  (how much depends on how bulky the underlying iterator is), so it should
//  be used only if necessary.
//
///////////////////////////////////////////////////////////////////////////////

template
<
    typename ForwardIteratorT,
    typename PositionT
>
class position_iterator2
    : public position_iterator
    <
        ForwardIteratorT,
        PositionT,
        position_iterator2<ForwardIteratorT, PositionT>
    >
{
    typedef position_iterator
    <
        ForwardIteratorT,
        PositionT,
        position_iterator2<ForwardIteratorT, PositionT> // JDG 4-15-03
    >  base_t;

public:
    typedef typename base_t::value_type value_type;
    typedef PositionT position_t;

    position_iterator2()
    {}

    position_iterator2(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end):
        base_t(begin, end),
        _startline(begin)
    {}

    template <typename FileNameT>
    position_iterator2(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end,
        FileNameT file):
        base_t(begin, end, file),
        _startline(begin)
    {}

    template <typename FileNameT, typename LineT>
    position_iterator2(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end,
        FileNameT file, LineT line):
        base_t(begin, end, file, line),
        _startline(begin)
    {}

    template <typename FileNameT, typename LineT, typename ColumnT>
    position_iterator2(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end,
        FileNameT file, LineT line, ColumnT column):
        base_t(begin, end, file, line, column),
        _startline(begin)
    {}

    position_iterator2(
        const ForwardIteratorT& begin,
        const ForwardIteratorT& end,
        const PositionT& pos):
        base_t(begin, end, pos),
        _startline(begin)
    {}

    position_iterator2(const position_iterator2& iter)
        : base_t(iter), _startline(iter._startline)
    {}

    position_iterator2& operator=(const position_iterator2& iter)
    {
        base_t::operator=(iter);
        _startline = iter._startline;
        return *this;
    }

    ForwardIteratorT get_currentline_begin() const
    { return _startline; }

    ForwardIteratorT get_currentline_end() const
    { return get_endline(); }

    std::basic_string<value_type> get_currentline() const
    {
        return std::basic_string<value_type>
            (get_currentline_begin(), get_currentline_end());
    }

protected:
    ForwardIteratorT _startline;

    friend class position_iterator<ForwardIteratorT, PositionT,
        position_iterator2<ForwardIteratorT, PositionT> >;

    ForwardIteratorT get_endline() const
    {
        ForwardIteratorT endline = _startline;
        while (endline != this->_end && *endline != '\r' && *endline != '\n')
        {
            ++endline;
        }
        return endline;
    }

    void newline()
    { _startline = this->base(); }
};

BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif

/* position_iterator.hpp
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
*/