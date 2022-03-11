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
        if (is_open())
            overflow(Traits::eof());
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
                *this->pptr() = ch;
                this->pbump(1);
                if (wr)
                    return ch;
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

        this->pbump(-wrt);

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