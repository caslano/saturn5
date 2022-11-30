// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_PROCESS_PIPE_HPP
#define BOOST_PROCESS_PIPE_HPP

#include <boost/config.hpp>
#include <boost/process/detail/config.hpp>
#include <streambuf>
#include <istream>
#include <ostream>
#include <vector>

#if defined(BOOST_POSIX_API)
#include <boost/process/detail/posix/basic_pipe.hpp>
#elif defined(BOOST_WINDOWS_API)
#include <boost/process/detail/windows/basic_pipe.hpp>
#endif

namespace boost { namespace process {

using ::boost::process::detail::api::basic_pipe;

#if defined(BOOST_PROCESS_DOXYGEN)
/** Class implementation of a pipe.
 *
 */
template<class CharT, class Traits = std::char_traits<CharT>>
class basic_pipe
{
public:
    typedef CharT                      char_type  ;
    typedef          Traits            traits_type;
    typedef typename Traits::int_type  int_type   ;
    typedef typename Traits::pos_type  pos_type   ;
    typedef typename Traits::off_type  off_type   ;
    typedef ::boost::detail::winapi::HANDLE_ native_handle;

    /// Default construct the pipe. Will be opened.
    basic_pipe();

    ///Construct a named pipe.
    inline explicit basic_pipe(const std::string & name);
    /** Copy construct the pipe.
     *  \note Duplicated the handles.
     */
    inline basic_pipe(const basic_pipe& p);
    /** Move construct the pipe. */
    basic_pipe(basic_pipe&& lhs);
    /** Copy assign the pipe.
     *  \note Duplicated the handles.
     */
    inline basic_pipe& operator=(const basic_pipe& p);
    /** Move assign the pipe. */
    basic_pipe& operator=(basic_pipe&& lhs);
    /** Destructor closes the handles. */
    ~basic_pipe();
    /** Get the native handle of the source. */
    native_handle native_source() const;
    /** Get the native handle of the sink. */
    native_handle native_sink  () const;

    /** Assign a new value to the source */
    void assign_source(native_handle h);
    /** Assign a new value to the sink */
    void assign_sink  (native_handle h);


    ///Write data to the pipe.
    int_type write(const char_type * data, int_type count);
    ///Read data from the pipe.
    int_type read(char_type * data, int_type count);
    ///Check if the pipe is open.
    bool is_open();
    ///Close the pipe
    void close();
};

#endif



typedef basic_pipe<char>     pipe;
typedef basic_pipe<wchar_t> wpipe;


/** Implementation of the stream buffer for a pipe.
 */
template<
    class CharT,
    class Traits = std::char_traits<CharT>
>
struct basic_pipebuf : std::basic_streambuf<CharT, Traits>
{
    typedef basic_pipe<CharT, Traits> pipe_type;

    typedef           CharT            char_type  ;
    typedef           Traits           traits_type;
    typedef  typename Traits::int_type int_type   ;
    typedef  typename Traits::pos_type pos_type   ;
    typedef  typename Traits::off_type off_type   ;

    constexpr static int default_buffer_size = BOOST_PROCESS_PIPE_SIZE;

    ///Default constructor, will also construct the pipe.
    basic_pipebuf() : _write(default_buffer_size), _read(default_buffer_size)
    {
        this->setg(_read.data(),  _read.data()+ 128,  _read.data() + 128);
        this->setp(_write.data(), _write.data() + _write.size());
    }
    ///Copy Constructor.
    basic_pipebuf(const basic_pipebuf & ) = default;
    ///Move Constructor
    basic_pipebuf(basic_pipebuf && ) = default;

    ///Destructor -> writes the frest of the data
    ~basic_pipebuf()
    {
        if (basic_pipebuf::is_open())
            basic_pipebuf::overflow(Traits::eof());
    }

    ///Move construct from a pipe.
    basic_pipebuf(pipe_type && p) : _pipe(std::move(p)),
                                    _write(default_buffer_size),
                                    _read(default_buffer_size)
    {
        this->setg(_read.data(),  _read.data()+ 128,  _read.data() + 128);
        this->setp(_write.data(), _write.data() + _write.size());
    }
    ///Construct from a pipe.
    basic_pipebuf(const pipe_type & p) : _pipe(p),
                                        _write(default_buffer_size),
                                        _read(default_buffer_size)
    {
        this->setg(_read.data(),  _read.data()+ 128,  _read.data() + 128);
        this->setp(_write.data(), _write.data() + _write.size());
    }
    ///Copy assign.
    basic_pipebuf& operator=(const basic_pipebuf & ) = delete;
    ///Move assign.
    basic_pipebuf& operator=(basic_pipebuf && ) = default;
    ///Move assign a pipe.
    basic_pipebuf& operator=(pipe_type && p)
    {
        _pipe = std::move(p);
        return *this;
    }
    ///Copy assign a pipe.
    basic_pipebuf& operator=(const pipe_type & p)
    {
        _pipe = p;
        return *this;
    }
    ///Writes characters to the associated output sequence from the put area
    int_type overflow(int_type ch = traits_type::eof()) override
    {
        if (_pipe.is_open() && (ch != traits_type::eof()))
        {
            if (this->pptr() == this->epptr())
            {
                bool wr = this->_write_impl();
                if (wr)
                {
                    *this->pptr() = ch;
                    this->pbump(1);
                    return ch;
                }
            }
            else
            {
                *this->pptr() = ch;
                this->pbump(1);
                if (this->_write_impl())
                    return ch;
            }
        }
        else if (ch == traits_type::eof())
           this->sync();

        return traits_type::eof();
    }
    ///Synchronizes the buffers with the associated character sequence
    int sync() override { return this->_write_impl() ? 0 : -1; }

    ///Reads characters from the associated input sequence to the get area
    int_type underflow() override
    {
        if (!_pipe.is_open())
            return traits_type::eof();

        if (this->egptr() == &_read.back()) //ok, so we're at the end of the buffer
            this->setg(_read.data(),  _read.data()+ 10,  _read.data() + 10);


        auto len = &_read.back() - this->egptr() ;
        auto res = _pipe.read(
                        this->egptr(),
                        static_cast<typename pipe_type::int_type>(len));
        if (res == 0)
            return traits_type::eof();

        this->setg(this->eback(), this->gptr(), this->egptr() + res);
        auto val = *this->gptr();

        return traits_type::to_int_type(val);
    }


    ///Set the pipe of the streambuf.
    void pipe(pipe_type&& p)      {_pipe = std::move(p); }
    ///Set the pipe of the streambuf.
    void pipe(const pipe_type& p) {_pipe = p; }
    ///Get a reference to the pipe.
    pipe_type &      pipe() &       {return _pipe;}
    ///Get a const reference to the pipe.
    const pipe_type &pipe() const & {return _pipe;}
    ///Get a rvalue reference to the pipe. Qualified as rvalue.
    pipe_type &&     pipe()  &&     {return std::move(_pipe);}

    ///Check if the pipe is open
    bool is_open() const {return _pipe.is_open(); }

    ///Open a new pipe
    basic_pipebuf<CharT, Traits>* open()
    {
        if (is_open())
            return nullptr;
        _pipe = pipe();
        return this;
    }

    ///Open a new named pipe
    basic_pipebuf<CharT, Traits>* open(const std::string & name)
    {
        if (is_open())
            return nullptr;
        _pipe = pipe(name);
        return this;
    }

    ///Flush the buffer & close the pipe
    basic_pipebuf<CharT, Traits>* close()
    {
        if (!is_open())
            return nullptr;
        overflow(Traits::eof());
        return this;
    }
private:
    pipe_type _pipe;
    std::vector<char_type> _write;
    std::vector<char_type> _read;

    bool _write_impl()
    {
        if (!_pipe.is_open())
            return false;

        auto base = this->pbase();

        if (base == this->pptr())
            return true;

        std::ptrdiff_t wrt = _pipe.write(base,
                static_cast<typename pipe_type::int_type>(this->pptr() - base));

        std::ptrdiff_t diff = this->pptr() - base;

        if (wrt < diff)
            std::move(base + wrt, base + diff, base);
        else if (wrt == 0) //broken pipe
            return false;

        this->pbump(static_cast<int>(-wrt));

        return true;
    }
};

typedef basic_pipebuf<char>     pipebuf;
typedef basic_pipebuf<wchar_t> wpipebuf;

/** Implementation of a reading pipe stream.
 *
 */
template<
    class CharT,
    class Traits = std::char_traits<CharT>
>
class basic_ipstream : public std::basic_istream<CharT, Traits>
{
    mutable basic_pipebuf<CharT, Traits> _buf;
public:

    typedef basic_pipe<CharT, Traits> pipe_type;

    typedef           CharT            char_type  ;
    typedef           Traits           traits_type;
    typedef  typename Traits::int_type int_type   ;
    typedef  typename Traits::pos_type pos_type   ;
    typedef  typename Traits::off_type off_type   ;

    ///Get access to the underlying stream_buf
    basic_pipebuf<CharT, Traits>* rdbuf() const {return &_buf;};

    ///Default constructor.
    basic_ipstream() : std::basic_istream<CharT, Traits>(nullptr)
    {
        std::basic_istream<CharT, Traits>::rdbuf(&_buf);
    };
    ///Copy constructor.
    basic_ipstream(const basic_ipstream & ) = delete;
    ///Move constructor.
    basic_ipstream(basic_ipstream && lhs) : std::basic_istream<CharT, Traits>(nullptr), _buf(std::move(lhs._buf))
    {
        std::basic_istream<CharT, Traits>::rdbuf(&_buf);
    }

    ///Move construct from a pipe.
    basic_ipstream(pipe_type && p)      : std::basic_istream<CharT, Traits>(nullptr), _buf(std::move(p))
    {
        std::basic_istream<CharT, Traits>::rdbuf(&_buf);
    }

    ///Copy construct from a pipe.
    basic_ipstream(const pipe_type & p) : std::basic_istream<CharT, Traits>(nullptr), _buf(p)
    {
        std::basic_istream<CharT, Traits>::rdbuf(&_buf);
    }

    ///Copy assignment.
    basic_ipstream& operator=(const basic_ipstream & ) = delete;
    ///Move assignment
    basic_ipstream& operator=(basic_ipstream && lhs)
    {
        std::basic_istream<CharT, Traits>::operator=(std::move(lhs));
        _buf = std::move(lhs._buf);
        std::basic_istream<CharT, Traits>::rdbuf(&_buf);
        return *this;
    };
    ///Move assignment of a pipe.
    basic_ipstream& operator=(pipe_type && p)
    {
        _buf = std::move(p);
        return *this;
    }
    ///Copy assignment of a pipe.
    basic_ipstream& operator=(const pipe_type & p)
    {
        _buf = p;
        return *this;
    }
    ///Set the pipe of the streambuf.
    void pipe(pipe_type&& p)      {_buf.pipe(std::move(p)); }
    ///Set the pipe of the streambuf.
    void pipe(const pipe_type& p) {_buf.pipe(p); }
    ///Get a reference to the pipe.
    pipe_type &      pipe() &       {return _buf.pipe();}
    ///Get a const reference to the pipe.
    const pipe_type &pipe() const & {return _buf.pipe();}
    ///Get a rvalue reference to the pipe. Qualified as rvalue.
    pipe_type &&     pipe()  &&     {return std::move(_buf).pipe();}
    ///Check if the pipe is open
    bool is_open() const {return _buf.is_open();}

    ///Open a new pipe
    void open()
    {
        if (_buf.open() == nullptr)
            this->setstate(std::ios_base::failbit);
        else
            this->clear();
    }

    ///Open a new named pipe
    void open(const std::string & name)
    {
        if (_buf.open() == nullptr)
            this->setstate(std::ios_base::failbit);
        else
            this->clear();
    }

    ///Flush the buffer & close the pipe
    void close()
    {
        if (_buf.close() == nullptr)
            this->setstate(std::ios_base::failbit);
    }
};

typedef basic_ipstream<char>     ipstream;
typedef basic_ipstream<wchar_t> wipstream;

/** Implementation of a write pipe stream.
 *
 */
template<
    class CharT,
    class Traits = std::char_traits<CharT>
>
class basic_opstream : public std::basic_ostream<CharT, Traits>
{
    mutable basic_pipebuf<CharT, Traits> _buf;
public:
    typedef basic_pipe<CharT, Traits> pipe_type;

    typedef           CharT            char_type  ;
    typedef           Traits           traits_type;
    typedef  typename Traits::int_type int_type   ;
    typedef  typename Traits::pos_type pos_type   ;
    typedef  typename Traits::off_type off_type   ;


    ///Get access to the underlying stream_buf
    basic_pipebuf<CharT, Traits>* rdbuf() const {return &_buf;};

    ///Default constructor.
    basic_opstream() : std::basic_ostream<CharT, Traits>(nullptr)
    {
        std::basic_ostream<CharT, Traits>::rdbuf(&_buf);
    };
    ///Copy constructor.
    basic_opstream(const basic_opstream & ) = delete;
    ///Move constructor.
    basic_opstream(basic_opstream && lhs) : std::basic_ostream<CharT, Traits>(nullptr), _buf(std::move(lhs._buf))
    {
        std::basic_ostream<CharT, Traits>::rdbuf(&_buf);
    }
    ///Move construct from a pipe.
    basic_opstream(pipe_type && p)      : std::basic_ostream<CharT, Traits>(nullptr), _buf(std::move(p))
    {
        std::basic_ostream<CharT, Traits>::rdbuf(&_buf);
    };
    ///Copy construct from a pipe.
    basic_opstream(const pipe_type & p) : std::basic_ostream<CharT, Traits>(nullptr), _buf(p)
    {
        std::basic_ostream<CharT, Traits>::rdbuf(&_buf);
    };
    ///Copy assignment.
    basic_opstream& operator=(const basic_opstream & ) = delete;
    ///Move assignment
    basic_opstream& operator=(basic_opstream && lhs)
    {
        std::basic_ostream<CharT, Traits>::operator=(std::move(lhs));
        _buf = std::move(lhs._buf);
        std::basic_ostream<CharT, Traits>::rdbuf(&_buf);
        return *this;
    };

    ///Move assignment of a pipe.
    basic_opstream& operator=(pipe_type && p)
    {
        _buf = std::move(p);
        return *this;
    }
    ///Copy assignment of a pipe.
    basic_opstream& operator=(const pipe_type & p)
    {
        _buf = p;
        return *this;
    }
    ///Set the pipe of the streambuf.
    void pipe(pipe_type&& p)      {_buf.pipe(std::move(p)); }
    ///Set the pipe of the streambuf.
    void pipe(const pipe_type& p) {_buf.pipe(p); }
    ///Get a reference to the pipe.
    pipe_type &      pipe() &       {return _buf.pipe();}
    ///Get a const reference to the pipe.
    const pipe_type &pipe() const & {return _buf.pipe();}
    ///Get a rvalue reference to the pipe. Qualified as rvalue.
    pipe_type &&     pipe()  &&     {return std::move(_buf).pipe();}

    ///Open a new pipe
    void open()
    {
        if (_buf.open() == nullptr)
            this->setstate(std::ios_base::failbit);
        else
            this->clear();
    }

    ///Open a new named pipe
    void open(const std::string & name)
    {
        if (_buf.open() == nullptr)
            this->setstate(std::ios_base::failbit);
        else
            this->clear();
    }

    ///Flush the buffer & close the pipe
    void close()
    {
        if (_buf.close() == nullptr)
            this->setstate(std::ios_base::failbit);
    }
};

typedef basic_opstream<char>     opstream;
typedef basic_opstream<wchar_t> wopstream;


/** Implementation of a read-write pipe stream.
 *
 */
template<
    class CharT,
    class Traits = std::char_traits<CharT>
>
class basic_pstream : public std::basic_iostream<CharT, Traits>
{
    mutable basic_pipebuf<CharT, Traits> _buf;
public:
    typedef basic_pipe<CharT, Traits> pipe_type;

    typedef           CharT            char_type  ;
    typedef           Traits           traits_type;
    typedef  typename Traits::int_type int_type   ;
    typedef  typename Traits::pos_type pos_type   ;
    typedef  typename Traits::off_type off_type   ;


    ///Get access to the underlying stream_buf
    basic_pipebuf<CharT, Traits>* rdbuf() const {return &_buf;};

    ///Default constructor.
    basic_pstream() : std::basic_iostream<CharT, Traits>(nullptr)
    {
        std::basic_iostream<CharT, Traits>::rdbuf(&_buf);
    };
    ///Copy constructor.
    basic_pstream(const basic_pstream & ) = delete;
    ///Move constructor.
    basic_pstream(basic_pstream && lhs) : std::basic_iostream<CharT, Traits>(nullptr), _buf(std::move(lhs._buf))
    {
        std::basic_iostream<CharT, Traits>::rdbuf(&_buf);
    }
    ///Move construct from a pipe.
    basic_pstream(pipe_type && p)      : std::basic_iostream<CharT, Traits>(nullptr), _buf(std::move(p))
    {
        std::basic_iostream<CharT, Traits>::rdbuf(&_buf);
    };
    ///Copy construct from a pipe.
    basic_pstream(const pipe_type & p) : std::basic_iostream<CharT, Traits>(nullptr), _buf(p)
    {
        std::basic_iostream<CharT, Traits>::rdbuf(&_buf);
    };
    ///Copy assignment.
    basic_pstream& operator=(const basic_pstream & ) = delete;
    ///Move assignment
    basic_pstream& operator=(basic_pstream && lhs)
    {
        std::basic_istream<CharT, Traits>::operator=(std::move(lhs));
        _buf = std::move(lhs._buf);
        std::basic_iostream<CharT, Traits>::rdbuf(&_buf);
        return *this;
    };
    ///Move assignment of a pipe.
    basic_pstream& operator=(pipe_type && p)
    {
        _buf = std::move(p);
        return *this;
    }
    ///Copy assignment of a pipe.
    basic_pstream& operator=(const pipe_type & p)
    {
        _buf = p;
        return *this;
    }
    ///Set the pipe of the streambuf.
    void pipe(pipe_type&& p)      {_buf.pipe(std::move(p)); }
    ///Set the pipe of the streambuf.
    void pipe(const pipe_type& p) {_buf.pipe(p); }
    ///Get a reference to the pipe.
    pipe_type &      pipe() &       {return _buf.pipe();}
    ///Get a const reference to the pipe.
    const pipe_type &pipe() const & {return _buf.pipe();}
    ///Get a rvalue reference to the pipe. Qualified as rvalue.
    pipe_type &&     pipe()  &&     {return std::move(_buf).pipe();}

    ///Open a new pipe
    void open()
    {
        if (_buf.open() == nullptr)
            this->setstate(std::ios_base::failbit);
        else
            this->clear();
    }

    ///Open a new named pipe
    void open(const std::string & name)
    {
        if (_buf.open() == nullptr)
            this->setstate(std::ios_base::failbit);
        else
            this->clear();
    }

    ///Flush the buffer & close the pipe
    void close()
    {
        if (_buf.close() == nullptr)
            this->setstate(std::ios_base::failbit);
    }
};

typedef basic_pstream<char>     pstream;
typedef basic_pstream<wchar_t> wpstream;



}}



#endif

/* pipe.hpp
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
*/