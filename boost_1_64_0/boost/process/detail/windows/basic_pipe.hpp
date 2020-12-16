// Copyright (c) 2016 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_WINDOWS_PIPE_HPP
#define BOOST_PROCESS_DETAIL_WINDOWS_PIPE_HPP

#include <boost/winapi/basic_types.hpp>
#include <boost/winapi/error_codes.hpp>
#include <boost/winapi/pipes.hpp>
#include <boost/winapi/handles.hpp>
#include <boost/winapi/file_management.hpp>
#include <boost/winapi/get_last_error.hpp>
#include <boost/winapi/access_rights.hpp>
#include <boost/winapi/process.hpp>
#include <boost/process/detail/windows/compare_handles.hpp>
#include <system_error>
#include <string>


namespace boost { namespace process { namespace detail { namespace windows {

template<class CharT, class Traits = std::char_traits<CharT>>
class basic_pipe
{
    ::boost::winapi::HANDLE_ _source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    ::boost::winapi::HANDLE_ _sink   = ::boost::winapi::INVALID_HANDLE_VALUE_;
public:
    typedef CharT                      char_type  ;
    typedef          Traits            traits_type;
    typedef typename Traits::int_type  int_type   ;
    typedef typename Traits::pos_type  pos_type   ;
    typedef typename Traits::off_type  off_type   ;
    typedef ::boost::winapi::HANDLE_ native_handle_type;

    explicit basic_pipe(::boost::winapi::HANDLE_ source, ::boost::winapi::HANDLE_ sink)
            : _source(source), _sink(sink) {}
    inline explicit basic_pipe(const std::string & name);
    inline basic_pipe(const basic_pipe& p);
    basic_pipe(basic_pipe&& lhs)  : _source(lhs._source), _sink(lhs._sink)
    {
        lhs._source = ::boost::winapi::INVALID_HANDLE_VALUE_;
        lhs._sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    }
    inline basic_pipe& operator=(const basic_pipe& p);
    inline basic_pipe& operator=(basic_pipe&& lhs);
    ~basic_pipe()
    {
        if (_sink   != ::boost::winapi::INVALID_HANDLE_VALUE_)
            ::boost::winapi::CloseHandle(_sink);
        if (_source != ::boost::winapi::INVALID_HANDLE_VALUE_)
            ::boost::winapi::CloseHandle(_source);
    }
    native_handle_type native_source() const {return _source;}
    native_handle_type native_sink  () const {return _sink;}

    void assign_source(native_handle_type h) { _source = h;}
    void assign_sink  (native_handle_type h) { _sink = h;}

    basic_pipe()
    {
        if (!::boost::winapi::CreatePipe(&_source, &_sink, nullptr, 0))
            throw_last_error("CreatePipe() failed");

    }

    int_type write(const char_type * data, int_type count)
    {
        ::boost::winapi::DWORD_ write_len;
        if (!::boost::winapi::WriteFile(
                _sink, data, count * sizeof(char_type), &write_len, nullptr
                ))
        {
            auto ec = ::boost::process::detail::get_last_error();
            if ((ec.value() == ::boost::winapi::ERROR_BROKEN_PIPE_) ||
                (ec.value() == ::boost::winapi::ERROR_NO_DATA_))
                return 0;
            else
                throw process_error(ec, "WriteFile failed");
        }
        return static_cast<int_type>(write_len);
    }
    int_type read(char_type * data, int_type count)
    {
        ::boost::winapi::DWORD_ read_len;
        if (!::boost::winapi::ReadFile(
                _source, data, count * sizeof(char_type), &read_len, nullptr
                ))
        {
            auto ec = ::boost::process::detail::get_last_error();
            if ((ec.value() == ::boost::winapi::ERROR_BROKEN_PIPE_) ||
                (ec.value() == ::boost::winapi::ERROR_NO_DATA_))
                return 0;
            else
                throw process_error(ec, "ReadFile failed");
        }
        return static_cast<int_type>(read_len);
    }

    bool is_open() const
    {
        return (_source != ::boost::winapi::INVALID_HANDLE_VALUE_) ||
               (_sink   != ::boost::winapi::INVALID_HANDLE_VALUE_);
    }

    void close()
    {
        ::boost::winapi::CloseHandle(_source);
        ::boost::winapi::CloseHandle(_sink);
        _source = ::boost::winapi::INVALID_HANDLE_VALUE_;
        _sink   = ::boost::winapi::INVALID_HANDLE_VALUE_;
    }
};

template<class Char, class Traits>
basic_pipe<Char, Traits>::basic_pipe(const basic_pipe & p)
{
    auto proc = ::boost::winapi::GetCurrentProcess();

    if (p._source == ::boost::winapi::INVALID_HANDLE_VALUE_)
        _source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, p._source, proc, &_source, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (p._sink == ::boost::winapi::INVALID_HANDLE_VALUE_)
        _sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, p._sink, proc, &_sink, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

}

template<class Char, class Traits>
basic_pipe<Char, Traits>::basic_pipe(const std::string & name)
{
    static constexpr int OPEN_EXISTING_         = 3; //temporary.
    static constexpr int FILE_FLAG_OVERLAPPED_  = 0x40000000; //temporary
    //static constexpr int FILE_ATTRIBUTE_NORMAL_ = 0x00000080; //temporary

#if BOOST_NO_ANSI_APIS
    std::wstring name_ = boost::process::detail::convert(name);
#else
    auto &name_ = name;
#endif
    ::boost::winapi::HANDLE_ source = ::boost::winapi::create_named_pipe(
            name_.c_str(),
            ::boost::winapi::PIPE_ACCESS_INBOUND_
            | FILE_FLAG_OVERLAPPED_, //write flag
            0, ::boost::winapi::PIPE_UNLIMITED_INSTANCES_, 8192, 8192, 0, nullptr);

    if (source == boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::process::detail::throw_last_error("create_named_pipe() failed");

    ::boost::winapi::HANDLE_ sink = boost::winapi::create_file(
            name.c_str(),
            ::boost::winapi::GENERIC_WRITE_, 0, nullptr,
            OPEN_EXISTING_,
            FILE_FLAG_OVERLAPPED_, //to allow read
            nullptr);

    if (sink == ::boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::process::detail::throw_last_error("create_file() failed");

    _source = source;
    _sink   = sink;
}

template<class Char, class Traits>
basic_pipe<Char, Traits>& basic_pipe<Char, Traits>::operator=(const basic_pipe & p)
{
    auto proc = ::boost::winapi::GetCurrentProcess();

    if (p._source == ::boost::winapi::INVALID_HANDLE_VALUE_)
        _source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, p._source, proc, &_source, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    if (p._sink == ::boost::winapi::INVALID_HANDLE_VALUE_)
        _sink = ::boost::winapi::INVALID_HANDLE_VALUE_;
    else if (!::boost::winapi::DuplicateHandle(
            proc, p._sink, proc, &_sink, 0,
            static_cast<::boost::winapi::BOOL_>(true),
             ::boost::winapi::DUPLICATE_SAME_ACCESS_))
        throw_last_error("Duplicate Pipe Failed");

    return *this;
}

template<class Char, class Traits>
basic_pipe<Char, Traits>& basic_pipe<Char, Traits>::operator=(basic_pipe && lhs)
{
    if (_source != ::boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::winapi::CloseHandle(_source);

    if (_sink != ::boost::winapi::INVALID_HANDLE_VALUE_)
        ::boost::winapi::CloseHandle(_sink);

    _source = lhs._source;
    _sink   = lhs._sink;
    lhs._source = ::boost::winapi::INVALID_HANDLE_VALUE_;
    lhs._sink   = ::boost::winapi::INVALID_HANDLE_VALUE_;
    return *this;
}

template<class Char, class Traits>
inline bool operator==(const basic_pipe<Char, Traits> & lhs, const basic_pipe<Char, Traits> & rhs)
{
    return compare_handles(lhs.native_source(), rhs.native_source()) &&
           compare_handles(lhs.native_sink(),   rhs.native_sink());
}

template<class Char, class Traits>
inline bool operator!=(const basic_pipe<Char, Traits> & lhs, const basic_pipe<Char, Traits> & rhs)
{
    return !compare_handles(lhs.native_source(), rhs.native_source()) ||
           !compare_handles(lhs.native_sink(),   rhs.native_sink());
}

}}}}

#endif

/* basic_pipe.hpp
pTDt3/hPkpcn7XDJMVNYUJRbPGLcWOMWldd6Ob+GxzczeAZG2Ew4iSXns8xn1Xi+lMnzpQLnOkdVdz0jnzf/5rqjjbvc3Z3J3nRjDMZ687wxvPGZxpoGb/aFX+tYFRFp7IzoYNSPvNc4HtnRkRHNF5Gj7zfaxEQbgwjTY7oYp2BK7Akjucwux/m4cH3c3CFj42pGGnXT57PxsYHzGdem+pw2zVHeuYKXXTa7LuPtv794volY6bgj6o/Oa2JdRlqJOfA6RxTeDz+nlCRHDcZNVekjw/dOq/TRZ6lb1ZwYPAYYAbrPz97pP4e3UWM7Q8bjiMiqxouOss51zjs8ScZjnnJGcliy0TysivEazPCm8EzxZsfsiClGPc49wWNHzjH62eGl3AvMdK90+581RFO/MjKm3kpdX+mCZ64yN9VS88tS2YdpCV5jo3OnM87zvvdD57uRnzmPxNR0eMokuQJz4aH7rM83WC+U7bfDaxoPh9s9gzGPu9d4nrDVUUE9J/DLpkd24GniaUdtjr95Drt31WiHfHd+ufRzj7RKqdZjQy52dP+ekmMhXvfR9+axIb7Jj0se0Wlv0RfmXDxWJmLrWkuy9G1z/7tder6vEluee+dJzCnmNTYPQOSUYaYdKeeKtqHTWu9VxsiDEHPtRdJGWt99Nd/nl35OMqqVnMtcF85lPR2R+lp8is77XdFvIn23RtpdNMKw3CclSP5j/WsiOv/GrnC+hHoPVtgrHPWM047mDss57IJ++1TS5JGH9Rw/P5xzPGf6tx3rnMXuk176wHw/XB52WuvxlqRpLfWsVAmB+s6/Xu+QekZI/K6ycv1RIr6fxMdYnmNMkAcZgTouXO+f5+r566if77cxXnO2YAw+ENbdaOWNMDK95Yxi7pHTIvxlHfTnNcJ6P1WwvuS1yEjZ7uI/JnXeqRFufJy3cBW7ffksUflY5/Spki7Jdr/Pk+O6L/1eIk+X2yjr+qV9EXW/34dDhQvu3auzClCb+/df3g+rRX+V2lbp2bJpg+hfJuUNtdG334/Z6n7GPJbUqoV1PG2S90zRYVvPK8WOFw3qrttefEHbH5VrpfI63f2y/bgRJbJu8fdGYI9YS/lqj7lp1q/x1b5Y5u5I8U8eyKO4VsBX+01jbHysi85Ws5zev6acfJtyjpvltA1VjlFblRM5d7EuJ0inRu1APnNvDM4nRelkmfkMjWbWD5VXoZnXlaHqtETnNS8qVD5bzXy+D1WnE2ad3vmlOrnr6Lz2h8qrATpXJ0idpvxSXj3rBPznz8sM1b5idBrHoxMx7/GAzoYgnWXoPIAMnWNaJ7h96KwRnZvbRXMd+mvGSY8VcvyUbH/dQPtvjgxV5zp1A+NxwVOh2p6l81mwMlQ+hWY+c0Pls8TMpyjk8VE30M8LI0Lu/7qBfbawfbQrLvT+r4fdWTx6SbffHNB5SOlUUDrN6ql9Fr34oWj3jI3R4R67bxlo/WvQb+rT9yzeE+3xRnPC1eVvDCp/NrpJKeh67xgSrJMWaG89NR7cdxZFh4dFu2cmR4dHGbZ10O0nzSbpxzuXRHsigsvXeuH1td486hpSrxF6A339GbaiYrQrUuttCdLrj95mGZcrZ1r7fUtQu6839aaE0llj6lQMpfOsqZMQSufj+mofx674Tu/jIJ3oBlrn01A6jRqossJXLgsuq7vrqvjDbF8SH/od/WT2cwpBbYcMfeM1tWyr4mQJpnyb0D48E7T9muIyxbLUpRyhPKECoS3l7UA+KMH0F7Bbv69PGit/w9+SXoWdejuIfyM8q3gLYS/hAeWPYHCCtAtLaonj75L8mbDH0vcVCS+xPUqlr8T2iAT+NmVWXUmbgfwR2BE=
*/